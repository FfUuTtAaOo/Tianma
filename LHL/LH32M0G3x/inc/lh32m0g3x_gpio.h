/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_gpio.h
 * @version 2025-09-01
 ******************************************************************************/

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_GPIO_H
#define __LH32M0G3x_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Public Definition ---------------------------------------------------------*/
/** 
  * @brief  GPIO Configuration Mode enumeration 
  */   
typedef enum { 
    GPIO_MODE_INPUT     = 0x00u,            /*!< GPIO Input Mode */
    GPIO_MODE_OUTPUT_PP,                    /*!< GPIO Output Push-Pull Mode */
    GPIO_MODE_OUTPUT_OD,                    /*!< GPIO Output Open-Drain Mode */
    GPIO_MODE_ANALOG,                       /*!< GPIO Analog Mode */
} GPIOMode_TypeDef;

/** 
  * @brief  GPIO Output Maximum Current enumeration 
  */  
typedef enum { 
    GPIO_CURRENT_2mA    = 0x00u,            /*!< Low current drive ability */
    GPIO_CURRENT_4mA    = 0x01u,            /*!< Medium current drive ability */
    GPIO_CURRENT_8mA    = 0x02u,            /*!< High current drive ability */
    GPIO_CURRENT_16mA   = 0x03u,            /*!< Ultra high current drive ability */
} GPIOCurrent_TypeDef;

/* legacy definition */
#define  GPIO_Speed_2MHz    GPIO_Low_Speed    
#define  GPIO_Speed_25MHz   GPIO_Medium_Speed 
#define  GPIO_Speed_50MHz   GPIO_Fast_Speed 
#define  GPIO_Speed_100MHz  GPIO_High_Speed 

/** 
  * @brief  GPIO Configuration PullUp PullDown enumeration 
  */ 
typedef enum { 
    GPIO_NOPULL         = 0x00u,
    GPIO_PULLUP         = 0x01u,
    GPIO_PULLDOWN       = 0x02u,
} GPIOPuPd_TypeDef;

/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */ 
typedef enum { 
    Bit_RESET           = 0u,
    Bit_SET,
} BitAction;

/**
  * @brief  GPIO Pin SET and Bit RESET enumeration
  */
typedef enum {
    GPIO_PIN_RESET      = 0u,
    GPIO_PIN_SET,
} GPIO_PinState;

/** 
  * @brief  GPIO Init structure definition  
  */ 
typedef struct
{
    uint16_t Pin;                       /*!< 引脚，GPIO_PIN_x（x：0~15），参数@ref GPIO_pins_define */

    GPIOMode_TypeDef Mode;              /*!< 基本输入输出模式 @ref GPIOMode_TypeDef */

    GPIOCurrent_TypeDef Current;        /*!< 引脚输出电流驱动能力 @ref GPIOCurrent_TypeDef */

    GPIOPuPd_TypeDef Pull;              /*!< 上下拉及开漏设置 @ref GPIOPuPd_TypeDef */
    
    FunctionalState SchmittTrigger;     /*!< 输入施密特触发设置 ENABLE or DISABLE */                                   
                                       
    uint8_t Alternate;                  /*!< 引脚复用功能设置 @ref GPIO AF Mode */
                                       
    uint8_t Reserved;  
    
}GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_pins_define 
  * @{
  */ 
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK              ((uint32_t)0x0000FFFF) /* PIN mask for assert test */
#define IS_GPIO_PIN(PIN)           (((PIN) & GPIO_PIN_MASK ) != (uint32_t)0x00)
#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_PIN_0) || \
                              ((PIN) == GPIO_PIN_1) || \
                              ((PIN) == GPIO_PIN_2) || \
                              ((PIN) == GPIO_PIN_3) || \
                              ((PIN) == GPIO_PIN_4) || \
                              ((PIN) == GPIO_PIN_5) || \
                              ((PIN) == GPIO_PIN_6) || \
                              ((PIN) == GPIO_PIN_7) || \
                              ((PIN) == GPIO_PIN_8) || \
                              ((PIN) == GPIO_PIN_9) || \
                              ((PIN) == GPIO_PIN_10) || \
                              ((PIN) == GPIO_PIN_11) || \
                              ((PIN) == GPIO_PIN_12) || \
                              ((PIN) == GPIO_PIN_13) || \
                              ((PIN) == GPIO_PIN_14) || \
                              ((PIN) == GPIO_PIN_15))
/**
  * @brief  GPIO PORT Position(0~4)
  */ 
