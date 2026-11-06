/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_power.c
 * @version 2025-09-22
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Private Variables ---------------------------------------------------------*/
// static __RW uint32_t uCR; deprecated for V10
// static __RW uint32_t uCFGR; deprecated for V10
// static __RW PWR_POWERMODE_t tPowerMode; deprecated for V10

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  执行休眠，在此之前需要调用LHL_PWR_SetPowerMode设定好具体的休眠模式
  * @param  None
  * @retval None
  */
void LHL_PWR_EnterSleep(void)
{
    __LHL_DSB
    __WFI();
}
//void LHL_PWR_EnterSleep(void) deprecated for V10
//{
//    uint32_t tmp;
//    
//    if (tPowerMode == PWR_MODE_SLEEP)
//    {
//        /* Sleep only */
//        __WFI();  
//    }
//    else
//    {
//        /* Spcial case handle */  
//        uCR = pRCC->CR;
//        uCFGR = pRCC->CFGR;
//        tmp = uCFGR;
//        tmp &= ~(RCC_CFGR_HSIDIV2_Msk | RCC_CFGR_HPRE_Msk);
//        tmp |= 0x80;
//        pRCC->CFGR = tmp;
//        if (tPowerMode == PWR_MODE_SPECIAL)
//        {
//            pFLASH->CTRL |= (uint32_t)0x10;
//        }
//        /* 执行休眠 */
//        __WFI();    
//        /* Restore Clocks */
//        if (tPowerMode == PWR_MODE_SPECIAL)
//        {
//            pFLASH->CTRL &= ~(uint32_t)0x10;
//        }
//        pRCC->CR = uCR;
//        pRCC->CFGR = uCFGR;
//    }
//}

/**
  * @brief  执行休眠之前，调用此函数选择具体的休眠模式
  * @param  PWR_Power_Mode_TypeDef：5种休眠模式
  *     @arg    PWR_MODE_SLEEP          普通休眠
  *     @arg    PWR_MODE_DEEP_SLEEP_1   深度休眠1
  *     @arg    PWR_MODE_DEEP_SLEEP_2   深度休眠2
  *     @arg    PWR_MODE_SNOOZE         ADC小睡模式
  *     @arg    PWR_MODE_SHUTDOWN       关断模式
  * @retval None
  */
void LHL_PWR_SetPowerMode(PWR_POWERMODE_t mode)
{
    SET_BIT(pRCC->APB1ENR, ((uint32_t)RCC_APB1ENR_FLASHEN_Msk));
    SET_BIT(pRCC->APB1ENR, ((uint32_t)RCC_APB1ENR_PWREN_Msk));
    
    LHL_RCC_Unlock();    
    
//    tPowerMode = mode;  deprecated for V10
    switch (mode)
    {
        case PWR_MODE_SHUTDOWN:
            /* 1: 使能flash自动进入关断模式 */
            SET_BIT(pFLASH->CTRL, ((uint32_t)FLASH_CTRL_DEEP_SLEEP_AUTO_Msk));
        
            /* 1: 系统进入深度睡眠2 */
            SET_BIT(pPWR->CR, ((uint32_t)PWR_CR_LPDS_Msk));
            
            /* 0: ADC小睡模式禁用 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_ADC_MSYS_EN_Msk));
            
            /* 1: 关断模式 */
            SET_BIT(pPWR->CR, ((uint32_t)PWR_CR_PDM_Msk));
        
            /* 1: Set SLEEPDEEP bit of Cortex System Control Register */
            SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
            break;
        case PWR_MODE_DEEP_SLEEP_1:
            /* 1: 使能flash自动进入关断模式 */
            SET_BIT(pFLASH->CTRL, ((uint32_t)FLASH_CTRL_DEEP_SLEEP_AUTO_Msk));          
                
            /* 0: 系统进入深度睡眠1 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_LPDS_Msk));
            
            /* 0: ADC小睡模式禁用 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_ADC_MSYS_EN_Msk));
            
            /* 0: 非关断模式 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_PDM_Msk));
                
            /* 1: Set SLEEPDEEP bit of Cortex System Control Register */
            SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk)); 
            break;
        case PWR_MODE_DEEP_SLEEP_2:
            /* 1: 使能flash自动进入关断模式 */
            SET_BIT(pFLASH->CTRL, ((uint32_t)FLASH_CTRL_DEEP_SLEEP_AUTO_Msk));
                        
            /* 1: 系统进入深度睡眠2 */
            SET_BIT(pPWR->CR, ((uint32_t)PWR_CR_LPDS_Msk));        

            /* 0: ADC小睡模式禁用 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_ADC_MSYS_EN_Msk));
            
            /* 0: 非关断模式 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_PDM_Msk));

            /* 1: Set SLEEPDEEP bit of Cortex System Control Register */
            SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));   
            break;
        case PWR_MODE_SNOOZE:
            /* 1: 使能flash自动进入关断模式 */
            SET_BIT(pFLASH->CTRL, ((uint32_t)FLASH_CTRL_DEEP_SLEEP_AUTO_Msk));
        
            /* 1: 系统进入深度睡眠2 */
            SET_BIT(pPWR->CR, ((uint32_t)PWR_CR_LPDS_Msk));
            
            /* 1: ADC小睡模式使用 */
            SET_BIT(pPWR->CR, ((uint32_t)PWR_CR_ADC_MSYS_EN_Msk));
            
            /* 0: 非关断模式 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_PDM_Msk));
        
            /* 1: Set SLEEPDEEP bit of Cortex System Control Register */
            SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk)); 
            break;
