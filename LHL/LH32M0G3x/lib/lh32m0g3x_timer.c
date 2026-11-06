/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_timer.c
 * @version    2025-10-09
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"


/* Private protype ---------------------------------------------------------- */
#define SMCR_ETR_Mask               ((uint16_t)0x00FF) 
#define CCMR_Offset                 ((uint16_t)0x0018)
#define CCER_CCE_Set                ((uint16_t)0x0001)  
#define    CCER_CCNE_Set               ((uint16_t)0x0004) 

static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);


/* Functions -----------------------------------------------------------------*/
/**
  * @brief  复位TIMx定时器到默认值
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @retval None
  */
void LHL_TIM_DeInit(TIM_TypeDef* TIMx)
{
  if (TIMx == pTIM1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_TIM1RST_Msk, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_TIM1RST_Msk, DISABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN_Msk, DISABLE);    
  }     
  else
  {
    RCC_APB1PeriphResetCmd(RCC_APB1RSTR_TIM2RST_Msk, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1RSTR_TIM2RST_Msk, DISABLE);
    
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN_Msk, DISABLE);
  }
}

/**
  * @brief  初始化TIMx定时器
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_InitStruct: 定时器初始化结构体参数
  * @retval None
  */
void LHL_TIM_Init(TIM_TypeDef* TIMx, TIM_InitTypeDef* TIM_InitStruct)
{
    uint32_t tmpcr1 = 0;
  
    if (TIMx == pTIM1)
    {
//        RCC_APB2PeriphResetCmd(RCC_APB2RSTR_TIM1RST_Msk, ENABLE);
//        RCC_APB2PeriphResetCmd(RCC_APB2RSTR_TIM1RST_Msk, DISABLE);    
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN_Msk, ENABLE);    
    }     
    else
    {   
//        RCC_APB1PeriphResetCmd(RCC_APB1RSTR_TIM2RST_Msk, ENABLE);
//        RCC_APB1PeriphResetCmd(RCC_APB1RSTR_TIM2RST_Msk, DISABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN_Msk, ENABLE);
    }

    tmpcr1 = TIMx->CR1;  

    /* 设置计数模式 */
    tmpcr1 &= ~(TIMER_TIMX_CR1_DIR_Msk | TIMER_TIMX_CR1_CMS_Msk);
    tmpcr1 |= TIM_InitStruct->CounterMode;
 
    /* 设置时钟分频因子 */
    tmpcr1 &= ~(TIMER_TIMX_CR1_CKD_Msk);
    tmpcr1 |= TIM_InitStruct->ClockDivision;
    
    /* 设置自动重装载模式 */
    if (TIM_InitStruct->AutoReloadPreload == DISABLE)
    {
        tmpcr1 &= ~TIMER_TIMX_CR1_ARPE_Msk;
    }
    else
    {
        tmpcr1 |= TIMER_TIMX_CR1_ARPE_Msk;
    }
    
    /* 设置UEV中断请求源*/
//    if (TIM_InitStruct->UpdateRequestSource != TIM_URS_OVERFLOW)
//    {
//        tmpcr1 &= ~TIMER_TIMX_CR1_URS_Msk;
//    }
//    else
//    {
//        tmpcr1 |= TIMER_TIMX_CR1_URS_Msk;
//    }
    
    /* ARR包含了将要传送至实际的自动重装载寄存器的数值 */
    TIMx->ARR = TIM_InitStruct->Period ;
 
    /* 预分频器：计数器的时钟频率CK_CNT等于fCK_PSC/(PSC[15:0]+1) */
    TIMx->PSC = TIM_InitStruct->Prescaler; 
    
    TIMx->CR1 = tmpcr1;
    
    /* 初始化完毕，产生软件UG事件，装载所有系数 */
    TIMx->EGR |= TIMER_TIMX_EGR_UG_Msk;
    
    /* Clear All Flags after Update @20251020 */
    TIMx->SR = 0;  
}

/**
  * @brief  运行TIMx定时器
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.
  * @retval None
  */
void LHL_TIM_Start(TIM_TypeDef* TIMx)
{
    TIMx->CR1 |= TIMER_TIMX_CR1_CEN_Msk; 
}

/**
  * @brief  停止TIMx定时器
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.
  * @retval None
  */
void LHL_TIM_Stop(TIM_TypeDef* TIMx)
{  
    TIMx->CR1 &= (uint16_t)(~((uint16_t)TIMER_TIMX_CR1_CEN_Msk));
}

/**
  * @brief  设置TIMx指定定时器中断
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.
  * @param  TIM_IT: 指定定时器中断:
  *     @arg TIM_IT_Update: TIM update Interrupt source
  *     @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *     @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *     @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void LHL_TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_ITs, FunctionalState NewState)
{    
    if (NewState != DISABLE)
    {
        TIMx->DIER |= TIM_ITs;
    }
    else
    {
        TIMx->DIER &= (uint16_t)~TIM_ITs;
    }
}

/**
  * @brief  检查TIMx中断是否发生
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_IT: 指定定时器中断:
  *     @arg TIM_IT_Update: TIM update Interrupt source
  *     @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *     @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *     @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  * @retval The new state of the TIM_IT(SET or RESET).
  */
ITStatus LHL_TIM_GetPending(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
    ITStatus bitstatus = RESET;  
    uint16_t itstatus, itenable;
   
    itstatus = TIMx->SR & TIM_IT;  
    itenable = TIMx->DIER & TIM_IT;
    
    if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
    {
        bitstatus = SET;    
    }
    else
    {
        bitstatus = RESET;
    }
    
    return bitstatus;
}

/**
  * @brief  清除TIMx指定定时器中断
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_IT: 指定定时器中断:
  *     @arg TIM_IT_Update: TIM1 update Interrupt source
  *     @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *     @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *     @arg TIM_IT_Trigger: TIM Trigger Interrupt source   
  * @retval None
  */
void LHL_TIM_ClearPending(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
    TIMx->SR = (uint16_t)~TIM_IT;
}

/**
  * @brief  检查TIMx指定标志位是否置位
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_FLAG: 定时器指定标志位:
  *     @arg TIM_FLAG_Update: TIM update Flag
  *     @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
  *     @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
  *     @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *     @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
  *     @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag  
  * @retval The new state of TIM_FLAG (SET or RESET).
  */
