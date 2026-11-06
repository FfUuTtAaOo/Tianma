/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_mio.c
 * @version 2025-10-16
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  使能MIO外设。注意：设置MIO任何功能之前必须使能MIO！
  * @param  None 
  * @retval None
  */
void LHL_MIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_MIOEN_Msk, ENABLE);
        
    LHL_MIO_Reset();

    MIO->CTRL |= MIO_CTRL_MIOEN_MASK; 
}

/**
  * @brief  禁用MIO外设。
  * @param  None 
  * @retval None
  */
void LHL_MIO_DeInit(void)
{
    MIO->CTRL &= ~MIO_CTRL_MIOEN_MASK; 
        
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_MIOEN_Msk, DISABLE);
}

/**
  * @brief  复位MIO外设
  * @param  None
  * @retval None
  */
void LHL_MIO_Reset(void)
{
    /*do software reset, software reset operation affect all other MIO registers except CTRL*/
    MIO->CTRL |= MIO_CTRL_SWRST_MASK;
    MIO->CTRL = 0;
}

/**
  * @brief  初始化MIO定时器外设
  * @param  id              MIO_TIMER_x（x取值0~1）
  * @param  init            定时器外设参数
  * @retval None
  */
void LHL_MIO_TimerInit(MIO_TIMER_t id, MIO_TIM_InitTypedef *init)
{
    MIO->TIMCFG[id] = MIO_TIMCFG_TIMOUT(init->Timer_Output) | \
                        MIO_TIMCFG_TIMDEC(init->Timer_Decrement_Clock) | \
                        MIO_TIMCFG_TIMRST(init->Timer_Reset_Condition) | \
                        MIO_TIMCFG_TIMDIS(init->Timer_Disable_Condition) | \
                        MIO_TIMCFG_TIMENA(init->Timer_Enable_Condition) | \
                        MIO_TIMCFG_TSTOP(init->Timer_StopBit_Condition) | \
                        MIO_TIMCFG_TSTART(init->Timer_StartBit_Condition);

    MIO->TIMCMP[id] = MIO_TIMCMP_CMP(init->Timer_Compare);

    MIO->TIMCTL[id] = MIO_TIMCTL_TRGSEL(init->Trigger_Select) | \
                          MIO_TIMCTL_TRGPOL(init->Trigger_Polarity) | \
                          MIO_TIMCTL_TRGSRC(init->Trigger_Source) | \
                          MIO_TIMCTL_PINCFG(init->Pin_Config) | \
                          MIO_TIMCTL_PINSEL(init->Pin_Select) | \
                          MIO_TIMCTL_PINPOL(init->Pin_Polarity) | \
                          MIO_TIMCTL_TIMOD(init->Timer_Mode);
}

/**
  * @brief  初始化MIO移位寄存器外设
  * @param  MIO_SHIFTER_t               MIO_SHIFTER_x（x取值0~1）
  * @param  MIO_SHIFTER_InitTypedef*    移位寄存器参数
  * @retval None
  */
void LHL_MIO_ShifterInit(MIO_SHIFTER_t id, MIO_SHIFTER_InitTypedef *init)
{

    MIO->SHIFTCFG[id] = MIO_SHIFTCFG_INSRC(init->Shifter_Input) | \
                            MIO_SHIFTCFG_SSTOP(init->Shifter_Stop) | \
                            MIO_SHIFTCFG_SSTART(init->Shifter_Start);

    MIO->SHIFTCTL[id] = MIO_SHIFTCTL_TIMSEL(init->Shifter_Timer) | \
                            MIO_SHIFTCTL_TIMPOL(init->Shifter_Timer_Polarity) | \
                            MIO_SHIFTCTL_PINCFG(init->Shifter_Pin_Config) | \
                            MIO_SHIFTCTL_PINSEL(init->Shifter_Pin) | \
                            MIO_SHIFTCTL_PINPOL(init->Shifter_Pin_Polarity) | \
                            MIO_SHIFTCTL_SMOD(init->Shifter_Mode);       
}

/**
  * @brief  初始化MIO模拟UART功能
  * @param  MUART_InitStructure     MUART外设参数
  * @retval None
  */
