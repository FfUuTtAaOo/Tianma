/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_xlink.c
 * @version 2025-09-15
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  设置XLINK的输入（触发源）和输出（需要硬件触发的目标外设）
  * @param  XLink_Init  结构体参数指针
  * @retval None
  */
void LHL_XLINK_Init(XLINK_InitTypeDef* XLink_Init)
{
    uint32_t tmp, pos;
    
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_CORSSBAREN_Msk, ENABLE);

    // 设定Cross Link 0 Input & Output
    tmp = (uint32_t)CROSSLINK_BASE;
    tmp += (XLink_Init->XLink_0_Output & 0x0F);
    
    pos = ((XLink_Init->XLink_0_Output >> 8) & 0xFF);
    
    *(__IO uint32_t *)tmp &= ~(0x1Fu << pos);
    *(__IO uint32_t *)tmp |= ((uint32_t)XLink_Init->XLink_0_Input << pos);
    
}

/**
  * @brief  使用XLINK的Logic Union模块将输入信号取反
  * @param  Input  输入信号
  * @param  Output 输出反相信号
  * @retval None
  */
void LHL_XLINK_InvertSingal(XLINK1_INPUT_SOURCE_t Input, XLINK1_LU_OUT_t Output)
{
    uint32_t tmp;
    
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_CORSSBAREN_Msk, ENABLE);

    // 设定Cross Link 1 Input & Output
    tmp = (uint32_t)CROSSLINK_BASE;
    tmp += Output;
    
    *(__IO uint32_t *)tmp = (uint32_t)Input;
    
    tmp += 0x08u;    
    *(__IO uint32_t *)tmp = 0xFEu;
}


/*********************************End of File**********************************/
