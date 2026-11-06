/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_crc32.c
 * @version 2025-09-22
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Private define ------------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  使用片上硬件计算CRC32
  * @note   计算结果是前一次CRC计算结果和新计算结果的组合(对整个32位字进行CRC计算，而不是逐字节地计算)
  * @note   在CRC计算期间会暂停CPU的写操作，因此可以对寄存器CRC_DR进行背靠背写入或者连续地写-读操作
  *         参数模型：CRC-32/MPEG-2，输入和输出数据无翻转，初始值0xFFFFFFFF，结果异或值0x00000000
  *         使用CRC-32(以太网)多项式：0x04C11DB7
  *         CRC计算时间为4个AHB时钟周期(HCLK)
  * @param  pData       以Word（32位字长）为单位的源数据
  *         Size        数据数量
  * @retval 计算的CRC32结果
  */
uint32_t LHL_CRC32_Calculate(uint32_t *pData, uint16_t Size)
{
    RCC_AHBPeriphClockCmd(RCC_AHBENR_CRCEN_Msk,ENABLE);
    
    /* 在开始新的 CRC 计算之前，必须将 1 写入 */
    pCRC32->CR |= CRC32_CR_RESET_Msk;
    
    while(Size--)
    {
        pCRC32->DR = *pData++;                          // 初始值：0xFFFFFFFF
    }
    
    return pCRC32->DR;
}

/**
  * @brief  通过软件方式计算CRC8
  * @param  pData       以Byte（8位字长）为单位的源数据
  *         Size        数据数量
  * @note   多项式 0x07，初始值0x00
  * @retval 计算的CRC8结果
  */
uint8_t LHL_CRC8_Calculate(uint8_t *pData, uint16_t Size)
{
    uint8_t crc = 0x00;                                 // 初始值：0x00
    
    for (uint16_t i = 0; i < Size; i++)
    {
        crc ^= pData[i];                                // 与当前数据字节异或
        
        for (uint8_t j = 0; j < 8; j++)                 // 处理每个字节的8位
        {
            if (crc & 0x80)
            {
                crc = (uint8_t)(crc << 1) ^ (uint8_t)LHL_CRC8_POLYNOMIAL;
            }
            else
            {
                crc <<= 1;
            }
        }
    }    
    return crc;
}

/**
  * @brief  通过软件方式计算CRC16
  * @param  pData       以Byte（8位字长）为单位的源数据
  *         Size        数据数量
  * @note   多项式 0x1021，初始值0x0000
  * @retval 计算的CRC16结果
  */
uint16_t LHL_CRC16_Calculate(uint8_t *pData, uint16_t Size)
{
    uint16_t crc = 0x0000;                              // 初始值：0x0000
    
    while (Size--) {
        uint8_t byte = *pData++;
        crc ^= (uint16_t)byte << 8;
        
        // 展开8次循环
        if (crc & 0x8000) crc = (uint16_t)(crc << 1) ^ LHL_CRC16_POLYNOMIAL; else crc <<= 1;
        if (crc & 0x8000) crc = (uint16_t)(crc << 1) ^ LHL_CRC16_POLYNOMIAL; else crc <<= 1;
        if (crc & 0x8000) crc = (uint16_t)(crc << 1) ^ LHL_CRC16_POLYNOMIAL; else crc <<= 1;
        if (crc & 0x8000) crc = (uint16_t)(crc << 1) ^ LHL_CRC16_POLYNOMIAL; else crc <<= 1;
        if (crc & 0x8000) crc = (uint16_t)(crc << 1) ^ LHL_CRC16_POLYNOMIAL; else crc <<= 1;
        if (crc & 0x8000) crc = (uint16_t)(crc << 1) ^ LHL_CRC16_POLYNOMIAL; else crc <<= 1;
        if (crc & 0x8000) crc = (uint16_t)(crc << 1) ^ LHL_CRC16_POLYNOMIAL; else crc <<= 1;
        if (crc & 0x8000) crc = (uint16_t)(crc << 1) ^ LHL_CRC16_POLYNOMIAL; else crc <<= 1;
    }
    
    return crc;
}

/*********************************End of File**********************************/
