/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_btim.c
 * @version    2025-09-29
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  初始化BTIM外设
  * @param  pBTIMx      x取值0或1
  *         BTIM_Init   BTIM_Base_InitTypeDef格式的参数指针
  * @retval None
  */
void LHL_BTIM_Base_Init(BTIM_TypeDef *pBTIMx, BTIM_Base_InitTypeDef*  BTIM_Init)
{
    RCC_AHBPeriphClockCmd(RCC_AHBENR_BTIMEN_Msk,ENABLE);
    
    // 启用或禁用BTIMER
    if (BTIM_Init->MDIS == ENABLE)
    {
        pBTIMx->MCR &= ~BTIM_MCR_MDIS_Msk;
    }
    else
    {
        pBTIMx->MCR |= BTIM_MCR_MDIS_Msk;
    }
    
    // 是否允许在设备进入待机模式时停止计时器
    if (BTIM_Init->FreezingMode == ENABLE)
    {
        pBTIMx->MCR &= ~BTIM_MCR_FRZ_Msk;
    }
    else
    {
        pBTIMx->MCR |= BTIM_MCR_FRZ_Msk;
    }
    
    // 是否启用链式模式，注意只能是TIMER1链接到TIMER0
    if (BTIM_Init->ChainedMode == ENABLE)
    {
        pBTIMx->TCTRL_1 |= BTIM_TCTRL_CHN_Msk;
    }
    else
    {
        pBTIMx->TCTRL_1 &= ~BTIM_TCTRL_CHN_Msk;
    }
}

/**
  * @brief  启动 BTIM 
  * @param  BTIMER_x：BTIMER_0, BTIMER_1或者BTIMER（链式模式）
  *         TIMER0_Period: TIMER0的周期设定
  *         TIMER1_Period: TIMER1的周期设定
  * @retval None
  */
void LHL_BTIM_Start(BTIM_ID_t BTIMER_x, uint16_t TIMER0_Period, uint16_t TIMER1_Period)
{
    switch(BTIMER_x)
    {
        case BTIMER_0:
            // 16bit基础定时器0
            pBTIM->LDVAL_0 = TIMER0_Period;
            pBTIM->TCTRL_0 |= BTIM_TCTRL_TEN_Msk;
            break;
            
        case BTIMER_1:
            // 16bit基础定时器1
            pBTIM->LDVAL_1 = TIMER1_Period;
            pBTIM->TCTRL_1 |= BTIM_TCTRL_TEN_Msk;
            break;
        case BTIMER:
            // 32bit链式模式
            pBTIM->LDVAL_0 = TIMER0_Period;
            pBTIM->LDVAL_1 = TIMER1_Period;
            pBTIM->TCTRL_0 |= BTIM_TCTRL_TEN_Msk;
            pBTIM->TCTRL_1 |= BTIM_TCTRL_TEN_Msk;
            break;
    }
}

/**
  * @brief  启动 BTIM 
  * @param  BTIMER_x：BTIMER_0, BTIMER_1或者BTIMER（链式模式）
  *         TIMER0_Period: TIMER0的周期设定
  *         TIMER1_Period: TIMER1的周期设定
  * @retval None
  */
void LHL_BTIM_SetPeriod(BTIM_ID_t BTIMER_x, uint16_t Period)
{
    switch(BTIMER_x)
    {
        case BTIMER_0:
            pBTIM->LDVAL_0 = Period;
            break;            
        case BTIMER_1:
            pBTIM->LDVAL_1 = Period;
            break;
        case BTIMER:
            pBTIM->LDVAL_0 = Period;
            pBTIM->LDVAL_1 = Period;
            break;
    }
}

/**
  * @brief  停止 BTIM 
  * @param  BTIMER_x：BTIMER_0, BTIMER_1或者BTIMER（链式模式）
  * @retval None
  */
void LHL_BTIM_Stop(BTIM_ID_t BTIMER_x)
{
    switch(BTIMER_x)
    {
        case BTIMER_0:
            // 16bit基础定时器0
            pBTIM->TCTRL_0 &= ~BTIM_TCTRL_TEN_Msk;
            break;            
        case BTIMER_1:
            // 16bit基础定时器1
            pBTIM->TCTRL_1 &= ~BTIM_TCTRL_TEN_Msk;
            break;
        case BTIMER:
            // 32bit链式模式
            pBTIM->TCTRL_0 &= ~BTIM_TCTRL_TEN_Msk;
            pBTIM->TCTRL_1 %= ~BTIM_TCTRL_TEN_Msk;
            break;
    }
}

