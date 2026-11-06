/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_rcc.c
 * @version 2025-09-01
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  按照参数，设置整个时钟树，并同步更新SystemCoreClock和Systick
  * @param  RCC_Clock_Init      时钟树参数
  *         Timeout             超时设定
  * @retval LHL_OK：成功；LHL_ERROR：时钟切换失败。
  */
LHL_StatusTypeDef LHL_RCC_ClockConfig(const RCC_ClockInitTypeDef *RCC_Clock_Init, uint32_t Timeout)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    uint32_t tmp, val, t;
    t = Timeout;
    
    /* 更新HSI分频系数 */
    tmp = pRCC->CFGR;
    if (RCC_Clock_Init->SYSCLKSource & RCC_SYSCLK_SRC_HSI_DIV2)
    {
        tmp |= RCC_CFGR_HSIDIV2_Msk;
    }
    else
    {
        tmp &= ~RCC_CFGR_HSIDIV2_Msk;
    }
    pRCC->CFGR = tmp;
    __NOP();
    
    /* 使用HSE默认开启P1.0 AFIO功能 */
    if (RCC_Clock_Init->SYSCLKSource & RCC_SYSCLK_SRC_HSE)
    {
        GPIO_InitStructure.Pin = GPIO_PIN_0;                       
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT;              
        GPIO_InitStructure.Pull = GPIO_NOPULL;                     
        GPIO_InitStructure.SchmittTrigger = ENABLE;               
        GPIO_InitStructure.Alternate = GPIO1_0_AF_EXTCLKIN;         // P1.0->EXTCLKIN(HSE)
        LHL_GPIO_Init(pGPIO1, &GPIO_InitStructure);   
    }
    
    /* 更新SYSCLK时钟源 */
    val = RCC_Clock_Init->SYSCLKSource & 0x03;
    tmp = pRCC->CFGR;    
    tmp &= ~RCC_CFGR_SW_Msk;
    tmp |= (val << RCC_CFGR_SW_Pos);
    pRCC->CFGR = tmp;
    __NOP();
    
    // 等待切换成功，超时则返回错误
    while (val != ((pRCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos))
    {
        if ((t--) == 0) return LHL_ERROR;
    }
    __NOP();
    
    /* 更新HCLK分频系数 */
    tmp = pRCC->CFGR;
    tmp &= ~RCC_CFGR_HPRE_Msk;
    tmp |= (RCC_Clock_Init->AHBCLKDivider << RCC_CFGR_HPRE_Pos);
    pRCC->CFGR = tmp;
    __NOP();
    
    /* 更新PCLK1分频系数 */
    tmp = pRCC->CFGR;
    tmp &= ~RCC_CFGR_PPRE1_Msk;
    tmp |= (RCC_Clock_Init->APB1CLKDivider << RCC_CFGR_PPRE1_Pos);
    pRCC->CFGR = tmp;
    __NOP();
    
    /* 更新PCLK2分频系数 */
    tmp = pRCC->CFGR;
    tmp &= ~RCC_CFGR_PPRE2_Msk;
    tmp |= (RCC_Clock_Init->APB2CLKDivider << RCC_CFGR_PPRE2_Pos);
      pRCC->CFGR = tmp;
    __NOP();
    
    /* 更新SystemCoreClock全局变量 */
    SystemCoreClockUpdate();
    
    /* 更新Systick时基 */
    //LHL_SetTickReload(SystemCoreClock);
    
    return LHL_OK;
}

