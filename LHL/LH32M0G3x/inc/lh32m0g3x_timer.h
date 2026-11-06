/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_timer.h
 * @version 2025-09-25
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_TIM_H
#define __LH32M0G3x_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Definition ----------------------------------------------------------------*/
/**   
  * @brief  TIM_Counter_Mode
  */
typedef enum {
    TIM_COUNTERMODE_UP              =   ((uint16_t)0x0000),
    TIM_COUNTERMODE_DOWN            =   ((uint16_t)0x0010),
    TIM_COUNTERMODE_CENTERALIGNED1  =   ((uint16_t)0x0020),
    TIM_COUNTERMODE_CENTERALIGNED2  =   ((uint16_t)0x0040),
    TIM_COUNTERMODE_CENTERALIGNED3  =   ((uint16_t)0x0060),
} TIM_COUNTERMODE_t;

/**   
  * @brief  TIM_Clock_Division_CKD
  */
typedef enum {
    TIM_CKD_DIV1                =   ((uint16_t)0x0000),
    TIM_CKD_DIV2                =   ((uint16_t)0x0100),
    TIM_CKD_DIV4                =   ((uint16_t)0x0200),
} TIM_CKD_DIV_t;

/**   
  * @brief  TIM_interrupt_sources
  */
#define TIM_IT_UPDATE           ((uint16_t)0x0001)
#define TIM_IT_CC1              ((uint16_t)0x0002)
#define TIM_IT_CC2              ((uint16_t)0x0004)
#define TIM_IT_TRIGGER          ((uint16_t)0x0040)

/** 
  * @brief  TIM_Flags
  */
typedef enum {
    TIM_FLAG_UIF                =   ((uint16_t)0x0001),
    TIM_FLAG_CC1IF              =   ((uint16_t)0x0002),
    TIM_FLAG_CC2IF              =   ((uint16_t)0x0004),
    TIM_FLAG_TIF                =   ((uint16_t)0x0040),
    TIM_FLAG_CC1OF              =   ((uint16_t)0x0200),
    TIM_FLAG_CC2OF              =   ((uint16_t)0x0400),
} TIM_FLAG_t;

/** @defgroup TIM_Channel 
  * @{
  */
typedef enum {
    TIM_CHANNEL_1               =   ((uint16_t)0x0000),
    TIM_CHANNEL_2               =   ((uint16_t)0x0004),
} TIM_CHANNEL_t;

/** @defgroup TIM_Input_Capture_Polarity 
  * @{
  */
typedef enum {
    TIM_ICPOLARITY_RISING       =   ((uint16_t)0x0000),
    TIM_ICPOLARITY_FALLING      =   ((uint16_t)0x0002),
    TIM_ICPOLARITY_BOTHEDGE     =   ((uint16_t)0x000A),
} TIM_ICPOLARITY_t;

/** @defgroup TIM_Input_Capture_Selection 
  * @{
  */
typedef enum {
    TIM_ICSELECTION_DIRECTTI    =   ((uint16_t)0x0001),     /*!< TIM Input 1 or 2 is selected to be connected to IC1 or IC2, respectively */
    TIM_ICSELECTION_INDIRECTTI  =   ((uint16_t)0x0002),     /*!< TIM Input 1 or 2 is selected to be connected to IC2 or IC1, respectively. */
    TIM_ICSELECTION_TRC         =   ((uint16_t)0x0003),     /*!< TIM Input 1 or 2 is selected to be connected to TRC. */
} TIM_ICSELECTION_t;

/** @defgroup TIM_Input_Capture_Prescaler 
  * @{
  */
typedef enum {
    TIM_ICPSC_DIV1              =   ((uint16_t)0x0000),     /*!< Capture performed each time an edge is detected on the capture input. */
    TIM_ICPSC_DIV2              =   ((uint16_t)0x0004),     /*!< Capture performed once every 2 events. */
    TIM_ICPSC_DIV4              =   ((uint16_t)0x0008),     /*!< Capture performed once every 4 events. */
    TIM_ICPSC_DIV8              =   ((uint16_t)0x000C),     /*!< Capture performed once every 8 events. */
} TIM_ICPRESCALER_t;

