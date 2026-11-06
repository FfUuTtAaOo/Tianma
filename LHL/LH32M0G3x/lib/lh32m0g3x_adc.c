/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_adc.c
 * @version 2025-09-22
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  初始化ADCx
  * @note   Configures control registers, channel settings, reference voltages,
  *         filter settings and interrupt controls for both ADCs
  * @param  ADCx        x取值0或1
  *         ADC_Init    ADC初始值参数指针
  * @retval LHL_OK：ADC初始化成功；LHL_ERROR：参数错误。
  */  
LHL_StatusTypeDef LHL_ADC_Init(ADC_ID_t ADCx, ADC_InitTypeDef* ADC_Init)
{
    // 开启AFE时钟
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFEEN_Msk, ENABLE);
    
    if (ADC_Init == NULL) return LHL_ERROR;
    
    if (ADCx == ADC_0)
    {
        // 开启ADC0时钟
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC0EN_Msk, ENABLE);
        
        // 默认配置前停止转换
        pADC->ADC_CONTROL_0 &= ~(ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk | \
                                ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Msk | \
                                ADC_SUBSYS_USER_ADC_CONTROL_0_TRIG_SRC_SEL_Msk);
        
        // 写入CONTROL寄存器
        pADC->ADC_CONTROL_0 |= (((uint32_t)ADC_Init->Mode << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos) | \
                                ((uint32_t)ADC_Init->Trigger << ADC_SUBSYS_USER_ADC_CONTROL_0_TRIG_SRC_SEL_Pos));

        // 写入CHANNEL CFG寄存器
        pADC->CHANNEL_CFG_0 = (((uint32_t)ADC_Init->AINP << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINP_Pos) | ADC_Init->AINM);
        
        // 写入CONFIGURATION寄存器
        pADC->CONFIGURATION_0 = ((uint32_t)ADC_Init->Code << ADC_SUBSYS_USER_CONFIGURATION_0_BIPOLAR_Pos) | \
                                ((uint32_t)ADC_Init->REF_BUFP << ADC_SUBSYS_USER_CONFIGURATION_0_REF_BUFP_Pos) | \
                                ((uint32_t)ADC_Init->REF_BUFM << ADC_SUBSYS_USER_CONFIGURATION_0_REF_BUFM_Pos) | \
                                ((uint32_t)ADC_Init->ReferenceSelect << ADC_SUBSYS_USER_CONFIGURATION_0_REF_SEL_Pos) | \
                                ((uint32_t)ADC_Init->PGA << ADC_SUBSYS_USER_CONFIGURATION_0_PGA_Pos);
        
        // 写入FILTER寄存器
        pADC->FILTER_0 = ADC_Init->FS;
        
        // 使能DRDY
        pADC->ADC_DRDY |= (ADC_0 << ADC_SUBSYS_USER_ADC_DRDY_DRDY_SEL_Pos);
        
        return LHL_OK;        
    }
    else if (ADCx == ADC_1)
    {
        // 开启ADC1时钟
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1EN_Msk, ENABLE);
        
        // 默认配置前停止转换
        pADC->ADC_CONTROL_1 &= ~(ADC_SUBSYS_USER_ADC_CONTROL_1_START_Msk | \
                                ADC_SUBSYS_USER_ADC_CONTROL_1_MODE_Msk | \
                                ADC_SUBSYS_USER_ADC_CONTROL_1_TRIG_SRC_SEL_Msk);
        
        // 写入CONTROL寄存器            
        pADC->ADC_CONTROL_1 |= (((uint32_t)ADC_Init->Mode << ADC_SUBSYS_USER_ADC_CONTROL_1_MODE_Pos) | \
                                ((uint32_t)ADC_Init->Trigger << ADC_SUBSYS_USER_ADC_CONTROL_1_TRIG_SRC_SEL_Pos));

        // 写入CHANNEL CFG寄存器
        pADC->CHANNEL_CFG_1 = (((uint32_t)ADC_Init->AINP << ADC_SUBSYS_USER_CHANNEL_CFG_1_AINP_Pos) | ADC_Init->AINM);
        
        // 写入CONFIGURATION寄存器
        pADC->CONFIGURATION_1 = ((uint32_t)ADC_Init->Code << ADC_SUBSYS_USER_CONFIGURATION_1_BIPOLAR_Pos) | \
                                ((uint32_t)ADC_Init->REF_BUFP << ADC_SUBSYS_USER_CONFIGURATION_1_REF_BUFP_Pos) | \
                                ((uint32_t)ADC_Init->REF_BUFM << ADC_SUBSYS_USER_CONFIGURATION_1_REF_BUFM_Pos) | \
                                ((uint32_t)ADC_Init->ReferenceSelect << ADC_SUBSYS_USER_CONFIGURATION_1_REF_SEL_Pos) | \
                                ((uint32_t)ADC_Init->PGA << ADC_SUBSYS_USER_CONFIGURATION_1_PGA_Pos);
        
        // 写入FILTER寄存器
        pADC->FILTER_1 = ADC_Init->FS;
        
        // 使能DRDY
        pADC->ADC_DRDY |= (ADC_1 << ADC_SUBSYS_USER_ADC_DRDY_DRDY_SEL_Pos);
    }
    else
    {
        return LHL_ERROR;
    }
    
    if (ADC_Init->REF_Precharge != ENABLE)
    {
        pADC->IO_CONTROL_IOUT &= ~ADC_SUBSYS_USER_IO_CONTROL_IOUT_REF_BUF_PREQ_ENABLE_Msk;
    }
    else
    {
        pADC->IO_CONTROL_IOUT |= ADC_SUBSYS_USER_IO_CONTROL_IOUT_REF_BUF_PREQ_ENABLE_Msk;
    }
    
    return LHL_OK;
}

