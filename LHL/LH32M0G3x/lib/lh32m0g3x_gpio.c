/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_gpio.c
 * @version 2025-09-01
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  复位所有GPIO端口状态，默认输入浮空状态（except JTAG pins）
  * @param  None                     
  * @retval None
  */
void LHL_GPIO_DeInit(void)
{
    // Disable the GPIO Reset Hold
    pRCC->CSR |= RCC_CSR_GPIO_RETAIN_Msk;
    
    // 通过RCC复位GPIO
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_GPIORST_Msk, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2RSTR_GPIORST_Msk, DISABLE);
    
    // 禁用GPIO时钟
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOEN_Msk, DISABLE);
    
    // Enable GPIO Reset Hold
    pRCC->CSR &= ~RCC_CSR_GPIO_RETAIN_Msk;
}

 /**
  * @brief  根据GPIO_Init设定GPIO指定引脚的模式
  * @param  pGPIOx：pGPIO0；pGPIO1；pGPIO2
  *         GPIO_Init：GPIO初始化结构体
  * @retval None
  */
void LHL_GPIO_Init(GPIO_TypeDef* pGPIOx, GPIO_InitTypeDef* GPIO_Init)
{
    uint32_t position = 0u;
    uint32_t pinpos, reg;
    
    // 使能GPIO外设时钟（AHB总线）
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOEN_Msk, ENABLE);
    
    // 依次检查是否有需要设置的Pin
    while ((GPIO_Init->Pin) >> position != 0)
    {
        // 检查当前Position的Pin是否为1        
        if (((GPIO_Init->Pin) & (1u << position)) != 0)
        {
            pinpos = position;
            
            /* AFIO设置应该首先被设置 */
            reg = pGPIOx->CON0;
            reg &= ~((uint32_t)0xf << (pinpos*4));
            reg |= ((uint32_t)GPIO_Init->Alternate << (pinpos*4));
            pGPIOx->CON0 = reg;
    
            /* Pull-up Pull-down 上下拉电阻设定 */
            if (GPIO_Init->Pull == GPIO_PULLUP)
            {
                pGPIOx->PDE &= ~(1u << pinpos);
                pGPIOx->PUE |= (1u << pinpos);
            }
            else if (GPIO_Init->Pull == GPIO_PULLDOWN)
            {
                pGPIOx->PUE &= ~(1u << pinpos);
                pGPIOx->PDE |= (1u << pinpos);
            }
            else
            {
                pGPIOx->PUE &= ~(1u << pinpos);
                pGPIOx->PDE &= ~(1u << pinpos);
            }
            
            /* 设定施密特触发器是否使能 */
            if (GPIO_Init->SchmittTrigger == DISABLE)
            {
                pGPIOx->SMT &= ~(1u << pinpos);
            }
            else
            {
                pGPIOx->SMT |= (1u << pinpos);
            }
            
            // 设置端口电流驱动能力
            reg = pGPIOx->DR;
            reg &= ~(3u << (pinpos * 2));
            reg |= ((uint32_t)GPIO_Init->Current << (pinpos * 2));
            pGPIOx->DR = reg;

            if(GPIO_Init->Mode == GPIO_MODE_INPUT) 
            {                   
                // 输出缓冲器使能应该被禁止
                pGPIOx->OE &= ~(1u << pinpos);
                pGPIOx->IE |= (1u << pinpos);
            }
            else if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP)
            {     
                pGPIOx->OE |= (1u << pinpos);                
                // 推挽输出设定
                pGPIOx->OD &= ~(1u << pinpos);
            }
            else if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD)
            {
                pGPIOx->OE |= (1u << pinpos);                
                // 开漏输出设定
                pGPIOx->OD |= (1u << pinpos);              
            }
            else
            {
                // 输出和输入都被禁用
                pGPIOx->OE &= ~(1u << pinpos);
                pGPIOx->IE &= ~(1u << pinpos);              
            }
        }
        
        position++;
    }
}

/**
  * @brief  读取特定引脚的电平
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Pin_x: x取值范围（0...15)
  * @retval Pin_State: 低电平GPIO_PIN_RESET；高电平GPIO_PIN_SET
  */
GPIO_PinState LHL_GPIO_ReadPin(GPIO_TypeDef *pGPIOx, uint16_t GPIO_Pin_x)
{
    GPIO_PinState bitstatus;
 
    if ((pGPIOx->DATA_IN & (uint32_t)GPIO_Pin_x) != (uint32_t)GPIO_PIN_RESET)
    {
        bitstatus = GPIO_PIN_SET;
    }
    else
    {
        bitstatus = GPIO_PIN_RESET;
    }
    return bitstatus;
}