/**
  * @brief  获取 BTIM 中断标志
  * @param  BTIMER_x：BTIMER_0, BTIMER_1或者BTIMER（链式模式）
  * @retval None
  */
ITStatus LHL_BTIM_GetPending(BTIM_ID_t BTIMER_x)
{
    if (BTIMER_x == BTIMER_1)
    {
        return (ITStatus)(pBTIM->TFLG_1 & BTIM_TFLG_1_TIF_Msk);
    }
    else
    {
        return (ITStatus)(pBTIM->TFLG_0 & BTIM_TFLG_0_TIF_Msk);
    }
}


/**
  * @brief  设定 BTIM 中断功能
  * @param  BTIMER_x：BTIMER_0, BTIMER_1或者BTIMER（链式模式）
  *         NewState: ENABLE 或 DISABLE
  * @retval None
  */
void LHL_BTIM_ITConfig(BTIM_ID_t BTIMER_x, FunctionalState NewState)
{    
    switch(BTIMER_x)
    {
        case BTIMER_0:
            // 16bit基础定时器0
            if (NewState == ENABLE)
            {
                LHL_BTIM_ClearPending(BTIMER_0);            // 清除相关的TFLGn[TIF]
                pBTIM->TCTRL_0 |= BTIM_TCTRL_TIE_Msk;
            }
            else
            {
                pBTIM->TCTRL_0 &= ~BTIM_TCTRL_TIE_Msk;
            }
            break;
            
        case BTIMER_1:
            // 16bit基础定时器1
            if (NewState == ENABLE)
            {
                LHL_BTIM_ClearPending(BTIMER_1);
                pBTIM->TCTRL_1 |= BTIM_TCTRL_TIE_Msk;
            }
            else
            {
                pBTIM->TCTRL_1 &= ~BTIM_TCTRL_TIE_Msk;
            }
            break;
        case BTIMER:    
            // 32bit链式模式下，仅开启BTIM1中断，关闭BTIM0中断
            if (NewState == ENABLE)
            {
                LHL_BTIM_ClearPending(BTIMER);
                pBTIM->TCTRL_0 &= ~BTIM_TCTRL_TIE_Msk;
                pBTIM->TCTRL_1 |= BTIM_TCTRL_TIE_Msk;
            }
            else
            {
                pBTIM->TCTRL_0 &= ~BTIM_TCTRL_TIE_Msk;
                pBTIM->TCTRL_1 &= ~BTIM_TCTRL_TIE_Msk;
            }
            break;
    }
}

/**
  * @brief  清除 BTIM 中断标志
  * @param  BTIMER_x：BTIMER_0, BTIMER_1或者BTIMER（链式模式）
  * @retval None
  */
void LHL_BTIM_ClearPending(BTIM_ID_t BTIMER_x)
{
    switch(BTIMER_x)
    {
        case BTIMER_0:
            // 16bit基础定时器0
            pBTIM->TFLG_0 |= BTIM_TFLG_TIF_Msk;
            break;
            
        case BTIMER_1:
            // 16bit基础定时器1
            pBTIM->TFLG_1 |= BTIM_TFLG_TIF_Msk;
            break;
            
        case BTIMER:
            // 32bit链式模式
            pBTIM->TFLG_0 |= BTIM_TFLG_TIF_Msk;
            pBTIM->TFLG_1 |= BTIM_TFLG_TIF_Msk;
            break;
    }
}

/**
  * @brief  仅适用于32bit链式模式下的精确计时
  * @param  None
  * @retval 以HCLK为单位的Cycle数量
  */
/* */
uint32_t LHL_BTIM_GetCycle(void)
{
    uint32_t high1, low, high2;
    
    // 第一次读取：先高16位，后低16位
    high1 = pBTIM->CVAL_1;
    low = pBTIM->CVAL_0;

    // 第二次读取：
    high2 = pBTIM->CVAL_1;
    
    if (high1 == high2)
    {
        // 如果两次读取高位结果相同，说明没有发生进位
        return ((0xFFFF - high1) << 16) | (0xFFFF - low);
    }
    else
    {
        if (low & 0x8000)
        {
            // 如果低位数字较大，说明读取low之前发生的进位
            return ((0xFFFF - high2) << 16) | (0xFFFF - low);
        }
        else
        {
            // 如果低位数字较小，说明读取low之后发生的进位
            return ((0xFFFF - high1) << 16) | (0xFFFF - low);
        }
    }
}

/*********************************End of File**********************************/
