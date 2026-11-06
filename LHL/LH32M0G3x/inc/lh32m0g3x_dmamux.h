/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_dmamux.h
 * @version 2025-09-28
 ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_DMAMUX_H
#define __LH32M0G3x_DMAMUX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"


/* Public Definition ---------------------------------------------------------*/
#define DMAMUX_CHCFG_SOURCE_Msk     (0x3FU)
#define DMAMUX_CHCFG_SOURCE_Pos     (0U)
#define DMAMUX_CHCFG_TRIG_Pos       (6U)
#define DMAMUX_CHCFG_ENBL_Pos       (7U)

typedef enum {
    REQUEST_SOURCE_NONE         =   0u,
    REQUEST_SOURCE_TIM1_CH1     =   1u,
    REQUEST_SOURCE_TIM1_CH2     =   2u,
    REQUEST_SOURCE_LPTIM2       =   7u,
    REQUEST_SOURCE_LPTIM1       =   8u,
    REQUEST_SOURCE_TIM2_CH1     =   9u,
    REQUEST_SOURCE_TIM2_CH2     =   10u,
    REQUEST_SOURCE_TIM2_UP      =   13u,
    REQUEST_SOURCE_SPI0_TX      =   14u,
    REQUEST_SOURCE_SPI0_RX      =   15u,   
    REQUEST_SOURCE_SPI1_TX      =   16u,
    REQUEST_SOURCE_SPI1_RX      =   17u,
    REQUEST_SOURCE_I2C0_TX      =   18u,
    REQUEST_SOURCE_I2C0_RX      =   19u,
    REQUEST_SOURCE_UART0_TX     =   20u,
    REQUEST_SOURCE_UART0_RX     =   21u,      
    REQUEST_SOURCE_UART1_TX     =   22u,
    REQUEST_SOURCE_UART1_RX     =   23u,
    REQUEST_SOURCE_FLASH        =   24u,
    REQUEST_SOURCE_ADC0         =   25u,
    REQUEST_SOURCE_ADC1         =   26u,
    REQUEST_SOURCE_XLINK_OUT0   =   27u,  
    REQUEST_SOURCE_XLINK_OUT1   =   28u,  
    REQUEST_SOURCE_XLINK_OUT2   =   29u,  
    REQUEST_SOURCE_XLINK_OUT3   =   30u,  
    REQUEST_SOURCE_ALWAYS_ON_31 =   31u,
    REQUEST_SOURCE_ALWAYS_ON_32 =   32u,     
} DMAMUX_REQ_SRC_t;

typedef struct {

    DMAMUX_REQ_SRC_t Request_Source;            /*<! DMAUX请求源 */
    
    DMA_CHANNEL_t DMA_Channel;                  /*<! 路由至DMA通道 */
    
    FunctionalState Periodic_Trigger;           /*<! 是否周期性触发 */
    
    FunctionalState Cmd;                        /*<! 是否使能此DMAMUX请求 */
    
} DMAMUX_InitTypeDef;

/* Function Prototype --------------------------------------------------------*/

LHL_StatusTypeDef   LHL_DMAMUX_Init(DMAMUX_InitTypeDef* DMAMUX_Init);

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