/**
  * @brief  获取SYSCLK frequency
  * @note   此功能根据库函数预设的时钟常量计算内核时钟，不一定与硬件完全一致（需正确设置！）:
  * @note     If SYSCLK source is HSI, function returns values based on HSI_VALUE/HSIDIV(*)
  * @note     If SYSCLK source is HSE, function returns values based on HSE_VALUE(**)
  * @note     If SYSCLK source is LSI, function returns values based on LSI_VALUE(***)
  * @note     If SYSCLK source is LSE, function returns values based on LSE_VALUE(****)
  * @note     (*) HSI_VALUE is a constant defined in lh32m0xx_lhl_config.h file (default value
  *               32 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature.
  * @note     (**) HSE_VALUE is a constant defined in lh32m0xx_lhl.h file (default value
  *                32 MHz), user has to ensure that HSE_VALUE is same as the real
  *                frequency of the crystal used. Otherwise, this function may
  *                have wrong result.
  * @note     (***) LSE_VALUE is a constant defined in lh32m0xx_lhl.h file (default value
  *               32768 Hz).
  * @note     (****) LSI_VALUE is a constant defined in lh32m0xx_lhl_config.h file (default value
  *               32000 Hz).
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  * @note   Each time SYSCLK changes, this function must be called to update the
  *         right SYSCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @retval SYSCLK frequency
  */
uint32_t LHL_RCC_GetSystemClockFreq(void)
{
    uint32_t tmp;

    /* Get SYSCLK source -----------------------------------------------------*/
    switch (pRCC->CFGR & RCC_CFGR_SWS_Msk)
    {
        case 0x00:  /* HSI used as system clock source */
            if (pRCC->CFGR & RCC_CFGR_HSIDIV2_Msk) 
            {
                tmp = (HSI_VALUE / 2);
            }
            else
            {
                tmp = HSI_VALUE;
            }
            break;
        case 0x01:  /* HSE used as system clock  source */
            tmp = HSE_VALUE;
            break;
        case 0x02:  /* LSI used as system clock  source */
            tmp = LSI_VALUE;
            break;
        case 0x03:  /* LSE used as system clock  source */
            tmp = LSE_VALUE;
            break;
        default:
            tmp = (HSI_VALUE / 2);
            break;
    }
    
    return tmp;
}

/**
  * @brief  获取HCLK frequency.
  * @note   Each time HCLK changes, this function must be called to update the
  *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @note   基于CMSIS内核主频全局变量SystemCoreClock计算
  * @retval HCLK frequency in Hz
  */
uint32_t LHL_RCC_GetHCLKFreq(void)
{
    return SystemCoreClock;
}

/**
  * @brief  获取PCLK1 frequency.
  * @note   Each time PCLK1 changes, this function must be called to update the
  *         right PCLK1 value. Otherwise, any configuration based on this function will be incorrect.
  * @note   基于CMSIS内核主频全局变量SystemCoreClock计算
  * @retval PCLK1 frequency in Hz
  */
uint32_t LHL_RCC_GetPCLK1Freq(void)
{
    uint32_t tmp, presc;
    
    /* Get PCLK1 prescaler */
    tmp = ((pRCC->CFGR & RCC_CFGR_PPRE1_Msk) >> 8);
    presc = (tmp<4) ? 0:(tmp-3);
    /* Compute PCLK1 frequency */
    return (LHL_RCC_GetHCLKFreq() >> presc);
}

/**
  * @brief  获取PCLK2 frequency.
  * @note   Each time PCLK2 changes, this function must be called to update the
  *         right PCLK2 value. Otherwise, any configuration based on this function will be incorrect.
  * @note   基于CMSIS内核主频全局变量SystemCoreClock计算
  * @retval PCLK2 frequency in Hz
  */
uint32_t LHL_RCC_GetPCLK2Freq(void)
{
    uint32_t tmp, presc;
    
    /* Get PCLK2 prescaler */
    tmp = ((pRCC->CFGR & RCC_CFGR_PPRE2_Msk) >> 11);
    presc = (tmp<4) ? 0:(tmp-3);
    /* Compute PCLK2 frequency */
    return (LHL_RCC_GetHCLKFreq() >> presc);
}

/**
  * @brief  获取时钟树所有频率
  * @param  RCC_Clocks  Pointer to a @ref RCC_ClocksTypeDef structure that will be stored.
  * @note   CMSIS内核主频全局变量SystemCoreClock同步更新
  * @retval None
  */