void LHL_MIO_UARTInit(MIO_UART_HandleTypeDef* handle)
{
    MIO_SHIFTER_InitTypedef shifterConfig;
    MIO_TIM_InitTypedef timerConfig;
    uint32_t freq, div, cmp;

    /* 计算波特率 */
    freq = LHL_RCC_GetPCLK2Freq();                              // 获取MIO clock    
    div = (freq + handle->MIO_UART_BaudRate) / (2 * handle->MIO_UART_BaudRate) - 1;    
    cmp = (uint16_t)(8U * 2U - 1U) << 8U;                       // UART固定位数8bit
    cmp |= (uint16_t)div;

    /* MIO移位寄存器和定时器配置 */
    if (handle->MIO_UART_TX == ENABLE)
    {
        /* 1. Configure the SHIFTER_x for UART_TX. */
        shifterConfig.Shifter_Pin = handle->MIO_UART_TX_Pin;
        shifterConfig.Shifter_Pin_Config = MIO_PIN_OUTPUT_ENABLED;
        shifterConfig.Shifter_Pin_Polarity = MIO_PIN_ACTIVE_HIGH;
        shifterConfig.Shifter_Timer = handle->MIO_UART_TX_Timer;
        shifterConfig.Shifter_Timer_Polarity = MIO_SHFT_TIM_POL_POS;
        shifterConfig.Shifter_Mode = MIO_SHFT_MODE_TRANSMIT;
        shifterConfig.Shifter_Input = MIO_SHFT_INPUT_PIN;
        shifterConfig.Shifter_Stop = MIO_SHFT_STOP_BIT_HIGH;
        shifterConfig.Shifter_Start = MIO_SHFT_START_BIT_LOW;
        
        LHL_MIO_ShifterInit(handle->MIO_UART_TX_Shifter, &shifterConfig);
    
        /*2. Configure the TIMER_x for UART_TX. */
        timerConfig.Trigger_Select   = (uint8_t)MIO_TIM_TRIG_SHIFT(handle->MIO_UART_TX_Shifter);
        timerConfig.Trigger_Polarity = MIO_TIM_TRIG_ACTIVE_LOW;
        timerConfig.Trigger_Source   = MIO_TIM_TRIG_SRC_INTERNAL;
        timerConfig.Pin_Config       = MIO_PIN_OUTPUT_DISABLED;
        timerConfig.Pin_Select       = handle->MIO_UART_TX_Pin;
        timerConfig.Pin_Polarity     = MIO_PIN_ACTIVE_HIGH;
        timerConfig.Timer_Mode       = MIO_TIM_DUAL_8BIT_BAUD;
        timerConfig.Timer_Output     = MIO_TIM_OUTPUT_HIGH;
        timerConfig.Timer_Decrement_Clock   = MIO_TIM_MIO_CLOCK;
        timerConfig.Timer_Reset_Condition   = MIO_TIM_RST_NEVER;
        timerConfig.Timer_Disable_Condition = MIO_TIM_DIS_COMPARE;
        timerConfig.Timer_Enable_Condition  = MIO_TIM_ENA_TRIGGER_HIGH;
        timerConfig.Timer_StopBit_Condition = MIO_TIM_STOP_BIT_ENABLED_ON_DISABLE;
        timerConfig.Timer_StartBit_Condition = MIO_TIM_START_BIT_ENABLED;
        timerConfig.Timer_Compare           = cmp;
        
        LHL_MIO_TimerInit(handle->MIO_UART_TX_Timer, &timerConfig);
    }
    else
    {
        MIO->SHIFTCFG[handle->MIO_UART_TX_Shifter] = 0U;
        MIO->SHIFTCTL[handle->MIO_UART_TX_Shifter] = 0U;
        MIO->TIMCFG[handle->MIO_UART_TX_Timer] = 0U;
        MIO->TIMCMP[handle->MIO_UART_TX_Timer] = 0U;
        MIO->SHIFTCTL[handle->MIO_UART_TX_Timer] = 0U;
    }

    if (handle->MIO_UART_RX == ENABLE)
    {
        /* 3. Configure the SHIFTER_x for UART_RX. */
        shifterConfig.Shifter_Pin = handle->MIO_UART_RX_Pin;
        shifterConfig.Shifter_Pin_Config = MIO_PIN_OUTPUT_DISABLED;
        shifterConfig.Shifter_Pin_Polarity = MIO_PIN_ACTIVE_HIGH;
        shifterConfig.Shifter_Timer = handle->MIO_UART_RX_Timer;
        shifterConfig.Shifter_Timer_Polarity = MIO_SHFT_TIM_POL_NEG;
        shifterConfig.Shifter_Mode = MIO_SHFT_MODE_RECEIVE;
        shifterConfig.Shifter_Input = MIO_SHFT_INPUT_PIN;
        shifterConfig.Shifter_Stop = MIO_SHFT_STOP_BIT_HIGH;
        shifterConfig.Shifter_Start = MIO_SHFT_START_BIT_LOW;
        
        LHL_MIO_ShifterInit(handle->MIO_UART_RX_Shifter, &shifterConfig);

        /* 4. Configure the TIMER_x for UART_RX. */
        timerConfig.Trigger_Select   = (uint8_t)MIO_TIM_TRIG_PIN(handle->MIO_UART_RX_Pin);
        timerConfig.Trigger_Polarity = MIO_TIM_TRIG_ACTIVE_HIGH;
        timerConfig.Trigger_Source   = MIO_TIM_TRIG_SRC_EXTERNAL;//??
        timerConfig.Pin_Config       = MIO_PIN_OUTPUT_DISABLED;
        timerConfig.Pin_Select       = handle->MIO_UART_RX_Pin;
        timerConfig.Pin_Polarity     = MIO_PIN_ACTIVE_LOW;
        timerConfig.Timer_Mode       = MIO_TIM_DUAL_8BIT_BAUD;
        timerConfig.Timer_Output     = MIO_TIM_OUTPUT_HIGH_ON_RESET;
        timerConfig.Timer_Decrement_Clock   = MIO_TIM_MIO_CLOCK;
        timerConfig.Timer_Reset_Condition   = MIO_TIM_RST_PIN_RISING_EDGE;
        timerConfig.Timer_Disable_Condition = MIO_TIM_DIS_COMPARE;
        timerConfig.Timer_Enable_Condition  = MIO_TIM_ENA_PIN_RISING_EDGE;
        timerConfig.Timer_StopBit_Condition = MIO_TIM_STOP_BIT_ENABLED_ON_DISABLE;
        timerConfig.Timer_StartBit_Condition = MIO_TIM_START_BIT_ENABLED;      
        timerConfig.Timer_Compare           = cmp;

        LHL_MIO_TimerInit(handle->MIO_UART_RX_Timer, &timerConfig);
    }
    else
    {
        MIO->SHIFTCFG[handle->MIO_UART_RX_Shifter] = 0U;
        MIO->SHIFTCTL[handle->MIO_UART_RX_Shifter] = 0U;
        MIO->TIMCFG[handle->MIO_UART_RX_Timer] = 0U;
        MIO->TIMCMP[handle->MIO_UART_RX_Timer] = 0U;
        MIO->SHIFTCTL[handle->MIO_UART_RX_Timer] = 0U;
    }
}

