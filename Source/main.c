/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"
#include "lh32_clock.h"
#include "lh32_gpio.h"
#include "lh32_spi.h"
#include "lh32_i2c.h"
#include "lh32_adc.h"
#include "lh32_uart.h"
#include "lh32_dac8562.h"
#include "lh32_eeprom.h"

/* Private define ------------------------------------------------------------*/ 
uint8_t I2C_RX_Data[10], I2C_TX_Data[10];

/* ---------- ADC 原始码 -> 输入电压 ----------
 * 基准电压 / PGA 增益 / 负端接法 统一定义在 Include/lh32_adc.h
 * (ADC_VREF_MV / SENSOR_PGA / SENSOR_AINM_MODE), 这里不再各写一份
 * 正满量程(相对负端) = ADC_VREF_MV / PGA增益 */
#define ADC_PGA_GAIN        1.0f
#define ADC_FULLSCALE_MV    (ADC_VREF_MV / ADC_PGA_GAIN)

/* DAC 输出满量程(单位: V), 直接由 DAC 驱动参数推导, 改增益时会自动跟随 */
#define DAC_VOUT_MAX_V      (DAC8562_INTERNAL_REF_V * (float)DAC8562_GAIN)

/* ---------- 传感器输入 -> DAC 输出 映射 ----------
 * 输出侧固定: 0V ~ 2.5V, 中值(零值) 1.25V, 不做配置。
 * 输入侧可配: 零值 in_zero, 极值幅值 in_span(量程 = 零值 ± 幅值)。
 *   vout = 1.25V + (vin - in_zero) * 1.25V / in_span
 * 默认: in_zero=0V, in_span=2.5V
 *   => 输入 -2.5V ~ +2.5V 线性映射到输出 0V ~ 2.5V, 输入 0V 输出 1.25V
 * 两个输入参数都可以通过串口命令修改(见下方协议)。 */
#define SENSOR_VIN_LIMIT_V  2.5f               /* 输入零值/极值允许的最大幅值 */
#define DAC_OUT_ZERO_V      (DAC_VOUT_MAX_V * 0.5f)   /* 输出中值, 固定 1.25V */
#define DAC_OUT_SPAN_V      (DAC_VOUT_MAX_V * 0.5f)   /* 输出半幅宽, 固定 1.25V */

typedef struct {
    float in_zero_v;                       /* 输入零值                       */
    float in_span_v;                       /* 输入极值幅值(量程 = 零值 ± 它) */
} MAP_Params_t;

static MAP_Params_t g_map = {
    0.001f,
    2.5f
};

typedef struct {
    float fx_zero_v;
    float fz_zero_v;
    uint8_t zero_flag;
    float fx_sum;
    float fz_sum;
    uint8_t zero_count;
} ZERO_Params_t;

/* volatile: -O2 下编译器会把这种没被外部引用的 static 结构体拆成
 * 每个成员单独的变量(符号只剩 g_zero.0/.1/...), 调试器就找不到 g_zero 的位置 */
static volatile ZERO_Params_t g_zero = {
    0.0f,
    0.0f,
    0,
    0.0f,
    0.0f,
    0
};

/* ---------- 串口调试打印开关 ---------- */
#define UART_DEBUG          0

/* 供 Debug 的 watch 窗口直接观察。volatile 防止被优化掉。 */
volatile int32_t g_fz_raw, g_fx_raw;
volatile float g_fz_mv, g_fx_mv;                /* 传感器输入电压(FZ / FX) */
float    vout_fz, vout_fx;
int32_t  fz_raw, fx_raw;

/* Global variable -----------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/* =================== 串口命令协议 ===================
 * 帧格式: AA 55 | CMD | [参数(int16 小端, 单位 mV)] | 0D 0A
 *
 *   0x30 清零(输入参数恢复默认)          AA 55 30 0D 0A
 *   0x40 设置输入零值(mV)                AA 55 40 LL HH 0D 0A
 *   0x41 设置输入极值(mV, 取绝对值, 对称) AA 55 41 LL HH 0D 0A
 *
 * 输出侧固定 0~2.5V(中值 1.25V), 不提供配置命令。
 * 举例(单位 mV):
 *   输入极值设 1V    : AA 55 41 E8 03 0D 0A
 *   输入极值设 -1.5V : AA 55 41 24 FA 0D 0A   (取绝对值 -> ±1.5V)
 */
#define PROTO_HEAD0             0xAAu
#define PROTO_HEAD1             0x55u
#define PROTO_TAIL0             0x0Du
#define PROTO_TAIL1             0x0Au

#define PROTO_CMD_CLEAR         0x30u
#define PROTO_CMD_IN_ZERO       0x40u
#define PROTO_CMD_IN_SPAN       0x41u

