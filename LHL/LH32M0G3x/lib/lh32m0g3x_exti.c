/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_exti.c
 * @version    2025-09-01
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  初始化EXTI外设
  * @param  EXTI_Init: 存放设置的EXTI_InitTypeDef结构体指针
  * @retval None
  */
void LHL_EXTI_Init(EXTI_InitTypeDef* EXTI_Init)
{
    uint32_t tmp;
    tmp = (uint32_t)EXTI_BASE;
  
    if (EXTI_Init->LineCmd != DISABLE)
    {
        /* Clear EXTI line configuration */
        pEXTI->IMR &= ~EXTI_Init->Line;
        pEXTI->EMR &= ~EXTI_Init->Line;  

        //通过地址偏移（0或4）选择IMR或EMR
        tmp += EXTI_Init->Mode;
        *(__IO uint32_t *) tmp |= EXTI_Init->Line;

        /* Clear Rising Falling edge configuration */
        pEXTI->RTSR &= ~EXTI_Init->Line;
        pEXTI->FTSR &= ~EXTI_Init->Line;
    
        /* Select the trigger for the selected external interrupts */
        if (EXTI_Init->Trigger == EXTI_TRIGGER_RISING_FALLING)
        {
            /* Rising Falling edge */
            pEXTI->RTSR |= EXTI_Init->Line;
            pEXTI->FTSR |= EXTI_Init->Line;
        }
        else
        {
            tmp = (uint32_t)EXTI_BASE;
            tmp += EXTI_Init->Trigger;

            *(__IO uint32_t *) tmp |= EXTI_Init->Line;
        }
    }
    else
    {
        tmp += EXTI_Init->Mode;

        /* Disable the selected external lines */
        *(__IO uint32_t *) tmp &= ~EXTI_Init->Line;
    }
}

/**
  * @brief  复位EXTI外设寄存器到默认值
  * @param  None
  * @retval None
  */
void LHL_EXTI_DeInit(void)
{
    pEXTI->IMR = 0x00000000;
    pEXTI->EMR = 0x00000000;
    pEXTI->RTSR = 0x00000000; 
    pEXTI->FTSR = 0x00000000; 
    pEXTI->PR = 0x0000FFFF;
}

/**
  * @brief  触发EXTI软件中断
  * @param  EXTI_LINE_x: 指定的EXTI线（x取值范围0~13）
  * @retval None
  */
void LHL_EXTI_GenerateSWI(EXTI_LINE_t EXTI_LINE_x)
{ 
    pEXTI->SWIER |= EXTI_LINE_x;
}

/**
  * @brief  检查EXTI线中断标志是否已设置
  * @param  EXTI_LINE_x: 指定的EXTI线（x取值范围0~13）
  * @retval EXTI线状态（SET or RESET）
  */
FlagStatus LHL_EXTI_GetPending(EXTI_LINE_t EXTI_LINE_x)
{
    return ((pEXTI->PR & EXTI_LINE_x) != RESET) ? SET : RESET;
}

/**
  * @brief  清除EXTI线中断标志
  * @param  EXTI_LINE_x: 指定的EXTI线（x取值范围0~13）
  * @retval None
  */
void LHL_EXTI_ClearPending(EXTI_LINE_t EXTI_LINE_x)
{
    pEXTI->PR = EXTI_LINE_x;
}

/*********************************End of File**********************************/