void LHL_RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, presc = 0;

    /* Get SYSCLK source -------------------------------------------------------*/
    tmp = pRCC->CFGR & RCC_CFGR_SWS_Msk;
    switch (tmp)
    {
        case 0x00:  /* HSI used as system clock source */
            if (pRCC->CFGR & RCC_CFGR_HSIDIV2_Msk) 
            {
                RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE / 2);
            }
            else
            {
                RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            }
            break;
        case 0x01:  /* HSE used as system clock  source */
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
            break;
        case 0x02:  /* LSI used as system clock  source */
            RCC_Clocks->SYSCLK_Frequency = LSI_VALUE;
            break;
        case 0x03:  /* LSE used as system clock  source */
            RCC_Clocks->SYSCLK_Frequency = LSE_VALUE;
            break;
        default:
            RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE / 2);
            break;
    }
    
    /* Compute HCLK, PCLK1 and PCLK2 clocks frequencies ------------------------*/
    /* Get HCLK prescaler */
    tmp = pRCC->CFGR & RCC_CFGR_HPRE_Msk;
    tmp = tmp >> 4;
    presc = (tmp<8) ? 0 : ((tmp<12) ? (tmp-7) : (tmp-6));
    /* HCLK clock frequency */
    RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

    /* Get PCLK1 prescaler */
    tmp = pRCC->CFGR & RCC_CFGR_PPRE1_Msk;
    tmp = tmp >> 8;
    presc = (tmp<4) ? 0:(tmp-3);
    /* PCLK1 clock frequency */
    RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

    /* Get PCLK2 prescaler */
    tmp = pRCC->CFGR & RCC_CFGR_PPRE2_Msk;
    tmp = tmp >> 11;
    presc = (tmp<4) ? 0:(tmp-3);
    /* PCLK2 clock frequency */
    RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
    
    /* 更新全局变量 */
    SystemCoreClock = RCC_Clocks->HCLK_Frequency;
}

/**
  * @brief  通过MCO引脚（ELCKO）输出指定的系统时钟
  * @note   ELCKO引脚应当被正确设置为alternate function mode
  * @param  RCC_MCOSource: specifies the clock source to output：
  *          @arg    RCC_MCOSource_LSI   
  *          @arg    RCC_MCOSource_SYSCLK
  *          @arg    RCC_MCOSource_HSI   
  *          @arg    RCC_MCOSource_HSE
  *          @arg    RCC_MCOSource_PLL_DIV2
  *          @arg    RCC_MCOSource_PCLK1 
  *          @arg    RCC_MCOSource_PCLK2 
  *          @arg    RCC_MCOSource_HCLK  
  * @retval None
  */
void LHL_RCC_MCOConfig(uint32_t RCC_MCOSource)
{
    pRCC->CFGR &= ~RCC_CFGR_MCO_Msk;
    pRCC->CFGR |= RCC_MCOSource<<RCC_CFGR_MCO_Pos;
}

/**
  * @brief  Configures the External Clock Input (HSE).
  * @note   用户必须保证在切换HSE之前，外部时钟已通过P1.0（EXTCLK）正确提供。频率1M~32MHz，占空比50%。
  * @param  NewState:
  *            @arg DISABLE: turn OFF the HSE，系统时钟由HSI提供
  *            @arg ENABLE: turn ON the LSE，系统时钟由HSE提供
  * @retval None
  */
