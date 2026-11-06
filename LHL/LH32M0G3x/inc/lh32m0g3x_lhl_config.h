/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g3x_lhl_config.h
 * @version 2025-09-01
 ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_LHL_CONFIG_H
#define __LH32M0G3x_LHL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lh32m0xx_lhl.h"
#include "lh32m0g3x.h"

/* LHL Definition ------------------------------------------------------------*/
#ifndef HSI_VALUE
#define HSI_VALUE ((uint32_t)32000000)  /* HSI */
#endif
#ifndef LSI_VALUE
#define LSI_VALUE ((uint32_t)32000)     /* LSI */
#endif
#ifndef LSE_VALUE
#define LSE_VALUE ((uint32_t)32768)     /* LSE */
#endif
#ifndef HSE_VALUE
#define HSE_VALUE ((uint32_t)8000000)   /* !!! HSE !!!需据设计更改外部时钟频率Hz */
#endif
#ifndef SYS_VALUE
#define SYS_VALUE ((HSI_VALUE/2)/8)     /* 上电启动时默认的SYSCLK时钟频率Hz */
#endif

#define __NOTHING __ASM volatile("")

typedef enum {RESET = 0u, SET = 1u} FlagStatus, ITStatus;

typedef enum {DISABLE = 0u, ENABLE = 1u} FunctionalState;

typedef enum {ERROR = 0u, SUCCESS = 1u} ErrorStatus;

typedef enum 
{
    LHL_OK          = 0u,       /* 设置成功                                    */
    LHL_ERROR,                  /* 参数或者异常标志错误                          */
    LHL_BUSY,                   /* 发起操作前，总线、标志、状态位等忙碌位持续置位   */
    LHL_TIMEOUT,                /* 发起操作后，通信、操作或者总线等等待超时        */
} LHL_StatusTypeDef;

#define LHL_MAX_TIMEOUT         0xFFFFFFFFu
#define LHL_LNG_TIMEOUT         0xFFFFFFu
#define LHL_NRM_TIMEOUT         0xFFFFu
#define LHL_MIN_TIMEOUT         0xFFu
#define LHL_NOT_TIMEOUT         0x01u

#ifndef __UNUSED
#define __UNUSED(X) (void)X     /* To avoid gcc/g++ warnings */
#endif /* UNUSED */

/* Bitmap操作宏 */
#define BITMAP_SET(bits, pos)       ((bits)[(pos) / 32] |= (1U << ((pos) % 32)))
#define BITMAP_CLEAR(bits, pos)     ((bits)[(pos) / 32] &= ~(1U << ((pos) % 32)))
#define BITMAP_GET(bits, pos)       (((bits)[(pos) / 32] >> ((pos) % 32)) & 1U)


/* 环形缓冲区，支持最多256个数据 */
typedef struct {
    uint8_t         *data;          // 缓冲区指针
    uint8_t         size;           // 缓冲区大小 (0-255)
    __RW uint8_t    head;           // 写入位置 (0-255)
    __RW uint8_t    tail;           // 读取位置 (0-255)
    __RW uint8_t    count;          // 已保存的数据数量
} RingBufferTypeDef;

void LHL_RB_Init(RingBufferTypeDef *rb, uint8_t *buffer, uint8_t size);
bool LHL_RB_Put(RingBufferTypeDef *rb, uint8_t byte);
bool LHL_RB_Get(RingBufferTypeDef *rb, uint8_t *byte);
bool LHL_RB_IsEmpty(RingBufferTypeDef *rb);
bool LHL_RB_IsFull(RingBufferTypeDef *rb);
uint8_t LHL_RB_GetCount(RingBufferTypeDef *rb);

int32_t LHL_Divide_Round(int32_t dividend, int32_t divisor);

/******************************************************************************
  *
  * @brief 编译器检测和配置                                                     *
  *
  *****************************************************************************/
#if defined(__ARMCC_VERSION)
    // ARM Compiler
    #if (__ARMCC_VERSION >= 6200000)
        // ARM Compiler 6.x
        #pragma GCC diagnostic ignored "-Wunsafe-buffer-usage"
    #else
        // ARM Compiler 5.x
    #endif
    #if (__ARMCC_VERSION >= 6010050)
        #define __LHL_DSB __DSB()
        #define __LHL_ISB __ISB()
    #else
        // AC5 - 宏需要额外分号
        #define __LHL_DSB __DSB();
        #define __LHL_ISB __ISB();
    #endif
    #define __LHL_RAMFUNC __attribute__ ((section (".ramfunc")))
