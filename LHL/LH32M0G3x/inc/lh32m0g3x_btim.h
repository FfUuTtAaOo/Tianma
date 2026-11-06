/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_btim.h
 * @version    2025-09-29
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_BTIM_H
#define __LH32M0G3x_BTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Public Definition ---------------------------------------------------------*/
#define BTIM_TCTRL_TEN_Msk          (0x1U)
#define BTIM_TCTRL_TEN_Pos          (0U)

#define BTIM_TCTRL_TIE_Msk          (0x2U)
#define BTIM_TCTRL_TIE_Pos          (1U)

#define BTIM_TCTRL_CHN_Msk          (0x4U)
#define BTIM_TCTRL_CHN_Pos          (2U)

#define BTIM_TFLG_TIF_Msk           (0x1U)

/**
  * @brief  BTIMER：32位链式模式；BTIMER_x：16位独立模式
  */
 typedef enum {
    BTIMER = 0,
    BTIMER_0,
    BTIMER_1,
} BTIM_ID_t;

/**
  * @brief  TIM Time base Configuration Structure definition
  */
typedef struct
{
    FunctionalState MDIS;            /*!< 使能或禁用BTIM定时器  */
                                    
    FunctionalState ChainedMode;    /*!< 定时器1链接到前一个定时器0，将2个16bit BTimer合并为1个32bit BTimer */
                                    
    FunctionalState FreezingMode;    /*!< 允许在设备进入待机模式时停止计时器  */

} BTIM_Base_InitTypeDef;

/* Function Prototype --------------------------------------------------------*/

void        LHL_BTIM_Base_Init(BTIM_TypeDef *pBTIMx, BTIM_Base_InitTypeDef* BTIM_Init);

void        LHL_BTIM_Start(BTIM_ID_t BTIMER_x, uint16_t TIMER0_Period, uint16_t TIMER1_Period);

void        LHL_BTIM_Stop(BTIM_ID_t BTIMER_x);

void        LHL_BTIM_ITConfig(BTIM_ID_t BTIMER_x, FunctionalState NewState);

ITStatus    LHL_BTIM_GetPending(BTIM_ID_t BTIMER_x);

void        LHL_BTIM_ClearPending(BTIM_ID_t BTIMER_x);

uint32_t    LHL_BTIM_GetCycle(void);

void        LHL_BTIM_SetPeriod(BTIM_ID_t BTIMER_x, uint16_t Period);

//uint16_t  LHL_BTIM_GetCounter (btim_id_t BTIMER_x);

#ifdef __cplusplus
}
#endif

#endif 

/*********************************End of File**********************************/
