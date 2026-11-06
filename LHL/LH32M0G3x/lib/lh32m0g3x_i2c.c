/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_i2c.c
 * @version 2025-09-15
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Private Definition ---------------------------------------------------------*/
//#define EEPROM_ADDRESS_16_BIT     /* 若使用M24C32等16位地址的芯片则需启用此项定义*/

/* I2C SPE mask */
#define CR1_PE_Set              ((uint16_t)0x0001)
#define CR1_PE_Reset            ((uint16_t)0xFFFE)

/* I2C START mask */
#define CR1_START_Set           ((uint16_t)0x0100)
#define CR1_START_Reset         ((uint16_t)0xFEFF)

/* I2C STOP mask */
#define CR1_STOP_Set            ((uint16_t)0x0200)
#define CR1_STOP_Reset          ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CR1_ACK_Set             ((uint16_t)0x0400)
#define CR1_ACK_Reset           ((uint16_t)0xFBFF)

/* I2C ENGC mask */
#define CR1_ENGC_Set            ((uint16_t)0x0040)
#define CR1_ENGC_Reset          ((uint16_t)0xFFBF)

/* I2C SWRST mask */
#define CR1_SWRST_Set           ((uint16_t)0x8000)
#define CR1_SWRST_Reset         ((uint16_t)0x7FFF)

/* I2C PEC mask */
#define CR1_PEC_Set             ((uint16_t)0x1000)
#define CR1_PEC_Reset           ((uint16_t)0xEFFF)

/* I2C ENPEC mask */
#define CR1_ENPEC_Set           ((uint16_t)0x0020)
#define CR1_ENPEC_Reset         ((uint16_t)0xFFDF)

/* I2C NOSTRETCH mask */
#define CR1_NOSTRETCH_Set       ((uint16_t)0x0080)
#define CR1_NOSTRETCH_Reset     ((uint16_t)0xFF7F)

/* I2C registers Masks */
#define CR1_CLEAR_Mask          ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CR2_DMAEN_Set           ((uint16_t)0x0800)
#define CR2_DMAEN_Reset         ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CR2_LAST_Set            ((uint16_t)0x1000)
#define CR2_LAST_Reset          ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CR2_FREQ_Reset          ((uint16_t)0xFFC0)

/* I2C ADD0 mask */
#define OAR1_ADD0_Set           ((uint16_t)0x0001)
#define OAR1_ADD0_Reset         ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OAR2_ENDUAL_Set         ((uint16_t)0x0001)
#define OAR2_ENDUAL_Reset       ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OAR2_ADD2_Reset         ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CCR_FS_Set              ((uint16_t)0x8000)

/* I2C CCR mask */
#define CCR_CCR_Set             ((uint16_t)0x0FFF)

/* I2C FLAG mask */
#define FLAG_Mask               ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define ITEN_Mask               ((uint32_t)0x07000000)

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  复位I2C外设到默认状态
  * @param  None
  * @retval None
  */
void LHL_I2C_DeInit(void)
{
    /* Enable I2C reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1RSTR_I2CRST_Msk, ENABLE);
    /* Release I2C from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1RSTR_I2CRST_Msk, DISABLE);
    
    /* Disable I2C clock */
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_I2CEN_Msk, DISABLE);
}

/**
  * @brief  初始化I2C外设
  * @param  I2C_InitStruct  初始化参数指针
  * @retval None
  */