#elif defined(__GNUC__)
    // GNU Compiler
    #define __LHL_DSB __DSB();
    #define __LHL_ISB __ISB();
    #define __LHL_RAMFUNC __attribute__((section(".ramfunc")))
#elif defined(__ICCARM__)
    // IAR Compiler
    #define __LHL_DSB __DSB();
    #define __LHL_ISB __ISB();
    #define __LHL_RAMFUNC __ramfunc
#endif

/* 变量对齐宏（后缀式声明，如：type var[4] __ALIGN(128);）：
 *   - IAR 8.x（__ICCARM_V8）：支持 GNU 属性，可作声明后缀
 *   - GCC / ARM Compiler 6：使用 __attribute__((aligned(n)))
 *   - ARM Compiler 5：__align(n) 仅支持前置，请将其放置于类型前使用
 */
#if defined(__ICCARM__)
    #define __ALIGN(n) __attribute__((aligned(n)))
#elif defined(__GNUC__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
    #define __ALIGN(n) __attribute__((aligned(n)))
#elif defined(__ARMCC_VERSION)
    #define __ALIGN(n) __align(n)
#else
    #define __ALIGN(n)
#endif

/******************************************************************************
  *
  * @brief Configuration of the Cortex-M0+ Processor and Core Peripherals     *
  *
  *****************************************************************************/
#define __CM0PLUS_REV           0   /*!< Core Revision r0p0                             */
#define __MPU_PRESENT           0   /*!< NO MPU                                         */
#define __VTOR_PRESENT          1   /*!< Vector  Table  Register supported              */
#define __NVIC_PRIO_BITS        2   /*!< LH32M0xx uses 2 Bits for the Priority Levels   */
#define __Vendor_SysTickConfig  0   /*!< Set to 1 if different SysTick Config is used   */

#define LHL_MAX_DELAY           (0xFFFFFFFFu)

/**
  * @brief Configuration of the System Tick Frequency and Priority
  */
typedef enum
{
  LHL_TICK_FREQ_10HZ        = 100u,
  LHL_TICK_FREQ_100HZ       = 10u,
  LHL_TICK_FREQ_1KHZ        = 1u,
  LHL_TICK_FREQ_DEFAULT     = LHL_TICK_FREQ_1KHZ    /* 默认Systick时基1mS，可根据系统需要更改 */
} LHL_TickFreqTypeDef;

typedef enum
{
  LHL_TICK_PRIO_HIGHEST     = 3u,
  LHL_TICK_PRIO_HIGH        = 2u,
  LHL_TICK_PRIO_LOW         = 1u,
  LHL_TICK_PRIO_LOWEST      = 0u,                   /* Systick中断优先级设定 */
} LHL_TickPrioTypeDef;

extern __RW uint32_t        uTick;
extern LHL_TickPrioTypeDef  uTickPrio;
extern LHL_TickFreqTypeDef  uTickFreq;

void                        LHL_IncTick(void);
uint32_t                    LHL_GetTick(void);
uint32_t                    LHL_GetTickPrio(void);
LHL_StatusTypeDef           LHL_SetTickFreq(LHL_TickFreqTypeDef Freq);
LHL_TickFreqTypeDef         LHL_GetTickFreq(void);
void                        LHL_SuspendTick(void);
void                        LHL_ResumeTick(void);
LHL_StatusTypeDef           LHL_SysTick_Init(LHL_TickPrioTypeDef TickPriority);
void                        LHL_SetTickReload(uint32_t systemclock);

/**
  * @brief  Interrupt Number Definition for NVIC
  */
typedef enum IRQn
{
    /************ Cortex Core Processor Exceptions Number  ********************/
    NonMaskableInt_IRQn         = -14,      
    HardFault_IRQn              = -13,    
    SVCall_IRQn                 = -5,     
    PendSV_IRQn                 = -2,     
    SysTick_IRQn                = -1,     
    /******* Device specific Interrupt Numbers ********************************/
    PVD_IRQn                    = 1,
    ADC_ERR_IRQn                = 2,
    RTC_IRQn                    = 3,
    CROSSLINK_IRQn              = 4,
    RCC_IRQn                    = 5,
    EXTI0_1_IRQn                = 6,
    EXTI2_3_IRQn                = 7,
    EXTI4_7_IRQn                = 8,
    DMA1_CH0_IRQn               = 9,
    DMA1_CH1_IRQn               = 10,
    DMA1_CH2_CH3_IRQn           = 11,
    SPI0_IRQn                   = 12,
    UART0_IRQn                  = 13,
    RTCAlarm_IRQn               = 14,
    FLASH_IRQn                  = 15,
    MIO_IRQn                    = 16,
    SPI1_IRQn                   = 17,
    ADC0_IRQn                   = 18,
    ADC1_IRQn                   = 19,
    TIM5_IRQn                   = 20,
    UART1_IRQn                    = 21,
    TIM6_IRQn                   = 22,
    EXTI10_11_IRQn              = 24,
    EXTI12_13_IRQn                = 25,
    LPTIM2_IRQn                 = 26,
    TIM1_IRQn                   = 27,
    TIM2_IRQn                   = 28,
    LPTIM1_IRQn                 = 29,
    MACL_IRQn                   = 30,
    I2C1_EV_IRQn                = 31,
} IRQn_Type;

