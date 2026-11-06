/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_i2c.c
 * @version 2025-09-15
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_I2C_H
#define __LH32M0G3x_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Public Definition ---------------------------------------------------------*/

#define I2C_STANDARD_SPEED  100000

/** @defgroup I2C_mode 
  * @{
  */
typedef enum {
    I2C_MODE_SLAVE_TRANSMITTER              = ((uint8_t)0x00),
    I2C_MODE_SLAVE_RECEIVER                 = ((uint8_t)0x01),
    I2C_MODE_MASTER_TRANSMITTER             = ((uint8_t)0x10),
    I2C_MODE_MASTER_RECEIVER                = ((uint8_t)0x11),
} I2C_MODE_t;
/**
  * @}
  */
  
/** @defgroup I2C_mode 
  * @{
  */
typedef enum {
    I2C_STATE_IDLE                          = ((uint8_t)0x00),
    I2C_STATE_START,
    I2C_STATE_ADDRESS,
    I2C_STATE_TRANSMITTING,
    I2C_STATE_TRANSMITTED,
    I2C_STATE_RECEIVING,
    I2C_STATE_RECEIVED,
    I2C_STATE_NACK,
    I2C_STATE_STOP,
    I2C_STATE_BUSY,
    I2C_STATE_ERROR,    
} I2C_STATE_t;
/**
  * @}
  */
  
/** @defgroup I2C_transfer_direction 
  * @{
  */
//typedef enum {
//    I2C_DIRECTION_TRANSMITTER       = ((uint8_t)0x00),
//    I2C_DIRECTION_RECEIVER          = ((uint8_t)0x01),
//} I2C_DIRECTION_t;
/**
  * @}
  */
  
/** @defgroup I2C_acknowledgement
  * @{
  */
typedef enum {
    I2C_ACK_ENABLE                  = ((uint8_t)0x04),
    I2C_ACK_DISABLE                 = ((uint8_t)0x00),
} I2C_ACK_t;
/**
  * @}
  */
  
/** @defgroup I2C_acknowledged_address 
  * @{
  */
typedef enum {
    I2C_ADDRESSMODE_7BIT            = ((uint8_t)0x40),
    I2C_ADDRESSMODE_10BIT           = ((uint8_t)0xC0),
} I2C_ADDRESSMODE_t;
/**
  * @}
  */ 
  
/** 
  * @brief  I2C Init structure definition  
  */
typedef struct {

  uint32_t Speed;               /*!< Specifies the clock frequency.
                                         This parameter must be set to a value lower than 400kHz */

//  uint16_t DutyCycle;             /*!< Reserved！Specifies the I2C fast mode duty cycle.
//                                         This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

  uint16_t Address;             /*!< Specifies the first device own address.
                                         This parameter can be a 7-bit or 10-bit address. */

  I2C_ACK_t ACK;                   /*!< Enables or disables the acknowledgement.
                                         This parameter can be a value of @ref I2C_acknowledgement */

  I2C_ADDRESSMODE_t AddressMode;      /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                         This parameter can be a value of @ref I2C_acknowledged_address */
                                         
} I2C_InitTypeDef;

typedef struct {

    __RW I2C_MODE_t Mode;               /*!< I2C模式：主机（Master）或从机（Slave），发送器或接收器 */
  
    __RW int8_t Size;                   /*!< I2Cz数据总长度：1~127 Bytes */
    
    __RW int8_t Count;                  /*!< I2C已收发数据的数量 */
    
    __RW I2C_STATE_t Status;            /*!< I2C传输状态 */
    
    uint8_t *RxData;
    
    uint8_t *TxData;

    I2C_InitTypeDef Init;               /*!< I2C初始化结构体  */
  
} I2C_HandleTypeDef;


/** @defgroup I2C_duty_cycle_in_fast_mode 
  * @{
  */
