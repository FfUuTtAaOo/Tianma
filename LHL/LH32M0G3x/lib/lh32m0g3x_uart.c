/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_uart.c
 * @version 2025-09-01
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  复位UART外设
  * @param  None                     
  * @retval None
  */
void LHL_UART_DeInit(void)
{ 
    // 通过RCC复位UART
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_UART0RST_Msk, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_UART0RST_Msk, DISABLE);
    
    // 禁用UART时钟
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_UART0EN_Msk, DISABLE);
}

/**
  * @brief  初始化UART外设
  * @param  pUARTx      x取值0或1 
  * @param  UART_Init   初始化参数结构体指针 
  * @retval LHL_OK      完成初始化
  */
LHL_StatusTypeDef LHL_UART_Init(UART_TypeDef* pUARTx, UART_InitTypeDef* UART_Init)
{
    uint16_t timeout = LHL_NRM_TIMEOUT;

    uint32_t freq, divider, remainder, temp;
    
    if (pUARTx == pUART0)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_UART0EN_Msk,ENABLE);//enable UART0 clock
        freq = LHL_RCC_GetPCLK2Freq();
    }
    else
    {
        RCC_APB1PeriphClockCmd(RCC_APB1ENR_UART1EN_Msk,ENABLE);//enable UART1 clock
        freq = LHL_RCC_GetPCLK1Freq();
    }

    /* ---------------------Configure the UART Baud Rate -------------------*/    
    /* Determine the divider and remainder */
    divider = (freq / 16) / (UART_Init->UART_BaudRate);
    
    remainder = (freq / 16) % (UART_Init->UART_BaudRate);     
    remainder = ((remainder * 16) + ((UART_Init->UART_BaudRate) / 2)) / (UART_Init->UART_BaudRate);
     
    // if reaminder>=16 ，then increase divider
    if (remainder >= 0x10)
    {
        divider++;
        remainder = remainder - 0x10;
    } 
    
    // Wait until NOT BUSY
    while (pUARTx->USR & 0x01)
    {
        if ((timeout--)==0) return LHL_TIMEOUT;
    }
    
    // Must Set DLAB first
    pUARTx->LCR |= UART_LCR_DLAB_Msk;
    
    pUARTx->RBR_THR_DLL = divider & 0xFF;
    pUARTx->IER_DLH = (divider >> 8) & 0xFF;
    pUARTx->DLF = remainder & 0x0F;

    /*----------------------- UART LCR Configuration -----------------------*/
    temp = 0;
    temp |= (uint32_t)UART_Init->UART_WordLength | UART_Init->UART_StopBits | UART_Init->UART_Parity;
    /* Write to UART LCR */
     pUARTx->LCR |= temp;
  
    // Must Clear DLAB when exiting
    pUARTx->LCR &= ~UART_LCR_DLAB_Msk;
    
    return LHL_OK;
}

/**
  * @brief  设置UART中断
  * @param  pUARTx      x取值0或1 
  * @param  UART_IT     specifies the UART interrupt sources to be enabled or disabled.
  *         @arg UART_IT_EDSSI 调制解调器状态中断使能
  *         @arg UART_IT_ELSI  接收线路状态中断使能
  *         @arg UART_IT_ETBEI TXE数据发送寄存器为空中断使能
  *         @arg UART_IT_ERBFI RXNE接收数据可用中断使能
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void LHL_UART_ITConfig(UART_TypeDef* pUARTx, uint32_t UART_IT, FunctionalState NewState)
{  
    if (NewState != DISABLE)
    {
        pUARTx->IER_DLH |= UART_IT;
    }
    else
    {
        pUARTx->IER_DLH &= ~UART_IT;
    }
}

/**
  * @brief  通过UART发送单个字节数据
  * @param  pUARTx      x取值0或1 
  * @param  Data        发送的单个字节数据
  * @retval None
  */
void LHL_UART_SendData(UART_TypeDef* pUARTx, uint8_t Data)
{   
    uint16_t t = 0xFFFF;
    
    pUARTx->RBR_THR_DLL = (uint32_t)Data;
    
    while((pUARTx->LSR & UART_FLAG_TEMT) == 0)
    {
        if ((t--) == 0) break;
    }
}

/**
  * @brief  通过UART接收单个字节数据
  * @param  pUARTx      x取值0或1
  * @retval 接收的单个字节数据
  */
uint8_t LHL_UART_ReceiveData(UART_TypeDef* pUARTx)
{
    uint16_t t = 0xFFFF;
    
    while((pUARTx->LSR & UART_FLAG_DR) == 0)
    {
        if ((t--) == 0) break;
    }
    
    return (uint8_t)pUARTx->RBR_THR_DLL;
}

/**
  * @brief  UART接收缓冲器Flush
  * @param  pUARTx      x取值0或1
  * @retval Null
  */
void LHL_UART_FlushData(UART_TypeDef* pUARTx)
{
    while((pUARTx->LSR & UART_FLAG_DR) != 0)
    {
        (void)pUARTx->RBR_THR_DLL; 
    }
}

/**
  * @brief  检查指定的UART标识是否设置
  * @param  pUARTx      x取值0或1 
  * @param  UART_FLAG   specifies the flag to check.
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus LHL_UART_GetFlag(UART_TypeDef* pUARTx, uint16_t UART_FLAG)
{
    FlagStatus bitstatus = RESET; 

    if ((pUARTx->LSR & UART_FLAG) != RESET)
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
  * @brief  deprecated
  */