FlagStatus LHL_TIM_GetFlag(TIM_TypeDef* TIMx, TIM_FLAG_t TIM_FLAG)
{ 
    FlagStatus bitstatus = RESET;  
  
    if ((TIMx->SR & TIM_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @brief  清除TIMx指定定时器标志位
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_FLAG: 指定定时器标志位:
  *     @arg TIM_FLAG_Update: TIM update Flag
  *     @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
  *     @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
  *     @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *     @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
  *     @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
  * @retval None
  */
void LHL_TIM_ClearFlag(TIM_TypeDef* TIMx, TIM_FLAG_t TIM_FLAG)
{  
    TIMx->SR = (uint16_t)~TIM_FLAG;
}


/**
  * @brief  初始化TIMx定时器外设指定通道的Output Compare输出比较功能
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM peripheral.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @retval None
  */
void LHL_TIM_OC_Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct, TIM_CHANNEL_t TIM_CHx)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
    //uint16_t tmpccmr1 = 0;
    
    if (TIM_CHx == TIM_CHANNEL_1)
    {
        /* Disable the Channel 1: Reset the CC1E Bit */
        TIMx->CCER &= (uint16_t)(~(uint16_t)TIMER_TIMX_CCER_CC1E_Msk);
        
        tmpccer = (uint16_t)TIMx->CCER;
        
        tmpcr2 =  (uint16_t)TIMx->CR2;
  
        tmpccmrx = (uint16_t)TIMx->CCMR1;
        
//        tmpccmr1 = (uint16_t)TIMx->CCMR1;
    
        /* Reset the Output Compare Mode Bits */
        tmpccmrx &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCMR1_OP_OC1M_Msk));
        tmpccmrx &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCMR1_OP_CC1S_Msk));
        tmpccmrx &= (uint16_t)~((uint16_t)TIMER_TIMX_CCMR1_OP_OC1PE_Msk);

        /* Select the Output Compare Mode */
        tmpccmrx |= (TIM_OCInitStruct->OCMode | ((uint16_t)TIM_OCInitStruct->OCPreload) << 3);
        
        /* Reset the Output Polarity level */
        tmpccer &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCER_CC1P_Msk));
        
        /* Set the Output Compare Polarity */
        tmpccer |= TIM_OCInitStruct->OCPolarity;
  
        /* Set the Output State */
        tmpccer |= TIM_OCInitStruct->OCPinState;        
    }
    else
    {
        /* Disable the Channel 2: Reset the CC2E Bit */
        TIMx->CCER &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCER_CC2E_Msk));
  
        /* Get the TIMx CCER register value */  
        tmpccer = (uint16_t)TIMx->CCER;
        /* Get the TIMx CR2 register value */
        tmpcr2 =  (uint16_t)TIMx->CR2;
  
        /* Get the TIMx CCMR1 register value */
        tmpccmrx = (uint16_t)TIMx->CCMR1;
    
        /* Reset the Output Compare mode and Capture/Compare selection Bits */
        tmpccmrx &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCMR1_OP_OC2M_Msk));
        tmpccmrx &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCMR1_OP_CC2S_Msk));
        tmpccmrx &= (uint16_t)~((uint16_t)TIMER_TIMX_CCMR1_OP_OC2PE_Msk);

        /* Select the Output Compare Mode */
        tmpccmrx |= (uint16_t)((TIM_OCInitStruct->OCMode << 8) | ((uint16_t)TIM_OCInitStruct->OCPreload) << 11);
  
        /* Reset the Output Polarity level */
        tmpccer &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCER_CC2P_Msk));
        /* Set the Output Compare Polarity */
        tmpccer |= (uint16_t)(TIM_OCInitStruct->OCPolarity << 4);
  
        /* Set the Output State */
        tmpccer |= (uint16_t)(TIM_OCInitStruct->OCPinState << 4);
    }

    /* Write to TIMx CR2 */
    TIMx->CR2 = tmpcr2;
  
    /* Write to TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmrx;

    /* Set the Capture Compare Register value */
    TIMx->CCR1 = TIM_OCInitStruct->Pulse; 
 
    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer;
    
    /* 初始化完毕，产生软件UG事件，装载所有系数 */
    TIMx->EGR |= TIMER_TIMX_EGR_UG_Msk;
    
    /* UEV事件后清除SR @20251020 */
    TIMx->SR = 0;  
}

/**
  * @brief  开启或关闭 TIMx 定时器指定通道的输出比较功能
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @param  NewState: ENABLE or DISABLE
  * @retval None
  */
void LHL_TIM_OC_Cmd(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        if (TIM_CHx == TIM_CHANNEL_1)
        {
            TIMx->CCER |= (uint16_t)TIMER_TIMX_CCER_CC1E_Msk;
        }
        else
        {
            TIMx->CCER |= (uint16_t)TIMER_TIMX_CCER_CC2E_Msk;
        }
    }
    else
    {
        if (TIM_CHx == TIM_CHANNEL_1)
        {
            TIMx->CCER &= (uint16_t)~TIMER_TIMX_CCER_CC1E_Msk;
        }
        else
        {
            TIMx->CCER &= (uint16_t)~TIMER_TIMX_CCER_CC2E_Msk;
        }
    } 
}

/**
  * @brief  关闭TIMx定时器指定通道的输出比较功能
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @param  NewState: ENABLE or DISABLE
  * @retval None
  */
void LHL_TIM_OC_Stop(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx)
{
    TIMx->CR1 &= (uint16_t)(~(uint16_t)TIMER_TIMX_CR1_CEN_Msk);
    
    if (TIM_CHx == TIM_CHANNEL_1)
    {
        TIMx->CCER &= (uint16_t)(~(uint16_t)TIMER_TIMX_CCER_CC1E_Msk);
    }
    else
    {
        TIMx->CCER &= (uint16_t)(~(uint16_t)TIMER_TIMX_CCER_CC2E_Msk);
    }
}

/**
  * @brief  Sets the TIMx Capture Compare1 Register value
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  Compare: specifies the Capture Compare1 register new value.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @retval None
  */
void LHL_TIM_OC_SetCompare(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx, uint16_t Compare)
{
    if (TIM_CHx == TIM_CHANNEL_1)
    {
        /* Set the Capture Compare1 Register value */
        TIMx->CCR1 = Compare;
    }
    else
    {
        /* Set the Capture Compare2 Register value */
        TIMx->CCR2 = Compare;
    }
}

/**
  * @brief  初始化TIMx定时器外设指定通道的PWM输出功能
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_PWMInitStruct: pointer to a TIM_PWMInitTypeDef structure
  *         that contains the configuration information for the specified TIM peripheral.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @retval None
  */
