/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_adc.h
 * @version 2025-09-22
 ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_ADC_H
#define __LH32M0G3x_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Public Definition ---------------------------------------------------------*/

/** 
  * @brief  ADC_IT Group
  */
#define ADC_IT_ERR              ((uint32_t)0x2)         /* 错误中断的使能 */
#define ADC_IT_RDY              ((uint32_t)0x1)         /* 数据ready中断的使能 */
#define ADC_IT_ALL              ((uint32_t)(ADC_IT_ERR | ADC_IT_RDY))

/** 
  * @brief  ADC_FLAG Group
  */
#define ADC_FLAG_RDY            ((uint32_t)0x1000)      /* ADC的数据ready指示 */
#define ADC_FLAG_ERR            ((uint32_t)0x0800)      /* ADC的错误指示 */
#define ADC_FLAG_POR            ((uint32_t)0x0400)      /* 上电复位指示 */

/** 
  * @brief  ADC_ERROR Group
  */
#define ADC1_ERROR_COMP_UV      ((uint32_t)0x4000)      /* ADC 1 数字比较器低于下阈值 */
#define ADC1_ERROR_COMP_OV      ((uint32_t)0x2000)      /* ADC 1 数字比较器超上阈值 */
#define ADC1_ERROR_AINP_OV      ((uint32_t)0x1000)      /* ADC 1 AIN正端输入overflow； */
#define ADC1_ERROR_AINP_UV      ((uint32_t)0x0800)      /* ADC 1 AIN正端输入underflow */
#define ADC1_ERROR_AINM_OV      ((uint32_t)0x0400)      /* ADC 1 AIN负端输入overflow */
#define ADC1_ERROR_AINM_UV      ((uint32_t)0x0200)      /* ADC 1 AIN负端输入underflow */
#define ADC1_ERROR_PGA_OV       ((uint32_t)0x0100)      /* ADC 1 PGA输入溢出 */
#define ADC0_ERROR_COMP_UV      ((uint32_t)0x0080)      /* ADC 0 数字比较器低于下阈值 */
#define ADC0_ERROR_COMP_OV      ((uint32_t)0x0040)      /* ADC 0 数字比较器超上阈值 */
#define ADC0_ERROR_AINP_OV      ((uint32_t)0x0020)      /* ADC 0 AIN正端输入overflow */
#define ADC0_ERROR_AINP_UV      ((uint32_t)0x0010)      /* ADC 0 AIN正端输入underflow */
#define ADC0_ERROR_AINM_OV      ((uint32_t)0x0008)      /* ADC 0 AIN负端输入overflow */
#define ADC0_ERROR_AINM_UV      ((uint32_t)0x0004)      /* ADC 0 AIN负端输入underflow */
#define ADC0_ERROR_PGA_OV       ((uint32_t)0x0002)      /* ADC 0 PGA输入溢出 */
#define ADC_ERROR_MEM_CRC       ((uint32_t)0x0001)      /* ADC寄存器校验 */
#define ADC_ERROR_ALL           ((uint32_t)0x7FFF)      /* ADC所有错误诊断全开 */
    
typedef enum{
    ADC_0 = 1u,
    ADC_1 = 2u,
} ADC_ID_t;

 typedef enum{
    REF_INTERNAL_2P5V = 0u,
    REF_INTERNAL_2P048V,
    REF_INTERNAL_1P25V,
    REF_INTERNAL_4P096V,
    REF_INTERNAL_OFF,
} REF_VOLTAGE_t;

// typedef enum{
//    REF_VOLTAGE_2P5V = 0u,
//    REF_VOLTAGE_2P048V,
//    REF_VOLTAGE_1P25V,
//    REF_VOLTAGE_4P096V,
//    REF_DISABLE,
//} REF_VOLTAGE_t;

//typedef struct
//{
//    REF_MODE_t REF0_Mode;           /*!< REF0基准电压:4.096/2.5/2.048/1.25 */
//    
//    FunctionalState REF0_Boost;     /*!< REFBUF0_BOOST_EN */

//    FunctionalState REF0;           /*!< Ref0 buffer enable。控制ADC的VREF+作为参考时的驱动使能。 */
//    
//    REF_MODE_t REF1_Mode;           /*!< REF1基准电压:4.096/2.5/2.048/1.25 */
//    
//    FunctionalState REF1_Boost;     /*!< REFBUF1_BOOST_EN */