/* 接收组帧状态 */
enum {
    RX_ST_HEAD0 = 0,
    RX_ST_HEAD1,
    RX_ST_CMD,
    RX_ST_DATA_L,
    RX_ST_DATA_H,
    RX_ST_TAIL0,
    RX_ST_TAIL1
};

static uint8_t  rx_state;
static uint8_t  rx_cmd;
static uint16_t rx_data;

/**
  * @brief  执行一条已经完整校验过的命令
  * @param  cmd : 命令码
  * @param  mv  : 参数, 单位 mV(0x30 无参数)
  */
static void proto_exec(uint8_t cmd, int16_t mv)
{
    float v = (float)mv * 0.001f;

    switch (cmd)
    {
    case PROTO_CMD_CLEAR:
        g_zero.zero_flag = 1;
        break;

    case PROTO_CMD_IN_ZERO:                     /* 输入零值: -2.5V ~ +2.5V */
        if (v < -SENSOR_VIN_LIMIT_V) v = -SENSOR_VIN_LIMIT_V;
        if (v >  SENSOR_VIN_LIMIT_V) v =  SENSOR_VIN_LIMIT_V;
        g_map.in_zero_v = v;
        break;

    case PROTO_CMD_IN_SPAN:                     /* 输入极值: 只给一端, 取幅值 -> ±幅值 */
        if (v < 0.0f) v = -v;
        if (v > SENSOR_VIN_LIMIT_V) v = SENSOR_VIN_LIMIT_V;
        g_map.in_span_v = v;
        break;

    default:
        break;
    }
}

/**
  * @brief  回复命令应答帧: AA 55 (cmd | 0x80) 0D 0A
  * @param  cmd : 刚执行成功的命令码
  */
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

/**
  * @brief  往接收状态机里喂一个字节, 凑齐一帧就执行命令
  * @param  byte : 收到的字节
  */
static void proto_feed(uint8_t byte)
{
    switch (rx_state)
    {
    case RX_ST_HEAD0:
        if (byte == PROTO_HEAD0) rx_state = RX_ST_HEAD1;
        break;

    case RX_ST_HEAD1:
        if (byte == PROTO_HEAD1)              rx_state = RX_ST_CMD;
        else if (byte != PROTO_HEAD0)         rx_state = RX_ST_HEAD0;  /* 连续 0xAA 继续等 */
        break;

    case RX_ST_CMD:
        if (byte == PROTO_CMD_CLEAR)
        {
            rx_cmd   = byte;
            rx_state = RX_ST_TAIL0;
        }
        else if ((byte == PROTO_CMD_IN_ZERO) || (byte == PROTO_CMD_IN_SPAN))
        {
            rx_cmd   = byte;
            rx_state = RX_ST_DATA_L;
        }
        else
        {
            rx_state = (byte == PROTO_HEAD0) ? RX_ST_HEAD1 : RX_ST_HEAD0;
        }
        break;

    case RX_ST_DATA_L:
        rx_data  = byte;
        rx_state = RX_ST_DATA_H;
        break;

    case RX_ST_DATA_H:
        rx_data |= (uint16_t)((uint16_t)byte << 8);
        rx_state = RX_ST_TAIL0;
        break;

    case RX_ST_TAIL0:
        if (byte == PROTO_TAIL0)              rx_state = RX_ST_TAIL1;
        else                                  rx_state = (byte == PROTO_HEAD0) ? RX_ST_HEAD1 : RX_ST_HEAD0;
        break;

    case RX_ST_TAIL1:
        if (byte == PROTO_TAIL1)
        {
            proto_exec(rx_cmd, (int16_t)rx_data);
            proto_ack(rx_cmd);
        }
        rx_state = (byte == PROTO_HEAD0) ? RX_ST_HEAD1 : RX_ST_HEAD0;
        break;

    default:
        rx_state = RX_ST_HEAD0;
        break;
    }
}

/**
  * @brief  传感器输入电压 -> DAC 目标输出电压
  * @param  vin_mv : 传感器输入电压, 单位 **mV** (主循环直接喂 g_fz_mv / g_fx_mv)
  * @retval DAC 目标输出电压, 单位 **V** (0 ~ DAC_VOUT_MAX_V)
  * @note   输出侧固定 0~2.5V(中值 1.25V), 只按输入端零值/极值线性映射
  */
static float sensor_mv_to_dac_v(float vin_mv)
{
    float vin_v = vin_mv * 0.001f;
    float vout_v;

    if (g_map.in_span_v < 0.001f)              /* 输入极值被设成 0, 避免除零 */
    {
        vout_v = DAC_OUT_ZERO_V;
    }
    else
    {
        vout_v = DAC_OUT_ZERO_V
               + (vin_v - g_map.in_zero_v) * DAC_OUT_SPAN_V / g_map.in_span_v;
    }

    if (vout_v < 0.0f) vout_v = 0.0f;
    if (vout_v > DAC_VOUT_MAX_V) vout_v = DAC_VOUT_MAX_V;

    return vout_v;
}