//        case PWR_MODE_SPECIAL: deprecated for V10
//            pFLASH->CTRL &= ~((uint32_t)0x20);
//        
//            pPWR->CR &= ~((uint32_t)0x200 | (uint32_t)0x02);
//            pPWR->CR |= 0x01;          
//        
//            /* 0: Clear SLEEPDEEP bit of Cortex System Control Register */
//            SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
//            break;
        case PWR_MODE_SLEEP: 
            /* 0: 禁用flash自动进入关断模式 */
            CLEAR_BIT(pFLASH->CTRL, ((uint32_t)FLASH_CTRL_DEEP_SLEEP_AUTO_Msk));
            
            /* 0: 系统不进入深度睡眠2 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_LPDS_Msk));
        
            /* 0: ADC小睡模式禁用 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_ADC_MSYS_EN_Msk));
        
            /* 0: 非关断模式 */
            CLEAR_BIT(pPWR->CR, ((uint32_t)PWR_CR_PDM_Msk));
    
            /* 0: Clear SLEEPDEEP bit of Cortex System Control Register */
            CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
            break;
    }

    /* 默认取消DBP */
    pPWR->CR |= PWR_CR_DBP_Msk;
}

/**
  * @brief  Enables or disables access to the RTC and backup registers.
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        pPWR->CR |= PWR_CR_DBP_Msk;
    }
    else
    {
        pPWR->CR &= ~PWR_CR_DBP_Msk;
    }
}

/**
  * @brief  启用PVD阈值电压监控
  * @param  PVD_InitStruct  初始值指针
  * @retval SET：监控电压低于阈值；RESET：监控电压高于阈值
  */
void LHL_PVD_Init(PVD_InitTypeDef *PVD_InitStruct)
{
    uint32_t tmp;
    
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWREN_Msk, ENABLE);
    
    tmp = pPWR->CR;
    
    tmp &= ~(PWR_CR_PVDE_Msk | PWR_CR_PVDMODE_Msk | PWR_CR_PSM_VTH_DVDD_Msk | PWR_CR_PSM_VTH_AVDD_Msk);

    tmp |= (uint32_t)PVD_InitStruct->DetectionSignal << PWR_CR_PVDMODE_Pos;
    if (PVD_InitStruct->DetectionSignal == PVD_MODE_IOVDD)
    {
        tmp |= (uint32_t)PVD_InitStruct->ThresholdVoltage << PWR_CR_PSM_VTH_DVDD_Pos;    
    }
    else
    {
        tmp |= (uint32_t)PVD_InitStruct->ThresholdVoltage << PWR_CR_PSM_VTH_AVDD_Pos; 
    }
    tmp |= (uint32_t)PVD_InitStruct->State << PWR_CR_PVDE_Pos;
    
    pPWR->CR = tmp;
}

/**
  * @brief  获取PVD阈值电压标识
  * @param  None
  * @retval SET：监控电压低于阈值；RESET：监控电压高于阈值
  */
FlagStatus LHL_PVD_GetFlag(void)
{
    if(pPWR->CSR & PWR_CSR_LVDO_Msk)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*********************************End of File**********************************/