//    FunctionalState REF1;           /*!< Ref1 buffer enable。控制VDRIVE引脚的驱动使能。 */
//    
//} REF_InitTypeDef;

typedef struct
{
    REF_VOLTAGE_t       VREF;           /*!< REF0基准电压:4.096/2.5/2.048/1.25/禁用 */
    
    FunctionalState     VREF_Boost;     /*!< REFBUF0_BOOST_EN */
    
    REF_VOLTAGE_t       VDRIVE;         /*!< REF1基准电压:4.096/2.5/2.048/1.25/禁用 */
    
    FunctionalState     VDRIVE_Boost;   /*!< REFBUF1_BOOST_EN */
    
} REF_InitTypeDef;

typedef enum {
    ADC_MODE_IDLE               = 0u,
    ADC_MODE_CONTINUOUS_CONVERSION,
    ADC_MODE_SINGLE_CONVERSION,
} ADC_MODE_t;

typedef enum {
    ADC_TRIGGER_SOFTWARE        = 0u,
    ADC_TRIGGER_HARDWARE,
} ADC_TRIGGER_t;

typedef enum {
    ADC_CODE_UNIPOLAR           = 0u,
    ADC_CODE_BIPOLAR,
} ADC_CODE_t;

typedef enum{
    ADC_REF_REFP_to_REFN        = 0u,
    ADC_REF_EXTREFP_to_EXTREFN,
    ADC_REF_REFP_to_AVSS,
    ADC_REF_VDRIVE_to_AVSS,
} ADC_REF_SELECT_t;

typedef enum {
    ADC_PGA_GAIN_1              = 0u,
    ADC_PGA_GAIN_2,
    ADC_PGA_GAIN_4,
    ADC_PGA_GAIN_8,
    ADC_PGA_GAIN_16,
    ADC_PGA_GAIN_32,
    ADC_PGA_GAIN_64,
    ADC_PGA_GAIN_128,
    ADC_PGA_BYPASS,
} ADC_PGA_t;

typedef enum {
    ADC0_AINP_AIN0              = 0x00u,
    ADC0_AINP_AIN1,
    ADC0_AINP_AIN2,
    ADC0_AINP_AIN3,
    ADC0_AINP_AIN4,
    ADC0_AINP_AIN5,
    ADC0_AINP_AIN6,
    ADC0_AINP_AIN7,
    ADC0_AINP_AIN8,
    ADC0_AINP_AIN9,
    ADC0_AINP_AIN10,
    ADC0_AINP_AIN11,
    ADC0_AINP_AVSS              = 0x10u,
    ADC0_AINP_REFP,
} ADC0_AINP_CHANNEL_t;

typedef enum {
    ADC0_AINM_AIN0              = 0x00u,
    ADC0_AINM_AIN1,
    ADC0_AINM_AIN2,
    ADC0_AINM_AIN3,
    ADC0_AINM_AIN4,
    ADC0_AINM_AIN5,
    ADC0_AINM_AIN6,
    ADC0_AINM_AIN7,
    ADC0_AINM_AIN8,
    ADC0_AINM_AIN9,
    ADC0_AINM_AIN10,
    ADC0_AINM_AIN11,
    ADC0_AINM_AVSS             = 0x10u,
    ADC0_AINM_REFP,
} ADC0_AINM_CHANNEL_t;

typedef enum {
    ADC1_AINP_AIN0              = 0x00u,
    ADC1_AINP_AIN1,
    ADC1_AINP_AIN2,
    ADC1_AINP_AIN3,
    ADC1_AINP_AIN4,
    ADC1_AINP_AIN5,
    ADC1_AINP_AIN6,
    ADC1_AINP_AIN7,
    ADC1_AINP_AIN8,
    ADC1_AINP_AIN9,
    ADC1_AINP_AIN10,
    ADC1_AINP_AIN11,
    ADC1_AINP_TEMPP             = 0x10u,
    ADC1_AINP_AVSS,
    ADC1_AINP_REFP,
    ADC1_AINP_DACP,
    ADC1_AINP_LOOPP,
    ADC1_AINP_AVDDP,
    ADC1_AINP_IOVDDP,
} ADC1_AINP_CHANNEL_t;

