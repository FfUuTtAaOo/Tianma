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
#include "rs485_cmd.h"

/* Private define ------------------------------------------------------------*/ 
uint8_t I2C_RX_Data[10], I2C_TX_Data[10];

#define ADC_PGA_GAIN        1.0f
#define ADC_FULLSCALE_MV    (ADC_VREF_MV / ADC_PGA_GAIN)

volatile ZERO_Params_t g_zero = {
    0.0f,
    0,
    0.0f,
    0
};

/* ---------- 串口调试打印开关 ---------- */
#define UART_DEBUG          1

/* 供 Debug 的 watch 窗口直接观察。volatile 防止被优化掉。 */
volatile float g_fz_mv;                         /* 传感器输入电压(FZ) */
int32_t  fz_raw;

uint32_t last_seq = 0;

/* Global variable -----------------------------------------------------------*/

static void zero_init(void)
{
    g_zero.fz_sum = 0;
    g_zero.fz_zero_v = 0;
    g_zero.zero_count = 0;
    g_zero.zero_flag = 0;
}

static void calib_zero_cale(float fz)
{
    g_zero.fz_sum += fz;

    g_zero.zero_count++;
    if (g_zero.zero_count >= 20) {
        g_zero.fz_zero_v = g_zero.fz_sum / 20.0f;

        g_zero.zero_flag = 0;
        g_zero.zero_count = 0;
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

    zero_init();

    uart_rx_count = 0;
    uart_tx_count = 0;

    printf("hello world\r\n");

    while(1) {
        /* ---- 1) 24位补码 -> 有符号, 换算成传感器输入电压(mV) ---- */
        fz_raw = ((int32_t)dADCBuffer.ADC_Data << 8) >> 8;   /* AIN0 - AIN1 = FZ */

        /* 差分测量: Vin(mV) = 码/2^23 × Vref */
        g_fz_mv = (float)fz_raw / 8388608.0f * ADC_FULLSCALE_MV;

        if (g_zero.zero_flag == 1) {
            calib_zero_cale(g_fz_mv);
        } else {
            g_fz_mv -= g_zero.fz_zero_v;
        }

#if (UART_DEBUG)
        /* ---- 4) 串口打印: 仅在新样本到达时打印, 不重复刷同一组 ----
         * 全部用整数打印(%d), 不用 %f: MicroLIB 的 printf 浮点支持要额外配置,
         * 而这里 mV 精度到 1mV 已经足够观察。 */
        if (g_adc_seq != last_seq) {
            last_seq = g_adc_seq;
            printf("FZ =%fmV\r\n", g_fz_mv);
        }
#endif

        uart_process();
    }
}
/*********************************End of File**********************************/