/** @defgroup TIM_Event_Source 
  * @{
  */
typedef enum {
    TIM_EVENTSRC_UPDATE         =   ((uint16_t)0x0001),
    TIM_EVENTSRC_CC1            =   ((uint16_t)0x0002),
    TIM_EVENTSRC_CC2            =   ((uint16_t)0x0004),
    TIM_EVENTSRC_TRIGGER        =   ((uint16_t)0x0040),
} TIM_EVENTSOURCE_t;

/** @defgroup TIM_Output_Compare_modes 
  * @{
  */
typedef enum {
    TIM_OCMODE_TIMING           =   ((uint16_t)0x0000),
    TIM_OCMODE_ACTIVE           =   ((uint16_t)0x0010),
    TIM_OCMODE_INACTIVE         =   ((uint16_t)0x0020),
    TIM_OCMODE_TOGGLE           =   ((uint16_t)0x0030),
    TIM_OCMODE_FORCED_INACTIVE  =   ((uint16_t)0x0040),
    TIM_OCMODE_FORCED_ACTIVE    =   ((uint16_t)0x0050),
} TIM_OCMODE_t;

/** @defgroup TIM_Output_PWM_modes 
  * @{
  */
typedef enum {
    TIM_PWMMODE_PWM1             =   ((uint16_t)0x0060),
    TIM_PWMMODE_PWM2             =   ((uint16_t)0x0070),
} TIM_PWMMODE_t;


/** @defgroup TIM_Output_Compare_state 
  * @{
  */
#define TIM_OutputState_Disable            ((uint16_t)0x0000)
#define TIM_OutputState_Enable             ((uint16_t)0x0001)

/** @defgroup TIM_Output_Compare_Polarity 
  * @{
  */
typedef enum {
    TIM_OCPOLARITY_ACTIVE_HIGH  =   ((uint16_t)0x0000),
    TIM_OCPOLARITY_ACTIVE_LOW   =   ((uint16_t)0x0002),
} TIM_OCPOLARITY_t;

/** @defgroup TIM_Output_PWM_Polarity 
  * @{
  */
typedef enum {
    TIM_PWMPOLARITY_ACTIVE_HIGH  =   ((uint16_t)0x0000),
    TIM_PWMPOLARITY_ACTIVE_LOW   =   ((uint16_t)0x0002),
} TIM_PWMPOLARITY_t;

typedef enum {
    TIM_URS_ALL  =   0u,
    TIM_URS_OVERFLOW,
} TIM_URS_t;

/** @defgroup TIM_Internal_Trigger_Selection 
  * @{
  */
typedef enum {
    TIM_TS_DISABLED = 0x0u,
    TIM_TS_ITR0 = 0x0u,
    TIM_TS_ITR1 = 0x1u,
    TIM_TS_ITR2 = 0x2u,
    TIM_TS_ITR3 = 0x3u,
    TIM_TS_TI1F_ED = 0x4u,
    TIM_TS_TI1FP1 = 0x5u,
    TIM_TS_TI2FP2 = 0x6u,
    TIM_TS_ETRF = 0x7u,
} TIM_TS_t;

/** @defgroup TIM_Slave_Mode 
  * @{
  */
typedef enum {
    TIM_SLAVEMODE_DISABLED = 0x0u,
    TIM_SLAVEMODE_ENCODER1 = 0x1u,
    TIM_SLAVEMODE_ENCODER2 = 0x2u,
    TIM_SLAVEMODE_ENCODER3 = 0x3u,
    TIM_SLAVEMODE_RESET = 0x4u,
    TIM_SLAVEMODE_GATED = 0x5u,
    TIM_SLAVEMODE_TRIGGER = 0x6u,
    TIM_SLAVEMODE_EXTERNAL1 = 0x7u,
//    TIM_SLAVEMODE_EXTERNAL2 = 0x8u,
} TIM_SLAVEMODE_t;