void LHL_TIM_PWM_Init(TIM_TypeDef* TIMx, TIM_PWMInitTypeDef* TIM_PWMInitStruct, TIM_CHANNEL_t TIM_CHx)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
    
    if (TIM_CHx == TIM_CHANNEL_1)
    {
        /* Disable the Channel 1: Reset the CC1E Bit */
        TIMx->CCER &= (uint16_t)(~(uint16_t)TIMER_TIMX_CCER_CC1E_Msk);
        
        tmpccer = (uint16_t)TIMx->CCER;
        
        tmpcr2 =  (uint16_t)TIMx->CR2;
  
        tmpccmrx = (uint16_t)TIMx->CCMR1;
            
        /* Reset the Output PWM Mode Bits */
        tmpccmrx &= 0xFF80;

        /* Select the Output PWM Mode */
        tmpccmrx |= (TIM_PWMInitStruct->PWMMode | \
                ((uint16_t)TIM_PWMInitStruct->PWMPreload << 3) | \
                ((uint16_t)TIM_PWMInitStruct->PWMFastMode << 2));
        
        /* Reset the Output Polarity level */
        tmpccer &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCER_CC1P_Msk));
        
        /* Set the Output PWM Polarity, PWM输出引脚始终使能 */
        tmpccer |= TIM_PWMInitStruct->PWMPolarity | TIMER_TIMX_CCER_CC1E_Msk;   

        /* 设置占空比 */
        TIMx->CCR1 = TIM_PWMInitStruct->Pulse;      
    }
    else
    {
        /* Disable the Channel 2: Reset the CC2E Bit */
        TIMx->CCER &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCER_CC2E_Msk));
  
        /* Get the TIMx CCER register value */  
        tmpccer = (uint16_t)TIMx->CCER;
        /* Get the TIMx CR2 register value */
        tmpcr2 =  (uint16_t)TIMx->CR2;
  
        /* Get the TIMx CCMR1 register value */
        tmpccmrx = (uint16_t)TIMx->CCMR1;
    
        /* Reset the Output Compare mode and Capture/Compare selection Bits */
        tmpccmrx &= 0x80FF;

        /* Select the Output Compare Mode */
        tmpccmrx |= ((uint16_t)((TIM_PWMInitStruct->PWMMode << 8) | \
                    ((uint16_t)TIM_PWMInitStruct->PWMPreload) << 11) | \
                    ((uint16_t)TIM_PWMInitStruct->PWMFastMode) << 10);
  
        /* Reset the Output Polarity level */
        tmpccer &= (uint16_t)(~((uint16_t)TIMER_TIMX_CCER_CC2P_Msk));
        
        /* Set the Output Compare Polarity, PWM输出引脚始终使能 */
        tmpccer |= (uint16_t)(TIM_PWMInitStruct->PWMPolarity << 4)  | TIMER_TIMX_CCER_CC2E_Msk;
        
        /* 设置占空比 */
        TIMx->CCR2 = TIM_PWMInitStruct->Pulse; 
    }

    /* Write to TIMx CR2 */
    TIMx->CR2 = tmpcr2;
  
    /* Write to TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmrx;
 
    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer; 
    
    /* 初始化完毕，产生软件UG事件，装载所有系数 */
    TIMx->EGR |= TIMER_TIMX_EGR_UG_Msk;
    
    /* UEV事件后清除SR @20251020 */
    TIMx->SR = 0; 
}

/**
  * @brief  设置TIMx PWM占空比
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  DutyCyle: PWM占空比（原始值，非百分比）
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @retval None
  */
void LHL_TIM_PWM_SetDutyCycle(TIM_TypeDef* TIMx, uint16_t DutyCyle, TIM_CHANNEL_t TIM_CHx)
{
    if (TIM_CHx == TIM_CHANNEL_1)
    {
        /* Set the Capture Compare1 Register value */
        TIMx->CCR1 = DutyCyle;
    }
    else
    {
        /* Set the Capture Compare2 Register value */
        TIMx->CCR2 = DutyCyle;
    }
}

/**
  * @brief  初始化TIM定时器外设为Input Capture输入捕获模式
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
  *         that contains the configuration information for the specified TIM peripheral.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @retval None
  */
void LHL_TIM_IC_Init(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct, TIM_CHANNEL_t TIM_CHx)
{

  if (TIM_CHx == TIM_CHANNEL_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIMx, TIM_ICInitStruct->ICPolarity, TIM_ICInitStruct->ICSelection, TIM_ICInitStruct->ICFilter);
  }
  else
  {
    /* TI2 Configuration */
    TI2_Config(TIMx, TIM_ICInitStruct->ICPolarity, TIM_ICInitStruct->ICSelection, TIM_ICInitStruct->ICFilter);
  }
    /* Set the Input Capture Prescaler value */
    LHL_TIM_IC_SetPrescaler(TIMx, TIM_ICInitStruct->ICPrescaler, TIM_CHx);
}

/**
  * @brief  使用或禁用TIMx定时器指定通道的输入捕获功能
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @param  NewState: ENABLE or DISABLE
  * @retval None
  */
void LHL_TIM_IC_Cmd(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx, FunctionalState NewState)
{
    //TIMx->CR1 |= TIMER_TIMX_CR1_CEN_Msk;
    
    if (NewState == ENABLE)
    {
        if (TIM_CHx == TIM_CHANNEL_1)
        {
            TIMx->CCER |= (uint16_t)TIMER_TIMX_CCER_CC1E_Msk;
        }
        else
        {
            TIMx->CCER |= (uint16_t)TIMER_TIMX_CCER_CC2E_Msk;
        }
    }
    else
    {
        if (TIM_CHx == TIM_CHANNEL_1)
        {
            TIMx->CCER &= (uint16_t)~TIMER_TIMX_CCER_CC1E_Msk;
        }
        else
        {
            TIMx->CCER &= (uint16_t)~TIMER_TIMX_CCER_CC2E_Msk;
        }
    }
    
    /* Clear all flags? @20251020 */
    //TIMx->SR = 0;   
}

/**
  * @brief  关闭TIMx定时器指定通道的输入捕获功能
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @retval None
  */
void LHL_TIM_IC_Stop(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx)
{
    TIMx->CR1 &= (uint16_t)(~(uint16_t)TIMER_TIMX_CR1_CEN_Msk);

    if (TIM_CHx == TIM_CHANNEL_1)
    {
        TIMx->CCER &= (uint16_t)(~(uint16_t)TIMER_TIMX_CCER_CC1E_Msk);
    }
    else
    {
        TIMx->CCER &= (uint16_t)(~(uint16_t)TIMER_TIMX_CCER_CC2E_Msk);
    }
}