/**
  * @brief  使用堵塞方式发送UART数据
  * @param  handle      MIO UART的结构体参数句柄
  * @param  txData      指向待发送数据的指针
  * @param  txSize      待发送数据量
  * @retval LHL_OK：发送成功；LHL_ERROR：超时失败。
  */
LHL_StatusTypeDef LHL_MIO_UARTTransmit(MIO_UART_HandleTypeDef* handle, const uint8_t *txData, uint8_t txSize)
{
    uint32_t timeout = LHL_LNG_TIMEOUT;

    while (0U != txSize--)
    {
        /* Wait until data transfer complete. */
        while (0U == ((MIO->SHIFTSTAT & MIO_SHIFTSTAT_SSF_MASK) & (1UL << handle->MIO_UART_TX_Shifter)))
        {
            if ((timeout--) == 0) return LHL_ERROR;
        }

        MIO->SHIFTBUF[handle->MIO_UART_TX_Shifter] = *txData++;
    }
    return LHL_OK;
}

/**
  * @brief  使用堵塞方式接收UART数据
  * @param  handle      MIO UART的结构体参数句柄
  * @param  rxData      指向接收数据的指针
  * @param  rxSize      待接收数据量
  * @retval LHL_OK：发送成功；LHL_ERROR：超时失败。
  */
LHL_StatusTypeDef LHL_MIO_UARTReceive(MIO_UART_HandleTypeDef* handle, uint8_t *rxData, size_t rxSize)
{
    uint32_t timeout = LHL_LNG_TIMEOUT;

    while (0U != rxSize--)
    {
        /* Wait until data transfer complete. */
        while (0U == ((MIO->SHIFTSTAT & MIO_SHIFTSTAT_SSF_MASK) & (1UL << handle->MIO_UART_RX_Shifter)))
        {
            if ((timeout--) == 0) return LHL_ERROR;
        }

        *rxData++ = (uint8_t)(MIO->SHIFTBUFBYS[handle->MIO_UART_RX_Shifter]);
    }
    return LHL_OK;
}

/**
  * @brief  设置MIO外设中断
  * @param  MIO_IT      SHIFT或者TIMER中断使能位
  * @param  NewState    ENABLE or DISABLE
  * @retval None
  */
