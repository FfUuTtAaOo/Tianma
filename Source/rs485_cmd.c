#include "rs485_cmd.h"
#include "lh32_i2c.h"

/* ============================== 内部状态 ============================== */

/* 输出格式 */
#define OUT_HEX             0u
#define OUT_ASCII           1u

/* 测量值 */
#define MEAS_KG             0u          /* y = a*x^2 + b*x + c          */
#define MEAS_N              1u          /* y × 9.80665                  */
#define MEAS_MV             2u          /* 原始电压 mV                  */

/* 重力加速度: N = kg × 9.80665 */
#define GRAVITY             9.80665f

static uint8_t  out_mode   = OUT_HEX;
static uint8_t  meas_mode  = MEAS_KG;
static uint8_t  stream_on;              /* 0x02 打开, 0x01 关闭 */
static uint8_t  single_pend;            /* 0x03 请求, 等下一个新采样应答 */
static float    latest_mv;

/* y = a*x^2 + b*x + c, x 单位 mV, y 单位 kg。
 * 默认 a=0,b=1,c=0: 未标定时直接输出电压读数, 写入系数后即按多项式换算。 */
static float    coef_a = 0.0f;
static float    coef_b = 1.0f;
static float    coef_c = 0.0f;

/* a/b/c 在 AT24C04 中的布局: 0x00~0x03 = a, 0x04~0x07 = b, 0x08~0x0B = c */
#define COEF_EEPROM_ADDR        0x0000u
#define COEF_EEPROM_BYTES       12u

extern volatile uint8_t uart_rx_count;
extern volatile uint8_t uart_tx_count;

/* 解析状态机(按负载长度收字节, 浮点数据里的 0D/0A 不会被误当帧尾) */
enum {
    P_HEAD0 = 0,
    P_HEAD1,
    P_CMD,
    P_DATA,
    P_TAIL0,
    P_TAIL1
};

static uint8_t p_state = P_HEAD0;
static uint8_t p_cmd;
static uint8_t p_idx;
static uint8_t p_len;
static uint8_t p_buf[5];

/* ============================== 小工具 ================================ */

/* 数据帧用的 float 小端序: 00 00 C0 3F = 1.5f */
static void put_f32_le(uint8_t *p, float v)
{
    union {
        float    f;
        uint32_t u;
    } cv;

    cv.f = v;
    p[0] = (uint8_t)(cv.u);
    p[1] = (uint8_t)(cv.u >> 8);
    p[2] = (uint8_t)(cv.u >> 16);
    p[3] = (uint8_t)(cv.u >> 24);
}

/* 系数指令 / EEPROM 统一用大端: 3F C0 00 00 = 1.5f, 3F 80 00 00 = 1.0f。
 * 上位机下发和 EEPROM 里的字节顺序完全一致, 方便直接核对 dump。 */
static void put_f32_be(uint8_t *p, float v)
{
    union {
        float    f;
        uint32_t u;
    } cv;

    cv.f = v;
    p[0] = (uint8_t)(cv.u >> 24);
    p[1] = (uint8_t)(cv.u >> 16);
    p[2] = (uint8_t)(cv.u >> 8);
    p[3] = (uint8_t)(cv.u);
}

static float get_f32_be(const uint8_t *p)
{
    union {
        float    f;
        uint32_t u;
    } cv;

    cv.u = ((uint32_t)p[0] << 24)
         | ((uint32_t)p[1] << 16)
         | ((uint32_t)p[2] << 8)
         | (uint32_t)p[3];
    return cv.f;
}

/* ---------------------- 系数掉电保存(AT24C04) ---------------------- */

/* NaN / inf 都判为无效: 新片读出全 0xFF 时, float 就是 NaN */
static uint8_t coef_is_valid(float f)
{
    return (uint8_t)((f == f) && (f < 1.0e30f) && (f > -1.0e30f));
}

static void coef_store(void)
{
    uint8_t buf[COEF_EEPROM_BYTES];

    put_f32_be(&buf[0], coef_a);
    put_f32_be(&buf[4], coef_b);
    put_f32_be(&buf[8], coef_c);

    /* 逐字节写, 内部每字节等满一个写周期; 12 字节约 60ms */
    (void)at24c04_write(COEF_EEPROM_ADDR, buf, COEF_EEPROM_BYTES);
}

void rs485_init(void)
{
    uint8_t buf[COEF_EEPROM_BYTES];
    uint8_t i;
    uint8_t all_ff = 1u;
    float   a, b, c;

    /* AT24C04 上电后 tPOR(约 1ms) 内不接受命令, 等一会再读 */
    LHL_Delay_uS(2000u);

    if (at24c04_read(COEF_EEPROM_ADDR, buf, COEF_EEPROM_BYTES) != LHL_OK)
    {
        return;                             /* 读失败: 保持代码里的默认值 */
    }

    for (i = 0u; i < COEF_EEPROM_BYTES; i++)
    {
        if (buf[i] != 0xFFu)
        {
            all_ff = 0u;
            break;
        }
    }
    if (all_ff != 0u)
    {
        return;                             /* 空白芯片(全 F): 用默认值 */
    }

    a = get_f32_be(&buf[0]);
    b = get_f32_be(&buf[4]);
    c = get_f32_be(&buf[8]);

    if ((coef_is_valid(a) == 0u) || (coef_is_valid(b) == 0u) || (coef_is_valid(c) == 0u))
    {
        return;                             /* 数据损坏(写一半掉电等): 用默认值 */
    }

    coef_a = a;
    coef_b = b;
    coef_c = c;
}