void LHL_ADC_DeInit(ADC_ID_t ADCx)
{
  if (ADCx == ADC_0)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_ADC0RST_Msk, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_ADC0RST_Msk, DISABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC0EN_Msk, DISABLE);    
  }     
  else
  {
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_ADC1RST_Msk, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_ADC1RST_Msk, DISABLE);
    
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1EN_Msk, DISABLE);
  }
}

/**
  * @brief  立即启动ADCx转换
  * @param  ADCx        x取值0或1
  * @retval None
  */
void LHL_ADC_Start(ADC_ID_t ADCx)
{
    if (ADCx == ADC_0)
    {
        pADC->ADC_CONTROL_0 |= ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk;
    }
    else
    {
        pADC->ADC_CONTROL_1 |= ADC_SUBSYS_USER_ADC_CONTROL_1_START_Msk;
    }
}

/**
  * @brief  立即停止ADCx转换
  * @param  ADCx        x取值0或1
  * @retval None
  */void LHL_ADC_Stop(ADC_ID_t ADCx)
{
    if (ADCx == ADC_0)
    {
        pADC->ADC_CONTROL_0 &= ~ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk;
    }
    else
    {
        pADC->ADC_CONTROL_1 &= ~ADC_SUBSYS_USER_ADC_CONTROL_1_START_Msk;
    }
}

/**
  * @brief  设置ADCx中断
  * @param  ADCx        x取值0或1
  *         ADC_IT      指定ADC中断
  *         NewState    ENABLE or DISABLE
  * @retval None
  */
void LHL_ADC_ITConfig(ADC_ID_t ADCx, uint32_t ADC_IT, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        if (ADCx == ADC_0)
        {
            pADC->INTERRUPT_CONTROL_0 |= ADC_IT;
        }
        else
        {
            pADC->INTERRUPT_CONTROL_1 |= ADC_IT;
        }
    }
    else
    {
        if (ADCx == ADC_0)
        {
            pADC->INTERRUPT_CONTROL_0 &= ~ADC_IT;
        }
        else
        {
            pADC->INTERRUPT_CONTROL_1 &= ~ADC_IT;
        }
    }
}

/**
  * @brief  获取ADCx中断标志位
  * @param  ADCx        x取值0或1
  *         ADC_IT_FLAG 指定ADC中断标志位
  * @retval SET or RESET
  */
ITStatus LHL_ADC_GetPending(ADC_ID_t ADCx, uint32_t ADC_IT_FLAG)
{
    uint32_t reg;
    
    if (ADCx == ADC_0)
    {
        /* Check the status of the specified ADC0 interrupt */
        reg = pADC->ADC_STATUS_0;
    }
    else
    {
        /* Check the status of the specified ADC1 interrupt */
        reg = pADC->ADC_STATUS_1;
    }
    if (ADC_IT_FLAG != ADC_IT_ERR)
    {
        return  SET;
    }
    else
    {
        if ((reg & ADC_IT_FLAG) != (uint32_t)RESET)
        {
            return SET;
        }
    }
    return RESET;
}