void LHL_I2C_Init(I2C_HandleTypeDef* handle)
{
    uint16_t tmpreg = 0, freqrange = 0;
    uint16_t result = 0x04;
    uint32_t pclk1 = 8000000;
    /* 使能I2C时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_I2CEN_Msk, ENABLE);

    /*---------------------------- I2Cx CR2 Configuration ------------------------*/
    /* Get the I2Cx CR2 value */
    tmpreg = pI2C->CR2;
    /* Clear frequency FREQ[5:0] bits */
    tmpreg &= CR2_FREQ_Reset;
    /* Get pclk1 frequency value */
    pclk1 = LHL_RCC_GetPCLK1Freq();
    /* Set frequency bits depending on pclk1 value */
    freqrange = (uint16_t)(pclk1 / 1000000);
    tmpreg |= freqrange;
    /* Write to pI2C CR2 */
    pI2C->CR2 = tmpreg;

    /*---------------------------- I2Cx CCR Configuration ------------------------*/
    /* Disable the selected I2C peripheral to configure TRISE */
    pI2C->CR1 &= CR1_PE_Reset;
    /* Reset tmpreg value */
    /* Clear F/S, DUTY and CCR[11:0] bits */
    tmpreg = 0;

    /* Configure speed in standard mode */
    if (handle->Init.Speed <= 100000)
    {
        /* Standard mode speed calculate */
        result = (uint16_t)(pclk1 / (handle->Init.Speed << 1));
        /* Test if CCR value is under 0x4*/
        if (result < 0x04)
        {
            /* Set minimum allowed value */
            result = 0x04;  
        }
        /* Set speed value for standard mode */
        tmpreg |= result;      
        /* Set Maximum Rise Time for standard mode */
        pI2C->TRISE = freqrange + 1; 
    }
    /* Configure speed in fast mode */
    else /*(I2C_InitStruct->I2C_ClockSpeed <= 400000)*/
    {
        /* 不设置DutyCycle */
//        if (I2C_InitStruct->DutyCycle == I2C_DutyCycle_2)
//        {
//            /* Fast mode speed calculate: Tlow/Thigh = 2 */
//            result = (uint16_t)(pclk1 / (I2C_InitStruct->ClockSpeed * 3));
//        }
//        else /*I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_16_9*/
//        {
//            /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
//            result = (uint16_t)(pclk1 / (I2C_InitStruct->ClockSpeed * 25));
//            /* Set DUTY bit */
//            result |= I2C_DutyCycle_16_9;
//        }
        result = (uint16_t)(pclk1 / (handle->Init.Speed * 3));
        /* Test if CCR value is under 0x1*/
        if ((result & CCR_CCR_Set) == 0)
        {
            /* Set minimum allowed value */
            result |= (uint16_t)0x0001;  
        }
        /* Set speed value and set F/S bit for fast mode */
        tmpreg |= (uint16_t)(result | CCR_FS_Set);
        /* Set Maximum Rise Time for fast mode */
        pI2C->TRISE = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);  
    }

    /* Write to I2Cx CCR */
    pI2C->CCR = tmpreg;
    /* Enable the selected I2C peripheral */
    pI2C->CR1 |= CR1_PE_Set;

    /*---------------------------- I2Cx CR1 Configuration ------------------------*/
    /* Get the I2Cx CR1 value */
    tmpreg = pI2C->CR1;
    /* Clear ACK, SMBTYPE and  SMBUS bits */
    tmpreg &= CR1_CLEAR_Mask;
    /* Set ACK bit according to I2C_Ack value */
    tmpreg |= (uint16_t)((uint16_t)handle->Init.ACK << 8);
    /* Write to I2Cx CR1 */
    pI2C->CR1 = tmpreg;

    /*---------------------------- I2Cx OAR1 Configuration -----------------------*/
    /* 根据主从机不同模式设定从机地址 */
    if (handle->Mode & 0x10)
    {
        pI2C->OAR1 = 0u;
    }
    else
    {
        pI2C->OAR1 = (uint16_t)(((uint16_t)handle->Init.AddressMode << 8) | handle->Init.Address);
    }
}

/**
  * @brief  使能或禁用I2C外设
  * @param  NewState        ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_Cmd(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        pI2C->CR1 |= CR1_PE_Set;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        pI2C->CR1 &= CR1_PE_Reset;
    }
}

/**
  * @brief  通过I2C外设读取EEPROM指定地址数据
  * @note   1. 仅支持单字节读取
  * @note   2. 可通过定义 EEPROM_ADDRESS_16_BIT 支持M24C32得16位长度地址
  * @note   3. 阻塞式读取
  * @param  ReadData        读取到的数据存入地址指针
  *         DeviceAddress   EEPROM设备地址
  *         ReadAddress     EERPOM数据地址
  *         Timeout         读取超时
  * @retval LHL_OK:         读取成功；
  *         LHL_BUSY:       I2C总线忙；
  *         LHL_ERROR:      I2C寄存器错误；
  *         LHL_TIMEOUT:    EEPROM超时未回应。
  */
LHL_StatusTypeDef LHL_I2C_Read(uint8_t *ReadData, uint8_t DeviceAddress, uint16_t ReadAddress, uint32_t Timeout)
{
    uint32_t t = Timeout;                                       //超时判断

    /*!< 1. While the bus is busy */
    while(LHL_I2C_GetFlag(I2C_FLAG_BUSY) != RESET)
    {
        if ((t--) == 0) return LHL_BUSY;
    }

    /*!< 2. Send START condition */
    LHL_I2C_GenerateSTART(ENABLE);             

    /*!< 3. Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
    while (LHL_I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT) != LHL_OK)
    {
        if ((t--) == 0) return LHL_ERROR;
    }

    /*!< 4. Send EEPROM ID (Device Address) */
    LHL_I2C_Send7bitAddress(DeviceAddress, I2C_MODE_MASTER_TRANSMITTER);

    /*!< 5. Test on EV6 and clear it */
    while(LHL_I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != LHL_OK)
    {
        if ((t--) == 0) return LHL_TIMEOUT;
    }
    
#ifdef EEPROM_ADDRESS_16_BIT   
    /*!< Send the EEPROM's internal 16bit address to read from: MSB of the address first */
    LHL_I2C_SendData((uint8_t)((ReadAddress & 0xFF00) >> 8));    

    /*!< Test on EV8 and clear it */
    while(LHL_I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != LHL_OK)
    {
        if((t--) == 0) return LHL_TIMEOUT;
    }
#endif
    /* 6. Send the EEPROM's internal 8bit/16bit LSB data address to read */
    LHL_I2C_SendData((uint8_t)(ReadAddress & 0x00FF));  

    /* 7. Test on EV8 and clear it */
    while(LHL_I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED) != LHL_OK)
    {
        if ((t--) == 0) return LHL_TIMEOUT;
    }    