typedef enum {
    TIM_ETF_DISABLE         = 0x00U,  /*!< No filter */
    TIM_ETF_FCK_N2          = 0x01U,  /*!< fSAMPLING = fCK_INT, N=2 */
    TIM_ETF_FCK_N4          = 0x02U,  /*!< fSAMPLING = fCK_INT, N=4 */
    TIM_ETF_FCK_N8          = 0x03U, 
    TIM_ETF_FDTS_D2_N6      = 0x04U,  /*!< fSAMPLING = fDTS/2, N=6 */
    TIM_ETF_FDTS_D2_N8      = 0x05U,  
    TIM_ETF_FDTS_D4_N6      = 0x06U,  
    TIM_ETF_FDTS_D4_N8      = 0x07U,
    TIM_ETF_FDTS_D8_N6      = 0x08U,
    TIM_ETF_FDTS_D8_N8      = 0x09U,
    TIM_ETF_FDTS_D16_N5     = 0x0AU,
    TIM_ETF_FDTS_D16_N6     = 0x0BU,
    TIM_ETF_FDTS_D16_N8     = 0x0CU,
    TIM_ETF_FDTS_D32_N5     = 0x0DU,
    TIM_ETF_FDTS_D32_N6     = 0x0EU,
    TIM_ETF_FDTS_D32_N8     = 0x0FU,   /*!< fSAMPLING = fDTS/32, N=8 */
} TIM_ETF_t;

/**
  * @brief  External Trigger Prescaler
  */
typedef enum {
    TIM_ETR_PRESCALER_DISABLE    = 0x00U,  /*!< Prescaler off */
    TIM_ETR_PRESCALER_DIV2       = 0x01U,  /*!< ETRP frequency divided by 2 */
    TIM_ETR_PRESCALER_DIV4       = 0x02U,  /*!< ETRP frequency divided by 4 */
    TIM_ETR_PRESCALER_DIV8       = 0x03U   /*!< ETRP frequency divided by 8 */
} TIM_ETPSC_t;
                     
/**
  * @brief  External Trigger Polarity
  */
typedef enum {
    TIM_ETR_POLARITY_NONINVERTED = 0x00U,  /*!< ETR non-inverted, active high/rising */
    TIM_ETR_POLARITY_INVERTED    = 0x01U   /*!< ETR inverted, active low/falling */
} TIM_ETPOL_t;
                     
/** 
  * @brief  TIM Time Base Init structure definition
  */
typedef struct
{
    uint16_t            Prescaler;      /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */
                                       
    uint16_t            Period;         /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF  */ 
                                       
    TIM_COUNTERMODE_t   CounterMode;    /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */
    
    FunctionalState     AutoReloadPreload;  /*!< Specifies if ARR Preload or Immediate Load */
    
    TIM_CKD_DIV_t       ClockDivision;  /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */
                                      
} TIM_InitTypeDef;       

/** 
  * @brief  TIM Output Compare Init structure definition  
  */
typedef struct
{
    TIM_OCMODE_t        OCMode;         /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_modes */
                                   
    TIM_OCPOLARITY_t    OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

    FunctionalState     OCPinState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */

    FunctionalState     OCPreload;      /*!< 禁用或使能CCR1预装载功能 */

    uint16_t            Pulse;      /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

} TIM_OCInitTypeDef;

/** 
  * @brief  TIM PWM Init structure definition  
  */
typedef struct
{
    TIM_PWMMODE_t        PWMMode;         /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_modes */
                                   
    TIM_PWMPOLARITY_t    PWMPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

    FunctionalState     PWMFastMode;      /*!< 禁用或使能CCR1 PWM模式下快速装载功能 */
    
    FunctionalState     PWMPreload;      /*!< 禁用或使能CCR1 PWM预装载功能 */

    uint16_t            Pulse;      /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

} TIM_PWMInitTypeDef;