#define I2C_DutyCycle_16_9              ((uint16_t)0x4000) /*!< I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_DutyCycle_2                 ((uint16_t)0xBFFF) /*!< I2C fast mode Tlow/Thigh = 2 */
/**
  * @}
  */ 







/** @defgroup I2C_registers 
  * @{
  */

#define I2C_Register_CR1                ((uint8_t)0x00)
#define I2C_Register_CR2                ((uint8_t)0x04)
#define I2C_Register_OAR1               ((uint8_t)0x08)
#define I2C_Register_OAR2               ((uint8_t)0x0C)
#define I2C_Register_DR                 ((uint8_t)0x10)
#define I2C_Register_SR1                ((uint8_t)0x14)
#define I2C_Register_SR2                ((uint8_t)0x18)
#define I2C_Register_CCR                ((uint8_t)0x1C)
#define I2C_Register_TRISE              ((uint8_t)0x20)
#define IS_I2C_REGISTER(REGISTER) (((REGISTER) == I2C_Register_CR1) || \
                                   ((REGISTER) == I2C_Register_CR2) || \
                                   ((REGISTER) == I2C_Register_OAR1) || \
                                   ((REGISTER) == I2C_Register_OAR2) || \
                                   ((REGISTER) == I2C_Register_DR) || \
                                   ((REGISTER) == I2C_Register_SR1) || \
                                   ((REGISTER) == I2C_Register_SR2) || \
                                   ((REGISTER) == I2C_Register_CCR) || \
                                   ((REGISTER) == I2C_Register_TRISE))
/**
  * @}
  */

/** @defgroup I2C_PEC_position 
  * @{
  */

#define I2C_PECPosition_Next            ((uint16_t)0x0800)
#define I2C_PECPosition_Current         ((uint16_t)0xF7FF)
#define IS_I2C_PEC_POSITION(POSITION) (((POSITION) == I2C_PECPosition_Next) || \
                                       ((POSITION) == I2C_PECPosition_Current))
/**
  * @}
  */ 

/** @defgroup I2C_NCAK_position 
  * @{
  */

#define I2C_NACKPosition_Next           ((uint16_t)0x0800)
#define I2C_NACKPosition_Current        ((uint16_t)0xF7FF)
#define IS_I2C_NACK_POSITION(POSITION)  (((POSITION) == I2C_NACKPosition_Next) || \
                                         ((POSITION) == I2C_NACKPosition_Current))
/**
  * @}
  */ 

/** @defgroup I2C_interrupts_definition 
  * @{
  */

#define I2C_IT_BUF                      ((uint16_t)0x0400)
#define I2C_IT_EVT                      ((uint16_t)0x0200)
#define I2C_IT_ERR                      ((uint16_t)0x0100)
#define IS_I2C_CONFIG_IT(IT) ((((IT) & (uint16_t)0xF8FF) == 0x00) && ((IT) != 0x00))
/**
  * @}
  */ 

/** @defgroup I2C_interrupts_definition 
  * @{
  */

#define I2C_IT_SMBALERT                 ((uint32_t)0x01008000)
#define I2C_IT_TIMEOUT                  ((uint32_t)0x01004000)
#define I2C_IT_PECERR                   ((uint32_t)0x01001000)
#define I2C_IT_OVR                      ((uint32_t)0x01000800)
#define I2C_IT_AF                       ((uint32_t)0x01000400)
#define I2C_IT_ARLO                     ((uint32_t)0x01000200)
#define I2C_IT_BERR                     ((uint32_t)0x01000100)
#define I2C_IT_TXE                      ((uint32_t)0x06000080)
#define I2C_IT_RXNE                     ((uint32_t)0x06000040)
#define I2C_IT_STOPF                    ((uint32_t)0x02000010)
#define I2C_IT_ADD10                    ((uint32_t)0x02000008)
#define I2C_IT_BTF                      ((uint32_t)0x02000004)
#define I2C_IT_ADDR                     ((uint32_t)0x02000002)
#define I2C_IT_SB                       ((uint32_t)0x02000001)