//    while(LHL_I2C_GetFlag(I2C_FLAG_BTF) == RESET)
//    {
//        if ((t--) == 0) return LHL_TIMEOUT;
//    }

    /*!< 8. Repeat STRAT condition a second time */       
    LHL_I2C_GenerateSTART(ENABLE);
    
    /*!< 9. Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */    
    while(LHL_I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT) != LHL_OK)
    {
        if ((t--) == 0) return LHL_TIMEOUT;
    }

    /*!< 10. Send EEPROM ID (Device Address) AGAIN for read */
    LHL_I2C_Send7bitAddress(DeviceAddress, I2C_MODE_MASTER_RECEIVER);
    
    /*!< 11. Test on EV6 and clear it */
    while(LHL_I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != LHL_OK)
    {
        if ((t--) == 0) return LHL_TIMEOUT;
    }
    
    /*!< 12. 读取单个字节 */
    LHL_I2C_AcknowledgeConfig(DISABLE);
    LHL_I2C_GenerateSTOP(ENABLE);
        
    while(LHL_I2C_GetFlag(I2C_FLAG_RXNE) == RESET)
    {
        if ((t--) == 0) 
        {
            LHL_I2C_AcknowledgeConfig(ENABLE);
            return LHL_TIMEOUT;
        }
    }
        
    *ReadData = LHL_I2C_ReceiveData();
        
    LHL_I2C_AcknowledgeConfig(ENABLE);

    return LHL_OK;
}

/**
  * @brief  通过I2C外设写入EEPROM指定地址数据
  * @note   1. 仅支持单字节写入
  * @note   2. 可通过定义 EEPROM_ADDRESS_16_BIT 支持M24C32得16位长度地址
  * @note   3. 阻塞式写入
  * @param  WriteData       待写入的数据地址指针
  *         DeviceAddress   EEPROM设备地址
  *         ReadAddress     EERPOM数据地址
  *         Timeout         读取超时
  * @retval LHL_OK:         读取成功；
  *         LHL_BUSY:       I2C总线忙；
  *         LHL_ERROR:      I2C寄存器错误；
  *         LHL_TIMEOUT:    EEPROM超时未回应。
  */
LHL_StatusTypeDef LHL_I2C_Write(uint8_t *WriteData, uint8_t DeviceAddress, uint16_t WriteAddress, uint32_t Timeout)
{ 
    uint32_t t = Timeout;                                       //超时判断
    
    /*!< 1. While the bus is busy */
    while(LHL_I2C_GetFlag(I2C_FLAG_BUSY) != RESET)
    {
        if ((t--) == 0) return LHL_BUSY;
    }

    /*!< 2. Send START condition */
    LHL_I2C_GenerateSTART(ENABLE);             

    /*!< 3. Test on EV5 and clear it */
    while(LHL_I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT) != LHL_OK)
    {
        if ((t--) == 0) return LHL_ERROR;
    }

    /*!< 4. Send EEPROM ID (Device Address) */
    LHL_I2C_Send7bitAddress(DeviceAddress, I2C_MODE_MASTER_TRANSMITTER);    

    /*!< 5. Test on EV6 and clear it */
    while(LHL_I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != LHL_OK)
    {
        if ((t--) == 0) return LHL_TIMEOUT;
    }

#ifdef EEPROM_ADDRESS_16_BIT   
    /*!< Send the EEPROM's internal 16bit address to write to: MSB of the address first */
    LHL_I2C_SendData((uint8_t)((ReadAddress & 0xFF00) >> 8));    

    /*!< Test on EV8 and clear it */
    while(LHL_I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != LHL_OK)
    {
        if((t--) == 0) return LHL_TIMEOUT;
    }
#endif
    /*!< 6. Send the EEPROM's internal 8bit/16bit LSB data address to write to */
    LHL_I2C_SendData((uint8_t)(WriteAddress & 0x00FF));  

    /*!< 7. Test on EV8 and clear it */
    while(LHL_I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED) != LHL_OK)
    {
        if ((t--) == 0) return LHL_TIMEOUT;
    }
    
    /*!< 8. Send the data to write */
    LHL_I2C_SendData(*WriteData);

    /*!< 9. Wait EV8 */
    while(LHL_I2C_GetFlag(I2C_FLAG_TXE) == RESET)
    {
        if ((t--) == 0) return LHL_TIMEOUT;
    }
    
    /*!< 10. Generate STOP */    
    LHL_I2C_GenerateSTOP(ENABLE);
    
    return LHL_OK;
}

