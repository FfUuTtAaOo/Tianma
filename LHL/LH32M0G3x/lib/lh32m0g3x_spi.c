/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_spi.c
 * @version 2025-09-15
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  复位SPIx外设到默认值
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @retval None
  */
void LHL_SPI_DeInit(SPI_TypeDef* SPIx)
{
    if (SPIx == pSPI0)
    {
        /* Reset SPI0 */
        RCC_APB2PeriphResetCmd(RCC_APB2RSTR_SPI0RST_Msk, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2RSTR_SPI0RST_Msk, DISABLE);
    
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_SPI0EN_Msk, DISABLE);
    }
    else
    {
        /* Reset SPI1 */
        RCC_APB1PeriphResetCmd(RCC_APB1RSTR_SPI1RST_Msk, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1RSTR_SPI1RST_Msk, DISABLE);
    
        RCC_APB1PeriphClockCmd(RCC_APB1ENR_SPI1EN_Msk, DISABLE);
    }
}

/**
  * @brief  初始化SPIx外设
  * @param  SPIx: where x can be 1or 2 to select the SPI peripheral.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
  *         contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void LHL_SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_Init)
{
    uint16_t tmpreg = 0;
    
    if (SPIx == pSPI0)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_SPI0EN_Msk, ENABLE);
    }
    else
    {    
        RCC_APB1PeriphClockCmd(RCC_APB1ENR_SPI1EN_Msk, ENABLE);
    }
    
    /* !!! 2025-09-04 SPI只能配置为16bit模式 */
    // 废弃
    // SPI_Init->DataSize = SPI_DataSize_16b;
  
    /*---------------------------- SPIx CR1 Configuration ------------------------*/
    /* Get the SPIx CR1 value */
    tmpreg = (uint16_t)SPIx->CR1;
    /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
    tmpreg &= SPI_CR1_CLEAR_Msk;
    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
     master/salve mode, CPOL and CPHA */
    /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
    /* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
    /* Set LSBFirst bit according to SPI_FirstBit value */
    /* Set BR bits according to SPI_BaudRatePrescaler value */
    /* Set CPOL bit according to SPI_CPOL value */
    /* Set CPHA bit according to SPI_CPHA value */
    tmpreg |= (uint16_t)((uint32_t)SPI_Init->Direction | \
                  SPI_Init->DataSize | SPI_Init->CPOL |  \
                  SPI_Init->CPHA | SPI_Init->NSS |  \
                  SPI_Init->BaudRatePrescaler | SPI_Init->FirstBit);
    /* Write to SPIx CR1 */
    SPIx->CR1 = tmpreg;
    
    tmpreg |= (uint16_t)SPI_Init->Mode;
    /* SPI MODE需要二次写入CR1寄存器 */
    SPIx->CR1 = tmpreg;

//    /*reserved---------------------------- SPIx CRCPOLY Configuration --------------------*/
//    /* Write to SPIx CRCPOLY */
//    SPIx->CRCPR = SPI_Init->CRCPolynomial;
    
    /* 使能SPIx */
    SPIx->CR1 |= SPI_CR1_SPE_Msk;
}

/**
  * @brief  使能或禁用SPIx外设
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void LHL_SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the selected SPI peripheral */
        SPIx->CR1 |= SPI_CR1_SPE_Msk;
    }
    else
    {
        /* Disable the selected SPI peripheral */
        SPIx->CR1 &= ~SPI_CR1_SPE_Msk;
    }
}

