/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_lhl.c
 * @version    2025-09-01
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Exported Variables --------------------------------------------------------*/
__RW uint32_t       uTick;
LHL_TickPrioTypeDef uTickPrio = LHL_TICK_PRIO_HIGHEST;      /* Highest PRIO   */
LHL_TickFreqTypeDef uTickFreq = LHL_TICK_FREQ_DEFAULT;      /* Time Base 1mS  */

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  初始化Systick并设置中断优先级
  */
LHL_StatusTypeDef LHL_SysTick_Init(LHL_TickPrioTypeDef TickPriority)
{
    // 获取系统时钟，更新SystemCoreClock
    SystemCoreClockUpdate();
    
    /*Configure the SysTick to have interrupt in 1ms time basis*/
    if (SysTick_Config(SystemCoreClock / (1000UL / (uint32_t)uTickFreq)) == 0U)
    {
        /* Systick默认优先级最高，如需其他优先级进行修改 */
        if (TickPriority < LHL_TICK_PRIO_HIGHEST)
        {
            NVIC_SetPriority(SysTick_IRQn, TickPriority);
            uTickPrio = TickPriority;
        }
        return LHL_OK;
    }
    else
    {
        return LHL_ERROR;
    }
}

/**
  * @brief  增加全局Tick
  */
void LHL_IncTick(void)
{
    uTick += uTickFreq;
}

/**
  * @brief  获取全局Tick
  */
uint32_t LHL_GetTick(void)
{
    return uTick;
}

/**
  * @brief  获取Systick中断优先级
  */
uint32_t LHL_GetTickPrio(void)
{
    return uTickPrio;
}

/**
  * @brief  获取Systick时基
  */
LHL_TickFreqTypeDef LHL_GetTickFreq(void)
{
    return uTickFreq;
}

/**
  * @brief  暂停Systick中断
  */
