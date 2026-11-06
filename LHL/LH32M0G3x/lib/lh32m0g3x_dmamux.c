/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_dmamux.c
 * @version 2025-09-29
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  初始化DMAMUX的通用参数
  * @param  handle      指向包含DMAMUX配置参数的结构体指针 
  * @retval LHL_OK：DMAMUX配置成功
  */
LHL_StatusTypeDef LHL_DMAMUX_Init(DMAMUX_InitTypeDef* DMAMUX_Init)
{
    uint8_t reg = 0;
    
    RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN_Msk, ENABLE);

    reg |= (DMAMUX_Init->Cmd << DMAMUX_CHCFG_ENBL_Pos) | \
            (DMAMUX_Init->Periodic_Trigger << DMAMUX_CHCFG_TRIG_Pos) | \
            (DMAMUX_Init->Request_Source << DMAMUX_CHCFG_SOURCE_Pos);
    
    *(__RW uint8_t *)(DMAMUX_BASE + DMAMUX_Init->DMA_Channel) = reg;
    
    return LHL_OK;
}

/*********************************End of File**********************************/