/**
  * @brief  使能或禁用SPIx中断
  * @param  SPIx: where x can be 1 or 2
  * @param  SPI_I2S_IT: specifies the SPI/I2S interrupt source to be enabled or disabled. 
  *   This parameter can be one of the following values:
  *     @arg SPI_IT_TXE: Tx buffer empty interrupt mask
  *     @arg SPI_IT_RXNE: Rx buffer not empty interrupt mask
  *     @arg SPI_IT_ERR: Error interrupt mask
  * @param  NewState: new state of the specified SPI/I2S interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState)
{
    uint16_t itpos = 0, itmask = 0 ;

    /* Get the SPI/I2S IT index */
    itpos = SPI_IT >> 4;

    /* Set the IT mask */
    itmask = (uint16_t)(1 << itpos);

    if (NewState != DISABLE)
    {
        /* Enable the selected SPI interrupt */
        SPIx->CR2 |= itmask;
    }
    else
    {
        /* Disable the selected SPI interrupt */
        SPIx->CR2 &= (uint16_t)~itmask;
    }
}

/**
  * @brief  Enables or disables the SPIx/I2Sx DMA interface.
  * @param  SPIx: where x can be
  *   - 1 or 2 in SPI mode 
  *   - 2 or 3 in I2S mode
  * @param  SPI_I2S_DMAReq: specifies the SPI/I2S DMA transfer request to be enabled or disabled. 
  *   This parameter can be any combination of the following values:
  *     @arg SPI_I2S_DMAReq_Tx: Tx buffer DMA transfer request
  *     @arg SPI_I2S_DMAReq_Rx: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected SPI/I2S DMA transfer request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
//void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)
//{
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  assert_param(IS_FUNCTIONAL_STATE(NewState));
//  assert_param(IS_SPI_I2S_DMAREQ(SPI_I2S_DMAReq));
//  if (NewState != DISABLE)
//  {
//    /* Enable the selected SPI/I2S DMA requests */
//    SPIx->CR2 |= SPI_I2S_DMAReq;
//  }
//  else
//  {
//    /* Disable the selected SPI/I2S DMA requests */
//    SPIx->CR2 &= (uint16_t)~SPI_I2S_DMAReq;
//  }
//}

/**
  * @brief  通过SPIx外设发送1个Half-word数据
  * @param  SPIx: where x can be 1 or 2
  * @param  Data : Data to be transmitted.
  * @retval None
  */
void LHL_SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data)
{ 
    /* Write in the DR register the data to be sent */
    SPIx->DR = Data;
}

/**
  * @brief  通过SPIx外设接收1个Half-word数据
  * @param  SPIx: where x can be 1 or 2.
  * @retval The value of the received data.
  */
uint16_t LHL_SPI_ReceiveData(SPI_TypeDef* SPIx)
{  
    /* Return the data in the DR register */
    return (uint16_t)SPIx->DR;
}

/**
  * @brief  全双工SPIx接收和发送函数
  * @param  SPIx        where x can be 1 or 2.
  *         pTxData     待发送数据缓存区指针
  *         pRxData     待接收数据缓存区指针
  *         Size        收发数据数量
  *         Timeout     超时设置
  * @retval LHL_OK：收发成功；LHL_TIMEOUT：收发超时。
  */
/**
  * @brief  deprecated
  */
//LHL_StatusTypeDef LHL_SPI_TransmitReceive(SPI_TypeDef *SPIx, const uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
//{   
//    uint16_t tmp;
//    
//    // Check if Size>0
//    if (Size == 0) return LHL_ERROR;

//    /* !!! 2025-09-04 SPI只能配置为16bit模式 */    
//    Size = Size / 2;            /* !!! 暂时配置为16bit发送接收 */

//    while (Size--)
//    {
//        while ((SPIx->SR & SPI_FLAG_TXE) == RESET)
//        {
//            if ((Timeout--) == 0) return LHL_TIMEOUT;
//        }
//        tmp = (uint16_t)(*pTxData << 8);      /* !!! */
//        pTxData += sizeof(uint8_t);
//        tmp |= (uint16_t)*pTxData;          /* !!! */
//        pTxData += sizeof(uint8_t);
//        
//        SPIx->DR = tmp;

