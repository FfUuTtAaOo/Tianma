/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_iwdg.h
 * @version 2025-09-08
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_IWDG_H
#define __LH32M0G3x_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Public Definition ---------------------------------------------------------*/

/* KR register bit mask */
#define KR_KEY_RELOAD   ((uint16_t)0xAAAA)
#define KR_KEY_ENABLE   ((uint16_t)0xCCCC)
#define KR_KEY_START    ((uint16_t)0xAAAA)
#define KR_KEY_UNLOCK   ((uint16_t)0x5555)

/** @defgroup IWDG_prescaler 
  * @{
  */
typedef enum {
    IWDG_PRESCALER_4    = ((uint8_t)0x00),
    IWDG_PRESCALER_8    = ((uint8_t)0x01),
    IWDG_PRESCALER_16   = ((uint8_t)0x02),
    IWDG_PRESCALER_32   = ((uint8_t)0x03),
    IWDG_PRESCALER_64   = ((uint8_t)0x04),
    IWDG_PRESCALER_128  = ((uint8_t)0x05),
    IWDG_PRESCALER_256  = ((uint8_t)0x06),
} IWDG_PRESCALER_t;
/**
  * @}
  */ 

/** @defgroup IWDG_Flag 
  * @{
  */
#define IWDG_FLAG_PVU               ((uint16_t)0x0001)
#define IWDG_FLAG_RVU               ((uint16_t)0x0002)
#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU))
#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Prescaler and Counter configuration functions ******************************/
LHL_StatusTypeDef   LHL_IWDG_SetPrescaler(IWDG_PRESCALER_t IWDG_Prescaler, uint32_t Timeout);
LHL_StatusTypeDef   LHL_IWDG_SetReload(uint16_t Reload, uint32_t Timeout);
LHL_StatusTypeDef   LHL_IWDG_Unlock(void);
void                LHL_IWDG_Lock(void);

/* IWDG activation function ***************************************************/
void                LHL_IWDG_Reload(void);
LHL_StatusTypeDef   LHL_IWDG_Stop(void);
LHL_StatusTypeDef   LHL_IWDG_Resume(void);
LHL_StatusTypeDef   LHL_IWDG_Start(void);

/* Flag management function ***************************************************/
//FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