/**
  * @brief  获取ADCx转换数据，读取数据前需保证ADC已转换完成
  * @param  ADCx        x取值0或1
  * @retval ADC Raw Data
  */
uint32_t LHL_ADC_GetData(ADC_ID_t ADCx)
{
    if (ADCx == ADC_0) 
    {    
        return pADC->ADC_DATA_0;
    }
    else
    {
        return pADC->ADC_DATA_1;
    }
}

/**
  * @brief  使用堵塞方式查询ADCx是否转换完成
  * @param  ADCx        x取值0或1
  *         Timeout     超时时间
  * @retval LHL_OK：转换完成；LHL_TIMEOUT：超时未完成。
  */
LHL_StatusTypeDef LHL_ADC_PollForConversion (ADC_ID_t ADCx, uint32_t Timeout)
{
    uint32_t t = Timeout;
    if (ADCx == ADC_0) 
    {
        while ((pADC->ADC_STATUS_0 & ADC_SUBSYS_USER_ADC_STATUS_0_RDYN_Msk) == 0)
        {
            if ((t--) == 0) return LHL_TIMEOUT;
        }
        return LHL_OK;
    }
    else
    {
        while ((pADC->ADC_STATUS_1 & ADC_SUBSYS_USER_ADC_STATUS_1_RDYN_Msk) == 0)
        {
            if ((t--) == 0) return LHL_TIMEOUT;
        }
        return LHL_OK;
    }
}

///**
//  * @brief  将ADC Raw Data转换为实际电压值（单位：毫伏/mV）
//  * @param  raw_data    ADC原始数据
//  *         REF_Init    ADC基准参数
//  *         ADC_Init    ADC初始参数
//  * @retval 以单精度浮点数（float）表达的电压值（单位：毫伏/mV）
//  */     
//float LHL_ADC_GetmVoltage(const uint32_t raw_data, REF_InitTypeDef* REF_Init, ADC_InitTypeDef* ADC_Init)
//{
//    float ref_mv;
//    
//    switch (REF_Init->REF0_Mode)
//    {
//        case REF_INTERNAL_1P25_V:   ref_mv = 1250; break;
//        case REF_INTERNAL_2P048_V:  ref_mv = 2048; break;
//        case REF_INTERNAL_2P5_V:    ref_mv = 2500; break;
//        case REF_INTERNAL_4P096_V:  ref_mv = 4096; break;
//    }
//    
//    if (ADC_Init->Code == ADC_CODE_BIPOLAR)
//    {
//        return (float)(((int32_t)raw_data << 8) >> 8) * ref_mv / (1<<23);
//    }
//    else
//    {
//        return (float)raw_data * ref_mv / (1<<24);
//    }
//}

/**
  * @brief  将ADC Raw Data转换为电压值
  * @param  raw_data    ADC原始数据
  *         ADC_Init    ADC初始参数
  * @retval 以单精度浮点数（float）表达的电压值（单位：伏/V）
  */     
float LHL_ADC_GetVoltage(const uint32_t raw_data, ADC_InitTypeDef* ADC_Init)
{
    uint32_t pga;
    float ref;
    
    pga = 1u << (ADC_Init->PGA & 7u);
    ref = ADC_Init->Reference / (float)pga;
    
    if (ADC_Init->Code == ADC_CODE_BIPOLAR)
    {
        return (float)(((int32_t)raw_data << 8) >> 8) * ref / (1<<23);
    }
    else
    {
        return (float)raw_data * ref / (1<<24);
    }
}

/**
  * @brief  将ADC Raw Data转换为温度值
  * @param  raw_data    ADC原始数据
  *         ADC_Init    ADC初始参数
  * @retval 以单精度浮点数（float）表达的温度值（单位：℃）
  */     
float LHL_ADC_GetTemperature(const uint32_t raw_data, ADC_InitTypeDef* ADC_Init)
{
    float ref;
    
    ref = 3022000.0f/ADC_Init->Reference;

    /* 必须使用ADC1，必须设置为 ADC_CODE_BIPOLAR模式 */
    return ((float)raw_data/ref - 272.7f);
}

