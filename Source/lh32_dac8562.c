/******************************************************************************
 * DAC8562 驱动实现 (TI DAC8562S, 16-bit 双通道电压输出 DAC)
 ******************************************************************************
 * 24 位数据帧:  DB23 DB22 | DB21 DB20 DB19 | DB18 DB17 DB16 | DB15 ... DB0
 *                   X  X  |   C2   C1   C0 |   A2   A1   A0 |  16 位数据
 ******************************************************************************/
#include "lh32_dac8562.h"

/* 引脚定义 ----------------------------------------------------------------
 * ⚠️ P1.5/P1.6 已让给 UART0 (SIN0/SOUT0), 所以 LDAC/CLR 移到了 P1.1/P1.4,
 *    必须与 gpio_init() 里配置的引脚一致。 */
#define DAC8562_SYNC_PORT       pGPIO0
#define DAC8562_SYNC_PIN        GPIO_PIN_3

#define DAC8562_LDAC_PORT       pGPIO1
#define DAC8562_LDAC_PIN        GPIO_PIN_1

#define DAC8562_CLR_PORT        pGPIO1
#define DAC8562_CLR_PIN         GPIO_PIN_4

/* 命令位 (DB21-DB19) ------------------------------------------------------*/
#define DAC8562_CMD_WRITE_INPUT     0x00u   /* 写输入寄存器 n                        */
#define DAC8562_CMD_SW_LDAC         0x01u   /* 软件 LDAC, 更新 DAC 寄存器 n          */
#define DAC8562_CMD_WRITE_UPD_ALL   0x02u   /* 写输入寄存器 n 并更新全部 DAC 寄存器  */
#define DAC8562_CMD_WRITE_UPD_N     0x03u   /* 写输入寄存器 n 并更新 DAC 寄存器 n    */
#define DAC8562_CMD_POWER           0x04u   /* 上电/掉电模式                         */
#define DAC8562_CMD_RESET           0x05u   /* 软件复位                              */
#define DAC8562_CMD_LDAC_REG        0x06u   /* 配置 LDAC 寄存器                      */
#define DAC8562_CMD_INTERNAL_REF    0x07u   /* 使能/禁止内部基准                     */

#define DAC8562_FULL_SCALE          65535.0f
#define DAC8562_SPI_TIMEOUT         0x00FFFFFFu

/* Private variable --------------------------------------------------------*/
static uint8_t dac_tx[3];
static uint8_t dac_rx[3];

/* 最近一次 SPI 帧的返回状态 (供 Debug 的 watch 窗口观察):
 *   0 (LHL_OK)      = 收发正常, 24 个时钟全部发完
 *   3 (LHL_TIMEOUT) = 超时, 说明 SPI 没有真正产生时钟(典型原因: SPI 外设实例
 *                     与引脚 AF 不匹配 / 引脚未复用)。 */
volatile uint32_t g_dac_spi_status = 0xFFFFFFFFu;

/* Private function --------------------------------------------------------*/

/**
  * @brief  发送一帧 24 位数据 (SYNC 低 -> 24 个时钟 -> SYNC 高)
  * @param  cmd : 命令位 C2 C1 C0
  * @param  addr: 地址位 A2 A1 A0
  * @param  data: 16 位数据
  */
static void dac8562_write_frame(uint8_t cmd, uint8_t addr, uint16_t data)
{
    dac_tx[0] = (uint8_t)(((cmd & 0x07u) << 3) | (addr & 0x07u));
    dac_tx[1] = (uint8_t)(data >> 8);
    dac_tx[2] = (uint8_t)(data & 0xFFu);

    LHL_GPIO_ResetPins(DAC8562_SYNC_PORT, DAC8562_SYNC_PIN);    /* SYNC 拉低, 使能输入移位寄存器 */

    /* 阻塞式发送 3 个字节, 共 24 个 SCLK 下降沿。
     * 必须用 pSPI1: DAC8562 接在 P0.1/P0.2 上, 而 P0.x 的复用功能是 SPI1。 */
    g_dac_spi_status = (uint32_t)LHL_SPI_TransmitReceive(pSPI1, dac_tx, dac_rx, 3, DAC8562_SPI_TIMEOUT);

    LHL_GPIO_SetPins(DAC8562_SYNC_PORT, DAC8562_SYNC_PIN);      /* 24 个时钟后拉高 SYNC, 结束一帧 */

    LHL_Delay_uS(1);                                            /* 帧间最小间隔 */
}

/* Public function ---------------------------------------------------------*/