/**
  * @brief  使用I2C发送1个BYTE数据
  * @param  Data        Byte to be transmitted
  * @retval None
  */
void LHL_I2C_SendData(uint8_t Data)
{
    /* Write in the DR register the data to be sent */
    pI2C->DR = Data;
}

/**
  * @brief  使用I2C接收1个BYTE数据
  * @param  None
  * @retval The value of the received data.
  */
uint8_t LHL_I2C_ReceiveData(void)
{
  /* Return the data in the DR register */
  return (uint8_t)pI2C->DR;
}

/**
  * @brief  Enables or disables the specified I2C DMA requests.
  * @param  NewState: new state of the I2C DMA transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_DMACmd(FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C DMA requests */
    pI2C->CR2 |= CR2_DMAEN_Set;
  }
  else
  {
    /* Disable the selected I2C DMA requests */
    pI2C->CR2 &= CR2_DMAEN_Reset;
  }
}

/**
  * @brief  Specifies if the next DMA transfer will be the last one.
  * @param  NewState: new state of the I2C DMA last transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_DMALastTransferCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Next DMA transfer is the last transfer */
    pI2C->CR2 |= CR2_LAST_Set;
  }
  else
  {
    /* Next DMA transfer is not the last transfer */
    pI2C->CR2 &= CR2_LAST_Reset;
  }
}

/**
  * @brief  生成I2C通信START条件
  * @param  NewState        ENABLE or DISABLE
  * @retval None
  */
void LHL_I2C_GenerateSTART(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    pI2C->CR1 |= CR1_START_Set;
  }
  else
  {
    /* Disable the START condition generation */
    pI2C->CR1 &= CR1_START_Reset;
  }
}

/**
  * @brief  生成I2C通信STOP条件
  * @param  NewState        ENABLE or DISABLE
  * @retval None
  */
void LHL_I2C_GenerateSTOP(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Generate a STOP condition */
        pI2C->CR1 |= CR1_STOP_Set;
    }
    else
    {
        /* Disable the STOP condition generation */
        pI2C->CR1 &= CR1_STOP_Reset;
    }
}

/**
  * @brief  使能或禁用I2C Acknowledge应答机制
  * @param  NewState        ENABLE or DISABLE
  * @retval None
  */
void LHL_I2C_AcknowledgeConfig(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    pI2C->CR1 |= CR1_ACK_Set;
  }
  else
  {
    /* Disable the acknowledgement */
    pI2C->CR1 &= CR1_ACK_Reset;
  }
}

/**
  * @brief  Configures the specified I2C own address2.
  * @param  Address: specifies the 7bit I2C own address2.
  * @retval None.
  */
void LHL_I2C_OwnAddress2Config(uint8_t Address)
{
  uint16_t tmpreg = 0;

  /* Get the old register value */
  tmpreg = pI2C->OAR2;

  /* Reset I2Cx Own address2 bit [7:1] */
  tmpreg &= OAR2_ADD2_Reset;

  /* Set I2Cx Own address2 */
  tmpreg |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);

  /* Store the new register value */
  pI2C->OAR2 = tmpreg;
}

/**
  * @brief  Enables or disables the specified I2C dual addressing mode.
  * @param  NewState: new state of the I2C dual addressing mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_DualAddressCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable dual addressing mode */
    pI2C->OAR2 |= OAR2_ENDUAL_Set;
  }
  else
  {
    /* Disable dual addressing mode */
    pI2C->OAR2 &= OAR2_ENDUAL_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C general call feature.
  * @param  NewState: new state of the I2C General call.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_GeneralCallCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable generall call */
    pI2C->CR1 |= CR1_ENGC_Set;
  }
  else
  {
    /* Disable generall call */
    pI2C->CR1 &= CR1_ENGC_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_IT_BUF: Buffer interrupt mask
  *     @arg I2C_IT_EVT: Event interrupt mask
  *     @arg I2C_IT_ERR: Error interrupt mask
  * @param  NewState: new state of the specified I2C interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_ITConfig(uint16_t I2C_IT, FunctionalState NewState)
{  
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    pI2C->CR2 |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    pI2C->CR2 &= (uint16_t)~I2C_IT;
  }
}

/**
  * @brief  向选定从机发送地址数据
  * @param  Address: specifies the slave address which will be transmitted
  * @param  I2C_Direction   specifies whether the I2C device will be a Transmitter or a Receiver：
  *     @arg I2C_Direction_Transmitter: Transmitter mode
  *     @arg I2C_Direction_Receiver: Receiver mode
  * @retval None.
  */