/**
  * @brief  使能或禁用内部基准源VREF
  * @param  voltage     内部基准的电压
  * @param  NewState    ENABLE or DISABLE
  * @retval None
  */
void LHL_ADC_SetVREF(REF_VOLTAGE_t voltage, FunctionalState NewState)
{
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFEEN_Msk, ENABLE);
    
    if (NewState == DISABLE)
    {
        /* 关闭内部基准VREF */
        pAFE->REF_CTRL &= ~(AFE_REF_CTRL_REF0_EN_Msk);
    }
    else
    {
        /* 设定内部基准电压并开启VREF */
        pAFE->REF_CTRL &= ~AFE_REF_CTRL_REF0_MODE_Msk;
        pAFE->REF_CTRL |= (((uint32_t)voltage << AFE_REF_CTRL_REF0_MODE_Pos) | AFE_REF_CTRL_REF0_EN_Msk);
    }
}

/**
  * @brief  使能或禁用内部驱动源VDRIVE
  * @param  voltage     驱动电压
  * @param  NewState    ENABLE or DISABLE
  * @retval None
  */
void LHL_ADC_SetVDRIVE(REF_VOLTAGE_t voltage, FunctionalState NewState)
{
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFEEN_Msk, ENABLE);
    
    if (NewState == DISABLE)
    {
        /* 关闭内部驱动VDRIVE */
        pAFE->REF_CTRL &= ~(AFE_REF_CTRL_REF1_EN_Msk);
    }
    else
    {
        /* 设定内部驱动电压并开启VDRIVE */
        pAFE->REF_CTRL &= ~AFE_REF_CTRL_REF1_MODE_Msk;
        pAFE->REF_CTRL |= (((uint32_t)voltage << AFE_REF_CTRL_REF1_MODE_Pos) | AFE_REF_CTRL_REF1_EN_Msk);
    }
}

/**
  * @brief  初始化ADC基准源设置
  * @param  REF_Init    ADC基准参数指针
  * @retval LHL_OK：基准源设置成功
  */
LHL_StatusTypeDef LHL_REF_Init(REF_InitTypeDef* REF_Init)
{
    // 开启AFE时钟
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFEEN_Msk, ENABLE);
    
    if (REF_Init == NULL) return LHL_ERROR;
    
    if (REF_Init->VREF == REF_INTERNAL_OFF)
    {
        // 关闭内部基准REF0
        pAFE->REF_CTRL &= ~(AFE_REF_CTRL_REF0_EN_Msk);
    }
    else
    {
        // 设定内部基准电压并开启REF0
        pAFE->REF_CTRL &= ~(AFE_REF_CTRL_REF0_MODE_Msk | AFE_REF_CTRL_REFBUF0_BOOST_EN_Msk);
        pAFE->REF_CTRL |= ((uint32_t)REF_Init->VREF << AFE_REF_CTRL_REF0_MODE_Pos) | \
                        ((uint32_t)REF_Init->VREF_Boost << AFE_REF_CTRL_REFBUF0_BOOST_EN_Pos) | \
                        AFE_REF_CTRL_REF0_EN_Msk;
    }
    
    if (REF_Init->VDRIVE == REF_INTERNAL_OFF)
    {
        // 关闭内部基准REF1
        pAFE->REF_CTRL &= ~(AFE_REF_CTRL_REF1_EN_Msk);
    }
    else
    {
        // 设定内部基准电压并开启REF1
        pAFE->REF_CTRL &= ~ (AFE_REF_CTRL_REF1_MODE_Msk | AFE_REF_CTRL_REFBUF1_BOOST_EN_Msk);
        pAFE->REF_CTRL |= ((uint32_t)REF_Init->VDRIVE << AFE_REF_CTRL_REF1_MODE_Pos) | \
                        ((uint32_t)REF_Init->VDRIVE_Boost << AFE_REF_CTRL_REFBUF1_BOOST_EN_Pos) | \
                        AFE_REF_CTRL_REF1_EN_Msk;
    }
    
    return LHL_OK;
}

/**
  * @brief  设置内部温度传感器启用或关闭
  * @param  NewState    ENABLE or DISABLE
  * @retval None
  */
void LHL_ADC_SetTempSensor(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {   
        pAFE->REF_CTRL |= AFE_REF_CTRL_TEMP_SENSER_EN_Msk;  
    }
    else
    {
        pAFE->REF_CTRL &= ~AFE_REF_CTRL_TEMP_SENSER_EN_Msk; 
    }
}

