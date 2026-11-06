/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_dac.c
 * @version 2025-09-22
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  初始化DAC
  * @param  DAC_Init    指向包含DAC配置参数的结构体指针 
  * @retval LHL_OK：DAC配置成功
  */
LHL_StatusTypeDef LHL_DAC_Init(DAC_InitTypeDef *DAC_Init)
{    
    /* 开启AFE时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFEEN_Msk, ENABLE);
    
    /* 开启DAC时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_DACEN_Msk, ENABLE);
    
    /* 配置前确认关闭DAC */
    pDAC->CTRL &= ~DAC_CTRL_DAC_EN_Msk;
    
    /* 写入DAC CTRL寄存器 */
    if (DAC_Init->Output_Mode != PWM_DIGITAL_OUTPUT)
    {
        DAC_Init->PWM_Drive_Strength = DAC_DRV_STR_WEAKEST; // DAC不是数字输出则无需设置驱动强度
    }
    if (DAC_Init->DAC_Mode != DAC_CURRENT_MODE)
    {
        DAC_Init->LoopN_Div = DISABLE;          // DAC不是电流输出则无需设置LOOPN
    }   
 
    pDAC->CTRL = (uint32_t)((DAC_Init->CLoad_Capability << DAC_CTRL_CLOAD_MODE_Pos) | \
                            (DAC_Init->LoopN_Div << DAC_CTRL_LOOPN_DIV_EN_Pos) | \
                            (DAC_Init->PWM_Drive_Strength << DAC_CTRL_DAC_PWMDIG_DR_Pos) | \
                            (DAC_Init->Filter << DAC_CTRL_DAC_FILTER_EN_Pos) | \
                            (DAC_Init->Trigger << DAC_CTRL_HARD_TRIG_EN_Pos) | \
                            (DAC_Init->Output_Mode << DAC_CTRL_OUT_MODE_Pos) | \
                            (DAC_Init->DAC_Mode << DAC_CTRL_DAC_MODE_Pos) | \
                            (DAC_Init->DAC_Voltage_Range << DAC_CTRL_DAC_RANGE_Pos));

    return LHL_OK;
}
  
/**
  * @brief  通过设置控制寄存器的使能位来激活DAC
  * @param  none
  * @retval none
  */
void LHL_DAC_Start(void)
{
    pDAC->CTRL |= DAC_CTRL_DAC_EN_Msk;
}

/**
  * @brief  通过清除控制寄存器的使能位来停用DAC，保留其他配置位不变
  * @param  none
  * @retval none
  */
void LHL_DAC_Stop(void)
{
    pDAC->CTRL &= ~DAC_CTRL_DAC_EN_Msk;
}

/**
  * @brief  写入DAC Code
  * @param  data: 要写入的DAC转换数据，高16位必须固定为DAC_KEY
  * @retval none
  */
void LHL_DAC_SetData(uint16_t data)
{
    pDAC->DATA = (DAC_KEY | (uint32_t)data);
}

/**
  * @brief  设定DAC电压输出模式时的输出范围
  * @param  range: DAC_VOLTAGE_RANGE_t定义的电压范围
  * @retval none
  */
void LHL_DAC_SetRange(DAC_VOLTAGE_RANGE_t range)
{
    uint32_t tmp;

    tmp = (pDAC->CTRL & ~DAC_CTRL_DAC_RANGE_Msk);
    pDAC->CTRL = (tmp | ((uint32_t)range << DAC_CTRL_DAC_RANGE_Pos));
}

/*********************************End of File**********************************/
