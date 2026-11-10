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

/* ---------- 串口调试打印开关 ----------
 * 注意: printf 和协议帧共用同一条 RS-485 总线, 打开后会往线上插入
 * "FZ =..." 这样的非协议字节。调试时用, 正式通讯请保持 0。 */
#define UART_DEBUG          0

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

    rs485_init();                       /* 从 AT24C04 读回 a/b/c 标定系数 */

    zero_init();

#if (UART_DEBUG)
    /* 调试问候语: 打开后会在上电时占用总线约 1ms, 和主机的第一条指令撞车,
     * 所以只在调试时编译。 */
    printf("hello world111\r\n");
#endif

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

        /* ---- 4) 协议上报: 每来一个新采样(50Hz)处理一次 ----
         * 连续发送/单次采集的应答都在这里按当前格式(HEX/ASCII)发出。
         * 放在 uart_process 之前, 让刚收到的指令在下一拍就生效。 */
        if (g_adc_seq != last_seq) {
            last_seq = g_adc_seq;

            rs485_report(g_fz_mv);

#if (UART_DEBUG)
            /* 调试打印用整数, 避免 MicroLIB 浮点格式化的开销 */
            printf("FZ =%dmV\r\n", (int)g_fz_mv);
#endif
        }

        uart_process();
    }
}
/*********************************End of File**********************************/
