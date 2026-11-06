/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_rtc.c
 * @version 2025-09-08
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Private Definition --------------------------------------------------------*/
#define LHL_RTC_TIMEOUT LHL_NRM_TIMEOUT                 /* RTC异步操作超时设定  */

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  初始化RTC
  * @param  RTC_Init    RTC参数
  * @retval OK：成功；ERROR：失败。
  */
LHL_StatusTypeDef LHL_RTC_Init(RTC_InitTypeDef* RTC_Init)
{
    // Enable Domain Clock
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWREN_Msk,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_BKPEN_Msk,ENABLE);
    
    // Enable Domain Access
    PWR_BackupAccessCmd(ENABLE);
    
    // Select RTC Clock
    RCC_RTCCLKConfig(RTC_Init->ClockSource);
       
    RCC_RTCCLKCmd(ENABLE);
    
    // Wait Sync    
    if (RTC_WaitForWriteDone() != LHL_OK) return LHL_ERROR;

    pRTC->CRL |= RTC_CRL_CNF_Msk;           // allow config
    
    pRTC->PRLH = (RTC_Init->Prescaler >> 16) & 0xF;
    pRTC->PRLL = (RTC_Init->Prescaler) & 0xFFFF;
    
    pRTC->CNTH = (RTC_Init->Counter >> 16) & 0xFFFF;
    pRTC->CNTL = (RTC_Init->Counter) & 0xFFFF;
    
    pRTC->ALRH = (RTC_Init->Alarm >> 16) & 0xFFFF;
    pRTC->ALRL = (RTC_Init->Alarm) & 0xFFFF;
    
    pRTC->CRL &= ~RTC_CRL_CNF_Msk;          // config update
    
    return LHL_OK;
}

/**
  * @brief  获取RTC计数值（带进位处理）
  * @param  cnt Pointer to counter value for read
  * @retval OK：成功；ERROR：失败。
  */
LHL_StatusTypeDef LHL_RTC_GetCounter(uint32_t* cnt)
{
    uint32_t high1, low, high2;
    
    /* 等待RTC同步 */
    if (RTC_WaitForReadSync() != LHL_OK) {
        return LHL_ERROR;
    }
    
    /* 循环读取直到高字节稳定 */
    do {
        high1 = pRTC->CNTH;    /* 第一次读取高字节 */
        low   = pRTC->CNTL;    /* 读取低字节 */
        high2 = pRTC->CNTH;    /* 第二次读取高字节 */
        
        /* 如果高字节变化，说明在读取过程中发生了进位，需要重新读取 */
    } while (high1 != high2);
    
    /* 组合32位计数值 */
    *cnt = (high1 << 16) | low;
    
    return LHL_OK;
}

/**
  * @brief  设置RTC计数值
  * @parm   cnt     设置计数值
  * @retval OK：成功；ERROR：失败。
  */
LHL_StatusTypeDef LHL_RTC_SetCounter(uint32_t cnt)
{
    if (RTC_WaitForWriteDone() != LHL_OK) return LHL_ERROR;

    pRTC->CRL |= RTC_CRL_CNF_Msk;           // allow config
    
    pRTC->CNTH = (cnt >> 16) & 0xFFFF;
    pRTC->CNTL = (cnt) & 0xFFFF;
    
    pRTC->CRL &= ~RTC_CRL_CNF_Msk;          // config update
    
    return LHL_OK;
}

/**
  * @brief  设置RTC闹钟值
  * @param  Alarm value
  * @retval OK：成功；ERROR：失败。
  */
LHL_StatusTypeDef LHL_RTC_SetAlarm(uint32_t alarm)
{
    if (RTC_WaitForWriteDone() != LHL_OK) return LHL_ERROR;

    pRTC->CRL |= RTC_CRL_CNF_Msk;
    
    pRTC->ALRH = (alarm >> 16) & 0xFFFF;
    pRTC->ALRL = (alarm) & 0xFFFF;
    
    pRTC->CRL &= ~RTC_CRL_CNF_Msk;
    
    return LHL_OK;
}

/**
  * @brief  设置RTC预分频装载寄存器，长度20位
  * @param  prl     预分频值
  * @retval OK：成功；ERROR：失败。
  */