LHL_StatusTypeDef LHL_RCC_HSEConfig(FunctionalState NewState)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    uint32_t tmp;
    uint32_t t = 0xFFFF;                                            //超时设定
    
    /* 更新SYSCLK时钟源 */
    tmp = pRCC->CFGR;    
    tmp &= ~RCC_CFGR_SW_Msk;
    if (NewState == ENABLE)
    {
        /* 使用HSE默认开启P1.0 AFIO功能 */
        GPIO_InitStructure.Pin = GPIO_PIN_0;                       
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT;              
        GPIO_InitStructure.Pull = GPIO_NOPULL;                     
        GPIO_InitStructure.SchmittTrigger = ENABLE;               
        GPIO_InitStructure.Alternate = GPIO1_0_AF_EXTCLKIN;         // P1.0->EXTCLKIN(HSE)
        LHL_GPIO_Init(pGPIO1, &GPIO_InitStructure);   
        
        tmp |= 0x01;
    }
    pRCC->CFGR = tmp;
    __NOP();
    
    /* 等待切换成功，超时则返回错误 */
    while (NewState != ((pRCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos))
    {
        if ((t--) == 0) return LHL_ERROR;
    }   
    
    /* 更新全局时钟变量 */
    SystemCoreClockUpdate();
    
    return LHL_OK;
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_Bypass), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  RCC_LSE: specifies the new state of the LSE.
  *          This parameter can be one of the following values:
  *            @arg DISABLE: turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg ENABLE: turn ON the LSE oscillator
  * @retval None
  */
LHL_StatusTypeDef LHL_RCC_LSEConfig(FunctionalState NewState)
{
    uint32_t t = 0xFFFFFF;  //超时设定
    
    // Enable Domain Clock
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWREN_Msk,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_BKPEN_Msk,ENABLE);
    
    // Enable Domain Access
    PWR_BackupAccessCmd(ENABLE);
    
    if (NewState == ENABLE)
    {
        pRCC->BDCR |= RCC_BDCR_LSEON_Msk;
        while((pRCC->BDCR & RCC_BDCR_LSERDY_Msk) == 0)
        {
            if((t--)==0) return LHL_ERROR;
        }
    }
    else
    {
        pRCC->BDCR &= ~RCC_BDCR_LSEON_Msk;
    }
    return LHL_OK;
}

/**
  * @brief  Configures HSIDIV2 
  * @param  RCC_HSI_DIV: defines the sysclk clock divider when SYSCLKsoure is HSI. 
  *          This parameter can be one of the following values:
  *            @arg RCC_HSI_Div1:  sysclk clock = HSI
  *            @arg RCC_HSI_Div2:  sysclk clock = HSI/2
  * @retval None
  */
void LHL_RCC_HSIConfig(uint32_t RCC_HSI_DIV)
{
    if (RCC_HSI_DIV == RCC_HSI_DIV2)
    {
        pRCC->CFGR |= RCC_CFGR_HSIDIV2_Msk;
    }
    else
    {
        pRCC->CFGR &= ~RCC_CFGR_HSIDIV2_Msk;
    }
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  *         It is used (enabled by hardware) as system clock source after startup
  *         from Reset, wakeup from STOP and STANDBY mode, or in case of failure
  *         of the HSE used directly or indirectly as system clock (if the Clock
  *         Security System CSS is enabled).             
  * @note   HSI can not be stopped if it is used as system clock source. In this case,
  *         you have to select another source of the system clock then stop the HSI.  
  * @note   After enabling the HSI, the application software should wait on HSIRDY
  *         flag to be set indicating that HSI clock is stable and can be used as
  *         system clock source.  
  * @param  NewState: new state of the HSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LHL_RCC_HSICmd(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        pRCC->CR |= RCC_CR_HSION_Msk;
    }
    else
    {
        pRCC->CR &= ~RCC_CR_HSION_Msk;
    }
}

/**
  * @brief  Configures the SYSCLK SOURCE
  * @param  RCC_SYSCLKSource:
  *          This parameter can be one of the following values:
  *            @arg RCC_SW_HSI:  sysclk clock = HSI
  *            @arg RCC_SW_HSE:  sysclk clock = HSE
  *            @arg RCC_SW_LSI:  sysclk clock = LSI
  *            @arg RCC_SW_LSE:  sysclk clock = LSE
  * @retval None
  */
