/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0XX_LHL_H
#define __LH32M0XX_LHL_H

/******************************************************************************
  *
  * @brief                  LH32M0xx LHL驱动库配置                             *
  *
  *****************************************************************************/
/* Define to use LHL Peripheral Drivers --------------------------------------*/
#define USE_LHL_DRIVERS                 /* 使用LHL驱动库                       */

#define LHL_UART_PRINTF pUART0          /* !!! 启用此定义则调用lhl.c的printf实现 */

/* Select the right Package and Pinout ---------------------------------------*/
//#define QFN48_PKG
//#define QFN32_PKG
#define QFN40_PKG                       /* !!! 根据设计选择合适封装              */

/* Select Clocks--------------------------------------------------------------*/
#define LSE_VALUE ((uint32_t)32768)     /* LSE 默认频率32.768kHz               */

#define HSE_VALUE ((uint32_t)32000000)  /* !!! HSE 根据设计设定外部高速时钟频率Hz */

/* Select Others -------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
/* @Note: MUST be placed here, at the end of configuration of LHL ------------*/
#include "lh32m0g3x_lhl_config.h"

/***************************LH32M0xx LHL驱动库配置结束***************************/


/*******************************以下为用户可用区域*******************************/

/* Global variable declaration------------------------------------------------*/
#define I2C_SLAVE_ADDRESS   0x30
#define MAX_SIZE            8

extern I2C_HandleTypeDef hI2C;
extern DMA_HandleTypeDef hDMA0;
extern uint8_t SPI_TX_Buffer[MAX_SIZE];
extern uint8_t SPI_RX_Buffer[MAX_SIZE];
extern bool bCommFlag;

extern __RW uint8_t counter, flag, index;
#endif

/*********************************End of File**********************************/
