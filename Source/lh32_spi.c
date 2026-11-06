#include "lh32_spi.h"

/* ============================================================================
 * 本工程使用 **SPI1 外设(pSPI1)** 驱动 DAC8562。
 *
 * ⚠️ 关键: SPI 外设实例必须与引脚复用(AF)匹配, 否则 SPI 的 SCLK/MOSI 信号
 *    根本不会出现在引脚上(外设时钟在跑, 但信号没有引出), 现象就是
 *    "代码看着没错, 但示波器/万用表量不到任何波形, DAC 输出恒 0V"。
 *
 *    依据 lh32m0g3x_gpio.h 的 AF 定义:
 *      SPI1 (pSPI1): P0.0=MISO1(AF1)  P0.1=SCLK1(AF1)  P0.2=MOSI1(AF1)  P0.3=CSN1(AF1)
 *      SPI0 (pSPI0): P1.4=MISO0(AF2)  P1.5=SCLK0(AF2)  P1.6=MOSI0(AF2)  P1.7=CSN0(AF2)
 *
 *    本工程 DAC8562 的 SCLK/DIN/SYNC 接在 P0.1/P0.2/P0.3 上(即 SPI1 的引脚),
 *    因此必须初始化 pSPI1。之前的代码初始化的是 pSPI0, 却把 P0.x 复用成 SPI1
 *    的功能 —— 属于"外设与引脚错配": SPI0 的时钟/数据没有引到任何引脚,
 *    P0.1/P0.2 上没有任何波形, DAC8562 收不到帧 -> OUTA/OUTB 恒为 0V。
 *    现已改为 pSPI1。
 *
 *    另: P1.5/P1.6 恰好是 SPI0 的 SCLK0/MOSI0 引脚位置, 但本工程把它们当普通
 *    GPIO 用来驱动 DAC 的 LDAC/CLR; 因为不使用 SPI0, 所以不存在冲突。
 * ==========================================================================*/

/* DAC8562 为只写器件(无 MISO), SPI 采用阻塞式发送, 不使用接收中断。
   以下缓冲区/变量供 lh32m0xx_it.c 中的 SPI0_IRQHandler 使用, 当前 DAC 场景下该中断未使能。 */
uint8_t SPI_TX_Buffer[MAX_SIZE] = {0xAA,0x55,0x08,0x00,0x00,0x00,0x00,0x00};
uint8_t SPI_RX_Buffer[MAX_SIZE];
__RW uint8_t counter, flag, index;

void spi_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    /* 1. SPI 引脚初始化 (SPI1, P0.0~P0.3) */
    GPIO_InitStructure.Pin = GPIO_PIN_0;                                        // P0.0 = SPI1(Master) MISO(闲置, DAC8562 无数据输出)
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Current = GPIO_CURRENT_4mA;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.SchmittTrigger = ENABLE;
    GPIO_InitStructure.Alternate = GPIO0_0_AF_MISO1;
    LHL_GPIO_Init(pGPIO0, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_1;                                        // P0.1 = SPI1(Master) SCLK  -> DAC8562 SCLK
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Current = GPIO_CURRENT_4mA;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.SchmittTrigger = DISABLE;
    GPIO_InitStructure.Alternate = GPIO0_1_AF_SCLK1;                            // AF1 = SCLK1(属于 SPI1)
    LHL_GPIO_Init(pGPIO0, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_2;                                        // P0.2 = SPI1(Master) MOSI  -> DAC8562 DIN
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Current = GPIO_CURRENT_4mA;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.SchmittTrigger = DISABLE;
    GPIO_InitStructure.Alternate = GPIO0_2_AF_MOSI1;                            // AF1 = MOSI1(属于 SPI1)
    LHL_GPIO_Init(pGPIO0, &GPIO_InitStructure);

    /* P0.3 = SPI1 的 CSN1 引脚位置, 但这里不交给硬件 NSS(已配 SPI_NSS_SOFT),
       而是当普通 GPIO 用软件手动控制帧同步 -> DAC8562 的 SYNC */
    GPIO_InitStructure.Pin = GPIO_PIN_3;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Current = GPIO_CURRENT_8mA;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.SchmittTrigger = DISABLE;
    GPIO_InitStructure.Alternate = GPIOx_AF_GPIO;
    LHL_GPIO_Init(pGPIO0, &GPIO_InitStructure);
    LHL_GPIO_SetPins(pGPIO0, GPIO_PIN_3);                                       // SYNC 空闲为高

    /* 2. SPI 外设配置 (pSPI1, 挂在 APB1) */
    SPI_InitStructure.Mode = SPI_MODE_MASTER;                                   // 主机
    SPI_InitStructure.Direction = SPI_DIR_2LINES_FULLDUPLEX;                    // 双线全双工
    SPI_InitStructure.DataSize = SPI_DATASIZE_8BIT;                             // 8 位帧(一帧 24bit = 连续 3 字节)
    SPI_InitStructure.CPOL = SPI_CPOL_LOW;                                      // DAC8562: SCLK 空闲低
    SPI_InitStructure.CPHA = SPI_CPHA_2EDGE;                                    // DAC8562: 下降沿采样 => SPI Mode 1
    /* SCLK = PCLK1/32 = 16MHz/32 = 500kHz(一帧 24bit ≈ 48us)。
     * DAC8562 手册上限 50MHz, 这里故意降速: 排线较长时高频容易振铃/错位,
     * 而 500kHz 对 DAC 刷新(约 10kHz)已绰绰有余。若用短排线可改回 PSC_4。 */
    SPI_InitStructure.BaudRatePrescaler = SPI_BAUDRATE_PSC_32;
    SPI_InitStructure.NSS = SPI_NSS_SOFT;                                       // NSS 软件控制(SSM=1, SSI=1)
    SPI_InitStructure.FirstBit = SPI_FIRSTBIT_MSB;                              // MSB First
    LHL_SPI_Init(pSPI1, &SPI_InitStructure);                                    // ★ 必须是 pSPI1(与 P0.x 的 AF 对应)
}
