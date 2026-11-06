/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_spi.h
 * @version 2025-09-15
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_SPI_H
#define __LH32M0G3x_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Defines -------------------------------------------------------------------*/
/** 
  * @brief  SPI_Private_Defines  
  */
#define SPI_CR1_CLEAR_Msk       ((uint16_t)0x3040)

/** @defgroup SPI_data_direction 
  * @{
  */
typedef enum {
    SPI_DIR_2LINES_FULLDUPLEX       = ((uint16_t)0x0000),
    SPI_DIR_2LINES_RXONLY           = ((uint16_t)0x0400),
    SPI_DIR_1LINE_RX                = ((uint16_t)0x8000),
    SPI_DIR_1LINE_TX                = ((uint16_t)0xC000),
} SPI_DIRECTION_t;
/**
  * @}
  */

/** @defgroup SPI_mode 
  * @{
  */
typedef enum {
    SPI_MODE_MASTER                 = ((uint16_t)0x0104),
    SPI_MODE_SLAVE                  = ((uint16_t)0x0000),
} SPI_MODE_t;
/**
  * @}
  */

/** @defgroup SPI_data_size 
  * @{
  */
typedef enum {
    SPI_DATASIZE_16BIT              = ((uint16_t)0x0800),
    SPI_DATASIZE_8BIT               = ((uint16_t)0x0000),
} SPI_DATASIZE_t;
/**
  * @}
  */ 

/** @defgroup SPI_Clock_Polarity 
  * @{
  */
