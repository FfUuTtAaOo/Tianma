/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_lptim.h
 * @version 2025-09-08
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_LPTIM_H
#define __LH32M0G3x_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Defines -------------------------------------------------------------------*/

/** @defgroup LPTIM_Mode
  * @{
  */
typedef enum {
    LPTIM_MODE_TIMER_COUNTER    = 0u,
    LPTIM_MODE_PLUSE_COUNTER    = 1u,
} LPTIM_MODE_t;
/**
  * @}
  */

/** @defgroup LPTIM_Clock_Source
  * @{
  */
typedef enum {
    LPTIM_CLOCKSOURCE_PCLK1     = 0u,
    LPTIM_CLOCKSOURCE_HCLK      = 1u,
    LPTIM_CLOCKSOURCE_LSI       = 2u,
    LPTIM_CLOCKSOURCE_LSE       = 3u,
} LPTIM_CLOCKSOURCE_t;
/**
  * @}
  */

/** @defgroup LPTIM_Clock_Prescaler
  * @{
  */
typedef enum {
    LPTIM_PRESCALER_DIV1        = 0x10u,
    LPTIM_PRESCALER_DIV2        = 0x00u,
    LPTIM_PRESCALER_DIV4        = 0x01u,
    LPTIM_PRESCALER_DIV8        = 0x02u,
    LPTIM_PRESCALER_DIV16       = 0x03u,
    LPTIM_PRESCALER_DIV32       = 0x04u,
    LPTIM_PRESCALER_DIV64       = 0x05u,
    LPTIM_PRESCALER_DIV128      = 0x06u,
    LPTIM_PRESCALER_DIV256      = 0x07u,
    LPTIM_PRESCALER_DIV512      = 0x08u,
    LPTIM_PRESCALER_DIV1024     = 0x09u,
    LPTIM_PRESCALER_DIV2048     = 0x0Au,
    LPTIM_PRESCALER_DIV4096     = 0x0Bu,
    LPTIM_PRESCALER_DIV8192     = 0x0Cu,
    LPTIM_PRESCALER_DIV16384    = 0x0Du,
    LPTIM_PRESCALER_DIV32768    = 0x0Eu,
    LPTIM_PRESCALER_DIV65536    = 0x0Fu,
} LPTIM_PRESCALER_t;
/**
  * @}
  */

/** @defgroup LPTIM Structure definition
  * @{
  */
  
/**
  * @brief  LPTIM Initialization Structure definition
  */
typedef struct
{
    LPTIM_MODE_t        Mode;                   /*!< Specifies the LPTIM Mode: LPTIM_Mode*/

    LPTIM_CLOCKSOURCE_t Clock;                  /*!< Specifies the LPTIM clock source: LPTIM_Clock_Source */

    LPTIM_PRESCALER_t   Prescaler;              /*!< 在时间计数器模式下配置预分频器的大小或在脉冲计数器模式下配置毛刺滤波器的宽度 */
    
    FunctionalState     FreeRunning;            /*!< 定时器自由运行  */
    
} LPTIM_InitTypeDef;

/**
  * @brief  LPTIM Output Compare Configuration Structure definition
  */
typedef struct
{
  uint32_t Pulse;                 /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                       This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */
  uint32_t OCPolarity;            /*!< Specifies the output polarity.
                                       This parameter can be a value of @ref LPTIM_Output_Compare_Polarity */
} LPTIM_OC_ConfigTypeDef;
  
/**
  * @brief  LPTIM Input Capture Configuration Structure definition
  */