typedef enum {
    ADC1_AINM_AIN0              = 0x00u,
    ADC1_AINM_AIN1,
    ADC1_AINM_AIN2,
    ADC1_AINM_AIN3,
    ADC1_AINM_AIN4,
    ADC1_AINM_AIN5,
    ADC1_AINM_AIN6,
    ADC1_AINM_AIN7,
    ADC1_AINM_AIN8,
    ADC1_AINM_AIN9,
    ADC1_AINM_AIN10,
    ADC1_AINM_AIN11,
    ADC1_AINM_TEMPN             = 0x10u,
    ADC1_AINM_AVSS,
    ADC1_AINM_REFP,
    ADC1_AINM_DACN,
    ADC1_AINM_LOOPN,
    ADC1_AINM_AVDDN,
    ADC1_AINM_IOVDDN,
} ADC1_AINM_CHANNEL_t;

typedef enum {
    ADC_SPS_7813                = 0u,
    ADC_SPS_3906,
    ADC_SPS_1953,
    ADC_SPS_977,
    ADC_SPS_488,
    ADC_SPS_244,
    ADC_SPS_122,
    ADC_SPS_61,
    ADC_SPS_60,
    ADC_SPS_30,
    ADC_SPS_15,
    ADC_SPS_50                  = 16u,
    ADC_SPS_25,
    ADC_SPS_12P5,
    ADC_SPS_10                  = 24u,
    ADC_SPS_5,
    ADC_SPS_2P5,
} ADC_DATA_RATE_t;

typedef struct{
                                             
    ADC_MODE_t          Mode;               /*!< ADC转换模式控制. Continuous or Single mode. */
  
    ADC_TRIGGER_t       Trigger;            /*!< 选择ADC启动的触发源 */

    uint8_t             AINP;               /*!< AINP端输入选择，对于ADC0：ADC0_AINP_CHANNEL_t；对于ADC1：ADC1_AINP_CHANNEL_t */

    uint8_t             AINM;               /*!< AINM端输入选择，对于ADC0：ADC0_AINM_CHANNEL_t；对于ADC1：ADC1_AINM_CHANNEL_t */
    
    ADC_PGA_t           PGA;                /*!< PGA增益倍数 或 BYPASS */                                                 
          
    ADC_DATA_RATE_t     FS;                 /*!< 数据输出速率*/

    ADC_CODE_t          Code;               /*!< ADC数据输出单极性/双极性控制 */
    
    ADC_REF_SELECT_t    ReferenceSelect;    /*!< ADC基准源选择 */

    FunctionalState     REF_BUFP;           /*!< 基准源正输入缓冲器 */
  
    FunctionalState     REF_BUFM;           /*!< 基准源负输入缓冲器 */

    FunctionalState     REF_Precharge;      /*!< 基准源采样电容预充电，增加少许功耗 */
    
    uint8_t             Reserved;           /*!< 保留位 */
    
    float               Reference;          /*!< 可选基准值，单位：伏（基准为电压类型）或欧姆（基准为比例电阻） */  

} ADC_InitTypeDef;

/*----------------- ADC 通道序列器配置 -----------------------------------------*/
#ifndef ADC_MAX_SEQUENCER_CHANNELS
#define ADC_MAX_SEQUENCER_CHANNELS 8
#endif

/* 单ADC 带状态位的转换数据结构体 */
typedef struct {
    uint32_t    ADC_Status;
    uint32_t    ADC_Data;
} ADC_Data_t;

/* 双ADC 带状态位的转换数据结构体 */
typedef struct {
    uint32_t    Dummy0;
    uint32_t    Dummy1;
    uint32_t    ADC0_Status;
    uint32_t    ADC0_Data; 
    uint32_t    Dummy2;
    uint32_t    ADC1_Status;
    uint32_t    ADC1_Data;
    uint32_t    Dummy3;
} ADC_DualData_t;

/* 单ADC 通道序列器配置文件 */
typedef struct {
    uint32_t    ADC_CONTROL;
    uint32_t    CHANNEL_CFG;
} ADC_Config_t;

/* 双ADC 通道序列器配置文件 */
typedef struct {
    uint32_t    INTERRUPT_CONTROL_0;
    uint32_t    ADC_CONTROL_0;
    uint32_t    CHANNEL_CFG_0;
    uint32_t    CONFIGURATION_0;
    uint32_t    ADC_CONTROL_1;
    uint32_t    CHANNEL_CFG_1;
    uint32_t    CONFIGURATION_1;
    uint32_t    FILTER_1;
} ADC_DualConfig_t;

