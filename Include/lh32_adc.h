#ifndef _LH32_ADC_H
#define _LH32_ADC_H

#include "lh32m0xx_lhl.h"

/* 双ADC同步采样结果, 由 DMA 通道0 以分散聚合模式搬运至此 */
typedef struct {
    uint32_t    ADC0_Data;
    uint32_t    ADC1_Data;
} ADC_DoubleData_t;

/* DMA 搬运目标缓冲区
 * 必须定义为全局(或 static 全局), 不能放在 adc_init() 的栈上:
 * adc_init() 返回后栈空间会被其他函数复用, DMA 持续写入会破坏调用栈。 */
extern ADC_DoubleData_t dADCBuffer;

/* 采样序号: DMA 通道0 中断里每完成一组(ADC0+ADC1)采样 +1。
 * 主循环据此判断"有新样本", 也用于串口按采样率(50Hz)打印, 不重复打印同一组。
 * ⚠️ 只能读, 不要在主循环里自增。 */
extern volatile uint32_t g_adc_seq;

/* adc_init() 里 LHL_DMA_Init(&hDMA0) 的返回值: 0=LHL_OK, 2=LHL_BUSY(控制器已 ACTIVE,
 * ch0 没配上也未启动采样)。出现 2 说明有人在 adc_init() 之前先 LHL_DMA_Start 了。 */
extern volatile uint32_t g_dma0_init_ret;

/* ======================= AIN 基准 / 负端接法 (全工程唯一定义处) =======================
 *
 * 【基准电压】硬件基准由 AFE->REF_CTRL 的 REF0_MODE 决定, 只有 4.096/2.5/2.048/1.25V
 *   四档。⚠️ 代码里写 REF_INTERNAL_4P096V ≠ 引脚上真的有 4.096V: 内部基准缓冲的输出
 *   不可能高于 AVDD, 3.3V 供电时 4.096V 档给不出来, 有效值会低于配置值。
 *   → 这个宏必须填"AIN 上实际生效的基准", 不能照抄 REF_CTRL 的档位名。
 *   校准(10 秒): 万用表量芯片 REFP 引脚对 AGND 的电压, 读数就是真值, 填到这里即可。
 *   (另: 软件里的 ADC_InitTypeDef.Reference 是死字段, 改它不影响硬件, 见 lh32_adc.c)
 */
#define ADC_VREF_MV         2500.0f

/* PGA 增益: 外部已做信号调理, 送到引脚的是"伏级"电压 -> 用 ×1 */
#define SENSOR_PGA          ADC_PGA_GAIN_1

void adc_init(void);        /* 配置 ADC0/ADC1 + DMAMUX + DMA TCD, 并使能并启动采样 */
void adc_start(void);       /* 启动 ADC0/ADC1 转换(软件触发, 连续转换模式) */

#endif