/* 无符号整数转十进制, 返回写入的字符数(不补前导零) */
static uint8_t put_uint(char *p, uint32_t v)
{
    char    tmp[10];
    uint8_t n = 0u;
    uint8_t i;

    do {
        tmp[n++] = (char)('0' + (v % 10u));
        v /= 10u;
    } while (v != 0u);

    for (i = 0u; i < n; i++) {
        p[i] = tmp[n - 1u - i];
    }
    return n;
}

/* "channel: 1.500000\r\n" —— 手工格式化, 不依赖 MicroLIB 的 %f */
static uint16_t fmt_ascii(char *buf, float v)
{
    static const char prefix[] = "channel: ";
    uint16_t n = 0u;
    uint8_t  i;
    char     frac[6];
    uint32_t ip;
    uint32_t fp;

    for (i = 0u; prefix[i] != '\0'; i++) {
        buf[n++] = prefix[i];
    }

    if (v < 0.0f) {
        buf[n++] = '-';
        v = -v;
    }
    if (v > 1.0e9f) {                   /* 防 uint32 溢出, 正常量程远达不到 */
        v = 1.0e9f;
    }

    ip = (uint32_t)v;
    fp = (uint32_t)((v - (float)ip) * 1000000.0f + 0.5f);
    if (fp >= 1000000u) {               /* 四舍五入进位 */
        fp = 0u;
        ip++;
    }

    n += put_uint(&buf[n], ip);
    buf[n++] = '.';

    for (i = 0u; i < 6u; i++) {
        frac[5u - i] = (char)('0' + (fp % 10u));
        fp /= 10u;
    }
    for (i = 0u; i < 6u; i++) {
        buf[n++] = frac[i];
    }

    buf[n++] = '\r';
    buf[n++] = '\n';
    return n;
}

/* ============================== 数据发送 ============================== */

static void send_value(uint8_t cmd, float mv)
{
    float y = coef_a * mv * mv + coef_b * mv + coef_c;
    float v;

    if (meas_mode == MEAS_MV) {
        v = mv;
    } else if (meas_mode == MEAS_N) {
        v = y * GRAVITY;
    } else {
        v = y;
    }

    if (out_mode == OUT_ASCII) {
        char     buf[32];
        uint16_t n = fmt_ascii(buf, v);
        uart_send((const uint8_t *)buf, n);
    } else {
        uint8_t frame[9];

        frame[0] = PROTO_HEAD0;
        frame[1] = PROTO_HEAD1;
        frame[2] = cmd;
        put_f32_le(&frame[3], v);
        frame[7] = PROTO_TAIL0;
        frame[8] = PROTO_TAIL1;
        uart_send(frame, sizeof(frame));
    }
}

/* ============================== 指令处理 ============================== */

static void proto_ack(uint8_t cmd)
{
    uint8_t frame[5];

    frame[0] = PROTO_HEAD0;
    frame[1] = PROTO_HEAD1;
    frame[2] = (uint8_t)(cmd | 0x80u);
    frame[3] = PROTO_TAIL0;
    frame[4] = PROTO_TAIL1;

    uart_send(frame, sizeof(frame));
}

static uint8_t proto_known(uint8_t cmd)
{
    switch (cmd)
    {
    case PROTO_CMD_STOP:
    case PROTO_CMD_START:
    case PROTO_CMD_SINGLE:
    case PROTO_CMD_BAUD:
    case PROTO_CMD_COEF:
    case PROTO_CMD_ZERO:
    case PROTO_CMD_OUT_HEX:
    case PROTO_CMD_OUT_ASCII:
    case PROTO_CMD_UNIT_KG:
    case PROTO_CMD_RAW_MV:
    case PROTO_CMD_UNIT_N:
    case PROTO_CMD_ZERO_CANCEL:
        return 1u;

    default:
        return 0u;
    }
}

/* 除 0x20 / 0x04 外都没有负载 */
static uint8_t proto_len(uint8_t cmd)
{
    if (cmd == PROTO_CMD_COEF) {
        return 5u;
    }
    if (cmd == PROTO_CMD_BAUD) {
        return 1u;
    }
    return 0u;
}

static void proto_flush_rx(void)
{
    uart_tx_count = uart_rx_count;      /* 丢弃旧波特率残留的字节 */
}

