/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_xlink.h
 * @version 2025-09-15
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_XLINK_H
#define __LH32M0G3x_XLINK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Defines -------------------------------------------------------------------*/
typedef enum
{
    XLINK0_INPUT_VSS                    = 0x00u,    /*!< Cross Link 0 输入源 */
    XLINK0_INPUT_VDD,
    XLINK0_INPUT_XB_IN0,
    XLINK0_INPUT_XB_IN1,
    XLINK0_INPUT_XB_IN2,
    XLINK0_INPUT_XB_IN3,
    XLINK0_INPUT_TIM1_TRGO,
    XLINK0_INPUT_TIM1_INT,
    XLINK0_INPUT_TIM2_TRGO,
    XLINK0_INPUT_TIM2_INT,
    XLINK0_INPUT_ADC0_CNV_DONE,
    XLINK0_INPUT_ADC1_CNV_DONE,
    XLINK0_INPUT_LPTIM1_INT             = 0x10u,    
    XLINK0_INPUT_LPTIM2_INT,
    XLINK0_INPUT_BTIM1_TRIGGER,
    XLINK0_INPUT_BTIM2_TRIGGER,
    XLINK0_INPUT_RTC_ALARM,
    XLINK0_INPUT_FAULT,
    XLINK0_INPUT_SOFT_SYNC,
    XLINK0_INPUT_PMU,
    XLINK0_INPUT_ADC_SYNC,
    XLINK0_INPUT_LU_OUT0                = 0x19u,
    XLINK0_INPUT_LU_OUT1,  
} XLINK0_INPUT_SOURCE_t;

typedef enum
{
    XLINK1_OUTPUT_LU_OUT0               = 0x18u,
    XLINK1_OUTPUT_LU_OUT1               = 0x1Cu,  
} XLINK1_LU_OUT_t;

typedef enum
{
    XLINK1_INPUT_TIM1_TRGO              = 0x00u,    /*!< Cross Link 1 输入源 */
    XLINK1_INPUT_TIM1_INT,
    XLINK1_INPUT_TIM2_TRGO,
    XLINK1_INPUT_TIM2_INT,
    XLINK1_INPUT_ADC0_CNV_DONE,
    XLINK1_INPUT_ADC1_CNV_DONE,
    XLINK1_INPUT_XB_IN0,
    XLINK1_INPUT_XB_IN1,
    XLINK1_INPUT_XB_IN2,
    XLINK1_INPUT_XB_IN3,
    XLINK1_INPUT_LPTIM1_INT             = 0x0Eu,
    XLINK1_INPUT_LPTIM2_INT,
    XLINK1_INPUT_BTIM1_TRIGGER,
    XLINK1_INPUT_BTIM2_TRIGGER,
    XLINK1_INPUT_RTC_ALARM,
    XLINK1_INPUT_FAULT,
    XLINK1_INPUT_SOFT_SYNC,
    XLINK1_INPUT_PMU,
    XLINK1_INPUT_ADC_SYNC,    
} XLINK1_INPUT_SOURCE_t;

typedef enum
{
    XLINK0_OUTPUT_ED0               = 0x0000U,    /*!< Cross Link 0 输出端口，低8位寄存器偏移地址，高8位位偏移地址 */
    XLINK0_OUTPUT_ED1               = 0x0800U,
    XLINK0_OUTPUT_ED2               = 0x1000U,
    XLINK0_OUTPUT_ED3               = 0x1800U,
    XLINK0_OUTPUT_XB_OUT0           = 0x0004U,
    XLINK0_OUTPUT_XB_OUT1           = 0x0804U,
    XLINK0_OUTPUT_XB_OUT2           = 0x1004U,
    XLINK0_OUTPUT_XB_OUT3           = 0x1804U,
    XLINK0_OUTPUT_ADC0_TRIG         = 0x0008U,
    XLINK0_OUTPUT_ADC1_TRIG         = 0x0808U,
    XLINK0_OUTPUT_DAC_SYNC          = 0x1008U,
    XLINK0_OUTPUT_TIM1_ITR0         = 0x1808U,
    XLINK0_OUTPUT_TIM2_ITR0         = 0x000CU,
    XLINK0_OUTPUT_MIO_TRIGGER_IN0   = 0x080CU,
    XLINK0_OUTPUT_MIO_TRIGGER_IN1   = 0x100CU,
    XLINK0_OUTPUT_LPTIM1_CL         = 0x180CU,
    XLINK0_OUTPUT_LPTIM2_CL         = 0x0010U,     
} XLINK0_OUTPUT_PORT_t;

/**
  * @brief  Cross Link Initialization Structure definition
  */
typedef struct
{
    XLINK0_INPUT_SOURCE_t           XLink_0_Input;      /*!< Specifies the Cross Link 0 Input Source*/
    
    XLINK1_INPUT_SOURCE_t           XLink_1_Input;      /* Reserved */

    XLINK0_OUTPUT_PORT_t            XLink_0_Output;     /*!< Specifies the Cross Link 0 Output (Trigger for Example) */  
    
    uint32_t                        Logic_Unit;         /* Reserved */
    
    uint32_t                        Edge_Detection;     /* Reserved */    
    
} XLINK_InitTypeDef;

/* Declaration ---------------------------------------------------------------*/
void LHL_XLINK_Init(XLINK_InitTypeDef* XLink_Init);
void LHL_XLINK_InvertSingal(XLINK1_INPUT_SOURCE_t Input, XLINK1_LU_OUT_t Output);

#ifdef __cplusplus
}
#endif

#endif 

/*********************************End of File**********************************/
