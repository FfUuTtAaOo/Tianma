;/**************************************************************************//**
; * @file     startup_ARMCM0.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM0 Device Series
; * @version  V1.08
; * @version     23. November 2012
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000             ;!!!Make sure if need: 0x00000400 

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY ;
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp            ; Top of Stack
                DCD     Reset_Handler           ; Reset Handler
                DCD     NMI_Handler             ; NMI Handler
                DCD     HardFault_Handler       ; Hard Fault Handler
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     SVC_Handler             ; SVCall Handler
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     PendSV_Handler          ; PendSV Handler
                DCD     SysTick_Handler         ; SysTick Handler

                ; External Interrupts
                DCD     0                       ; Reserved
                DCD     PVD_IRQHandler          ; PVD 1:  
                DCD     ADC_ERR_IRQHandler      ;ADC ERROR  2:  
                DCD     RTC_IRQHandler          ;  3:  RTC
                DCD     CROSSLINK_IRQHandler    ;CROSSLINK  4:  
                DCD     RCC_IRQHandler          ;  5:  RCC
                DCD     EXTI0_1_IRQHandler      ;EXTI Line 0,1  6: 
                DCD     EXTI2_3_IRQHandler      ;EXTI Line 2,3  7:  
                DCD     EXTI4_7_IRQHandler      ;EXTI Line 4..7  8:  
                DCD     DMA1_CH0_IRQHandler     ;DMA1_Channel 0  9
                DCD     DMA1_CH1_IRQHandler     ;DMA1_Channel 1 10:
                DCD     DMA1_CH2_3_IRQHandler   ;DMA1_Channel 2,3 11: 
                DCD     SPI0_IRQHandler         ;SPI0 12:
                DCD     UART0_IRQHandler        ;UART0 13: 
                DCD     RTCAlarm_IRQHandler     ;RTCAlarm 14:
                DCD     QSPI_IRQHandlern        ;QSPI FLASH 15: 
                DCD     MIO_IRQHandler          ;MIO 16:
                DCD     SPI1_IRQHandler         ;SPI1 17:
                DCD     ADC0_IRQHandler         ;ADC0 ready 18:
                DCD     ADC1_IRQHandler         ;ADC1 ready 19: 
                DCD     TIM5_IRQHandler         ;TIM5 20: 
                DCD     UART1_IRQHandler        ;UART1 21: 
                DCD     TIM6_IRQHandler         ;TIM6 22: 
                DCD     EEPROM_IRQHandler       ;AFE EEPROM prog 23: 
                DCD     EXTI10_11_IRQHandler    ;EXTI Line 10,11 24: 
                DCD     EXTI12_13_IRQHandler    ;EXTI Line 12,13 25: 
                DCD     LPTIM2_IRQHandler       ;LPTIM2 trigger 26: 
                DCD     TIM1_IRQHandler         ;TIM1 Global 27: 
                DCD     TIM2_IRQHandler         ;TIM2 Global 28: 
                DCD     LPTIM1_IRQHandler       ;LPTIM1 trigger 29: 
                DCD     MACL_IRQHandler         ; MACL RDY,ERR 30: 
                DCD     I2C1_EV_IRQHandler      ;I2C1 Evnt 31: 
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  PVD_IRQHandler            [WEAK]    
                EXPORT  ADC_ERR_IRQHandler        [WEAK]        
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  CROSSLINK_IRQHandler      [WEAK]            
                EXPORT  RCC_IRQHandler            [WEAK]    
                EXPORT  EXTI0_1_IRQHandler        [WEAK]    
                EXPORT  EXTI2_3_IRQHandler        [WEAK]    
                EXPORT  EXTI4_7_IRQHandler        [WEAK]    
                EXPORT  DMA1_CH0_IRQHandler       [WEAK]    
                EXPORT  DMA1_CH1_IRQHandler       [WEAK]     
                EXPORT  DMA1_CH2_3_IRQHandler     [WEAK]     
                EXPORT  SPI0_IRQHandler           [WEAK]     
                EXPORT  UART0_IRQHandler          [WEAK]     
                EXPORT  RTCAlarm_IRQHandler       [WEAK]     
                EXPORT  QSPI_IRQHandlern          [WEAK]     
                EXPORT  MIO_IRQHandler            [WEAK]     
                EXPORT  SPI1_IRQHandler           [WEAK]     
                EXPORT  ADC0_IRQHandler           [WEAK]     
                EXPORT  ADC1_IRQHandler           [WEAK]         
                EXPORT  TIM5_IRQHandler           [WEAK] 
                EXPORT  UART1_IRQHandler          [WEAK]                                         
                EXPORT  TIM6_IRQHandler           [WEAK]     
                EXPORT  EEPROM_IRQHandler         [WEAK]     
                EXPORT  EXTI10_11_IRQHandler      [WEAK]     
                EXPORT  EXTI12_13_IRQHandler      [WEAK]     
                EXPORT  LPTIM2_IRQHandler         [WEAK]        
                EXPORT  TIM1_IRQHandler           [WEAK] 
                EXPORT  TIM2_IRQHandler           [WEAK] 
                EXPORT  LPTIM1_IRQHandler         [WEAK] 
                EXPORT  MACL_IRQHandler           [WEAK] 
                EXPORT  I2C1_EV_IRQHandler        [WEAK] 

PVD_IRQHandler           
ADC_ERR_IRQHandler           
RTC_IRQHandler           
CROSSLINK_IRQHandler         
RCC_IRQHandler           
EXTI0_1_IRQHandler         
EXTI2_3_IRQHandler         
EXTI4_7_IRQHandler         
DMA1_CH0_IRQHandler         
DMA1_CH1_IRQHandler         
DMA1_CH2_3_IRQHandler           
SPI0_IRQHandler          
UART0_IRQHandler         
RTCAlarm_IRQHandler     
QSPI_IRQHandlern         
MIO_IRQHandler        
SPI1_IRQHandler           
ADC0_IRQHandler           
ADC1_IRQHandler          
TIM5_IRQHandler 
UART1_IRQHandler
TIM6_IRQHandler    
EEPROM_IRQHandler     
EXTI10_11_IRQHandler
EXTI12_13_IRQHandler     
LPTIM2_IRQHandler 
TIM1_IRQHandler
TIM2_IRQHandler        
LPTIM1_IRQHandler   
MACL_IRQHandler
I2C1_EV_IRQHandler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, =(Heap_Mem +  Heap_Size)
                LDR     R3, =Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