/* 单ADC 通道序列器参数结构体 */
typedef struct {
    ADC_Config_t*   ADC_CFG;   

    ADC_ID_t        ADC_ID;                                     /*!< 使用序列器的ADC_0或ADC_1 */
    
    uint8_t         Active_Channels;                            /*!< 序列器使能的通道数量：2 to ADC_MAX_SEQUENCER_CHANNELS */
    
    FunctionalState Cycle_Mode;                                 /*!< 循环模式：软件触发一次所有通道无限循环；硬件触发一次所有通道采集完毕等待下次触发 */
    
    ADC_TRIGGER_t   Sequencer_Trigger;                          /*!< 触发源：软件或硬件 */
    
    uint8_t         AINP_Channel[ADC_MAX_SEQUENCER_CHANNELS];   /*!< AINP端输入选择。ADC0：ADC0_AINP_CHANNEL_t；ADC1：ADC1_AINP_CHANNEL_t */
    
    uint8_t         AINM_Channel[ADC_MAX_SEQUENCER_CHANNELS];   /*!< AINM端输入选择。ADC0：ADC0_AINM_CHANNEL_t；ADC1：ADC1_AINM_CHANNEL_t */
    
} ADC_SingleCSInitTypeDef;

/* 双ADC 通道序列器参数结构体 */
typedef struct {

    ADC_DualConfig_t*    ADC_CFGs;   

    ADC_ID_t        ADC_ID;                                     /*!< Reserved。双序列器默认使用双ADC */
    
    uint8_t         Active_Channels;                            /*!< 序列器使能的通道数量：2 to ADC_MAX_SEQUENCER_CHANNELS */
    
    FunctionalState Cycle_Mode;                                 /*!< 循环模式：软件触发一次所有通道无限循环；硬件触发一次所有通道采集完毕等待下次触发 */
    
    ADC_TRIGGER_t   Sequencer_Trigger;                          /*!< 触发源：软件或硬件 */
    
    ADC0_AINP_CHANNEL_t     AINP0_Channel[ADC_MAX_SEQUENCER_CHANNELS];   /*!< ADC0 AINP端输入选择 */
    
    ADC0_AINM_CHANNEL_t     AINM0_Channel[ADC_MAX_SEQUENCER_CHANNELS];   /*!< ADC0 AINM端输入选择 */
    
    ADC1_AINP_CHANNEL_t     AINP1_Channel[ADC_MAX_SEQUENCER_CHANNELS];   /*!< ADC1 AINP端输入选择 */
    
    ADC1_AINM_CHANNEL_t     AINM1_Channel[ADC_MAX_SEQUENCER_CHANNELS];   /*!< ADC1 AINM端输入选择 */
    
} ADC_DualCSInitTypeDef;

typedef enum {
    EXC_CURRENT_0uA             =   0u,
    EXC_CURRENT_50uA,
    EXC_CURRENT_100uA,
    EXC_CURRENT_150uA,
    EXC_CURRENT_200uA,
    EXC_CURRENT_250uA,
    EXC_CURRENT_300uA,
    EXC_CURRENT_350uA,
    EXC_CURRENT_400uA,
    EXC_CURRENT_450uA,
    EXC_CURRENT_500uA,
    EXC_CURRENT_600uA,
    EXC_CURRENT_700uA,
    EXC_CURRENT_800uA,
    EXC_CURRENT_900uA,
    EXC_CURRENT_1000uA,
} IEXC_RANGE_t;

typedef enum {
    EXC_CURRENT_SRC0            =   1u,
    EXC_CURRENT_SRC1            =   2u,
    EXC_CURRENT_DUAL            =   3u,
} IEXC_SOURCE_t;

typedef enum {
    EXC_CURRENT_AIN2            =   2u,
    EXC_CURRENT_AIN3            =   3u,
    EXC_CURRENT_AIN4            =   4u,
    EXC_CURRENT_AIN5            =   5u,
    EXC_CURRENT_AIN7            =   7u,
    EXC_CURRENT_AIN8            =   8u,
    EXC_CURRENT_AIN10           =   10u,
    EXC_CURRENT_AIN11           =   11u,
} IEXC_CHANNEL_t;