#define IS_I2C_CLEAR_IT(IT) ((((IT) & (uint16_t)0x20FF) == 0x00) && ((IT) != (uint16_t)0x00))

#define IS_I2C_GET_IT(IT) (((IT) == I2C_IT_SMBALERT) || ((IT) == I2C_IT_TIMEOUT) || \
                           ((IT) == I2C_IT_PECERR) || ((IT) == I2C_IT_OVR) || \
                           ((IT) == I2C_IT_AF) || ((IT) == I2C_IT_ARLO) || \
                           ((IT) == I2C_IT_BERR) || ((IT) == I2C_IT_TXE) || \
                           ((IT) == I2C_IT_RXNE) || ((IT) == I2C_IT_STOPF) || \
                           ((IT) == I2C_IT_ADD10) || ((IT) == I2C_IT_BTF) || \
                           ((IT) == I2C_IT_ADDR) || ((IT) == I2C_IT_SB))
/**
  * @}
  */

/** @defgroup I2C_flags_definition 
  * @{
  */

/** 
  * @brief  SR2 register flags  
  */

#define I2C_FLAG_DUALF                  ((uint32_t)0x00800000)
#define I2C_FLAG_SMBHOST                ((uint32_t)0x00400000)
#define I2C_FLAG_SMBDEFAULT             ((uint32_t)0x00200000)
#define I2C_FLAG_GENCALL                ((uint32_t)0x00100000)
#define I2C_FLAG_TRA                    ((uint32_t)0x00040000)
#define I2C_FLAG_BUSY                   ((uint32_t)0x00020000)
#define I2C_FLAG_MSL                    ((uint32_t)0x00010000)

/** 
  * @brief  SR1 register flags  
  */

#define I2C_FLAG_SMBALERT               ((uint32_t)0x10008000)
#define I2C_FLAG_TIMEOUT                ((uint32_t)0x10004000)
#define I2C_FLAG_PECERR                 ((uint32_t)0x10001000)
#define I2C_FLAG_OVR                    ((uint32_t)0x10000800)
#define I2C_FLAG_AF                     ((uint32_t)0x10000400)
#define I2C_FLAG_ARLO                   ((uint32_t)0x10000200)
#define I2C_FLAG_BERR                   ((uint32_t)0x10000100)
#define I2C_FLAG_TXE                    ((uint32_t)0x10000080)
#define I2C_FLAG_RXNE                   ((uint32_t)0x10000040)
#define I2C_FLAG_STOPF                  ((uint32_t)0x10000010)
#define I2C_FLAG_ADD10                  ((uint32_t)0x10000008)
#define I2C_FLAG_BTF                    ((uint32_t)0x10000004)
#define I2C_FLAG_ADDR                   ((uint32_t)0x10000002)
#define I2C_FLAG_SB                     ((uint32_t)0x10000001)

#define IS_I2C_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0x20FF) == 0x00) && ((FLAG) != (uint16_t)0x00))

#define IS_I2C_GET_FLAG(FLAG) (((FLAG) == I2C_FLAG_DUALF) || ((FLAG) == I2C_FLAG_SMBHOST) || \
                               ((FLAG) == I2C_FLAG_SMBDEFAULT) || ((FLAG) == I2C_FLAG_GENCALL) || \
                               ((FLAG) == I2C_FLAG_TRA) || ((FLAG) == I2C_FLAG_BUSY) || \
                               ((FLAG) == I2C_FLAG_MSL) || ((FLAG) == I2C_FLAG_SMBALERT) || \
                               ((FLAG) == I2C_FLAG_TIMEOUT) || ((FLAG) == I2C_FLAG_PECERR) || \
                               ((FLAG) == I2C_FLAG_OVR) || ((FLAG) == I2C_FLAG_AF) || \
                               ((FLAG) == I2C_FLAG_ARLO) || ((FLAG) == I2C_FLAG_BERR) || \
                               ((FLAG) == I2C_FLAG_TXE) || ((FLAG) == I2C_FLAG_RXNE) || \
                               ((FLAG) == I2C_FLAG_STOPF) || ((FLAG) == I2C_FLAG_ADD10) || \
                               ((FLAG) == I2C_FLAG_BTF) || ((FLAG) == I2C_FLAG_ADDR) || \
                               ((FLAG) == I2C_FLAG_SB))