void LHL_I2C_Send7bitAddress(uint8_t Address, I2C_MODE_t I2C_Mode)
{
    /* 判断发送器还是接收器 */
    if (I2C_Mode & 0x01)
    {
        /* 接收器，Set the address bit0 for read */
        Address |= OAR1_ADD0_Set;
    }
    else
    {
        /* 发送器，Reset the address bit0 for write */
        Address &= OAR1_ADD0_Reset;
    }

    pI2C->DR = Address;
}

/**
  * @brief  使能或禁用I2C software reset.
  * @param  NewState        ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_SoftwareResetCmd( FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    pI2C->CR1 |= CR1_SWRST_Set;
  }
  else
  {
    /* Peripheral not under reset */
    pI2C->CR1 &= CR1_SWRST_Reset;
  }
}

/**
  * @brief  Selects the specified I2C NACK position in master receiver mode.
  *         This function is useful in I2C Master Receiver mode when the number
  *         of data to be received is equal to 2. In this case, this function 
  *         should be called (with parameter I2C_NACKPosition_Next) before data 
  *         reception starts,as described in the 2-byte reception procedure 
  *         recommended in Reference Manual in Section: Master receiver.                
  * @param  I2C_NACKPosition: specifies the NACK position. 
  *   This parameter can be one of the following values:
  *     @arg I2C_NACKPosition_Next: indicates that the next byte will be the last
  *          received byte.  
  *     @arg I2C_NACKPosition_Current: indicates that current byte is the last 
  *          received byte.            
  * @retval None
  */
void LHL_I2C_NACKPositionConfig(uint16_t I2C_NACKPosition)
{  
  /* Check the input parameter */
  if (I2C_NACKPosition == I2C_NACKPosition_Next)
  {
    /* Next byte in shift register is the last received byte */
    pI2C->CR1 |= I2C_NACKPosition_Next;
  }
  else
  {
    /* Current byte in shift register is the last received byte */
    pI2C->CR1 &= I2C_NACKPosition_Current;
  }
}

/**
  * @brief  Enables or disables the specified I2C PEC transfer.
  * @param  NewState: new state of the I2C PEC transmission.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_TransmitPEC(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC transmission */
    pI2C->CR1 |= CR1_PEC_Set;
  }
  else
  {
    /* Disable the selected I2C PEC transmission */
    pI2C->CR1 &= CR1_PEC_Reset;
  }
}

/**
  * @brief  Enables or disables the PEC value calculation of the transferred bytes.
  * @param  NewState: new state of the I2C PEC value calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_CalculatePEC(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC calculation */
    pI2C->CR1 |= CR1_ENPEC_Set;
  }
  else
  {
    /* Disable the selected I2C PEC calculation */
    pI2C->CR1 &= CR1_ENPEC_Reset;
  }
}

/**
  * @brief  Returns the PEC value for the specified I2C.
  * @retval The PEC value.
  */
uint8_t LHL_I2C_GetPEC(void)
{
  /* Return the selected I2C PEC value */
  return ((pI2C->SR2) >> 8);
}

/**
  * @brief  Enables or disables the specified I2C Clock stretching.
  * @param  NewState: new state of the I2Cx Clock stretching.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_I2C_StretchClockCmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    /* Enable the selected I2C Clock stretching */
    pI2C->CR1 |= CR1_NOSTRETCH_Set;
  }
  else
  {
    /* Disable the selected I2C Clock stretching */
    pI2C->CR1 &= CR1_NOSTRETCH_Reset;
  }
}

/**
  * @brief  Selects the specified I2C fast mode duty cycle.
  * @param  I2C_DutyCycle: specifies the fast mode duty cycle.
  *   This parameter can be one of the following values:
  *     @arg I2C_DutyCycle_2: I2C fast mode Tlow/Thigh = 2
  *     @arg I2C_DutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9
  * @retval None
  */
void LHL_I2C_FastModeDutyCycleConfig(uint16_t I2C_DutyCycle)
{
  if (I2C_DutyCycle != I2C_DutyCycle_16_9)
  {
    /* I2C fast mode Tlow/Thigh=2 */
    pI2C->CCR &= I2C_DutyCycle_2;
  }
  else
  {
    /* I2C fast mode Tlow/Thigh=16/9 */
    pI2C->CCR |= I2C_DutyCycle_16_9;
  }
}