//ITStatus LHL_UART_GetPending(UART_TypeDef* pUARTx, UART_IT_t UART_IT)
//{
//    FlagStatus bitstatus; 
//    
//    if ((pUARTx->IIR & UART_IT) != RESET)
//    {
//        bitstatus = SET;
//    }
//    else
//    {
//        bitstatus = RESET;
//    }

//  return bitstatus;
//}

/**
  * @brief  检查指定的UART中断标志是否设置
  * @param  pUARTx      x取值0或1 
  * @param  UART_IT     specifies the flag to check.
  * @retval The new state of UART_FLAG (SET or RESET).
  */
ITStatus LHL_UART_GetPending(UART_TypeDef* pUARTx, UART_IT_t UART_IT)
{
    FlagStatus bitstatus = RESET;
    
    switch (UART_IT)
    {
        case UART_IT_RXNE:
            if ((pUARTx->IER_DLH & UART_IER_DLH_ERBFI_Msk) && (pUARTx->LSR & UART_LSR_DR_Msk))
            {
                bitstatus = SET;
            }
            else
            {
                bitstatus = RESET;
            }
            break;
        case UART_IT_TXE:
            if ((pUARTx->IER_DLH & UART_IER_DLH_ETBEI_Msk) && (pUARTx->LSR & UART_LSR_THRE_Msk))
            {
                bitstatus = SET;
            }
            else
            {
                bitstatus = RESET;
            }
            break;
         case UART_IT_ERROR:
            if (pUARTx->LSR & (UART_LSR_BI_Msk | UART_LSR_FE_Msk | UART_LSR_PE_Msk | UART_LSR_OE_Msk))
            {
                bitstatus = SET;
            }
            else
            {
                bitstatus = RESET;
            }
            break;            
    }
    return bitstatus;
}

/**
  * @brief  使用UART阻塞模式发送一组数据
  * @param  pUARTx  x取值0或1
  * @param  pTxData 指向发送数据的指针
  * @param  Size    待发送的数据数量
  * @param  Timeout 超时设定
  * @retval OK：发送成功；ERROR：参数错误；TIMEOUT：发送超时。
  */
LHL_StatusTypeDef LHL_UART_Transmit(UART_TypeDef *pUARTx, const uint8_t* pTxData, uint16_t size, uint32_t Timeout)
{
    uint32_t t = Timeout;
    
    if (size == 0) return LHL_ERROR;        
    
    while (size--)
    {
        /* Transmit Data */
        pUARTx->RBR_THR_DLL = *pTxData++;
        
        while((pUARTx->LSR & UART_FLAG_THRE) == 0)
        {
            if ((t--) == 0) return LHL_TIMEOUT;
        }    
    }
    
    /* Wait until All Data is transmitted */
    while((pUARTx->LSR & UART_FLAG_TEMT) == 0)
    {
        if ((t--) == 0) return LHL_TIMEOUT;
    }
    
    return LHL_OK; 
}

/**
  * @brief  使用UART阻塞模式接收一组数据
  * @param  pUARTx  x取值0或1
  * @param  pTxData 指向接收数据的指针
  * @param  Size    待接收的数据数量
  * @param  Timeout 超时设定
  * @retval OK：接收成功；ERROR：参数错误；TIMEOUT：接收超时。
  */
LHL_StatusTypeDef LHL_UART_Receive(UART_TypeDef *pUARTx, uint8_t* pRxData, uint16_t size, uint32_t Timeout)
{
    uint32_t t = Timeout;
    
    if (size == 0) return LHL_ERROR;
    
    while (size--)
    {
        while ((pUARTx->LSR & UART_FLAG_DR) == 0)
        {
            if ((t--) == 0) return LHL_TIMEOUT;
        }
        
        /* Receive Data */
        *pRxData++ = (uint8_t)pUARTx->RBR_THR_DLL;
    }
    
    return LHL_OK;
}

/**
  * @brief  更新UART波特率
  * @param  pUARTx          UARTx外设指正，x取值0或1
  * @param  UART_BaudRate   UARTx波特率
  * @retval OK：更新成功；BUSY：设置超时。
  */
LHL_StatusTypeDef LHL_UART_SetBaudrate(UART_TypeDef* pUARTx, uint32_t UART_BaudRate)
{
    uint32_t timeout = LHL_LNG_TIMEOUT;

    uint32_t freq, divider, remainder;
    
    if (pUARTx == pUART0)
    {
        freq = LHL_RCC_GetPCLK2Freq();
    }
    else
    {
        freq = LHL_RCC_GetPCLK1Freq();
    }

    /* ---------------------Configure the UART Baud Rate -------------------*/    
    /* Determine the divider and remainder */
    divider = (freq / 16) / (UART_BaudRate);
    
    remainder = (freq / 16) % (UART_BaudRate);     
    remainder = ((remainder * 16) + ((UART_BaudRate) / 2)) / (UART_BaudRate);
     
    // if reaminder>=16 ，then increase divider
    if (remainder >= 0x10)
    {
        divider++;
        remainder = remainder - 0x10;
    } 
    
    // Wait until NOT BUSY
    while (pUARTx->USR & 0x01)
    {
        if ((timeout--)==0) return LHL_BUSY;
    }
    
    // Must Set DLAB first
    pUARTx->LCR |= UART_LCR_DLAB_Msk;
    
    pUARTx->RBR_THR_DLL = divider & 0xFF;
    pUARTx->IER_DLH = (divider >> 8) & 0xFF;
    pUARTx->DLF = remainder & 0x0F;
  
    // Must Clear DLAB when exiting
    pUARTx->LCR &= ~UART_LCR_DLAB_Msk;
    
    return LHL_OK;
}

/*********************************End of File**********************************/