void LHL_MIO_ITConfig(MIO_IT_t MIO_IT, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        switch (MIO_IT)
        {
            case MIO_SHIFT0_IT_SSIE:
                MIO->SHIFTSIEN |= 0x01;
                break;
            case MIO_SHIFT1_IT_SSIE:
                MIO->SHIFTSIEN |= 0x02;
                break;    
            case MIO_SHIFT0_IT_SEIE:
                MIO->SHIFTEIEN |= 0x01;
                break;
            case MIO_SHIFT1_IT_SEIE:
                MIO->SHIFTEIEN |= 0x02;
                break;
            case MIO_TIMER0_IT_TSIE:
                MIO->TIMIEN |= 0x01;
                break;
            case MIO_TIMER1_IT_TSIE:
                MIO->TIMIEN |= 0x02;
                break;
        }
    }
    else
    {
        switch (MIO_IT)
        {
            case MIO_SHIFT0_IT_SSIE:
                MIO->SHIFTSIEN &= ~(uint32_t)0x01;
                break;
            case MIO_SHIFT1_IT_SSIE:
                MIO->SHIFTSIEN &= ~(uint32_t)0x02;
                break;    
            case MIO_SHIFT0_IT_SEIE:
                MIO->SHIFTEIEN &= ~(uint32_t)0x01;
                break;
            case MIO_SHIFT1_IT_SEIE:
                MIO->SHIFTEIEN &= ~(uint32_t)0x02;
                break;
            case MIO_TIMER0_IT_TSIE:
                MIO->TIMIEN &= ~(uint32_t)0x01;
                break;
            case MIO_TIMER1_IT_TSIE:
                MIO->TIMIEN &= ~(uint32_t)0x02;
                break;
        }
    }
}

/**
  * @brief  获取MIO外设指定中断状态
  * @param  MIO_IT_t    SHIFT或者TIMER中断状态位
  * @retval SET or RESET
  */
ITStatus LHL_MIO_GetPending(MIO_IT_FLAG_t MIO_IT)
{
    uint32_t stat;
 
    switch (MIO_IT)
    {
        case MIO_SHIFT0_IT_FLAG_SSF:
            stat = (MIO->SHIFTSTAT & 0x01) && (MIO->SHIFTSIEN & 0x01);
            break;
        case MIO_SHIFT1_IT_FLAG_SSF:
            stat = (MIO->SHIFTSTAT & 0x02) && (MIO->SHIFTSIEN & 0x02);
            break;    
        case MIO_SHIFT0_IT_FLAG_SEF:
            stat = (MIO->SHIFTERR & 0x01) && (MIO->SHIFTEIEN & 0x01);
            break;
        case MIO_SHIFT1_IT_FLAG_SEF:
            stat = (MIO->SHIFTERR & 0x02) && (MIO->SHIFTEIEN & 0x02);
            break;
        case MIO_TIMER0_IT_FLAG_TSF:
            stat = (MIO->TIMSTAT & 0x01) && (MIO->TIMIEN & 0x01);
            break;
        case MIO_TIMER1_IT_FLAG_TSF:
            stat = (MIO->TIMSTAT & 0x02) && (MIO->TIMIEN & 0x02);
            break;
    }
        
   return (ITStatus)stat;
}

/**
  * @brief  清除MIO外设指定中断位
  * @param  MIO_IT_t    SHIFT或者TIMER中断状态位
  * @retval SET or RESET
  */
void LHL_MIO_ClearPending(MIO_IT_FLAG_t IT_FLAG)
{    
    switch (IT_FLAG)
    {
        case MIO_SHIFT0_IT_FLAG_SSF:
            MIO->SHIFTSTAT |= 0x01;
            break;
        case MIO_SHIFT1_IT_FLAG_SSF:
            MIO->SHIFTSTAT |= 0x02;
            break;    
        case MIO_SHIFT0_IT_FLAG_SEF:
            MIO->SHIFTERR |= 0x01;
            break;
        case MIO_SHIFT1_IT_FLAG_SEF:
            MIO->SHIFTERR |= 0x02;
            break;
        case MIO_TIMER0_IT_FLAG_TSF:
            MIO->TIMSTAT |= 0x01;
            break;
        case MIO_TIMER1_IT_FLAG_TSF:
            MIO->TIMSTAT |= 0x02;
            break;
    }
}

/**
  * @brief  获取MIO外设指定状态
  * @param  MIO_FLAG_t      MIO状态位
  * @retval SET or RESET
  */
FlagStatus LHL_MIO_GetFlag(MIO_FLAG_t MIO_FLAG)
{
    uint32_t stat;
 
    switch (MIO_FLAG)
    {
        case MIO_SHIFT0_FLAG_SSF:
            stat = MIO->SHIFTSTAT & 0x01;
            break;
        case MIO_SHIFT1_FLAG_SSF:
            stat = MIO->SHIFTSTAT & 0x02;
            break;    
        case MIO_SHIFT0_FLAG_SEF:
            stat = MIO->SHIFTERR & 0x01;
            break;
        case MIO_SHIFT1_FLAG_SEF:
            stat = MIO->SHIFTERR & 0x02;
            break;
        case MIO_TIMER0_FLAG_TSF:
            stat = MIO->TIMSTAT & 0x01;
            break;
        case MIO_TIMER1_FLAG_TSF:
            stat = MIO->TIMSTAT & 0x02;
            break;
    }
        
   return (FlagStatus)stat;
}

/*********************************End of File**********************************/
