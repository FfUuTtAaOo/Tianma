/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_dac.h
 * @version 2025-09-22
 ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_DAC_H
#define __LH32M0G3x_DAC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Defines -------------------------------------------------------------------*/
#define DAC_KEY             (0x6E940000)

typedef enum {
    DAC_OUTPUT              = 0u,
    OWI_OUTPUT              = 1u,
    PWM_VOLTAGE_OUTPUT      = 2u,
    PWM_DIGITAL_OUTPUT      = 6u,
} DAC_OUT_MODE_t;

typedef enum {
    DAC_VOLTAGE_MODE        = 0u,
    DAC_CURRENT_MODE,
} DAC_MODE_t;

typedef enum {
    DAC_VOLTAGE_RANGE_5V    = 0u,
    DAC_VOLTAGE_RANGE_2P5V  = 1u,
    DAC_VOLTAGE_RANGE_1P2V  = 2u,
    DAC_VOLTAGE_RANGE_AVDD  = 3u,
} DAC_VOLTAGE_RANGE_t;

typedef enum {
    DAC_CLOAD_0_to_100pF    = 0u,                   
    DAC_CLOAD_0_to_25nF     = 4u,                   /*已考虑CLOAD_100NF_EN位设置*/
    DAC_CLOAD_25_to_50nF    = 5u,
    DAC_CLOAD_50_to_75nF    = 6u,
    DAC_CLOAD_75_to_100nF   = 7u,
} DAC_CLOAD_CAPABILITY_t;

typedef enum {
    DAC_TRIGGER_SOFTWARE    = 0u,
    DAC_TRIGGER_HARDWARE,
} DAC_TRIGGER_t;

typedef enum {
    DAC_DRV_STR_WEAKEST     = 0u,   /* 驱动强度最弱 */
    DAC_DRV_STR_WEAK,
    DAC_DRV_STR_STRONG,
    DAC_DRV_STR_STRONGEST,
} DAC_PWM_DRIVE_STRENGTH_t;
     
typedef struct {

    DAC_OUT_MODE_t                  Output_Mode;            /* DAC使用模式 */
    
    DAC_MODE_t                      DAC_Mode;               /* DAC输出电压电流模式 */
    
    DAC_VOLTAGE_RANGE_t             DAC_Voltage_Range;      /* DAC电压输出Range选择 */
    
    DAC_CLOAD_CAPABILITY_t          CLoad_Capability;       /* 电压输出负载电容大小 */
    
    FunctionalState                 LoopN_Div;              /* loopn 电阻分压使能 */
    
    FunctionalState                 Filter;                 /* dac输出滤波使能（HART位置外接电容） */
    
    DAC_TRIGGER_t                   Trigger;                /* 引脚触发DAC输出使能 */
    
    DAC_PWM_DRIVE_STRENGTH_t        PWM_Drive_Strength;     /* dac作为数字输出时，驱动强度控制 */
    
} DAC_InitTypeDef;

/* Declaration ---------------------------------------------------------------*/
LHL_StatusTypeDef   LHL_DAC_Init(DAC_InitTypeDef *DAC_Init);

void                LHL_DAC_Start(void);
void                LHL_DAC_Stop(void);

void                LHL_DAC_SetData(uint16_t data);
void                LHL_DAC_SetRange(DAC_VOLTAGE_RANGE_t range);

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