/**
  * @}
  */

/** @defgroup I2C_Events 
  * @{
  */
/*===================================
     
           I2C Master Events (Events grouped in order of communication)
                                        ======================================*/
/** 
  * @brief  Communication start
  * 
  * After sending the START condition (I2C_GenerateSTART() function) the master 
  * has to wait for this event. It means that the Start condition has been correctly 
  * released on the I2C bus (the bus is free, no other devices is communicating).
  * 
  */
/* --EV5 */
#define  I2C_EVENT_MASTER_MODE_SELECT                   ((uint32_t)0x00030001)  /* BUSY, MSL and SB flag */

/** 
  * @brief  Address Acknowledge
  * 
  * After checking on EV5 (start condition correctly released on the bus), the 
  * master sends the address of the slave(s) with which it will communicate 
  * (I2C_Send7bitAddress() function, it also determines the direction of the communication: 
  * Master transmitter or Receiver). Then the master has to wait that a slave acknowledges 
  * his address. If an acknowledge is sent on the bus, one of the following events will 
  * be set:
  * 
  *  1) In case of Master Receiver (7-bit addressing): the I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED 
  *     event is set.
  *  
  *  2) In case of Master Transmitter (7-bit addressing): the I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED 
  *     is set
  *  
  *  3) In case of 10-Bit addressing mode, the master (just after generating the START 
  *  and checking on EV5) has to send the header of 10-bit addressing mode (I2C_SendData() 
  *  function). Then master should wait on EV9. It means that the 10-bit addressing 
  *  header has been correctly sent on the bus. Then master should send the second part of 
  *  the 10-bit address (LSB) using the function I2C_Send7bitAddress(). Then master 
  *  should wait for event EV6. 
  *     
  */

/* --EV6 */
#define  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED     ((uint32_t)0x00070082)  /* BUSY, MSL, ADDR, TXE and TRA flags */
#define  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED        ((uint32_t)0x00030002)  /* BUSY, MSL and ADDR flags */
/* --EV9 */
#define  I2C_EVENT_MASTER_MODE_ADDRESS10                ((uint32_t)0x00030008)  /* BUSY, MSL and ADD10 flags */

/** 
  * @brief Communication events
  * 
  * If a communication is established (START condition generated and slave address 
  * acknowledged) then the master has to check on one of the following events for 
  * communication procedures:
  *  
  * 1) Master Receiver mode: The master has to wait on the event EV7 then to read 
  *    the data received from the slave (I2C_ReceiveData() function).
  * 
  * 2) Master Transmitter mode: The master has to send data (I2C_SendData() 
  *    function) then to wait on event EV8 or EV8_2.
  *    These two events are similar: 
  *     - EV8 means that the data has been written in the data register and is 
  *       being shifted out.
  *     - EV8_2 means that the data has been physically shifted out and output 
  *       on the bus.
  *     In most cases, using EV8 is sufficient for the application.
  *     Using EV8_2 leads to a slower communication but ensure more reliable test.
  *     EV8_2 is also more suitable than EV8 for testing on the last data transmission 
  *     (before Stop condition generation).
  *     
  *  @note In case the  user software does not guarantee that this event EV7 is 
  *  managed before the current byte end of transfer, then user may check on EV7 
  *  and BTF flag at the same time (ie. (I2C_EVENT_MASTER_BYTE_RECEIVED | I2C_FLAG_BTF)).
  *  In this case the communication may be slower.
  * 
  */