/**
  * @brief  设置ADC同步方式
  * @note   需保证ADC0.FILTER0和ADC1.FILTER1的配置相同，并且ADC处于同一种转换模式（单次或连续转换），两个ADC的输出速率才能完全一致。
  * @note   使能同步，则ADC_0的启动源（软件寄存器或者硬件trigger）自动被应用到ADC_1，此时，两个ADC的启动同时受ADC_0的启动源控制。
  * @param  NewState    ENABLE or DISABLE
  * @retval None
  */
void LHL_ADC_SetSync(FunctionalState NewState)
{
    if (NewState ==  ENABLE)
    {   
        pADC->ADC_CONTROL_0 |= ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Msk;  
    }
    else
    {
        pADC->ADC_CONTROL_0 &= ~ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Msk;  
    }
}

/**
  * @brief  在指定的模拟通道上输出指定大小的激励电流
  * @param  source      分别设置激励电流源0或激励电流源1，或者两路电流源同步
  *         range       电流大小
  *         channel     电流输出通道即AINx引脚
  * @retval None
  */
void LHL_ADC_StartExcitationCurrent(IEXC_SOURCE_t source, IEXC_RANGE_t range, IEXC_CHANNEL_t channel)
{
    uint32_t tmp0 = pAFE->IEXC_CTRL;
    uint32_t tmp1 = pAFE->IEXC_RANGE;
    
    switch (source)
    {
        case EXC_CURRENT_DUAL:
            // 双路激励电流源在同一个通道上输出，电流大小翻倍
            tmp1 = (uint32_t)(range << AFE_IEXC_RANGE_IEXC1_RANGE_Pos) | \
                    (uint32_t)(range << AFE_IEXC_RANGE_IEXC0_RANGE_Pos);
            tmp0 &= ~(AFE_IEXC_CTRL_IEXC0_CHAN_Msk | AFE_IEXC_CTRL_IEXC1_CHAN_Msk);
            tmp0 |=  (uint32_t)(source << AFE_IEXC_CTRL_IEXC0_EN_Pos) | \
                    (uint32_t)(channel << AFE_IEXC_CTRL_IEXC1_CHAN_Pos) | \
                    (uint32_t)(channel << AFE_IEXC_CTRL_IEXC0_CHAN_Pos);
            break;
        case EXC_CURRENT_SRC0:
            // 激励电流源0
            tmp1 &= ~AFE_IEXC_RANGE_IEXC0_RANGE_Msk;
            tmp1 |= (uint32_t)(range << AFE_IEXC_RANGE_IEXC0_RANGE_Pos);
            tmp0 &= ~AFE_IEXC_CTRL_IEXC0_CHAN_Msk;
            tmp0 |=  (uint32_t)(source << AFE_IEXC_CTRL_IEXC0_EN_Pos) | \
                    (uint32_t)(channel << AFE_IEXC_CTRL_IEXC0_CHAN_Pos);
            break;
        case EXC_CURRENT_SRC1:
            // 激励电流源1
            tmp1 &= ~AFE_IEXC_RANGE_IEXC1_RANGE_Msk;
            tmp1 |= (uint32_t)(range << AFE_IEXC_RANGE_IEXC1_RANGE_Pos);
            tmp0 &= ~AFE_IEXC_CTRL_IEXC1_CHAN_Msk;
            tmp0 |=  (uint32_t)(source << AFE_IEXC_CTRL_IEXC0_EN_Pos) | \
                    (uint32_t)(channel << AFE_IEXC_CTRL_IEXC1_CHAN_Pos);           
    }
    pAFE->IEXC_RANGE = tmp1;
    pAFE->IEXC_CTRL = tmp0;
}

/**
  * @brief  停止指定的激励电流源输出
  * @param  source      分别设置激励电流源0或激励电流源1，或者两路电流源同步
  * @retval None
  */
void LHL_ADC_StopExcitationCurrent(IEXC_SOURCE_t source)
{
    pAFE->IEXC_CTRL &= ~((uint32_t)(source << AFE_IEXC_CTRL_IEXC0_EN_Pos));
}

/**
  * @brief  在指定通道上使能偏置电压输出
  * @param  source      电压输出通道
  * @retval None
  */