/**
 * @brief
 ****************************************************************************************
 *
 *                         I2C State Monitoring Functions
 *                       
 ****************************************************************************************   
 * This I2C driver provides three different ways for I2C state monitoring
 *  depending on the application requirements and constraints:    
 *  
 * 1) Basic state monitoring:
 *    Using I2C_CheckEvent() function:
 *    It compares the status registers (SR1 and SR2) content to a given event
 *    (can be the combination of one or more flags).
 *    It returns SUCCESS if the current status includes the given flags 
 *    and returns ERROR if one or more flags are missing in the current status.
 *    - When to use:
 *      - This function is suitable for most applications as well as for startup 
 *      activity since the events are fully described in the product reference manual.
 *      - It is also suitable for users who need to define their own events.
 *    - Limitations:
 *      - If an error occurs (ie. error flags are set besides to the monitored flags),
 *        the I2C_CheckEvent() function may return SUCCESS despite the communication
 *        hold or corrupted real state. 
 *        In this case, it is advised to use error interrupts to monitor the error
 *        events and handle them in the interrupt IRQ handler.
 *        
 *        @note 
 *        For error management, it is advised to use the following functions:
 *          - I2C_ITConfig() to configure and enable the error interrupts (I2C_IT_ERR).
 *          - I2Cx_ER_IRQHandler() which is called when the error interrupt occurs.
 *            Where x is the peripheral instance (I2C1, I2C2 ...)
 *          - I2C_GetFlagStatus() or I2C_GetITStatus() to be called into I2Cx_ER_IRQHandler() 
 *            in order to determine which error occured.
 *          - I2C_ClearFlag() or I2C_ClearITPendingBit() and/or I2C_SoftwareResetCmd()
 *            and/or I2C_GenerateStop() in order to clear the error flag and source,
 *            and return to correct communication status.
 *            
 *
 *  2) Advanced state monitoring:
 *     Using the function I2C_GetLastEvent() which returns the image of both status 
 *     registers in a single word (uint32_t) (Status Register 2 value is shifted left 
 *     by 16 bits and concatenated to Status Register 1).
 *     - When to use:
 *       - This function is suitable for the same applications above but it allows to
 *         overcome the mentioned limitation of I2C_GetFlagStatus() function.
 *         The returned value could be compared to events already defined in the 
 *         library or to custom values defined by user.
 *       - This function is suitable when multiple flags are monitored at the same time.
 *       - At the opposite of I2C_CheckEvent() function, this function allows user to
 *         choose when an event is accepted (when all events flags are set and no 
 *         other flags are set or just when the needed flags are set like 
 *         I2C_CheckEvent() function).
 *     - Limitations:
 *       - User may need to define his own events.
 *       - Same remark concerning the error management is applicable for this 
 *         function if user decides to check only regular communication flags (and 
 *         ignores error flags).
 *
 *  3) Flag-based state monitoring:
 *     Using the function I2C_GetFlagStatus() which simply returns the status of 
 *     one single flag (ie. I2C_FLAG_RXNE ...). 
 *     - When to use:
 *        - This function could be used for specific applications or in debug phase.
 *        - It is suitable when only one flag checking is needed (most I2C events 
 *          are monitored through multiple flags).
 *     - Limitations: 
 *        - When calling this function, the Status register is accessed. Some flags are
 *          cleared when the status register is accessed. So checking the status
 *          of one Flag, may clear other ones.
 *        - Function may need to be called twice or more in order to monitor one 
 *          single event.
 *     
 */

/**
 * 
 *  1) Basic state monitoring
 *******************************************************************************
 */
 
/**
  * @brief  Checks whether the last I2Cx Event is equal to the one passed
  *   as parameter.
  * @param  I2C_EVENT: specifies the event to be checked. 
  *   This parameter can be one of the following values:
  *     @arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED           : EV1
  *     @arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED              : EV1
  *     @arg I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED     : EV1
  *     @arg I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED        : EV1
  *     @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED            : EV1
  *     @arg I2C_EVENT_SLAVE_BYTE_RECEIVED                         : EV2
  *     @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF)      : EV2
  *     @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL)    : EV2
  *     @arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED                      : EV3
  *     @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF)   : EV3
  *     @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL) : EV3
  *     @arg I2C_EVENT_SLAVE_ACK_FAILURE                           : EV3_2
  *     @arg I2C_EVENT_SLAVE_STOP_DETECTED                         : EV4
  *     @arg I2C_EVENT_MASTER_MODE_SELECT                          : EV5
  *     @arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED            : EV6     
  *     @arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED               : EV6
  *     @arg I2C_EVENT_MASTER_BYTE_RECEIVED                        : EV7
  *     @arg I2C_EVENT_MASTER_BYTE_TRANSMITTING                    : EV8
  *     @arg I2C_EVENT_MASTER_BYTE_TRANSMITTED                     : EV8_2
  *     @arg I2C_EVENT_MASTER_MODE_ADDRESS10                       : EV9
  * @retval An ErrorStatus enumeration value:
  * - LHL_OK: Last event is equal to the I2C_EVENT
  * - LHL_ERROR: Last event is different from the I2C_EVENT
  */