void LHL_RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
    uint32_t reg = pRCC->CFGR;
    
    reg &= ~RCC_CFGR_SW_Msk;
      reg |= RCC_SYSCLKSource<<RCC_CFGR_SW_Pos;
    
    pRCC->CFGR = reg;
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @note   Depending on the device voltage range, the software has to set correctly
  *         these bits to ensure that HCLK not exceed the maximum allowed frequency
  *         (for more details refer to section above
  *           "CPU, AHB and APB busses clocks configuration functions")
  * @param  RCC_SYSCLK: defines the AHB clock divider. This clock is derived from 
  *         the system clock (SYSCLK).
  *          This parameter can be one of the following values:
  *            @arg RCC_SYSCLK_Div1: AHB clock = SYSCLK
  *            @arg RCC_SYSCLK_Div2: AHB clock = SYSCLK/2
  *            @arg RCC_SYSCLK_Div4: AHB clock = SYSCLK/4
  *            @arg RCC_SYSCLK_Div8: AHB clock = SYSCLK/8
  *            @arg RCC_SYSCLK_Div16: AHB clock = SYSCLK/16
  *            @arg RCC_SYSCLK_Div64: AHB clock = SYSCLK/64
  *            @arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *            @arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *            @arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @retval None
  */
void LHL_RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
    uint32_t reg = pRCC->CFGR;

    reg &= ~RCC_CFGR_HPRE_Msk;
    reg |= RCC_SYSCLK<<RCC_CFGR_HPRE_Pos;
    
    pRCC->CFGR = reg;
}

/**
  * @brief  Configures the Low Speed APB clock (PCLK1).
  * @param  RCC_HCLK: defines the APB1 clock divider. This clock is derived from 
  *         the AHB clock (HCLK).
  *          This parameter can be one of the following values:
  *            @arg RCC_HCLK_Div1:  APB1 clock = HCLK
  *            @arg RCC_HCLK_Div2:  APB1 clock = HCLK/2
  *            @arg RCC_HCLK_Div4:  APB1 clock = HCLK/4
  *            @arg RCC_HCLK_Div8:  APB1 clock = HCLK/8
  *            @arg RCC_HCLK_Div16: APB1 clock = HCLK/16
  * @retval None
  */
void LHL_RCC_PCLK1Config(uint32_t RCC_HCLK)
{
    uint32_t reg = pRCC->CFGR;

    reg &= ~RCC_CFGR_PPRE1_Msk;
    reg |= RCC_HCLK<<RCC_CFGR_PPRE1_Pos;
    
    pRCC->CFGR = reg;
}

/**
  * @brief  Configures the High Speed APB clock (PCLK2).
  * @param  RCC_HCLK: defines the APB2 clock divider. This clock is derived from 
  *         the AHB clock (HCLK).
  *          This parameter can be one of the following values:
  *            @arg RCC_HCLK_Div1:  APB2 clock = HCLK
  *            @arg RCC_HCLK_Div2:  APB2 clock = HCLK/2
  *            @arg RCC_HCLK_Div4:  APB2 clock = HCLK/4
  *            @arg RCC_HCLK_Div8:  APB2 clock = HCLK/8
  *            @arg RCC_HCLK_Div16: APB2 clock = HCLK/16
  * @retval None
  */
void LHL_RCC_PCLK2Config(uint32_t RCC_HCLK)
{
    uint32_t reg = pRCC->CFGR;

    reg &= ~RCC_CFGR_PPRE2_Msk;
    reg |= RCC_HCLK<<RCC_CFGR_PPRE2_Pos;
    
    pRCC->CFGR = reg;
}