/**
  * @brief  设置TIMx定时器外设指定通道的输入捕获预分频系数
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_ICPSC: specifies the Input Capture1 prescaler new value:
  *     @arg TIM_ICPSC_DIV1: no prescaler
  *     @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *     @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *     @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @param  TIM_CHx：TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @retval None
  */
void LHL_TIM_IC_SetPrescaler(TIM_TypeDef* TIMx, TIM_ICPRESCALER_t TIM_ICPSC, TIM_CHANNEL_t TIM_CHx)
{
    if (TIM_CHx == TIM_CHANNEL_1)
    {
        /* Reset the IC1PSC Bits */
        TIMx->CCMR1 &= (uint16_t)~((uint16_t)TIMER_TIMX_CCMR1_IC_IC1PSC_Msk);
        /* Set the IC1PSC value */
        TIMx->CCMR1 |= TIM_ICPSC;
    }
    else
    {
        /* Reset the IC2PSC Bits */
        TIMx->CCMR1 &= (uint16_t)~((uint16_t)TIMER_TIMX_CCMR1_IC_IC2PSC_Msk);
        /* Set the IC2PSC value */
        TIMx->CCMR1 |= (uint16_t)(TIM_ICPSC << 8);
    }
}

/**
  * @brief  返回TIMx输入捕获计数值
  * @param  TIMx: where x can be 1 to 2  to select the TIM peripheral.
  * @param  TIM_CHx: TIM_CHANNEL_1 or TIM_CHANNEL_2
  * @retval Capture Compare 1 Register value.
  */
uint16_t LHL_TIM_IC_GetCapture(TIM_TypeDef* TIMx, TIM_CHANNEL_t TIM_CHx)
{
    if (TIM_CHx == TIM_CHANNEL_1)
    {
        /* Get the Capture 1 Register value */
        return (uint16_t)TIMx->CCR1;
    }
    else
    {
        /* Get the Capture 2 Register value */
        return (uint16_t)TIMx->CCR2;
    }
}

///**
//  * @brief  Configures the TIM peripheral according to the specified
//  *         parameters in the TIM_ICInitStruct to measure an external PWM signal.
//  * @param  TIMx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TIM peripheral.
//  * @param  TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
//  *         that contains the configuration information for the specified TIM peripheral.
//  * @retval None
//  */
//void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
//{
//  uint16_t icoppositepolarity = TIM_ICPolarity_Rising;
//  uint16_t icoppositeselection = TIM_ICSelection_DirectTI;
//  /* Check the parameters */
//  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
//  /* Select the Opposite Input Polarity */
//  if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
//  {
//    icoppositepolarity = TIM_ICPolarity_Falling;
//  }
//  else
//  {
//    icoppositepolarity = TIM_ICPolarity_Rising;
//  }
//  /* Select the Opposite Input */
//  if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
//  {
//    icoppositeselection = TIM_ICSelection_IndirectTI;
//  }
//  else
//  {
//    icoppositeselection = TIM_ICSelection_DirectTI;
//  }
//  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
//  {
//    /* TI1 Configuration */
//    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
//               TIM_ICInitStruct->TIM_ICFilter);
//    /* Set the Input Capture Prescaler value */
//    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
//    /* TI2 Configuration */
//    TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
//    /* Set the Input Capture Prescaler value */
//    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
//  }
//  else
//  { 
//    /* TI2 Configuration */
//    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
//               TIM_ICInitStruct->TIM_ICFilter);
//    /* Set the Input Capture Prescaler value */
//    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
//    /* TI1 Configuration */
//    TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
//    /* Set the Input Capture Prescaler value */
//    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
//  }
//}

/**
  * @brief  软件生成TIMx event事件
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_EventSource: specifies the event source.
  *   This parameter can be one or more of the following values:       
  *     @arg TIM_EventSource_Update: Timer update Event source
  *     @arg TIM_EventSource_CC1: Timer Capture Compare 1 Event source
  *     @arg TIM_EventSource_CC2: Timer Capture Compare 2 Event source
  *     @arg TIM_EventSource_Trigger: Timer Trigger Event source    
  * @retval None
  */
void LHL_TIM_GenerateEvent(TIM_TypeDef* TIMx, TIM_EVENTSOURCE_t TIM_EventSource)
{   
    /* Set the event sources */
    TIMx->EGR = TIM_EventSource;
}

/**
  * @brief  Configures the TIMx's DMA interface.
  * @param  TIMx: where x can be  1, 2, 3, 4, 5, 8, 15, 16 or 17 to select 
  *   the TIM peripheral.
  * @param  TIM_DMABase: DMA Base address.
  *   This parameter can be one of the following values:
  *     @arg TIM_DMABase_CR, TIM_DMABase_CR2, TIM_DMABase_SMCR,
  *          TIM_DMABase_DIER, TIM1_DMABase_SR, TIM_DMABase_EGR,
  *          TIM_DMABase_CCMR1, TIM_DMABase_CCMR2, TIM_DMABase_CCER,
  *          TIM_DMABase_CNT, TIM_DMABase_PSC, TIM_DMABase_ARR,
  *          TIM_DMABase_RCR, TIM_DMABase_CCR1, TIM_DMABase_CCR2,
  *          TIM_DMABase_CCR3, TIM_DMABase_CCR4, TIM_DMABase_BDTR,
  *          TIM_DMABase_DCR.
  * @param  TIM_DMABurstLength: DMA Burst length.
  *   This parameter can be one value between:
  *   TIM_DMABurstLength_1Transfer and TIM_DMABurstLength_18Transfers.
  * @retval None
  */
void LHL_TIM_DMAConfig(TIM_TypeDef* TIMx, TIM_DMABASE_t TIM_DMABase, TIM_DMABURSTLENGTH_t TIM_DMABurstLength)
{
    /* Set the DMA Base and the DMA Burst Length */
    TIMx->DCR = (uint16_t)TIM_DMABase | (uint16_t)TIM_DMABurstLength;
}