/* Master RECEIVER mode -----------------------------*/ 
/* --EV7 */
#define  I2C_EVENT_MASTER_BYTE_RECEIVED                 ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */

#define  I2C_EVENT_MASTER_BTF_RECEIVED                  ((uint32_t)0x00030044)  /* BUSY, MSL ,BTF and RXNE flags */

#define  I2C_EVENT_MASTER_RECEIVED                      ((uint32_t)0x00000040)  /* RXNE flags */


/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING              ((uint32_t)0x00070080)  /* TRA, BUSY, MSL, TXE flags */
/* --EV8_2 */
#define  I2C_EVENT_MASTER_BYTE_TRANSMITTED              ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */

/* --EV_ERROR */
#define  I2C_EVENT_ONLY_BYTE_RECEIVED                   ((uint32_t)0x00000040)  /* RXNE flags only */

/*================================
     
            I2C Slave Events (Events grouped in order of communication)
                                            ==================================*/

/** 
  * @brief  Communication start events
  * 
  * Wait on one of these events at the start of the communication. It means that 
  * the I2C peripheral detected a Start condition on the bus (generated by master 
  * device) followed by the peripheral address. The peripheral generates an ACK 
  * condition on the bus (if the acknowledge feature is enabled through function 
  * I2C_AcknowledgeConfig()) and the events listed above are set :
  *  
  * 1) In normal case (only one address managed by the slave), when the address 
  *   sent by the master matches the own address of the peripheral (configured by 
  *   I2C_OwnAddress1 field) the I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is set 
  *   (where XXX could be TRANSMITTER or RECEIVER).
  *    
  * 2) In case the address sent by the master matches the second address of the 
  *   peripheral (configured by the function I2C_OwnAddress2Config() and enabled 
  *   by the function I2C_DualAddressCmd()) the events I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED 
  *   (where XXX could be TRANSMITTER or RECEIVER) are set.
  *   
  * 3) In case the address sent by the master is General Call (address 0x00) and 
  *   if the General Call is enabled for the peripheral (using function I2C_GeneralCallCmd()) 
  *   the following event is set I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED.   
  * 
  */

/* --EV1  (all the events below are variants of EV1) */   
/* 1) Case of One Single Address managed by the slave */
#define  I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED           ((uint32_t)0x00020002)  /* BUSY and ADDR flags */
#define  I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED        ((uint32_t)0x00060082)  /* TRA, BUSY, TXE and ADDR flags */

/* 2) Case of Dual address managed by the slave */
#define  I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED     ((uint32_t)0x00820000)  /* DUALF and BUSY flags */
#define  I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED  ((uint32_t)0x00860080)  /* DUALF, TRA, BUSY and TXE flags */

/* 3) Case of General Call enabled for the slave */
#define  I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED         ((uint32_t)0x00120000)  /* GENCALL and BUSY flags */

/** 
  * @brief  Communication events
  * 
  * Wait on one of these events when EV1 has already been checked and: 
  * 
  * - Slave RECEIVER mode:
  *     - EV2: When the application is expecting a data byte to be received. 
  *     - EV4: When the application is expecting the end of the communication: master 
  *       sends a stop condition and data transmission is stopped.
  *    
  * - Slave Transmitter mode:
  *    - EV3: When a byte has been transmitted by the slave and the application is expecting 
  *      the end of the byte transmission. The two events I2C_EVENT_SLAVE_BYTE_TRANSMITTED and
  *      I2C_EVENT_SLAVE_BYTE_TRANSMITTING are similar. The second one can optionally be 
  *      used when the user software doesn't guarantee the EV3 is managed before the
  *      current byte end of transfer.
  *    - EV3_2: When the master sends a NACK in order to tell slave that data transmission 
  *      shall end (before sending the STOP condition). In this case slave has to stop sending 
  *      data bytes and expect a Stop condition on the bus.
  *      
  *  @note In case the  user software does not guarantee that the event EV2 is 
  *  managed before the current byte end of transfer, then user may check on EV2 
  *  and BTF flag at the same time (ie. (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_BTF)).
  * In this case the communication may be slower.
  *
  */