LHL_StatusTypeDef LHL_RTC_SetPrescaler(uint32_t prl)
{
    if (RTC_WaitForWriteDone() != LHL_OK) return LHL_ERROR;
    
    pRTC->CRL |= RTC_CRL_CNF_Msk;           //allow config
    
    pRTC->PRLH = (prl >> 16) & 0xF;
    pRTC->PRLL = (prl) & 0xFFFF;
    
    pRTC->CRL &= ~RTC_CRL_CNF_Msk;          //config update
    
    return LHL_OK;
}

/**
  * @brief  设置RTC指定中断
  * @param  RTC_IT: interrupts of timer, this parameter can be any combination of following options:
  *         @arg    RTC_IT_SECIE：秒中断使能
  *         @arg    RTC_IT_ALRIE：闹钟中断使能
  *         @arg    RTC_IT_OWIE：溢出中断使能
  * @param  ENABLE or DISABLE.
  * @retval OK：成功；ERROR：错误。
  */
LHL_StatusTypeDef LHL_RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState)
{
    if (RTC_WaitForWriteDone() != LHL_OK) return LHL_ERROR;
    if (RTC_WaitForReadSync() != LHL_OK) return LHL_ERROR;

    if (NewState != DISABLE)
    {
        pRTC->CRH |= RTC_IT;
        
        if(RTC_IT & RTC_IT_ALRIE)
        {
            // EXTI9连接到RTC闹钟事件
            pEXTI->RTSR |= EXTI_LINE_9;
            pEXTI->IMR |= EXTI_LINE_9;
        }
    }
    else
    {
        pRTC->CRH &= ~RTC_IT;
        
        if(RTC_IT & RTC_IT_ALRIE)
        {
            pEXTI->IMR &= ~(uint32_t)EXTI_LINE_9;
            pEXTI->RTSR &= ~(uint32_t)EXTI_LINE_9;
        }
    }
    
    return LHL_OK;
}

/**
  * @brief  获取RTC指定中断标志位状态
  * @param  RTC_IT: interrupt flags of RTC, this parameter can be any one of following options:
  *         @arg    RTC_FLAG_SECF：秒中断标志
  *         @arg    RTC_FLAG_ALRF：闹钟中断标志
  *         @arg    RTC_FLAG_OWF：溢出中断标志
  * @retval SET or RESET
  */
ITStatus LHL_RTC_GetPending(uint32_t RTC_IT_FLAG)
{
    ITStatus bitstatus = RESET;

    /* Check the status of the specified RCC interrupt */
    if ((pRTC->CRL & RTC_IT_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the RTC_IT status */
    return  bitstatus;
}

/**
  * @brief  清除RTC中断标志位
  * @param  RTC_IT: interrupts of timer, this parameter can be any combination of following options:
  *         @arg    RTC_CRL_SECF_Msk：秒中断标志
  *         @arg    RTC_CRL_ALRF_Msk：闹钟中断标志
  *         @arg    RTC_CRL_OWF_Msk：溢出中断标志
  * @retval LHL Status
  */
LHL_StatusTypeDef LHL_RTC_ClearPending(uint32_t RTC_IT_FLAG)
{
    if (RTC_WaitForWriteDone() != LHL_OK) return LHL_ERROR;
    if (RTC_WaitForReadSync() != LHL_OK) return LHL_ERROR;
    
    pRTC->CRL &= ~RTC_IT_FLAG;
    
    if(RTC_IT_FLAG & RTC_FLAG_ALRF)
    {   
        // EXTI9连接到RTC闹钟事件
        LHL_EXTI_ClearPending(EXTI_LINE_9);
    }
    return LHL_OK;
}

/**
  * @brief  Wait until previous write to RTC operation complete
  * @retval OK：写入同步成功；TIMEOUT：写入超时
  */
LHL_StatusTypeDef RTC_WaitForWriteDone(void)
{
    uint32_t timeout = LHL_RTC_TIMEOUT;
    while ((pRTC->CRL & RTC_CRL_RTOFF_Msk)==0)
    {
        if ((timeout--) == 0) return LHL_TIMEOUT;
    }
    return LHL_OK;
}

/**
  * @brief  Wait for rtc register has been updated before read RTC_CNT, RTC_ALR, RTC_PRL registers
  * @retval OK：读取同步成功；TIMEOUT：读取超时
  */
LHL_StatusTypeDef RTC_WaitForReadSync(void)
{
    uint32_t timeout = LHL_RTC_TIMEOUT;
    while ((pRTC->CRL & RTC_CRL_RSF_Msk)==0)
    {
        if ((timeout--) == 0) return LHL_TIMEOUT;
    }
    return LHL_OK;
}

/*********************************End of File**********************************/