/**
  * @brief  Enables or disables the TIMx's DMA Requests.
  * @param  TIMx: where x can be  1, 2, 3, 4, 5, 6, 7, 8, 15, 16 or 17 
  *   to select the TIM peripheral. 
  * @param  TIM_DMASource: specifies the DMA Request sources.
  *   This parameter can be any combination of the following values:
  *     @arg TIM_DMA_Update: TIM update Interrupt source
  *     @arg TIM_DMA_CC1: TIM Capture Compare 1 DMA source
  *     @arg TIM_DMA_CC2: TIM Capture Compare 2 DMA source
  *     @arg TIM_DMA_Trigger: TIM Trigger DMA source
  * @param  NewState: new state of the DMA Request sources.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState)
{
      if (NewState != DISABLE)
      {
        /* Enable the DMA sources */
        TIMx->DIER |= TIM_DMASource; 
      }
      else
      {
        /* Disable the DMA sources */
        TIMx->DIER &= (uint16_t)~TIM_DMASource;
      }
}

///**
//  * @brief  Configures the TIMx internal Clock
//  * @param  TIMx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15
//  *         to select the TIM peripheral.
//  * @retval None
//  */
//void TIM_InternalClockConfig(TIM_TypeDef* TIMx)
//{
//  /* Check the parameters */
//  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
//  /* Disable slave mode to clock the prescaler directly with the internal clock */
//  TIMx->SMCR &=  (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
//}

///**
//  * @brief  Configures the TIMx Internal Trigger as External Clock
//  * @param  TIMx: where x can be  1, 2, 3, 4, 5, 9, 12 or 15 to select the TIM peripheral.
//  * @param  TIM_ITRSource: Trigger source.
//  *   This parameter can be one of the following values:
//  * @param  TIM_TS_ITR0: Internal Trigger 0
//  * @param  TIM_TS_ITR1: Internal Trigger 1
//  * @param  TIM_TS_ITR2: Internal Trigger 2
//  * @param  TIM_TS_ITR3: Internal Trigger 3
//  * @retval None
//  */
//void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource)
//{
//  /* Check the parameters */
//  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
//  assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));
//  /* Select the Internal Trigger */
//  TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);
//  /* Select the External clock mode1 */
//  TIMx->SMCR |= TIM_SlaveMode_External1;
//}

///**
//  * @brief  Configures the TIMx Trigger as External Clock
//  * @param  TIMx: where x can be  1, 2, 3, 4, 5, 9, 12 or 15 to select the TIM peripheral.
//  * @param  TIM_TIxExternalCLKSource: Trigger source.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
//  *     @arg TIM_TIxExternalCLK1Source_TI1: Filtered Timer Input 1
//  *     @arg TIM_TIxExternalCLK1Source_TI2: Filtered Timer Input 2
//  * @param  TIM_ICPolarity: specifies the TIx Polarity.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ICPolarity_Rising
//  *     @arg TIM_ICPolarity_Falling
//  * @param  ICFilter : specifies the filter value.
//  *   This parameter must be a value between 0x0 and 0xF.
//  * @retval None
//  */
//void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
//                                uint16_t TIM_ICPolarity, uint16_t ICFilter)
//{
//  /* Check the parameters */
//  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
//  assert_param(IS_TIM_TIXCLK_SOURCE(TIM_TIxExternalCLKSource));
//  assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
//  assert_param(IS_TIM_IC_FILTER(ICFilter));
//  /* Configure the Timer Input Clock Source */
//  if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
//  {
//    TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
//  }
//  else
//  {
//    TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
//  }
//  /* Select the Trigger source */
//  TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
//  /* Select the External clock mode1 */
//  TIMx->SMCR |= TIM_SlaveMode_External1;
//}

///**
//  * @brief  Configures the External clock Mode1
//  * @param  TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
//  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
//  *     @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
//  *     @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
//  *     @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
//  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
//  *     @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
//  * @param  ExtTRGFilter: External Trigger Filter.
//  *   This parameter must be a value between 0x00 and 0x0F
//  * @retval None
//  */
//void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
//                             uint16_t ExtTRGFilter)
//{
//  uint16_t tmpsmcr = 0;
//  /* Check the parameters */
//  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
//  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
//  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
//  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
//  /* Configure the ETR Clock source */
//  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
//  
//  /* Get the TIMx SMCR register value */
//  tmpsmcr = TIMx->SMCR;
//  /* Reset the SMS Bits */
//  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
//  /* Select the External clock mode1 */
//  tmpsmcr |= TIM_SlaveMode_External1;
//  /* Select the Trigger selection : ETRF */
//  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_TS));
//  tmpsmcr |= TIM_TS_ETRF;
//  /* Write to TIMx SMCR */
//  TIMx->SMCR = tmpsmcr;
//}

///**
//  * @brief  Configures the External clock Mode2
//  * @param  TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
//  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
//  *     @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
//  *     @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
//  *     @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
//  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
//  *     @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
//  * @param  ExtTRGFilter: External Trigger Filter.
//  *   This parameter must be a value between 0x00 and 0x0F
//  * @retval None
//  */
//void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
//                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
//{
//  /* Check the parameters */
//  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
//  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
//  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
//  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
//  /* Configure the ETR Clock source */
//  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
//  /* Enable the External clock mode2 */
//  TIMx->SMCR |= TIM_SMCR_ECE;
//}

///**
//  * @brief  Configures the TIMx External Trigger (ETR).
//  * @param  TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
//  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
//  *     @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
//  *     @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
//  *     @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
//  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
//  *     @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
//  * @param  ExtTRGFilter: External Trigger Filter.
//  *   This parameter must be a value between 0x00 and 0x0F
//  * @retval None
//  */
//void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
//                   uint16_t ExtTRGFilter)
//{
//  uint16_t tmpsmcr = 0;
//  /* Check the parameters */
//  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
//  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
//  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
//  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
//  tmpsmcr = TIMx->SMCR;
//  /* Reset the ETR Bits */
//  tmpsmcr &= SMCR_ETR_Mask;
//  /* Set the Prescaler, the Filter value and the Polarity */
//  tmpsmcr |= (uint16_t)(TIM_ExtTRGPrescaler | (uint16_t)(TIM_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
//  /* Write to TIMx SMCR */
//  TIMx->SMCR = tmpsmcr;
//}

/**
  * @brief  Configures the TIMx Prescaler.
  * @param  TIMx: where x can be 1 to 17 to select the TIM peripheral.
  * @param  Prescaler: specifies the Prescaler Register value
  * @note   如果需要立即加载预分频系数，需要随后调用GenerateEvent
  * @retval None
  */
void LHL_TIM_SetPrescaler(TIM_TypeDef* TIMx, uint16_t Prescaler)
{
    /* Set the Prescaler value */
    TIMx->PSC = Prescaler;
}