typedef struct
{
  uint32_t ICInputSource; /*!< Specifies source selected for IC channel.
                               This parameter can be a value of @ref LPTIM_Input_Capture_Source */

  uint32_t ICPrescaler;   /*!< Specifies the Input Capture Prescaler.
                               This parameter can be a value of @ref LPTIM_Input_Capture_Prescaler */

  uint32_t ICPolarity;    /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref LPTIM_Input_Capture_Polarity */

  uint32_t ICFilter;      /*!< Specifies the input capture filter.
                               This parameter can be a value of @ref LPTIM_Input_Capture_Filter */
} LPTIM_IC_ConfigTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Constants LPTIM Exported Constants
  * @{
  */


/** @defgroup LPTIM_Clock_Sample_Time LPTIM Clock Sample Time
  * @{
  */
#define LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION  0x00000000U
#define LPTIM_CLOCKSAMPLETIME_2TRANSITIONS      LPTIM_CFGR_CKFLT_0
#define LPTIM_CLOCKSAMPLETIME_4TRANSITIONS      LPTIM_CFGR_CKFLT_1
#define LPTIM_CLOCKSAMPLETIME_8TRANSITIONS      LPTIM_CFGR_CKFLT
/**
  * @}
  */

/** @defgroup LPTIM_Clock_Polarity LPTIM Clock Polarity
  * @{
  */
#define LPTIM_CLOCKPOLARITY_RISING              0x00000000U
#define LPTIM_CLOCKPOLARITY_FALLING             LPTIM_CFGR_CKPOL_0
#define LPTIM_CLOCKPOLARITY_RISING_FALLING      LPTIM_CFGR_CKPOL_1
/**
  * @}
  */

/** @defgroup LPTIM_Trigger_Source LPTIM Trigger Source
  * @{
  */
#define LPTIM_TRIGSOURCE_SOFTWARE               0x0000FFFFU
#define LPTIM_TRIGSOURCE_0                      0x00000000U
#define LPTIM_TRIGSOURCE_1                      LPTIM_CFGR_TRIGSEL_0
#define LPTIM_TRIGSOURCE_2                      LPTIM_CFGR_TRIGSEL_1
#define LPTIM_TRIGSOURCE_3                      (LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_1)
#define LPTIM_TRIGSOURCE_4                      LPTIM_CFGR_TRIGSEL_2
#define LPTIM_TRIGSOURCE_5                      (LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_2)
#define LPTIM_TRIGSOURCE_6                      (LPTIM_CFGR_TRIGSEL_1 | LPTIM_CFGR_TRIGSEL_2)
#define LPTIM_TRIGSOURCE_7                      LPTIM_CFGR_TRIGSEL
/**
  * @}
  */

/** @defgroup LPTIM_External_Trigger_Polarity LPTIM External Trigger Polarity
  * @{
  */
#define LPTIM_ACTIVEEDGE_RISING                LPTIM_CFGR_TRIGEN_0
#define LPTIM_ACTIVEEDGE_FALLING               LPTIM_CFGR_TRIGEN_1
#define LPTIM_ACTIVEEDGE_RISING_FALLING        LPTIM_CFGR_TRIGEN
/**
  * @}
  */

/** @defgroup LPTIM_Trigger_Sample_Time LPTIM Trigger Sample Time
  * @{
  */
#define LPTIM_TRIGSAMPLETIME_DIRECTTRANSITION  0x00000000U
#define LPTIM_TRIGSAMPLETIME_2TRANSITIONS      LPTIM_CFGR_TRGFLT_0
#define LPTIM_TRIGSAMPLETIME_4TRANSITIONS      LPTIM_CFGR_TRGFLT_1
#define LPTIM_TRIGSAMPLETIME_8TRANSITIONS      LPTIM_CFGR_TRGFLT
/**
  * @}
  */

/** @defgroup LPTIM_Updating_Mode LPTIM Updating Mode
  * @{
  */

#define LPTIM_UPDATE_IMMEDIATE                  0x00000000U
#define LPTIM_UPDATE_ENDOFPERIOD                LPTIM_CFGR_PRELOAD
/**
  * @}
  */

/** @defgroup LPTIM_Counter_Source LPTIM Counter Source
  * @{
  */

#define LPTIM_COUNTERSOURCE_INTERNAL            0x00000000U
#define LPTIM_COUNTERSOURCE_EXTERNAL            LPTIM_CFGR_COUNTMODE
/**
  * @}
  */

/** @defgroup LPTIM_Input1_Source LPTIM Input1 Source
  * @{
  */

#define LPTIM_INPUT1SOURCE_GPIO          0x00000000U             /*!< For LPTIM1, LPTIM2, LPTIM3 and LPTIM4 */
#define LPTIM_INPUT1SOURCE_COMP1         LPTIM_CFGR2_IN1SEL_0    /*!< For LPTIM1, LPTIM2, LPTIM3 and LPTIM4 */
/**
  * @}
  */

/** @defgroup LPTIM_Input2_Source LPTIM Input2 Source
  * @{
  */

#define LPTIM_INPUT2SOURCE_GPIO         0x00000000U                    /*!< For LPTIM1 and LPTIM2 */
#define LPTIM_INPUT2SOURCE_COMP2        LPTIM_CFGR2_IN2SEL_0           /*!< For LPTIM1 and LPTIM2 */
/**
  * @}
  */

/** @defgroup LPTIM_Flag_Definition LPTIM Flags Definition
  * @{
  */

#define LPTIM_FLAG_CC1O                          LPTIM_ISR_CC1OF
#define LPTIM_FLAG_CC2O                          LPTIM_ISR_CC2OF
#define LPTIM_FLAG_CC1                           LPTIM_ISR_CC1IF
#define LPTIM_FLAG_CC2                           LPTIM_ISR_CC2IF
#define LPTIM_FLAG_CMP1OK                        LPTIM_ISR_CMP1OK
#define LPTIM_FLAG_CMP2OK                        LPTIM_ISR_CMP2OK
#define LPTIM_FLAG_DIEROK                        LPTIM_ISR_DIEROK
#define LPTIM_FLAG_REPOK                         LPTIM_ISR_REPOK
#define LPTIM_FLAG_UPDATE                        LPTIM_ISR_UE
#define LPTIM_FLAG_DOWN                          LPTIM_ISR_DOWN
#define LPTIM_FLAG_UP                            LPTIM_ISR_UP
#define LPTIM_FLAG_ARROK                         LPTIM_ISR_ARROK
#define LPTIM_FLAG_EXTTRIG                       LPTIM_ISR_EXTTRIG
#define LPTIM_FLAG_ARRM                          LPTIM_ISR_ARRM
/**
  * @}
  */

/** @defgroup LPTIM_DMA_sources LPTIM DMA Sources
  * @{
  */
#define LPTIM_DMA_UPDATE                     LPTIM_DIER_UEDE         /*!< DMA request is triggered by the update event */
#define LPTIM_DMA_CC1                        LPTIM_DIER_CC1DE        /*!< DMA request is triggered by the capture 1 event */
#define LPTIM_DMA_CC2                        LPTIM_DIER_CC2DE        /*!< DMA request is triggered by the capture 2 event */

/**
  * @}
  */

/** @defgroup LPTIM_DMA_Handle_index LPTIM DMA Handle Index
  * @{
  */
#define LPTIM_DMA_ID_UPDATE                ((uint16_t) 0x0000)       /*!< Index of the DMA handle used for Update DMA requests */
#define LPTIM_DMA_ID_CC1                   ((uint16_t) 0x0001)       /*!< Index of the DMA handle used for Capture/Update event 1 DMA request */
#define LPTIM_DMA_ID_CC2                   ((uint16_t) 0x0002)       /*!< Index of the DMA handle used for Capture/Update event 2 DMA request */
/**
  * @}
  */

/** @defgroup LPTIM_Interrupts_Definition LPTIM Interrupts Definition
  * @{
  */
#define LPTIM_IT_CC1O                            LPTIM_DIER_CC1OIE
#define LPTIM_IT_CC2O                            LPTIM_DIER_CC2OIE
#define LPTIM_IT_CC1                             LPTIM_DIER_CC1IE
#define LPTIM_IT_CC2                             LPTIM_DIER_CC2IE
#define LPTIM_IT_CMP1OK                          LPTIM_DIER_CMP1OKIE
#define LPTIM_IT_CMP2OK                          LPTIM_DIER_CMP2OKIE
#define LPTIM_IT_REPOK                           LPTIM_DIER_REPOKIE
#define LPTIM_IT_UPDATE                          LPTIM_DIER_UEIE
#define LPTIM_IT_DOWN                            LPTIM_DIER_DOWNIE
#define LPTIM_IT_UP                              LPTIM_DIER_UPIE
#define LPTIM_IT_ARROK                           LPTIM_DIER_ARROKIE
#define LPTIM_IT_EXTTRIG                         LPTIM_DIER_EXTTRIGIE
#define LPTIM_IT_ARRM                            LPTIM_DIER_ARRMIE
/**
  * @}
  */

/** @defgroup LPTIM_Channel LPTIM Channel
  * @{
  */
#define LPTIM_CHANNEL_1                      0x00000000U                          /*!< Capture/compare channel 1 identifier      */
#define LPTIM_CHANNEL_2                      0x00000004U                          /*!< Capture/compare channel 2 identifier      */
#define LPTIM_CHANNEL_ALL                    0x00000013U                          /*!< Global Capture/compare channel identifier  */
/**
  * @}
  */

/** @defgroup LPTIM_Output_Compare_Polarity LPTIM Output Compare Polarity
  * @{
  */
#define LPTIM_OCPOLARITY_HIGH                    0x00000000U                    /*!< Capture/Compare output polarity */
#define LPTIM_OCPOLARITY_LOW                     0x00000001U                    /*!< Capture/Compare output polarity */
/**
  * @}
  */

/** @defgroup LPTIM_Input_Capture_Prescaler LPTIM Input Capture Prescaler
  * @{
  */
#define LPTIM_ICPSC_DIV1                          0x00000000UL                                  /*!< Capture performed each time an edge is detected on the capture input */
#define LPTIM_ICPSC_DIV2                          LPTIM_CCMR1_IC1PSC_0                          /*!< Capture performed once every 2 events                                */
#define LPTIM_ICPSC_DIV4                          LPTIM_CCMR1_IC1PSC_1                          /*!< Capture performed once every 4 events                                */
#define LPTIM_ICPSC_DIV8                         (LPTIM_CCMR1_IC1PSC_0|LPTIM_CCMR1_IC1PSC_1)    /*!< Capture performed once every 8 events                                */
/**
  * @}
  */

/** @defgroup LPTIM_Input_Capture_Polarity LPTIM Input Capture Polarity
  * @{
  */
#define LPTIM_ICPOLARITY_RISING                    0x00000000UL                              /*!< Capture/Compare input rising polarity */
#define LPTIM_ICPOLARITY_FALLING                   LPTIM_CCMR1_CC1P_0                        /*!< Capture/Compare input falling polarity */
#define LPTIM_ICPOLARITY_RISING_FALLING           (LPTIM_CCMR1_CC1P_0|LPTIM_CCMR1_CC1P_1)    /*!< Capture/Compare input rising and falling polarities */
/**
  * @}
  */

/** @defgroup LPTIM_Input_Capture_Filter LPTIM Input Capture Filter
  * @{
  */
#define LPTIM_ICFLT_CLOCK_DIV1                     0x00000000UL                            /*!< any external input capture signal level change is considered as a valid transition */
#define LPTIM_ICFLT_CLOCK_DIV2                     LPTIM_CCMR1_IC1F_0                      /*!< external input capture signal level change must be stable for at least 2 clock periods before it is considered as valid transition */
#define LPTIM_ICFLT_CLOCK_DIV4                     LPTIM_CCMR1_IC1F_1                      /*!< external input capture signal level change must be stable for at least 4 clock periods before it is considered as valid transition */
#define LPTIM_ICFLT_CLOCK_DIV8                    (LPTIM_CCMR1_IC1F_0|LPTIM_CCMR1_IC1F_1)  /*!< external input capture signal level change must be stable for at least 8 clock periods before it is considered as valid transition */
/**
  * @}
  */

/** @defgroup LPTIM_Input_Capture_Source LPTIM Input Capture Source
  * @{
  */
#define LPTIM_IC1SOURCE_GPIO                       0x00000000UL                               /*!< For LPTIM1, LPTIM2 and LPTIM3 */
#define LPTIM_IC1SOURCE_COMP1                      LPTIM_CFGR2_IC1SEL_0                       /*!< For LPTIM1, LPTIM2 and LPTIM3 */
#define LPTIM_IC1SOURCE_COMP2                      LPTIM_CFGR2_IC1SEL_1                       /*!< For LPTIM1, LPTIM2 and LPTIM3 */
#define LPTIM_IC2SOURCE_GPIO                       0x00000000UL                               /*!< For LPTIM1, LPTIM2 and LPTIM3 */
#define LPTIM_IC2SOURCE_LSI                        LPTIM_CFGR2_IC2SEL_0                       /*!< For LPTIM1 */
#define LPTIM_IC2SOURCE_LSE                        LPTIM_CFGR2_IC2SEL_1                       /*!< For LPTIM1 */
#define LPTIM_IC2SOURCE_HSI_256                    LPTIM_CFGR2_IC2SEL_0                       /*!< For LPTIM2 */
#define LPTIM_IC2SOURCE_MSIS_1024                  LPTIM_CFGR2_IC2SEL_1                       /*!< For LPTIM2 */
#define LPTIM_IC2SOURCE_MSIS_4                    (LPTIM_CFGR2_IC2SEL_0|LPTIM_CFGR2_IC2SEL_1) /*!< For LPTIM2 */
/**
  * @}
  */
/* Declaration ---------------------------------------------------------------*/
void        LHL_LPTIM_Init (LPTIM_TypeDef* pLPTIMx, LPTIM_InitTypeDef* LPTIM_Init);

void        LHL_LPTIM_Start(LPTIM_TypeDef* pLPTIMx, uint16_t Period);

void        LHL_LPTIM_Stop(LPTIM_TypeDef* pLPTIMx);

void        LHL_LPTIM_Reset(LPTIM_TypeDef* pLPTIMx);

void        LHL_LPTIM_PWM_Start(LPTIM_TypeDef* pLPTIMx, uint16_t Period, uint16_t Duty);

void        LHL_LPTIM_ITConfig(LPTIM_TypeDef* pLPTIMx, FunctionalState NewState);

void        LHL_LPTIM_ClearPending(LPTIM_TypeDef* pLPTIMx);

void        LHL_LPTIM_PWM_Init(LPTIM_TypeDef* pLPTIMx);

uint16_t    LHL_LPTIM_GetCounter(LPTIM_TypeDef* pLPTIMx);

void        LHL_LPTIM_DeInit(LPTIM_TypeDef* pLPTIMx);

#ifdef __cplusplus
}
#endif

#endif 

/*********************************End of File**********************************/