typedef enum {
    GPIO_P0                     = 0u,
    GPIO_P1,
    GPIO_P2,
    GPIO_P3,
    GPIO_P4,
} GPIO_PORT_t;

/**
  * @brief  GPIO PIN Position(0~15)
  */
typedef enum {
    GPIO_0                      = 0u,
    GPIO_1,
    GPIO_2,
    GPIO_3,
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7,
    GPIO_8,
    GPIO_9,
    GPIO_10,
    GPIO_11,
    GPIO_12,
    GPIO_13,
    GPIO_14,
    GPIO_15,
} GPIO_t;

/**
  * @brief  GPIO AF Mode
  */ 
#define GPIOx_AF_GPIO           0

#define GPIO0_0_AF_MISO1        1
#define GPIO0_0_AF_UARTDCD1     2
#define GPIO0_0_AF_UARTDCD0     3
#define GPIO0_0_AF_MIO_D0       4
#define GPIO0_0_AF_LPTIM_CH1    5
#define GPIO0_0_AF_XB_IN0       6

#define GPIO0_1_AF_SCLK1        1
#define GPIO0_1_AF_SCL          2
#define GPIO0_1_AF_SIN0         3
#define GPIO0_1_AF_MIO_D1       4
#define GPIO0_1_AF_LPTIM_CH2    5
#define GPIO0_1_AF_XB_IN1       6

#define GPIO0_2_AF_MOSI1        1
#define GPIO0_2_AF_SDA          2
#define GPIO0_2_AF_SOUT0        3
#define GPIO0_2_AF_MIO_D2       4
#define GPIO0_2_AF_LPTIM_CH1    5
#define GPIO0_2_AF_XB_IN2       6

#define GPIO0_3_AF_CSN1         1
#define GPIO0_3_AF_RTS1         2
#define GPIO0_3_AF_RTS0         3
#define GPIO0_3_AF_MIO_D3       4
#define GPIO0_3_AF_LPTIM_CH2    5
#define GPIO0_3_AF_XB_IN3       6

#define GPIO0_4_AF_RTS0         1
#define GPIO0_4_AF_ECLKOUT      2
#define GPIO0_4_AF_RTS1         3
#define GPIO0_4_AF_MIO_D0       4
#define GPIO0_4_AF_RI0          5
#define GPIO0_4_AF_XB_OUT0      6

#define GPIO0_5_AF_CTS0         1
#define GPIO0_5_AF_SDA          2
#define GPIO0_5_AF_OWI2         3
#define GPIO0_5_AF_MIO_D1       4
#define GPIO0_5_AF_TIM1_CH1     5
#define GPIO0_5_AF_XB_OUT1      6

#define GPIO0_6_AF_SIN1         1
#define GPIO0_6_AF_SIN0         3
#define GPIO0_6_AF_MIO_D2       4
#define GPIO0_6_AF_LPTIM_CH1    5
#define GPIO0_6_AF_XB_OUT2      6

#define GPIO0_7_AF_SOUT1        2
#define GPIO0_7_AF_SOUT0        3
#define GPIO0_7_AF_MIO_D3       4
#define GPIO0_7_AF_LPTIM_CH2    5
#define GPIO0_7_AF_XB_OUT3      6

#define GPIO1_0_AF_TIM1_ETR     1
#define GPIO1_0_AF_EXTCLKIN     2
#define GPIO1_0_AF_CTS1         3
#define GPIO1_0_AF_MIO_D0       4
#define GPIO1_0_AF_SIN1         5
#define GPIO1_0_AF_XB_IN0       6

#define GPIO1_1_AF_TIM2_ETR     1
#define GPIO1_1_AF_ECLKOUT      2
#define GPIO1_1_AF_DTR0         3
#define GPIO1_1_AF_MIO_D1       4
#define GPIO1_1_AF_SOUT1        5
#define GPIO1_1_AF_XB_IN1       6

#define GPIO1_2_AF_TIM1_CH1     1
#define GPIO1_2_AF_RI0          3
#define GPIO1_2_AF_MIO_D2       4
#define GPIO1_2_AF_XB_IN2       6

#define GPIO1_3_AF_TIM1_CH2     1
#define GPIO1_3_AF_SCL          2
#define GPIO1_3_AF_DSR0         3
#define GPIO1_3_AF_MIO_D3       4
#define GPIO1_3_AF_ECLKOUT      5
#define GPIO1_3_AF_XB_IN3       6

#define GPIO1_4_AF_TIM2_CH1     1
#define GPIO1_4_AF_MISO0        2
#define GPIO1_4_AF_SDA          3
#define GPIO1_4_AF_MIO_D0       4
#define GPIO1_4_AF_SIN0         5
#define GPIO1_4_AF_XB_OUT0      6