/** 
  * @brief  TIM Input Capture Init structure definition  
  */
typedef struct
{
    uint16_t            ICFilter;       /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
                                  
    TIM_ICPRESCALER_t   ICPrescaler;    /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */                                  
                                  
    TIM_ICPOLARITY_t    ICPolarity;     /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

    TIM_ICSELECTION_t   ICSelection;    /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */
    
    uint8_t             Reserved;
                                  
} TIM_ICInitTypeDef;

/**
  * @brief  Slave Mode Configuration Structure
  */
typedef struct {
    /* Basic Configuration */
    TIM_SLAVEMODE_t     SlaveMode;          /*!< Slave mode selection */
    
    TIM_TS_t            TriggerSource;      /*!< Trigger source selection */
    
    FunctionalState     MasterSlaveSync;    /*!< Master/Slave synchronization */
    
    /* External Trigger Configuration (only when triggerSource = TIM_TS_ETRF) */
    TIM_ETPOL_t         ETRPolarity;        /*!< ETR polarity */
    
    TIM_ETPSC_t         ETRPrescaler;       /*!< ETR prescaler */
    
    TIM_ETF_t           ETRFilter;          /*!< ETR digital filter */
    
} TIM_SMInitTypeDef;

/**  
  * @brief TIM_Update_Source
  */
typedef enum {
    TIM_UPDATESOURCE_GLOBAL     = ((uint16_t)0x0000), /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
    TIM_UPDATESOURCE_REGULAR    = ((uint16_t)0x0001), /*!< Source of update is counter overflow/underflow. */
    
} TIM_UPDATESOURCE_t;

typedef enum {
    TIM_TRGOSOURCE_RESET        = ((uint16_t)0x0000),
    TIM_TRGOSOURCE_ENABLE       = ((uint16_t)0x0010),
    TIM_TRGOSOURCE_UPDATE       = ((uint16_t)0x0020),
    TIM_TRGOSOURCE_OC1          = ((uint16_t)0x0030),
    TIM_TRGOSOURCE_OC1REF       = ((uint16_t)0x0040),
    TIM_TRGOSOURCE_OC2REF       = ((uint16_t)0x0050),
} TIM_TRGOSOURCE_t;
                                         

/** @defgroup TIM_One_Pulse_Mode 
  * @{
  */

#define TIM_OPMode_Single                  ((uint16_t)0x0008)
#define TIM_OPMode_Repetitive              ((uint16_t)0x0000)
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))
/**
  * @}
  */ 


/**
  * @}
  */



/** @defgroup TIM_Capture_Compare_state 
  * @{
  */

#define TIM_CCx_Enable                      ((uint16_t)0x0001)
#define TIM_CCx_Disable                     ((uint16_t)0x0000)
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))
/**
  * @}
  */ 



/** @defgroup TIM_AOE_Bit_Set_Reset 
  * @{
  */

#define TIM_AutomaticOutput_Enable         ((uint16_t)0x4000)
#define TIM_AutomaticOutput_Disable        ((uint16_t)0x0000)
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable))
/**
  * @}
  */ 

/** @defgroup Lock_level 
  * @{
  */

#define TIM_LOCKLevel_OFF                  ((uint16_t)0x0000)
#define TIM_LOCKLevel_1                    ((uint16_t)0x0100)
#define TIM_LOCKLevel_2                    ((uint16_t)0x0200)
#define TIM_LOCKLevel_3                    ((uint16_t)0x0300)
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) || \
                                  ((LEVEL) == TIM_LOCKLevel_2) || \
                                  ((LEVEL) == TIM_LOCKLevel_3))
/**
  * @}
  */ 

/** @defgroup OSSI_Off_State_Selection_for_Idle_mode_state 
  * @{
  */

#define TIM_OSSIState_Enable               ((uint16_t)0x0400)
#define TIM_OSSIState_Disable              ((uint16_t)0x0000)
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))
/**
  * @}
  */