//        while ((SPIx->SR & SPI_FLAG_RXNE) == RESET)
//        {
//            if ((Timeout--) == 0) return LHL_TIMEOUT;
//        }
//        tmp = (uint16_t)SPIx->DR;
//        *pRxData = tmp >> 8;                /* !!! */
//        pRxData += sizeof(uint8_t);
//        *pRxData = tmp & 0xFF;
//        pRxData += sizeof(uint8_t);        
//    }
//    
//    while ((SPIx->SR & SPI_FLAG_BSY) ==  SET)
//    {
//        if ((Timeout--) == 0) return LHL_TIMEOUT;
//    }
//    
//    return LHL_OK;
//}

LHL_StatusTypeDef LHL_SPI_TransmitReceive(SPI_TypeDef *SPIx, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout)
{
    uint16_t rx16;
    
    if (SPIx->CR1 & SPI_CR1_DFF_Msk)
    {
        /* 使用16位数据帧格式 */
        for (uint32_t i = 0; i < Size; i++) 
        {
            while ((SPIx->SR & SPI_FLAG_TXE) == RESET)
            {
                if ((--Timeout) == 0) return LHL_TIMEOUT;
            }            
            SPIx->DR = (uint32_t)pTxData[0] | ((uint32_t)pTxData[1] << 8);      // ARM默认小端序
            pTxData += sizeof(uint16_t);

            while ((SPIx->SR & SPI_FLAG_RXNE) == RESET)
            {
                if ((--Timeout) == 0) return LHL_TIMEOUT;
            }            
            rx16 = (uint16_t)SPIx->DR;
            *pRxData++ = (uint8_t)rx16;
            *pRxData++ = (uint8_t)(rx16 >> 8);  
        }
    }
    else
    {
        /* 使用8位数据帧格式 */
        for (uint32_t i = 0; i < Size; i++)
        {
            while ((SPIx->SR & SPI_FLAG_TXE) == RESET)
            {
                if ((--Timeout) == 0) return LHL_TIMEOUT;
            }
            SPIx->DR = *pTxData++;

            while ((SPIx->SR & SPI_FLAG_RXNE) == RESET)
            {
                if ((--Timeout) == 0) return LHL_TIMEOUT;
            }
            *pRxData++ = (uint8_t)SPIx->DR;   
        }
    }

    /* 等待传输完成 */
    while ((SPIx->SR & SPI_FLAG_TXE) ==  RESET)
    {
        if ((--Timeout) == 0) return LHL_TIMEOUT;
    }
    
    while ((SPIx->SR & SPI_FLAG_BSY) ==  SET)
    {
        if ((--Timeout) == 0) return LHL_TIMEOUT;
    }
    
    return LHL_OK;
}

/**
  * @brief  Configures internally by software the NSS pin for the selected SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @param  SPI_NSSInternalSoft: specifies the SPI NSS internal state.
  *   This parameter can be one of the following values:
  *     @arg SPI_NSSInternalSoft_Set: Set NSS pin internally
  *     @arg SPI_NSSInternalSoft_Reset: Reset NSS pin internally
  * @retval None
  */
//void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft)
//{
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));
//  if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
//  {
//    /* Set NSS pin internally by software */
//    SPIx->CR1 |= SPI_NSSInternalSoft_Set;
//  }
//  else
//  {
//    /* Reset NSS pin internally by software */
//    SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
//  }
//}

/**
  * @brief  Enables or disables the SS output for the selected SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx SS output. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
//void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
//{
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  assert_param(IS_FUNCTIONAL_STATE(NewState));
//  if (NewState != DISABLE)
//  {
//    /* Enable the selected SPI SS output */
//    SPIx->CR2 |= CR2_SSOE_Set;
//  }
//  else
//  {
//    /* Disable the selected SPI SS output */
//    SPIx->CR2 &= CR2_SSOE_Reset;
//  }
//}

/**
  * @brief  Configures the data size for the selected SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @param  SPI_DataSize: specifies the SPI data size.
  *   This parameter can be one of the following values:
  *     @arg SPI_DataSize_16b: Set data frame format to 16bit
  *     @arg SPI_DataSize_8b: Set data frame format to 8bit
  * @retval None
  */