typedef enum {
    SPI_CPOL_LOW                    = ((uint16_t)0x0000),
    SPI_CPOL_HIGH                   = ((uint16_t)0x0002),
} SPI_CPOL_t;
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase 
  * @{
  */
typedef enum {
    SPI_CPHA_1EDGE                  = ((uint16_t)0x0000),
    SPI_CPHA_2EDGE                  = ((uint16_t)0x0001),
} SPI_CPHA_t;
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management 
  * @{
  */
typedef enum {
    SPI_NSS_SOFT                    = ((uint16_t)0x0200),
    SPI_NSS_HARD                    = ((uint16_t)0x0000),
} SPI_NSS_t;
/**
  * @}
  */ 

/** @defgroup SPI_BaudRate_Prescaler 
  * @{
  */
typedef enum {  
    SPI_BAUDRATE_PSC_2              = ((uint16_t)0x0000),
    SPI_BAUDRATE_PSC_4              = ((uint16_t)0x0008),
    SPI_BAUDRATE_PSC_8              = ((uint16_t)0x0010),
    SPI_BAUDRATE_PSC_16             = ((uint16_t)0x0018),
    SPI_BAUDRATE_PSC_32             = ((uint16_t)0x0020),
    SPI_BAUDRATE_PSC_64             = ((uint16_t)0x0028),
    SPI_BAUDRATE_PSC_128            = ((uint16_t)0x0030),
    SPI_BAUDRATE_PSC_256            = ((uint16_t)0x0038),
}SPI_BAUDRATE_t;
/**
  * @}
  */ 

/** @defgroup SPI_MSB_LSB_transmission 
  * @{
  */
typedef enum {  
    SPI_FIRSTBIT_MSB                = ((uint16_t)0x0000),
    SPI_FIRSTBIT_LSB                = ((uint16_t)0x0080),
} SPI_FIRSTBIT_t;
/**
  * @}
  */
  
/** 
  * @brief  SPI Init structure definition  
  */
typedef struct {

    SPI_DIRECTION_t Direction;          /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

    SPI_MODE_t Mode;                    /*!< Specifies the SPI operating mode.
                                         This parameter can be a value of @ref SPI_mode */

    SPI_DATASIZE_t DataSize;            /*!< 设置SPI数据帧格式：8位或16位
                                         This parameter can be a value of @ref SPI_data_size */

    SPI_CPOL_t CPOL;                    /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

    SPI_CPHA_t CPHA;                    /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

    SPI_NSS_t NSS;                      /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */
 
    SPI_BAUDRATE_t BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

    SPI_FIRSTBIT_t FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */
                                         
//  FunctionalState CRC;                /*!< Reserved. */
//  
//  uint16_t CRCPolynomial;             /*!< Specifies the polynomial used for the CRC calculation. */
  
} SPI_InitTypeDef;
/**
  * @}
  */





/** @defgroup SPI_DMA_transfer_requests 
  * @{
  */
#define SPI_DMAReq_Tx               ((uint16_t)0x0002)
#define SPI_DMAReq_Rx               ((uint16_t)0x0001)
/**
  * @}
  */

/** @defgroup SPI_NSS_internal_software_management 
  * @{
  */
#define SPI_NSSInternalSoft_Set     ((uint16_t)0x0100)
#define SPI_NSSInternalSoft_Reset   ((uint16_t)0xFEFF)
/**
  * @}
  */

/** @defgroup SPI_CRC_Transmit_Receive 
  * @{
  */
#define SPI_CRC_Tx                  ((uint8_t)0x00)
#define SPI_CRC_Rx                  ((uint8_t)0x01)
/**
  * @}
  */

/** @defgroup SPI_direction_transmit_receive 
  * @{
  */
#define SPI_Direction_Rx            ((uint16_t)0xBFFF)
#define SPI_Direction_Tx            ((uint16_t)0x4000)
/**
  * @}
  */

/** @defgroup SPI_interrupts_definition 
  * @{
  */
#define SPI_IT_TXE                  ((uint8_t)0x71)
#define SPI_IT_RXNE                 ((uint8_t)0x60)
#define SPI_IT_ERR                  ((uint8_t)0x50)

#define SPI_IT_OVR                  ((uint8_t)0x56)
#define SPI_IT_MODF                 ((uint8_t)0x55)
#define SPI_IT_CRCERR               ((uint8_t)0x54)
/**
  * @}
  */

/** @defgroup SPI_flags_definition 
  * @{
  */
#define SPI_FLAG_RXNE               ((uint16_t)0x0001)
#define SPI_FLAG_TXE                ((uint16_t)0x0002)

#define SPI_FLAG_CRCERR             ((uint16_t)0x0010)
#define SPI_FLAG_MODF               ((uint16_t)0x0020)
#define SPI_FLAG_OVR                ((uint16_t)0x0040)
#define SPI_FLAG_BSY                ((uint16_t)0x0080)
/**
  * @}
  */

/* Function Prototypes -------------------------------------------------------*/

/** @defgroup SPI_Exported_Functions
  * @{
  */
void                LHL_SPI_DeInit(SPI_TypeDef* pSPIx);
void                LHL_SPI_Init(SPI_TypeDef* pSPIx, SPI_InitTypeDef* SPI_Init);

void                LHL_SPI_Cmd(SPI_TypeDef* pSPIx, FunctionalState NewState);

void                LHL_SPI_ITConfig(SPI_TypeDef* pSPIx, uint8_t SPI_IT, FunctionalState NewState);
ITStatus            LHL_SPI_GetPending(SPI_TypeDef* SPIx, uint8_t SPI_IT);
void                LHL_SPI_ClearPending(SPI_TypeDef* SPIx, uint8_t SPI_IT);

void                LHL_SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t            LHL_SPI_ReceiveData(SPI_TypeDef* SPIx);

LHL_StatusTypeDef   LHL_SPI_Transmit(SPI_TypeDef *pSPIx, uint8_t* pTxData, uint16_t size, uint32_t Timeout);
LHL_StatusTypeDef   LHL_SPI_Receive(SPI_TypeDef *pSPIx, uint8_t* pRxData, uint16_t size, uint32_t Timeout);
LHL_StatusTypeDef   LHL_SPI_TransmitReceive(SPI_TypeDef *SPIx, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout);

FlagStatus          LHL_SPI_GetFlag(SPI_TypeDef* pSPIx, uint16_t SPI_FLAG);

#define LHL_SPI_ReadData(pSPIx)           ((pSPIx)->DR)
#define LHL_SPI_WriteData(pSPIx, Data)    (((pSPIx)->DR) = (Data))

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