/**
  * @brief  Specifies the TIMx Counter Mode to be used.
  * @param  TIMx: where x can be  1 or 2 to select the TIM peripheral.
  * @param  TIM_CounterMode: specifies the Counter Mode to be used
  *   This parameter can be one of the following values:
  *     @arg TIM_COUNTERMODE_UP: TIM Up Counting Mode
  *     @arg TIM_COUNTERMODE_DOWN: TIM Down Counting Mode
  *     @arg TIM_COUNTERMODE_CENTERALIGNED1: TIM Center Aligned Mode1
  *     @arg TIM_COUNTERMODE_CENTERALIGNED2: TIM Center Aligned Mode2
  *     @arg TIM_COUNTERMODE_CENTERALIGNED3: TIM Center Aligned Mode3
  * @retval None
  */
void LHL_TIM_SetCounterMode(TIM_TypeDef* TIMx, TIM_COUNTERMODE_t TIM_CounterMode)
{
    uint16_t tmpcr1 = 0;

    tmpcr1 = (uint16_t)TIMx->CR1;
    /* Reset the CMS and DIR Bits */
    tmpcr1 &= (uint16_t)(~((uint16_t)(TIMER_TIMX_CR1_DIR_Msk | TIMER_TIMX_CR1_CMS_Msk)));
    /* Set the Counter Mode */
    tmpcr1 |= TIM_CounterMode;
    /* Write to TIMx CR1 register */
    TIMx->CR1 = tmpcr1;
}

/**
  * @brief  配置定时器TIMx外设的从模式
  * @param  TIMx: where x can be  1 or 2 to select the TIM peripheral.
  * @param  smInit: TIM_SMInitTypeDef指定的结构体
  * @retval LHL_OK 或 LHL_ERROR
  */
LHL_StatusTypeDef LHL_TIM_SMInit(TIM_TypeDef* TIMx, TIM_SMInitTypeDef *smInit)
{
    __RW uint32_t smcr;
    
    /* Check parameters */
    if (TIMx == NULL || smInit == NULL) return LHL_ERROR;
    
    /* 关闭定时器和从模式 */
    TIMx->CR1 &= ~TIMER_TIMX_CR1_CEN_Msk;
    TIMx->SMCR &= ~TIMER_TIMX_SMCR_SMS_Msk;
    
    /* 根据参数设定SMCR */    
    smcr = ((uint32_t)(smInit->SlaveMode & 0x07) | \
            ((uint32_t)smInit->TriggerSource << TIMER_TIMX_SMCR_TS_Pos) | \
            ((uint32_t)smInit->MasterSlaveSync << TIMER_TIMX_SMCR_MSM_Pos));
    
    
    /* Configure external trigger if needed */
    if (smInit->TriggerSource == TIM_TS_ETRF) 
    {
        /* Configure ETR polarity, prescaler and filter */
        smcr |= ((uint32_t)smInit->ETRPolarity << TIMER_TIMX_SMCR_ETP_Pos) | \
                ((uint32_t)smInit->ETRPrescaler << TIMER_TIMX_SMCR_ETPS_Pos) | \
                ((uint32_t)smInit->ETRFilter << TIMER_TIMX_SMCR_ETF_Pos);
    }
    
    TIMx->SMCR = smcr;
    
    return LHL_OK;
}

/**
  * @brief  Selects the Input Trigger source
  * @param  TIMx: where x can be  1 or 2 to select the TIM peripheral.
  * @param  TIM_InputTriggerSource: The Input Trigger source.
  *   This parameter can be one of the following values:
  *     @arg TIM_TS_ITR0: Internal Trigger 0
  *     @arg TIM_TS_ITR1: Internal Trigger 1
  *     @arg TIM_TS_ITR2: Internal Trigger 2
  *     @arg TIM_TS_ITR3: Internal Trigger 3
  *     @arg TIM_TS_TI1F_ED: TI1 Edge Detector
  *     @arg TIM_TS_TI1FP1: Filtered Timer Input 1
  *     @arg TIM_TS_TI2FP2: Filtered Timer Input 2
  *     @arg TIM_TS_ETRF: External Trigger input
  * @retval None
  */
void LHL_TIM_SetInputTrigger(TIM_TypeDef* TIMx, TIM_TS_t TIM_InputTriggerSource)
{
    uint32_t tmpsmcr, tmpsms;

    /* Get the TIMx SMCR register value */
    tmpsmcr = TIMx->SMCR;
    tmpsms = tmpsmcr & TIMER_TIMX_SMCR_SMS_Msk;
    
    /* 关闭从模式 */
    TIMx->SMCR &= ~TIMER_TIMX_SMCR_SMS_Msk;
    
    /* Reset the TS Bits */
    tmpsmcr &= ~TIMER_TIMX_SMCR_TS_Msk;
    
    /* Set the Input Trigger source */
    tmpsmcr |= TIM_InputTriggerSource;
    
    /* Write to TIMx SMCR */
    TIMx->SMCR = tmpsmcr;
    
    /* 回写从模式 */
    TIMx->SMCR |= tmpsms;
}

///**
//  * @brief  Configures the TIMx Encoder Interface.
//  * @param  TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
//  * @param  TIM_EncoderMode: specifies the TIMx Encoder Mode.
//  *   This parameter can be one of the following values:
//  *     @arg TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
//  *     @arg TIM_EncoderMode_TI2: Counter counts on TI2FP2 edge depending on TI1FP1 level.
//  *     @arg TIM_EncoderMode_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
//  *                                on the level of the other input.
//  * @param  TIM_IC1Polarity: specifies the IC1 Polarity
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ICPolarity_Falling: IC Falling edge.
//  *     @arg TIM_ICPolarity_Rising: IC Rising edge.
//  * @param  TIM_IC2Polarity: specifies the IC2 Polarity
//  *   This parameter can be one of the following values:
//  *     @arg TIM_ICPolarity_Falling: IC Falling edge.
//  *     @arg TIM_ICPolarity_Rising: IC Rising edge.
//  * @retval None
//  */
//void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
//                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity)
//{
//  uint16_t tmpsmcr = 0;
//  uint16_t tmpccmr1 = 0;
//  uint16_t tmpccer = 0;
//    
//  /* Check the parameters */
//  assert_param(IS_TIM_LIST5_PERIPH(TIMx));
//  assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
//  assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
//  assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));