//void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize)
//{
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  assert_param(IS_SPI_DATASIZE(SPI_DataSize));
//  /* Clear DFF bit */
//  SPIx->CR1 &= (uint16_t)~SPI_DataSize_16b;
//  /* Set new DFF bit value */
//  SPIx->CR1 |= SPI_DataSize;
//}

/**
  * @brief  Transmit the SPIx CRC value.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @retval None
  */
//void SPI_TransmitCRC(SPI_TypeDef* SPIx)
//{
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  
//  /* Enable the selected SPI CRC transmission */
//  SPIx->CR1 |= CR1_CRCNext_Set;
//}

/**
  * @brief  Enables or disables the CRC value calculation of the transferred bytes.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx CRC value calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
//void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState)
//{

//  if (NewState != DISABLE)
//  {
//    /* Enable the selected SPI CRC calculation */
//    SPIx->CR1 |= CR1_CRCEN_Set;
//  }
//  else
//  {
//    /* Disable the selected SPI CRC calculation */
//    SPIx->CR1 &= CR1_CRCEN_Reset;
//  }
//}

/**
  * @brief  Returns the transmit or the receive CRC register value for the specified SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @param  SPI_CRC: specifies the CRC register to be read.
  *   This parameter can be one of the following values:
  *     @arg SPI_CRC_Tx: Selects Tx CRC register
  *     @arg SPI_CRC_Rx: Selects Rx CRC register
  * @retval The selected CRC register value..
  */
//uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC)
//{
//  uint16_t crcreg = 0;
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  assert_param(IS_SPI_CRC(SPI_CRC));
//  if (SPI_CRC != SPI_CRC_Rx)
//  {
//    /* Get the Tx CRC register */
//    crcreg = SPIx->TXCRCR;
//  }
//  else
//  {
//    /* Get the Rx CRC register */
//    crcreg = SPIx->RXCRCR;
//  }
//  /* Return the selected CRC register */
//  return crcreg;
//}

/**
  * @brief  Returns the CRC Polynomial register value for the specified SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @retval The CRC Polynomial register value.
  */
//uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx)
//{
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  
//  /* Return the CRC polynomial register */
//  return SPIx->CRCPR;
//}

/**
  * @brief  Selects the data transfer direction in bi-directional mode for the specified SPI.
  * @param  SPIx: where x can be 1 or 2 to select the SPI peripheral.
  * @param  SPI_Direction: specifies the data transfer direction in bi-directional mode. 
  *   This parameter can be one of the following values:
  *     @arg SPI_Direction_Tx: Selects Tx transmission direction
  *     @arg SPI_Direction_Rx: Selects Rx receive direction
  * @retval None
  */
//void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction)
//{
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  assert_param(IS_SPI_DIRECTION(SPI_Direction));
//  if (SPI_Direction == SPI_Direction_Tx)
//  {
//    /* Set the Tx only mode */
//    SPIx->CR1 |= SPI_Direction_Tx;
//  }
//  else
//  {
//    /* Set the Rx only mode */
//    SPIx->CR1 &= SPI_Direction_Rx;
//  }
//}

/**
  * @brief  检查SPIx指定标志是否置位
  * @param  SPIx: where x can be 1 or 2
  * @param  SPI_FLAG: specifies the SPI flag to check:
  *     @arg SPI_FLAG_TXE: Transmit buffer empty flag.
  *     @arg SPI_FLAG_RXNE: Receive buffer not empty flag.
  *     @arg SPI_FLAG_BSY: Busy flag.
  *     @arg SPI_FLAG_OVR: Overrun flag.
  *     @arg SPI_FLAG_MODF: Mode Fault flag.
  *     @arg SPI_FLAG_CRCERR: CRC Error flag.
  * @retval The new state of SPI_FLAG (SET or RESET).
  */
