/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_rcc.h
 * @version 2025-09-01
 ******************************************************************************/

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __LH32M0G3x_RCC_H
#define __LH32M0G3x_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"
                          
/* Public Definition ---------------------------------------------------------*/
/**
  * @brief 获取RCC时钟树结构体参数
  */
typedef struct
{
  uint32_t SYSCLK_Frequency;    /*!<  SYSCLK clock frequency expressed in Hz */
  
  uint32_t HCLK_Frequency;      /*!<  HCLK clock frequency expressed in Hz   */
  
  uint32_t PCLK1_Frequency;     /*!<  PCLK1 clock frequency expressed in Hz  */
  
  uint32_t PCLK2_Frequency;     /*!<  PCLK2 clock frequency expressed in Hz  */
  
} RCC_ClocksTypeDef;

/**
  * @brief RCC System, AHB and APB bus clock configuration structure definition
  */
typedef struct
{                                       
  uint32_t SYSCLKSource;        /*!< The clock source used as system clock (SYSCLK).
                                This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t AHBCLKDivider;       /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                This parameter can be a value of @ref RCC_HCLK_Clock_Source       */

  uint32_t APB1CLKDivider;      /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                This parameter can be a value of @ref RCC_APB1_Clock_Source */

  uint32_t APB2CLKDivider;      /*!< The APB2 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                This parameter can be a value of @ref RCC_APB1_Clock_Source */

} RCC_ClockInitTypeDef;

/**
  * @brief RCC Reset Source Type Define Structure
  */