void LHL_ADC_StartBiasVoltage(VBIAS_CHANNEL_t channel)
{
    pADC->IO_CONTROL_VBIAS = channel;
}

/**
  * @brief  禁用偏置电压输出
  * @param  None
  * @retval None
  */
void LHL_ADC_StopBiasVoltage(void)
{
    pADC->IO_CONTROL_VBIAS = 0u;
}

/**
  * @brief  使能指定ADCx的Burnout Current Detection
  * @param  ADCx        进行检测的ADC0或者ADC1
  *         current     Burnout检测电流输出大小
  * @retval None
  */
void LHL_ADC_StartBurnoutCurrent(ADC_ID_t ADCx, BURNOUT_CURRENT_t current)
{
    uint32_t tmp = pADC->IO_CONTROL_IOUT;
    
    tmp &= ~ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_STRENTH_Msk;
    tmp |= (uint32_t)ADCx << ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_ADC_0_ENABLE_Pos | \
            (uint32_t)current << ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_STRENTH_Pos;
                
    pADC->IO_CONTROL_IOUT = tmp;
}

/**
  * @brief  禁用指定ADCx的Burnout Current Detection
  * @param  ADCx        停止检测的ADC0或者ADC1
  * @retval None
  */
void LHL_ADC_StopBurnoutCurrent(ADC_ID_t ADCx)
{
    pADC->IO_CONTROL_IOUT &= ~(ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_STRENTH_Msk | \
                    (uint32_t)ADCx << ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_ADC_0_ENABLE_Pos);
}


/**
  * @brief  使能或禁用ADC ERROR功能
  * @param  ADC_ERRs: 指定的ADC错误诊断功能（可选多个）
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void LHL_ADC_ErrorConfig(uint32_t ADC_ERRs,FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        pADC->ERROR_EN |= ADC_ERRs;
    }
    else
    {
        pADC->ERROR_EN &= ~ADC_ERRs;
    }
}

FlagStatus LHL_ADC_GetError(uint32_t ADC_ERR)
{
    if(pADC->ERROR_STATUS & ADC_ERR)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}


/**
  * @brief  使能或禁用ADC DMA请求功能
  * @param  ADCx: where x can be 1 or 2 to select the ADC peripheral.
  * @param  NewState: ENABLE or DISABLE.
  * @retval None
  */
void LHL_ADC_DMACmd(ADC_ID_t ADCx, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        pADC->DMA_MODE |= ADCx;
    }
    else
    {
        pADC->DMA_MODE &= ~ADCx;
    }
}

// Original：正序
//LHL_StatusTypeDef LHL_ADC_ChannelSequencer0Init(ADC_CS0InitTypeDef* CS0_Init)
//{
//    if (CS0_Init->Active_Channels > ADC_MAX_SEQUENCER_CHANNELS) return LHL_ERROR;
//    for (uint8_t i=0; i< CS0_Init->Active_Channels; i++)
//    {
//        /* 设为ADC为单次转换模式，软件触发，并启动转换 */
//        CS0_Init->ADC_CFG[i*2] = ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos);
//        /* 设为ADC输入通道 */
//        CS0_Init->ADC_CFG[i*2+1] = ((uint32_t)CS0_Init->AINP_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINP_Pos) | \
//                            ((uint32_t)CS0_Init->AINM_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINM_Pos);        
//    }
//    return LHL_OK;
//}