/**
  * @brief  Configures the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using PWR_BackupAccessCmd(ENABLE) function before to configure
  *         the RTC clock source (to be done once after reset).    
  * @note   Once the RTC clock is configured it can't be changed unless the  
  *         Backup domain is reset using RCC_BackupResetCmd() function, or by
  *         a Power On Reset (POR).
  *    
  * @param  RCC_RTCCLKSource: specifies the RTC clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_RTCCLKSource_LSE: LSE selected as RTC clock
  *            @arg RCC_RTCCLKSource_LSI: LSI selected as RTC clock
  *            @arg RCC_RTCCLKSource_HSE_Div128: HSE clock divided by 128
  *  
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.    
  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
  *         RTC clock source).
  *  
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
    uint32_t reg = pRCC->BDCR;

    reg &= ~RCC_BDCR_RTCSEL_Msk;
    /* Select the RTC clock source */
    reg |= RCC_RTCCLKSource;
    
    pRCC->BDCR = reg;    
}

/**
  * @brief  Enables or disables the RTC clock.
  * @note   This function must be used only after the RTC clock source was selected
  *         using the RCC_RTCCLKConfig function.
  * @param  NewState: new state of the RTC clock. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
    uint32_t reg = pRCC->BDCR;
    
    reg &= ~RCC_BDCR_RTCEN_Msk;
    reg |= (uint32_t)NewState << RCC_BDCR_RTCEN_Pos;
    
    pRCC->BDCR = reg;
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.   
  * @param  RCC_AHBPeriph: specifies the AHB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHBENR_DMA1EN_Msk:
  *            @arg RCC_AHBENR_SRAMEN_Msk:
  *            @arg RCC_AHBENR_FLITFEN_Msk:
  *            @arg RCC_AHBENR_CRCEN_Msk:
  *            @arg RCC_AHBENR_GPIOEN_Msk:
  *            @arg RCC_AHBENR_MCALEN_Msk:
  *            @arg RCC_AHBENR_BTIMEN_Msk:
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        pRCC->AHBENR |= RCC_AHBPeriph;
    }
    else
    {
        pRCC->AHBENR &= ~RCC_AHBPeriph;
    }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it. 
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB1ENR_TIM2EN_Msk:
  *            @arg RCC_APB1ENR_SPI1EN_Msk:
  *            @arg RCC_APB1ENR_UART1EN_Msk:
  *            @arg RCC_APB1ENR_I2CEN_Msk:
  *            @arg RCC_APB1ENR_BKPEN_Msk:
  *            @arg RCC_APB1ENR_PWREN_Msk:
  *            @arg RCC_APB1ENR_LPT1EN_Msk:
  *            @arg RCC_APB1ENR_LPT2EN_Msk:
  *            @arg RCC_APB1ENR_FLASHEN_Msk:
  *            @arg RCC_APB1ENR_DACEN_Msk:
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        pRCC->APB1ENR |= RCC_APB1Periph;
    }
    else
    {
        pRCC->APB1ENR &= ~RCC_APB1Periph;
    }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB2ENR_ADC0EN_Msk:
  *            @arg RCC_APB2ENR_ADC1EN_Msk:
  *            @arg RCC_APB2ENR_TIM1EN_Msk:
  *            @arg RCC_APB2ENR_SPI0EN_Msk:
  *            @arg RCC_APB2ENR_UART0EN_Msk:
  *            @arg RCC_APB2ENR_MIOEN_Msk: 
  *            @arg RCC_APB2ENR_CORSSBAREN_Msk:
  *            @arg RCC_APB2ENR_CAM0EN_Msk:
  *            @arg RCC_APB2ENR_AFEEN_Msk:
  *            @arg RCC_APB2ENR_PWMEN_Msk:
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        pRCC->APB2ENR |= RCC_APB2Periph;
    }
    else
    {
        pRCC->APB2ENR &= ~RCC_APB2Periph;
    }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB1RSTR_TIM2RST_Msk:
  *            @arg RCC_APB1RSTR_SPI1RST_Msk:
  *            @arg RCC_APB1RSTR_UART1RST_Msk:
  *            @arg RCC_APB1RSTR_I2CRST_Msk:
  *            @arg RCC_APB1RSTR_BKPRST_Msk:
  *            @arg RCC_APB1RSTR_PWRRST_Msk:
  *            @arg RCC_APB1RSTR_DACRST_Msk:
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    pRCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    pRCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB2RSTR_ADC1RST_Msk:
  *            @arg RCC_APB2RSTR_ADC2RST_Msk:
  *            @arg RCC_APB2RSTR_TIM1RST_Msk:
  *            @arg RCC_APB2RSTR_SPI0RST_Msk:
  *            @arg RCC_APB2RSTR_UART0RST_Msk:
  *            @arg RCC_APB2RSTR_MIORST_Msk:
  *            @arg RCC_APB2RSTR_CORSSBARRST_Msk:
  *            @arg RCC_APB2RSTR_CAM0RST_Msk: 
  *            @arg RCC_APB2RSTR_GPIORST_Msk:
  *            @arg RCC_APB2RSTR_AFERST_Msk:
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    pRCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    pRCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  设置RCC中断
  * @param  RCC_IT: specifies the RCC interrupt sources to be enabled or disabled：
  *         @arg    RCC_CIR_LSIRDYIE_Msk: LSI ready interrupt
  * @param  NewState：ENABLE or DISABLE.
  * @retval None
  */
