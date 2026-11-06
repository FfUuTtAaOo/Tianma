/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_crc32.h
 * @version 2025-09-22
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_CRC_H
#define __LH32M0G3x_CRC_H

#ifdef __cplusplus
extern "C" {
#endif
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Public Definition ---------------------------------------------------------*/
#define LHL_CRC8_POLYNOMIAL     0x07u       // 常用多项式CRC-8: x^8 + x^2 + x + 1
#define LHL_CRC16_POLYNOMIAL    0x1021u     // 常用多项式CRC-16: x^16 + x^12 + x^5 + 1
#define LHL_CRC32_POLYNOMIAL    0x04C11DB7u // CRC-32/MPEG-22

/* Function Prototype --------------------------------------------------------*/
uint8_t LHL_CRC8_Calculate(uint8_t *pData, uint16_t Size);

uint32_t LHL_CRC32_Calculate(uint32_t *pData, uint16_t Size);

uint16_t LHL_CRC16_Calculate(uint8_t *pData, uint16_t Size);

#ifdef __cplusplus
}
#endif

#endif 

/*********************************End of File**********************************/
