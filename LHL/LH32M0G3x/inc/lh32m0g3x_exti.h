/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_exti.h
 * @version 2025-09-01
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_EXTI_H
#define __LH32M0G3x_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Public Definition ---------------------------------------------------------*/

typedef enum {
    EXTI_LINE_0     = 0x0001u,  /*!< External interrupt line 0 */
    EXTI_LINE_1     = 0x0002u,  /*!< External interrupt line 1 */
    EXTI_LINE_2     = 0x0004u,  /*!< External interrupt line 2 */
    EXTI_LINE_3     = 0x0008u,  /*!< External interrupt line 3 */
    EXTI_LINE_4     = 0x0010u,  /*!< External interrupt line 4 */
    EXTI_LINE_5     = 0x0020u,  /*!< External interrupt line 5 */
    EXTI_LINE_6     = 0x0040u,  /*!< External interrupt line 6 */
    EXTI_LINE_7     = 0x0080u,  /*!< External interrupt line 7 */
    EXTI_LINE_8     = 0x0100u,  /*!< External interrupt line 8 PVD（电压低于阈值标记）输出 */
    EXTI_LINE_9     = 0x0200u,  /*!< External interrupt line 9 RTC闹钟事件 */
    EXTI_LINE_10    = 0x0400u,  /*!< External interrupt line 10 LPTIMER1触发事件输出 */
    EXTI_LINE_11    = 0x0800u,  /*!< External interrupt line 11 LPTIMER2触发事件输出 */
    EXTI_LINE_12    = 0x1000u,  /*!< External interrupt line 12 ADC0的错误、数据就绪输出或ADC1的错误、数据就绪输出 */
    EXTI_LINE_13    = 0x2000u,  /*!< External interrupt line 13 DMA所有通道中断的或 */   
} EXTI_LINE_t;

typedef enum {
  EXTI_MODE_INTERRUPT           = 0x00u,
  EXTI_MODE_EVENT               = 0x04u,
} EXTI_Mode_t;

typedef enum {
  EXTI_TRIGGER_RISING           = 0x08u,
  EXTI_TRIGGER_FALLING          = 0x0Cu,  
  EXTI_TRIGGER_RISING_FALLING   = 0x10u,
} EXTI_TRIGGER_t;

/** 
  * @brief  EXTI Init Structure definition  
  */
typedef struct {

    EXTI_LINE_t     Line;           /*!< 待设定的外部中断线EXTI_LINE_x（x：0~13）*/
   
    EXTI_Mode_t     Mode;           /*!< 外部中断线EXTI模式 */

    EXTI_TRIGGER_t  Trigger;        /*!< 外部中断线EXTI触发沿 */

    FunctionalState LineCmd;        /*!< 外部中断线EXTI使能 */ 
    
    uint8_t         Reserved;
    
} EXTI_InitTypeDef;                                       

/* Function Prototype --------------------------------------------------------*/

void                LHL_EXTI_DeInit(void);

void                LHL_EXTI_Init(EXTI_InitTypeDef* EXTI_Init);

void                LHL_EXTI_GenerateSWI(EXTI_LINE_t EXTI_LINE_x);

ITStatus            LHL_EXTI_GetPending(EXTI_LINE_t EXTI_LINE_x);

void                LHL_EXTI_ClearPending(EXTI_LINE_t EXTI_LINE_x);

#ifdef __cplusplus
}
#endif

#endif 

/*********************************End of File**********************************/