void LHL_RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        pRCC->CIR |= RCC_IT;
    }
    else
    {
        pRCC->CIR &= ~RCC_IT;
    }
}

/**
  * @brief  检查RCC指定标志是否置位
  * @param  RCC_FLAG: specifies the flag to check：
  *         @arg    RCC_FLAG_LSIRDY: LSI oscillator clock ready
  *         @arg    RCC_FLAG_PVDRST: POR/PDR or BOR reset
  *         @arg    RCC_FLAG_PINRST: Pin reset
  *         @arg    RCC_FLAG_SFTRST: Software reset
  *         @arg    RCC_FLAG_IWDGRST: Independent Watchdog reset
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus LHL_RCC_GetFlag(uint32_t RCC_FLAG)
{
    uint32_t statusreg = 0;
    FlagStatus bitstatus = RESET;

    /* Get the RCC register index */
    statusreg = pRCC->CSR;

    /* Get the flag position */
    if ((statusreg & RCC_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
  * @brief  清除RCC复位标志
  * @param  None
  * @retval None
  */
void LHL_RCC_ClearFlag(void)
{
    /* Set RMVF bit to clear the reset flags */
    pRCC->CSR |= RCC_CSR_RMVF_Msk;
}

/**
  * @brief  检查RCC指定中断是否置位
  * @param  RCC_IT: specifies the RCC interrupt source to check：
  *         @arg    RCC_CIR_LSIRDYF_Msk: LSI ready interrupt
  * @retval The new state of RCC_IT (SET or RESET).
  */
ITStatus LHL_RCC_GetPending(uint32_t RCC_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the status of the specified RCC interrupt */
    if ((pRCC->CIR & RCC_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the RCC_IT status */
    return  bitstatus;
}

/**
  * @brief  清除RCC中断标志位
  * @param  RCC_IT: specifies the interrupt pending bit to clear：
  *         @arg    RCC_CIR_LSIRDYC_Msk: LSI ready interrupt
  * @retval None
  */
void LHL_RCC_ClearPending(uint32_t RCC_IT)
{
    pRCC->CIR |= RCC_IT;
}

/**
  * @brief  获取系统复位源状态
  * @param  无
  * @retval 包含所有复位源状态的结构体
  */
RCC_ResetSourceTypeDef LHL_RCC_GetResetSource(void)
{
    __RW uint32_t csr = pRCC->CSR;  // 读取CSR寄存器一次
    RCC_ResetSourceTypeDef resetSource = {
        .PORReset = (csr & RCC_CSR_PORRSTF_Msk) ? SET : RESET,
        .PINReset = (csr & RCC_CSR_PINRSTF_Msk) ? SET : RESET,
        .SFTReset = (csr & RCC_CSR_SFTRSTF_Msk) ? SET : RESET,
        .IWDGReset = (csr & RCC_CSR_IWDGRSTF_Msk) ? SET : RESET,
    };

    /* 清除复位标志（写1清标志）*/
    pRCC->CSR |= RCC_CSR_RMVF_Msk;
    
    return resetSource;
}

/**
  * @brief  复位HSI初始寄存器
  * @param  Null
  * @retval Null
  */
void LHL_RCC_ResetHSI(void)
{
    LHL_RCC_Unlock();
    pRCC->CR = HSITrimCode;
    LHL_RCC_Lock();  
}

/**
  * @brief  写入HSI校准值
  * @param  无
  * @retval 包含所有复位源状态的结构体
  */
#define HSI_TRIM_STEP   10              /* 80k/STEP，对应32M/8=4M OSC，单位kHz */
#define HSI_CAL_STEP    135             /* 1080k/CAL */

void LHL_RCC_CalibrateHSI(uint32_t Measured_Frequency, uint32_t Target_Frequency)
{
    int32_t iFreqDiff, iTrimDiff;
    uint8_t uCAL, uTrim;
    uint32_t uFreqH, uFreqL;
    __RW uint32_t cr;
    
    uint32_t uTrimStep = HSI_TRIM_STEP * Target_Frequency / 4000;   /* 根据目标频率计算分频 */
    uint32_t uCalStep = HSI_CAL_STEP * Target_Frequency / 4000;
    
    /* 读取CSR寄存器 */
    cr = pRCC->CR;
    
    /* 归一化系数 */
    uCAL = (cr >> 8) & 0x1F;                                        
    uTrim = (cr >> 3) & 0x1F;
    if (uTrim >= 0x10)             
    {
        uTrim = 0x1F - uTrim;
    }
    else
    {
        uTrim = uTrim + 0x10;
    }
    uFreqL = Measured_Frequency - uTrim*uTrimStep - uTrimStep/2;            //计算上下限
    uFreqH = Measured_Frequency + (0x1F - uTrim)*uTrimStep + uTrimStep/2;

    /* 计算Cal Code，设计校准区间±3%（规格书HRC最大频率误差） */
    if (Target_Frequency >= uFreqH)
    {
//        iCalDiff = (int32_t)(Target_Frequency - Measured_Frequency)/(int32_t)uCalStep;
        uCAL++;
        Target_Frequency = Target_Frequency - uCalStep;
    }
    else if (Target_Frequency <= uFreqL)
    {
        uCAL--;
        Target_Frequency = Target_Frequency + uCalStep;
    }
    
    /* 计算Trim Code */
    iFreqDiff = (int32_t)Target_Frequency - (int32_t)Measured_Frequency;
    iTrimDiff = LHL_Divide_Round(iFreqDiff, (int32_t)uTrimStep);
    uTrim = uTrim + (uint8_t)iTrimDiff;
    
    /* 还原系数 */
    if (uTrim >= 0x10)
    {
        uTrim = uTrim - 0x10;
    }
    else
    {
        uTrim = 0x1F - uTrim;
    }

    /* 写入寄存器 */
    cr &= ~(uint32_t)0x1FF8;
    cr |= ((uint32_t)(uCAL&0x1F) << 8) | ((uint32_t)(uTrim&0x1F) << 3); 
    LHL_RCC_Unlock();
    pRCC->CR = cr;
    LHL_RCC_Lock();    
}

/**
  * @brief  Unlock HSI
  */
void LHL_RCC_Unlock(void)
{
    *((__RW uint32_t *)0x40012830) = 0xAC;
}

/**
  * @brief  Lock HSI
  */
void LHL_RCC_Lock(void)
{
    *((__RW uint32_t *)0x40012830) = 0x53;
}
/*********************************End of File**********************************/