/** @defgroup OSSR_Off_State_Selection_for_Run_mode_state 
  * @{
  */

#define TIM_OSSRState_Enable               ((uint16_t)0x0800)
#define TIM_OSSRState_Disable              ((uint16_t)0x0000)
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Idle_State 
  * @{
  */

#define TIM_OCIdleState_Set                ((uint16_t)0x0100)
#define TIM_OCIdleState_Reset              ((uint16_t)0x0000)
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))
/**
  * @}
  */ 

 



/** 
  * @brief  TIM_DMA_Base_address
  */
typedef enum {
    TIM_DMABASE_CR1         = ((uint16_t)0x0000),
    TIM_DMABASE_CR2         = ((uint16_t)0x0001),
    TIM_DMABASE_SMCR        = ((uint16_t)0x0002),
    TIM_DMABASE_DIER        = ((uint16_t)0x0003),
    TIM_DMABASE_SR          = ((uint16_t)0x0004),
    TIM_DMABASE_EGR         = ((uint16_t)0x0005),
    TIM_DMABASE_CCMR1       = ((uint16_t)0x0006),
    TIM_DMABASE_CCMR2       = ((uint16_t)0x0007),
    TIM_DMABASE_CCER        = ((uint16_t)0x0008),
    TIM_DMABASE_CNT         = ((uint16_t)0x0009),
    TIM_DMABASE_PSC         = ((uint16_t)0x000A),
    TIM_DMABASE_ARR         = ((uint16_t)0x000B),
    TIM_DMABASE_RCR         = ((uint16_t)0x000C),
    TIM_DMABASE_CCR1        = ((uint16_t)0x000D),
    TIM_DMABASE_CCR2        = ((uint16_t)0x000E),
    TIM_DMABASE_CCR3        = ((uint16_t)0x000F),
    TIM_DMABASE_CCR4        = ((uint16_t)0x0010),
    TIM_DMABASE_BDTR        = ((uint16_t)0x0011),
    TIM_DMABASE_DCR         = ((uint16_t)0x0012),
} TIM_DMABASE_t;

/** @  
  * @brief TIM_DMA_Burst_Length
  */
typedef enum {
    TIM_DMABURSTLENGTH_1BYTE        = ((uint16_t)0x0000),
    TIM_DMABURSTLENGTH_2BYTE        =  ((uint16_t)0x0100),
    TIM_DMABURSTLENGTH_3BYTE        =  ((uint16_t)0x0200),
    TIM_DMABURSTLENGTH_4BYTE        =  ((uint16_t)0x0300),
    TIM_DMABURSTLENGTH_5BYTE        =  ((uint16_t)0x0400),
    TIM_DMABURSTLENGTH_6BYTE        =  ((uint16_t)0x0500),
    TIM_DMABURSTLENGTH_7BYTE        =  ((uint16_t)0x0600),
    TIM_DMABURSTLENGTH_8BYTE        =  ((uint16_t)0x0700),
    TIM_DMABURSTLENGTH_9BYTE        =  ((uint16_t)0x0800),
    TIM_DMABURSTLENGTH_10BYTE       =  ((uint16_t)0x0900),
    TIM_DMABURSTLENGTH_11BYTE       =  ((uint16_t)0x0A00),
    TIM_DMABURSTLENGTH_12BYTE       =  ((uint16_t)0x0B00),
    TIM_DMABURSTLENGTH_13BYTE       =  ((uint16_t)0x0C00),
    TIM_DMABURSTLENGTH_14BYTE       =  ((uint16_t)0x0D00),
    TIM_DMABURSTLENGTH_15BYTE       =  ((uint16_t)0x0E00),
    TIM_DMABURSTLENGTH_16BYTE       =  ((uint16_t)0x0F00),
    TIM_DMABURSTLENGTH_17BYTE       =  ((uint16_t)0x1000),
    TIM_DMABURSTLENGTH_18BYTE       =  ((uint16_t)0x1100),
} TIM_DMABURSTLENGTH_t;