void LHL_SuspendTick(void)
{
    /* Disable SysTick Interrupt */
    CLEAR_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  恢复Systick中断
  */
void LHL_ResumeTick(void)
{
    /* Enable SysTick Interrupt */
    SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  根据SystemClock设置Systick重装载值
  */
void LHL_SetTickReload(uint32_t systemclock)
{
    uint32_t tmpreg;
    
    tmpreg = SysTick->CTRL;
    SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);             /* Disable SysTick IRQ and SysTick Timer */
    SysTick->LOAD  = (uint32_t)(systemclock / (1000UL / (uint32_t)uTickFreq) - 1UL);    /* set reload register */
    SysTick->VAL   = 0UL;                                                               /* Load the SysTick Counter Value */
    SysTick->CTRL  = tmpreg;                                                            /* Enable SysTick IRQ and SysTick Timer */
}

/**
  * @brief  根据Freq时基设置Systick计时周期
  */
LHL_StatusTypeDef LHL_SetTickFreq(LHL_TickFreqTypeDef Freq)
{
    LHL_StatusTypeDef status  = LHL_OK;

    if (uTickFreq != Freq)
    {
        /* Apply the new tick Freq  */
        status = LHL_SysTick_Init(uTickPrio);

        if (status == LHL_OK)
        {
            uTickFreq = Freq;
        }
        else
        {
            status = LHL_ERROR;
        }
    }

  return status;
}

/**
  * @brief  禁用所有32个可能的中断
  */
void LHL_Disable_All_IRQs(void)
{
    NVIC->ICER[0U] = 0xFFFFFFFF;    
    __LHL_DSB
    __LHL_ISB
}

/**
  * @brief  清除所有中断挂起标志
  */ 
void LHL_Clear_All_IRQs(void)
{
    NVIC->ICPR[0U] = 0xFFFFFFFF;
    __LHL_DSB
    __LHL_ISB
}

/**
  * @brief  以毫秒（mS）为单位进行硬延时。注意：Systcik堵塞式延时，严禁用于中断！
  */
__WEAK void LHL_Delay(uint32_t mS)
{
    uint32_t tickstart = LHL_GetTick();
    uint32_t wait = mS;

    /* 至少延时1个tick */
    if (wait < LHL_MAX_DELAY)
    {
        wait += (uint32_t)(uTickFreq);
    }

    while ((LHL_GetTick() - tickstart) < wait)
    {
        /* !!!严禁在中断处理中使用LHL_Delay */
    }
}

/**
  * @brief  以微秒（uS）为单位进行软延时，可以用于中断
  * @note   Compute ClockShift based on default ARM M0+ 16MHz Core without any Optimization
  */
__WEAK void LHL_Delay_uS(uint32_t uS)
{
    volatile uint32_t cycle = (uS >> CoreClockShift);
    while(cycle--)
    {
        __NOP();
        __NOTHING;
    }
}

/**
  * @brief  使用编译器内置指令根据GPIO引脚值获取其位置，x取值范围0~15
  */
uint8_t LHL_Get_PinPosition(uint16_t GPIO_PIN_x)
{
    if (GPIO_PIN_x == 0) {
        // 处理特殊情况，GPIO_Pin为0时返回一个错误值或抛出异常
        return 0;
    }
    else {
        #if defined(__CC_ARM) // Keil ARM Compiler
            return (uint8_t)(31 - __clz(GPIO_PIN_x));
        #elif defined(__ICCARM__) // IAR Compiler
            return (uint8_t)(31 - __CLZ(GPIO_PIN_x));
        #else   //GCC Compiler
            return (uint8_t)__builtin_ctz(GPIO_PIN_x);
        #endif
    }
}

/**
  * @brief  根据默认时钟和实际内核时钟估算分频移位值
  */
uint8_t LHL_Get_ClockShift(uint32_t default_clock, uint32_t core_clock)
{
    uint32_t clz_default, clz_core;
    
    if (core_clock == 0) return 0;   // 防止异常
    if (default_clock == 0) return 0; // 原始值太小
    if (core_clock >= default_clock) return 0;
    
    // 使用编译器内置的CLZ函数
    clz_default = __CLZ(default_clock);
    clz_core = __CLZ(core_clock);
    
    // 估算移位次数
    return (uint8_t)(clz_core - clz_default);
}

/**
  * @brief  初始化单个环形缓冲区
  */
void LHL_RB_Init(RingBufferTypeDef *rb, uint8_t *buffer, uint8_t size) {
    rb->data = buffer;
    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

/**
  * @brief  判断环形缓冲区是否为空
  */
bool LHL_RB_IsEmpty(RingBufferTypeDef *rb) {
    return (rb->count == 0);
}

/**
  * @brief  判断环形缓冲区是否已满
  */
bool LHL_RB_IsFull(RingBufferTypeDef *rb) {
    return (rb->count == rb->size);
}

/**
  * @brief  向环形缓冲区存放数据
  */
bool LHL_RB_Put(RingBufferTypeDef *rb, uint8_t byte) {
    if (LHL_RB_IsFull(rb)) return false;
    
    rb->data[rb->head] = byte;
    rb->head = (rb->head + 1) % rb->size;
    rb->count++;
    return true;
}

/**
  * @brief  从环形缓冲区读取数据
  */
bool LHL_RB_Get(RingBufferTypeDef *rb, uint8_t *byte) {
    if (LHL_RB_IsEmpty(rb)) return false;
    
    *byte = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;
    rb->count--;
    return true;
}

/**
  * @brief  获取环形缓冲区有效数据的数量
  */
uint8_t LHL_RB_GetCount(RingBufferTypeDef *rb) {
    return rb->count;
}

/**
  * @brief  带符号四舍五入除法
  */
int32_t LHL_Divide_Round(int32_t dividend, int32_t divisor) 
{
    int8_t sign;
    int32_t abs_dividend, abs_divisor, result;
    
    if (divisor == 0) return 0;
    
    // 判断符号
    sign = ((dividend ^ divisor) < 0) ? -1 : 1;
    
    // 取绝对值
    abs_dividend = (dividend < 0) ? -dividend : dividend;
    abs_divisor = (divisor < 0) ? -divisor : divisor;
    
    // 四舍五入计算
    result = (abs_dividend + abs_divisor / 2) / abs_divisor;
    
    // 恢复符号
    return sign * result;
}

/**
  * @brief  默认PRINTF函数实现，注意勾选MicroLIB，并定义LHL_UART_PRINTF
  */
#ifdef LHL_UART_PRINTF
#ifdef __ICCARM__
int putchar(int c)
{
    while(0 == (LHL_UART_PRINTF->LSR & UART_FLAG_THRE));  
    LHL_UART_PRINTF->RBR_THR_DLL = (unsigned char) c;  
    return c;
}
#else 
/* GCC/ARMCC Compiler UART0 Printf for Reference Only*/
int fputc(int ch, FILE *f)
{
    (void)f;
    LHL_UART_PRINTF->RBR_THR_DLL = (unsigned char) ch;
    while(0 == (LHL_UART_PRINTF->LSR & UART_FLAG_TEMT));
    return ch;
}

int fgetc(FILE *f)
{
    (void)f;
    while (0 == (LHL_UART_PRINTF->LSR & UART_FLAG_DR));
    return (int)LHL_UART_PRINTF->RBR_THR_DLL;  
}
#endif
#endif

/*********************************End of File**********************************/
