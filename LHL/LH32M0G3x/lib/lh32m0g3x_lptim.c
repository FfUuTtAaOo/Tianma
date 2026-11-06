/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_lptim.c
 * @version 2025-09-08
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  复位LPTIM寄存器为默认值并关闭LPTIM时钟
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2  
  * @retval None
  */
void LHL_LPTIM_DeInit(LPTIM_TypeDef* pLPTIMx)
{    
    // Restore all LPTIM registers to default values
    pLPTIMx->CSR = 0x00;
    pLPTIMx->PSR = 0x00;
    pLPTIMx->CMR = 0x00;
    pLPTIMx->CNR = 0x00;
    pLPTIMx->ARR = 0x00;
    
    // DISABLE LPTIMER Clock
    if (pLPTIMx == pLPTIM1)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1ENR_LPT1EN_Msk, DISABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(RCC_APB1ENR_LPT2EN_Msk, DISABLE);
    }  
}

/**
  * @brief  对LPTIM的定时器基本配置进行初始化，参数从LPTIM_Init种获取
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2
  *         LPTIM_Init：LPTIM_InitTypeDef定义的结构体参数  
  * @retval None
  */
void LHL_LPTIM_Init (LPTIM_TypeDef* pLPTIMx, LPTIM_InitTypeDef* LPTIM_Init) 
{    
    // Enable LPTIMER Clock
    if (pLPTIMx == pLPTIM1)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1ENR_LPT1EN_Msk, ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(RCC_APB1ENR_LPT2EN_Msk, ENABLE);
    }    
    
    // 配置前禁用LPTIMER
    pLPTIMx->CSR &= ~LPTIM_CSR_TEN_Msk;
    
    // 设置模式
    if (LPTIM_Init->Mode == LPTIM_MODE_TIMER_COUNTER)
    {
        pLPTIMx->CSR &= ~LPTIM_CSR_TMS_Msk;
    }
    else
    {
        pLPTIMx->CSR |= LPTIM_CSR_TMS_Msk;
    }
    
    // 设置自由运行模式
    if (LPTIM_Init->FreeRunning == DISABLE)
    {
        pLPTIMx->CSR &= ~LPTIM_CSR_TFC_Msk;
    }
    else
    {
        pLPTIMx->CSR |= LPTIM_CSR_TFC_Msk;
    }
    
    // 设置Clock Source和Prescaler以及Bypass
    pLPTIMx->PSR &= ~(LPTIM_PSR_PCS_Msk | LPTIM_PSR_PRESCALE_Msk | LPTIM_PSR_PBYP_Msk);
    
    pLPTIMx->PSR |= (((uint32_t)LPTIM_Init->Clock << LPTIM_PSR_PCS_Pos) | \
                    ((uint32_t)(LPTIM_Init->Prescaler & 0x0F) << LPTIM_PSR_PRESCALE_Pos)) | \
                    ((uint32_t)(LPTIM_Init->Prescaler & 0x10) >> 2);
}

/**
  * @brief  启用LPTIM的定时器中断
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2
  *         NewState：ENABLE 或 DISABLE  
  * @retval None
  */
void LHL_LPTIM_ITConfig(LPTIM_TypeDef* pLPTIMx, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        pLPTIMx->CSR |= LPTIM_CSR_TCF_Msk;
        pLPTIMx->CSR |= LPTIM_CSR_TIE_Msk;
    }
    else
    {
        pLPTIMx->CSR |= LPTIM_CSR_TCF_Msk;
        pLPTIMx->CSR &= ~LPTIM_CSR_TIE_Msk;
    }
}

/**
  * @brief  清除LPTIM的定时器比较标志
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2  
  * @retval None
  */
void LHL_LPTIM_ClearPending(LPTIM_TypeDef* pLPTIMx)
{
    pLPTIMx->CSR |= LPTIM_CSR_TCF_Msk;
}

/**
  * @brief  设置LPTIM的比较参数并启定时器
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2  
  *         Period：16bit 周期值
  * @retval None
  */
void LHL_LPTIM_Start(LPTIM_TypeDef* pLPTIMx, uint16_t Period)
{
    // 比较模式下，CMR控制定时周期
    pLPTIMx->CMR = Period;

    /* CNR不能初始化，但可以随时读取
    * pLPTIMx->CNR = 0;
    */
       
    // 启用定时器
    pLPTIMx->CSR |= (LPTIM_CSR_TCF_Msk | LPTIM_CSR_TEN_Msk);
}

/**
  * @brief  关闭LPTIM定时器
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2  
  * @retval None
  */
void LHL_LPTIM_Stop(LPTIM_TypeDef* pLPTIMx)
{    
    // 关闭定时器
    pLPTIMx->CSR &= (~LPTIM_CSR_TEN_Msk);
}

/**
  * @brief  重置LPTIM定时器
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2  
  * @retval None
  */
void LHL_LPTIM_Reset(LPTIM_TypeDef* pLPTIMx)
{    
    // 关闭定时器 
    pLPTIMx->CSR &= (~LPTIM_CSR_TEN_Msk);
    
    // 开启定时器
    pLPTIMx->CSR |= LPTIM_CSR_TEN_Msk;
}

/**
  * @brief  设置LPTIM的PWM参数并启用PWM通道输出
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2  
  *         Period：16bit 周期值
  *         Duty: 16bit 占空比（低电平输出）
  * @retval None
  */
void LHL_LPTIM_PWM_Start(LPTIM_TypeDef* pLPTIMx, uint16_t Period, uint16_t Duty)
{
    // CMR控制PWM占空比
    pLPTIMx->CMR = Duty;
    
    // ARR控制PWM频率
    pLPTIMx->ARR = Period;

    /* CNR不能初始化，但可以随时读取
    * pLPTIMx->CNR = 0;
    */    
    
    // 启用定时器PWM输出
    pLPTIMx->CSR |= (LPTIM_CSR_TEN_Msk | LPTIM_CSR_TPWM_Msk | LPTIM_CSR_TCF_Msk);
}


/**
  * @brief  读取LPTIM定时器的实时计数值
  * @note   CNR不能初始化，但可以随时读取。在每次读取CNR时，软件必须首先以任何值写入CNR。
  *         这将CNR的当前值同步并记录到临时寄存器中。临时寄存器的内容在CNR的每个读取上都返回。
  *         在读取CNR时，总线时钟必须至少要比LPTIMER计数器增加的速率要快两倍，否则可能会返回错误的数据。
  * @param  pLPTIMx：pLPTIM1 或 pLPTIM2  
  * @retval None
  */
uint16_t LHL_LPTIM_GetCounter(LPTIM_TypeDef* pLPTIMx)
{
    pLPTIMx->CNR = 0x00;
    return (uint16_t)pLPTIMx->CNR;
}

/*********************************End of File**********************************/