/** @defgroup TIM_DMA_sources 
  * @{
  */
typedef enum {
    TIM_DMA_UPDATE          = ((uint16_t)0x0100),
    TIM_DMA_CC1             = ((uint16_t)0x0200),
    TIM_DMA_CC2             = ((uint16_t)0x0400),
    TIM_DMA_TRIGGER         = ((uint16_t)0x4000),
} TIM_DMASOURCE_t;

/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Prescaler 
  * @{
  */

#define TIM_ExtTRGPSC_OFF                  ((uint16_t)0x0000)
#define TIM_ExtTRGPSC_DIV2                 ((uint16_t)0x1000)
#define TIM_ExtTRGPSC_DIV4                 ((uint16_t)0x2000)
#define TIM_ExtTRGPSC_DIV8                 ((uint16_t)0x3000)
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))
/**
  * @}
  */ 



/** @defgroup TIM_TIx_External_Clock_Source 
  * @{
  */

#define TIM_TIxExternalCLK1Source_TI1      ((uint16_t)0x0050)
#define TIM_TIxExternalCLK1Source_TI2      ((uint16_t)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED    ((uint16_t)0x0040)
#define IS_TIM_TIXCLK_SOURCE(SOURCE) (((SOURCE) == TIM_TIxExternalCLK1Source_TI1) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI2) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI1ED))
/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Polarity 
  * @{
  */ 
#define TIM_ExtTRGPolarity_Inverted        ((uint16_t)0x8000)
#define TIM_ExtTRGPolarity_NonInverted     ((uint16_t)0x0000)
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))
/**
  * @}
  */


/**
  * @}
  */ 

/** @defgroup TIM_Forced_Action 
  * @{
  */

#define TIM_ForcedAction_Active            ((uint16_t)0x0050)
#define TIM_ForcedAction_InActive          ((uint16_t)0x0040)
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))
/**
  * @}
  */ 

/** @defgroup TIM_Encoder_Mode 
  * @{
  */

#define TIM_EncoderMode_TI1                ((uint16_t)0x0001)
#define TIM_EncoderMode_TI2                ((uint16_t)0x0002)
#define TIM_EncoderMode_TI12               ((uint16_t)0x0003)
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))
/**
  * @}
  */ 



#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */ 


/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Preload_State 
  * @{
  */

#define TIM_OCPreload_Enable               ((uint16_t)0x0008)
#define TIM_OCPreload_Disable              ((uint16_t)0x0000)
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Fast_State 
  * @{
  */

#define TIM_OCFast_Enable                  ((uint16_t)0x0004)
#define TIM_OCFast_Disable                 ((uint16_t)0x0000)
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))
                                     
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Clear_State 
  * @{
  */

#define TIM_OCClear_Enable                 ((uint16_t)0x0080)
#define TIM_OCClear_Disable                ((uint16_t)0x0000)
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))
/**
  * @}
  */ 

/** @defgroup TIM_Trigger_Output_Source 
  * @{
  */



/** @defgroup TIM_Master_Slave_Mode 
  * @{
  */

#define TIM_MasterSlaveMode_Enable         ((uint16_t)0x0080)
#define TIM_MasterSlaveMode_Disable        ((uint16_t)0x0000)
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))
/**
  * @}
  */ 




/* Function Declaration ------------------------------------------------------*/
void            LHL_TIM_DeInit(TIM_TypeDef* TIMx);
void            LHL_TIM_Init(TIM_TypeDef* TIMx, TIM_InitTypeDef* TIM_InitStruct);

void            LHL_TIM_Start(TIM_TypeDef* TIMx);
void            LHL_TIM_Stop(TIM_TypeDef* TIMx);

void            LHL_TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_ITs, FunctionalState NewState);