static void proto_exec(void)
{
    switch (p_cmd)
    {
    case PROTO_CMD_STOP:
        stream_on = 0u;
        proto_ack(PROTO_CMD_STOP);
        break;

    case PROTO_CMD_START:
        /* 应答就是一帧 cmd=0x02 的数据, 不额外回 ACK */
        stream_on = 1u;
        break;

    case PROTO_CMD_SINGLE:
        /* 等下一个新采样再回, 保证是"刚采到的"数据 */
        single_pend = 1u;
        break;

    case PROTO_CMD_BAUD:
    {
        uint32_t baud = 0u;

        switch (p_buf[0])
        {
        case 1u: baud = 460800u; break;
        case 2u: baud = 256000u; break;
        case 3u: baud = 115200u; break;
        case 4u: baud = 19200u;  break;
        case 5u: baud = 9600u;   break;
        default: break;
        }

        proto_ack(PROTO_CMD_BAUD);      /* 必须在旧波特率下发完 */
        if (baud != 0u) {
            uart_set_baud(baud);
        }
        proto_flush_rx();
        p_state = P_HEAD0;
        break;
    }

    case PROTO_CMD_COEF:
    {
        float f = get_f32_be(&p_buf[1]);

        switch (p_buf[0])
        {
        case 1u: coef_a = f; break;
        case 2u: coef_b = f; break;
        case 3u: coef_c = f; break;
        default: break;
        }
        proto_ack(PROTO_CMD_COEF);
        if ((p_buf[0] >= 1u) && (p_buf[0] <= 3u))
        {
            coef_store();                   /* 应答先发, 再落盘(约 60ms) */
        }
        break;
    }

    case PROTO_CMD_ZERO:
        g_zero.zero_flag  = 1u;
        g_zero.zero_count = 0u;
        g_zero.fz_sum     = 0.0f;
        proto_ack(PROTO_CMD_ZERO);
        break;

    case PROTO_CMD_ZERO_CANCEL:
        g_zero.zero_flag  = 0u;
        g_zero.zero_count = 0u;
        g_zero.fz_sum     = 0.0f;
        g_zero.fz_zero_v  = 0.0f;
        proto_ack(PROTO_CMD_ZERO_CANCEL);
        break;

    case PROTO_CMD_OUT_HEX:
        out_mode = OUT_HEX;
        proto_ack(PROTO_CMD_OUT_HEX);
        break;

    case PROTO_CMD_OUT_ASCII:
        out_mode = OUT_ASCII;
        proto_ack(PROTO_CMD_OUT_ASCII);
        break;

    case PROTO_CMD_UNIT_KG:
        meas_mode = MEAS_KG;
        proto_ack(PROTO_CMD_UNIT_KG);
        break;

    case PROTO_CMD_UNIT_N:
        meas_mode = MEAS_N;
        proto_ack(PROTO_CMD_UNIT_N);
        break;

    case PROTO_CMD_RAW_MV:
        meas_mode = MEAS_MV;
        proto_ack(PROTO_CMD_RAW_MV);
        break;

    default:
        break;
    }
}

/* ============================== 帧解析 ================================ */

/* 失步后重新找帧头; 若当前字节就是 0xAA, 直接进入 HEAD1 */
static void proto_resync(uint8_t byte)
{
    p_state = (byte == PROTO_HEAD0) ? P_HEAD1 : P_HEAD0;
}

static void proto_feed(uint8_t byte)
{
    switch (p_state)
    {
    case P_HEAD0:
        if (byte == PROTO_HEAD0) {
            p_state = P_HEAD1;
        }
        break;

    case P_HEAD1:
        if (byte == PROTO_HEAD1) {
            p_state = P_CMD;
        } else {
            proto_resync(byte);
        }
        break;

    case P_CMD:
        if (!proto_known(byte)) {
            proto_resync(byte);
            break;
        }
        p_cmd   = byte;
        p_len   = proto_len(byte);
        p_idx   = 0u;
        p_state = (p_len != 0u) ? P_DATA : P_TAIL0;
        break;

    case P_DATA:
        p_buf[p_idx++] = byte;
        if (p_idx >= p_len) {
            p_state = P_TAIL0;
        }
        break;

    case P_TAIL0:
        if (byte == PROTO_TAIL0) {
            p_state = P_TAIL1;
        } else {
            proto_resync(byte);
        }
        break;

    case P_TAIL1:
        if (byte == PROTO_TAIL1) {
            proto_exec();
        }
        proto_resync(byte);
        break;

    default:
        p_state = P_HEAD0;
        break;
    }
}

void uart_process(void)
{
    while (uart_rx_count != uart_tx_count)
    {
        proto_feed(uart_buffer[uart_tx_count++]);
    }
}

/* ============================== 周期上报 ============================== */

void rs485_report(float voltage_mv)
{
    latest_mv = voltage_mv;

    if (stream_on != 0u) {
        send_value(PROTO_CMD_START, latest_mv);
    }

    if (single_pend != 0u) {
        single_pend = 0u;
        send_value(PROTO_CMD_SINGLE, latest_mv);
    }
}