//  /* Get the TIMx SMCR register value */
//  tmpsmcr = TIMx->SMCR;
//  
//  /* Get the TIMx CCMR1 register value */
//  tmpccmr1 = TIMx->CCMR1;
//  
//  /* Get the TIMx CCER register value */
//  tmpccer = TIMx->CCER;
//  
//  /* Set the encoder Mode */
//  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
//  tmpsmcr |= TIM_EncoderMode;
//  
//  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
//  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIM_CCMR1_CC1S)) & (uint16_t)(~((uint16_t)TIM_CCMR1_CC2S)));
//  tmpccmr1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
//  
//  /* Set the TI1 and the TI2 Polarities */
//  tmpccer &= (uint16_t)(((uint16_t)~((uint16_t)TIM_CCER_CC1P)) & ((uint16_t)~((uint16_t)TIM_CCER_CC2P)));
//  tmpccer |= (uint16_t)(TIM_IC1Polarity | (uint16_t)(TIM_IC2Polarity << (uint16_t)4));
//  
//  /* Write to TIMx SMCR */
//  TIMx->SMCR = tmpsmcr;
//  /* Write to TIMx CCMR1 */
//  TIMx->CCMR1 = tmpccmr1;
//  /* Write to TIMx CCER */
//  TIMx->CCER = tmpccer;
//}

/**
  * @brief  Enables or disables 自动重装载预装载功能
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  NewState: new state of the TIMx peripheral Preload register
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_TIM_SetARRPreload(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Set the ARR Preload Bit */
    TIMx->CR1 |= TIMER_TIMX_CR1_ARPE_Msk;
  }
  else
  {
    /* Reset the ARR Preload Bit */
    TIMx->CR1 &= (uint16_t)~((uint16_t)TIMER_TIMX_CR1_ARPE_Msk);
  }
}

/**
  * @brief  Selects the TIMx peripheral Capture Compare DMA source.
  * @param  TIMx: where x can be 1 or 2 to select the TIM peripheral.
  * @param  NewState: new state of the Capture Compare DMA source
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_TIM_SetCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Set the CCDS Bit */
        TIMx->CR2 |= TIMER_TIMX_CR2_CCDS_Msk;
    }
    else
    {
        /* Reset the CCDS Bit */
        TIMx->CR2 &= (uint16_t)~((uint16_t)TIMER_TIMX_CR2_CCDS_Msk);
    }
}

/**
  * @brief  Enables or Disables the TIMx Update event.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  NewState: new state of the TIMx UDIS bit
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_TIM_SetUpdateEvent(TIM_TypeDef* TIMx, FunctionalState NewState)
{
      if (NewState != DISABLE)
      {
        /* Set the Update Disable Bit */
        TIMx->CR1 |= TIMER_TIMX_CR1_UDIS_Msk;
      }
      else
      {
        /* Reset the Update Disable Bit */
        TIMx->CR1 &= (uint16_t)~((uint16_t)TIMER_TIMX_CR1_UDIS_Msk);
      }
}

/**
  * @brief  Configures the TIMx Update Request Interrupt source.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_UpdateSource: specifies the Update source.
  *   This parameter can be one of the following values:
  *     @arg TIM_UPDATESOURCE_GLOBAL: Source of update is the counter overflow/underflow
                                       or the setting of UG bit, or an update generation
                                       through the slave mode controller.
  *     @arg TIM_UPDATESOURCE_REGULAR: Source of update is counter overflow/underflow.
  * @retval None
  */
void LHL_TIM_SetUpdateRequest(TIM_TypeDef* TIMx, TIM_UPDATESOURCE_t TIM_UpdateSource)
{
    if (TIM_UpdateSource != TIM_UPDATESOURCE_GLOBAL)
    {
        /* Set the URS Bit */
        TIMx->CR1 |= TIMER_TIMX_CR1_URS_Msk;
    }
    else
    {
        /* Reset the URS Bit */
        TIMx->CR1 &= (uint16_t)~((uint16_t)TIMER_TIMX_CR1_URS_Msk);
    }
}

/**
  * @brief  设置TIMER是否单脉冲模式（发生更新事件时，计数器是否停止）
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  NewState：ENABLE or DISABLE
  * @retval None
  */
void LHL_TIM_SetOnePulseMode(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        TIMx->CR1 |= (uint16_t)TIMER_TIMX_CR1_OPM_Msk;
    }
    else
    {
        TIMx->CR1 &= (uint16_t)~((uint16_t)TIMER_TIMX_CR1_OPM_Msk);
    }
}

/**
  * @brief  Selects the TIMx Trigger Output Mode.
  * @param  TIMx: where x can be 1 or 2 to select the TIM peripheral.
  * @param  TIM_TRGOSource: specifies the Trigger Output source.
  *   This paramter can be one of the following values:
  *     @arg TIM_TRGOSource_Reset:  The UG bit in the TIM_EGR register is used as the trigger output (TRGO).
  *     @arg TIM_TRGOSource_Enable: The Counter Enable CEN is used as the trigger output (TRGO).
  *     @arg TIM_TRGOSource_Update: The update event is selected as the trigger output (TRGO).
  *     @arg TIM_TRGOSource_OC1: The trigger output sends a positive pulse when the CC1IF flag
  *                              is to be set, as soon as a capture or compare match occurs (TRGO).
  *     @arg TIM_TRGOSource_OC1Ref: OC1REF signal is used as the trigger output (TRGO).
  *     @arg TIM_TRGOSource_OC2Ref: OC2REF signal is used as the trigger output (TRGO).

  *
  * @retval None
  */
void LHL_TIM_SetOutputTrigger(TIM_TypeDef* TIMx, TIM_TRGOSOURCE_t TIM_TRGOSource)
{
    /* Reset the MMS Bits */
    TIMx->CR2 &= (uint16_t)~((uint16_t)TIMER_TIMX_CR2_MMS_Msk);
    /* Select the TRGO source */
    TIMx->CR2 |=  TIM_TRGOSource;
}

/**
  * @brief  Selects the TIMx Slave Mode.
  * @param  TIMx: where x can be 1 or 2 to select the TIM peripheral.
  * @param  TIM_SlaveMode: specifies the Timer Slave Mode.
  *   This parameter can be one of the following values:
  *     @arg TIM_SlaveMode_Reset: Rising edge of the selected trigger signal (TRGI) re-initializes
  *                               the counter and triggers an update of the registers.
  *     @arg TIM_SlaveMode_Gated:     The counter clock is enabled when the trigger signal (TRGI) is high.
  *     @arg TIM_SlaveMode_Trigger:   The counter starts at a rising edge of the trigger TRGI.
  *     @arg TIM_SlaveMode_External1: Rising edges of the selected trigger (TRGI) clock the counter.
  * @retval None
  */