typedef enum {
    BIAS_VOLTAGE_AIN0           =   0x0001u,
    BIAS_VOLTAGE_AIN1           =   0x0002u,
    BIAS_VOLTAGE_AIN2           =   0x0004u,
    BIAS_VOLTAGE_AIN3           =   0x0008u,
    BIAS_VOLTAGE_AIN4           =   0x0010u,
    BIAS_VOLTAGE_AIN5           =   0x0020u,
    BIAS_VOLTAGE_AIN6           =   0x0040u,
    BIAS_VOLTAGE_AIN7           =   0x0080u,
    BIAS_VOLTAGE_AIN8           =   0x0100u,
    BIAS_VOLTAGE_AIN9           =   0x0200u,
    BIAS_VOLTAGE_AIN10          =   0x0400u,
    BIAS_VOLTAGE_AIN11          =   0x0800u,
} VBIAS_CHANNEL_t;

typedef enum {
    BURNOUT_CURRENT_0uA         =   0u,
    BURNOUT_CURRENT_0_5uA,
    BURNOUT_CURRENT_2uA,
    BURNOUT_CURRENT_4uA,
} BURNOUT_CURRENT_t;


/* Function Prototype --------------------------------------------------------*/

LHL_StatusTypeDef   LHL_REF_Init(REF_InitTypeDef* REF_Init);

LHL_StatusTypeDef   LHL_ADC_Init(ADC_ID_t ADCx, ADC_InitTypeDef* ADC_Init);

void                LHL_ADC_DeInit(ADC_ID_t ADCx);

void                LHL_ADC_ITConfig(ADC_ID_t ADCx, uint32_t ADC_ITs, FunctionalState NewState);

void                LHL_ADC_SetVREF(REF_VOLTAGE_t voltage, FunctionalState NewState);

void                LHL_ADC_SetTempSensor(FunctionalState NewState);

void                LHL_ADC_SetVDRIVE(REF_VOLTAGE_t voltage, FunctionalState NewState);

void                LHL_ADC_ErrorConfig(uint32_t ADC_ERRs, FunctionalState NewState);

FlagStatus          LHL_ADC_GetError(uint32_t ADC_ERR);

void                LHL_ADC_Start(ADC_ID_t ADCx);

void                LHL_ADC_Stop(ADC_ID_t ADCx);

LHL_StatusTypeDef   LHL_ADC_PollForConversion (ADC_ID_t ADCx, uint32_t Timeout);

uint32_t            LHL_ADC_GetData(ADC_ID_t ADCx);

float               LHL_ADC_GetVoltage(const uint32_t raw_data, ADC_InitTypeDef* ADC_Init);

float               LHL_ADC_GetTemperature(const uint32_t raw_data, ADC_InitTypeDef* ADC_Init);

ITStatus            LHL_ADC_GetPending(ADC_ID_t ADCx, uint32_t ADC_IT_FLAG);

void                LHL_ADC_SetSync(FunctionalState NewState);

void                LHL_ADC_StartExcitationCurrent(IEXC_SOURCE_t source, IEXC_RANGE_t range, IEXC_CHANNEL_t channel);

void                LHL_ADC_StopExcitationCurrent(IEXC_SOURCE_t source);

void                LHL_ADC_StartBiasVoltage(VBIAS_CHANNEL_t channel);

void                LHL_ADC_StopBiasVoltage(void);

void                LHL_ADC_StartBurnoutCurrent(ADC_ID_t ADCx, BURNOUT_CURRENT_t current);

void                LHL_ADC_StopBurnoutCurrent(ADC_ID_t ADCx);

void                LHL_ADC_DMACmd(ADC_ID_t ADCx, FunctionalState NewState);

LHL_StatusTypeDef   LHL_ADC_SingleChannelSequencerInit(ADC_InitTypeDef* ADC_Init, ADC_SingleCSInitTypeDef* ADC_CSInit);

LHL_StatusTypeDef   LHL_ADC_DualChannelSequencerInit(ADC_InitTypeDef* ADC_Init, ADC_DualCSInitTypeDef* ADC_DualCSInit);

#ifdef __cplusplus
}
#endif

#endif 

/*********************************End of File**********************************/
