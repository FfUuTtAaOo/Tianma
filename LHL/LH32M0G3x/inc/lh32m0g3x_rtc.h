/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_rtc.h
 * @version 2025-09-08
 ******************************************************************************/
 
/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __LH32M0G3x_RTC_H
#define __LH32M0G3x_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"     

/* Public Definition ---------------------------------------------------------*/
/**
  * @brief  RTC Configuration Structure definition
  */
typedef struct
{
  uint32_t ClockSource;     /*!< Specifies the RTC Clock Source: LSI, LSE or HSE/128 */
  
  uint32_t Prescaler;       /*!< Specifies the RTC Synchronous Predivider value.
                                 This parameter must be a number between Min_Data = 0x1 and Max_Data = 0xFFFFF */

  uint32_t Counter;         /*!< Specifies the RTC Counter value. Max Data 32bit */

  uint32_t Alarm;           /*!< Specifies the RTC Alarm value. Max Data 32bit */

} RTC_InitTypeDef;

/** 
  * @brief  RTC Flags 
  */ 
#define RTC_FLAG_SECF           ((uint32_t)0x1)     // 秒标志
#define RTC_FLAG_ALRF           ((uint32_t)0x2)     // 闹钟标志
#define RTC_FLAG_OWF            ((uint32_t)0x4)     // 溢出标志

/** 
  * @brief  RTC IT 
  */
#define RTC_IT_SECIE            ((uint32_t)0x1)     /* 允许秒中断 (Second interrupt enable) 0：屏蔽(不允许)秒中断1：允许秒中断*/
#define RTC_IT_ALRIE            ((uint32_t)0x2)     /* 允许闹钟中断 (Alarm interrupt enable) 0：屏蔽(不允许)闹钟中断1：允许闹钟中断*/
#define RTC_IT_OWIE             ((uint32_t)0x4)     /* 允许溢出中断位 (Overflow interrupt enable) 0：屏蔽(不允许)溢出中断1：允许溢出中断*/

/* Function Prototype --------------------------------------------------------*/
LHL_StatusTypeDef LHL_RTC_Init(RTC_InitTypeDef* RTC_Init);

LHL_StatusTypeDef RTC_WaitForReadSync(void);
LHL_StatusTypeDef RTC_WaitForWriteDone(void);

/*--------- cnt, prescaler ----------*/
LHL_StatusTypeDef LHL_RTC_SetCounter(uint32_t cnt);
LHL_StatusTypeDef LHL_RTC_SetPrescaler(uint32_t prl);

LHL_StatusTypeDef LHL_RTC_GetCounter(uint32_t* cnt);

/*--------- alarm ------------*/
LHL_StatusTypeDef LHL_RTC_SetAlarm(uint32_t alarm);

/*--------- Interrupt ----------*/
LHL_StatusTypeDef LHL_RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState);

ITStatus LHL_RTC_GetPending(uint32_t RTC_IT_FLAG);
LHL_StatusTypeDef LHL_RTC_ClearPending(uint32_t RTC_IT_FLAG);

#ifdef __cplusplus
}
#endif

#endif 

/*********************************End of File**********************************/
