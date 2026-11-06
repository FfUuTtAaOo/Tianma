/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_power.h
 * @version 2025-09-22
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_PWR_H
#define __LH32M0G3x_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Defines -------------------------------------------------------------------*/  
/** 
  * @brief  Config power mode while sleeping 
  */
typedef enum {
    PWR_MODE_SLEEP          = 0u,
    PWR_MODE_DEEP_SLEEP_1,
    PWR_MODE_DEEP_SLEEP_2,
    PWR_MODE_SNOOZE,
    PWR_MODE_SHUTDOWN,
//    PWR_MODE_SPECIAL, deprecated for V10
} PWR_POWERMODE_t;

typedef enum {
    PVD_TH_2_6V             = 0u,
    PVD_TH_2_8V             = 1u,
    PVD_TH_3_0V             = 2u,
    PVD_TH_3_6V             = 3u,
    PVD_TH_4_5V             = 4u,
} PVD_THRESHOLD_t;

typedef enum {
    PVD_MODE_IOVDD          = 0u,
    PVD_MODE_AVDD           = 1u,
} PVD_MODE_t;

typedef struct {

    PVD_MODE_t          DetectionSignal;        /*<! 低电压检测信号选择 */
    
    PVD_THRESHOLD_t     ThresholdVoltage;       /*<! 低电压检测阈值挡位 */    
    
    FunctionalState     State;                  /*<! 使能低电压检测功能 */
    
} PVD_InitTypeDef;

/* Function Prototype --------------------------------------------------------*/
/* 低功耗休眠 */
void        LHL_PWR_SetPowerMode(PWR_POWERMODE_t mode);

void        LHL_PWR_EnterSleep(void);

/* 低电压检测 */
void        LHL_PVD_Init(PVD_InitTypeDef *PVD_InitStruct);

FlagStatus  LHL_PVD_GetFlag(void);

/* 备份域访问 */
void        PWR_BackupAccessCmd(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