/* Slave RECEIVER mode --------------------------*/ 
/* --EV2 */
#define  I2C_EVENT_SLAVE_BYTE_RECEIVED                     ((uint32_t)0x00020040)  /* BUSY and RXNE flags */
/* --EV4  */
#define  I2C_EVENT_SLAVE_STOP_DETECTED                     ((uint32_t)0x00000010)  /* STOPF flag */

/* Slave TRANSMITTER mode -----------------------*/
/* --EV3 */
#define  I2C_EVENT_SLAVE_BYTE_TRANSMITTED                  ((uint32_t)0x00060084)  /* TRA, BUSY, TXE and BTF flags */
#define  I2C_EVENT_SLAVE_BYTE_TRANSMITTING                 ((uint32_t)0x00060080)  /* TRA, BUSY and TXE flags */
/* --EV3_2 */
#define  I2C_EVENT_SLAVE_ACK_FAILURE                       ((uint32_t)0x00000400)  /* AF flag */

/*====================== End of Events Description ===========================*/
/**
  * @}
  */

/* Function Prototype --------------------------------------------------------*/
void                LHL_I2C_DeInit(void);
void                LHL_I2C_Init(I2C_HandleTypeDef* handle);
void                LHL_I2C_Config(I2C_InitTypeDef* I2C_InitStruct);

void                LHL_I2C_SendData(uint8_t Data);
uint8_t             LHL_I2C_ReceiveData(void);

LHL_StatusTypeDef   LHL_I2C_Read(uint8_t *ReadData, uint8_t DeviceAddress, uint16_t ReadAddress, uint32_t Timeout);
LHL_StatusTypeDef   LHL_I2C_Write(uint8_t *WriteData, uint8_t DeviceAddress, uint16_t WriteAddress, uint32_t Timeout);

void                LHL_I2C_Send7bitAddress(uint8_t Address, I2C_MODE_t I2C_Direction);

void                LHL_I2C_Cmd(FunctionalState NewState);

void                LHL_I2C_DMACmd(FunctionalState NewState);
void                LHL_I2C_DMALastTransferCmd(FunctionalState NewState);

void                LHL_I2C_GenerateSTART(FunctionalState NewState);
void                LHL_I2C_GenerateSTOP(FunctionalState NewState);
void                LHL_I2C_AcknowledgeConfig(FunctionalState NewState);

void                LHL_I2C_OwnAddress2Config(uint8_t Address);
void                LHL_I2C_DualAddressCmd(FunctionalState NewState);
void                LHL_I2C_GeneralCallCmd(FunctionalState NewState);

void                LHL_I2C_SoftwareResetCmd(FunctionalState NewState);
void                LHL_I2C_NACKPositionConfig(uint16_t I2C_NACKPosition);
void                LHL_I2C_TransmitPEC(FunctionalState NewState);
void                LHL_I2C_CalculatePEC(FunctionalState NewState);
uint8_t             LHL_I2C_GetPEC(void);
void                LHL_I2C_StretchClockCmd(FunctionalState NewState);
void                LHL_I2C_FastModeDutyCycleConfig(uint16_t I2C_DutyCycle);

LHL_StatusTypeDef   LHL_I2C_CheckEvent(uint32_t I2C_EVENT);
uint32_t            LHL_I2C_GetLastEvent(void);

FlagStatus          LHL_I2C_GetFlag(uint32_t I2C_FLAG);
void                LHL_I2C_ClearFlag(uint32_t I2C_FLAG);

void                LHL_I2C_ITConfig(uint16_t I2C_IT, FunctionalState NewState);
ITStatus            LHL_I2C_GetPending(uint32_t I2C_IT);
void                LHL_I2C_ClearPending(uint32_t I2C_IT);

uint32_t            LHL_I2C_GetLastFlag(void);

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