/**
  * @brief  设定特定引脚的电平
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Pin_x: x取值范围（0...15)
  *         Pin_State: 低电平GPIO_PIN_RESET；高电平GPIO_PIN_SET
  * @retval None
  */
void LHL_GPIO_WritePin(GPIO_TypeDef *pGPIOx, uint16_t GPIO_Pin_x, GPIO_PinState Pin_State)
{
    if (Pin_State == GPIO_PIN_RESET)
    {
        pGPIOx->OCLR = GPIO_Pin_x;
    }
    else
    {
        pGPIOx->OSET = GPIO_Pin_x;
    }
}

/**
  * @brief  翻转特定引脚
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Pin_x: x取值范围（0...15)
  * @retval None
  */
void LHL_GPIO_TogglePin(GPIO_TypeDef *pGPIOx, uint16_t GPIO_Pin_x)
{
    pGPIOx->OTGL = GPIO_Pin_x;
}

/**
  * @brief  读取整个端口的输入电平
  * @param  pGPIOx: x取值范围(0...3)
  * @retval uint8_t格式的端口电平
  */
uint8_t LHL_GPIO_Read(GPIO_TypeDef* pGPIOx)
{
    return ((uint8_t)pGPIOx->DATA_IN);
}

/**
  * @brief  写入整个端口的输出电平
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Port_Val：输出端口电平
  * @retval None
  */
void LHL_GPIO_Write(GPIO_TypeDef* pGPIOx, uint8_t GPIO_Port_Val)
{
    pGPIOx->DATA_OUT = (uint32_t)GPIO_Port_Val;
}

/**
  * @brief  清零特定引脚
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Pin_x: x取值范围（0...15)
  * @retval None
  */
void LHL_GPIO_SetPins(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin_x)
{
    pGPIOx->OSET = GPIO_Pin_x;
}

/**
  * @brief  置位特定引脚
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Pin_x: x取值范围（0...15)
  * @retval None
  */
void LHL_GPIO_ResetPins(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin_x)
{
    pGPIOx->OCLR = GPIO_Pin_x;
}

/**
  * @brief  remapping特定引脚的AFIO重映射功能
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Pin_x: x取值范围（0...15)
  *         GPIO_AF: 默认是GPIOx_AF_GPIO；其余参见规格书
  * @retval None
  */
void LHL_GPIO_SetAFIO(GPIO_TypeDef* pGPIOx, GPIO_t GPIO_x, uint32_t GPIO_AFIO)
{
    uint32_t shift = (uint32_t)GPIO_x << 2;                                     // 等于GPIO_x * 4

    pGPIOx->CON0 = (pGPIOx->CON0 & ~(0xFU << shift)) | (GPIO_AFIO << shift);
}

/**
  * @brief  设定特定引脚的电流驱动能力
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Pin_x: x取值范围（0...15)
  *         GPIO_Current: GPIO_2mA；GPIO_4mA；GPIO_8mA；GPIO_16mA
  * @retval None
  */
void LHL_GPIO_SetCurrent(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin_x, GPIOCurrent_TypeDef GPIO_Current)
{
    uint32_t pinpos, reg;
  
    // 转换GPIO_Pin_x到GPIO_PinPos
    pinpos = LHL_Get_PinPosition(GPIO_Pin_x);
    
    reg = pGPIOx->DR;
    
    reg &= ~(3u << (pinpos*2));
    reg |= (uint32_t)GPIO_Current << (pinpos*2);
    
    pGPIOx->DR = reg;
}

/**
  * @brief  设定特定Port的特定Pin引脚为EXTI外部触发中断源
  * @param  pGPIOx: x取值范围(0...3)
  *         GPIO_Pin_x: x取值范围（0...15)
  * @retval None
  */
void LHL_GPIO_SetEXTILine(GPIO_TypeDef *pGPIOx, uint16_t GPIO_Pin_x)
{
    uint32_t pinpos, temp, reg;
  
    // 转换GPIO_Pin_x到GPIO_PinPos
    pinpos = LHL_Get_PinPosition(GPIO_Pin_x);
    
    if (pGPIOx == pGPIO1)
    {
        temp = (uint32_t)0x01;
    }
    else if (pGPIOx == pGPIO2)
    {
        temp = (uint32_t)0x02;
    }
    else
    {
        temp = (uint32_t)0x00;
    }
    
    reg = pINT_SEL->INT_SEL;
    
    reg &= ~((uint32_t)0xf << (pinpos*4));
    reg |= (temp << (pinpos*4));
    
    pINT_SEL->INT_SEL = reg;
}

/*********************************End of File**********************************/
