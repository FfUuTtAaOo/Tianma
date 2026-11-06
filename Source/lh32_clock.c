/******************************************************************************
 * 系统时钟配置 (LH32M0G314)
 ******************************************************************************
 * 本芯片内部**没有 PLL**, SYSCLK 只能直接选取下面 5 个时钟源之一:
 *   HSI      = 32MHz          (内部 RC)
 *   HSI/2    = 16MHz          (内部 RC 二分频)   <-- 本文件使用
 *   HSE      = 外部 4~16MHz   (高速晶振)
 *   LSI      = 32kHz          (内部低速 RC)
 *   LSE      = 32.768kHz      (外部低速晶振)
 *
 * 本文件把 SYSCLK 配置为**内部 HSI 二分频 = 16MHz**。
 * 复位默认时 HPRE 不是 1 分频, 实际 HCLK 只有 1~2MHz; 本函数显式把
 * HPRE/PPRE1/PPRE2 都设为 1 分频, 使 SYSCLK = HCLK = PCLK1 = PCLK2 = 16MHz。
 ******************************************************************************/
#include "lh32_clock.h"

/**
  * @brief  把系统时钟配置为 HSI/2 = 16MHz
  * @note   配置完成后:
  *           SYSCLK = HCLK = PCLK1 = PCLK2 = 16MHz
  *         由此带来的连锁影响:
  *           - SPI0 SCLK = PCLK2/4 = 4MHz, 一帧 24bit 约 6us;
  *           - I2C 的 CCR = PCLK1/(2*100k) = 80, 标准模式可用;
  *           - LHL_Delay_uS 的 CoreClockShift 变为 0, 软件延时 1 次循环/uS;
  *           - ADC/DAC 的采样率由各自内部时钟决定, 不受 SYSCLK 影响。
  *
  * @note   直接使用库函数 LHL_RCC_ClockConfig, 它内部会依次完成:
  *           HSIDIV2(=1) -> SW(=HSI) 并等待 SWS 确认 -> HPRE/PPRE1/PPRE2 设置,
  *           最后调用 SystemCoreClockUpdate() 同步 CMSIS 变量与 CoreClockShift。
  *         安全说明: 该库函数只在 SYSCLKSource 的 bit0 置位时(HSE=0x1 / LSE=0x3)
  *           才会把 P1.0 配成 EXTCLKIN 复用; 这里传 RCC_SYSCLK_SRC_HSI_DIV2=0x4,
  *           bit0=0, 因此**不会**误配 P1.0。
  */
void clock_init(void)
{
    RCC_ClockInitTypeDef clk;

    clk.SYSCLKSource   = RCC_SYSCLK_SRC_HSI_DIV2;   /* 0x4: 置 HSIDIV2, SW 选 HSI -> SYSCLK=HSI/2=16MHz */
    clk.AHBCLKDivider  = RCC_SYSCLK_DIV2;           /* HCLK  = SYSCLK = 16MHz */
    clk.APB1CLKDivider = RCC_HCLK_DIV1;             /* PCLK1 = HCLK   = 16MHz */
    clk.APB2CLKDivider = RCC_HCLK_DIV1;             /* PCLK2 = HCLK   = 16MHz */

    (void)LHL_RCC_ClockConfig(&clk, LHL_NRM_TIMEOUT);
}
/*********************************End of File**********************************/