void LHL_TIM_SetSlaveMode(TIM_TypeDef* TIMx, TIM_SLAVEMODE_t TIM_SlaveMode)
{
    /* Reset the SMS Bits */
    TIMx->SMCR &= ~(TIMER_TIMX_SMCR_SMS_Msk);
    /* Select the Slave Mode */
    TIMx->SMCR |= TIM_SlaveMode;
}

/**
  * @brief  Sets or Resets the TIMx Master/Slave Mode.
  * @param  TIMx: where x can be 1 or 2 to select the TIM peripheral.
  * @param  TIM_MasterSlaveMode: specifies the Timer Master Slave Mode.
  *   This parameter can be one of the following values:
  *     @arg ENABLE: synchronization between the current timer and its slaves (through TRGO).
  *     @arg DISABLE: No action
  * @retval None
  */
void LHL_TIM_SetMasterSlaveMode(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        TIMx->SMCR |= TIMER_TIMX_SMCR_MSM_Msk;
    }
    else
    {
        /* Reset the MSM Bit */
        TIMx->SMCR &= (uint16_t)~((uint16_t)TIMER_TIMX_SMCR_MSM_Msk);
    }    
}

/**
  * @brief  Sets the TIMx Counter Register value
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void LHL_TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter)
{
    /* Set the Counter Register value */
    TIMx->CNT = Counter;
}

/**
  * @brief  设置TIMx Autoreload Register value（ARR寄存器）
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  Autoreload: specifies the Autoreload register new value.
  * @retval None
  */
void LHL_TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload)
{
    /* Set the Autoreload Register value */
    TIMx->ARR = Autoreload;
}

/**
  * @brief  Sets the TIMx Clock Division value.
  * @param  TIMx: where x can be  1 to 2 to select the TIM peripheral.
  * @param  TIM_CKD: specifies the clock division value.
  *   This parameter can be one of the following value:
  *     @arg TIM_CKD_DIV1: TDTS = Tck_tim
  *     @arg TIM_CKD_DIV2: TDTS = 2*Tck_tim
  *     @arg TIM_CKD_DIV4: TDTS = 4*Tck_tim
  * @retval None
  */
void LHL_TIM_SetClockDivision(TIM_TypeDef* TIMx, TIM_CKD_DIV_t TIM_CKD)
{
      /* Reset the CKD Bits */
      TIMx->CR1 &= (uint16_t)~((uint16_t)TIMER_TIMX_CR1_CKD_Msk);
      /* Set the CKD value */
      TIMx->CR1 |= TIM_CKD;
}

/**
  * @brief  获取定时器计数值
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @retval Counter Register value.
  */
uint16_t LHL_TIM_GetCounter(TIM_TypeDef* TIMx)
{
  /* Get the Counter Register value */
  return (uint16_t)TIMx->CNT;
}

/**
  * @brief  Gets the TIMx Prescaler value.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @retval Prescaler Register value.
  */
uint16_t LHL_TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
    /* Get the Prescaler Register value */
    return (uint16_t)TIMx->PSC;
}

/**
  * @brief  Configure the TI1 as Input.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg TIM_ICPolarity_Rising
  *     @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg TIM_ICSelection_DirectTI: TIM Input 1 is selected to be connected to IC1.
  *     @arg TIM_ICSelection_IndirectTI: TIM Input 1 is selected to be connected to IC2.
  *     @arg TIM_ICSelection_TRC: TIM Input 1 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter)
{
    uint16_t tmpccmr1 = 0, tmpccer = 0;
    
    /* Disable the Channel 1: Reset the CC1E Bit */
    TIMx->CCER &= (uint16_t)~((uint16_t)TIMER_TIMX_CCER_CC1E_Msk);
    tmpccmr1 = (uint16_t)TIMx->CCMR1;
    tmpccer = (uint16_t)TIMx->CCER;
    
    /* Select the Input and set the filter */
    tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIMER_TIMX_CCMR1_IC_CC1S_Msk)) & ((uint16_t)~((uint16_t)TIMER_TIMX_CCMR1_IC_IC1F_Msk)));
    tmpccmr1 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));
  
    /* Select the Polarity，注意此时CC1E默认开启 */
    tmpccer &= (uint16_t)~((uint16_t)(TIMER_TIMX_CCER_CC1P_Msk));
    tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIMER_TIMX_CCER_CC1E_Msk);
//    tmpccer |= (uint16_t)TIM_ICPolarity;
    
    /* Write to TIMx CCMR1 and CCER registers */
    TIMx->CCMR1 = tmpccmr1;
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TIMx: where x can be 1 or 2 to select the TIM peripheral.
  * @param  TIM_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg TIM_ICPolarity_Rising
  *     @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg TIM_ICSelection_DirectTI: TIM Input 2 is selected to be connected to IC2.
  *     @arg TIM_ICSelection_IndirectTI: TIM Input 2 is selected to be connected to IC1.
  *     @arg TIM_ICSelection_TRC: TIM Input 2 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter)
{
    uint16_t tmpccmr1 = 0, tmpccer = 0;
    
    /* Disable the Channel 2: Reset the CC2E Bit */
    TIMx->CCER &= (uint16_t)~((uint16_t)TIMER_TIMX_CCER_CC2E_Msk);
    tmpccmr1 = (uint16_t)TIMx->CCMR1;
    tmpccer = (uint16_t)TIMx->CCER;

    /* Select the Input and set the filter */
    tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TIMER_TIMX_CCMR1_IC_CC2S_Msk)) & ((uint16_t)~((uint16_t)TIMER_TIMX_CCMR1_IC_IC2F_Msk)));
    tmpccmr1 |= (uint16_t)(TIM_ICFilter << 12);
    tmpccmr1 |= (uint16_t)(TIM_ICSelection << 8);
  
    /* Select the Polarity，注意此时CC2E默认开启 */
    tmpccer &= (uint16_t)~((uint16_t)(TIMER_TIMX_CCER_CC2P_Msk));
    tmpccer |=  (uint16_t)((TIM_ICPolarity << 4) | (uint16_t)TIMER_TIMX_CCER_CC2E_Msk);
    //tmpccer |=  (uint16_t)(TIM_ICPolarity << 4);

    /* Write to TIMx CCMR1 and CCER registers */
    TIMx->CCMR1 = tmpccmr1 ;
    TIMx->CCER = tmpccer;
}

/*********************************End of File**********************************/
