/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_iwdg.c
 * @version 2025-09-08
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  禁用IWDG的EN位，暂停运行IWDG
  * @param  None
  * @retval 如果IWDG已锁，则返回LHL_ERROR；成功暂停IWDG返回LHL_OK
  */
LHL_StatusTypeDef LHL_IWDG_Stop(void)
{
    if (pIWDG->LOCK & IWDG_LOCK_IWDG_LOCK_Msk)
    {
        return LHL_ERROR;
    }
    else
    {
        pIWDG->EN = 0;
        return LHL_OK;
    }
}

/**
  * @brief  使能IWDG的EN位，继续运行IWDG
  * @param  None
  * @retval 如果IWDG已锁，则返回LHL_ERROR；成功启动IWDG返回LHL_OK
  */
LHL_StatusTypeDef LHL_IWDG_Resume(void)
{
    if (pIWDG->LOCK & IWDG_LOCK_IWDG_LOCK_Msk)
    {
        return LHL_ERROR;
    }
    else
    {
        pIWDG->EN = 1;
        return LHL_OK;
    }
}

/**
  * @brief  写入0xAAAA重装载并启动IWDG
  * @param  None
  * @retval 如果IWDG已锁，则返回LHL_ERROR；成功启动IWDG返回LHL_OK
  */
LHL_StatusTypeDef LHL_IWDG_Start(void)
{
    if (pIWDG->LOCK & IWDG_LOCK_IWDG_LOCK_Msk)
    {
        return LHL_ERROR;
    }
    else
    {
        pIWDG->KR = KR_KEY_START;
        pIWDG->EN = 1;        
        return LHL_OK;
    }
}

/**
  * @brief  写入0xAAAA重装载IWDG
  * @param  None
  * @retval None
  */
void LHL_IWDG_Reload(void)
{
    pIWDG->KR = KR_KEY_RELOAD;
}

/**
  * @brief  写入0x5555表示允许访问IWDG_PR和IWDG_RLR寄存器
  * @param  None
  * @retval 如果IWDG已锁，则返回LHL_ERROR；成功解锁返回LHL_OK
  */
LHL_StatusTypeDef LHL_IWDG_Unlock(void)
{
    if (pIWDG->LOCK & IWDG_LOCK_IWDG_LOCK_Msk)
    {
        return LHL_ERROR;
    }
    else
    {
        pIWDG->KR = KR_KEY_UNLOCK;
        return LHL_OK;
    }
}

/**
  * @brief  当写该位为1时，WDG_PR 、IWDG_RLR、IWDG_EN 三个寄存器不可被改写。只有任意复位源才能将该位复位到0
  * @param  None
  * @retval None
  */
void LHL_IWDG_Lock(void)
{
    pIWDG->LOCK = 1;
}

/**
  * @brief  Sets IWDG Prescaler value。在PVU位被清除后才能重新改变预分频值。
  * @param  IWDG_Prescaler: specifies the IWDG Prescaler value, can be one of the following:
  *            @arg IWDG_Prescaler_4: IWDG prescaler set to 4
  *            @arg IWDG_Prescaler_8: IWDG prescaler set to 8
  *            @arg IWDG_Prescaler_16: IWDG prescaler set to 16
  *            @arg IWDG_Prescaler_32: IWDG prescaler set to 32
  *            @arg IWDG_Prescaler_64: IWDG prescaler set to 64
  *            @arg IWDG_Prescaler_128: IWDG prescaler set to 128
  *            @arg IWDG_Prescaler_256: IWDG prescaler set to 256
  *         Timeout：超时设定
  * @retval 如果IWDG已锁或写入超时，返回LHL_ERROR；成功修改预分频值返回LHL_OK
  */
LHL_StatusTypeDef LHL_IWDG_SetPrescaler(IWDG_PRESCALER_t IWDG_Prescaler, uint32_t Timeout)
{
    uint32_t t = Timeout;
    
    if (LHL_IWDG_Unlock() == LHL_ERROR)
    {
        return LHL_ERROR;
    }
    
    while (pIWDG->SR & IWDG_SR_PVU_Msk)
    {
        if ((t--) == 0) return LHL_ERROR;
    }
    
    pIWDG->PR = IWDG_Prescaler;
    
    // 在预分频值更新后，不必等待PVU复位，可继续执行下面的代码
//    while (pIWDG->SR & IWDG_SR_PVU_Msk)
//    {
//        if ((t--) == 0) return LHL_ERROR;
//    }
    
    return LHL_OK;
}

/**
  * @brief  Sets IWDG Reload value。必须在RVU位被清除后才能重新改变预装载值。
  * @param  Reload：12位长度，默认值是0xFFF，最小值是0x000
  *         Timeout：超时设定
  * @retval 如果IWDG已锁或写入超时，返回LHL_ERROR；成功修改预分频值返回LHL_OK
  */
LHL_StatusTypeDef LHL_IWDG_SetReload(uint16_t Reload, uint32_t Timeout)
{
    uint32_t t = Timeout;
    
    if (LHL_IWDG_Unlock() == LHL_ERROR)
    {
        return LHL_ERROR;
    }
    
    while (pIWDG->SR & IWDG_SR_RVU_Msk)
    {
        if ((t--) == 0) return LHL_ERROR;
    }
    
    pIWDG->RLR = (Reload & 0xFFF);      // 12bit Reload Vaule for IWDG
    
    // 在重装载值更新后，不必等待RVU复位，可继续执行下面的代码
//    while (pIWDG->SR & IWDG_SR_RVU_Msk)
//    {
//        if ((t--) == 0) return LHL_ERROR;
//    }
    
    return LHL_OK;
}

/*********************************End of File**********************************/