ITStatus        LHL_TIM_GetPending(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void            LHL_TIM_ClearPending(TIM_TypeDef* TIMx, uint16_t TIM_IT);

FlagStatus      LHL_TIM_GetFlag(TIM_TypeDef* TIMx, TIM_FLAG_t TIM_FLAG);
void            LHL_TIM_ClearFlag(TIM_TypeDef* TIMx, TIM_FLAG_t TIM_FLAG);

void            LHL_TIM_IC_Init(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct, TIM_CHANNEL_t TIM_CHx);
void            LHL_TIM_IC_Cmd(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx, FunctionalState NewState);
void            LHL_TIM_IC_SetPrescaler(TIM_TypeDef* TIMx, TIM_ICPRESCALER_t TIM_ICPSC, TIM_CHANNEL_t TIM_CHx);
//void            LHL_TIM_IC_Start(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx);
void            LHL_TIM_IC_Stop(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx);
uint16_t        LHL_TIM_IC_GetCapture(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx);

void            LHL_TIM_OC_Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct, TIM_CHANNEL_t TIM_CHx);
void            LHL_TIM_OC_Cmd(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx, FunctionalState NewState);
void            LHL_TIM_OC_SetCompare(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx, uint16_t Compare);
//void            LHL_TIM_OC_Start(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx);
void            LHL_TIM_OC_Stop(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx);

LHL_StatusTypeDef   LHL_TIM_SMInit(TIM_TypeDef* TIMx, TIM_SMInitTypeDef *smInit);

void            LHL_TIM_PWM_Init(TIM_TypeDef* TIMx, TIM_PWMInitTypeDef* TIM_PWMInitStruct, TIM_CHANNEL_t TIM_CHx);
void            LHL_TIM_PWM_SetDutyCycle(TIM_TypeDef* TIMx, uint16_t DutyCyle, TIM_CHANNEL_t TIM_CHx);

void            LHL_TIM_GenerateEvent(TIM_TypeDef* TIMx, TIM_EVENTSOURCE_t TIM_EventSource);

void            LHL_TIM_SetOnePulseMode(TIM_TypeDef* TIMx, FunctionalState NewState);
void            LHL_TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload);

void            LHL_TIM_SetSlaveMode(TIM_TypeDef* TIMx, TIM_SLAVEMODE_t TIM_SlaveMode);
void            LHL_TIM_SetInputTrigger(TIM_TypeDef* TIMx, TIM_TS_t TIM_InputTriggerSource);
void            LHL_TIM_SetClockDivision(TIM_TypeDef* TIMx, TIM_CKD_DIV_t TIM_CKD);
void            LHL_TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);
void            LHL_TIM_SetPrescaler(TIM_TypeDef* TIMx, uint16_t Prescaler);
void            LHL_TIM_SetCounterMode(TIM_TypeDef* TIMx, TIM_COUNTERMODE_t TIM_CounterMode);
void            LHL_TIM_SetARRPreload(TIM_TypeDef* TIMx, FunctionalState NewState);
void            LHL_TIM_SetUpdateEvent(TIM_TypeDef* TIMx, FunctionalState NewState);
void            LHL_TIM_SetOutputTrigger(TIM_TypeDef* TIMx, TIM_TRGOSOURCE_t TIM_TRGOSource);
void            LHL_TIM_SetUpdateRequest(TIM_TypeDef* TIMx, TIM_UPDATESOURCE_t TIM_UpdateSource);
void            LHL_TIM_SetMasterSlaveMode(TIM_TypeDef* TIMx, FunctionalState NewState);

uint16_t        LHL_TIM_GetCounter(TIM_TypeDef* TIMx);
uint16_t        LHL_TIM_GetPrescaler(TIM_TypeDef* TIMx);

void            LHL_TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void            LHL_TIM_SetCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void            LHL_TIM_DMAConfig(TIM_TypeDef* TIMx, TIM_DMABASE_t TIM_DMABase, TIM_DMABURSTLENGTH_t TIM_DMABurstLength);


#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