#define GPIO1_5_AF_TIM2_CH2     1
#define GPIO1_5_AF_SCLK0        2
#define GPIO1_5_AF_SIN0         3
#define GPIO1_5_AF_MIO_D1       4
#define GPIO1_5_AF_SOUT0        5
#define GPIO1_5_AF_XB_OUT1      6
#define GPIO1_5_AF_AFE_DRDY     7

#define GPIO1_6_AF_LPTIM_CH1    1
#define GPIO1_6_AF_MOSI0        2
#define GPIO1_6_AF_SOUT0        3
#define GPIO1_6_AF_MIO_D2       4
//#define GPIO1_6_AF_LPTIM_CH1    5
#define GPIO1_6_AF_XB_OUT2      6
#define GPIO1_6_AF_AFE_SCK      7

#define GPIO1_7_AF_LPTIM_CH2    1
#define GPIO1_7_AF_CSN0         2
#define GPIO1_7_AF_DSR0         3
#define GPIO1_7_AF_MIO_D3       4
//#define GPIO1_7_AF_LPTIM_CH2    5
#define GPIO1_7_AF_XB_OUT3      6
#define GPIO1_7_AF_AFE_CSN      7

#define GPIO2_0_AF_SCL          1
#define GPIO2_0_AF_UARTCLK      3  
#define GPIO2_0_AF_MIO_D0       4
#define GPIO2_0_AF_LPTIM_CH1    5
#define GPIO2_0_AF_XB_IN0       6

#define GPIO2_1_AF_SDA          1
#define GPIO2_1_AF_UARTDCD1     2
#define GPIO2_1_AF_UARTDCD0     3
#define GPIO2_1_AF_MIO_D1       4
#define GPIO2_1_AF_LPTIM_CH2    5
#define GPIO2_1_AF_XB_IN1       6

#define GPIO2_2_AF_OWI2         2
#define GPIO2_2_AF_ECLKOUT      3
#define GPIO2_2_AF_MIO_D2       4
#define GPIO2_2_AF_LPTIM_CH1    5
#define GPIO2_2_AF_XB_IN2       6

#define GPIO2_3_AF_SWCLK        0
#define GPIO2_3_AF_GPIO         1
#define GPIO2_3_AF_MIO_D3       4
#define GPIO2_3_AF_LPTIM_CH2    5
#define GPIO2_3_AF_XB_IN3       6
#define GPIO2_3_AF_AFE_SDO      7

#define GPIO2_4_AF_SWDIO        0
#define GPIO2_4_AF_GPIO         1
#define GPIO2_4_AF_MIO_D0       4
#define GPIO2_4_AF_LPTIM_CH1    5
#define GPIO2_4_AF_XB_OUT0      6
#define GPIO2_4_AF_AFE_SDI      7

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  Function used to set the GPIO configuration to the default reset state ****/
void            LHL_GPIO_DeInit(void);

/* Initialization and Configuration functions *********************************/
void            LHL_GPIO_Init(GPIO_TypeDef* pGPIOx, GPIO_InitTypeDef* GPIO_Init);

/* GPIO Read and Write functions **********************************************/
GPIO_PinState   LHL_GPIO_ReadPin (GPIO_TypeDef *pGPIOx, uint16_t GPIO_Pin_x);

void            LHL_GPIO_WritePin (GPIO_TypeDef *pGPIOx, uint16_t GPIO_Pin_x, GPIO_PinState Pin_State);

void            LHL_GPIO_TogglePin (GPIO_TypeDef *pGPIOx, uint16_t GPIO_Pin_x);

uint8_t         LHL_GPIO_Read (GPIO_TypeDef *pGPIOx);

void            LHL_GPIO_Write (GPIO_TypeDef *pGPIOx, uint8_t GPIO_Port_Val);

void            LHL_GPIO_SetPins(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin_x);

void            LHL_GPIO_ResetPins(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin_x);

/* GPIO Alternate functions configuration function ****************************/
void            LHL_GPIO_SetAFIO(GPIO_TypeDef* pGPIOx, GPIO_t GPIO_x, uint32_t GPIO_AFIO);

void            LHL_GPIO_SetCurrent(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin_x, GPIOCurrent_TypeDef GPIO_Current);

void            LHL_GPIO_SetEXTILine(GPIO_TypeDef *pGPIOx, uint16_t GPIO_Pin_x);

#ifdef __cplusplus
}
#endif                         

#endif

/*********************************End of File**********************************/
