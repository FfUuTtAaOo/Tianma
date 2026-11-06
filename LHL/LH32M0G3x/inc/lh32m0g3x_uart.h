/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_uart.h
 * @version 2025-09-01
 ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_UART_H
#define __LH32M0G3x_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"
     
/* Defines -------------------------------------------------------------------*/
/** 
  * @brief  UART Init Structure definition  
  */   
typedef struct
{
    uint32_t UART_BaudRate;            /*!< This member configures the UART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (UART_InitStruct->UART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

    uint16_t UART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */

    uint16_t UART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits */

    uint16_t UART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
    uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control */
} 
UART_InitTypeDef;

/** @defgroup UART_Word_Length 
  * @{
  */ 
#define UART_WordLength_5b                  ((uint32_t)0x00000000)
#define UART_WordLength_6b                  ((uint32_t)0x00000001)
#define UART_WordLength_7b                  ((uint32_t)0x00000002)
#define UART_WordLength_8b                  ((uint32_t)0x00000003)

/** @defgroup UART_Stop_Bits 
  * @{
  */ 
#define UART_StopBits_1                     ((uint32_t)0x00000000)
#define UART_StopBits_2                     ((uint32_t)0x00000004)
#define UART_StopBits_1_5                   ((uint32_t)0x00000004)


/** @defgroup UART_Parity 
  * @{
  */ 
#define UART_Parity_Even                    ((uint32_t)0x00000018) 
#define UART_Parity_Odd                     ((uint32_t)0x00000008) 
#define UART_Parity_None                    ((uint32_t)0x00000000)
 

/** @defgroup UART_Interrupt_definition 
  * @{
  */
#define UART_IT_EDSSI                       ((uint32_t)0x08)    //调制解调器状态中断使能
#define UART_IT_ELSI                        ((uint32_t)0x04)    //接收线路状态中断使能
#define UART_IT_ETBEI                       ((uint32_t)0x02)    //TXE数据发送寄存器为空中断使能
#define UART_IT_ERBFI                       ((uint32_t)0x01)    //RXNE接收数据可用中断使能

/** @defgroup UART_Flags 
  * @{
  */

#define UART_FLAG_TEMT                      ((uint32_t)0x40)
#define UART_FLAG_THRE                      ((uint32_t)0x20)
#define UART_FLAG_FE                        ((uint32_t)0x08)
#define UART_FLAG_PE                        ((uint32_t)0x04)
#define UART_FLAG_OE                        ((uint32_t)0x02)
#define UART_FLAG_DR                        ((uint32_t)0x01)

/** 
  * @brief  UART_Interrupt_Enum
  */
typedef enum {
    UART_IT_TXE         =   ((uint32_t)0x02),
    UART_IT_RXNE        =   ((uint32_t)0x04),
    UART_IT_ERROR       =   ((uint32_t)0x06),
} UART_IT_t;

/* Declaration ---------------------------------------------------------------*/
/** @defgroup UART_Exported_Functions
  * @{
  */
LHL_StatusTypeDef LHL_UART_Init(UART_TypeDef* pUARTx, UART_InitTypeDef* UART_Init);

void LHL_UART_ITConfig(UART_TypeDef* pUARTx, uint32_t UART_IT, FunctionalState NewState);

FlagStatus LHL_UART_GetFlag(UART_TypeDef* pUARTx, uint16_t UART_FLAG);

ITStatus LHL_UART_GetPending(UART_TypeDef* pUARTx, UART_IT_t UART_IT);

LHL_StatusTypeDef LHL_UART_Transmit(UART_TypeDef *pUARTx, const uint8_t* pTxData, uint16_t size, uint32_t Timeout);

LHL_StatusTypeDef LHL_UART_Receive(UART_TypeDef *pUARTx, uint8_t* pRxData, uint16_t size, uint32_t Timeout);

void LHL_UART_SendData(UART_TypeDef* pUARTx, uint8_t Data);

uint8_t LHL_UART_ReceiveData(UART_TypeDef* pUARTx);

LHL_StatusTypeDef LHL_UART_SetBaudrate(UART_TypeDef* pUARTx, uint32_t UART_BaudRate);

void LHL_UART_DeInit(void);
void LHL_UART_FlushData(UART_TypeDef* pUARTx);

#define LHL_UART_GetITStatus(pUARTx)        ((uint8_t)((pUARTx)->IIR))
#define LHL_UART_ReadData(pUARTx)           ((uint8_t)((pUARTx)->RBR_THR_DLL))
#define LHL_UART_WriteData(pUARTx, Data)    (((pUARTx)->RBR_THR_DLL) = (Data))

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