LHL_StatusTypeDef LHL_I2C_CheckEvent(uint32_t I2C_EVENT)
{
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;
    LHL_StatusTypeDef status = LHL_ERROR;

    /* Read the I2Cx status register */
    flag1 = pI2C->SR1;
    flag2 = pI2C->SR2;
    flag2 = flag2 << 16;

    /* Get the last event value from I2C status register */
    lastevent = (flag1 | flag2) & FLAG_Mask;

    /* Check whether the last event contains the I2C_EVENT */
    if ((lastevent & I2C_EVENT) == I2C_EVENT)
    {
        status = LHL_OK;
    }
    else
    {
        status = LHL_ERROR;
    }
    return status;
}

/**
 * 
 *  2) Advanced state monitoring
 *******************************************************************************
 */

/**
  * @brief  Returns the last I2Cx Event.
  * @param  None.   
  * @retval The last event
  */
uint32_t LHL_I2C_GetLastEvent(void)
{
  uint32_t lastevent, flag1, flag2;

  /* Read the I2Cx status register */
  flag1 = pI2C->SR1;
  flag2 = pI2C->SR2;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | (flag2 << 16)) & FLAG_Mask;

  /* Return status */
  return lastevent;
}

/**
 * 
 *  3) Flag-based state monitoring
 *******************************************************************************
 */

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2C_FLAG: specifies the flag to check. 
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_DUALF: Dual flag (Slave mode)
  *     @arg I2C_FLAG_SMBHOST: SMBus host header (Slave mode)
  *     @arg I2C_FLAG_SMBDEFAULT: SMBus default header (Slave mode)
  *     @arg I2C_FLAG_GENCALL: General call header flag (Slave mode)
  *     @arg I2C_FLAG_TRA: Transmitter/Receiver flag
  *     @arg I2C_FLAG_BUSY: Bus busy flag
  *     @arg I2C_FLAG_MSL: Master/Slave flag
  *     @arg I2C_FLAG_SMBALERT: SMBus Alert flag
  *     @arg I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
  *     @arg I2C_FLAG_PECERR: PEC error in reception flag
  *     @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_FLAG_AF: Acknowledge failure flag
  *     @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
  *     @arg I2C_FLAG_BERR: Bus error flag
  *     @arg I2C_FLAG_TXE: Data register empty flag (Transmitter)
  *     @arg I2C_FLAG_RXNE: Data register not empty (Receiver) flag
  *     @arg I2C_FLAG_STOPF: Stop detection flag (Slave mode)
  *     @arg I2C_FLAG_ADD10: 10-bit header sent flag (Master mode)
  *     @arg I2C_FLAG_BTF: Byte transfer finished flag
  *     @arg I2C_FLAG_ADDR: Address sent flag (Master mode) "ADSL"
  *   Address matched flag (Slave mode)"ENDA"
  *     @arg I2C_FLAG_SB: Start bit flag (Master mode)
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus LHL_I2C_GetFlag(uint32_t I2C_FLAG)
{
    FlagStatus bitstatus = RESET;
    __IO uint32_t i2creg = 0, i2cxbase = 0;

    /* Get the I2Cx peripheral base address */
    i2cxbase = (uint32_t)pI2C;
  
    /* Read flag register index */
    i2creg = I2C_FLAG >> 28;
  
    /* Get bit[23:0] of the flag */
    I2C_FLAG &= FLAG_Mask;
  
    if(i2creg != 0)
    {
        /* Get the I2Cx SR1 register address */
        i2cxbase += 0x14;
    }
    else
    {
        /* Flag in I2Cx SR2 Register */
        I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
        /* Get the I2Cx SR2 register address */
        i2cxbase += 0x18;
    }
  
    if(((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
    {
        /* I2C_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* I2C_FLAG is reset */
        bitstatus = RESET;
    }
  
    /* Return the I2C_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Clears the I2Cx's pending flags.
  * @param  I2C_FLAG: specifies the flag to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
  *     @arg I2C_FLAG_PECERR: PEC error in reception flag
  *     @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_FLAG_AF: Acknowledge failure flag
  *     @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
  *     @arg I2C_FLAG_BERR: Bus error flag
  *   
  * @note
  *   - STOPF (STOP detection) is cleared by software sequence: a read operation 
  *     to I2C_SR1 register (I2C_GetFlagStatus()) followed by a write operation 
  *     to I2C_CR1 register (I2C_Cmd() to re-enable the I2C peripheral).
  *   - ADD10 (10-bit header sent) is cleared by software sequence: a read 
  *     operation to I2C_SR1 (I2C_GetFlagStatus()) followed by writing the 
  *     second byte of the address in DR register.
  *   - BTF (Byte Transfer Finished) is cleared by software sequence: a read 
  *     operation to I2C_SR1 register (I2C_GetFlagStatus()) followed by a 
  *     read/write to I2C_DR register (I2C_SendData()).
  *   - ADDR (Address sent) is cleared by software sequence: a read operation to 
  *     I2C_SR1 register (I2C_GetFlagStatus()) followed by a read operation to 
  *     I2C_SR2 register ((void)(I2Cx->SR2)).
  *   - SB (Start Bit) is cleared software sequence: a read operation to I2C_SR1
  *     register (I2C_GetFlagStatus()) followed by a write operation to I2C_DR
  *     register  (I2C_SendData()).
  * @retval None
  */
void LHL_I2C_ClearFlag(uint32_t I2C_FLAG)
{
    uint32_t flagpos = 0;

    /* Get the I2C flag position */
    flagpos = I2C_FLAG & FLAG_Mask;
    /* Clear the selected I2C flag */
    pI2C->SR1 = (uint16_t)~flagpos;
}

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2C_IT: specifies the interrupt source to check. 
  *   This parameter can be one of the following values:
  *     @arg I2C_IT_TIMEOUT: Timeout or Tlow error flag
  *     @arg I2C_IT_PECERR: PEC error in reception flag
  *     @arg I2C_IT_OVR: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_IT_AF: Acknowledge failure flag
  *     @arg I2C_IT_ARLO: Arbitration lost flag (Master mode)
  *     @arg I2C_IT_BERR: Bus error flag
  *     @arg I2C_IT_TXE: Data register empty flag (Transmitter)
  *     @arg I2C_IT_RXNE: Data register not empty (Receiver) flag
  *     @arg I2C_IT_STOPF: Stop detection flag (Slave mode)
  *     @arg I2C_IT_ADD10: 10-bit header sent flag (Master mode)
  *     @arg I2C_IT_BTF: Byte transfer finished flag
  *     @arg I2C_IT_ADDR: Address sent flag (Master mode) "ADSL"
  *                       Address matched flag (Slave mode)"ENDAD"
  *     @arg I2C_IT_SB: Start bit flag (Master mode)
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus LHL_I2C_GetPending(uint32_t I2C_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check if the interrupt source is enabled or not */
  enablestatus = (uint32_t)(((I2C_IT & ITEN_Mask) >> 16) & (pI2C->CR2)) ;
  
  /* Get bit[23:0] of the flag */
  I2C_IT &= FLAG_Mask;

  /* Check the status of the specified I2C flag */
  if (((pI2C->SR1 & I2C_IT) != (uint32_t)RESET) && enablestatus)
  {
    /* I2C_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_IT is reset */
    bitstatus = RESET;
  }
  /* Return the I2C_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the I2C interrupt pending bits.
  * @param  I2C_IT: specifies the interrupt pending bit to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_IT_SMBALERT: SMBus Alert interrupt
  *     @arg I2C_IT_TIMEOUT: Timeout or Tlow error interrupt
  *     @arg I2C_IT_PECERR: PEC error in reception  interrupt
  *     @arg I2C_IT_OVR: Overrun/Underrun interrupt (Slave mode)
  *     @arg I2C_IT_AF: Acknowledge failure interrupt
  *     @arg I2C_IT_ARLO: Arbitration lost interrupt (Master mode)
  *     @arg I2C_IT_BERR: Bus error interrupt
  *   
  * @note
  *   - STOPF (STOP detection) is cleared by software sequence: a read operation 
  *     to I2C_SR1 register (I2C_GetITStatus()) followed by a write operation to 
  *     I2C_CR1 register (I2C_Cmd() to re-enable the I2C peripheral).
  *   - ADD10 (10-bit header sent) is cleared by software sequence: a read 
  *     operation to I2C_SR1 (I2C_GetITStatus()) followed by writing the second 
  *     byte of the address in I2C_DR register.
  *   - BTF (Byte Transfer Finished) is cleared by software sequence: a read 
  *     operation to I2C_SR1 register (I2C_GetITStatus()) followed by a 
  *     read/write to I2C_DR register (I2C_SendData()).
  *   - ADDR (Address sent) is cleared by software sequence: a read operation to 
  *     I2C_SR1 register (I2C_GetITStatus()) followed by a read operation to 
  *     I2C_SR2 register ((void)(I2Cx->SR2)).
  *   - SB (Start Bit) is cleared by software sequence: a read operation to 
  *     I2C_SR1 register (I2C_GetITStatus()) followed by a write operation to 
  *     I2C_DR register (I2C_SendData()).
  * @retval None
  */
void LHL_I2C_ClearPending(uint32_t I2C_IT)
{
  uint32_t flagpos = 0;

  /* Get the I2C flag position */
  flagpos = I2C_IT & FLAG_Mask;
  /* Clear the selected I2C flag */
  pI2C->SR1 = (uint16_t)~flagpos;
}

/**
  * @brief  获取I2C最新的全部标志位
  * @param  None.   
  * @retval 包括SR2和SR1的状态位
  */
uint32_t LHL_I2C_GetLastFlag(void)
{
  uint32_t flag1, flag2;

  /* Read the I2Cx status register */
  flag1 = pI2C->SR1;
  flag2 = pI2C->SR2;

  /* Return status */
  return (flag1 | (flag2 << 16));
}


