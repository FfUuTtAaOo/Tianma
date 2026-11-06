/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0XX_LHL_H_
#define __LH32M0XX_LHL_H_

/* Define to select the right Package and Pinout -----------------------------*/
//#define QFN48_PKG
#define QFN40_PKG                       /* !!! 需根据设计选择合适封装 */
//#define QFN32_PKG

/* Define to select LH Libraries of Peripheral Drivers------------------------*/
#define USE_LHL_DRIVERS

#define LHL_UART_PRINTF pUART0          /* !!! 启用此定义则调用lhl.c的printf实现 */

/* Select Clocks--------------------------------------------------------------*/
#define SYS_VALUE ((uint32_t)16000000)  /* 上电启动时默认SYSCLK时钟频率Hz */
#define HSI_VALUE ((uint32_t)32000000)  /* 内部HSI时钟频率Hz */
#define LSI_VALUE ((uint32_t)32000)     /* 内部LSI时钟频率Hz */
#define LSE_VALUE ((uint32_t)32768)     /* 外部LSE时钟频率Hz */

#define HSE_VALUE ((uint32_t)32000000)  /* !!! 需根据设计更改外部HSE时钟频率Hz */

// select others

/* Includes-------------------------------------------------------------------*/
#include "lh32m0g3x_lhl_config.h"

/* 全局变量声明区---------------------------------------------------------------*/

#endif

/*********************************End of File**********************************/