static void zero_init(void)
{
    g_zero.fx_sum = 0;
    g_zero.fx_zero_v = 0;
    g_zero.fz_sum = 0;
    g_zero.fz_zero_v = 0;
    g_zero.zero_count = 0;
    g_zero.zero_flag = 0;
}

static void calib_zero_cale(float fx, float fz)
{
    g_zero.fx_sum += fx;
    g_zero.fz_sum += fz;

    g_zero.zero_count++;
    if (g_zero.zero_count >= 20) {
        g_zero.fx_zero_v = g_zero.fx_sum / 20.0f;
        g_zero.fz_zero_v = g_zero.fz_sum / 20.0f;
        
        g_zero.zero_flag = 0;
        g_zero.zero_count = 0;
    }
}

/**
  * @brief  串口处理: 把接收环形缓冲里的字节逐个喂给协议状态机
  * @note   中断只负责收字节, 解析/执行全部在主循环里做
  */
static void uart_process(void)
{
    while (uart_rx_count != uart_tx_count)
    {
        proto_feed(uart_buffer[uart_tx_count++]);
    }
}

int main(void)
{
    /* 上电后IWDG默认开启，若无处理约20秒后复位 */
    LHL_IWDG_Stop();

    /* 复位所有GPIO默认状态 */
    LHL_GPIO_DeInit();

    /* 系统时钟: 配置为内部 HSI 二分频 = 16MHz -> SYSCLK=HCLK=PCLK1=PCLK2=16MHz */
    clock_init();

    /* Init Config */
    gpio_init();
    uart_init();
//    spi_init();
    i2c_init();
    adc_init();
//    eeprom_init();

    /* DAC8562 上电配置: 软件复位 + 双通道上电 + 使能内部基准 + 设置增益 */
    dac8562_init();
    zero_init();

    uart_rx_count = 0;
    uart_tx_count = 0;
    g_map.in_zero_v = 0.001;

    printf("hello world\r\n");

    while(1) {
        /* ---- 1) 24位补码 -> 有符号, 换算成传感器输入电压(mV) ---- */
        g_fz_raw = fz_raw = ((int32_t)dADCBuffer.ADC0_Data << 8) >> 8;   /* AIN0 = FZ */
        g_fx_raw = fx_raw = ((int32_t)dADCBuffer.ADC1_Data << 8) >> 8;   /* AIN1 = FX */

        /* 负端 = AVSS 的经典单端测量: Vin(mV) = 码/2^23 × Vref(量程 0 ~ +Vref) */
        g_fz_mv = (float)fz_raw / 8388608.0f * ADC_FULLSCALE_MV;
        g_fx_mv = (float)fx_raw / 8388608.0f * ADC_FULLSCALE_MV;
        g_fz_mv = (-g_fz_mv);

        /* ---- 2) 输入电压 -> 目标输出电压: 按 g_map 的零值/极值线性映射 ----
         *      sensor_mv_to_dac_v() 入参 mV、返回 V, 直接喂给 DAC 驱动 */
        vout_fz = sensor_mv_to_dac_v(g_fz_mv);
        vout_fx = sensor_mv_to_dac_v(g_fx_mv);

        if (g_zero.zero_flag == 1) {
            calib_zero_cale(vout_fx, vout_fz);
        }

        vout_fz -= g_zero.fz_zero_v;
        vout_fx -= g_zero.fx_zero_v;

        /* ---- 3) 双通道同步写入 DAC (电压->码, LDAC 同步更新) ---- */
        dac8562_write_both(dac8562_voltage_to_code(vout_fx), dac8562_voltage_to_code(vout_fz));

#if (UART_DEBUG)
        /* ---- 4) 串口打印: 仅在新样本到达时打印, 不重复刷同一组 ----
         * 全部用整数打印(%d), 不用 %f: MicroLIB 的 printf 浮点支持要额外配置,
         * 而这里 mV 精度到 1mV 已经足够观察。 */
        if (g_adc_seq != last_seq)
        {
            last_seq = g_adc_seq;
            printf("FZ raw=%d mV=%d out=%dmV | FX raw=%d mV=%d out=%dmV\r\n",
                   (int)g_fz_raw, (int)g_fz_mv, (int)g_fz_vout_mv,
                   (int)g_fx_raw, (int)g_fx_mv, (int)g_fx_vout_mv);
        }
#endif

        uart_process();
    }
}
/*********************************End of File**********************************/