void dac8562_init(void)
{
    /* 1. 引脚默认电平: SYNC 高(空闲), CLR 高(不复位), LDAC 低(同步模式, 写入即更新) */
    LHL_GPIO_SetPins(DAC8562_SYNC_PORT, DAC8562_SYNC_PIN);
    LHL_GPIO_SetPins(DAC8562_CLR_PORT, DAC8562_CLR_PIN);
    LHL_GPIO_ResetPins(DAC8562_LDAC_PORT, DAC8562_LDAC_PIN);

    /* 2. 软件复位(DB0=1: 复位全部寄存器, 含 LDAC/上电/基准/增益寄存器) */
    dac8562_write_frame(DAC8562_CMD_RESET, 0x00u, 0x0001u);

    /* 3. 先把两个通道上电到"正常模式"(PD1/PD0 = 00, DB1=DB0=1 选中双通道)。
     *    手册明确要求: 内部基准只有在"DAC 通道处于正常模式"时才可能被使能,
     *    所以这一步必须排在使能基准之前。 */
    dac8562_write_frame(DAC8562_CMD_POWER, 0x00u, 0x0003u);

    /* 4. 使能内部 2.5V 基准 (DB0=1)。
     *    ⚠️ 该命令会把两个通道的增益复位成 2, 因此"设置增益"必须放在它后面。 */
    dac8562_write_frame(DAC8562_CMD_INTERNAL_REF, 0x00u, 0x0001u);

    /* 5. 设置双通道输出增益 (命令 000 + 地址 010, DB1=DAC-B, DB0=DAC-A; 0=增益2, 1=增益1)。
     *    必须放在"使能基准"之后, 否则会被上一步复位掉。 */
#if (DAC8562_GAIN == 1u)
    dac8562_write_frame(DAC8562_CMD_WRITE_INPUT, DAC8562_ADDR_GAIN, 0x0003u);  /* 双通道增益 = 1 */
#else
    dac8562_write_frame(DAC8562_CMD_WRITE_INPUT, DAC8562_ADDR_GAIN, 0x0000u);  /* 双通道增益 = 2 */
#endif

    /* 6. LDAC 寄存器清零(DB1=DAC-B, DB0=DAC-A; 0 = 由 LDAC 引脚控制更新)。
     *    复位后的默认值本就是 0, 这里显式写一次, 保证 dac8562_write_both()
     *    依赖的"LDAC 下降沿同步更新"一定有效。 */
    dac8562_write_frame(DAC8562_CMD_LDAC_REG, 0x00u, 0x0000u);

    /* 7. 双通道输出零刻度 */
    dac8562_write_frame(DAC8562_CMD_WRITE_UPD_N, DAC8562_CH_A, 0x0000u);
    dac8562_write_frame(DAC8562_CMD_WRITE_UPD_N, DAC8562_CH_B, 0x0000u);
}

void dac8562_write(uint8_t channel, uint16_t code)
{
    /* 写输入寄存器 n 并更新 DAC 寄存器 n: LDAC 保持低(同步模式)时, 第 24 个
       下降沿即完成寄存器更新与输出刷新 */
    dac8562_write_frame(DAC8562_CMD_WRITE_UPD_N, channel, code);
}

uint16_t dac8562_voltage_to_code(float voltage)
{
    const float v_max = DAC8562_INTERNAL_REF_V * (float)DAC8562_GAIN;

    if (voltage < 0.0f)        voltage = 0.0f;
    if (voltage > v_max)       voltage = v_max;

    return (uint16_t)((voltage / v_max) * DAC8562_FULL_SCALE + 0.5f);
}

void dac8562_write_voltage(uint8_t channel, float voltage)
{
    dac8562_write(channel, dac8562_voltage_to_code(voltage));
}

void dac8562_write_both(uint16_t code_a, uint16_t code_b)
{
    /* 异步方式: 先把两个通道写入输入寄存器(不更新输出), 再用 LDAC 下降沿同步更新 */
    LHL_GPIO_SetPins(DAC8562_LDAC_PORT, DAC8562_LDAC_PIN);      /* LDAC 拉高 */

    dac8562_write_frame(DAC8562_CMD_WRITE_INPUT, DAC8562_CH_A, code_a);
    dac8562_write_frame(DAC8562_CMD_WRITE_INPUT, DAC8562_CH_B, code_b);

    LHL_GPIO_ResetPins(DAC8562_LDAC_PORT, DAC8562_LDAC_PIN);    /* LDAC 下降沿, 双通道同时更新 */
    LHL_Delay_uS(1);
}

void dac8562_set_ldac(uint8_t level)
{
    if (level)
    {
        LHL_GPIO_SetPins(DAC8562_LDAC_PORT, DAC8562_LDAC_PIN);
    }
    else
    {
        LHL_GPIO_ResetPins(DAC8562_LDAC_PORT, DAC8562_LDAC_PIN);
    }
}

void dac8562_clear(void)
{
    /* CLR 下降沿: 输入寄存器与 DAC 寄存器全部清零, 输出回到零刻度 */
    LHL_GPIO_ResetPins(DAC8562_CLR_PORT, DAC8562_CLR_PIN);
    LHL_Delay_uS(1);
    LHL_GPIO_SetPins(DAC8562_CLR_PORT, DAC8562_CLR_PIN);
}

/*********************************End of File**********************************/