void NMI_Handler(void) __attribute__((noreturn));
void HardFault_Handler(void) __attribute__((noreturn));
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void PVD_IRQHandler(void);           
void ADC_ERR_IRQHandler(void);           
void RTC_IRQHandler(void);           
void CROSSLINK_IRQHandler(void);         
void RCC_IRQHandler(void);           
void EXTI0_1_IRQHandler(void);         
void EXTI2_3_IRQHandler(void);         
void EXTI4_7_IRQHandler(void);         
void DMA1_CH0_IRQHandler(void);         
void DMA1_CH1_IRQHandler(void);         
void DMA1_CH2_3_IRQHandler(void);           
void SPI0_IRQHandler(void);          
void UART0_IRQHandler(void);         
void RTCAlarm_IRQHandler(void);     
void QSPI_IRQHandlern(void);         
void MIO_IRQHandler(void);        
void SPI1_IRQHandler(void);           
void ADC0_IRQHandler(void);           
void ADC1_IRQHandler(void);          
void TIM5_IRQHandler(void); 
void UART1_IRQHandler(void);
void TIM6_IRQHandler(void);    
void EEPROM_IRQHandler(void);     
void EXTI10_11_IRQHandler(void);
void EXTI12_13_IRQHandler(void);     
void LPTIM2_IRQHandler(void); 
void TIM1_IRQHandler(void);
void TIM2_IRQHandler(void);        
void LPTIM1_IRQHandler(void);   
void MACL_IRQHandler(void);
void I2C1_EV_IRQHandler(void);

void LHL_Disable_All_IRQs(void);
void LHL_Clear_All_IRQs(void);

#include <core_cm0plus.h>       /* Cortex-M0+ processor and core peripherals  */

/**
  * @brief  System clock and timing and core contrl funcitons
  */
extern __RW uint32_t SystemCoreClock;   /*!< System Clock (MCU Core) Frequency*/
extern __RW uint8_t CoreClockShift;
extern __RW uint32_t HSITrimCode;

extern void     SystemInit(void);
extern void     SystemCoreClockUpdate(void);

void            LHL_Delay(uint32_t mS);
void            LHL_Delay_uS(uint32_t uS);

/* Exported variables --------------------------------------------------------*/

/* Exported functions in lhl.c -----------------------------------------------*/
uint8_t         LHL_Get_PinPosition(uint16_t GPIO_Pin);
uint8_t         LHL_Get_ClockShift(uint32_t default_clock, uint32_t core_clock);

int xprintf_out(int ch);
int xprintf_in(void);

/* Periphral includes --------------------------------------------------------*/
#ifdef USE_LHL_DRIVERS
    #include "sdk_mio_common.h"
    #include "lh32m0g3x_gpio.h"
    #include "lh32m0g3x_rcc.h"
    #include "lh32m0g3x_iwdg.h"
    #include "lh32m0g3x_uart.h"
    #include "lh32m0g3x_rtc.h"
    #include "lh32m0g3x_lptim.h"
    #include "lh32m0g3x_spi.h"
    #include "lh32m0g3x_mcal.h"
    #include "lh32m0g3x_exti.h"
    #include "lh32m0g3x_power.h"
    #include "lh32m0g3x_timer.h"
    #include "lh32m0g3x_i2c.h"
    #include "lh32m0g3x_dma.h"
    #include "lh32m0g3x_dmamux.h"
    #include "lh32m0g3x_dac.h"
    #include "lh32m0g3x_adc.h"
    #include "lh32m0g3x_flash.h"
    #include "lh32m0g3x_btim.h"
    #include "lh32m0g3x_eeprom.h"
    #include "lh32m0g3x_xlink.h"
    #include "lh32m0g3x_crc.h"
    #include "lh32m0g3x_mio.h"
#endif

#ifdef USE_LHL_OWI
    #include "lh32m0g3x_owi.h"
#endif

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
