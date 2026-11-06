/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    system_lh32m0g3x.c
 * @version    2025-09-01
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/*----------------------------------------------------------------------------
 * Define System Core Clock Variable。
 * 建议使用库函数更新系统时钟，否则此变量必须手动调用SystemCoreClockUpdate进行维护！
 *----------------------------------------------------------------------------*/
__RW uint32_t SystemCoreClock = SYS_VALUE;              /* Default Frequency  */
__RW uint8_t CoreClockShift = 3;
__RW uint32_t HSITrimCode;

/* Functions -----------------------------------------------------------------*/
/**
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 * @param  none
 * @return none
 */
void SystemCoreClockUpdate(void)
{
    uint32_t tmp1,tmp2;    

    /* Get SYSCLK source -----------------------------------------------------*/
    tmp2 = (pRCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos;
    switch (tmp2)
    {
        case 0x00:  /* HSI used as system clock source */
            if (pRCC->CFGR & RCC_CFGR_HSIDIV2_Msk) 
            {
                tmp1 = (HSI_VALUE / 2);
            }
            else
            {
                tmp1 = HSI_VALUE;
            }
            break;
        case 0x01:  /* HSE used as system clock  source */
            tmp1 = HSE_VALUE;
            break;
        case 0x02:  /* LSI used as system clock  source */
            tmp1 = LSI_VALUE;
            break;
        case 0x03:  /* LSE used as system clock  source */
            tmp1 = LSE_VALUE;
            break;
        default:
            tmp1 = (HSI_VALUE / 2);
            break;
    }    
    
    /* Compute HCLK clocks frequencies ---------------------------------------*/
    tmp2 = (pRCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos;
    tmp2 = (tmp2 < 8) ? 0 : ((tmp2 < 12) ? (tmp2 - 7) : (tmp2 - 6));
    
    /* HCLK clock frequency --------------------------------------------------*/
    SystemCoreClock = tmp1 >> tmp2;
    
    CoreClockShift = LHL_Get_ClockShift(16000000u, SystemCoreClock);
}

/**
 * @brief   Setup the microcontroller system before main. 
 * @param   none
 * @return  none
 */
void SystemInit(void)
{
    pRCC->AHBENR |= RCC_AHBENR_DMA1EN_Msk;

    SystemCoreClock = SYS_VALUE;        
    
    CoreClockShift = 3;
    
    HSITrimCode = pRCC->CR;
}

/*********************************End of File**********************************/