LHL_StatusTypeDef LHL_ADC_SingleChannelSequencerInit(ADC_InitTypeDef* ADC_Init, ADC_SingleCSInitTypeDef* ADC_CSInit)
{
    if ((ADC_CSInit == NULL) || (ADC_Init == NULL)) return LHL_ERROR;
    
    if ((ADC_CSInit->Active_Channels > ADC_MAX_SEQUENCER_CHANNELS) || (ADC_CSInit->Active_Channels < 2)) return LHL_ERROR;
    
    /* 设置ADC参数链表 */
    for (uint8_t i = 0; i < ADC_CSInit->Active_Channels; i++)
    {
        if (i == 0)
        {
            /* 首通道，设置触发模式 */
            if (ADC_CSInit->Sequencer_Trigger == ADC_TRIGGER_SOFTWARE)
            {   
                if (ADC_CSInit->Cycle_Mode == DISABLE)
                {
                    ADC_CSInit->ADC_CFG[ADC_CSInit->Active_Channels-1].ADC_CONTROL = (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos);
                }
                else
                {
                    ADC_CSInit->ADC_CFG[ADC_CSInit->Active_Channels-1].ADC_CONTROL = ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos);
                }
            }
            else
            {
                ADC_CSInit->ADC_CFG[ADC_CSInit->Active_Channels-1].ADC_CONTROL = ADC_SUBSYS_USER_ADC_CONTROL_0_TRIG_SRC_SEL_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos);
            }
            
            /* 设ADC输入通道 */
            ADC_CSInit->ADC_CFG[ADC_CSInit->Active_Channels-1].CHANNEL_CFG = ((uint32_t)ADC_CSInit->AINP_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINP_Pos) | \
                            ((uint32_t)ADC_CSInit->AINM_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINM_Pos); 
        }
        else
        {
            /* 其他通道，设置触发和循环模式 */
            if ((ADC_CSInit->Cycle_Mode == DISABLE) && (ADC_CSInit->Sequencer_Trigger == ADC_TRIGGER_HARDWARE))
            {
                ADC_CSInit->ADC_CFG[i-1].ADC_CONTROL = ADC_SUBSYS_USER_ADC_CONTROL_0_TRIG_SRC_SEL_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos);
            }
            else
            {
                ADC_CSInit->ADC_CFG[i-1].ADC_CONTROL = ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos);
            }
            /* 设ADC输入通道 */
            ADC_CSInit->ADC_CFG[i-1].CHANNEL_CFG = ((uint32_t)ADC_CSInit->AINP_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINP_Pos) | \
                            ((uint32_t)ADC_CSInit->AINM_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINM_Pos);             
        }       
    }
    
    /* 初始化ADC寄存器 */
    ADC_Init->AINP = ADC_CSInit->AINP_Channel[0];           // 装载首个通道
    ADC_Init->AINM = ADC_CSInit->AINM_Channel[0];
    ADC_Init->Mode = ADC_MODE_SINGLE_CONVERSION;            // 序列器模式固定为单次转换
    ADC_Init->Trigger = ADC_CSInit->Sequencer_Trigger;      // 首个通道触发源
    
    LHL_ADC_Init(ADC_CSInit->ADC_ID, ADC_Init); 
    
    return LHL_OK;
}