FlagStatus LHL_SPI_GetFlag(SPI_TypeDef* SPIx, uint16_t SPI_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the status of the specified SPI flag */
    if ((SPIx->SR & SPI_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return  bitstatus;
}

/**
  * @brief  Clears the SPIx CRC Error (CRCERR) flag.
  * @param  SPIx: where x can be
  *   - 1 or 2 in SPI mode 
  * @param  SPI_I2S_FLAG: specifies the SPI flag to clear. 
  *   This function clears only CRCERR flag.
  * @note
  *   - OVR (OverRun error) flag is cleared by software sequence: a read 
  *     operation to SPI_DR register (SPI_I2S_ReceiveData()) followed by a read 
  *     operation to SPI_SR register (SPI_I2S_GetFlagStatus()).
  *   - UDR (UnderRun error) flag is cleared by a read operation to 
  *     SPI_SR register (SPI_I2S_GetFlagStatus()).
  *   - MODF (Mode Fault) flag is cleared by software sequence: a read/write 
  *     operation to SPI_SR register (SPI_I2S_GetFlagStatus()) followed by a 
  *     write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
  * @retval None
  */
//void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
//{
//  /* Check the parameters */
//  assert_param(IS_SPI_ALL_PERIPH(SPIx));
//  assert_param(IS_SPI_I2S_CLEAR_FLAG(SPI_I2S_FLAG));
//    
//    /* Clear the selected SPI CRC Error (CRCERR) flag */
//    SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
//}

/**
  * @brief  检查SPI指定中断标志是否置位
  * @param  SPIx: where x can be 1 or 2 
  * @param  SPI_IT: specifies the SPI interrupt source to check. 
  *   This parameter can be one of the following values:
  *     @arg SPI_IT_TXE: Transmit buffer empty interrupt.
  *     @arg SPI_IT_RXNE: Receive buffer not empty interrupt.
  *     @arg SPI_IT_OVR: Overrun interrupt.
  *     @arg SPI_IT_MODF: Mode Fault interrupt.
  *     @arg SPI_IT_CRCERR: CRC Error interrupt.
  * @retval The new state of SPI_IT (SET or RESET).
  */
ITStatus LHL_SPI_GetPending(SPI_TypeDef* SPIx, uint8_t SPI_IT)
{
    ITStatus bitstatus = RESET;
    uint16_t itpos = 0, itmask = 0, enablestatus = 0;

    /* Get the SPI IT index */
    itpos = (uint16_t)(0x01 << (SPI_IT & 0x0F));

    /* Get the SPI IT mask */
    itmask = SPI_IT >> 4;

    /* Set the IT mask */
    itmask = (uint16_t)(0x01 << itmask);

    /* Get the SPI_IT enable bit status */
    enablestatus = (SPIx->CR2 & itmask) ;

    /* Check the status of the specified SPI interrupt */
    if (((SPIx->SR & itpos) != (uint16_t)RESET) && enablestatus)
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
  * @brief  清除SPIx指定中断标志
  * @param  SPIx: where x can be 1 or 2 
  * @param  SPI_IT: specifies the SPI interrupt pending bit to clear.
  *   This function clears only CRCERR interrupt pending bit.   
  * @note
  *   - OVR (OverRun Error) interrupt pending bit is cleared by software sequence: 
  *     a read operation to SPI_DR register followed by a read operation to SPI_SR register.
  *
  *   - UDR (UnderRun Error) interrupt pending bit is cleared by a read operation to SPI_SR register.
  *
  *   - MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
  *     a read/write operation to SPI_SR register followed by a write operation to SPI_CR1 register.
  * @retval None
  */
void LHL_SPI_ClearPending(SPI_TypeDef* SPIx, uint8_t SPI_IT)
{
    uint16_t itpos = 0;

    /* Get the SPI IT index */
    itpos = (uint16_t)(0x01 << (SPI_IT & 0x0F));

    /* Clear the selected SPI Error (CRCERR) interrupt pending bit */
    SPIx->SR = (uint16_t)~itpos;
}

/*********************************End of File**********************************/
