/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_mio.h
 * @version 2025-10-16
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0S3x_MIO_H
#define __LH32M0S3x_MIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* ----------------------------------------------------------------------------
   -- MIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MIO_Peripheral_Access_Layer MIO Peripheral Access Layer
 * @{
 */

///** MIO - Register Layout Typedef */
//typedef struct {
//  __I  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
//  __I  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
//  __IO uint32_t CTRL;                              /**< MIO Control Register, offset: 0x8 */
//  __I  uint32_t PIN;                               /**< Pin State Register, offset: 0xC */
//  __IO uint32_t SHIFTSTAT;                         /**< Shifter Status Register, offset: 0x10 */
//  __IO uint32_t SHIFTERR;                          /**< Shifter Error Register, offset: 0x14 */
//  __IO uint32_t TIMSTAT;                           /**< Timer Status Register, offset: 0x18 */
//       uint8_t RESERVED_0[4];
//  __IO uint32_t SHIFTSIEN;                         /**< Shifter Status Interrupt Enable, offset: 0x20 */
//  __IO uint32_t SHIFTEIEN;                         /**< Shifter Error Interrupt Enable, offset: 0x24 */
//  __IO uint32_t TIMIEN;                            /**< Timer Interrupt Enable Register, offset: 0x28 */
//       uint8_t RESERVED_1[4];
//  __IO uint32_t SHIFTSDEN;                         /**< Shifter Status DMA Enable, offset: 0x30 */
//       uint8_t RESERVED_2[76];
//  __IO uint32_t SHIFTCTL[4];                       /**< Shifter Control N Register, array offset: 0x80, array step: 0x4 */
//       uint8_t RESERVED_3[112];
//  __IO uint32_t SHIFTCFG[4];                       /**< Shifter Configuration N Register, array offset: 0x100, array step: 0x4 */
//       uint8_t RESERVED_4[240];
//  __IO uint32_t SHIFTBUF[4];                       /**< Shifter Buffer N Register, array offset: 0x200, array step: 0x4 */
//       uint8_t RESERVED_5[112];
//  __IO uint32_t SHIFTBUFBIS[4];                    /**< Shifter Buffer N Bit Swapped Register, array offset: 0x280, array step: 0x4 */
//       uint8_t RESERVED_6[112];
//  __IO uint32_t SHIFTBUFBYS[4];                    /**< Shifter Buffer N Byte Swapped Register, array offset: 0x300, array step: 0x4 */
//       uint8_t RESERVED_7[112];
//  __IO uint32_t SHIFTBUFBBS[4];                    /**< Shifter Buffer N Bit Byte Swapped Register, array offset: 0x380, array step: 0x4 */
//       uint8_t RESERVED_8[112];
//  __IO uint32_t TIMCTL[4];                         /**< Timer Control N Register, array offset: 0x400, array step: 0x4 */
//       uint8_t RESERVED_9[112];
//  __IO uint32_t TIMCFG[4];                         /**< Timer Configuration N Register, array offset: 0x480, array step: 0x4 */
//       uint8_t RESERVED_10[112];
//  __IO uint32_t TIMCMP[4];                         /**< Timer Compare N Register, array offset: 0x500, array step: 0x4 */
//} MIO_Type;

/**
  * @brief  MIO_TIMER_x：0或1
  */
 typedef enum {
    MIO_TIMER_0 = 0u,
    MIO_TIMER_1 = 1u,
} MIO_TIMER_t;

/**
  * @brief  MIO_SHIFTER_x：0或1
  */
 typedef enum {
    MIO_SHIFTER_0 = 0u,
    MIO_SHIFTER_1 = 1u,
} MIO_SHIFTER_t;

typedef enum {
    MIO_TIM_TRIG_ACTIVE_HIGH = 0x0u,            /*!< Active high. */
    MIO_TIM_TRIG_ACTIVE_LOW,                    /*!< Active low. */
} MIO_TIM_TRIG_POL_t;

typedef enum {
    MIO_TIM_TRIG_SRC_EXTERNAL = 0x0u,           /*!< External trigger selected. */
    MIO_TIM_TRIG_SRC_INTERNAL,                  /*!< Internal trigger selected. */
} MIO_TIM_TRIG_SRC_t;

typedef enum{
    MIO_PIN_OUTPUT_DISABLED = 0x0u,             /*!< Pin output disabled. */
    MIO_PIN_OPENDRAIN_OR_BIDIRECTION_ENABLED,   /*!< Pin open drain or bidirectional output enable. */
    MIO_PIN_BIDIRECTION_ENABLED,                /*!< Pin bidirectional output data. */
    MIO_PIN_OUTPUT_ENABLED,                     /*!< Pin output. */
} MIO_PIN_CONFIG_t;

typedef enum{
    MIO_PIN_0 = 0x0u,                           /*!< MIO_D0 Pin. */
    MIO_PIN_1,                                  /*!< MIO_D1 Pin. */
    MIO_PIN_2,                                  /*!< MIO_D2 Pin. */
    MIO_PIN_3,                                  /*!< MIO_D3 Pin. */
} MIO_PIN_t;

typedef enum{
    MIO_PIN_ACTIVE_HIGH = 0x0u,                 /*!< Active high. */
    MIO_PIN_ACTIVE_LOW,                         /*!< Active low. */
} MIO_PIN_POL_t;

typedef enum{
    MIO_TIM_DISABLED        = 0x0u,             /*!< Timer Disabled. */
    MIO_TIM_DUAL_8BIT_BAUD,                     /*!< Dual 8-bit counters baud/bit mode. */
    MIO_TIM_DUAL_8BIT_PWM,                      /*!< Dual 8-bit counters PWM mode. */
    MIO_TIM_SINGLE_16BIT,                       /*!< Single 16-bit counter mode. */
} MIO_TIM_MODE_t;

typedef enum{
    MIO_TIM_OUTPUT_HIGH = 0x0u,                 /*!< Logic one when enabled and is not affected by timer reset. */
    MIO_TIM_OUTPUT_LOW,                         /*!< Logic zero when enabled and is not affected by timer reset. */
    MIO_TIM_OUTPUT_HIGH_ON_RESET,               /*!< Logic one when enabled and on timer reset. */
    MIO_TIM_OUTPUT_LOW_ON_RESET,                /*!< Logic zero when enabled and on timer reset. */
} MIO_TIM_OUTPUT_t;

typedef enum{
    MIO_TIM_MIO_CLOCK = 0x0u,                   /*!< Decrement counter on MIO clock, Shift clock equals Timer output. */
    MIO_TIM_TRIGGER_INPUT,                      /*!< Decrement counter on Trigger input (both edges),  Shift clock equals Timer output. */
    MIO_TIM_PIN_INPUT,                          /*!< Decrement counter on Pin input (both edges), Shift clock equals Pin input. */
    MIO_TIM_TRIGGER_INPUT_EQUAL_SHIFT_CLOCK      /*!< Decrement counter on Trigger input (both edges), Shift clock equals Trigger input. */
} MIO_TIM_CLK_t;

typedef enum {
    MIO_TIM_RST_NEVER                   = 0x0u, /*!< Timer never reset. */
    MIO_TIM_RST_PIN_EQUAL_OUTPUT        = 0x2u, /*!< Timer reset on Timer Pin equal to Timer Output. */
    MIO_TIM_RST_TRIGGER_EQUAL_OUTPUT    = 0x3u, /*!< Timer reset on Timer Trigger equal to Timer Output. */
    MIO_TIM_RST_PIN_RISING_EDGE         = 0x4u, /*!< Timer reset on Timer Pin rising edge. */
    MIO_TIM_RST_TRIGGER_RISING_EDGE     = 0x6u, /*!< Timer reset on Trigger rising edge. */
    MIO_TIM_RST_TRIGGER_BOTH_EDGE       = 0x7u, /*!< Timer reset on Trigger rising or falling edge. */
} MIO_TIM_RESET_t;

typedef enum {
    MIO_TIM_DIS_NEVER                   = 0x0u, /*!< Timer never disabled. */
    MIO_TIM_DIS_PRE_TIMER_DISABLE       = 0x1u, /*!< Timer disabled on Timer N-1 disable. */
    MIO_TIM_DIS_COMPARE                 = 0x2u, /*!< Timer disabled on Timer compare. */
    MIO_TIM_DIS_COMPARE_AND_TRIGGER_LOW = 0x3u, /*!< Timer disabled on Timer compare and Trigger Low. */
    MIO_TIM_DIS_PIN_BOTH_EDGE           = 0x4u, /*!< Timer disabled on Pin rising or falling edge. */
    MIO_TIM_DIS_PIN_BOTH_EDGE_AND_TRIGGER_HIGH = 0x5u, /*!< Timer disabled on Pin rising or falling edge provided Trigger is high. */
    MIO_TIM_DIS_TRIGGER_FALLING_EDGE    = 0x6u, /*!< Timer disabled on Trigger falling edge. */
} MIO_TIM_DISABLE_t;

typedef enum {
    MIO_TIM_ENA_ALWAYS                  = 0x0u, /*!< Timer always enabled. */
    MIO_TIM_ENA_PRE_TIMER_ENABLE        = 0x1u, /*!< Timer enabled on Timer N-1 enable. */
    MIO_TIM_ENA_TRIGGER_HIGH            = 0x2u, /*!< Timer enabled on Trigger high. */
    MIO_TIM_ENA_TRIGGER_HIGH_AND_PIN_HIGH = 0x3u, /*!< Timer enabled on Trigger high and Pin high. */
    MIO_TIM_ENA_PIN_RISING_EDGE         = 0x4u, /*!< Timer enabled on Pin rising edge. */
    MIO_TIM_ENA_PIN_RISING_EDGE_AND_TRIGGER_HIGH = 0x5u, /*!< Timer enabled on Pin rising edge and Trigger high. */
    MIO_TIM_ENA_TRIGGER_RISING_EDGE     = 0x6u, /*!< Timer enabled on Trigger rising edge. */
    MIO_TIM_ENA_TRIGGER_BOTH_EDGE       = 0x7u, /*!< Timer enabled on Trigger rising or falling edge. */
} MIO_TIM_ENABLE_t;

typedef enum {
    MIO_TIM_STOP_BIT_DISABLED           = 0x0U, /*!< Stop bit disabled. */
    MIO_TIM_STOP_BIT_ENABLED_ON_COMPARE = 0x1U, /*!< Stop bit is enabled on timer compare. */
    MIO_TIM_STOP_BIT_ENABLED_ON_DISABLE = 0x2U, /*!< Stop bit is enabled on timer disable. */
    MIO_TIM_STOP_BIT_ENABLED_ON_COMPARE_AND_DISABLE = 0x3U, /*!< Stop bit is enabled on timer compare and timer disable. */
} MIO_TIM_STOP_BIT_t;

typedef enum {
    MIO_TIM_START_BIT_DISABLED          = 0x0U, /*!< Start bit disabled. */
    MIO_TIM_START_BIT_ENABLED           = 0x1U, /*!< Start bit enabled. */
} MIO_TIM_START_BIT_t;

/*! @brief Define type of shifter working mode.*/
typedef enum {
    MIO_SHFT_MODE_DISABLED                = 0x0U, /*!< Shifter is disabled. */
    MIO_SHFT_MODE_RECEIVE                 = 0x1U, /*!< Receive mode. */
    MIO_SHFT_MODE_TRANSMIT                = 0x2U, /*!< Transmit mode. */
    MIO_SHFT_MODE_MATCH                   = 0x4U, /*!< Match store mode. */
} MIO_SHIFTER_MODE_t;

/*! @brief Define type of timer polarity for shifter control. */
typedef enum {
    MIO_SHFT_TIM_POL_POS                 = 0x0U, /*!< Shift on positive edge of shift clock. */
    MIO_SHFT_TIM_POL_NEG                 = 0x1U, /*!< Shift on negative edge of shift clock. */
} MIO_SHIFTER_TIM_POL_t;

/*! @brief Define type of shifter input source.*/
typedef enum {
    MIO_SHFT_INPUT_PIN                   = 0x0U, /*!< Shifter input from pin. */
    MIO_SHFT_INPUT_NEXT_OUTPUT           = 0x1U, /*!< Shifter input from Shifter N+1. */
} MIO_SHIFTER_INPUT_SRC_t;

/*! @brief Define of STOP bit configuration.*/
typedef enum {
    MIO_SHFT_STOP_BIT_DISABLED          = 0x0U, /*!< Disable shifter stop bit. */
    MIO_SHFT_STOP_BIT_LOW               = 0x2U, /*!< Set shifter stop bit to logic low level. */
    MIO_SHFT_STOP_BIT_HIGH              = 0x3U, /*!< Set shifter stop bit to logic high level. */
} MIO_SHIFTER_STOP_BIT_t;

/*! @brief Define type of START bit configuration.*/
typedef enum {
    MIO_SHFT_START_BIT_DISABLED_AND_LOAD_ON_ENABLE = 0x0U, /*!< Disable shifter start bit, transmitter loads
                                                             data on enable. */
    MIO_SHFT_START_BIT_DISABLED_AND_LOAD_ON_SHIFT = 0x1U,  /*!< Disable shifter start bit, transmitter loads
                                                             data on first shift. */
    MIO_SHFT_START_BIT_LOW              = 0x2U, /*!< Set shifter start bit to logic low level. */
    MIO_SHFT_START_BIT_HIGH             = 0x3U, /*!< Set shifter start bit to logic high level. */
} MIO_SHIFTER_START_BIT_t;

/*! @brief Define of STOP bit configuration.*/
typedef enum {
    MIO_SHFT_DATA_WIDTH_1BIT              = 0x0U, /*!< 配置每个shift clock移位1位. */
    MIO_SHFT_DATA_WIDTH_2BIT              = 0x1U, /*!< 配置每个shift clock移位2位.. */
    MIO_SHFT_DATA_WIDTH_4BIT              = 0x2U, /*!< 配置每个shift clock移位4位.. */
    MIO_SHFT_DATA_WIDTH_8BIT              = 0x4U, /*!< 配置每个shift clock移位8位.. */
    MIO_SHFT_DATA_WIDTH_16BIT             = 0x8U, /*!< 配置每个shift clock移位16位.. */
    MIO_SHFT_DATA_WIDTH_32BIT             = 0x10U, /*!< 配置每个shift clock移位32位.. */
} MIO_SHIFTER_DATA_WIDTH_t;

typedef struct {
    /* Trigger. */
    uint8_t             Trigger_Select;         /*!< The internal trigger selection number using MACROs. */
    
    MIO_TIM_TRIG_POL_t  Trigger_Polarity;       /*!< Trigger Polarity. */
    
    MIO_TIM_TRIG_SRC_t  Trigger_Source;         /*!< Trigger Source, internal (see 'trgsel') or external. */
    
    /* Pin. */
    MIO_PIN_CONFIG_t    Pin_Config;             /*!< Timer Pin Configuration. */
    
    MIO_PIN_t           Pin_Select;            /*!< Timer Pin number Select. */
    
    MIO_PIN_POL_t       Pin_Polarity;           /*!< Timer Pin Polarity. */
    
    /* Timer. */
    MIO_TIM_MODE_t      Timer_Mode;             /*!< Timer work Mode. */
    
    MIO_TIM_OUTPUT_t    Timer_Output;           /*!< Configures the initial state of the Timer Output and
                                                    whether it is affected by the Timer reset. */
    MIO_TIM_CLK_t       Timer_Decrement_Clock;  /*!< Configures the source of the Timer decrement and the
                                                    source of the Shift clock. */
    MIO_TIM_RESET_t     Timer_Reset_Condition;  /*!< Configures the condition that causes the timer counter
                                                    (and optionally the timer output) to be reset. */
    MIO_TIM_DISABLE_t   Timer_Disable_Condition;/*!< Configures the condition that causes the Timer to be
                                                    disabled and stop decrementing. */
    MIO_TIM_ENABLE_t    Timer_Enable_Condition; /*!< Configures the condition that causes the Timer to be
                                                    enabled and start decrementing. */
    MIO_TIM_STOP_BIT_t  Timer_StopBit_Condition;    /*!< Timer STOP Bit generation. */
    
    MIO_TIM_START_BIT_t Timer_StartBit_Condition;   /*!< Timer STRAT Bit generation. */
    
    uint8_t             Reserved[2];
    
    uint32_t            Timer_Compare;              /*!< Value for Timer Compare N Register. */
    
} MIO_TIM_InitTypedef;

/*! @brief Define MIO shifter configuration structure. */
typedef struct {

    /* Timer. */
    MIO_TIMER_t             Shifter_Timer;              /*!< Selects which Timer is used for controlling the
                                                    logic/shift register and generating the Shift clock. */
    MIO_SHIFTER_TIM_POL_t   Shifter_Timer_Polarity;     /*!< Timer Polarity. */
    /* Pin. */
    MIO_PIN_t               Shifter_Pin;                /*!< Shifter Pin number Select. */
    MIO_PIN_CONFIG_t        Shifter_Pin_Config;         /*!< Shifter Pin Configuration. */
    MIO_PIN_POL_t           Shifter_Pin_Polarity;       /*!< Shifter Pin Polarity. */
    /* Shifter. */
    MIO_SHIFTER_MODE_t      Shifter_Mode;               /*!< Configures the mode of the Shifter. */
//  MIO_SHIFTER_DATA_WIDTH_t    Shifter_Width;          /*!< Configures the data width of the shifter.Reserved. */
    MIO_SHIFTER_INPUT_SRC_t Shifter_Input;              /*!< Selects the input source for the shifter. */
    MIO_SHIFTER_STOP_BIT_t  Shifter_Stop;               /*!< Shifter STOP bit. */
    MIO_SHIFTER_START_BIT_t Shifter_Start;              /*!< Shifter START bit. */
    
} MIO_SHIFTER_InitTypedef;

/** 
  * @brief  MIO UART Init Structure definition  
  */   
typedef struct
{
    uint32_t MIO_UART_BaudRate;                         /*!< 设定MIO模拟UART的波特率 */

    MIO_PIN_t MIO_UART_RX_Pin;                              /*!< 设定MIO模拟UART的RX接收引脚 */
    
    MIO_TIMER_t MIO_UART_RX_Timer;                      /*!< 设定MIO UART RX使用的定时器 */
    
    MIO_SHIFTER_t MIO_UART_RX_Shifter;
    
    FunctionalState MIO_UART_RX;

    MIO_PIN_t MIO_UART_TX_Pin;                              /*!< 设定MIO模拟UART的TX发送引脚 */
    
    MIO_TIMER_t MIO_UART_TX_Timer;                      /*!< 设定MIO UART TX使用的定时器 */
    
    MIO_SHIFTER_t MIO_UART_TX_Shifter;
    
    FunctionalState MIO_UART_TX;

} MIO_UART_HandleTypeDef;

/* ----------------------------------------------------------------------------
   -- MIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MIO_Register_Masks MIO Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */
#define MIO_VERID_FEATURE_MASK                (0xFFFFU)
#define MIO_VERID_FEATURE_SHIFT               (0U)
/*! FEATURE - Feature Specification Number
 *  0b0000000000000000..Standard features implemented.
 *  0b0000000000000001..Supports state, logic and parallel modes.
 */
#define MIO_VERID_FEATURE(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_VERID_FEATURE_SHIFT)) & MIO_VERID_FEATURE_MASK)
#define MIO_VERID_MINOR_MASK                  (0xFF0000U)
#define MIO_VERID_MINOR_SHIFT                 (16U)
/*! MINOR - Minor Version Number
 */
#define MIO_VERID_MINOR(x)                    (((uint32_t)(((uint32_t)(x)) << MIO_VERID_MINOR_SHIFT)) & MIO_VERID_MINOR_MASK)
#define MIO_VERID_MAJOR_MASK                  (0xFF000000U)
#define MIO_VERID_MAJOR_SHIFT                 (24U)
/*! MAJOR - Major Version Number
 */
#define MIO_VERID_MAJOR(x)                    (((uint32_t)(((uint32_t)(x)) << MIO_VERID_MAJOR_SHIFT)) & MIO_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */
#define MIO_PARAM_SHIFTER_MASK                (0xFFU)
#define MIO_PARAM_SHIFTER_SHIFT               (0U)
/*! SHIFTER - Shifter Number
 */
#define MIO_PARAM_SHIFTER(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_PARAM_SHIFTER_SHIFT)) & MIO_PARAM_SHIFTER_MASK)
#define MIO_PARAM_TIMER_MASK                  (0xFF00U)
#define MIO_PARAM_TIMER_SHIFT                 (8U)
/*! TIMER - Timer Number
 */
#define MIO_PARAM_TIMER(x)                    (((uint32_t)(((uint32_t)(x)) << MIO_PARAM_TIMER_SHIFT)) & MIO_PARAM_TIMER_MASK)
#define MIO_PARAM_PIN_MASK                    (0xFF0000U)
#define MIO_PARAM_PIN_SHIFT                   (16U)
/*! PIN - Pin Number
 */
#define MIO_PARAM_PIN(x)                      (((uint32_t)(((uint32_t)(x)) << MIO_PARAM_PIN_SHIFT)) & MIO_PARAM_PIN_MASK)
#define MIO_PARAM_TRIGGER_MASK                (0xFF000000U)
#define MIO_PARAM_TRIGGER_SHIFT               (24U)
/*! TRIGGER - Trigger Number
 */
#define MIO_PARAM_TRIGGER(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_PARAM_TRIGGER_SHIFT)) & MIO_PARAM_TRIGGER_MASK)
/*! @} */

/*! @name CTRL - MIO Control Register */
/*! @{ */
#define MIO_CTRL_MIOEN_MASK                  (0x1U)
#define MIO_CTRL_MIOEN_SHIFT                 (0U)
/*! MIOEN - MIO Enable
 *  0b0..MIO module is disabled.
 *  0b1..MIO module is enabled.
 */
#define MIO_CTRL_MIOEN(x)                    (((uint32_t)(((uint32_t)(x)) << MIO_CTRL_MIOEN_SHIFT)) & MIO_CTRL_MIOEN_MASK)
#define MIO_CTRL_SWRST_MASK                   (0x2U)
#define MIO_CTRL_SWRST_SHIFT                  (1U)
/*! SWRST - Software Reset
 *  0b0..Software reset is disabled
 *  0b1..Software reset is enabled, all MIO registers except the Control Register are reset.
 */
#define MIO_CTRL_SWRST(x)                     (((uint32_t)(((uint32_t)(x)) << MIO_CTRL_SWRST_SHIFT)) & MIO_CTRL_SWRST_MASK)
#define MIO_CTRL_FASTACC_MASK                 (0x4U)
#define MIO_CTRL_FASTACC_SHIFT                (2U)
/*! FASTACC - Fast Access
 *  0b0..Configures for normal register accesses to MIO
 *  0b1..Configures for fast register accesses to MIO
 */
#define MIO_CTRL_FASTACC(x)                   (((uint32_t)(((uint32_t)(x)) << MIO_CTRL_FASTACC_SHIFT)) & MIO_CTRL_FASTACC_MASK)
#define MIO_CTRL_DBGE_MASK                    (0x40000000U)
#define MIO_CTRL_DBGE_SHIFT                   (30U)
/*! DBGE - Debug Enable
 *  0b0..MIO is disabled in debug modes.
 *  0b1..MIO is enabled in debug modes
 */
#define MIO_CTRL_DBGE(x)                      (((uint32_t)(((uint32_t)(x)) << MIO_CTRL_DBGE_SHIFT)) & MIO_CTRL_DBGE_MASK)
#define MIO_CTRL_DOZEN_MASK                   (0x80000000U)
#define MIO_CTRL_DOZEN_SHIFT                  (31U)
/*! DOZEN - Doze Enable
 *  0b0..MIO enabled in Doze modes.
 *  0b1..MIO disabled in Doze modes.
 */
#define MIO_CTRL_DOZEN(x)                     (((uint32_t)(((uint32_t)(x)) << MIO_CTRL_DOZEN_SHIFT)) & MIO_CTRL_DOZEN_MASK)
/*! @} */

/*! @name PIN - Pin State Register */
/*! @{ */
#define MIO_PIN_PDI_MASK                      (0xFFU)
#define MIO_PIN_PDI_SHIFT                     (0U)
/*! PDI - Pin Data Input
 */
#define MIO_PIN_PDI(x)                        (((uint32_t)(((uint32_t)(x)) << MIO_PIN_PDI_SHIFT)) & MIO_PIN_PDI_MASK)
/*! @} */

/*! @name SHIFTSTAT - Shifter Status Register */
/*! @{ */
#define MIO_SHIFTSTAT_SSF_MASK                (0xFU)
#define MIO_SHIFTSTAT_SSF_SHIFT               (0U)
/*! SSF - Shifter Status Flag
 *  0b0000..Status flag is clear
 *  0b0001..Status flag is set
 */
#define MIO_SHIFTSTAT_SSF(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTSTAT_SSF_SHIFT)) & MIO_SHIFTSTAT_SSF_MASK)
/*! @} */

/*! @name SHIFTERR - Shifter Error Register */
/*! @{ */
#define MIO_SHIFTERR_SEF_MASK                 (0xFU)
#define MIO_SHIFTERR_SEF_SHIFT                (0U)
/*! SEF - Shifter Error Flags
 *  0b0000..Shifter Error Flag is clear
 *  0b0001..Shifter Error Flag is set
 */
#define MIO_SHIFTERR_SEF(x)                   (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTERR_SEF_SHIFT)) & MIO_SHIFTERR_SEF_MASK)
/*! @} */

/*! @name TIMSTAT - Timer Status Register */
/*! @{ */
#define MIO_TIMSTAT_TSF_MASK                  (0xFU)
#define MIO_TIMSTAT_TSF_SHIFT                 (0U)
/*! TSF - Timer Status Flags
 *  0b0000..Timer Status Flag is clear
 *  0b0001..Timer Status Flag is set
 */
#define MIO_TIMSTAT_TSF(x)                    (((uint32_t)(((uint32_t)(x)) << MIO_TIMSTAT_TSF_SHIFT)) & MIO_TIMSTAT_TSF_MASK)
/*! @} */

/*! @name SHIFTSIEN - Shifter Status Interrupt Enable */
/*! @{ */
#define MIO_SHIFTSIEN_SSIE_MASK               (0xFU)
#define MIO_SHIFTSIEN_SSIE_SHIFT              (0U)
/*! SSIE - Shifter Status Interrupt Enable
 *  0b0000..Shifter Status Flag interrupt disabled
 *  0b0001..Shifter Status Flag interrupt enabled
 */
#define MIO_SHIFTSIEN_SSIE(x)                 (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTSIEN_SSIE_SHIFT)) & MIO_SHIFTSIEN_SSIE_MASK)
/*! @} */

/*! @name SHIFTEIEN - Shifter Error Interrupt Enable */
/*! @{ */
#define MIO_SHIFTEIEN_SEIE_MASK               (0xFU)
#define MIO_SHIFTEIEN_SEIE_SHIFT              (0U)
/*! SEIE - Shifter Error Interrupt Enable
 *  0b0000..Shifter Error Flag interrupt disabled
 *  0b0001..Shifter Error Flag interrupt enabled
 */
#define MIO_SHIFTEIEN_SEIE(x)                 (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTEIEN_SEIE_SHIFT)) & MIO_SHIFTEIEN_SEIE_MASK)
/*! @} */

/*! @name TIMIEN - Timer Interrupt Enable Register */
/*! @{ */
#define MIO_TIMIEN_TEIE_MASK                  (0xFU)
#define MIO_TIMIEN_TEIE_SHIFT                 (0U)
/*! TEIE - Timer Status Interrupt Enable
 *  0b0000..Timer Status Flag interrupt is disabled
 *  0b0001..Timer Status Flag interrupt is enabled
 */
#define MIO_TIMIEN_TEIE(x)                    (((uint32_t)(((uint32_t)(x)) << MIO_TIMIEN_TEIE_SHIFT)) & MIO_TIMIEN_TEIE_MASK)
/*! @} */

/*! @name SHIFTSDEN - Shifter Status DMA Enable */
/*! @{ */
#define MIO_SHIFTSDEN_SSDE_MASK               (0xFU)
#define MIO_SHIFTSDEN_SSDE_SHIFT              (0U)
/*! SSDE - Shifter Status DMA Enable
 *  0b0000..Shifter Status Flag DMA request is disabled
 *  0b0001..Shifter Status Flag DMA request is enabled
 */
#define MIO_SHIFTSDEN_SSDE(x)                 (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTSDEN_SSDE_SHIFT)) & MIO_SHIFTSDEN_SSDE_MASK)
/*! @} */

/*! @name SHIFTCTL - Shifter Control N Register */
/*! @{ */
#define MIO_SHIFTCTL_SMOD_MASK                (0x7U)
#define MIO_SHIFTCTL_SMOD_SHIFT               (0U)
/*! SMOD - Shifter Mode
 *  0b000..Disabled.
 *  0b001..Receive mode. Captures the current Shifter content into the SHIFTBUF on expiration of the Timer.
 *  0b010..Transmit mode. Load SHIFTBUF contents into the Shifter on expiration of the Timer.
 *  0b011..Reserved.
 *  0b100..Match Store mode. Shifter data is compared to SHIFTBUF content on expiration of the Timer.
 *  0b101..Match Continuous mode. Shifter data is continuously compared to SHIFTBUF contents.
 *  0b110..Reserved.
 *  0b111..Reserved.
 */
#define MIO_SHIFTCTL_SMOD(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCTL_SMOD_SHIFT)) & MIO_SHIFTCTL_SMOD_MASK)
#define MIO_SHIFTCTL_PINPOL_MASK              (0x80U)
#define MIO_SHIFTCTL_PINPOL_SHIFT             (7U)
/*! PINPOL - Shifter Pin Polarity
 *  0b0..Pin is active high
 *  0b1..Pin is active low
 */
#define MIO_SHIFTCTL_PINPOL(x)                (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCTL_PINPOL_SHIFT)) & MIO_SHIFTCTL_PINPOL_MASK)
#define MIO_SHIFTCTL_PINSEL_MASK              (0x700U)
#define MIO_SHIFTCTL_PINSEL_SHIFT             (8U)
/*! PINSEL - Shifter Pin Select
 */
#define MIO_SHIFTCTL_PINSEL(x)                (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCTL_PINSEL_SHIFT)) & MIO_SHIFTCTL_PINSEL_MASK)
#define MIO_SHIFTCTL_PINCFG_MASK              (0x30000U)
#define MIO_SHIFTCTL_PINCFG_SHIFT             (16U)
/*! PINCFG - Shifter Pin Configuration
 *  0b00..Shifter pin output disabled
 *  0b01..Shifter pin open drain or bidirectional output enable
 *  0b10..Shifter pin bidirectional output data
 *  0b11..Shifter pin output
 */
#define MIO_SHIFTCTL_PINCFG(x)                (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCTL_PINCFG_SHIFT)) & MIO_SHIFTCTL_PINCFG_MASK)
#define MIO_SHIFTCTL_TIMPOL_MASK              (0x800000U)
#define MIO_SHIFTCTL_TIMPOL_SHIFT             (23U)
/*! TIMPOL - Timer Polarity
 *  0b0..Shift on posedge of Shift clock
 *  0b1..Shift on negedge of Shift clock
 */
#define MIO_SHIFTCTL_TIMPOL(x)                (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCTL_TIMPOL_SHIFT)) & MIO_SHIFTCTL_TIMPOL_MASK)
#define MIO_SHIFTCTL_TIMSEL_MASK              (0x3000000U)
#define MIO_SHIFTCTL_TIMSEL_SHIFT             (24U)
/*! TIMSEL - Timer Select
 */
#define MIO_SHIFTCTL_TIMSEL(x)                (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCTL_TIMSEL_SHIFT)) & MIO_SHIFTCTL_TIMSEL_MASK)
/*! @} */

/* The count of MIO_SHIFTCTL */
#define MIO_SHIFTCTL_COUNT                    (4U)

/*! @name SHIFTCFG - Shifter Configuration N Register */
/*! @{ */
#define MIO_SHIFTCFG_SSTART_MASK              (0x3U)
#define MIO_SHIFTCFG_SSTART_SHIFT             (0U)
/*! SSTART - Shifter Start bit
 *  0b00..Start bit disabled for transmitter/receiver/match store, transmitter loads data on enable
 *  0b01..Start bit disabled for transmitter/receiver/match store, transmitter loads data on first shift
 *  0b10..Transmitter outputs start bit value 0 before loading data on first shift, receiver/match store sets error flag if start bit is not 0
 *  0b11..Transmitter outputs start bit value 1 before loading data on first shift, receiver/match store sets error flag if start bit is not 1
 */
#define MIO_SHIFTCFG_SSTART(x)                (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCFG_SSTART_SHIFT)) & MIO_SHIFTCFG_SSTART_MASK)
#define MIO_SHIFTCFG_SSTOP_MASK               (0x30U)
#define MIO_SHIFTCFG_SSTOP_SHIFT              (4U)
/*! SSTOP - Shifter Stop bit
 *  0b00..Stop bit disabled for transmitter/receiver/match store
 *  0b01..Reserved for transmitter/receiver/match store
 *  0b10..Transmitter outputs stop bit value 0 on store, receiver/match store sets error flag if stop bit is not 0
 *  0b11..Transmitter outputs stop bit value 1 on store, receiver/match store sets error flag if stop bit is not 1
 */
#define MIO_SHIFTCFG_SSTOP(x)                 (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCFG_SSTOP_SHIFT)) & MIO_SHIFTCFG_SSTOP_MASK)
#define MIO_SHIFTCFG_INSRC_MASK               (0x100U)
#define MIO_SHIFTCFG_INSRC_SHIFT              (8U)
/*! INSRC - Input Source
 *  0b0..Pin
 *  0b1..Shifter N+1 Output
 */
#define MIO_SHIFTCFG_INSRC(x)                 (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTCFG_INSRC_SHIFT)) & MIO_SHIFTCFG_INSRC_MASK)
/*! @} */

/* The count of MIO_SHIFTCFG */
#define MIO_SHIFTCFG_COUNT                    (4U)

/*! @name SHIFTBUF - Shifter Buffer N Register */
/*! @{ */
#define MIO_SHIFTBUF_SHIFTBUF_MASK            (0xFFFFFFFFU)
#define MIO_SHIFTBUF_SHIFTBUF_SHIFT           (0U)
/*! SHIFTBUF - Shift Buffer
 */
#define MIO_SHIFTBUF_SHIFTBUF(x)              (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTBUF_SHIFTBUF_SHIFT)) & MIO_SHIFTBUF_SHIFTBUF_MASK)
/*! @} */

/* The count of MIO_SHIFTBUF */
#define MIO_SHIFTBUF_COUNT                    (4U)

/*! @name SHIFTBUFBIS - Shifter Buffer N Bit Swapped Register */
/*! @{ */
#define MIO_SHIFTBUFBIS_SHIFTBUFBIS_MASK      (0xFFFFFFFFU)
#define MIO_SHIFTBUFBIS_SHIFTBUFBIS_SHIFT     (0U)
/*! SHIFTBUFBIS - Shift Buffer
 */
#define MIO_SHIFTBUFBIS_SHIFTBUFBIS(x)        (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTBUFBIS_SHIFTBUFBIS_SHIFT)) & MIO_SHIFTBUFBIS_SHIFTBUFBIS_MASK)
/*! @} */

/* The count of MIO_SHIFTBUFBIS */
#define MIO_SHIFTBUFBIS_COUNT                 (4U)

/*! @name SHIFTBUFBYS - Shifter Buffer N Byte Swapped Register */
/*! @{ */
#define MIO_SHIFTBUFBYS_SHIFTBUFBYS_MASK      (0xFFFFFFFFU)
#define MIO_SHIFTBUFBYS_SHIFTBUFBYS_SHIFT     (0U)
/*! SHIFTBUFBYS - Shift Buffer
 */
#define MIO_SHIFTBUFBYS_SHIFTBUFBYS(x)        (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTBUFBYS_SHIFTBUFBYS_SHIFT)) & MIO_SHIFTBUFBYS_SHIFTBUFBYS_MASK)
/*! @} */

/* The count of MIO_SHIFTBUFBYS */
#define MIO_SHIFTBUFBYS_COUNT                 (4U)

/*! @name SHIFTBUFBBS - Shifter Buffer N Bit Byte Swapped Register */
/*! @{ */
#define MIO_SHIFTBUFBBS_SHIFTBUFBBS_MASK      (0xFFFFFFFFU)
#define MIO_SHIFTBUFBBS_SHIFTBUFBBS_SHIFT     (0U)
/*! SHIFTBUFBBS - Shift Buffer
 */
#define MIO_SHIFTBUFBBS_SHIFTBUFBBS(x)        (((uint32_t)(((uint32_t)(x)) << MIO_SHIFTBUFBBS_SHIFTBUFBBS_SHIFT)) & MIO_SHIFTBUFBBS_SHIFTBUFBBS_MASK)
/*! @} */

/* The count of MIO_SHIFTBUFBBS */
#define MIO_SHIFTBUFBBS_COUNT                 (4U)

/*! @name TIMCTL - Timer Control N Register */
/*! @{ */
#define MIO_TIMCTL_TIMOD_MASK                 (0x3U)
#define MIO_TIMCTL_TIMOD_SHIFT                (0U)
/*! TIMOD - Timer Mode
 *  0b00..Timer Disabled.
 *  0b01..Dual 8-bit counters baud/bit mode.
 *  0b10..Dual 8-bit counters PWM mode.
 *  0b11..Single 16-bit counter mode.
 */
#define MIO_TIMCTL_TIMOD(x)                   (((uint32_t)(((uint32_t)(x)) << MIO_TIMCTL_TIMOD_SHIFT)) & MIO_TIMCTL_TIMOD_MASK)
#define MIO_TIMCTL_PINPOL_MASK                (0x80U)
#define MIO_TIMCTL_PINPOL_SHIFT               (7U)
/*! PINPOL - Timer Pin Polarity
 *  0b0..Pin is active high
 *  0b1..Pin is active low
 */
#define MIO_TIMCTL_PINPOL(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCTL_PINPOL_SHIFT)) & MIO_TIMCTL_PINPOL_MASK)
#define MIO_TIMCTL_PINSEL_MASK                (0x700U)
#define MIO_TIMCTL_PINSEL_SHIFT               (8U)
/*! PINSEL - Timer Pin Select
 */
#define MIO_TIMCTL_PINSEL(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCTL_PINSEL_SHIFT)) & MIO_TIMCTL_PINSEL_MASK)
#define MIO_TIMCTL_PINCFG_MASK                (0x30000U)
#define MIO_TIMCTL_PINCFG_SHIFT               (16U)
/*! PINCFG - Timer Pin Configuration
 *  0b00..Timer pin output disabled
 *  0b01..Timer pin open drain or bidirectional output enable
 *  0b10..Timer pin bidirectional output data
 *  0b11..Timer pin output
 */
#define MIO_TIMCTL_PINCFG(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCTL_PINCFG_SHIFT)) & MIO_TIMCTL_PINCFG_MASK)
#define MIO_TIMCTL_TRGSRC_MASK                (0x400000U)
#define MIO_TIMCTL_TRGSRC_SHIFT               (22U)
/*! TRGSRC - Trigger Source
 *  0b0..External trigger selected
 *  0b1..Internal trigger selected
 */
#define MIO_TIMCTL_TRGSRC(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCTL_TRGSRC_SHIFT)) & MIO_TIMCTL_TRGSRC_MASK)
#define MIO_TIMCTL_TRGPOL_MASK                (0x800000U)
#define MIO_TIMCTL_TRGPOL_SHIFT               (23U)
/*! TRGPOL - Trigger Polarity
 *  0b0..Trigger active high
 *  0b1..Trigger active low
 */
#define MIO_TIMCTL_TRGPOL(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCTL_TRGPOL_SHIFT)) & MIO_TIMCTL_TRGPOL_MASK)
#define MIO_TIMCTL_TRGSEL_MASK                (0xF000000U)
#define MIO_TIMCTL_TRGSEL_SHIFT               (24U)
/*! TRGSEL - Trigger Select
 */
#define MIO_TIMCTL_TRGSEL(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCTL_TRGSEL_SHIFT)) & MIO_TIMCTL_TRGSEL_MASK)
/*! @} */

/* The count of MIO_TIMCTL */
#define MIO_TIMCTL_COUNT                      (4U)

/*! @name TIMCFG - Timer Configuration N Register */
/*! @{ */
#define MIO_TIMCFG_TSTART_MASK                (0x2U)
#define MIO_TIMCFG_TSTART_SHIFT               (1U)
/*! TSTART - Timer Start Bit
 *  0b0..Start bit disabled
 *  0b1..Start bit enabled
 */
#define MIO_TIMCFG_TSTART(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCFG_TSTART_SHIFT)) & MIO_TIMCFG_TSTART_MASK)
#define MIO_TIMCFG_TSTOP_MASK                 (0x30U)
#define MIO_TIMCFG_TSTOP_SHIFT                (4U)
/*! TSTOP - Timer Stop Bit
 *  0b00..Stop bit disabled
 *  0b01..Stop bit is enabled on timer compare
 *  0b10..Stop bit is enabled on timer disable
 *  0b11..Stop bit is enabled on timer compare and timer disable
 */
#define MIO_TIMCFG_TSTOP(x)                   (((uint32_t)(((uint32_t)(x)) << MIO_TIMCFG_TSTOP_SHIFT)) & MIO_TIMCFG_TSTOP_MASK)
#define MIO_TIMCFG_TIMENA_MASK                (0x700U)
#define MIO_TIMCFG_TIMENA_SHIFT               (8U)
/*! TIMENA - Timer Enable
 *  0b000..Timer always enabled
 *  0b001..Timer enabled on Timer N-1 enable
 *  0b010..Timer enabled on Trigger high
 *  0b011..Timer enabled on Trigger high and Pin high
 *  0b100..Timer enabled on Pin rising edge
 *  0b101..Timer enabled on Pin rising edge and Trigger high
 *  0b110..Timer enabled on Trigger rising edge
 *  0b111..Timer enabled on Trigger rising or falling edge
 */
#define MIO_TIMCFG_TIMENA(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCFG_TIMENA_SHIFT)) & MIO_TIMCFG_TIMENA_MASK)
#define MIO_TIMCFG_TIMDIS_MASK                (0x7000U)
#define MIO_TIMCFG_TIMDIS_SHIFT               (12U)
/*! TIMDIS - Timer Disable
 *  0b000..Timer never disabled
 *  0b001..Timer disabled on Timer N-1 disable
 *  0b010..Timer disabled on Timer compare
 *  0b011..Timer disabled on Timer compare and Trigger Low
 *  0b100..Timer disabled on Pin rising or falling edge
 *  0b101..Timer disabled on Pin rising or falling edge provided Trigger is high
 *  0b110..Timer disabled on Trigger falling edge
 *  0b111..Reserved
 */
#define MIO_TIMCFG_TIMDIS(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCFG_TIMDIS_SHIFT)) & MIO_TIMCFG_TIMDIS_MASK)
#define MIO_TIMCFG_TIMRST_MASK                (0x70000U)
#define MIO_TIMCFG_TIMRST_SHIFT               (16U)
/*! TIMRST - Timer Reset
 *  0b000..Timer never reset
 *  0b001..Reserved
 *  0b010..Timer reset on Timer Pin equal to Timer Output
 *  0b011..Timer reset on Timer Trigger equal to Timer Output
 *  0b100..Timer reset on Timer Pin rising edge
 *  0b101..Reserved
 *  0b110..Timer reset on Trigger rising edge
 *  0b111..Timer reset on Trigger rising or falling edge
 */
#define MIO_TIMCFG_TIMRST(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCFG_TIMRST_SHIFT)) & MIO_TIMCFG_TIMRST_MASK)
#define MIO_TIMCFG_TIMDEC_MASK                (0x300000U)
#define MIO_TIMCFG_TIMDEC_SHIFT               (20U)
/*! TIMDEC - Timer Decrement
 *  0b00..Decrement counter on MIO clock, Shift clock equals Timer output.
 *  0b01..Decrement counter on Trigger input (both edges), Shift clock equals Timer output.
 *  0b10..Decrement counter on Pin input (both edges), Shift clock equals Pin input.
 *  0b11..Decrement counter on Trigger input (both edges), Shift clock equals Trigger input.
 */
#define MIO_TIMCFG_TIMDEC(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCFG_TIMDEC_SHIFT)) & MIO_TIMCFG_TIMDEC_MASK)
#define MIO_TIMCFG_TIMOUT_MASK                (0x3000000U)
#define MIO_TIMCFG_TIMOUT_SHIFT               (24U)
/*! TIMOUT - Timer Output
 *  0b00..Timer output is logic one when enabled and is not affected by timer reset
 *  0b01..Timer output is logic zero when enabled and is not affected by timer reset
 *  0b10..Timer output is logic one when enabled and on timer reset
 *  0b11..Timer output is logic zero when enabled and on timer reset
 */
#define MIO_TIMCFG_TIMOUT(x)                  (((uint32_t)(((uint32_t)(x)) << MIO_TIMCFG_TIMOUT_SHIFT)) & MIO_TIMCFG_TIMOUT_MASK)
/*! @} */

/* The count of MIO_TIMCFG */
#define MIO_TIMCFG_COUNT                      (4U)

/*! @name TIMCMP - Timer Compare N Register */
/*! @{ */
#define MIO_TIMCMP_CMP_MASK                   (0xFFFFU)
#define MIO_TIMCMP_CMP_SHIFT                  (0U)
/*! CMP - Timer Compare Value
 */
#define MIO_TIMCMP_CMP(x)                     (((uint32_t)(((uint32_t)(x)) << MIO_TIMCMP_CMP_SHIFT)) & MIO_TIMCMP_CMP_MASK)
/*! @} */

/* The count of MIO_TIMCMP */
#define MIO_TIMCMP_COUNT                      (4U)


/*!
 * @}
 */ /* end of group MIO_Register_Masks */


/* MIO - Peripheral instance base addresses */
/** Peripheral MIO base address */
//#define MIO_BASE                              (0x40018000u)
/** Peripheral MIO base pointer */
#define MIO                                   ((MIO_Type *)MIO_BASE)
/** Array initializer of MIO peripheral base addresses */
#define MIO_BASE_ADDRS                        { MIO_BASE }
/** Array initializer of MIO peripheral base pointers */
#define MIO_BASE_PTRS                         { MIO }
/** Interrupt vectors for the MIO peripheral type */
#define MIO_IRQS                              { MIO_IRQn }

/*!
 * @}
 */ /* end of group MIO_Peripheral_Access_Layer */

/*!
 * @addtogroup mio_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum {
    MIO_SHIFT0_IT_SSIE,
    MIO_SHIFT1_IT_SSIE,
    MIO_SHIFT0_IT_SEIE,
    MIO_SHIFT1_IT_SEIE,
    MIO_TIMER0_IT_TSIE,
    MIO_TIMER1_IT_TSIE,
} MIO_IT_t;

typedef enum {
    MIO_SHIFT0_IT_FLAG_SSF,
    MIO_SHIFT1_IT_FLAG_SSF,
    MIO_SHIFT0_IT_FLAG_SEF,
    MIO_SHIFT1_IT_FLAG_SEF,
    MIO_TIMER0_IT_FLAG_TSF,
    MIO_TIMER1_IT_FLAG_TSF,
} MIO_IT_FLAG_t;
    
typedef enum {
    MIO_SHIFT0_FLAG_SSF,
    MIO_SHIFT1_FLAG_SSF,
    MIO_SHIFT0_FLAG_SEF,
    MIO_SHIFT1_FLAG_SEF,
    MIO_TIMER0_FLAG_TSF,
    MIO_TIMER1_FLAG_TSF,
} MIO_FLAG_t;

#define MIO_TIM_TRIG_PIN(x)            (((uint32_t)(x) & 0xFF) << 1U)
#define MIO_TIM_TRIG_SHIFT(x)          ((((uint32_t)(x) & 0xFF) << 2U) | 0x1U)
#define MIO_TIM_TRIG_TIMER(x)          (((uint8_t)(x) << 2U) | 0x3U)
#define MIO_TIM_TRIG_XLINK(x)          ((uint8_t)(x))

/*! @brief Calculate MIO timer trigger.*/
//#define MIO_TIMER_TRIGGER_SEL_PININPUT(x)   ((uint32_t)(x) << 1U)
//#define MIO_TIMER_TRIGGER_SEL_SHIFTnSTAT(x) (((uint32_t)(x) << 2U) | 0x1U)
//#define MIO_TIMER_TRIGGER_SEL_TIMn(x)       (((uint32_t)(x) << 2U) | 0x3U)

/*! @brief Define time of timer trigger polarity.*/
typedef enum _mio_timer_trigger_polarity
{
    MIO_TimerTriggerPolarityActiveHigh = 0x0U, /*!< Active high. */
    MIO_TimerTriggerPolarityActiveLow  = 0x1U, /*!< Active low. */
} mio_timer_trigger_polarity_t;

/*! @brief Define type of timer trigger source.*/
typedef enum _mio_timer_trigger_source
{
    MIO_TimerTriggerSourceExternal = 0x0U, /*!< External trigger selected. */
    MIO_TimerTriggerSourceInternal = 0x1U, /*!< Internal trigger selected. */
} mio_timer_trigger_source_t;

/*! @brief Define type of timer/shifter pin configuration.*/
typedef enum _mio_pin_config
{
    MIO_PinConfigOutputDisabled         = 0x0U, /*!< Pin output disabled. */
    MIO_PinConfigOpenDrainOrBidirection = 0x1U, /*!< Pin open drain or bidirectional output enable. */
    MIO_PinConfigBidirectionOutputData  = 0x2U, /*!< Pin bidirectional output data. */
    MIO_PinConfigOutput                 = 0x3U, /*!< Pin output. */
} mio_pin_config_t;

/*! @brief Definition of pin polarity.*/
typedef enum _mio_pin_polarity
{
    MIO_PinActiveHigh = 0x0U, /*!< Active high. */
    MIO_PinActiveLow  = 0x1U, /*!< Active low. */
} mio_pin_polarity_t;

/*! @brief Define type of timer work mode.*/
typedef enum _mio_timer_mode
{
    MIO_TimerModeDisabled        = 0x0U, /*!< Timer Disabled. */
    MIO_TimerModeDual8BitBaudBit = 0x1U, /*!< Dual 8-bit counters baud/bit mode. */
    MIO_TimerModeDual8BitPWM     = 0x2U, /*!< Dual 8-bit counters PWM mode. */
    MIO_TimerModeSingle16Bit     = 0x3U, /*!< Single 16-bit counter mode. */
} mio_timer_mode_t;

/*! @brief Define type of timer initial output or timer reset condition.*/
typedef enum _mio_timer_output
{
    MIO_TimerOutputOneNotAffectedByReset = 0x0U,  /*!< Logic one when enabled and is not affected by timer
                                                       reset. */
    MIO_TimerOutputZeroNotAffectedByReset = 0x1U, /*!< Logic zero when enabled and is not affected by timer
                                                       reset. */
    MIO_TimerOutputOneAffectedByReset  = 0x2U,    /*!< Logic one when enabled and on timer reset. */
    MIO_TimerOutputZeroAffectedByReset = 0x3U,    /*!< Logic zero when enabled and on timer reset. */
} mio_timer_output_t;

/*! @brief Define type of timer decrement.*/
typedef enum _mio_timer_decrement_source
{
    MIO_TimerDecSrcOnMIOClockShiftTimerOutput = 0x0U, /*!< Decrement counter on MIO clock, Shift clock
                                                              equals Timer output. */
    MIO_TimerDecSrcOnTriggerInputShiftTimerOutput,       /*!< Decrement counter on Trigger input (both edges),
                                                                     Shift clock equals Timer output. */
    MIO_TimerDecSrcOnPinInputShiftPinInput,              /*!< Decrement counter on Pin input (both edges),
                                                                     Shift clock equals Pin input. */
    MIO_TimerDecSrcOnTriggerInputShiftTriggerInput       /*!< Decrement counter on Trigger input (both edges),
                                                                     Shift clock equals Trigger input. */
#if (defined(LHC_FEATURE_MIO_TIMCFG_TIMDCE_FIELD_WIDTH) && (LHC_FEATURE_MIO_TIMCFG_TIMDCE_FIELD_WIDTH == 3))
    ,
    MIO_TimerDecSrcDiv16OnMIOClockShiftTimerOutput,  /*!< Decrement counter on MIO clock divided by 16,
                                                               Shift clock equals Timer output. */
    MIO_TimerDecSrcDiv256OnMIOClockShiftTimerOutput, /*!< Decrement counter on MIO clock divided by 256,
                                                                Shift clock equals Timer output. */
    MIO_TimerRisSrcOnPinInputShiftPinInput,             /*!< Decrement counter on Pin input (rising edges),
                                                                     Shift clock equals Pin input. */
    MIO_TimerRisSrcOnTriggerInputShiftTriggerInput /*!< Decrement counter on Trigger input (rising edges), Shift
                                                          clock equals Trigger input. */
#endif                                                 /* LHC_FEATURE_MIO_TIMCFG_TIMDCE_FIELD_WIDTH */
} mio_timer_decrement_source_t;

/*! @brief Define type of timer reset condition.*/
typedef enum _mio_timer_reset_condition
{
    MIO_TimerResetNever                            = 0x0U, /*!< Timer never reset. */
    MIO_TimerResetOnTimerPinEqualToTimerOutput     = 0x2U, /*!< Timer reset on Timer Pin equal to Timer Output. */
    MIO_TimerResetOnTimerTriggerEqualToTimerOutput = 0x3U, /*!< Timer reset on Timer Trigger equal to
                                                                Timer Output. */
    MIO_TimerResetOnTimerPinRisingEdge     = 0x4U,         /*!< Timer reset on Timer Pin rising edge. */
    MIO_TimerResetOnTimerTriggerRisingEdge = 0x6U,         /*!< Timer reset on Trigger rising edge. */
    MIO_TimerResetOnTimerTriggerBothEdge   = 0x7U,         /*!< Timer reset on Trigger rising or falling edge. */
} mio_timer_reset_condition_t;

/*! @brief Define type of timer disable condition.*/
typedef enum _mio_timer_disable_condition
{
    MIO_TimerDisableNever                    = 0x0U, /*!< Timer never disabled. */
    MIO_TimerDisableOnPreTimerDisable        = 0x1U, /*!< Timer disabled on Timer N-1 disable. */
    MIO_TimerDisableOnTimerCompare           = 0x2U, /*!< Timer disabled on Timer compare. */
    MIO_TimerDisableOnTimerCompareTriggerLow = 0x3U, /*!< Timer disabled on Timer compare and Trigger Low. */
    MIO_TimerDisableOnPinBothEdge            = 0x4U, /*!< Timer disabled on Pin rising or falling edge. */
    MIO_TimerDisableOnPinBothEdgeTriggerHigh = 0x5U, /*!< Timer disabled on Pin rising or falling edge provided
                                                          Trigger is high. */
    MIO_TimerDisableOnTriggerFallingEdge = 0x6U,     /*!< Timer disabled on Trigger falling edge. */
} mio_timer_disable_condition_t;

/*! @brief Define type of timer enable condition.*/
typedef enum _mio_timer_enable_condition
{
    MIO_TimerEnabledAlways                    = 0x0U, /*!< Timer always enabled. */
    MIO_TimerEnableOnPrevTimerEnable          = 0x1U, /*!< Timer enabled on Timer N-1 enable. */
    MIO_TimerEnableOnTriggerHigh              = 0x2U, /*!< Timer enabled on Trigger high. */
    MIO_TimerEnableOnTriggerHighPinHigh       = 0x3U, /*!< Timer enabled on Trigger high and Pin high. */
    MIO_TimerEnableOnPinRisingEdge            = 0x4U, /*!< Timer enabled on Pin rising edge. */
    MIO_TimerEnableOnPinRisingEdgeTriggerHigh = 0x5U, /*!< Timer enabled on Pin rising edge and Trigger high. */
    MIO_TimerEnableOnTriggerRisingEdge        = 0x6U, /*!< Timer enabled on Trigger rising edge. */
    MIO_TimerEnableOnTriggerBothEdge          = 0x7U, /*!< Timer enabled on Trigger rising or falling edge. */
} mio_timer_enable_condition_t;

/*! @brief Define type of timer stop bit generate condition.*/
typedef enum _mio_timer_stop_bit_condition
{
    MIO_TimerStopBitDisabled                    = 0x0U, /*!< Stop bit disabled. */
    MIO_TimerStopBitEnableOnTimerCompare        = 0x1U, /*!< Stop bit is enabled on timer compare. */
    MIO_TimerStopBitEnableOnTimerDisable        = 0x2U, /*!< Stop bit is enabled on timer disable. */
    MIO_TimerStopBitEnableOnTimerCompareDisable = 0x3U, /*!< Stop bit is enabled on timer compare and timer
                                                             disable. */
} mio_timer_stop_bit_condition_t;

/*! @brief Define type of timer start bit generate condition.*/
typedef enum _mio_timer_start_bit_condition
{
    MIO_TimerStartBitDisabled = 0x0U, /*!< Start bit disabled. */
    MIO_TimerStartBitEnabled  = 0x1U, /*!< Start bit enabled. */
} mio_timer_start_bit_condition_t;

/*! @brief MIO as PWM channel output state */
typedef enum _mio_timer_output_state
{
    MIO_PwmLow = 0, /*!< The output state of PWM channel is low */
    MIO_PwmHigh,    /*!< The output state of PWM channel is high */
} mio_timer_output_state_t;

/*! @brief Define type of timer polarity for shifter control. */
typedef enum _mio_shifter_timer_polarity
{
    MIO_ShifterTimerPolarityOnPositive = 0x0U, /*!< Shift on positive edge of shift clock. */
    MIO_ShifterTimerPolarityOnNegitive = 0x1U, /*!< Shift on negative edge of shift clock. */
} mio_shifter_timer_polarity_t;

/*! @brief Define type of shifter working mode.*/
typedef enum _mio_shifter_mode
{
    MIO_ShifterDisabled            = 0x0U, /*!< Shifter is disabled. */
    MIO_ShifterModeReceive         = 0x1U, /*!< Receive mode. */
    MIO_ShifterModeTransmit        = 0x2U, /*!< Transmit mode. */
    MIO_ShifterModeMatchStore      = 0x4U, /*!< Match store mode. */
    MIO_ShifterModeMatchContinuous = 0x5U, /*!< Match continuous mode. */
#if defined(LHC_FEATURE_MIO_HAS_STATE_MODE) && LHC_FEATURE_MIO_HAS_STATE_MODE
    MIO_ShifterModeState = 0x6U, /*!< SHIFTBUF contents are used for storing
                                      programmable state attributes. */
#endif                               /* LHC_FEATURE_MIO_HAS_STATE_MODE */
#if defined(LHC_FEATURE_MIO_HAS_LOGIC_MODE) && LHC_FEATURE_MIO_HAS_LOGIC_MODE
    MIO_ShifterModeLogic = 0x7U, /*!< SHIFTBUF contents are used for implementing
                                     programmable logic look up table. */
#endif                               /* LHC_FEATURE_MIO_HAS_LOGIC_MODE */
} mio_shifter_mode_t;

/*! @brief Define type of shifter input source.*/
typedef enum _mio_shifter_input_source
{
    MIO_ShifterInputFromPin               = 0x0U, /*!< Shifter input from pin. */
    MIO_ShifterInputFromNextShifterOutput = 0x1U, /*!< Shifter input from Shifter N+1. */
} mio_shifter_input_source_t;

/*! @brief Define of STOP bit configuration.*/
typedef enum _mio_shifter_stop_bit
{
    MIO_ShifterStopBitDisable = 0x0U, /*!< Disable shifter stop bit. */
    MIO_ShifterStopBitLow     = 0x2U, /*!< Set shifter stop bit to logic low level. */
    MIO_ShifterStopBitHigh    = 0x3U, /*!< Set shifter stop bit to logic high level. */
} mio_shifter_stop_bit_t;

/*! @brief Define type of START bit configuration.*/
typedef enum _mio_shifter_start_bit
{
    MIO_ShifterStartBitDisabledLoadDataOnEnable = 0x0U, /*!< Disable shifter start bit, transmitter loads
                                                             data on enable. */
    MIO_ShifterStartBitDisabledLoadDataOnShift = 0x1U,  /*!< Disable shifter start bit, transmitter loads
                                                             data on first shift. */
    MIO_ShifterStartBitLow  = 0x2U,                     /*!< Set shifter start bit to logic low level. */
    MIO_ShifterStartBitHigh = 0x3U,                     /*!< Set shifter start bit to logic high level. */
} mio_shifter_start_bit_t;

/*! @brief Define MIO shifter buffer type*/
typedef enum _mio_shifter_buffer_type
{
    MIO_ShifterBuffer               = 0x0U, /*!< Shifter Buffer N Register. */
    MIO_ShifterBufferBitSwapped     = 0x1U, /*!< Shifter Buffer N Bit Byte Swapped Register. */
    MIO_ShifterBufferByteSwapped    = 0x2U, /*!< Shifter Buffer N Byte Swapped Register. */
    MIO_ShifterBufferBitByteSwapped = 0x3U, /*!< Shifter Buffer N Bit Swapped Register. */
#if defined(LHC_FEATURE_MIO_HAS_SHFT_BUFFER_NIBBLE_BYTE_SWAP) && LHC_FEATURE_MIO_HAS_SHFT_BUFFER_NIBBLE_BYTE_SWAP
    MIO_ShifterBufferNibbleByteSwapped = 0x4U, /*!< Shifter Buffer N Nibble Byte Swapped Register. */
#endif                                             /*LHC_FEATURE_MIO_HAS_SHFT_BUFFER_NIBBLE_BYTE_SWAP*/
#if defined(LHC_FEATURE_MIO_HAS_SHFT_BUFFER_HALF_WORD_SWAP) && LHC_FEATURE_MIO_HAS_SHFT_BUFFER_HALF_WORD_SWAP
    MIO_ShifterBufferHalfWordSwapped = 0x5U, /*!< Shifter Buffer N Half Word Swapped Register. */
#endif
#if defined(LHC_FEATURE_MIO_HAS_SHFT_BUFFER_NIBBLE_SWAP) && LHC_FEATURE_MIO_HAS_SHFT_BUFFER_NIBBLE_SWAP
    MIO_ShifterBufferNibbleSwapped = 0x6U, /*!< Shifter Buffer N Nibble Swapped Register. */
#endif
} mio_shifter_buffer_type_t;

/*! @brief Define MIO user configuration structure. */
typedef struct _mio_config_
{
    bool enableMio;     /*!< Enable/disable MIO module */
    bool enableInDoze;     /*!< Enable/disable MIO operation in doze mode */
    bool enableInDebug;    /*!< Enable/disable MIO operation in debug mode */
    bool enableFastAccess; /*!< Enable/disable fast access to MIO registers, fast access requires
                           the MIO clock to be at least twice the frequency of the bus clock. */
} mio_config_t;

/*! @brief Define MIO timer configuration structure. */
typedef struct _mio_timer_config
{
    /* Trigger. */
    uint32_t triggerSelect;                          /*!< The internal trigger selection number using MACROs. */
    mio_timer_trigger_polarity_t triggerPolarity; /*!< Trigger Polarity. */
    mio_timer_trigger_source_t triggerSource;     /*!< Trigger Source, internal (see 'trgsel') or external. */
    /* Pin. */
    mio_pin_config_t pinConfig;     /*!< Timer Pin Configuration. */
    uint32_t pinSelect;                /*!< Timer Pin number Select. */
    mio_pin_polarity_t pinPolarity; /*!< Timer Pin Polarity. */
    /* Timer. */
    mio_timer_mode_t timerMode;                  /*!< Timer work Mode. */
    mio_timer_output_t timerOutput;              /*!< Configures the initial state of the Timer Output and
                                                    whether it is affected by the Timer reset. */
    mio_timer_decrement_source_t timerDecrement; /*!< Configures the source of the Timer decrement and the
                                                    source of the Shift clock. */
    mio_timer_reset_condition_t timerReset;      /*!< Configures the condition that causes the timer counter
                                                    (and optionally the timer output) to be reset. */
    mio_timer_disable_condition_t timerDisable;  /*!< Configures the condition that causes the Timer to be
                                                    disabled and stop decrementing. */
    mio_timer_enable_condition_t timerEnable;    /*!< Configures the condition that causes the Timer to be
                                                    enabled and start decrementing. */
    mio_timer_stop_bit_condition_t timerStop;    /*!< Timer STOP Bit generation. */
    mio_timer_start_bit_condition_t timerStart;  /*!< Timer STRAT Bit generation. */
    uint32_t timerCompare;                          /*!< Value for Timer Compare N Register. */
} mio_timer_config_t;

/*! @brief Define MIO shifter configuration structure. */
typedef struct _mio_shifter_config
{
    /* Timer. */
    uint32_t timerSelect;                          /*!< Selects which Timer is used for controlling the
                                                    logic/shift register and generating the Shift clock. */
    mio_shifter_timer_polarity_t timerPolarity; /*!< Timer Polarity. */
    /* Pin. */
    mio_pin_config_t pinConfig;     /*!< Shifter Pin Configuration. */
    uint32_t pinSelect;                /*!< Shifter Pin number Select. */
    mio_pin_polarity_t pinPolarity; /*!< Shifter Pin Polarity. */
    /* Shifter. */
    mio_shifter_mode_t shifterMode; /*!< Configures the mode of the Shifter. */
#if defined(LHC_FEATURE_MIO_HAS_PARALLEL_WIDTH) && LHC_FEATURE_MIO_HAS_PARALLEL_WIDTH
    uint32_t parallelWidth;                    /*!< Configures the parallel width when using parallel mode.*/
#endif                                         /* LHC_FEATURE_MIO_HAS_PARALLEL_WIDTH */
    mio_shifter_input_source_t inputSource; /*!< Selects the input source for the shifter. */
    mio_shifter_stop_bit_t shifterStop;     /*!< Shifter STOP bit. */
    mio_shifter_start_bit_t shifterStart;   /*!< Shifter START bit. */
} mio_shifter_config_t;

#if defined(LHC_FEATURE_MIO_HAS_PIN_REGISTER) && LHC_FEATURE_MIO_HAS_PIN_REGISTER
/*! @brief MIO gpio direction definition */
typedef enum _mio_gpio_direction
{
    MIO_DigitalInput  = 0U, /*!< Set current pin as digital input*/
    MIO_DigitalOutput = 1U, /*!< Set current pin as digital output*/
} mio_gpio_direction_t;

/*! @brief MIO gpio input config */
typedef enum _mio_pin_input_config
{
    MIO_InputInterruptDisabled = 0x0U, /*!< Interrupt request is disabled. */
    MIO_InputInterruptEnable   = 0x1U, /*!< Interrupt request is enable. */
    MIO_FlagRisingEdgeEnable   = 0x2U, /*!< Input pin flag on rising edge. */
    MIO_FlagFallingEdgeEnable  = 0x4U, /*!< Input pin flag on falling edge. */
} mio_pin_input_config_t;

/*!
 * @brief The MIO pin configuration structure.
 *
 * Each pin can only be configured as either an output pin or an input pin at a time.
 * If configured as an input pin, use inputConfig param.
 * If configured as an output pin, use outputLogic.
 */
typedef struct _mio_gpio_config
{
    mio_gpio_direction_t pinDirection; /*!< MIO pin direction, input or output */
    uint8_t outputLogic;                  /*!< Set a default output logic, which has no use in input */
    uint8_t inputConfig;                  /*!< Set an input config */
} mio_gpio_config_t;
#endif /*LHC_FEATURE_MIO_HAS_PIN_REGISTER*/

/*! @brief typedef for MIO simulated driver interrupt handler.*/
typedef void (*mio_isr_t)(void *base, void *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/
///*! @brief Pointers to mio bases for each instance. */
//extern MIO_Type *const s_mioBases[];

//#if !(defined(LHC_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && LHC_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
///*! @brief Pointers to mio clocks for each instance. */
//extern const clock_ip_name_t s_mioClocks[];
//#endif /* LHC_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(LHC_FEATURE_MIO_HAS_PIN_STATUS) && LHC_FEATURE_MIO_HAS_PIN_STATUS
/*!
 * @brief Reads the input data on each of the MIO pins.
 *
 * @param base MIO peripheral base address
 * @return MIO pin input data
 */
static inline uint32_t MIO_ReadPinInput(MIO_Type *base)
{
    return base->PIN;
}
#endif /*LHC_FEATURE_MIO_HAS_PIN_STATUS*/

#if defined(LHC_FEATURE_MIO_HAS_STATE_MODE) && LHC_FEATURE_MIO_HAS_STATE_MODE
/*!
 * @brief Gets the current state pointer for state mode use.
 *
 * @param base MIO peripheral base address
 * @return current State pointer
 */
static inline uint8_t MIO_GetShifterState(MIO_Type *base)
{
    return ((uint8_t)(base->SHIFTSTATE) & MIO_SHIFTSTATE_STATE_MASK);
}
#endif /*LHC_FEATURE_MIO_HAS_STATE_MODE*/

/*!
 * @brief Configures the shifter with the shifter configuration. The configuration structure
 * covers both the SHIFTCTL and SHIFTCFG registers. To configure the shifter to the proper
 * mode, select which timer controls the shifter to shift, whether to generate start bit/stop
 *  bit, and the polarity of start bit and stop bit.
 *
 * Example
   @code
   mio_shifter_config_t config = {
   .timerSelect = 0,
   .timerPolarity = MIO_ShifterTimerPolarityOnPositive,
   .pinConfig = MIO_PinConfigOpenDrainOrBidirection,
   .pinPolarity = MIO_PinActiveLow,
   .shifterMode = MIO_ShifterModeTransmit,
   .inputSource = MIO_ShifterInputFromPin,
   .shifterStop = MIO_ShifterStopBitHigh,
   .shifterStart = MIO_ShifterStartBitLow
   };
   MIO_SetShifterConfig(base, &config);
   @endcode
 *
 * @param base MIO peripheral base address
 * @param index Shifter index
 * @param shifterConfig Pointer to mio_shifter_config_t structure
*/
void MIO_SetShifterConfig(MIO_Type *base, uint8_t index, const mio_shifter_config_t *shifterConfig);
/*!
 * @brief Configures the timer with the timer configuration. The configuration structure
 * covers both the TIMCTL and TIMCFG registers. To configure the timer to the proper
 * mode, select trigger source for timer and the timer pin output and the timing for timer.
 *
 * Example
   @code
   mio_timer_config_t config = {
   .triggerSelect = MIO_TIMER_TRIGGER_SEL_SHIFTnSTAT(0),
   .triggerPolarity = MIO_TimerTriggerPolarityActiveLow,
   .triggerSource = MIO_TimerTriggerSourceInternal,
   .pinConfig = MIO_PinConfigOpenDrainOrBidirection,
   .pinSelect = 0,
   .pinPolarity = MIO_PinActiveHigh,
   .timerMode = MIO_TimerModeDual8BitBaudBit,
   .timerOutput = MIO_TimerOutputZeroNotAffectedByReset,
   .timerDecrement = MIO_TimerDecSrcOnMIOClockShiftTimerOutput,
   .timerReset = MIO_TimerResetOnTimerPinEqualToTimerOutput,
   .timerDisable = MIO_TimerDisableOnTimerCompare,
   .timerEnable = MIO_TimerEnableOnTriggerHigh,
   .timerStop = MIO_TimerStopBitEnableOnTimerDisable,
   .timerStart = MIO_TimerStartBitEnabled
   };
   MIO_SetTimerConfig(base, &config);
   @endcode
 *
 * @param base MIO peripheral base address
 * @param index Timer index
 * @param timerConfig Pointer to the mio_timer_config_t structure
*/
void MIO_SetTimerConfig(MIO_Type *base, uint8_t index, const mio_timer_config_t *timerConfig);

#if 0
/*!
 * @brief This function set the value of the prescaler on mio channels
 *
 * @param base       Pointer to the MIO simulated peripheral type.
 * @param index      Timer index
 * @param clocksource  Set clock value
 */
static inline void MIO_SetClockMode(MIO_Type *base, uint8_t index, mio_timer_decrement_source_t clocksource)
{
    uint32_t reg = base->TIMCFG[index];

    reg &= ~MIO_TIMCFG_TIMDEC_MASK;

    reg |= MIO_TIMCFG_TIMDEC(clocksource);

    base->TIMCFG[index] = reg;
}

/*! @} */

/*!
 * @name MIO Interrupt Operation
 * @{
 */

/*!
 * @brief Enables the shifter status interrupt. The interrupt generates when the corresponding SSF is set.
 *
 * @param base MIO peripheral base address
 * @param mask The shifter status mask which can be calculated by (1 << shifter index)
 * @note For multiple shifter status interrupt enable, for example, two shifter status enable, can calculate
 * the mask by using ((1 << shifter index0) | (1 << shifter index1))
 */
static inline void MIO_EnableShifterStatusInterrupts(MIO_Type *base, uint32_t mask)
{
    base->SHIFTSIEN |= mask;
}

/*!
 * @brief Disables the shifter status interrupt. The interrupt won't generate when the corresponding SSF is set.
 *
 * @param base MIO peripheral base address
 * @param mask The shifter status mask which can be calculated by (1 << shifter index)
 * @note For multiple shifter status interrupt enable, for example, two shifter status enable, can calculate
 * the mask by using ((1 << shifter index0) | (1 << shifter index1))
 */
static inline void MIO_DisableShifterStatusInterrupts(MIO_Type *base, uint32_t mask)
{
    base->SHIFTSIEN &= ~mask;
}

/*!
 * @brief Enables the shifter error interrupt. The interrupt generates when the corresponding SEF is set.
 *
 * @param base MIO peripheral base address
 * @param mask The shifter error mask which can be calculated by (1 << shifter index)
 * @note For multiple shifter error interrupt enable, for example, two shifter error enable, can calculate
 * the mask by using ((1 << shifter index0) | (1 << shifter index1))
 */
static inline void MIO_EnableShifterErrorInterrupts(MIO_Type *base, uint32_t mask)
{
    base->SHIFTEIEN |= mask;
}

/*!
 * @brief Disables the shifter error interrupt. The interrupt won't generate when the corresponding SEF is set.
 *
 * @param base MIO peripheral base address
 * @param mask The shifter error mask which can be calculated by (1 << shifter index)
 * @note For multiple shifter error interrupt enable, for example, two shifter error enable, can calculate
 * the mask by using ((1 << shifter index0) | (1 << shifter index1))
 */
static inline void MIO_DisableShifterErrorInterrupts(MIO_Type *base, uint32_t mask)
{
    base->SHIFTEIEN &= ~mask;
}

/*!
 * @brief Enables the timer status interrupt. The interrupt generates when the corresponding SSF is set.
 *
 * @param base MIO peripheral base address
 * @param mask The timer status mask which can be calculated by (1 << timer index)
 * @note For multiple timer status interrupt enable, for example, two timer status enable, can calculate
 * the mask by using ((1 << timer index0) | (1 << timer index1))
 */
static inline void MIO_EnableTimerStatusInterrupts(MIO_Type *base, uint32_t mask)
{
    base->TIMIEN |= mask;
}

/*!
 * @brief Disables the timer status interrupt. The interrupt won't generate when the corresponding SSF is set.
 *
 * @param base MIO peripheral base address
 * @param mask The timer status mask which can be calculated by (1 << timer index)
 * @note For multiple timer status interrupt enable, for example, two timer status enable, can calculate
 * the mask by using ((1 << timer index0) | (1 << timer index1))
 */
static inline void MIO_DisableTimerStatusInterrupts(MIO_Type *base, uint32_t mask)
{
    base->TIMIEN &= ~mask;
}

/*! @} */

/*!
 * @name MIO Status Operation
 * @{
 */

/*!
 * @brief Gets the shifter status flags.
 *
 * @param base MIO peripheral base address
 * @return Shifter status flags
 */
static inline uint32_t MIO_GetShifterStatusFlags(MIO_Type *base)
{
    return ((base->SHIFTSTAT) & MIO_SHIFTSTAT_SSF_MASK);
}

/*!
 * @brief Clears the shifter status flags.
 *
 * @param base MIO peripheral base address
 * @param mask The shifter status mask which can be calculated by (1 << shifter index)
 * @note For clearing multiple shifter status flags, for example, two shifter status flags, can calculate
 * the mask by using ((1 << shifter index0) | (1 << shifter index1))
 */
static inline void MIO_ClearShifterStatusFlags(MIO_Type *base, uint32_t mask)
{
    base->SHIFTSTAT = mask;
}

/*!
 * @brief Gets the shifter error flags.
 *
 * @param base MIO peripheral base address
 * @return Shifter error flags
 */
static inline uint32_t MIO_GetShifterErrorFlags(MIO_Type *base)
{
    return ((base->SHIFTERR) & MIO_SHIFTERR_SEF_MASK);
}

/*!
 * @brief Clears the shifter error flags.
 *
 * @param base MIO peripheral base address
 * @param mask The shifter error mask which can be calculated by (1 << shifter index)
 * @note For clearing multiple shifter error flags, for example, two shifter error flags, can calculate
 * the mask by using ((1 << shifter index0) | (1 << shifter index1))
 */
static inline void MIO_ClearShifterErrorFlags(MIO_Type *base, uint32_t mask)
{
    base->SHIFTERR = mask;
}

/*!
 * @brief Gets the timer status flags.
 *
 * @param base MIO peripheral base address
 * @return Timer status flags
 */
static inline uint32_t MIO_GetTimerStatusFlags(MIO_Type *base)
{
    return ((base->TIMSTAT) & MIO_TIMSTAT_TSF_MASK);
}

#endif

/*!
 * @brief Clears the timer status flags.
 *
 * @param base MIO peripheral base address
 * @param mask The timer status mask which can be calculated by (1 << timer index)
 * @note For clearing multiple timer status flags, for example, two timer status flags, can calculate
 * the mask by using ((1 << timer index0) | (1 << timer index1))
 */
/*static inline void MIO_ClearTimerStatusFlags(MIO_Type *base, uint32_t mask)
{
    base->TIMSTAT = mask;
}

*/

/*! @} */

/*!
 * @name MIO DMA Operation
 * @{
 */

/*!
 * @brief Enables/disables the shifter status DMA. The DMA request  generates when the corresponding SSF is set.
 *
 * @note For multiple shifter status DMA enables, for example, calculate
 * the mask by using ((1 << shifter index0) | (1 << shifter index1))
 *
 * @param base MIO peripheral base address
 * @param mask The shifter status mask which can be calculated by (1 << shifter index)
 * @param enable True to enable, false to disable.
 */
static inline void MIO_EnableShifterStatusDMA(MIO_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->SHIFTSDEN |= mask;
    }
    else
    {
        base->SHIFTSDEN &= ~mask;
    }
}

/*!
 * @brief Gets the shifter buffer address for the DMA transfer usage.
 *
 * @param base MIO peripheral base address
 * @param type Shifter type of mio_shifter_buffer_type_t
 * @param index Shifter index
 * @return Corresponding shifter buffer index
 */
uint32_t MIO_GetShifterBufferAddress(MIO_Type *base, mio_shifter_buffer_type_t type, uint8_t index);

/*!
 * @brief Registers the handle and the interrupt handler for the MIO-simulated peripheral.
 *
 * @param base Pointer to the MIO simulated peripheral type.
 * @param handle Pointer to the handler for MIO simulated peripheral.
 * @param isr MIO simulated peripheral interrupt handler.
 * @retval kStatus_Success Successfully create the handle.
 * @retval kStatus_OutOfRange The MIO type/handle/ISR table out of range.
 */
status_t MIO_RegisterHandleIRQ(void *base, void *handle, mio_isr_t isr);

/*!
 * @brief Unregisters the handle and the interrupt handler for the MIO-simulated peripheral.
 *
 * @param base Pointer to the MIO simulated peripheral type.
 * @retval kStatus_Success Successfully create the handle.
 * @retval kStatus_OutOfRange The MIO type/handle/ISR table out of range.
 */
status_t MIO_UnregisterHandleIRQ(void *base);
/*! @} */

#if defined(LHC_FEATURE_MIO_HAS_PIN_REGISTER) && LHC_FEATURE_MIO_HAS_PIN_REGISTER

/*!
 * @brief Configure a MIO pin used by the board.
 *
 * To Config the MIO PIN, define a pin configuration, as either input or output, in the user file.
 * Then, call the MIO_SetPinConfig() function.
 *
 * This is an example to define an input pin or an output pin configuration.
 * @code
 * Define a digital input pin configuration,
 * mio_gpio_config_t config =
 * {
 *   MIO_DigitalInput,
 *   0U,
 *   MIO_FlagRisingEdgeEnable | MIO_InputInterruptEnable,
 * }
 * Define a digital output pin configuration,
 * mio_gpio_config_t config =
 * {
 *   MIO_DigitalOutput,
 *   0U,
 *   0U
 * }
 * @endcode
 * @param base   MIO peripheral base address
 * @param pin    MIO pin number.
 * @param config MIO pin configuration pointer.
 */
void MIO_SetPinConfig(MIO_Type *base, uint32_t pin, mio_gpio_config_t *config);

/*!
 * @name GPIO Output Operations
 * @{
 */

/*!
 * @brief Sets the output level of the multiple MIO pins to the logic 0.
 *
 * @param base   MIO peripheral base address
 * @param mask   MIO pin number mask
 */
static inline void MIO_ClearPortOutput(MIO_Type *base, uint32_t mask)
{
    base->PINOUTCLR = mask;
}

/*!
 * @brief Sets the output level of the multiple MIO pins to the logic 1.
 *
 * @param base   MIO peripheral base address
 * @param mask   MIO pin number mask
 */
static inline void MIO_SetPortOutput(MIO_Type *base, uint32_t mask)
{
    base->PINOUTSET = mask;
}

/*!
 * @brief Reverses the current output logic of the multiple MIO pins.
 *
 * @param base   MIO peripheral base address
 * @param mask   MIO pin number mask
 */
static inline void MIO_TogglePortOutput(MIO_Type *base, uint32_t mask)
{
    base->PINOUTTOG = mask;
}

/*!
 * @brief Sets the output level of the MIO pins to the logic 1 or 0.
 *
 * @param base    MIO peripheral base address
 * @param pin     MIO pin number.
 * @param output  MIO pin output logic level.
 *        - 0: corresponding pin output low-logic level.
 *        - 1: corresponding pin output high-logic level.
 */
static inline void MIO_PinWrite(MIO_Type *base, uint32_t pin, uint8_t output)
{
    if (output == 0U)
    {
        MIO_ClearPortOutput(base, 1UL << pin);
    }
    else
    {
        MIO_SetPortOutput(base, 1UL << pin);
    }
}

/*!
 * @brief Enables the MIO output pin function.
 *
 * @param base   MIO peripheral base address
 * @param pin    MIO pin number.
 */
static inline void MIO_EnablePinOutput(MIO_Type *base, uint32_t pin)
{
    base->PINOUTE |= (1UL << pin);
}
/*! @} */

/*!
 * @name MIO PIN Input Operations
 * @{
 */

/*!
 * @brief  Reads the current input value of the MIO pin.
 *
 * @param base   MIO peripheral base address
 * @param pin    MIO pin number.
 * @retval MIO port input value
 *        - 0: corresponding pin input low-logic level.
 *        - 1: corresponding pin input high-logic level.
 */
static inline uint32_t MIO_PinRead(MIO_Type *base, uint32_t pin)
{
    return (((base->PIN) >> pin) & 0x01U);
}

/*!
 * @brief Gets the MIO input pin status.
 *
 * @param base   MIO peripheral base address
 * @param pin    MIO pin number.
 * @retval MIO port input status
 *        - 0: corresponding pin input capture no status.
 *        - 1: corresponding pin input capture rising or falling edge.
 */
static inline uint32_t MIO_GetPinStatus(MIO_Type *base, uint32_t pin)
{
    return (((base->PINSTAT) >> pin) & 0x01U);
}

/*!
 * @brief Clears the multiple MIO input pins status.
 *
 * @param base   MIO peripheral base address
 * @param mask   MIO pin number mask
 */
static inline void MIO_ClearPortStatus(MIO_Type *base, uint32_t mask)
{
    base->PINSTAT = mask;
}
/*! @} */

#endif /*LHC_FEATURE_MIO_HAS_PIN_REGISTER*/

void            LHL_MIO_Init(void);

void            LHL_MIO_DeInit(void);

void            LHL_MIO_Reset(void);

void            LHL_MIO_TimerInit(MIO_TIMER_t id, MIO_TIM_InitTypedef *init);

void            LHL_MIO_ShifterInit(MIO_SHIFTER_t id, MIO_SHIFTER_InitTypedef *init);

void            LHL_MIO_UARTInit(MIO_UART_HandleTypeDef* handle);

LHL_StatusTypeDef LHL_MIO_UARTTransmit(MIO_UART_HandleTypeDef* handle, const uint8_t *txData, uint8_t txSize);

LHL_StatusTypeDef LHL_MIO_UARTReceive(MIO_UART_HandleTypeDef* handle, uint8_t *rxData, size_t rxSize);

void            LHL_MIO_ITConfig(MIO_IT_t MIO_IT, FunctionalState NewState);

ITStatus        LHL_MIO_GetPending(MIO_IT_FLAG_t MIO_IT);

void            LHL_MIO_ClearPending(MIO_IT_FLAG_t IT_FLAG);

FlagStatus      LHL_MIO_GetFlag(MIO_FLAG_t MIO_FLAG);


#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