LHL_StatusTypeDef LHL_ADC_DualChannelSequencerInit(ADC_InitTypeDef* ADC_Init, ADC_DualCSInitTypeDef* ADC_DualCSInit)
{
    if ((ADC_DualCSInit == NULL) || (ADC_Init == NULL)) return LHL_ERROR;
    
    if ((ADC_DualCSInit->Active_Channels > ADC_MAX_SEQUENCER_CHANNELS) || (ADC_DualCSInit->Active_Channels < 2)) return LHL_ERROR;
    
    /* 设置ADC参数链表 */
    for (uint8_t i = 0; i < ADC_DualCSInit->Active_Channels; i++)
    {
        if (i == 0)
        {
            /* 首通道，设置触发模式 */
            if (ADC_DualCSInit->Sequencer_Trigger == ADC_TRIGGER_SOFTWARE)
            {   
                if (ADC_DualCSInit->Cycle_Mode == DISABLE)
                {
                    ADC_DualCSInit->ADC_CFGs[ADC_DualCSInit->Active_Channels-1].ADC_CONTROL_0 = (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos) | ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Msk;
                }
                else
                {
                    ADC_DualCSInit->ADC_CFGs[ADC_DualCSInit->Active_Channels-1].ADC_CONTROL_0 = ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos) | ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Msk;
                }
                ADC_DualCSInit->ADC_CFGs[ADC_DualCSInit->Active_Channels-1].ADC_CONTROL_1 = ADC_SUBSYS_USER_ADC_CONTROL_1_START_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_1_MODE_Pos);
            }
            else
            {
                ADC_DualCSInit->ADC_CFGs[ADC_DualCSInit->Active_Channels-1].ADC_CONTROL_0 = ADC_SUBSYS_USER_ADC_CONTROL_0_TRIG_SRC_SEL_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos) | ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Msk;
                ADC_DualCSInit->ADC_CFGs[ADC_DualCSInit->Active_Channels-1].ADC_CONTROL_1 = ADC_SUBSYS_USER_ADC_CONTROL_1_TRIG_SRC_SEL_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_1_MODE_Pos);
            }
            
            
            /* 设ADC输入通道 */
            ADC_DualCSInit->ADC_CFGs[ADC_DualCSInit->Active_Channels-1].CHANNEL_CFG_0 = ((uint32_t)ADC_DualCSInit->AINP0_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINP_Pos) | \
                            ((uint32_t)ADC_DualCSInit->AINM0_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINM_Pos); 
            ADC_DualCSInit->ADC_CFGs[ADC_DualCSInit->Active_Channels-1].CHANNEL_CFG_1 = ((uint32_t)ADC_DualCSInit->AINP1_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_1_AINP_Pos) | \
                            ((uint32_t)ADC_DualCSInit->AINM1_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_1_AINM_Pos); 
        }
        else
        {
            /* 其他通道，设置触发和循环模式 */
            if ((ADC_DualCSInit->Cycle_Mode == DISABLE) && (ADC_DualCSInit->Sequencer_Trigger == ADC_TRIGGER_HARDWARE))
            {
                ADC_DualCSInit->ADC_CFGs[i-1].ADC_CONTROL_0 = ADC_SUBSYS_USER_ADC_CONTROL_0_TRIG_SRC_SEL_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos) | ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Msk;
                ADC_DualCSInit->ADC_CFGs[i-1].ADC_CONTROL_1 = ADC_SUBSYS_USER_ADC_CONTROL_1_TRIG_SRC_SEL_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_1_MODE_Pos);
            }         
            else
            {
                ADC_DualCSInit->ADC_CFGs[i-1].ADC_CONTROL_0 = ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos) | ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Msk;
                ADC_DualCSInit->ADC_CFGs[i-1].ADC_CONTROL_1 = ADC_SUBSYS_USER_ADC_CONTROL_1_START_Msk | (2u << ADC_SUBSYS_USER_ADC_CONTROL_1_MODE_Pos);
            }
            /* 设ADC输入通道 */
            ADC_DualCSInit->ADC_CFGs[i-1].CHANNEL_CFG_0 = ((uint32_t)ADC_DualCSInit->AINP0_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINP_Pos) | \
                            ((uint32_t)ADC_DualCSInit->AINM0_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_0_AINM_Pos);             
            ADC_DualCSInit->ADC_CFGs[i-1].CHANNEL_CFG_1 = ((uint32_t)ADC_DualCSInit->AINP1_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_1_AINP_Pos) | \
                            ((uint32_t)ADC_DualCSInit->AINM1_Channel[i] << ADC_SUBSYS_USER_CHANNEL_CFG_1_AINM_Pos); 
        }       
    }
    
    /* 初始化ADC寄存器 */
    ADC_Init->AINP = ADC_DualCSInit->AINP0_Channel[0];          // 装载首个通道
    ADC_Init->AINM = ADC_DualCSInit->AINM0_Channel[0];
    ADC_Init->Mode = ADC_MODE_SINGLE_CONVERSION;                // 序列器模式固定为单次转换
    ADC_Init->Trigger = ADC_DualCSInit->Sequencer_Trigger;      // 首个通道触发源
    LHL_ADC_Init(ADC_0, ADC_Init);

    ADC_Init->AINP = ADC_DualCSInit->AINP1_Channel[0];           // 装载首个通道
    ADC_Init->AINM = ADC_DualCSInit->AINM1_Channel[0];    
    LHL_ADC_Init(ADC_1, ADC_Init);
    
    //LHL_ADC_SetSync(ENABLE);
    
    /* Dummy寄存器赋值 */
    for (uint8_t i = 0; i < ADC_DualCSInit->Active_Channels; i++)
    {
        ADC_DualCSInit->ADC_CFGs[i].INTERRUPT_CONTROL_0 = ADC_SUBSYS_USER_INTERRUPT_CONTROL_0_RESET;
        ADC_DualCSInit->ADC_CFGs[i].CONFIGURATION_0 = pADC->CONFIGURATION_0;
        ADC_DualCSInit->ADC_CFGs[i].CONFIGURATION_1 = pADC->CONFIGURATION_1;
        ADC_DualCSInit->ADC_CFGs[i].FILTER_1 = pADC->FILTER_1;
    }   
    
    return LHL_OK;
}
 
/*********************************End of File**********************************/