typedef struct
{
    FlagStatus PORReset;        /*!< POR/PDR reset flag */
    
    FlagStatus PINReset;        /*!< NRST pin reset flag */
    
    FlagStatus SFTReset;        /*!< Software reset flag */
    
    FlagStatus IWDGReset;       /*!< Independent watchdog reset flag */
    
} RCC_ResetSourceTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_System_Clock_Source
  * @{
  */
#define RCC_SYSCLK_SRC_HSI_DIV2             ((uint32_t)0x4)
#define RCC_SYSCLK_SRC_HSI_DIV1             ((uint32_t)0x0)
#define RCC_SYSCLK_SRC_HSE                  ((uint32_t)0x1)
#define RCC_SYSCLK_SRC_LSI                  ((uint32_t)0x2)
#define RCC_SYSCLK_SRC_LSE                  ((uint32_t)0x3)
  
/** @defgroup RCC_HSE_configuration 
  * @{
  */
#define RCC_HSE_OFF                         (0)
#define RCC_HSE_ON                          (RCC_CR_HSEON_Msk)

/** @defgroup RCC_Flag 
  * @{
  */
#define RCC_FLAG_LSIRDY                     (RCC_CSR_LSIRDY_Msk)
#define RCC_FLAG_PVDRST                     (RCC_CSR_PVDRSTF_Msk)             
#define RCC_FLAG_PINRST                     (RCC_CSR_PINRSTF_Msk)            
#define RCC_FLAG_PORRST                     (RCC_CSR_PORRSTF_Msk)            
#define RCC_FLAG_SFTRST                     (RCC_CSR_SFTRSTF_Msk)            
#define RCC_FLAG_IWDGRST                    (RCC_CSR_IWDGRSTF_Msk) 

/** @defgroup HSI DIV
  * @{
  */
#define RCC_HSI_DIV1                        ((uint32_t)0x0)
#define RCC_HSI_DIV2                        ((uint32_t)0x1)

/** @defgroup RCC_SYSCLK_Source
  * @{
  */
#define RCC_SW_HSI                          ((uint32_t)0x0)
#define RCC_SW_HSE                          ((uint32_t)0x1)
#define RCC_SW_LSI                          ((uint32_t)0x2)
#define RCC_SW_LSE                          ((uint32_t)0x3)

/** @defgroup RCC_AHB_Clock_Source
  * @{
  */
#define RCC_SYSCLK_DIV1                     ((uint32_t)0x0)
#define RCC_SYSCLK_DIV2                     ((uint32_t)0x8)
#define RCC_SYSCLK_DIV4                     ((uint32_t)0x9)
#define RCC_SYSCLK_DIV8                     ((uint32_t)0xA)
#define RCC_SYSCLK_DIV16                    ((uint32_t)0xB)
#define RCC_SYSCLK_DIV64                    ((uint32_t)0xC)
#define RCC_SYSCLK_DIV128                   ((uint32_t)0xD)
#define RCC_SYSCLK_DIV256                   ((uint32_t)0xE)
#define RCC_SYSCLK_DIV512                   ((uint32_t)0xF)

/** @defgroup RCC_APB1_APB2_Clock_Source
  * @{
  */
#define RCC_HCLK_DIV1                       ((uint32_t)0x0)
#define RCC_HCLK_DIV2                       ((uint32_t)0x4)
#define RCC_HCLK_DIV4                       ((uint32_t)0x5)
#define RCC_HCLK_DIV8                       ((uint32_t)0x6)
#define RCC_HCLK_DIV16                      ((uint32_t)0x7)

/** @defgroup RCC_MCO_Clock_Source
  * @{
  */
#define RCC_MCOSOURCE_LSI                   ((uint32_t)0)
#define RCC_MCOSOURCE_SYSCLK                ((uint32_t)1)
#define RCC_MCOSOURCE_HSI                   ((uint32_t)2)
#define RCC_MCOSOURCE_HSE                   ((uint32_t)3)
#define RCC_MCOSOURCE_LSE                   ((uint32_t)4)
#define RCC_MCOSOURCE_PCLK1                 ((uint32_t)5)
#define RCC_MCOSOURCE_PCLK2                 ((uint32_t)6)
#define RCC_MCOSOURCE_HCLK                  ((uint32_t)7)
#define RCC_MCOSOURCE_ADC_OUT_CLK           ((uint32_t)8)

/** @defgroup RTC_clock_source 
  * @{
  */
#define RCC_RTCCLKSource_LSE                ((uint32_t)0x00000100)
#define RCC_RTCCLKSource_LSI                ((uint32_t)0x00000200)
#define RCC_RTCCLKSource_HSE_DIV128         ((uint32_t)0x00000300)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/* Function used to set the RCC clock configuration to the default reset state */
void                LHL_RCC_DeInit(void);
LHL_StatusTypeDef   LHL_RCC_ClockConfig(const RCC_ClockInitTypeDef *RCC_Clock_Init, uint32_t timeout);

/* Internal/external clocks, PLL, CSS and MCO configuration functions *********/
LHL_StatusTypeDef   LHL_RCC_LSEConfig(FunctionalState NewState);
LHL_StatusTypeDef   LHL_RCC_HSEConfig(FunctionalState NewState);

void        LHL_RCC_HSIConfig(uint32_t RCC_HSI_DIV);
void        LHL_RCC_HSICmd(FunctionalState NewState);

void        LHL_RCC_MCOConfig(uint32_t RCC_MCOSource);

/* System, AHB and APB busses clocks configuration functions ******************/
void        LHL_RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
void        LHL_RCC_HSIConfig(uint32_t RCC_HSI_DIV);
void        LHL_RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void        LHL_RCC_PCLK1Config(uint32_t RCC_HCLK);
void        LHL_RCC_PCLK2Config(uint32_t RCC_HCLK);

void        LHL_RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

uint32_t    LHL_RCC_GetSystemClockFreq(void);
uint32_t    LHL_RCC_GetHCLKFreq(void);
uint32_t    LHL_RCC_GetPCLK1Freq(void);
uint32_t    LHL_RCC_GetPCLK2Freq(void);

/* Peripheral clocks configuration functions **********************************/
void        RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void        RCC_RTCCLKCmd(FunctionalState NewState);
void        RCC_BackupResetCmd(FunctionalState NewState);

void        RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void        RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void        RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

void        RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void        RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
FlagStatus  LHL_RCC_GetFlag(uint32_t RCC_FLAG);
void        LHL_RCC_ClearFlag(void);

RCC_ResetSourceTypeDef LHL_RCC_GetResetSource(void);

void        LHL_RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);
ITStatus    LHL_RCC_GetPending(uint32_t RCC_IT);
void        LHL_RCC_ClearPending(uint32_t RCC_IT);

void        LHL_RCC_ResetHSI(void);
void        LHL_RCC_CalibrateHSI(uint32_t Measured_Frequency, uint32_t Target_Frequency);

void        LHL_RCC_Unlock(void);
void        LHL_RCC_Lock(void);
#ifdef __cplusplus
}
#endif

#endif 

/*********************************End of File**********************************/
