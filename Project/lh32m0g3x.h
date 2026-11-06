/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g3x.h
 * @version 2025-09-01
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3X_H
#define __LH32M0G3X_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Defines -------------------------------------------------------------------*/
#ifdef cplusplus 
    #define __RO volatile  
#else
    #define __RO volatile const     //Read Only 
#endif        
#define __WO volatile               //Write Only 
#define __RW volatile               //Read and Write

#define SET_BIT(REG, BIT)           ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)         ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)          ((REG) & (BIT))

#define CLEAR_REG(REG)              ((REG) = (0x0))

#define WRITE_REG(REG, VAL)         ((REG) = (VAL))

#define READ_REG(REG)               ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/* Registers Map -------------------------------------------------------------*/
//----------------------------------------------------
//Regsiter Structure Definition for Module TIMER
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CR1;                /*!<控制寄存器 1*/
    __RW uint32_t CR2;                /*!<控制寄存器 2*/
    __RW uint32_t SMCR;                /*!<从模式控制寄存器*/
    __RW uint32_t DIER;                /*!<DMA/中断使能寄存器*/
    __RW uint32_t SR;                /*!<状态寄存器*/
    __RW uint32_t EGR;                /*!<事件产生寄存器*/
    __RW uint32_t CCMR1;        /*!<通道用于输出比较模式，通道的方向由相应的CCxS定义。该寄存器其它位的作用在输入和输出模式下不同。OCxx描述了通道在输出模式下的功能，ICxx描述了通道在输出模式下的功能。因此必须注意，同一个位在输出模式和输入模式下的功能是不同的。*/
    __RO uint8_t RESERVED0[4];
    __RW uint32_t CCER;                /*!<捕获/比较使能寄存器*/
    __RW uint32_t CNT;                /*!<计数器*/
    __RW uint32_t PSC;                /*!<预分频器*/
    __RW uint32_t ARR;                /*!<自动重装载寄存器*/
    __RO uint8_t RESERVED1[4];
    __RW uint32_t CCR1;                /*!<捕获/比较寄存器 1*/
    __RW uint32_t CCR2;                /*!<捕获/比较寄存器 2*/
    __RO uint8_t RESERVED2[12];
    __RW uint32_t DCR;                /*!<DMA控制寄存器*/
    __RW uint32_t DMAR;                /*!<连续模式的DMA地址*/
}TIM_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module LPTIM
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CSR;                /*!<*/
    __RW uint32_t PSR;                /*!<*/
    __RW uint32_t CMR;                /*!<*/
    __RW uint32_t CNR;                /*!<*/
    __RW uint32_t ARR;                /*!<*/
}LPTIM_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module RTC
//----------------------------------------------------
typedef struct
{
    __RW uint16_t CRH;                /*!<RTC控制寄存器高位*/
    __RO uint8_t RESERVED0[2];
    __RW uint16_t CRL;                /*!<中断使能寄存器*/
    __RO uint8_t RESERVED1[2];
    __RW uint16_t PRLH;                /*!<RTC预分频装载寄存器高位. 预分频装载寄存器用来保存RTC预分频器的周期计数值。它们受RTC_CR寄存器的RTOFF位保护，仅当RTOFF值为’1’时允许进行写操作。*/
    __RO uint8_t RESERVED2[2];
    __RW uint16_t PRLL;                /*!<RTC预分频装载寄存器低位。 预分频装载寄存器用来保存RTC预分频器的周期计数值。它们受RTC_CR寄存器的RTOFF位保护，仅当RTOFF值为’1’时允许进行写操作。*/
    __RO uint8_t RESERVED3[2];
    __RW uint16_t DIVH;                /*!<RTC预分频器余数寄存器高位*/
    __RO uint8_t RESERVED4[2];
    __RW uint16_t DIVL;                /*!<RTC预分频器余数寄存器低位*/
    __RO uint8_t RESERVED5[2];
    __RW uint16_t CNTH;                /*!<RTC计数器寄存器高位*/
    __RO uint8_t RESERVED6[2];
    __RW uint16_t CNTL;                /*!<RTC计数器寄存器低位*/
    __RO uint8_t RESERVED7[2];
    __RW uint16_t ALRH;                /*!<RTC闹钟寄存器高位*/
    __RO uint8_t RESERVED8[2];
    __RW uint16_t ALRL;                /*!<RTC闹钟寄存器低位*/
}RTC_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module IWDG
//----------------------------------------------------
typedef struct
{
    __RW uint32_t KR;                /*!<键寄存器*/
    __RW uint32_t PR;                /*!<预分频寄存器*/
    __RW uint32_t RLR;                /*!<重装载寄存器*/
    __RW uint32_t SR;                /*!<状态寄存器*/
    __RW uint32_t EN;                /*!<看门狗使能寄存器*/
    __RW uint32_t LOCK;                /*!<看门狗配置死锁寄存器*/
}IWDG_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module SPI
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CR1;                /*!<SPI控制寄存器1*/
    __RW uint32_t CR2;                /*!<SPI控制寄存器2*/
    __RW uint32_t SR;                /*!<SPI 状态寄存器*/
    __RW uint32_t DR;                /*!<SPI 数据寄存器*/
    __RW uint32_t CRCPR;                /*!<SPI CRC多项式寄存器*/
    __RW uint32_t RXCRCR;                /*!<SPI Rx CRC寄存器*/
    __RW uint32_t TXCRCR;                /*!<SPI Tx CRC寄存器*/
}SPI_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module FLASH
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CTRL;                /*!<控制寄存器*/
    __RW uint32_t CMD;                /*!<命令寄存器*/
    __RW uint32_t PAGE_ADDR0;                /*!<页擦除/签名起始地址*/
    __RO uint8_t RESERVED0[4];
    __RW uint32_t STAT;                /*!<状态寄存器*/
    __RW uint32_t USER_WR_PROT;                /*!<用户空间写保护bit*/
    __RO uint8_t RESERVED1[4];
    __RW uint32_t USERKEY;                /*!<userkey*/
}FLASH_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module UART
//----------------------------------------------------
typedef struct
{
    __RW uint32_t RBR_THR_DLL;                /*!<RBR-接收缓冲寄存器。内含下一个要读取的已接收字符。THR-发送保持寄存器。在此写入下一个要发送的字符。DLL-除数锁存器LSB。波特率除数值的最低有效字节。分数波特
率分频器是使用整个除数来产生波特率的。*/
    __RW uint32_t IER_DLH;                /*!<IER-中断使能寄存器;DLH-除数锁存器MSB。波特率除数值的最高有效字节。分数波特
率分频器是使用整个除数来产生波特率的。*/
    __RW uint32_t IIR;                /*!<中断ID寄存器。识别处于挂起状态的中断。*/
    __RW uint32_t LCR;                /*!<线控制寄存器。包含帧格式控制和间隔产生控制。*/
    __RW uint32_t MCR;                /*!<Modem 控制寄存器。包含流控制握手控制和回写模式控制。*/
    __RW uint32_t LSR;                /*!<线状态寄存器。包含发送和接收的状态标志（包括线错误）。*/
    __RW uint32_t MSR;                /*!<Modem 状态寄存器。包含握手信号状态标志。*/
    __RW uint32_t SCR;                /*!<高速缓存寄存器。 8 位的临时存储空间，供软件使用。*/
    __RO uint8_t RESERVED0[80];
    __RW uint32_t FAR;                /*!<*/
    __RO uint8_t RESERVED1[8];
    __RW uint32_t USR;                /*!<UART状态寄存器*/
    __RO uint8_t RESERVED2[36];
    __RW uint32_t HTX;                /*!<UART停止发送寄存器*/
    __RW uint32_t DMASA;                /*!<DMA软件应答寄存器*/
    __RO uint8_t RESERVED3[20];
    __RW uint32_t DLF;                /*!<分数分频器寄存器。为波特率分频器产生时钟输入。*/
    __RW uint32_t RAR;                /*!<接收模式地址寄存器*/
    __RW uint32_t TAR;                /*!<发送模式地址寄存器*/
    __RW uint32_t LCR_EXT;              /*!<线控制扩展功能寄存器*/
}UART_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module I2C
//----------------------------------------------------
typedef struct
{
    __RW uint16_t CR1;                /*!<控制寄存器1*/
    __RO uint8_t RESERVED0[2];
    __RW uint16_t CR2;                /*!<控制寄存器2*/
    __RO uint8_t RESERVED1[2];
    __RW uint16_t OAR1;                /*!<自身地址寄存器1*/
    __RO uint8_t RESERVED2[2];
    __RW uint16_t OAR2;                /*!<自身地址寄存器2*/
    __RO uint8_t RESERVED3[2];
    __RW uint16_t DR;                /*!<软件中断事件寄存器*/
    __RO uint8_t RESERVED4[2];
    __RW uint16_t SR1;                /*!<状态寄存器1*/
    __RO uint8_t RESERVED5[2];
    __RW uint16_t SR2;                /*!<状态寄存器2*/
    __RO uint8_t RESERVED6[2];
    __RW uint16_t CCR;                /*!<时钟控制寄存器*/
    __RO uint8_t RESERVED7[2];
    __RW uint16_t TRISE;                /*!<TRISE寄存器*/
}I2C_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module AON
//----------------------------------------------------
typedef struct
{
    __RO uint8_t RESERVED0[44];
    __RW uint32_t BKP_RTCCR;                /*!<*/
}AON_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module PWR
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CR;                /*!<*/
    __RW uint32_t CSR;                /*!<*/
}PWR_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module EXTI
//----------------------------------------------------
typedef struct
{
    __RW uint32_t IMR;                /*!<中断屏蔽寄存器*/
    __RW uint32_t EMR;                /*!<事件屏蔽寄存器*/
    __RW uint32_t RTSR;                /*!<上升沿触发选择寄存器*/
    __RW uint32_t FTSR;                /*!<下降沿触发选择寄存器*/
    __RW uint32_t SWIER;                /*!<软件中断事件寄存器*/
    __RW uint32_t PR;                /*!<挂起寄存器*/
}EXTI_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module GPIO0
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CON0;                /*!<GPIO0端口复用选择寄存器0*/
    __RW uint32_t OE;                /*!<GPIO0输出使能寄存器*/
    __RW uint32_t PUE;                /*!<GPIO0上拉使能寄存器*/
    __RW uint32_t PDE;                /*!<GPIO0下拉使能寄存器*/
    __RW uint32_t OD;                /*!<GPIO0开漏使能寄存器*/
    __RW uint32_t IE;                /*!<GPIO0输入使能寄存器*/
    __RW uint32_t SMT;                /*!<GPIO0施密特输入使能寄存器*/
    __RW uint32_t SL;                /*!<GPIO0压摆率*/
    __RW uint32_t DR;                /*!<GPIO0驱动能力选择寄存器*/
    __RW uint32_t DATA_IN;                /*!<GPIO0输入数据寄存器*/
    __RW uint32_t DATA_OUT;                /*!<GPIO0输出数据寄存器*/
    __RW uint32_t OSET;                /*!<GPIO0输出数据置位寄存器*/
    __RW uint32_t OCLR;                /*!<GPIO0输出数据复位寄存器*/
    __RW uint32_t OTGL;                /*!<GPIO0输出数据翻转寄存器*/
    __RO uint8_t RESERVED0[4];
    __RW uint32_t INT_SEL;                /*!<外中断管脚选择寄存器*/
}GPIO_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for INT_SEL reg
//----------------------------------------------------
typedef struct
{
    __RW uint32_t INT_SEL;               
}GPIO_INT_SEL_TypeDef;

//----------------------------------------------------
//Regsiter Structure Definition for Module AFE
//----------------------------------------------------
typedef struct
{
    __RW uint32_t NOP;                /*!<*/
    __RW uint32_t PAGE;                /*!<*/
    __RW uint32_t STATUS;                /*!<*/
    __RW uint32_t CFG;                /*!<*/
    __RW uint32_t SPI_CFG;                /*!<*/
    __RW uint32_t PWM_CTRL;                /*!<*/
    __RO uint8_t RESERVED1[4];
    __RW uint32_t REF_CTRL;                /*!<*/
    __RW uint32_t IEXC_RANGE;                /*!<*/
    __RW uint32_t IEXC_CTRL;                /*!<*/
    __RO uint8_t RESERVED0[8];
    __RW uint32_t USERKEY;                /*!<*/
}AFE_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module DAC
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CTRL;                /*!<*/
    __RW uint32_t DATA;                /*!<*/
    __RW uint32_t CLAMPH;                /*!<*/
    __RW uint32_t CLAMPL;                /*!<*/
    __RW uint32_t AOUT_REG0;                /*!<*/
    __RW uint32_t AOUT_REG1;                /*!<*/
}DAC_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module ADC_SUBSYS_USER
//----------------------------------------------------
typedef struct
{
    __RW uint32_t ERROR_STATUS;                /*!<common 寄存器；*/
    __RW uint32_t ERROR_EN;                /*!<common 寄存器；*/
    __RW uint32_t ADC_DRDY;                /*!<common 寄存器；*/
    __RW uint32_t DMA_MODE;                /*!<common 寄存器；*/
    __RW uint32_t IO_CONTROL_IOUT;                /*!<common 寄存器；*/
    __RW uint32_t IO_CONTROL_VBIAS;                /*!<common 寄存器；*/
    __RW uint32_t ADC_STATUS_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t ADC_DATA_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t INTERRUPT_CONTROL_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t ADC_CONTROL_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t CHANNEL_CFG_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t CONFIGURATION_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t FILTER_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t OFFSET_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t GAIN_0;                /*!<ADC 0 寄存器；*/
    __RW uint32_t ADC_0_HI_COMPARATOR;                /*!<ADC 0 寄存器；*/
    __RW uint32_t ADC_0_LO_COMPARATOR;                /*!<ADC 0 寄存器；*/
    __RW uint32_t ADC_STATUS_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t ADC_DATA_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t INTERRUPT_CONTROL_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t ADC_CONTROL_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t CHANNEL_CFG_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t CONFIGURATION_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t FILTER_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t OFFSET_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t GAIN_1;                /*!<ADC 1 寄存器；*/
    __RW uint32_t ADC_1_HI_COMPARATOR;                /*!<ADC 1 寄存器；*/
    __RW uint32_t ADC_1_LO_COMPARATOR;                /*!<ADC 1 寄存器；*/
}ADC_SUBSYS_USER_TypeDef;
//----------------------------------------------------
//----------------------------------------------------
//Regsiter Structure Definition for Module MIO
//----------------------------------------------------
typedef struct {
  __RO  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  __RO  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  __RW uint32_t CTRL;                              /**< MIO Control Register, offset: 0x8 */
  __RO  uint32_t PIN;                               /**< Pin State Register, offset: 0xC */
  __RW uint32_t SHIFTSTAT;                         /**< Shifter Status Register, offset: 0x10 */
  __RW uint32_t SHIFTERR;                          /**< Shifter Error Register, offset: 0x14 */
  __RW uint32_t TIMSTAT;                           /**< Timer Status Register, offset: 0x18 */
       uint8_t RESERVED_0[4];
  __RW uint32_t SHIFTSIEN;                         /**< Shifter Status Interrupt Enable, offset: 0x20 */
  __RW uint32_t SHIFTEIEN;                         /**< Shifter Error Interrupt Enable, offset: 0x24 */
  __RW uint32_t TIMIEN;                            /**< Timer Interrupt Enable Register, offset: 0x28 */
       uint8_t RESERVED_1[4];
  __RW uint32_t SHIFTSDEN;                         /**< Shifter Status DMA Enable, offset: 0x30 */
       uint8_t RESERVED_2[76];
  __RW uint32_t SHIFTCTL[4];                       /**< Shifter Control N Register, array offset: 0x80, array step: 0x4 */
       uint8_t RESERVED_3[112];
  __RW uint32_t SHIFTCFG[4];                       /**< Shifter Configuration N Register, array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_4[240];
  __RW uint32_t SHIFTBUF[4];                       /**< Shifter Buffer N Register, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_5[112];
  __RW uint32_t SHIFTBUFBIS[4];                    /**< Shifter Buffer N Bit Swapped Register, array offset: 0x280, array step: 0x4 */
       uint8_t RESERVED_6[112];
  __RW uint32_t SHIFTBUFBYS[4];                    /**< Shifter Buffer N Byte Swapped Register, array offset: 0x300, array step: 0x4 */
       uint8_t RESERVED_7[112];
  __RW uint32_t SHIFTBUFBBS[4];                    /**< Shifter Buffer N Bit Byte Swapped Register, array offset: 0x380, array step: 0x4 */
       uint8_t RESERVED_8[112];
  __RW uint32_t TIMCTL[4];                         /**< Timer Control N Register, array offset: 0x400, array step: 0x4 */
       uint8_t RESERVED_9[112];
  __RW uint32_t TIMCFG[4];                         /**< Timer Configuration N Register, array offset: 0x480, array step: 0x4 */
       uint8_t RESERVED_10[112];
  __RW uint32_t TIMCMP[4];                         /**< Timer Compare N Register, array offset: 0x500, array step: 0x4 */
} MIO_Type;

//typedef struct
//{
//    __RO uint8_t RESERVED17[4];
//    __RO uint8_t RESERVED18[4];
//    __RW uint32_t CTRL;                /*!<控制寄存器*/
//    __RO uint32_t PIN;                /*!<引脚寄存器*/
//    __RW uint32_t SHIFTSTAT;                /*!<移位器状态寄存器*/
//    __RW uint32_t SHIFTERR;                /*!<移位器错误状态寄存器*/
//    __RW uint32_t TIMSTAT;                /*!<定时器状态寄存器*/
//    __RO uint8_t RESERVED0[4];
//    __RW uint32_t SHIFTSIEN;                /*!<移位器中断使能寄存器*/
//    __RW uint32_t SHIFTEIEN;                /*!<移位器错误中断使能寄存器*/
//    __RW uint32_t TIMIEN;                /*!<定时器中断使能寄存器*/
//    __RO uint8_t RESERVED1[4];
//    __RW uint32_t SHIFTSDEN;                /*!<移位器DMA使能寄存器*/
//    __RO uint8_t RESERVED2[76];
//    __RW uint32_t SHIFTCTL0;                /*!<移位器控制寄存器0*/
//    __RW uint32_t SHIFTCTL1;                /*!<移位器控制寄存器1*/
//    __RO uint8_t RESERVED3[120];
//    __RW uint32_t SHIFTCFG0;                /*!<移位器配置寄存器0*/
//    __RW uint32_t SHIFTCFG1;                /*!<移位器配置寄存器1*/
//    __RO uint8_t RESERVED4[248];
//    __RW uint32_t SHIFTBUF0;                /*!<移位器缓冲寄存器0*/
//    __RW uint32_t SHIFTBUF1;                /*!<移位器缓冲寄存器1*/
//    __RO uint8_t RESERVED5[120];
//    __RW uint32_t SHIFTBUFBIS0;                /*!<移位器缓冲位交换寄存器0*/
//    __RW uint32_t SHIFTBUFBIS1;                /*!<移位器缓冲位交换寄存器1*/
//    __RO uint8_t RESERVED6[120];
//    __RW uint32_t SHIFTBUFBYS0;                /*!<移位器缓冲字节交换寄存器0*/
//    __RW uint32_t SHIFTBUFBYS1;                /*!<移位器缓冲字节交换寄存器1*/
//    __RO uint8_t RESERVED7[120];
//    __RW uint32_t SHIFTBUFBBS0;                /*!<移位器缓冲位字节交换寄存器0*/
//    __RW uint32_t SHIFTBUFBBS1;                /*!<移位器缓冲位字节交换寄存器1*/
//    __RO uint8_t RESERVED8[120];
//    __RW uint32_t TIMCTL0;                /*!<定时器控制寄存器0*/
//    __RW uint32_t TIMCTL1;                /*!<定时器控制寄存器1*/
//    __RO uint8_t RESERVED9[120];
//    __RW uint32_t TIMCFG0;                /*!<定时器配置寄存器0*/
//    __RW uint32_t TIMCFG1;                /*!<定时器配置寄存器1*/
//    __RO uint8_t RESERVED10[120];
//    __RW uint32_t TIMCMP0;                /*!<定时器比较值寄存器0*/
//    __RW uint32_t TIMCMP1;                /*!<定时器比较值寄存器1*/
//    __RO uint8_t RESERVED11[376];
//    __RW uint32_t SHIFTBUFNBS0;                /*!<移位器缓冲半字节字节交换寄存器0*/
//    __RW uint32_t SHIFTBUFNBS1;                /*!<移位器缓冲半字节字节交换寄存器1*/
//    __RO uint8_t RESERVED12[120];
//    __RW uint32_t SHIFTBUFHWS0;                /*!<移位器缓冲半字交换寄存器0*/
//    __RW uint32_t SHIFTBUFHWS1;                /*!<移位器缓冲半字交换寄存器1*/
//    __RO uint8_t RESERVED13[120];
//    __RW uint32_t SHIFTBUFNIS0;                /*!<移位器缓冲半字节交换寄存器0*/
//    __RW uint32_t SHIFTBUFNIS1;                /*!<移位器缓冲半字节交换寄存器1*/
//    __RO uint8_t RESERVED14[120];
//    __RW uint32_t SHIFTBUFOES0;                /*!<移位器缓冲偶数奇数交换寄存器0*/
//    __RW uint32_t SHIFTBUFOES1;                /*!<移位器缓冲偶数奇数交换寄存器1*/
//    __RO uint8_t RESERVED15[120];
//    __RW uint32_t SHIFTBUFEOS0;                /*!<移位器缓冲奇数偶数交换寄存器0*/
//    __RW uint32_t SHIFTBUFEOS1;                /*!<移位器缓冲奇数偶数交换寄存器1*/
//    __RO uint8_t RESERVED16[120];
//    __RW uint32_t SHIFTBUFHBS0;                /*!<移位器缓冲半字字节交换寄存器0*/
//    __RW uint32_t SHIFTBUFHBS1;                /*!<移位器缓冲半字字节交换寄存器1*/
//} Legacy_MIO_TypeDef;

//----------------------------------------------------
//Regsiter Structure Definition for Module Crosslink
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CROSS_LINK0_SEL0;                /*!<*/
    __RW uint32_t CROSS_LINK0_SEL1;                /*!<*/
    __RW uint32_t CROSS_LINK0_SEL2;                /*!<*/
    __RW uint32_t CROSS_LINK0_SEL3;                /*!<*/
    __RW uint32_t CROSS_LINK0_SEL4;                /*!<*/
    __RW uint32_t CROSS_LINK0_CTR0;                /*!<*/
    __RW uint32_t CROSS_LINK1_SEL0;                /*!<*/
    __RW uint32_t CROSS_LINK1_SEL1;                /*!<*/
    __RW uint32_t LOGIC_UNION_SEL0;                /*!<*/
    __RW uint32_t LOGIC_UNION_SEL1;                /*!<*/
    __RW uint32_t SOFT_SYNC;                /*!<该地址发起写操作，产生一次触发，可配置与Cross Link 输入源*/
}CROSSLINK_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module RCC
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CR;                /*!<时钟控制寄存器*/
    __RW uint32_t CFGR;                /*!<*/
    __RW uint32_t CIR;                /*!<时钟中断寄存器*/
    __RW uint32_t APB2RSTR;                /*!<APB2外设复位*/
    __RW uint32_t APB1RSTR;                /*!<APB1外设复位*/
    __RW uint32_t AHBENR;                /*!<AHB外设时钟使能寄存器*/
    __RW uint32_t APB2ENR;                /*!<APB2外设时钟使能*/
    __RW uint32_t APB1ENR;                /*!<APB1外设时钟使能*/
    __RW uint32_t BDCR;                /*!<AON域控制寄存器中的位在复位后处于写保护状态，只有在电源控制寄存器(PWR_CR)中的DBP位置’1’后才能对这些位进行改动。这些位只能由AON域和上电复位清除*/
    __RW uint32_t CSR;                /*!<控制/状态寄存器*/
}RCC_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module CRC32
//----------------------------------------------------
typedef struct
{
    __RW uint32_t DR;                /*!<数据寄存器*/
    __RW uint32_t IDR;                /*!<独立数据寄存器*/
    __RW uint32_t CR;                /*!<控制寄存器*/
}CRC32_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module MACL
//----------------------------------------------------
typedef struct
{
    __RW uint32_t A0;                /*!<操作数a0*/
    __RW uint32_t A1;                /*!<操作数a1*/
    __RW uint32_t B0;                /*!<操作数b0*/
    __RW uint32_t B1;                /*!<操作数b1*/
    __RW uint32_t CFG;                /*!<配置状态寄存器CFS->CFG*/ 
    __WO uint32_t CLR;                /*!<状态数据清除操作*/
}MACL_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module DMA_CONTROL
//----------------------------------------------------
typedef struct
{
    __RW uint32_t DMA_CR;                /*!<控制寄存器*/
    __RO uint32_t DMA_ES;                /*!<错误状态寄存器*/
    __RO uint8_t RESERVED0[4];
    __RW uint32_t DMA_ERQ;                /*!<请求使能寄存器*/
    __RO uint8_t RESERVED1[4];
    __RW uint32_t DMA_EEI;                /*!<错误中断使能寄存器*/
    __WO uint8_t DMA_CEEI;                /*!<清除错误中断使能寄存器*/
    __WO uint8_t DMA_SEEI;                /*!<设置错误中断使能寄存器*/
    __WO uint8_t DMA_CERQ;                /*!<清除请求使能寄存器*/
    __WO uint8_t DMA_SERQ;                /*!<设置请求使能寄存器*/
    __WO uint8_t DMA_CDNE;                /*!<清除完成状态标志位*/
    __WO uint8_t DMA_SSRT;                /*!<设置启动寄存器*/
    __WO uint8_t DMA_CERR;                /*!<清除错误寄存器*/
    __WO uint8_t DMA_CINT;                /*!<清除中断请求寄存器*/
    __RO uint8_t RESERVED2[4];
    __RW uint32_t DMA_INT;                /*!<中断请求寄存器*/
    __RO uint8_t RESERVED3[4];
    __RW uint32_t DMA_ERR;                /*!<DMA错误寄存器*/
    __RO uint8_t RESERVED4[4];
    __RO uint32_t DMA_HRS;                /*!<硬件请求状态寄存器*/
    __RO uint8_t RESERVED5[12];
    __RW uint32_t DMA_EARS;                /*!<异步请求使能寄存器*/
    __RO uint8_t RESERVED6[184];
    __RO uint8_t DMA_DCHPRI0;                /*!<*/
    __RO uint8_t DMA_DCHPRI1;                /*!<*/
    __RO uint8_t DMA_DCHPRI2;                /*!<*/
    __RO uint8_t DMA_DCHPRI3;                /*!<*/
}DMA_CONTROL_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module DMA_DES_n
//----------------------------------------------------
typedef struct
{
    __RW uint32_t DMA_DESN_SADDR;                /*!<*/
    __RW int16_t DMA_DESN_SOFF;                /*!<*/
    __RW uint16_t DMA_DESN_ATTR;                /*!<*/
    __RW uint32_t DMA_DESN_NBYTES_MLNO;                /*!<*/
    __RW int32_t DMA_DESN_SLAST;                /*!<*/
    __RW uint32_t DMA_DESN_DADDR;                /*!<*/
    __RW int16_t DMA_DESN_DOFF;                /*!<*/
    __RW uint16_t DMA_DESN_CITER_ELINKYES;                /*!<*/
    __RW int32_t DMA_DESN_DLASTSGA;                /*!<*/
    __RW uint16_t DMA_DESN_CSR;                /*!<*/
    __RW uint16_t DMA_DESN_BITER_ELINKYES;                /*!<*/
}DMA_DES_N_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module DMAMUX
//----------------------------------------------------
typedef struct
{
    __RW uint8_t CHCFG0;                /*!<DMAMUX通道0配置*/
    __RW uint8_t CHCFG1;                /*!<DMAMUX通道1配置*/
    __RW uint8_t CHCFG2;                /*!<DMAMUX通道2配置*/
    __RW uint8_t CHCFG3;                /*!<DMAMUX通道3配置*/
}DMAMUX_TypeDef;
//----------------------------------------------------
//Regsiter Structure Definition for Module BTIM
//----------------------------------------------------
typedef struct
{
    __RW uint32_t MCR;                /*!<该寄存器使能或禁用PIT定时器时钟，并在PIT进入触发模式时控制定时器*/
    __RO uint8_t RESERVED0[252];
    __RW uint32_t LDVAL_0;                /*!<这些寄存器选择定时器中断的超时周期*/
    __RO uint32_t CVAL_0;                /*!<这些寄存器指示当前定时器位置*/
    __RW uint32_t TCTRL_0;                /*!<这些寄存器包含每个定时器的控制位*/
    __RW uint32_t TFLG_0;                /*!<这些寄存器保存PIT中断标志。*/
    __RW uint32_t LDVAL_1;                /*!<这些寄存器选择定时器中断的超时周期*/
    __RO uint32_t CVAL_1;                /*!<这些寄存器指示当前定时器位置*/
    __RW uint32_t TCTRL_1;                /*!<这些寄存器包含每个定时器的控制位*/
    __RW uint32_t TFLG_1;                /*!<这些寄存器保存PIT中断标志。*/
}BTIM_TypeDef;



#define TIM2_BASE               ((uint32_t)0x40000000)    /*多功能定时器2*/
#define LPTIM1_BASE               ((uint32_t)0x40000c00)    /*低功耗定时器1*/
#define LPTIM2_BASE               ((uint32_t)0x40000c20)    /*低功耗定时器2*/
#define RTC_BASE               ((uint32_t)0x40002800)    /*实时时钟模块*/
#define IWDG_BASE               ((uint32_t)0x40003000)    /*独立看门狗*/
#define SPI1_BASE               ((uint32_t)0x40003800)    /*串行外设接口1*/
#define FLASH_BASE               ((uint32_t)0x40003c00)    /*闪存控制器*/
#define UART1_BASE               ((uint32_t)0x40004800)    /*通用异步收发器1*/
#define I2C_BASE               ((uint32_t)0x40005400)    /*内部集成电路总线接口*/
#define AON_BASE               ((uint32_t)0x40006c00)    /*AON控制单元*/
#define PWR_BASE               ((uint32_t)0x40007000)    /*电源管理单元*/
#define EXTI_BASE               ((uint32_t)0x40010400)    /*中断/事件控制器*/
#define GPIO0_BASE               ((uint32_t)0x40010800)    /*快速通用输入输出0*/
#define GPIO1_BASE               ((uint32_t)0x40010840)    /*快速通用输入输出1*/
#define GPIO2_BASE               ((uint32_t)0x40010880)    /*快速通用输入输出2*/
#define INT_SEL_ADDR             ((uint32_t)0x4001093C)    /*GPIO INT_SEL寄存器地址*/

#define AFE_BASE               ((uint32_t)0x40012800)    /*模拟前端模块*/
#define DAC_BASE               ((uint32_t)0x40012850)    /*数模转换控制器*/
#define ADC_SUBSYS_USER_BASE               ((uint32_t)0x40012880)    /*模数转换控制器*/
#define TIM1_BASE               ((uint32_t)0x40012c00)    /*多功能定时器1*/
#define SPI0_BASE               ((uint32_t)0x40013000)    /*串行外设接口0*/
#define UART0_BASE               ((uint32_t)0x40013800)    /*通用异步收发器0*/
#define MIO_BASE               ((uint32_t)0x40018000)    /*多功能IO接口*/
#define CROSSLINK_BASE               ((uint32_t)0x40019000)    /*全芯片互联单元*/
#define RCC_BASE               ((uint32_t)0x40021000)    /*时钟复位控制器*/
#define CRC32_BASE               ((uint32_t)0x40023000)    /*CRC32加速单元*/
#define MACL_BASE               ((uint32_t)0x40024000)    /*数学计算加速单元*/
#define DMA_CONTROL_BASE               ((uint32_t)0x40028000)    /*增强型DMA控制器*/
#define DMA_DES_N_BASE               ((uint32_t)0x40029000)    /*增强型DMA描述符*/
#define DMAMUX_BASE               ((uint32_t)0x4002a000)    /*增强型DMAMUX*/
#define BTIM_BASE               ((uint32_t)0x4002a400)    /*基础定时器*/

#define pTIM2                 ((TIM_TypeDef *)TIM2_BASE)
#define pLPTIM1               ((LPTIM_TypeDef *)LPTIM1_BASE)
#define pLPTIM2               ((LPTIM_TypeDef *)LPTIM2_BASE)
#define pRTC               ((RTC_TypeDef *)RTC_BASE)
#define pIWDG               ((IWDG_TypeDef *)IWDG_BASE)
#define pSPI1               ((SPI_TypeDef *)SPI1_BASE)
#define pFLASH               ((FLASH_TypeDef *)FLASH_BASE)
#define pUART1               ((UART_TypeDef *)UART1_BASE)
#define pI2C               ((I2C_TypeDef *)I2C_BASE)
#define pAON               ((AON_TypeDef *)AON_BASE)
#define pPWR               ((PWR_TypeDef *)PWR_BASE)
#define pEXTI               ((EXTI_TypeDef *)EXTI_BASE)
#define pGPIO0               ((GPIO_TypeDef *)GPIO0_BASE)
#define pGPIO1               ((GPIO_TypeDef *)GPIO1_BASE)
#define pGPIO2               ((GPIO_TypeDef *)GPIO2_BASE)
#define pINT_SEL             ((GPIO_INT_SEL_TypeDef *)INT_SEL_ADDR)
#define pAFE               ((AFE_TypeDef *)AFE_BASE)
#define pDAC               ((DAC_TypeDef *)DAC_BASE)
#define pADC               ((ADC_SUBSYS_USER_TypeDef *)ADC_SUBSYS_USER_BASE)
#define pTIM1               ((TIM_TypeDef *)TIM1_BASE)
#define pSPI0               ((SPI_TypeDef *)SPI0_BASE)
#define pUART0               ((UART_TypeDef *)UART0_BASE)
#define pMIO               ((MIO_TypeDef *)MIO_BASE)
#define pCROSSLINK               ((CROSSLINK_TypeDef *)CROSSLINK_BASE)
#define pRCC               ((RCC_TypeDef *)RCC_BASE)
#define pCRC32               ((CRC32_TypeDef *)CRC32_BASE)
#define pMACL               ((MACL_TypeDef *)MACL_BASE)
#define pDMA_CONTROL            ((DMA_CONTROL_TypeDef *)DMA_CONTROL_BASE)
#define pDMA_DES_N              ((DMA_DES_N_TypeDef *)DMA_DES_N_BASE)
#define pDMAMUX                 ((DMAMUX_TypeDef *)DMAMUX_BASE)
#define pBTIM                   ((BTIM_TypeDef *)BTIM_BASE)


//----------------------------------------------------
//Regsiter Structure Definition for Module OWI
//----------------------------------------------------
typedef struct
{
    __RW uint32_t CTRL;                /*!<*/
    __RW uint32_t QUIT;                /*!<*/
    __RW uint32_t CFG;                /*!<*/
    __RW uint32_t STATUS;                /*!<*/
}OWI_TypeDef;

#define OWI_BASE               ((uint32_t)0x40012840)    /*单线通信外设*/
#define pOWI               ((OWI_TypeDef *)OWI_BASE)

/******************************************************************************/
/*                    Reset Value for Module TIMER                            */
/******************************************************************************/

#define TIMER_TIMX_CR1_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_CR2_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_SMCR_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_DIER_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_SR_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_EGR_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_CCMR1_OP_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_CCMR1_IC_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_CCER_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_CNT_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_PSC_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_ARR_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_CCR1_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_CCR2_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_DCR_RESET             ((uint32_t)0x0)
#define TIMER_TIMX_DMAR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module LPTIM                            */
/******************************************************************************/

#define LPTIM_CSR_RESET             ((uint32_t)0x0)
#define LPTIM_PSR_RESET             ((uint32_t)0x0)
#define LPTIM_CMR_RESET             ((uint32_t)0x0)
#define LPTIM_CNR_RESET             ((uint32_t)0x0)
#define LPTIM_ARR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module RTC                            */
/******************************************************************************/

#define RTC_CRH_RESET             ((uint32_t)0x0)
#define RTC_CRL_RESET             ((uint32_t)0x0)
#define RTC_PRLH_RESET             ((uint32_t)0x0)
#define RTC_PRLL_RESET             ((uint32_t)0x8000)
#define RTC_DIVH_RESET             ((uint32_t)0x0)
#define RTC_DIVL_RESET             ((uint32_t)0x0)
#define RTC_CNTH_RESET             ((uint32_t)0x0)
#define RTC_CNTL_RESET             ((uint32_t)0x0)
#define RTC_ALRH_RESET             ((uint32_t)0xffff)
#define RTC_ALRL_RESET             ((uint32_t)0xffff)

/******************************************************************************/
/*                    Reset Value for Module IWDG                            */
/******************************************************************************/

#define IWDG_KR_RESET             ((uint32_t)0x0)
#define IWDG_PR_RESET             ((uint32_t)0x7)
#define IWDG_RLR_RESET             ((uint32_t)0x9c0)
#define IWDG_SR_RESET             ((uint32_t)0x0)
#define IWDG_EN_RESET             ((uint32_t)0x1)
#define IWDG_LOCK_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module SPI                            */
/******************************************************************************/

#define SPI_CR1_RESET             ((uint32_t)0x0)
#define SPI_CR2_RESET             ((uint32_t)0x0)
#define SPI_SR_RESET             ((uint32_t)0x0)
#define SPI_DR_RESET             ((uint32_t)0x0)
#define SPI_CRCPR_RESET             ((uint32_t)0x0)
#define SPI_RXCRCR_RESET             ((uint32_t)0x0)
#define SPI_TXCRCR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module FLASH                            */
/******************************************************************************/

#define FLASH_CTRL_RESET             ((uint32_t)0x180)
#define FLASH_CMD_RESET             ((uint32_t)0x0)
#define FLASH_PAGE_ADDR0_RESET             ((uint32_t)0x0)
#define FLASH_STAT_RESET             ((uint32_t)0x104f)
#define FLASH_USER_WR_PROT_RESET             ((uint32_t)0xffffffff)
#define FLASH_USERKEY_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module UART                            */
/******************************************************************************/

#define UART_RBR_THR_DLL_RESET             ((uint32_t)0x0)
#define UART_IER_DLH_RESET             ((uint32_t)0x0)
#define UART_IIR_RESET             ((uint32_t)0x0)
#define UART_LCR_RESET             ((uint32_t)0x0)
#define UART_MCR_RESET             ((uint32_t)0x0)
#define UART_LSR_RESET             ((uint32_t)0x0)
#define UART_MSR_RESET             ((uint32_t)0x0)
#define UART_SCR_RESET             ((uint32_t)0x0)
#define UART_FAR_RESET             ((uint32_t)0x0)
#define UART_USR_RESET             ((uint32_t)0x0)
#define UART_HTX_RESET             ((uint32_t)0x0)
#define UART_DMASA_RESET             ((uint32_t)0x0)
#define UART_DLF_RESET             ((uint32_t)0x0)
#define UART_RAR_RESET             ((uint32_t)0x0)
#define UART_TAR_RESET             ((uint32_t)0x0)
#define UART_LCR_EXT_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module I2C                            */
/******************************************************************************/

#define I2C_CR1_RESET             ((uint32_t)0x0)
#define I2C_CR2_RESET             ((uint32_t)0x0)
#define I2C_OAR1_RESET             ((uint32_t)0x0)
#define I2C_OAR2_RESET             ((uint32_t)0x0)
#define I2C_DR_RESET             ((uint32_t)0x0)
#define I2C_SR1_RESET             ((uint32_t)0x0)
#define I2C_SR2_RESET             ((uint32_t)0x0)
#define I2C_CCR_RESET             ((uint32_t)0x0)
#define I2C_TRISE_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module AON                            */
/******************************************************************************/

#define AON_BKP_RTCCR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module PWR                            */
/******************************************************************************/

#define PWR_CR_RESET             ((uint32_t)0x0)
#define PWR_CSR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module EXTI                            */
/******************************************************************************/

#define EXTI_IMR_RESET             ((uint32_t)0x0)
#define EXTI_EMR_RESET             ((uint32_t)0x0)
#define EXTI_RTSR_RESET             ((uint32_t)0x0)
#define EXTI_FTSR_RESET             ((uint32_t)0x0)
#define EXTI_SWIER_RESET             ((uint32_t)0x0)
#define EXTI_PR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module GPIO                            */
/******************************************************************************/

#define GPIO_CON0_RESET             ((uint32_t)0x0)
#define GPIO_OE_RESET             ((uint32_t)0x0)
#define GPIO_PUE_RESET             ((uint32_t)0x0)
#define GPIO_PDE_RESET             ((uint32_t)0x0)
#define GPIO_OD_RESET             ((uint32_t)0x0)
#define GPIO_IE_RESET             ((uint32_t)0x0)
#define GPIO_SMT_RESET             ((uint32_t)0x0)
#define GPIO_SL_RESET             ((uint32_t)0x0)
#define GPIO_DR_RESET             ((uint32_t)0x0)
#define GPIO_DATA_IN_RESET             ((uint32_t)0x0)
#define GPIO_DATA_OUT_RESET             ((uint32_t)0x0)
#define GPIO_OSET_RESET             ((uint32_t)0x0)
#define GPIO_OCLR_RESET             ((uint32_t)0x0)
#define GPIO_OTGL_RESET             ((uint32_t)0x0)
#define GPIO_INT_SEL_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module AFE                            */
/******************************************************************************/

#define AFE_NOP_RESET             ((uint32_t)0x0)
#define AFE_PAGE_RESET             ((uint32_t)0x400128)
#define AFE_STATUS_RESET             ((uint32_t)0x0)
#define AFE_CFG_RESET             ((uint32_t)0x0)
#define AFE_SPI_CFG_RESET             ((uint32_t)0x0)
#define AFE_PWM_CTRL_RESET             ((uint32_t)0x2c)
#define AFE_REF_CTRL_RESET             ((uint32_t)0x0)
#define AFE_IEXC_RANGE_RESET             ((uint32_t)0x0)
#define AFE_IEXC_CTRL_RESET             ((uint32_t)0x0)
#define AFE_USERKEY_RESET             ((uint32_t)0x0)

/******************************************************************************/

/******************************************************************************/
/*                    Reset Value for Module DAC                            */
/******************************************************************************/

#define DAC_CTRL_RESET             ((uint32_t)0x0)
#define DAC_DATA_RESET             ((uint32_t)0x0)
#define DAC_CLAMPH_RESET             ((uint32_t)0xffff)
#define DAC_CLAMPL_RESET             ((uint32_t)0x0)
#define DAC_AOUT_REG0_RESET             ((uint32_t)0x0)
#define DAC_AOUT_REG1_RESET             ((uint32_t)0x1000)

/******************************************************************************/
/*                    Reset Value for Module ADC_SUBSYS_USER                            */
/******************************************************************************/

#define ADC_SUBSYS_USER_ERROR_STATUS_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_ERROR_EN_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_ADC_DRDY_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_DMA_MODE_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_ADC_STATUS_0_RESET             ((uint32_t)0x400)
#define ADC_SUBSYS_USER_ADC_DATA_0_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_0_RESET             ((uint32_t)0x4)
#define ADC_SUBSYS_USER_ADC_CONTROL_0_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_CHANNEL_CFG_0_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_CONFIGURATION_0_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_FILTER_0_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_OFFSET_0_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_GAIN_0_RESET             ((uint32_t)0x400000)
#define ADC_SUBSYS_USER_ADC_0_HI_COMPARATOR_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_ADC_0_LO_COMPARATOR_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_ADC_STATUS_1_RESET             ((uint32_t)0x400)
#define ADC_SUBSYS_USER_ADC_DATA_1_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_1_RESET             ((uint32_t)0x4)
#define ADC_SUBSYS_USER_ADC_CONTROL_1_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_CHANNEL_CFG_1_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_CONFIGURATION_1_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_FILTER_1_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_OFFSET_1_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_GAIN_1_RESET             ((uint32_t)0x400000)
#define ADC_SUBSYS_USER_ADC_1_HI_COMPARATOR_RESET             ((uint32_t)0x0)
#define ADC_SUBSYS_USER_ADC_1_LO_COMPARATOR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module MIO                            */
/******************************************************************************/
#define MIO_CTRL_RESET             ((uint32_t)0x0)
#define MIO_PIN_RESET             ((uint32_t)0x0)
#define MIO_SHIFTSTAT_RESET             ((uint32_t)0x0)
#define MIO_SHIFTERR_RESET             ((uint32_t)0x0)
#define MIO_TIMSTAT_RESET             ((uint32_t)0x0)
#define MIO_SHIFTSIEN_RESET             ((uint32_t)0x0)
#define MIO_SHIFTEIEN_RESET             ((uint32_t)0x0)
#define MIO_TIMIEN_RESET             ((uint32_t)0x0)
#define MIO_SHIFTSDEN_RESET             ((uint32_t)0x0)
#define MIO_SHIFTCTL0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTCTL1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTCFG0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTCFG1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUF0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUF1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFBIS0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFBIS1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFBYS0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFBYS1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFBBS0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFBBS1_RESET             ((uint32_t)0x0)
#define MIO_TIMCTL0_RESET             ((uint32_t)0x0)
#define MIO_TIMCTL1_RESET             ((uint32_t)0x0)
#define MIO_TIMCFG0_RESET             ((uint32_t)0x0)
#define MIO_TIMCFG1_RESET             ((uint32_t)0x0)
#define MIO_TIMCMP0_RESET             ((uint32_t)0x0)
#define MIO_TIMCMP1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFNBS0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFNBS1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFHWS0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFHWS1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFNIS0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFNIS1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFOES0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFOES1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFEOS0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFEOS1_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFHBS0_RESET             ((uint32_t)0x0)
#define MIO_SHIFTBUFHBS1_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module CROSSLINK                            */
/******************************************************************************/

#define CROSSLINK_CROSS_LINK0_SEL0_RESET             ((uint32_t)0x0)
#define CROSSLINK_CROSS_LINK0_SEL1_RESET             ((uint32_t)0x0)
#define CROSSLINK_CROSS_LINK0_SEL2_RESET             ((uint32_t)0x0)
#define CROSSLINK_CROSS_LINK0_SEL3_RESET             ((uint32_t)0x0)
#define CROSSLINK_CROSS_LINK0_SEL4_RESET             ((uint32_t)0x0)
#define CROSSLINK_CROSS_LINK0_CTR0_RESET             ((uint32_t)0x0)
#define CROSSLINK_CROSS_LINK1_SEL0_RESET             ((uint32_t)0x0)
#define CROSSLINK_CROSS_LINK1_SEL1_RESET             ((uint32_t)0x0)
#define CROSSLINK_LOGIC_UNION_SEL0_RESET             ((uint32_t)0x0)
#define CROSSLINK_LOGIC_UNION_SEL1_RESET             ((uint32_t)0x0)
#define CROSSLINK_SOFT_SYNC_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module RCC                            */
/******************************************************************************/

#define RCC_CR_RESET             ((uint32_t)0x1)
#define RCC_CFGR_RESET             ((uint32_t)0x40b0)
#define RCC_CIR_RESET             ((uint32_t)0x0)
#define RCC_APB2RSTR_RESET             ((uint32_t)0x0)
#define RCC_APB1RSTR_RESET             ((uint32_t)0x0)
#define RCC_AHBENR_RESET             ((uint32_t)0x6)
#define RCC_APB2ENR_RESET             ((uint32_t)0x10000)
#define RCC_APB1ENR_RESET             ((uint32_t)0x0)
#define RCC_BDCR_RESET             ((uint32_t)0x0)
#define RCC_CSR_RESET             ((uint32_t)0xc000002)

/******************************************************************************/
/*                    Reset Value for Module CRC3                            */
/******************************************************************************/

#define CRC32_DR_RESET             ((uint32_t)0xffffffff)
#define CRC32_IDR_RESET             ((uint32_t)0x0)
#define CRC32_CR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module MACL                            */
/******************************************************************************/

#define MACL_A0_RESET             ((uint32_t)0x0)
#define MACL_A1_RESET             ((uint32_t)0x0)
#define MACL_B0_RESET             ((uint32_t)0x0)
#define MACL_B1_RESET             ((uint32_t)0x0)
#define MACL_CFS_RESET             ((uint32_t)0x0)
#define MACL_CLR_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module DMA_CONTROL                            */
/******************************************************************************/

#define DMA_CONTROL_DMA_CR_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_ES_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_ERQ_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_EEI_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_CEEI_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_SEEI_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_CERQ_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_SERQ_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_CDNE_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_SSRT_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_CERR_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_CINT_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_INT_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_ERR_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_HRS_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_EARS_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_DCHPRI0_RESET             ((uint32_t)0x0)
#define DMA_CONTROL_DMA_DCHPRI1_RESET             ((uint32_t)0x1)
#define DMA_CONTROL_DMA_DCHPRI2_RESET             ((uint32_t)0x2)
#define DMA_CONTROL_DMA_DCHPRI3_RESET             ((uint32_t)0x3)

/******************************************************************************/
/*                    Reset Value for Module DMA_DES_N                            */
/******************************************************************************/

#define DMA_DES_N_DMA_DESN_SADDR_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_SOFF_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_ATTR_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_NBYTES_MLNO_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_NBYTES_MLOFFNO_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_NBYTES_MLOFFYES_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_SLAST_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_DADDR_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_DOFF_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_CITER_ELINKYES_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_CITER_ELINKNO_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_DLASTSGA_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_CSR_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_BITER_ELINKYES_RESET             ((uint32_t)0x0)
#define DMA_DES_N_DMA_DESN_BITER_ELINKNO_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module DMAMUX                            */
/******************************************************************************/

#define DMAMUX_CHCFG0_RESET             ((uint32_t)0x0)
#define DMAMUX_CHCFG1_RESET             ((uint32_t)0x0)
#define DMAMUX_CHCFG2_RESET             ((uint32_t)0x0)
#define DMAMUX_CHCFG3_RESET             ((uint32_t)0x0)

/******************************************************************************/
/*                    Reset Value for Module BTIM                            */
/******************************************************************************/

#define BTIM_MCR_RESET             ((uint32_t)0x2)
#define BTIM_LDVAL_0_RESET             ((uint32_t)0x0)
#define BTIM_CVAL_0_RESET             ((uint32_t)0x0)
#define BTIM_TCTRL_0_RESET             ((uint32_t)0x0)
#define BTIM_TFLG_0_RESET             ((uint32_t)0x0)
#define BTIM_LDVAL_1_RESET             ((uint32_t)0x0)
#define BTIM_CVAL_1_RESET             ((uint32_t)0x0)
#define BTIM_TCTRL_1_RESET             ((uint32_t)0x0)
#define BTIM_TFLG_1_RESET             ((uint32_t)0x0)


/******************************************************************************/
/*                    TIMER                         */
/******************************************************************************/


/******************  Bit Definition for Register TIMX_CR1  *********************/
#define TIMER_TIMX_CR1_CEN_Msk             ((uint32_t)0x1)   /* bit mask, 使能计数器，注：在软件设置了CEN位后，外部时钟、门控模式和编码器模式才能工作。触发模式可以自动地通过硬件设置CEN位。
在单脉冲模式下，当发生更新事件时，CEN被自动清除。
*/
#define TIMER_TIMX_CR1_CEN_Pos             ((uint32_t)0)   /*bit position, 使能计数器，注：在软件设置了CEN位后，外部时钟、门控模式和编码器模式才能工作。触发模式可以自动地通过硬件设置CEN位。
在单脉冲模式下，当发生更新事件时，CEN被自动清除。
*/
#define TIMER_TIMX_CR1_UDIS_Msk             ((uint32_t)0x2)   /* bit mask, 禁止更新 (Update disable)
软件通过该位允许/禁止UEV事件的产生
*/
#define TIMER_TIMX_CR1_UDIS_Pos             ((uint32_t)1)   /*bit position, 禁止更新 (Update disable)
软件通过该位允许/禁止UEV事件的产生
*/
#define TIMER_TIMX_CR1_URS_Msk             ((uint32_t)0x4)   /* bit mask, 更新请求源 (Update request source)
软件通过该位选择UEV事件的源
*/
#define TIMER_TIMX_CR1_URS_Pos             ((uint32_t)2)   /*bit position, 更新请求源 (Update request source)
软件通过该位选择UEV事件的源
*/
#define TIMER_TIMX_CR1_OPM_Msk             ((uint32_t)0x8)   /* bit mask, 单脉冲模式 (One pulse mode) */
#define TIMER_TIMX_CR1_OPM_Pos             ((uint32_t)3)   /*bit position, 单脉冲模式 (One pulse mode) */
#define TIMER_TIMX_CR1_DIR_Msk             ((uint32_t)0x10)   /* bit mask, 方向 (Direction) ，注：当计数器配置为中央对齐模式或编码器模式时，该位为只读*/
#define TIMER_TIMX_CR1_DIR_Pos             ((uint32_t)4)   /*bit position, 方向 (Direction) ，注：当计数器配置为中央对齐模式或编码器模式时，该位为只读*/
#define TIMER_TIMX_CR1_CMS_Msk             ((uint32_t)0x60)   /* bit mask, 选择中央对齐模式，注：在计数器开启时(CEN=1)，不允许从边沿对齐模式转换到中央对齐模式。*/
#define TIMER_TIMX_CR1_CMS_Pos             ((uint32_t)5)   /*bit position, 选择中央对齐模式，注：在计数器开启时(CEN=1)，不允许从边沿对齐模式转换到中央对齐模式。*/
#define TIMER_TIMX_CR1_ARPE_Msk             ((uint32_t)0x80)   /* bit mask, 自动重装载预装载允许位 (Auto-reload preload enable)*/
#define TIMER_TIMX_CR1_ARPE_Pos             ((uint32_t)7)   /*bit position, 自动重装载预装载允许位 (Auto-reload preload enable)*/
#define TIMER_TIMX_CR1_CKD_Msk             ((uint32_t)0x300)   /* bit mask, 时钟分频因子 (Clock division)
定义在定时器时钟(CK_INT)频率与数字滤波器(ETR，TIx)使用的采样频率之间的分频比例。
*/
#define TIMER_TIMX_CR1_CKD_Pos             ((uint32_t)8)   /*bit position, 时钟分频因子 (Clock division)
定义在定时器时钟(CK_INT)频率与数字滤波器(ETR，TIx)使用的采样频率之间的分频比例。
*/

/******************  Bit Definition for Register TIMX_CR2  *********************/
#define TIMER_TIMX_CR2_CCDS_Msk             ((uint32_t)0x8)   /* bit mask, 捕获/比较的DMA选择*/
#define TIMER_TIMX_CR2_CCDS_Pos             ((uint32_t)3)   /*bit position, 捕获/比较的DMA选择*/
#define TIMER_TIMX_CR2_MMS_Msk             ((uint32_t)0x70)   /* bit mask, 主模式选择 (Master mode selection)
这3位用于选择在主模式下送到从定时器的同步信息(TRGO)
*/
#define TIMER_TIMX_CR2_MMS_Pos             ((uint32_t)4)   /*bit position, 主模式选择 (Master mode selection)
这3位用于选择在主模式下送到从定时器的同步信息(TRGO)
*/
#define TIMER_TIMX_CR2_TI1S_Msk             ((uint32_t)0x80)   /* bit mask, TI1 选 择*/
#define TIMER_TIMX_CR2_TI1S_Pos             ((uint32_t)7)   /*bit position, TI1 选 择*/

/******************  Bit Definition for Register TIMX_SMCR  *********************/
#define TIMER_TIMX_SMCR_SMS_Msk             ((uint32_t)0x7)   /* bit mask, 从模式选择 (Slave mode selection)
当选择了外部信号，触发信号(TRGI)的有效边沿与选中的外部输入极性相关(见输入控制寄存器和控制寄存器的说明)
,注：如果TI1F_EN被选为触发输入(TS=100)时，不要使用门控模式。这是因为，TI1F_ED在每次TI1F变化时输出一个脉冲，然而门控模式是要检查触发输入的电平。
*/
#define TIMER_TIMX_SMCR_SMS_Pos             ((uint32_t)0)   /*bit position, 从模式选择 (Slave mode selection)
当选择了外部信号，触发信号(TRGI)的有效边沿与选中的外部输入极性相关(见输入控制寄存器和控制寄存器的说明)
,注：如果TI1F_EN被选为触发输入(TS=100)时，不要使用门控模式。这是因为，TI1F_ED在每次TI1F变化时输出一个脉冲，然而门控模式是要检查触发输入的电平。
*/
#define TIMER_TIMX_SMCR_TS_Msk             ((uint32_t)0x70)   /* bit mask, 触发选择 (Trigger selection)
这3位选择用于同步计数器的触发输入。
注：这些位只能在未用到(如SMS=000)时被改变，以避免在改变时产生错误的边沿检测。
*/
#define TIMER_TIMX_SMCR_TS_Pos             ((uint32_t)4)   /*bit position, 触发选择 (Trigger selection)
这3位选择用于同步计数器的触发输入。
注：这些位只能在未用到(如SMS=000)时被改变，以避免在改变时产生错误的边沿检测。
*/
#define TIMER_TIMX_SMCR_MSM_Msk             ((uint32_t)0x80)   /* bit mask, 主/从模式 (Master/slave mode)*/
#define TIMER_TIMX_SMCR_MSM_Pos             ((uint32_t)7)   /*bit position, 主/从模式 (Master/slave mode)*/
#define TIMER_TIMX_SMCR_ETF_Msk             ((uint32_t)0xf00)   /* bit mask, 外部触发滤波 (External trigger filter)
这些位定义了对ETRP信号采样的频率和对ETRP数字滤波的带宽。实际上，数字滤波器是一个事件计数器，它记录到N个事件后会产生一个输出的跳变
*/
#define TIMER_TIMX_SMCR_ETF_Pos             ((uint32_t)8)   /*bit position, 外部触发滤波 (External trigger filter)
这些位定义了对ETRP信号采样的频率和对ETRP数字滤波的带宽。实际上，数字滤波器是一个事件计数器，它记录到N个事件后会产生一个输出的跳变
*/
#define TIMER_TIMX_SMCR_ETPS_Msk             ((uint32_t)0x3000)   /* bit mask, 外部触发预分频 (External trigger prescaler)
外部触发信号ETRP的频率必须最多是CK_INT频率的1/4。当输入较快的外部时钟时，可以使用预分频降低ETRP的频率。
*/
#define TIMER_TIMX_SMCR_ETPS_Pos             ((uint32_t)12)   /*bit position, 外部触发预分频 (External trigger prescaler)
外部触发信号ETRP的频率必须最多是CK_INT频率的1/4。当输入较快的外部时钟时，可以使用预分频降低ETRP的频率。
*/
#define TIMER_TIMX_SMCR_ECE_Msk             ((uint32_t)0x4000)   /* bit mask, 外部时钟使能位 (External clock enable) 该位启用外部时钟模式2 ,注1：设置ECE位与选择外部时钟模式1并将TRGI连到ETRF(SMS=111和TS=111)具有相同功效。
注2：下述从模式可以与外部时钟模式2同时使用：复位模式、门控模式和触发模式；但是，这时TRGI不能连到ETRF(TS位不能是’111’)。
注3：外部时钟模式1和外部时钟模式2同时被使能时，外部时钟的输入是ETRF。
*/
#define TIMER_TIMX_SMCR_ECE_Pos             ((uint32_t)14)   /*bit position, 外部时钟使能位 (External clock enable) 该位启用外部时钟模式2 ,注1：设置ECE位与选择外部时钟模式1并将TRGI连到ETRF(SMS=111和TS=111)具有相同功效。
注2：下述从模式可以与外部时钟模式2同时使用：复位模式、门控模式和触发模式；但是，这时TRGI不能连到ETRF(TS位不能是’111’)。
注3：外部时钟模式1和外部时钟模式2同时被使能时，外部时钟的输入是ETRF。
*/
#define TIMER_TIMX_SMCR_ETP_Msk             ((uint32_t)0x8000)   /* bit mask, 外部触发极性 (External trigger polarity)
该位选择是用ETR还是ETR的反相来作为触发操作
*/
#define TIMER_TIMX_SMCR_ETP_Pos             ((uint32_t)15)   /*bit position, 外部触发极性 (External trigger polarity)
该位选择是用ETR还是ETR的反相来作为触发操作
*/

/******************  Bit Definition for Register TIMX_DIER  *********************/
#define TIMER_TIMX_DIER_UIE_Msk             ((uint32_t)0x1)   /* bit mask, 允许更新中断 (Update interrupt enable)*/
#define TIMER_TIMX_DIER_UIE_Pos             ((uint32_t)0)   /*bit position, 允许更新中断 (Update interrupt enable)*/
#define TIMER_TIMX_DIER_CC1IE_Msk             ((uint32_t)0x2)   /* bit mask, 允许捕获/比较1中断 (Capture/Compare 1 interrupt enable)*/
#define TIMER_TIMX_DIER_CC1IE_Pos             ((uint32_t)1)   /*bit position, 允许捕获/比较1中断 (Capture/Compare 1 interrupt enable)*/
#define TIMER_TIMX_DIER_CC2IE_Msk             ((uint32_t)0x4)   /* bit mask, 允许捕获/比较2中断 (Capture/Compare 2 interrupt enable)*/
#define TIMER_TIMX_DIER_CC2IE_Pos             ((uint32_t)2)   /*bit position, 允许捕获/比较2中断 (Capture/Compare 2 interrupt enable)*/
#define TIMER_TIMX_DIER_TIE_Msk             ((uint32_t)0x40)   /* bit mask, 触发中断使能 (Trigger interrupt enable*/
#define TIMER_TIMX_DIER_TIE_Pos             ((uint32_t)6)   /*bit position, 触发中断使能 (Trigger interrupt enable*/
#define TIMER_TIMX_DIER_UDE_Msk             ((uint32_t)0x100)   /* bit mask, 允许更新的DMA请求 (Update DMA request enable)*/
#define TIMER_TIMX_DIER_UDE_Pos             ((uint32_t)8)   /*bit position, 允许更新的DMA请求 (Update DMA request enable)*/
#define TIMER_TIMX_DIER_CC1DE_Msk             ((uint32_t)0x200)   /* bit mask, 允许捕获/比较1的DMA请求 (Capture/Compare 1 DMA request enable)*/
#define TIMER_TIMX_DIER_CC1DE_Pos             ((uint32_t)9)   /*bit position, 允许捕获/比较1的DMA请求 (Capture/Compare 1 DMA request enable)*/
#define TIMER_TIMX_DIER_CC2DE_Msk             ((uint32_t)0x400)   /* bit mask, 允许捕获/比较2的DMA请求 (Capture/Compare 2 DMA request enable)*/
#define TIMER_TIMX_DIER_CC2DE_Pos             ((uint32_t)10)   /*bit position, 允许捕获/比较2的DMA请求 (Capture/Compare 2 DMA request enable)*/
#define TIMER_TIMX_DIER_TDE_Msk             ((uint32_t)0x4000)   /* bit mask, 允许触发DMA请求 (Trigger DMA request enable)*/
#define TIMER_TIMX_DIER_TDE_Pos             ((uint32_t)14)   /*bit position, 允许触发DMA请求 (Trigger DMA request enable)*/

/******************  Bit Definition for Register TIMX_SR  *********************/
#define TIMER_TIMX_SR_UIF_Msk             ((uint32_t)0x1)   /* bit mask, 更新中断标记 (Update interrupt flag)
当产生更新事件时该位由硬件置’1’。它由软件清’0’。
-若TIMx_CR1寄存器的UDIS=0、URS=0，当TIMx_EGR寄存器的UG=1时产生更新事件
(软件对计数器CNT重新初始化)；
-若TIMx_CR1寄存器的UDIS=0、URS=0，当计数器CNT被触发事件重初始化时产生更新事件。
*/
#define TIMER_TIMX_SR_UIF_Pos             ((uint32_t)0)   /*bit position, 更新中断标记 (Update interrupt flag)
当产生更新事件时该位由硬件置’1’。它由软件清’0’。
-若TIMx_CR1寄存器的UDIS=0、URS=0，当TIMx_EGR寄存器的UG=1时产生更新事件
(软件对计数器CNT重新初始化)；
-若TIMx_CR1寄存器的UDIS=0、URS=0，当计数器CNT被触发事件重初始化时产生更新事件。
*/
#define TIMER_TIMX_SR_CC1IF_Msk             ((uint32_t)0x2)   /* bit mask, 捕获/比较1 中断标记*/
#define TIMER_TIMX_SR_CC1IF_Pos             ((uint32_t)1)   /*bit position, 捕获/比较1 中断标记*/
#define TIMER_TIMX_SR_CC2IF_Msk             ((uint32_t)0x4)   /* bit mask, 捕获/比较2 中断标记*/
#define TIMER_TIMX_SR_CC2IF_Pos             ((uint32_t)2)   /*bit position, 捕获/比较2 中断标记*/
#define TIMER_TIMX_SR_TIF_Msk             ((uint32_t)0x40)   /* bit mask, 触发器中断标记,仅当相应的通道被配置为输入捕获时，该标记可由硬件置’1’。写’0’可清除该位。*/
#define TIMER_TIMX_SR_TIF_Pos             ((uint32_t)6)   /*bit position, 触发器中断标记,仅当相应的通道被配置为输入捕获时，该标记可由硬件置’1’。写’0’可清除该位。*/
#define TIMER_TIMX_SR_CC1OF_Msk             ((uint32_t)0x200)   /* bit mask, 捕获/比较1重复捕获标记 (Capture/Compare 1 overcapture flag)
仅当相应的通道被配置为输入捕获时，该标记可由硬件置’1’。写’0’可清除该位。
*/
#define TIMER_TIMX_SR_CC1OF_Pos             ((uint32_t)9)   /*bit position, 捕获/比较1重复捕获标记 (Capture/Compare 1 overcapture flag)
仅当相应的通道被配置为输入捕获时，该标记可由硬件置’1’。写’0’可清除该位。
*/
#define TIMER_TIMX_SR_CC2OF_Msk             ((uint32_t)0x400)   /* bit mask, 捕获/比较2重复捕获标记,仅当相应的通道被配置为输入捕获时，该标记可由硬件置’1’。写’0’可清除该位。*/
#define TIMER_TIMX_SR_CC2OF_Pos             ((uint32_t)10)   /*bit position, 捕获/比较2重复捕获标记,仅当相应的通道被配置为输入捕获时，该标记可由硬件置’1’。写’0’可清除该位。*/

/******************  Bit Definition for Register TIMX_EGR  *********************/
#define TIMER_TIMX_EGR_UG_Msk             ((uint32_t)0x1)   /* bit mask, 产生更新事件 (Update generation) 该位由软件置’1’，由硬件自动清’0’*/
#define TIMER_TIMX_EGR_UG_Pos             ((uint32_t)0)   /*bit position, 产生更新事件 (Update generation) 该位由软件置’1’，由硬件自动清’0’*/
#define TIMER_TIMX_EGR_CC1G_Msk             ((uint32_t)0x2)   /* bit mask, 产生捕获/比较1事件 (Capture/compare 1 generation)
该位由软件置’1’，用于产生一个捕获/比较事件，由硬件自动清’0’。
置CC1IF=1，若开启对应的中断和DMA，则产生相应的中断和DMA。若通道CC1配置为输入：
当前的计数器值捕获至TIMx_CCR1寄存器；设置CC1IF=1，若开启对应的中断和DMA，则产生相应的中断和DMA。若CC1IF已经为1，则设置CC1OF=1。
*/
#define TIMER_TIMX_EGR_CC1G_Pos             ((uint32_t)1)   /*bit position, 产生捕获/比较1事件 (Capture/compare 1 generation)
该位由软件置’1’，用于产生一个捕获/比较事件，由硬件自动清’0’。
置CC1IF=1，若开启对应的中断和DMA，则产生相应的中断和DMA。若通道CC1配置为输入：
当前的计数器值捕获至TIMx_CCR1寄存器；设置CC1IF=1，若开启对应的中断和DMA，则产生相应的中断和DMA。若CC1IF已经为1，则设置CC1OF=1。
*/
#define TIMER_TIMX_EGR_CC2G_Msk             ((uint32_t)0x4)   /* bit mask, 产生捕获/比较2事件*/
#define TIMER_TIMX_EGR_CC2G_Pos             ((uint32_t)2)   /*bit position, 产生捕获/比较2事件*/
#define TIMER_TIMX_EGR_TG_Msk             ((uint32_t)0x40)   /* bit mask, 产生触发事件 (Trigger generation)
该位由软件置’1’，用于产生一个触发事件，由硬件自动清’0’。
*/
#define TIMER_TIMX_EGR_TG_Pos             ((uint32_t)6)   /*bit position, 产生触发事件 (Trigger generation)
该位由软件置’1’，用于产生一个触发事件，由硬件自动清’0’。
*/

/******************  Bit Definition for Register TIMX_CCMR1_OP  *********************/
#define TIMER_TIMX_CCMR1_OP_CC1S_Msk             ((uint32_t)0x3)   /* bit mask, 捕获/比较1 选择 (Capture/Compare 1 selection) 这2位定义通道的方向(输入/输出)，及输入脚的选择：CC1S仅在通道关闭时(TIMx_CCER寄存器的CC1E=’0’)才是可写的。*/
#define TIMER_TIMX_CCMR1_OP_CC1S_Pos             ((uint32_t)0)   /*bit position, 捕获/比较1 选择 (Capture/Compare 1 selection) 这2位定义通道的方向(输入/输出)，及输入脚的选择：CC1S仅在通道关闭时(TIMx_CCER寄存器的CC1E=’0’)才是可写的。*/
#define TIMER_TIMX_CCMR1_OP_OC1FE_Msk             ((uint32_t)0x4)   /* bit mask, 输出比较1 快速使能 (Output compare 1 fast enable)
该位用于加快CC输出对触发器输入事件的响应。
该位只在通道被配置成PWM1或PWM2模式时起作用。配置为输入捕获时做预分频器
*/
#define TIMER_TIMX_CCMR1_OP_OC1FE_Pos             ((uint32_t)2)   /*bit position, 输出比较1 快速使能 (Output compare 1 fast enable)
该位用于加快CC输出对触发器输入事件的响应。
该位只在通道被配置成PWM1或PWM2模式时起作用。配置为输入捕获时做预分频器
*/
#define TIMER_TIMX_CCMR1_OP_OC1PE_Msk             ((uint32_t)0x8)   /* bit mask, 输出比较1预装载使能.注1：一旦LOCK级别设为3(TIMx_BDTR寄存器中的LOCK位)并且CC1S=’00’(该通道配置成输出)则该位不能被修改。
注2：仅在单脉冲模式下(TIMx_CR1寄存器的OPM=’1’)，可以在未确认预装载寄存器情况下使用PWM模式，否则其动作不确定。
*/
#define TIMER_TIMX_CCMR1_OP_OC1PE_Pos             ((uint32_t)3)   /*bit position, 输出比较1预装载使能.注1：一旦LOCK级别设为3(TIMx_BDTR寄存器中的LOCK位)并且CC1S=’00’(该通道配置成输出)则该位不能被修改。
注2：仅在单脉冲模式下(TIMx_CR1寄存器的OPM=’1’)，可以在未确认预装载寄存器情况下使用PWM模式，否则其动作不确定。
*/
#define TIMER_TIMX_CCMR1_OP_OC1M_Msk             ((uint32_t)0x70)   /* bit mask, 输出比较1模式 (Output compare 1 enable)
该3位定义了输出参考信号OC1REF的动作，而OC1REF决定了OC1的值。OC1REF是高电平有效，而OC1的有效电平取决于CC1P位。
注1：一旦LOCK级别设为3(TIMx_BDTR寄存器中的LOCK位)并且CC1S=’00’(该通道配置成输出)则该位不能被修改。
注2：在PWM模式1或PWM模式2中，只有当比较结果改变了或在输出比较模式中从冻结模式切换到PWM模式时，OC1REF电平才改变。*/
#define TIMER_TIMX_CCMR1_OP_OC1M_Pos             ((uint32_t)4)   /*bit position, 输出比较1模式 (Output compare 1 enable)
该3位定义了输出参考信号OC1REF的动作，而OC1REF决定了OC1的值。OC1REF是高电平有效，而OC1的有效电平取决于CC1P位。
注1：一旦LOCK级别设为3(TIMx_BDTR寄存器中的LOCK位)并且CC1S=’00’(该通道配置成输出)则该位不能被修改。
注2：在PWM模式1或PWM模式2中，只有当比较结果改变了或在输出比较模式中从冻结模式切换到PWM模式时，OC1REF电平才改变。*/
#define TIMER_TIMX_CCMR1_OP_OC1CE_Msk             ((uint32_t)0x80)   /* bit mask, 输出比较1清0使能 (Output compare 1 clear enable) */
#define TIMER_TIMX_CCMR1_OP_OC1CE_Pos             ((uint32_t)7)   /*bit position, 输出比较1清0使能 (Output compare 1 clear enable) */
#define TIMER_TIMX_CCMR1_OP_CC2S_Msk             ((uint32_t)0x300)   /* bit mask, 捕获/比较2选择 (Capture/Compare 2 selection) 该位定义通道的方向(输入/输出)，及输入脚的选择.注：CC2S仅在通道关闭时(TIMx_CCER寄存器的CC2E=’0’)才是可写的。*/
#define TIMER_TIMX_CCMR1_OP_CC2S_Pos             ((uint32_t)8)   /*bit position, 捕获/比较2选择 (Capture/Compare 2 selection) 该位定义通道的方向(输入/输出)，及输入脚的选择.注：CC2S仅在通道关闭时(TIMx_CCER寄存器的CC2E=’0’)才是可写的。*/
#define TIMER_TIMX_CCMR1_OP_OC2FE_Msk             ((uint32_t)0x400)   /* bit mask, 输出比较2快速使能*/
#define TIMER_TIMX_CCMR1_OP_OC2FE_Pos             ((uint32_t)10)   /*bit position, 输出比较2快速使能*/
#define TIMER_TIMX_CCMR1_OP_OC2PE_Msk             ((uint32_t)0x800)   /* bit mask, 输出比较2预装载使能*/
#define TIMER_TIMX_CCMR1_OP_OC2PE_Pos             ((uint32_t)11)   /*bit position, 输出比较2预装载使能*/
#define TIMER_TIMX_CCMR1_OP_OC2M_Msk             ((uint32_t)0x7000)   /* bit mask, 输出比较2模式*/
#define TIMER_TIMX_CCMR1_OP_OC2M_Pos             ((uint32_t)12)   /*bit position, 输出比较2模式*/
#define TIMER_TIMX_CCMR1_OP_OC2CE_Msk             ((uint32_t)0x8000)   /* bit mask, 输出比较2清0使能*/
#define TIMER_TIMX_CCMR1_OP_OC2CE_Pos             ((uint32_t)15)   /*bit position, 输出比较2清0使能*/

/******************  Bit Definition for Register TIMX_CCMR1_IC  *********************/
#define TIMER_TIMX_CCMR1_IC_CC1S_Msk             ((uint32_t)0x3)   /* bit mask, 捕获/比较1选择 (Capture/Compare 1 selection) 这2位定义通道的方向(输入/输出)，及输入脚的选择*/
#define TIMER_TIMX_CCMR1_IC_CC1S_Pos             ((uint32_t)0)   /*bit position, 捕获/比较1选择 (Capture/Compare 1 selection) 这2位定义通道的方向(输入/输出)，及输入脚的选择*/
#define TIMER_TIMX_CCMR1_IC_IC1PSC_Msk             ((uint32_t)0xc)   /* bit mask, 输入/捕获1预分频器 (Input capture 1 prescaler)
这2位定义了CC1输入(IC1)的预分频系数。
一旦CC1E=’0’(TIMx_CCER寄存器中)，则预分频器复位。
*/
#define TIMER_TIMX_CCMR1_IC_IC1PSC_Pos             ((uint32_t)2)   /*bit position, 输入/捕获1预分频器 (Input capture 1 prescaler)
这2位定义了CC1输入(IC1)的预分频系数。
一旦CC1E=’0’(TIMx_CCER寄存器中)，则预分频器复位。
*/
#define TIMER_TIMX_CCMR1_IC_IC1F_Msk             ((uint32_t)0xf0)   /* bit mask, 输入捕获1滤波器 (Input capture 1 filter)
这几位定义了TI1输入的采样频率及数字滤波器长度。数字滤波器由一个事件计数器组成，它记录到N个事件后会产生一个输出的跳变：
*/
#define TIMER_TIMX_CCMR1_IC_IC1F_Pos             ((uint32_t)4)   /*bit position, 输入捕获1滤波器 (Input capture 1 filter)
这几位定义了TI1输入的采样频率及数字滤波器长度。数字滤波器由一个事件计数器组成，它记录到N个事件后会产生一个输出的跳变：
*/
#define TIMER_TIMX_CCMR1_IC_CC2S_Msk             ((uint32_t)0x300)   /* bit mask, 捕获/比较2选择 (Capture/compare 2 selection) 这2位定义通道的方向(输入/输出)，及输入脚的选择*/
#define TIMER_TIMX_CCMR1_IC_CC2S_Pos             ((uint32_t)8)   /*bit position, 捕获/比较2选择 (Capture/compare 2 selection) 这2位定义通道的方向(输入/输出)，及输入脚的选择*/
#define TIMER_TIMX_CCMR1_IC_IC2PSC_Msk             ((uint32_t)0xc00)   /* bit mask, 输入/捕获2预分频器 (input capture 2 prescaler)*/
#define TIMER_TIMX_CCMR1_IC_IC2PSC_Pos             ((uint32_t)10)   /*bit position, 输入/捕获2预分频器 (input capture 2 prescaler)*/
#define TIMER_TIMX_CCMR1_IC_IC2F_Msk             ((uint32_t)0xf000)   /* bit mask, 输入捕获2滤波器 (Input capture 2 filter)*/
#define TIMER_TIMX_CCMR1_IC_IC2F_Pos             ((uint32_t)12)   /*bit position, 输入捕获2滤波器 (Input capture 2 filter)*/

/******************  Bit Definition for Register TIMX_CCER  *********************/
#define TIMER_TIMX_CCER_CC1E_Msk             ((uint32_t)0x1)   /* bit mask, 输入/捕获1输出使能 (Capture/Compare 1 output enable)
CC1通道配置为输出：
0： 关闭－ OC1禁止输出。
1： 开启－ OC1信号输出到对应的输出引脚。
CC1通道配置为输入：
该位决定了计数器的值是否能捕获入TIMx_CCR1寄存器。
0：捕获禁止；
1：捕获使能。
*/
#define TIMER_TIMX_CCER_CC1E_Pos             ((uint32_t)0)   /*bit position, 输入/捕获1输出使能 (Capture/Compare 1 output enable)
CC1通道配置为输出：
0： 关闭－ OC1禁止输出。
1： 开启－ OC1信号输出到对应的输出引脚。
CC1通道配置为输入：
该位决定了计数器的值是否能捕获入TIMx_CCR1寄存器。
0：捕获禁止；
1：捕获使能。
*/
#define TIMER_TIMX_CCER_CC1P_Msk             ((uint32_t)0x2)   /* bit mask, 输入/捕获1输出极性 (Capture/Compare 1 output polarity)
CC1通道配置为输出：
0：OC1高电平有效
1：OC1低电平有效
CC1通道配置为输入：
该位选择是IC1还是IC1的反相信号作为触发或捕获信号。
0：不反相：捕获发生在IC1的上升沿；当用作外部触发器时，IC1不反相。
1：反相：捕获发生在IC1的下降沿；当用作外部触发器时，IC1反相。
*/
#define TIMER_TIMX_CCER_CC1P_Pos             ((uint32_t)1)   /*bit position, 输入/捕获1输出极性 (Capture/Compare 1 output polarity)
CC1通道配置为输出：
0：OC1高电平有效
1：OC1低电平有效
CC1通道配置为输入：
该位选择是IC1还是IC1的反相信号作为触发或捕获信号。
0：不反相：捕获发生在IC1的上升沿；当用作外部触发器时，IC1不反相。
1：反相：捕获发生在IC1的下降沿；当用作外部触发器时，IC1反相。
*/
#define TIMER_TIMX_CCER_CC2E_Msk             ((uint32_t)0x10)   /* bit mask, 输入/捕获2输出使能*/
#define TIMER_TIMX_CCER_CC2E_Pos             ((uint32_t)4)   /*bit position, 输入/捕获2输出使能*/
#define TIMER_TIMX_CCER_CC2P_Msk             ((uint32_t)0x20)   /* bit mask, 输入/捕获2输出极性*/
#define TIMER_TIMX_CCER_CC2P_Pos             ((uint32_t)5)   /*bit position, 输入/捕获2输出极性*/

/******************  Bit Definition for Register TIMX_CNT  *********************/
#define TIMER_TIMX_CNT_CNT_Msk             ((uint32_t)0xffff)   /* bit mask, 计数器的值*/
#define TIMER_TIMX_CNT_CNT_Pos             ((uint32_t)0)   /*bit position, 计数器的值*/

/******************  Bit Definition for Register TIMX_PSC  *********************/
#define TIMER_TIMX_PSC_PSC_Msk             ((uint32_t)0xffff)   /* bit mask, 预分频器的值 (Prescaler value)
计数器的时钟频率CK_CNT等于fCK_PSC/(PSC[15:0]+1)。
PSC包含了当更新事件产生时装入当前预分频器寄存器的值。
*/
#define TIMER_TIMX_PSC_PSC_Pos             ((uint32_t)0)   /*bit position, 预分频器的值 (Prescaler value)
计数器的时钟频率CK_CNT等于fCK_PSC/(PSC[15:0]+1)。
PSC包含了当更新事件产生时装入当前预分频器寄存器的值。
*/

/******************  Bit Definition for Register TIMX_ARR  *********************/
#define TIMER_TIMX_ARR_ARR_Msk             ((uint32_t)0xffff)   /* bit mask, 自动重装载的值 (Auto reload value)
ARR包含了将要传送至实际的自动重装载寄存器的数值。详细参考14.3.1节：有关ARR的更新和动作。
当自动重装载的值为空时，计数器不工作。
*/
#define TIMER_TIMX_ARR_ARR_Pos             ((uint32_t)0)   /*bit position, 自动重装载的值 (Auto reload value)
ARR包含了将要传送至实际的自动重装载寄存器的数值。详细参考14.3.1节：有关ARR的更新和动作。
当自动重装载的值为空时，计数器不工作。
*/

/******************  Bit Definition for Register TIMX_CCR1  *********************/
#define TIMER_TIMX_CCR1_CCR1_Msk             ((uint32_t)0xffff)   /* bit mask, 捕获/比较1的值 (Capture/Compare 1 value)
若CC1通道配置为输出：
CCR1包含了装入当前捕获/比较1寄存器的值(预装载值)。
如果在TIMx_CCMR1寄存器(OC1PE位)中未选择预装载特性，写入的数值会被立即传输至当前寄存器中。否则只有当更新事件发生时，此预装载值才传输至当前捕获/比较1寄存器中。
当前捕获/比较寄存器参与同计数器TIMx_CNT的比较，并在OC1端口上产生输出信号。若CC1通道配置为输入：
CCR1包含了由上一次输入捕获1事件(IC1)传输的计数器值。
*/
#define TIMER_TIMX_CCR1_CCR1_Pos             ((uint32_t)0)   /*bit position, 捕获/比较1的值 (Capture/Compare 1 value)
若CC1通道配置为输出：
CCR1包含了装入当前捕获/比较1寄存器的值(预装载值)。
如果在TIMx_CCMR1寄存器(OC1PE位)中未选择预装载特性，写入的数值会被立即传输至当前寄存器中。否则只有当更新事件发生时，此预装载值才传输至当前捕获/比较1寄存器中。
当前捕获/比较寄存器参与同计数器TIMx_CNT的比较，并在OC1端口上产生输出信号。若CC1通道配置为输入：
CCR1包含了由上一次输入捕获1事件(IC1)传输的计数器值。
*/

/******************  Bit Definition for Register TIMX_CCR2  *********************/
#define TIMER_TIMX_CCR2_CCR2_Msk             ((uint32_t)0xffff)   /* bit mask, 捕获/比较2的值 (Capture/Compare 2 value)
若CC2通道配置为输出：
CCR2包含了装入当前捕获/比较2寄存器的值(预装载值)。
如果在TIMx_CCMR2寄存器(OC2PE位)中未选择预装载特性，写入的数值会被立即传输至当前寄存器中。否则只有当更新事件发生时，此预装载值才传输至当前捕获/比较2寄存器中。
当前捕获/比较寄存器参与同计数器TIMx_CNT的比较，并在OC2端口上产生输出信号。若CC2通道配置为输入：
CCR2包含了由上一次输入捕获2事件(IC2)传输的计数器值。
*/
#define TIMER_TIMX_CCR2_CCR2_Pos             ((uint32_t)0)   /*bit position, 捕获/比较2的值 (Capture/Compare 2 value)
若CC2通道配置为输出：
CCR2包含了装入当前捕获/比较2寄存器的值(预装载值)。
如果在TIMx_CCMR2寄存器(OC2PE位)中未选择预装载特性，写入的数值会被立即传输至当前寄存器中。否则只有当更新事件发生时，此预装载值才传输至当前捕获/比较2寄存器中。
当前捕获/比较寄存器参与同计数器TIMx_CNT的比较，并在OC2端口上产生输出信号。若CC2通道配置为输入：
CCR2包含了由上一次输入捕获2事件(IC2)传输的计数器值。
*/

/******************  Bit Definition for Register TIMX_DCR  *********************/
#define TIMER_TIMX_DCR_DBA_Msk             ((uint32_t)0x1f)   /* bit mask, DMA基地址 (DMA base address)
这些位定义了DMA在连续模式下的基地址(当对TIMx_DMAR寄存器进行读或写时)，DBA定义为从TIMx_CR1寄存器所在地址开始的偏移量：
00000：TIMx_CR1，
00001：TIMx_CR2，
00010：TIMx_SMCR，
......
*/
#define TIMER_TIMX_DCR_DBA_Pos             ((uint32_t)0)   /*bit position, DMA基地址 (DMA base address)
这些位定义了DMA在连续模式下的基地址(当对TIMx_DMAR寄存器进行读或写时)，DBA定义为从TIMx_CR1寄存器所在地址开始的偏移量：
00000：TIMx_CR1，
00001：TIMx_CR2，
00010：TIMx_SMCR，
......
*/
#define TIMER_TIMX_DCR_DBL_Msk             ((uint32_t)0x1f00)   /* bit mask, DMA连续传送长度 (DMA burst length)
这些位定义了DMA在连续模式下的传送长度(当对TIMx_DMAR寄存器进行读或写时，定时器则进行一次连续传送)，即：定义传输的字节数目：
00000：1个字节
00001：2个字节
00010：3个字节
......
*/
#define TIMER_TIMX_DCR_DBL_Pos             ((uint32_t)8)   /*bit position, DMA连续传送长度 (DMA burst length)
这些位定义了DMA在连续模式下的传送长度(当对TIMx_DMAR寄存器进行读或写时，定时器则进行一次连续传送)，即：定义传输的字节数目：
00000：1个字节
00001：2个字节
00010：3个字节
......
*/

/******************  Bit Definition for Register TIMX_DMAR  *********************/
#define TIMER_TIMX_DMAR_DMAB_Msk             ((uint32_t)0xffff)   /* bit mask, DMA连续传送寄存器 (DMA register for burst accesses)
对TIMx_DMAR寄存器的读或写会导致对以下地址所在寄存器的存取操作：
TIMx_CR1地址 + DBA + DMA索引，其中：
“TIMx_CR1地址”是控制寄存器1(TIMx_CR1)所在的地址； “DBA”是TIMx_DCR寄存器中定义的基地址；
“DMA索引”是由DMA自动控制的偏移量，它取决于TIMx_DCR寄存器中定义的DBL。
*/
#define TIMER_TIMX_DMAR_DMAB_Pos             ((uint32_t)0)   /*bit position, DMA连续传送寄存器 (DMA register for burst accesses)
对TIMx_DMAR寄存器的读或写会导致对以下地址所在寄存器的存取操作：
TIMx_CR1地址 + DBA + DMA索引，其中：
“TIMx_CR1地址”是控制寄存器1(TIMx_CR1)所在的地址； “DBA”是TIMx_DCR寄存器中定义的基地址；
“DMA索引”是由DMA自动控制的偏移量，它取决于TIMx_DCR寄存器中定义的DBL。
*/

/******************************************************************************/
/*                    LPTIM                         */
/******************************************************************************/


/******************  Bit Definition for Register CSR  *********************/
#define LPTIM_CSR_TEN_Msk             ((uint32_t)0x1)   /* bit mask, 定时器启用
启用LPTMR定时器。当TEN清除时，它重置LPTMR内部逻辑，包括CNR和TCF。当TEN设置时，LPTMR启用。将1写入此字段时，不得更改CSR[5:1]。
0-禁用
1-启用
*/
#define LPTIM_CSR_TEN_Pos             ((uint32_t)0)   /*bit position, 定时器启用
启用LPTMR定时器。当TEN清除时，它重置LPTMR内部逻辑，包括CNR和TCF。当TEN设置时，LPTMR启用。将1写入此字段时，不得更改CSR[5:1]。
0-禁用
1-启用
*/
#define LPTIM_CSR_TMS_Msk             ((uint32_t)0x2)   /* bit mask, 定时器模式选择配置LPTMR的模式。
仅当LPTMR被禁用时，您才必须更改TMS。
0-时间计数器模式
1-脉冲计数器模式
*/
#define LPTIM_CSR_TMS_Pos             ((uint32_t)1)   /*bit position, 定时器模式选择配置LPTMR的模式。
仅当LPTMR被禁用时，您才必须更改TMS。
0-时间计数器模式
1-脉冲计数器模式
*/
#define LPTIM_CSR_TFC_Msk             ((uint32_t)0x4)   /* bit mask, 定时器自由运行计数器
只有在禁用LPTMR时才能更改TFC。
如果TFC=0，则每当TCF=1时，LPTMR都会重置CNR。如果TFC=1，则LPTMR会在溢出时重置CNR。
0-TCF置位时复位定时器计数值
1-计数器溢出时复位定时器计数值
*/
#define LPTIM_CSR_TFC_Pos             ((uint32_t)2)   /*bit position, 定时器自由运行计数器
只有在禁用LPTMR时才能更改TFC。
如果TFC=0，则每当TCF=1时，LPTMR都会重置CNR。如果TFC=1，则LPTMR会在溢出时重置CNR。
0-TCF置位时复位定时器计数值
1-计数器溢出时复位定时器计数值
*/
#define LPTIM_CSR_TPP_Msk             ((uint32_t)0x8)   /* bit mask, 定时器引脚极性
在脉冲计数器模式下配置输入源的极性。
只有禁用LPTMR时，您才能更改TPP。如果TPP=0，则脉冲计数器输入源为高电平，CNR在上升沿递增。如果TPP=1，则脉冲计数器输入源为低电平，CNR在下降沿递增。
0-高电平
1-低电平
*/
#define LPTIM_CSR_TPP_Pos             ((uint32_t)3)   /*bit position, 定时器引脚极性
在脉冲计数器模式下配置输入源的极性。
只有禁用LPTMR时，您才能更改TPP。如果TPP=0，则脉冲计数器输入源为高电平，CNR在上升沿递增。如果TPP=1，则脉冲计数器输入源为低电平，CNR在下降沿递增。
0-高电平
1-低电平
*/
#define LPTIM_CSR_TPS_Msk             ((uint32_t)0x30)   /* bit mask, 定时器引脚选择
配置在脉冲计数器模式下使用的输入源。只有禁用LPTMR时，您才能更改TPS。输入连接因设备而异。有关详细信息，请参阅有关这些输入连接的芯片配置信息。
00-输入0
01-输入1
10-输入2
11-输入3
*/
#define LPTIM_CSR_TPS_Pos             ((uint32_t)4)   /*bit position, 定时器引脚选择
配置在脉冲计数器模式下使用的输入源。只有禁用LPTMR时，您才能更改TPS。输入连接因设备而异。有关详细信息，请参阅有关这些输入连接的芯片配置信息。
00-输入0
01-输入1
10-输入2
11-输入3
*/
#define LPTIM_CSR_TIE_Msk             ((uint32_t)0x40)   /* bit mask, 定时器中断
启用如果TIE=1，则LPTMR在TCF=1的情况下也会产生中断。
0-禁用
1-启用
*/
#define LPTIM_CSR_TIE_Pos             ((uint32_t)6)   /*bit position, 定时器中断
启用如果TIE=1，则LPTMR在TCF=1的情况下也会产生中断。
0-禁用
1-启用
*/
#define LPTIM_CSR_TCF_Msk             ((uint32_t)0x80)   /* bit mask, 定时器比较标志 
当启用LPTMR且CNR等于CMR时，在下一个CNR增量上设置定时器比较标志。
当LPTMR被禁用或逻辑1被写入TCF时，TCF被清除。
在启用定时器中断或DMA请求之前，请清除此字段。
0-CNR≠（CMR+1）
1-CNR=（CMR+1）
*/
#define LPTIM_CSR_TCF_Pos             ((uint32_t)7)   /*bit position, 定时器比较标志 
当启用LPTMR且CNR等于CMR时，在下一个CNR增量上设置定时器比较标志。
当LPTMR被禁用或逻辑1被写入TCF时，TCF被清除。
在启用定时器中断或DMA请求之前，请清除此字段。
0-CNR≠（CMR+1）
1-CNR=（CMR+1）
*/
#define LPTIM_CSR_TDRE_Msk             ((uint32_t)0x100)   /* bit mask, 定时器DMA请求
启用定时器DMA请求。当TDRE被设置时，只要TCF也被设置，就会生成LPTMR DMA请求。然后，DMA控制器完成后，TCF被清除。
0-禁用
1-启用
*/
#define LPTIM_CSR_TDRE_Pos             ((uint32_t)8)   /*bit position, 定时器DMA请求
启用定时器DMA请求。当TDRE被设置时，只要TCF也被设置，就会生成LPTMR DMA请求。然后，DMA控制器完成后，TCF被清除。
0-禁用
1-启用
*/
#define LPTIM_CSR_TPWM_Msk             ((uint32_t)0x200)   /* bit mask, 定时器PWM功能
启用定时器的PWM输出功能
0-禁用
1-启用
*/
#define LPTIM_CSR_TPWM_Pos             ((uint32_t)9)   /*bit position, 定时器PWM功能
启用定时器的PWM输出功能
0-禁用
1-启用
*/

/******************  Bit Definition for Register PSR  *********************/
#define LPTIM_PSR_PCS_Msk             ((uint32_t)0x3)   /* bit mask, 预分频器/毛刺滤波器时钟选择
选择LPTMR预分频器或毛刺滤波器所使用的时钟。只有禁用LPTMR时，您才能更改PCS。有关这些输入的连接信息，请参阅芯片配置详细信息。
在时间计数器模式下，PCS选择预分频器的输入时钟在脉冲计数器模式下，PCS选择毛刺滤波器的输入时钟。
00-时钟0
01-时钟1
10-时钟2
11-时钟3
*/
#define LPTIM_PSR_PCS_Pos             ((uint32_t)0)   /*bit position, 预分频器/毛刺滤波器时钟选择
选择LPTMR预分频器或毛刺滤波器所使用的时钟。只有禁用LPTMR时，您才能更改PCS。有关这些输入的连接信息，请参阅芯片配置详细信息。
在时间计数器模式下，PCS选择预分频器的输入时钟在脉冲计数器模式下，PCS选择毛刺滤波器的输入时钟。
00-时钟0
01-时钟1
10-时钟2
11-时钟3
*/
#define LPTIM_PSR_PBYP_Msk             ((uint32_t)0x4)   /* bit mask, 预分频器/毛刺滤波器旁路
控制CNR的时钟。当PBYP=1时，在时间计数器模式下选定的预分频器时钟，或者在脉冲计数器模式下的选定输入源，直接对CNR进行时钟控制。当PBYP=0时，预分频器/毛刺滤波器的输出为CNR计时。只有禁用LPTMR时，您才能更改PBYP。
0-预分频器/毛刺滤波器启用
1-预分频器/毛刺滤波器旁路
*/
#define LPTIM_PSR_PBYP_Pos             ((uint32_t)2)   /*bit position, 预分频器/毛刺滤波器旁路
控制CNR的时钟。当PBYP=1时，在时间计数器模式下选定的预分频器时钟，或者在脉冲计数器模式下的选定输入源，直接对CNR进行时钟控制。当PBYP=0时，预分频器/毛刺滤波器的输出为CNR计时。只有禁用LPTMR时，您才能更改PBYP。
0-预分频器/毛刺滤波器启用
1-预分频器/毛刺滤波器旁路
*/
#define LPTIM_PSR_PRESCALE_Msk             ((uint32_t)0x78)   /* bit mask, 预分频/毛刺滤波器值
在时间计数器模式下配置预分频器的大小或在脉冲计数器模式下配置毛刺滤波器的宽度。由于脉冲计数器输入的同步，毛刺滤波器的宽度可以变化1个周期。只有当LPTMR被禁用时，才必须更改precale。
0000 -预分频器将预分频时钟除以2；故障过滤器不支持此配置。
0001 -预分频器将预分频时钟除以4；毛刺滤波器识别输入引脚的变化后2上升时钟边缘。
0010 -预分频器将预分频时钟除以8；毛刺滤波器在4个上升时钟边缘后识别输入引脚的变化。
0011 -预分频器将预分频时钟除以16；毛刺滤波器识别输入引脚在8上升时钟边缘后的变化。
0100 -预分频器将预分频时钟除以32；毛刺滤波器在16个上升时钟边缘后识别输入引脚的变化。
0101 -预分频器将预分频时钟除以64；毛刺滤波器识别在32上升时钟边缘后输入引脚的变化。
0110 -预分频器将预分频时钟除以128；毛刺滤波器识别64个上升时钟边缘后输入引脚的变化。
0111 -预分频器将预分频时钟除以256；毛刺滤波器识别在128上升时钟边缘后输入引脚的变化。
1000 -预分频器将预分频时钟除以512；毛刺滤波器识别输入引脚的变化后256上升时钟边。
1001 -预分频器将预分频时钟除以1024；毛刺滤波器识别512上升时钟沿后输入引脚的变化。
1010 -预分频器将预分频时钟除以2048；毛刺滤波器识别1024上升时钟边缘后输入引脚的变化。
1011 -预分频器将预分频时钟除以4096；毛刺滤波器识别2048上升时钟边缘后输入引脚的变化。
1100 -预分频器将预分频时钟除以8192；毛刺滤波器识别4096上升时钟边缘后输入引脚的变化。
1101 -预分频器将预分频器时钟除以16,384；毛刺滤波器识别8192上升时钟边缘后输入引脚的变化。
1110 -预分频器将预分频器时钟除以32,768；毛刺滤波器在16384个上升时钟边缘后识别输入引脚的变化。
1111 -预分频器将预分频时钟除以65,536；毛刺滤波器在32,768个上升时钟边后识别输入引脚的变化。
*/
#define LPTIM_PSR_PRESCALE_Pos             ((uint32_t)3)   /*bit position, 预分频/毛刺滤波器值
在时间计数器模式下配置预分频器的大小或在脉冲计数器模式下配置毛刺滤波器的宽度。由于脉冲计数器输入的同步，毛刺滤波器的宽度可以变化1个周期。只有当LPTMR被禁用时，才必须更改precale。
0000 -预分频器将预分频时钟除以2；故障过滤器不支持此配置。
0001 -预分频器将预分频时钟除以4；毛刺滤波器识别输入引脚的变化后2上升时钟边缘。
0010 -预分频器将预分频时钟除以8；毛刺滤波器在4个上升时钟边缘后识别输入引脚的变化。
0011 -预分频器将预分频时钟除以16；毛刺滤波器识别输入引脚在8上升时钟边缘后的变化。
0100 -预分频器将预分频时钟除以32；毛刺滤波器在16个上升时钟边缘后识别输入引脚的变化。
0101 -预分频器将预分频时钟除以64；毛刺滤波器识别在32上升时钟边缘后输入引脚的变化。
0110 -预分频器将预分频时钟除以128；毛刺滤波器识别64个上升时钟边缘后输入引脚的变化。
0111 -预分频器将预分频时钟除以256；毛刺滤波器识别在128上升时钟边缘后输入引脚的变化。
1000 -预分频器将预分频时钟除以512；毛刺滤波器识别输入引脚的变化后256上升时钟边。
1001 -预分频器将预分频时钟除以1024；毛刺滤波器识别512上升时钟沿后输入引脚的变化。
1010 -预分频器将预分频时钟除以2048；毛刺滤波器识别1024上升时钟边缘后输入引脚的变化。
1011 -预分频器将预分频时钟除以4096；毛刺滤波器识别2048上升时钟边缘后输入引脚的变化。
1100 -预分频器将预分频时钟除以8192；毛刺滤波器识别4096上升时钟边缘后输入引脚的变化。
1101 -预分频器将预分频器时钟除以16,384；毛刺滤波器识别8192上升时钟边缘后输入引脚的变化。
1110 -预分频器将预分频器时钟除以32,768；毛刺滤波器在16384个上升时钟边缘后识别输入引脚的变化。
1111 -预分频器将预分频时钟除以65,536；毛刺滤波器在32,768个上升时钟边后识别输入引脚的变化。
*/

/******************  Bit Definition for Register CMR  *********************/
#define LPTIM_CMR_COMPARE_Msk             ((uint32_t)0xffffffff)   /* bit mask, 比较值
在下一个CNR增量上，如果启用了LPTMR并且CNR等于CMR，则：
1。LPTMR向TCF写入1。
2.硬件触发器一直有效，直到下次CNR递增。
如果CMR=0，则硬件触发器保持有效，直到禁用LPTMR。如果启用了LPTMR，则必须仅在TCF=1时更改CMR。
*/
#define LPTIM_CMR_COMPARE_Pos             ((uint32_t)0)   /*bit position, 比较值
在下一个CNR增量上，如果启用了LPTMR并且CNR等于CMR，则：
1。LPTMR向TCF写入1。
2.硬件触发器一直有效，直到下次CNR递增。
如果CMR=0，则硬件触发器保持有效，直到禁用LPTMR。如果启用了LPTMR，则必须仅在TCF=1时更改CMR。
*/

/******************  Bit Definition for Register CNR  *********************/
#define LPTIM_CNR_COUNTER_Msk             ((uint32_t)0x7fffffff)   /* bit mask, 计数器值
包含上次写入此寄存器时LPTMR计数器的当前值。
*/
#define LPTIM_CNR_COUNTER_Pos             ((uint32_t)0)   /*bit position, 计数器值
包含上次写入此寄存器时LPTMR计数器的当前值。
*/

/******************  Bit Definition for Register ARR  *********************/
#define LPTIM_ARR_AUTORELOAD_Msk             ((uint32_t)0xffffffff)   /* bit mask,  自动重加载值
在PWM模式使能的基础上，通过配置ARR值，实现第二次比较
*/
#define LPTIM_ARR_AUTORELOAD_Pos             ((uint32_t)0)   /*bit position,  自动重加载值
在PWM模式使能的基础上，通过配置ARR值，实现第二次比较
*/

/******************************************************************************/
/*                    RTC                         */
/******************************************************************************/


/******************  Bit Definition for Register RTC_CRH  *********************/
#define RTC_CRH_SECIE_Msk             ((uint32_t)0x1)   /* bit mask, 允许秒中断 (Second interrupt enable) 0：屏蔽(不允许)秒中断1：允许秒中断*/
#define RTC_CRH_SECIE_Pos             ((uint32_t)0)   /*bit position, 允许秒中断 (Second interrupt enable) 0：屏蔽(不允许)秒中断1：允许秒中断*/
#define RTC_CRH_ALRIE_Msk             ((uint32_t)0x2)   /* bit mask, 允许闹钟中断 (Alarm interrupt enable) 0：屏蔽(不允许)闹钟中断1：允许闹钟中断*/
#define RTC_CRH_ALRIE_Pos             ((uint32_t)1)   /*bit position, 允许闹钟中断 (Alarm interrupt enable) 0：屏蔽(不允许)闹钟中断1：允许闹钟中断*/
#define RTC_CRH_OWIE_Msk             ((uint32_t)0x4)   /* bit mask, 允许溢出中断位 (Overflow interrupt enable) 0：屏蔽(不允许)溢出中断1：允许溢出中断*/
#define RTC_CRH_OWIE_Pos             ((uint32_t)2)   /*bit position, 允许溢出中断位 (Overflow interrupt enable) 0：屏蔽(不允许)溢出中断1：允许溢出中断*/

/******************  Bit Definition for Register RTC_CRL  *********************/
#define RTC_CRL_SECF_Msk             ((uint32_t)0x1)   /* bit mask, 秒标志 (Second flag)
当32位可编程预分频器溢出时，此位由硬件置’1’同时RTC计数器加1。因此，此标志为分辨率可编程的RTC计数器提供一个周期性的信号(通常为1秒)。如果RTC_CRH寄存器中SECIE=1，则产生中断。此位只能由软件清除。对此位写’1’是无效的。
0：秒标志条件不成立；
1：秒标志条件成立。
*/
#define RTC_CRL_SECF_Pos             ((uint32_t)0)   /*bit position, 秒标志 (Second flag)
当32位可编程预分频器溢出时，此位由硬件置’1’同时RTC计数器加1。因此，此标志为分辨率可编程的RTC计数器提供一个周期性的信号(通常为1秒)。如果RTC_CRH寄存器中SECIE=1，则产生中断。此位只能由软件清除。对此位写’1’是无效的。
0：秒标志条件不成立；
1：秒标志条件成立。
*/
#define RTC_CRL_ALRF_Msk             ((uint32_t)0x2)   /* bit mask, 允许闹钟中断 (Alarm interrupt enable) 当32位可编程计数器达到RTC_ALR寄存器所设置的预定值，此位由硬件置’1’。如果RTC_CRH 寄存器中ALRIE=1，则产生中断。此位只能由软件清’0’。对此位写’1’是无效的。
0：无闹钟；
1：有闹钟。
*/
#define RTC_CRL_ALRF_Pos             ((uint32_t)1)   /*bit position, 允许闹钟中断 (Alarm interrupt enable) 当32位可编程计数器达到RTC_ALR寄存器所设置的预定值，此位由硬件置’1’。如果RTC_CRH 寄存器中ALRIE=1，则产生中断。此位只能由软件清’0’。对此位写’1’是无效的。
0：无闹钟；
1：有闹钟。
*/
#define RTC_CRL_OWF_Msk             ((uint32_t)0x4)   /* bit mask, 溢出标志 (Overflow flag)
当32位可编程计数器溢出时，此位由硬件置’1’。如果RTC_CRH寄存器中OWIE=1，则产生中断。此位只能由软件清’0’。对此位写’1’是无效的。
0：无溢出；
1：32位可编程计数器溢出。
*/
#define RTC_CRL_OWF_Pos             ((uint32_t)2)   /*bit position, 溢出标志 (Overflow flag)
当32位可编程计数器溢出时，此位由硬件置’1’。如果RTC_CRH寄存器中OWIE=1，则产生中断。此位只能由软件清’0’。对此位写’1’是无效的。
0：无溢出；
1：32位可编程计数器溢出。
*/
#define RTC_CRL_RSF_Msk             ((uint32_t)0x8)   /* bit mask, 寄存器同步标志 (Registers synchronized flag)
每当RTC_CNT寄存器和RTC_DIV寄存器由软件更新或清’0’时，此位由硬件置’1’。在APB1复位后，或APB1时钟停止后，此位必须由软件清’0’。要进行任何的读操作之前，用户程序必须等待这位被硬件置’1’，以确保RTC_CNT、RTC_ALR或RTC_PRL已经被同步。
0：寄存器尚未被同步；
1：寄存器已经被同步。
*/
#define RTC_CRL_RSF_Pos             ((uint32_t)3)   /*bit position, 寄存器同步标志 (Registers synchronized flag)
每当RTC_CNT寄存器和RTC_DIV寄存器由软件更新或清’0’时，此位由硬件置’1’。在APB1复位后，或APB1时钟停止后，此位必须由软件清’0’。要进行任何的读操作之前，用户程序必须等待这位被硬件置’1’，以确保RTC_CNT、RTC_ALR或RTC_PRL已经被同步。
0：寄存器尚未被同步；
1：寄存器已经被同步。
*/
#define RTC_CRL_CNF_Msk             ((uint32_t)0x10)   /* bit mask, 配置标志 (Configuration flag)
此位必须由软件置’1’以进入配置模式，从而允许向RTC_CNT、RTC_ALR或RTC_PRL寄存器写入数据。只有当此位在被置’1’并重新由软件清’0’后，才会执行写操作。
0：退出配置模式(开始更新RTC寄存器)；
1：进入配置模式。
*/
#define RTC_CRL_CNF_Pos             ((uint32_t)4)   /*bit position, 配置标志 (Configuration flag)
此位必须由软件置’1’以进入配置模式，从而允许向RTC_CNT、RTC_ALR或RTC_PRL寄存器写入数据。只有当此位在被置’1’并重新由软件清’0’后，才会执行写操作。
0：退出配置模式(开始更新RTC寄存器)；
1：进入配置模式。
*/
#define RTC_CRL_RTOFF_Msk             ((uint32_t)0x20)   /* bit mask, RTC操作关闭 (RTC operation OFF)
RTC模块利用这位来指示对其寄存器进行的最后一次操作的状态，指示操作是否完成。若此位为’0’，则表示无法对任何的RTC寄存器进行写操作。此位为只读位。
0：上一次对RTC寄存器的写操作仍在进行;
1：上一次对RTC寄存器的写操作已经完成。
*/
#define RTC_CRL_RTOFF_Pos             ((uint32_t)5)   /*bit position, RTC操作关闭 (RTC operation OFF)
RTC模块利用这位来指示对其寄存器进行的最后一次操作的状态，指示操作是否完成。若此位为’0’，则表示无法对任何的RTC寄存器进行写操作。此位为只读位。
0：上一次对RTC寄存器的写操作仍在进行;
1：上一次对RTC寄存器的写操作已经完成。
*/

/******************  Bit Definition for Register RTC_PRLH  *********************/
#define RTC_PRLH_PRLH_Msk             ((uint32_t)0xf)   /* bit mask, RTC预分频装载值高位 (RTC prescaler reload value high)
根据以下公式，这些位用来定义计数器的时钟频率：
fTR_CLK = fRTCCLK/(PRL[19:0]+1)
注：不推荐使用0值，否则无法正确的产生RTC中断和标志位。
*/
#define RTC_PRLH_PRLH_Pos             ((uint32_t)0)   /*bit position, RTC预分频装载值高位 (RTC prescaler reload value high)
根据以下公式，这些位用来定义计数器的时钟频率：
fTR_CLK = fRTCCLK/(PRL[19:0]+1)
注：不推荐使用0值，否则无法正确的产生RTC中断和标志位。
*/

/******************  Bit Definition for Register RTC_PRLL  *********************/
#define RTC_PRLL_PRLL_Msk             ((uint32_t)0xffff)   /* bit mask, RTC预分频装载值低位
根据以下公式，这些位用来定义计数器的时钟频率：
fTR_CLK = fRTCCLK/(PRL[19:0]+1)
*/
#define RTC_PRLL_PRLL_Pos             ((uint32_t)0)   /*bit position, RTC预分频装载值低位
根据以下公式，这些位用来定义计数器的时钟频率：
fTR_CLK = fRTCCLK/(PRL[19:0]+1)
*/

/******************  Bit Definition for Register RTC_DIVH  *********************/
#define RTC_DIVH_RTC_DIVH_Msk             ((uint32_t)0xf)   /* bit mask, RTC时钟分频器余数高位 (RTC clock divider high)*/
#define RTC_DIVH_RTC_DIVH_Pos             ((uint32_t)0)   /*bit position, RTC时钟分频器余数高位 (RTC clock divider high)*/

/******************  Bit Definition for Register RTC_DIVL  *********************/
#define RTC_DIVL_RTC_DIVL_Msk             ((uint32_t)0xffff)   /* bit mask, RTC时钟分频器余数低位 (RTC clock divider low)*/
#define RTC_DIVL_RTC_DIVL_Pos             ((uint32_t)0)   /*bit position, RTC时钟分频器余数低位 (RTC clock divider low)*/

/******************  Bit Definition for Register RTC_CNTH  *********************/
#define RTC_CNTH_RTC_CNTH_Msk             ((uint32_t)0xffff)   /* bit mask, RTC计数器高位 (RTC counter high)
可通过读RTC_CNTH寄存器来获得RTC计数器当前值的高位部分。要对此寄存器进行写操作前，必须先进入配置模式
*/
#define RTC_CNTH_RTC_CNTH_Pos             ((uint32_t)0)   /*bit position, RTC计数器高位 (RTC counter high)
可通过读RTC_CNTH寄存器来获得RTC计数器当前值的高位部分。要对此寄存器进行写操作前，必须先进入配置模式
*/

/******************  Bit Definition for Register RTC_CNTL  *********************/
#define RTC_CNTL_RTC_CNTL_Msk             ((uint32_t)0xffff)   /* bit mask, RTC计数器低位。
可通过读RTC_CNTL寄存器来获得RTC计数器当前值的低位部分。要对此寄存器进行写操作， 必须先进入配置模式
*/
#define RTC_CNTL_RTC_CNTL_Pos             ((uint32_t)0)   /*bit position, RTC计数器低位。
可通过读RTC_CNTL寄存器来获得RTC计数器当前值的低位部分。要对此寄存器进行写操作， 必须先进入配置模式
*/

/******************  Bit Definition for Register RTC_ALRH  *********************/
#define RTC_ALRH_RTC_ALRH_Msk             ((uint32_t)0xffff)   /* bit mask, RTC闹钟值高位 (RTC alarm high)
此寄存器用来保存由软件写入的闹钟时间的高位部分。要对此寄存器进行写操作，必须先进入配置模式。
*/
#define RTC_ALRH_RTC_ALRH_Pos             ((uint32_t)0)   /*bit position, RTC闹钟值高位 (RTC alarm high)
此寄存器用来保存由软件写入的闹钟时间的高位部分。要对此寄存器进行写操作，必须先进入配置模式。
*/

/******************  Bit Definition for Register RTC_ALRL  *********************/
#define RTC_ALRL_RTC_ALRL_Msk             ((uint32_t)0xffff)   /* bit mask, RTC闹钟值低位 (RTC alarm low)
此寄存器用来保存由软件写入的闹钟时间的低位部分。要对此寄存器进行写操作，必须先进入配置模式。
*/
#define RTC_ALRL_RTC_ALRL_Pos             ((uint32_t)0)   /*bit position, RTC闹钟值低位 (RTC alarm low)
此寄存器用来保存由软件写入的闹钟时间的低位部分。要对此寄存器进行写操作，必须先进入配置模式。
*/

/******************************************************************************/
/*                    IWDG                         */
/******************************************************************************/


/******************  Bit Definition for Register IWDG_KR  *********************/
#define IWDG_KR_KEY_Msk             ((uint32_t)0xffff)   /* bit mask, 键值(只写寄存器，读出值为0x0000) (Key value)
软件必须以一定的间隔写入0xAAAA，否则，当计数器为0时，看门狗会产生复位。写入0x5555表示允许访问IWDG_PR和IWDG_RLR寄存器。*/
#define IWDG_KR_KEY_Pos             ((uint32_t)0)   /*bit position, 键值(只写寄存器，读出值为0x0000) (Key value)
软件必须以一定的间隔写入0xAAAA，否则，当计数器为0时，看门狗会产生复位。写入0x5555表示允许访问IWDG_PR和IWDG_RLR寄存器。*/

/******************  Bit Definition for Register IWDG_PR  *********************/
#define IWDG_PR_PR_Msk             ((uint32_t)0x7)   /* bit mask, 预分频因子 (Prescaler divider)
这些位具有写保护设置，参见17.3.2节。通过设置这些位来选择计数器时钟的预分频因子。要改变预分频因子，IWDG_SR寄存器的PVU位必须为0。
000: 预分频因子=4    100: 预分频因子=64
001: 预分频因子=8    101: 预分频因子=128
010: 预分频因子=16    110: 预分频因子=256
011: 预分频因子=32    111: 预分频因子=256
注意：对此寄存器进行读操作，将从VDD电压域返回预分频值。如果写操作正在进行，则读回的值可能是无效的。因此，只有当IWDG_SR寄存器的PVU位为0时，读出的值才有效。*/
#define IWDG_PR_PR_Pos             ((uint32_t)0)   /*bit position, 预分频因子 (Prescaler divider)
这些位具有写保护设置，参见17.3.2节。通过设置这些位来选择计数器时钟的预分频因子。要改变预分频因子，IWDG_SR寄存器的PVU位必须为0。
000: 预分频因子=4    100: 预分频因子=64
001: 预分频因子=8    101: 预分频因子=128
010: 预分频因子=16    110: 预分频因子=256
011: 预分频因子=32    111: 预分频因子=256
注意：对此寄存器进行读操作，将从VDD电压域返回预分频值。如果写操作正在进行，则读回的值可能是无效的。因此，只有当IWDG_SR寄存器的PVU位为0时，读出的值才有效。*/

/******************  Bit Definition for Register IWDG_RLR  *********************/
#define IWDG_RLR_RL_Msk             ((uint32_t)0xfff)   /* bit mask, 看门狗计数器重装载值 (Watchdog counter reload value)
这些位具有写保护功能。用于定义看门狗计数器的重装载值，每当向IWDG_KR 寄存器写入0xAAAA时，重装载值会被传送到计数器中。随后计数器从这个值开始递减计数。看门狗超时周期可通过此重装载值和时钟预分频值来计算，参照表83。
只有当IWDG_SR寄存器中的RVU位为0时，才能对此寄存器进行修改。
注：对此寄存器进行读操作，将从VDD电压域返回预分频值。如果写操作正在进行，则读回的值可能是无效的。因此，只有当IWDG_SR寄存器的RVU位为0时，读出的值才有效。*/
#define IWDG_RLR_RL_Pos             ((uint32_t)0)   /*bit position, 看门狗计数器重装载值 (Watchdog counter reload value)
这些位具有写保护功能。用于定义看门狗计数器的重装载值，每当向IWDG_KR 寄存器写入0xAAAA时，重装载值会被传送到计数器中。随后计数器从这个值开始递减计数。看门狗超时周期可通过此重装载值和时钟预分频值来计算，参照表83。
只有当IWDG_SR寄存器中的RVU位为0时，才能对此寄存器进行修改。
注：对此寄存器进行读操作，将从VDD电压域返回预分频值。如果写操作正在进行，则读回的值可能是无效的。因此，只有当IWDG_SR寄存器的RVU位为0时，读出的值才有效。*/

/******************  Bit Definition for Register IWDG_SR  *********************/
#define IWDG_SR_PVU_Msk             ((uint32_t)0x1)   /* bit mask, 看门狗预分频值更新 (Watchdog prescaler value update)
此位由硬件置’1’用来指示预分频值的更新正在进行中。当在VDD域中的预分频值更新结束后， 此位由硬件清’0’(最多需5个40kHz的RC周期)。预分频值只有在PVU位被清’0’后才可更新。
如果在应用程序中使用了多个重装载值或预分频值，则必须在RVU位被清除后才能重新改变预装载值，在PVU位被清除后才能重新改变预分频值。然而，在预分频和/或重装值更新后，不 必等待RVU或PVU复位，可继续执行下面的代码。*/
#define IWDG_SR_PVU_Pos             ((uint32_t)0)   /*bit position, 看门狗预分频值更新 (Watchdog prescaler value update)
此位由硬件置’1’用来指示预分频值的更新正在进行中。当在VDD域中的预分频值更新结束后， 此位由硬件清’0’(最多需5个40kHz的RC周期)。预分频值只有在PVU位被清’0’后才可更新。
如果在应用程序中使用了多个重装载值或预分频值，则必须在RVU位被清除后才能重新改变预装载值，在PVU位被清除后才能重新改变预分频值。然而，在预分频和/或重装值更新后，不 必等待RVU或PVU复位，可继续执行下面的代码。*/
#define IWDG_SR_RVU_Msk             ((uint32_t)0x2)   /* bit mask, 看门狗计数器重装载值更新 (Watchdog counter reload value update)
此位由硬件置’1’用来指示重装载值的更新正在进行中。当在VDD域中的重装载更新结束后，此位由硬件清’0’(最多需5个40kHz的RC周期)。重装载值只有在RVU位被清’0’后才可更新。
如果在应用程序中使用了多个重装载值或预分频值，则必须在RVU位被清除后才能重新改变预装载值，在PVU位被清除后才能重新改变预分频值。然而，在预分频和/或重装值更新后，不 必等待RVU或PVU复位，可继续执行下面的代码。*/
#define IWDG_SR_RVU_Pos             ((uint32_t)1)   /*bit position, 看门狗计数器重装载值更新 (Watchdog counter reload value update)
此位由硬件置’1’用来指示重装载值的更新正在进行中。当在VDD域中的重装载更新结束后，此位由硬件清’0’(最多需5个40kHz的RC周期)。重装载值只有在RVU位被清’0’后才可更新。
如果在应用程序中使用了多个重装载值或预分频值，则必须在RVU位被清除后才能重新改变预装载值，在PVU位被清除后才能重新改变预分频值。然而，在预分频和/或重装值更新后，不 必等待RVU或PVU复位，可继续执行下面的代码。*/

/******************  Bit Definition for Register IWDG_EN  *********************/
#define IWDG_EN_IWDG_AUTO_EN_Msk             ((uint32_t)0x1)   /* bit mask, 上电默认启动看门狗，可在IWDG_LOCK为0的前提下改写该位为0关闭看门狗的运行*/
#define IWDG_EN_IWDG_AUTO_EN_Pos             ((uint32_t)0)   /*bit position, 上电默认启动看门狗，可在IWDG_LOCK为0的前提下改写该位为0关闭看门狗的运行*/

/******************  Bit Definition for Register IWDG_LOCK  *********************/
#define IWDG_LOCK_IWDG_LOCK_Msk             ((uint32_t)0x1)   /* bit mask, 当写该位为1时，WDG_PR 、IWDG_RLR、IWDG_EN 三个寄存器不可被改写。只有任意复位源才能将该位复位到0.*/
#define IWDG_LOCK_IWDG_LOCK_Pos             ((uint32_t)0)   /*bit position, 当写该位为1时，WDG_PR 、IWDG_RLR、IWDG_EN 三个寄存器不可被改写。只有任意复位源才能将该位复位到0.*/

/******************************************************************************/
/*                    SPI                         */
/******************************************************************************/


/******************  Bit Definition for Register CR1  *********************/
#define SPI_CR1_CPHA_Msk             ((uint32_t)0x1)   /* bit mask, CPHA：时钟相位 (Clock phase)
0： 数据采样从第一个时钟边沿开始；
1： 数据采样从第二个时钟边沿开始。
注：当通信正在进行的时候，不能修改该位。*/
#define SPI_CR1_CPHA_Pos             ((uint32_t)0)   /*bit position, CPHA：时钟相位 (Clock phase)
0： 数据采样从第一个时钟边沿开始；
1： 数据采样从第二个时钟边沿开始。
注：当通信正在进行的时候，不能修改该位。*/
#define SPI_CR1_CPOL_Msk             ((uint32_t)0x2)   /* bit mask, CPOL：时钟极性 (Clock polarity) 0： 空闲状态时，SCK保持低电平；
1： 空闲状态时，SCK保持高电平。
注：当通信正在进行的时候，不能修改该位。*/
#define SPI_CR1_CPOL_Pos             ((uint32_t)1)   /*bit position, CPOL：时钟极性 (Clock polarity) 0： 空闲状态时，SCK保持低电平；
1： 空闲状态时，SCK保持高电平。
注：当通信正在进行的时候，不能修改该位。*/
#define SPI_CR1_MSTR_Msk             ((uint32_t)0x4)   /* bit mask, MSTR：主设备选择 (Master selection) 0：配置为从设备；
1：配置为主设备。
注：当通信正在进行的时候，不能修改该位。*/
#define SPI_CR1_MSTR_Pos             ((uint32_t)2)   /*bit position, MSTR：主设备选择 (Master selection) 0：配置为从设备；
1：配置为主设备。
注：当通信正在进行的时候，不能修改该位。*/
#define SPI_CR1_BR_Msk             ((uint32_t)0x38)   /* bit mask, BR[2:0]：波特率控制 (Baud rate control)
000： fPCLK/2    001： fPCLK/4    010： fPCLK/8    011： fPCLK/16
100： fPCLK/32    101： fPCLK/64    110： fPCLK/128    111： fPCLK/256
当通信正在进行的时候，不能修改这些位。*/
#define SPI_CR1_BR_Pos             ((uint32_t)3)   /*bit position, BR[2:0]：波特率控制 (Baud rate control)
000： fPCLK/2    001： fPCLK/4    010： fPCLK/8    011： fPCLK/16
100： fPCLK/32    101： fPCLK/64    110： fPCLK/128    111： fPCLK/256
当通信正在进行的时候，不能修改这些位。*/
#define SPI_CR1_SPE_Msk             ((uint32_t)0x40)   /* bit mask, SPE：SPI使能 (SPI enable) 0：禁止SPI设备；
1：开启SPI设备。
*/
#define SPI_CR1_SPE_Pos             ((uint32_t)6)   /*bit position, SPE：SPI使能 (SPI enable) 0：禁止SPI设备；
1：开启SPI设备。
*/
#define SPI_CR1_LSBFIRST_Msk             ((uint32_t)0x80)   /* bit mask, LSBFIRST：帧格式 (Frame format) 0：先发送MSB；
1：先发送LSB。
注：当通信在进行时不能改变该位的值。*/
#define SPI_CR1_LSBFIRST_Pos             ((uint32_t)7)   /*bit position, LSBFIRST：帧格式 (Frame format) 0：先发送MSB；
1：先发送LSB。
注：当通信在进行时不能改变该位的值。*/
#define SPI_CR1_SSI_Msk             ((uint32_t)0x100)   /* bit mask, SSI：内部从设备选择 (Internal slave select)
该位只在SSM位为’1’时有意义。它决定了NSS上的电平，在NSS引脚上的I/O操作无效。*/
#define SPI_CR1_SSI_Pos             ((uint32_t)8)   /*bit position, SSI：内部从设备选择 (Internal slave select)
该位只在SSM位为’1’时有意义。它决定了NSS上的电平，在NSS引脚上的I/O操作无效。*/
#define SPI_CR1_SSM_Msk             ((uint32_t)0x200)   /* bit mask, SSM：软件从设备管理 (Software slave management) 当SSM被置位时，NSS引脚上的电平由SSI位的值决定。 0：禁止软件从设备管理；
1：启用软件从设备管理。
*/
#define SPI_CR1_SSM_Pos             ((uint32_t)9)   /*bit position, SSM：软件从设备管理 (Software slave management) 当SSM被置位时，NSS引脚上的电平由SSI位的值决定。 0：禁止软件从设备管理；
1：启用软件从设备管理。
*/
#define SPI_CR1_RXONLY_Msk             ((uint32_t)0x400)   /* bit mask, RXONLY：只接收 (Receive only)
该位和BIDIMODE位一起决定在“双线双向”模式下的传输方向。在多个从设备的配置中，在未被访问的从设备上该位被置1，使得只有被访问的从设备有输出，从而不会造成数据线上数据冲突。
0：全双工(发送和接收)；
1：禁止输出(只接收模式)。*/
#define SPI_CR1_RXONLY_Pos             ((uint32_t)10)   /*bit position, RXONLY：只接收 (Receive only)
该位和BIDIMODE位一起决定在“双线双向”模式下的传输方向。在多个从设备的配置中，在未被访问的从设备上该位被置1，使得只有被访问的从设备有输出，从而不会造成数据线上数据冲突。
0：全双工(发送和接收)；
1：禁止输出(只接收模式)。*/
#define SPI_CR1_DFF_Msk             ((uint32_t)0x800)   /* bit mask, DFF：数据帧格式 (Data frame format) 0：使用8位数据帧格式进行发送/接收；
1：使用16位数据帧格式进行发送/接收。
注：只有当SPI禁止(SPE=0)时，才能写该位，否则出错。*/
#define SPI_CR1_DFF_Pos             ((uint32_t)11)   /*bit position, DFF：数据帧格式 (Data frame format) 0：使用8位数据帧格式进行发送/接收；
1：使用16位数据帧格式进行发送/接收。
注：只有当SPI禁止(SPE=0)时，才能写该位，否则出错。*/
#define SPI_CR1_CRCNEXT_Msk             ((uint32_t)0x1000)   /* bit mask, CRCNEXT：下一个发送CRC (Transmit CRC next) 0：下一个发送的值来自发送缓冲区。
1：下一个发送的值来自发送CRC寄存器。
注：在SPI_DR寄存器写入最后一个数据后应马上设置该位。*/
#define SPI_CR1_CRCNEXT_Pos             ((uint32_t)12)   /*bit position, CRCNEXT：下一个发送CRC (Transmit CRC next) 0：下一个发送的值来自发送缓冲区。
1：下一个发送的值来自发送CRC寄存器。
注：在SPI_DR寄存器写入最后一个数据后应马上设置该位。*/
#define SPI_CR1_CRCEN_Msk             ((uint32_t)0x2000)   /* bit mask, CRCEN：硬件CRC校验使能 (Hardware CRC calculation enable) 0：禁止CRC计算；
1：启动CRC计算。
注：只有在禁止SPI时(SPE=0)，才能写该位，否则出错。该位只能在全双工模式下使用。
*/
#define SPI_CR1_CRCEN_Pos             ((uint32_t)13)   /*bit position, CRCEN：硬件CRC校验使能 (Hardware CRC calculation enable) 0：禁止CRC计算；
1：启动CRC计算。
注：只有在禁止SPI时(SPE=0)，才能写该位，否则出错。该位只能在全双工模式下使用。
*/
#define SPI_CR1_BIDIOE_Msk             ((uint32_t)0x4000)   /* bit mask, BIDIOE：双向模式下的输出使能 (Output enable in bidirectional mode)和BIDIMODE位一起决定在“单线双向”模式下数据的输出方向  0：输出禁止(只收模式)；
1：输出使能(只发模式)。
这个“单线”数据线在主设备端为MOSI引脚，在从设备端为MISO引脚。*/
#define SPI_CR1_BIDIOE_Pos             ((uint32_t)14)   /*bit position, BIDIOE：双向模式下的输出使能 (Output enable in bidirectional mode)和BIDIMODE位一起决定在“单线双向”模式下数据的输出方向  0：输出禁止(只收模式)；
1：输出使能(只发模式)。
这个“单线”数据线在主设备端为MOSI引脚，在从设备端为MISO引脚。*/
#define SPI_CR1_BIDIMODE_Msk             ((uint32_t)0x8000)   /* bit mask, BIDIMODE：双向数据模式使能 (Bidirectional data mode enable) 0：选择“双线双向”模式；
1：选择“单线双向”模式。
*/
#define SPI_CR1_BIDIMODE_Pos             ((uint32_t)15)   /*bit position, BIDIMODE：双向数据模式使能 (Bidirectional data mode enable) 0：选择“双线双向”模式；
1：选择“单线双向”模式。
*/

/******************  Bit Definition for Register CR2  *********************/
#define SPI_CR2_RXDMAEN_Msk             ((uint32_t)0x1)   /* bit mask, RXDMAEN：接收缓冲区DMA使能 (Rx buffer DMA enable)当该位被设置时，RXNE标志一旦被置位就发出DMA请求 0：禁止接收缓冲区DMA；
1：启动接收缓冲区DMA。
*/
#define SPI_CR2_RXDMAEN_Pos             ((uint32_t)0)   /*bit position, RXDMAEN：接收缓冲区DMA使能 (Rx buffer DMA enable)当该位被设置时，RXNE标志一旦被置位就发出DMA请求 0：禁止接收缓冲区DMA；
1：启动接收缓冲区DMA。
*/
#define SPI_CR2_TXDMAEN_Msk             ((uint32_t)0x2)   /* bit mask, TXDMAEN：发送缓冲区DMA使能 (Tx buffer DMA enable)当该位被设置时，TXE标志一旦被置位就发出DMA请求 0：禁止发送缓冲区DMA；
1：启动发送缓冲区DMA。
*/
#define SPI_CR2_TXDMAEN_Pos             ((uint32_t)1)   /*bit position, TXDMAEN：发送缓冲区DMA使能 (Tx buffer DMA enable)当该位被设置时，TXE标志一旦被置位就发出DMA请求 0：禁止发送缓冲区DMA；
1：启动发送缓冲区DMA。
*/
#define SPI_CR2_SSOE_Msk             ((uint32_t)0x4)   /* bit mask, SSOE：SS输出使能   (SS    output    enable) 0：禁止在主模式下SS输出，该设备可以工作在多主设备模式；
1：设备开启时，开启主模式下SS输出，该设备不能工作在多主设备模式。
*/
#define SPI_CR2_SSOE_Pos             ((uint32_t)2)   /*bit position, SSOE：SS输出使能   (SS    output    enable) 0：禁止在主模式下SS输出，该设备可以工作在多主设备模式；
1：设备开启时，开启主模式下SS输出，该设备不能工作在多主设备模式。
*/
#define SPI_CR2_ERRIR_Msk             ((uint32_t)0x20)   /* bit mask, ERRIR：错误中断使能 (Error interrupt enable)
当错误(CRCERR、OVR、MODF)产生时，该位控制是否产生中断
0：禁止错误中断；
1：允许错误中断。
*/
#define SPI_CR2_ERRIR_Pos             ((uint32_t)5)   /*bit position, ERRIR：错误中断使能 (Error interrupt enable)
当错误(CRCERR、OVR、MODF)产生时，该位控制是否产生中断
0：禁止错误中断；
1：允许错误中断。
*/
#define SPI_CR2_RXNEIE_Msk             ((uint32_t)0x40)   /* bit mask, RXNEIE：接收缓冲区非空中断使能 (RX buffer not empty interrupt enable) 0：禁止RXNE中断；
1：允许RXNE中断，当RXNE标志置位时产生中断请求。
*/
#define SPI_CR2_RXNEIE_Pos             ((uint32_t)6)   /*bit position, RXNEIE：接收缓冲区非空中断使能 (RX buffer not empty interrupt enable) 0：禁止RXNE中断；
1：允许RXNE中断，当RXNE标志置位时产生中断请求。
*/
#define SPI_CR2_TXEIE_Msk             ((uint32_t)0x80)   /* bit mask, TXEIE：发送缓冲区空中断使能 (Tx buffer empty interrupt enable) 0：禁止TXE中断；
1：允许TXE中断，当TXE标志置位为’1’时产生中断请求。
*/
#define SPI_CR2_TXEIE_Pos             ((uint32_t)7)   /*bit position, TXEIE：发送缓冲区空中断使能 (Tx buffer empty interrupt enable) 0：禁止TXE中断；
1：允许TXE中断，当TXE标志置位为’1’时产生中断请求。
*/

/******************  Bit Definition for Register SR  *********************/
#define SPI_SR_RXNE_Msk             ((uint32_t)0x1)   /* bit mask, RXNE：接收缓冲非空 (Receive buffer not empty) 0：接收缓冲为空；
1：接收缓冲非空。
*/
#define SPI_SR_RXNE_Pos             ((uint32_t)0)   /*bit position, RXNE：接收缓冲非空 (Receive buffer not empty) 0：接收缓冲为空；
1：接收缓冲非空。
*/
#define SPI_SR_TXE_Msk             ((uint32_t)0x2)   /* bit mask, TXE：发送缓冲为空 (Transmit buffer empty) 0：发送缓冲非空；
1：发送缓冲为空。
*/
#define SPI_SR_TXE_Pos             ((uint32_t)1)   /*bit position, TXE：发送缓冲为空 (Transmit buffer empty) 0：发送缓冲非空；
1：发送缓冲为空。
*/
#define SPI_SR_CHSIDE_Msk             ((uint32_t)0x4)   /* bit mask, Reserved*/
#define SPI_SR_CHSIDE_Pos             ((uint32_t)2)   /*bit position, Reserved*/
#define SPI_SR_UDR_Msk             ((uint32_t)0x8)   /* bit mask, Reserved*/
#define SPI_SR_UDR_Pos             ((uint32_t)3)   /*bit position, Reserved*/
#define SPI_SR_CRCERR_Msk             ((uint32_t)0x10)   /* bit mask, CRCERR：CRC错误标志  (CRC  error  flag) 0：收到的CRC值和SPI_RXCRCR寄存器中的值匹配；
1：收到的CRC值和SPI_RXCRCR寄存器中的值不匹配。该位由硬件置位，由软件写’0’而复位。
*/
#define SPI_SR_CRCERR_Pos             ((uint32_t)4)   /*bit position, CRCERR：CRC错误标志  (CRC  error  flag) 0：收到的CRC值和SPI_RXCRCR寄存器中的值匹配；
1：收到的CRC值和SPI_RXCRCR寄存器中的值不匹配。该位由硬件置位，由软件写’0’而复位。
*/
#define SPI_SR_MODF_Msk             ((uint32_t)0x20)   /* bit mask, MODF：模式错误 (Mode fault) 0：没有出现模式错误；
1：出现模式错误。
该位由硬件置位，由软件序列复位。*/
#define SPI_SR_MODF_Pos             ((uint32_t)5)   /*bit position, MODF：模式错误 (Mode fault) 0：没有出现模式错误；
1：出现模式错误。
该位由硬件置位，由软件序列复位。*/
#define SPI_SR_OVR_Msk             ((uint32_t)0x40)   /* bit mask, OVR：溢出标志 (Overrun flag) 0：没有出现溢出错误；
1：出现溢出错误。
该位由硬件置位，由软件序列复位。
*/
#define SPI_SR_OVR_Pos             ((uint32_t)6)   /*bit position, OVR：溢出标志 (Overrun flag) 0：没有出现溢出错误；
1：出现溢出错误。
该位由硬件置位，由软件序列复位。
*/
#define SPI_SR_BSY_Msk             ((uint32_t)0x80)   /* bit mask, BSY：忙标志 (Busy flag) 0：SPI不忙；
1：SPI正忙于通信，或者发送缓冲非空。该位由硬件置位或者复位。
注：使用这个标志时需要特别注意
*/
#define SPI_SR_BSY_Pos             ((uint32_t)7)   /*bit position, BSY：忙标志 (Busy flag) 0：SPI不忙；
1：SPI正忙于通信，或者发送缓冲非空。该位由硬件置位或者复位。
注：使用这个标志时需要特别注意
*/

/******************  Bit Definition for Register DR  *********************/
#define SPI_DR_DR_Msk             ((uint32_t)0xffff)   /* bit mask, DR[15:0]：数据寄存器 (Data register)
待发送或者已经收到的数据
数据寄存器对应两个缓冲区：一个用于写(发送缓冲)；另外一个用于读(接收缓冲)。写操作将数据写到发送缓冲区；读操作将返回接收缓冲区里的数据。
对SPI模式的注释：根据SPI_CR1的DFF位对数据帧格式的选择，数据的发送和接收可以是8位或者16位的。为保证正确的操作，需要在启用SPI之前就确定好数据帧格式。
对于8位的数据，缓冲器是8位的，发送和接收时只会用到SPI_DR[7:0]。在接收时，
SPI_DR[15:8]被强制为0。
对于16位的数据，缓冲器是16位的，发送和接收时会用到整个数据寄存器，即SPI_DR[15:0]。
*/
#define SPI_DR_DR_Pos             ((uint32_t)0)   /*bit position, DR[15:0]：数据寄存器 (Data register)
待发送或者已经收到的数据
数据寄存器对应两个缓冲区：一个用于写(发送缓冲)；另外一个用于读(接收缓冲)。写操作将数据写到发送缓冲区；读操作将返回接收缓冲区里的数据。
对SPI模式的注释：根据SPI_CR1的DFF位对数据帧格式的选择，数据的发送和接收可以是8位或者16位的。为保证正确的操作，需要在启用SPI之前就确定好数据帧格式。
对于8位的数据，缓冲器是8位的，发送和接收时只会用到SPI_DR[7:0]。在接收时，
SPI_DR[15:8]被强制为0。
对于16位的数据，缓冲器是16位的，发送和接收时会用到整个数据寄存器，即SPI_DR[15:0]。
*/

/******************  Bit Definition for Register CRCPR  *********************/
#define SPI_CRCPR_CRCPOLY_Msk             ((uint32_t)0xffff)   /* bit mask, CRCPOLY[15:0]：CRC多项式寄存器 (CRC polynomial register)
该寄存器包含了CRC计算时用到的多项式。
其复位值为0x0007，根据应用可以设置其他数值。*/
#define SPI_CRCPR_CRCPOLY_Pos             ((uint32_t)0)   /*bit position, CRCPOLY[15:0]：CRC多项式寄存器 (CRC polynomial register)
该寄存器包含了CRC计算时用到的多项式。
其复位值为0x0007，根据应用可以设置其他数值。*/

/******************  Bit Definition for Register RXCRCR  *********************/
#define SPI_RXCRCR_RXCRC_Msk             ((uint32_t)0xffff)   /* bit mask, RXCRC[15:0]：接收CRC寄存器
在启用CRC计算时，RXCRC[15:0]中包含了依据收到的字节计算的CRC数值。当在SPI_CR1的CRCEN位写入’1’时，该寄存器被复位。CRC计算使用SPI_CRCPR中的多项式。
当数据帧格式被设置为8位时，仅低8位参与计算，并且按照CRC8的方法进行；当数据帧格式为16位时，寄存器中的所有16位都参与计算，并且按照CRC16的标准。
注：当BSY标志为’1’时读该寄存器，将可能读到不正确的数值。*/
#define SPI_RXCRCR_RXCRC_Pos             ((uint32_t)0)   /*bit position, RXCRC[15:0]：接收CRC寄存器
在启用CRC计算时，RXCRC[15:0]中包含了依据收到的字节计算的CRC数值。当在SPI_CR1的CRCEN位写入’1’时，该寄存器被复位。CRC计算使用SPI_CRCPR中的多项式。
当数据帧格式被设置为8位时，仅低8位参与计算，并且按照CRC8的方法进行；当数据帧格式为16位时，寄存器中的所有16位都参与计算，并且按照CRC16的标准。
注：当BSY标志为’1’时读该寄存器，将可能读到不正确的数值。*/

/******************  Bit Definition for Register TXCRCR  *********************/
#define SPI_TXCRCR_TXCRC_Msk             ((uint32_t)0xffff)   /* bit mask, TxCRC[15:0]：发送CRC寄存器
在启用CRC计算时，TXCRC[15:0]中包含了依据将要发送的字节计算的CRC数值。当在 SPI_CR1中的CRCEN位写入’1’时，该寄存器被复位。CRC计算使用SPI_CRCPR中的多项式。
当数据帧格式被设置为8位时，仅低8位参与计算，并且按照CRC8的方法进行；当数据帧格式为16位时，寄存器中的所有16个位都参与计算，并且按照CRC16的标准。
注：当BSY标志为’1’时读该寄存器，将可能读到不正确的数值。*/
#define SPI_TXCRCR_TXCRC_Pos             ((uint32_t)0)   /*bit position, TxCRC[15:0]：发送CRC寄存器
在启用CRC计算时，TXCRC[15:0]中包含了依据将要发送的字节计算的CRC数值。当在 SPI_CR1中的CRCEN位写入’1’时，该寄存器被复位。CRC计算使用SPI_CRCPR中的多项式。
当数据帧格式被设置为8位时，仅低8位参与计算，并且按照CRC8的方法进行；当数据帧格式为16位时，寄存器中的所有16个位都参与计算，并且按照CRC16的标准。
注：当BSY标志为’1’时读该寄存器，将可能读到不正确的数值。*/

/******************************************************************************/
/*                    FLASH                         */
/******************************************************************************/


/******************  Bit Definition for Register CTRL  *********************/
#define FLASH_CTRL_PROGRAM_EN_Msk             ((uint32_t)0x1)   /* bit mask, 编程操作前配置该bit为1，编程完成后需要再配置该bit为0*/
#define FLASH_CTRL_PROGRAM_EN_Pos             ((uint32_t)0)   /*bit position, 编程操作前配置该bit为1，编程完成后需要再配置该bit为0*/
#define FLASH_CTRL_CMD_DONE_INT_EN_Msk             ((uint32_t)0x2)   /* bit mask, 命令结束中断使能*/
#define FLASH_CTRL_CMD_DONE_INT_EN_Pos             ((uint32_t)1)   /*bit position, 命令结束中断使能*/
#define FLASH_CTRL_PG_DONE_INT_EN_Msk             ((uint32_t)0x4)   /* bit mask, 编程结束中断使能*/
#define FLASH_CTRL_PG_DONE_INT_EN_Pos             ((uint32_t)2)   /*bit position, 编程结束中断使能*/
#define FLASH_CTRL_ERR_INT_EN_Msk             ((uint32_t)0x8)   /* bit mask, 写入或者擦除受保护区域错误中断使能*/
#define FLASH_CTRL_ERR_INT_EN_Pos             ((uint32_t)3)   /*bit position, 写入或者擦除受保护区域错误中断使能*/
#define FLASH_CTRL_DEEP_SLEEP_AUTO_Msk             ((uint32_t)0x20)   /* bit mask, 如果CPU进入睡眠模式，FLASH也自动进入deep sleep模式*/
#define FLASH_CTRL_DEEP_SLEEP_AUTO_Pos             ((uint32_t)5)   /*bit position, 如果CPU进入睡眠模式，FLASH也自动进入deep sleep模式*/
#define FLASH_CTRL_RESERVED_Msk             ((uint32_t)0x40)   /* bit mask, 保留*/
#define FLASH_CTRL_RESERVED_Pos             ((uint32_t)6)   /*bit position, 保留*/
#define FLASH_CTRL_JTAG_DEBUG_EN_Msk             ((uint32_t)0x80)   /* bit mask, 使能swd接口，该bit可被CONFIG字初始化*/
#define FLASH_CTRL_JTAG_DEBUG_EN_Pos             ((uint32_t)7)   /*bit position, 使能swd接口，该bit可被CONFIG字初始化*/
#define FLASH_CTRL_CACHE_EN_Msk             ((uint32_t)0x100)   /* bit mask, 0:使能cache  1：关闭cache*/
#define FLASH_CTRL_CACHE_EN_Pos             ((uint32_t)8)   /*bit position, 0:使能cache  1：关闭cache*/

/******************  Bit Definition for Register CMD  *********************/
#define FLASH_CMD_CMD_Msk             ((uint32_t)0x1f)   /* bit mask, 命令完成后，CMD自动清零*/
#define FLASH_CMD_CMD_Pos             ((uint32_t)0)   /*bit position, 命令完成后，CMD自动清零*/

/******************  Bit Definition for Register PAGE_ADDR0  *********************/
#define FLASH_PAGE_ADDR0_START_ADDR_Msk             ((uint32_t)0xffffffff)   /* bit mask, 配置为要擦除的页面的地址或者计算CRC签名的第一页面的地址，忽视该寄存器的低12位，一次擦除4KB的大小*/
#define FLASH_PAGE_ADDR0_START_ADDR_Pos             ((uint32_t)0)   /*bit position, 配置为要擦除的页面的地址或者计算CRC签名的第一页面的地址，忽视该寄存器的低12位，一次擦除4KB的大小*/


/******************  Bit Definition for Register STAT  *********************/
#define FLASH_STAT_CMDBUSY_Msk             ((uint32_t)0x10)   /* bit mask, */
#define FLASH_STAT_CMDBUSY_Pos             ((uint32_t)4)   /*bit position, */
#define FLASH_STAT_PGBUSY_Msk             ((uint32_t)0x20)   /* bit mask, */
#define FLASH_STAT_PGBUSY_Pos             ((uint32_t)5)   /*bit position, */
#define FLASH_STAT_CMDDONE_Msk             ((uint32_t)0x40)   /* bit mask, 擦除命令结束标志，读清*/
#define FLASH_STAT_CMDDONE_Pos             ((uint32_t)6)   /*bit position, 擦除命令结束标志，读清*/
#define FLASH_STAT_PGDONE_Msk             ((uint32_t)0x80)   /* bit mask, 编程结束标志，读清*/
#define FLASH_STAT_PGDONE_Pos             ((uint32_t)7)   /*bit position, 编程结束标志，读清*/
#define FLASH_STAT_WR_ERASE_ERROR_Msk             ((uint32_t)0x100)   /* bit mask, 写入或擦除受保护区域标志，读清*/
#define FLASH_STAT_WR_ERASE_ERROR_Pos             ((uint32_t)8)   /*bit position, 写入或擦除受保护区域标志，读清*/
#define FLASH_STAT_UPLD_VERIFYERR_Msk             ((uint32_t)0x800)   /* bit mask, 复位后INFO自动签名检查失败*/
#define FLASH_STAT_UPLD_VERIFYERR_Pos             ((uint32_t)11)   /*bit position, 复位后INFO自动签名检查失败*/
#define FLASH_STAT_RD_PERF_MODE_Msk             ((uint32_t)0x1000)   /* bit mask,CONFIG字初始化的读操作功耗模式*/
#define FLASH_STAT_RD_PERF_MODE_Pos             ((uint32_t)12)   /*bit position,CONFIG字初始化的读操作功耗模式*/
#define FLASH_STAT_FLASH_IN_DEEP_SLEEP_Msk             ((uint32_t)0x10000)   /* bit mask, */
#define FLASH_STAT_FLASH_IN_DEEP_SLEEP_Pos             ((uint32_t)16)   /*bit position, */

/******************  Bit Definition for Register USER_WR_PROT  *********************/
#define FLASH_USER_WR_PROT_USER_WRPROT_Msk             ((uint32_t)0xffffffff)   /* bit mask, 某位为0可以单独使能user空间某block的保护功能，每个block的大小=avail_flash_size/32。*/
#define FLASH_USER_WR_PROT_USER_WRPROT_Pos             ((uint32_t)0)   /*bit position, 某位为0可以单独使能user空间某block的保护功能，每个block的大小=avail_flash_size/32。*/


/******************  Bit Definition for Register USERKEY  *********************/
#define FLASH_USERKEY_FEEKEY_Msk             ((uint32_t)0xffffffff)   /* bit mask, 写入0x789A_0123可解锁userkey，命令完成userkey再次上锁*/
#define FLASH_USERKEY_FEEKEY_Pos             ((uint32_t)0)   /*bit position, 写入0x789A_0123可解锁userkey，命令完成userkey再次上锁*/

/******************************************************************************/
/*                    UART                         */
/******************************************************************************/


/******************  Bit Definition for Register RBR_THR_DLL  *********************/
#define UART_RBR_THR_DLL_RBR_Msk             ((uint32_t)0x1ff)   /* bit mask, 接收缓冲寄存器包含了接收到的数据字节 UART RX FIFO 当中最早接收到的字节。UART_9BIT_DATA_EN=0时，位宽是8位，UART_9BIT_DATA_EN=1时，位宽是9位*/
#define UART_RBR_THR_DLL_RBR_Pos             ((uint32_t)0)   /*bit position, 接收缓冲寄存器包含了接收到的数据字节 UART RX FIFO 当中最早接收到的字节。UART_9BIT_DATA_EN=0时，位宽是8位，UART_9BIT_DATA_EN=1时，位宽是9位*/

/******************  Bit Definition for Register IER_DLH  *********************/
#define UART_IER_DLH_ERBFI_Msk             ((uint32_t)0x1)   /* bit mask, ERBFI
接收数据可用中断使能 (Enable Receive Data Available Interrupt)

用于接收数据可用中断使能控制，以及字符超时中断控制（如果在 FIFO 模式并且 FIFO 使能），为第二优先级中断。
0：未使能

1：使能*/
#define UART_IER_DLH_ERBFI_Pos             ((uint32_t)0)   /*bit position, ERBFI
接收数据可用中断使能 (Enable Receive Data Available Interrupt)

用于接收数据可用中断使能控制，以及字符超时中断控制（如果在 FIFO 模式并且 FIFO 使能），为第二优先级中断。
0：未使能

1：使能*/
#define UART_IER_DLH_ETBEI_Msk             ((uint32_t)0x2)   /* bit mask, ETBEI
数据发送寄存器为空中断使能 (Enable Transmit Holding Register Empty Interrupt)

用于数据发送寄存器为空中断使能控制，为第三优先级中断。
0：未使能

1：使能*/
#define UART_IER_DLH_ETBEI_Pos             ((uint32_t)1)   /*bit position, ETBEI
数据发送寄存器为空中断使能 (Enable Transmit Holding Register Empty Interrupt)

用于数据发送寄存器为空中断使能控制，为第三优先级中断。
0：未使能

1：使能*/
#define UART_IER_DLH_ELSI_Msk             ((uint32_t)0x4)   /* bit mask, ELSI
接收线路状态中断使能 (Enable Receive Line Status Interrupt)

用于接收线路状态中断使能控制，为最高级中断。
0：未使能

1：使能*/
#define UART_IER_DLH_ELSI_Pos             ((uint32_t)2)   /*bit position, ELSI
接收线路状态中断使能 (Enable Receive Line Status Interrupt)

用于接收线路状态中断使能控制，为最高级中断。
0：未使能

1：使能*/
#define UART_IER_DLH_EDSSI_Msk             ((uint32_t)0x8)   /* bit mask, EDSSI
调制解调器状态中断使能 (Enable Modem Status Interrupt)

用于调制解调器状态 (MSR) 中断使能控制，为第四优先级中断。
0：未使能

1：使能*/
#define UART_IER_DLH_EDSSI_Pos             ((uint32_t)3)   /*bit position, EDSSI
调制解调器状态中断使能 (Enable Modem Status Interrupt)

用于调制解调器状态 (MSR) 中断使能控制，为第四优先级中断。
0：未使能

1：使能*/
#define UART_IER_DLH_ELCOLR_Msk             ((uint32_t)0x10)   /* bit mask, ELCOLR 中断清除，0：LSR状态在读取RBR或读LSR寄存器时清除 1：LSR状态在读LSR寄存器时清除*/
#define UART_IER_DLH_ELCOLR_Pos             ((uint32_t)4)   /*bit position, ELCOLR 中断清除，0：LSR状态在读取RBR或读LSR寄存器时清除 1：LSR状态在读LSR寄存器时清除*/
#define UART_IER_DLH_PTIME_Msk             ((uint32_t)0x80)   /* bit mask, PTIME
THRE 中断模式使能 (Programmable THRE Interrupt Mode Enable)
0：未使能。THRE 中断会在非空的条件清除。

1：使能。THRE 中断会在低于触发深度 FCR[5:4] 的条件清除。*/
#define UART_IER_DLH_PTIME_Pos             ((uint32_t)7)   /*bit position, PTIME
THRE 中断模式使能 (Programmable THRE Interrupt Mode Enable)
0：未使能。THRE 中断会在非空的条件清除。

1：使能。THRE 中断会在低于触发深度 FCR[5:4] 的条件清除。*/

/******************  Bit Definition for Register IIR  *********************/
#define UART_IIR_IID_Msk             ((uint32_t)0xf)   /* bit mask, IID
中断 ID (Interrupt ID) ，表示最高优先级的挂起中断，可以是以下类型之一：
0x0：调制解调器状态

0x1：无中断

0x2：THR 为空

0x3：RS485 中断

0x4：接收数据可用

0x6：接收线路状态

0x7：繁忙检测

0xC：字符超时。*/
#define UART_IIR_IID_Pos             ((uint32_t)0)   /*bit position, IID
中断 ID (Interrupt ID) ，表示最高优先级的挂起中断，可以是以下类型之一：
0x0：调制解调器状态

0x1：无中断

0x2：THR 为空

0x3：RS485 中断

0x4：接收数据可用

0x6：接收线路状态

0x7：繁忙检测

0xC：字符超时。*/

/******************  Bit Definition for Register LCR  *********************/
#define UART_LCR_DLS_Msk             ((uint32_t)0x3)   /* bit mask,     DLS
数据长度选择 (Data Length Select)

仅当 UART 空闲时（USR[0] 为 0）此位才可写。用于选择外围设备发送和接收的每个字符的数据位数。可选择的位数如下：
0：5 位

1：6 位

2：7 位

3：8 位*/
#define UART_LCR_DLS_Pos             ((uint32_t)0)   /*bit position,     DLS
数据长度选择 (Data Length Select)

仅当 UART 空闲时（USR[0] 为 0）此位才可写。用于选择外围设备发送和接收的每个字符的数据位数。可选择的位数如下：
0：5 位

1：6 位

2：7 位

3：8 位*/
#define UART_LCR_STOP_Msk             ((uint32_t)0x4)   /* bit mask,     STOP
停止位数 (Number of Stop Bits)，用于选择外围设备发送和接收的每个字符的停止位数。

仅当 UART 空闲时（USR[0] 为 0）此位才可写。0：1 个停止位

1：当 DLS (LCR[1：0]) 为 0 时，1.5 个停止位，否则 2 个停止位。当设为 1 且数据位设为 5 位时 (LCR[1：0]) ，传输 1.5 个停止位，否则传输 2 位停止位。*/
#define UART_LCR_STOP_Pos             ((uint32_t)2)   /*bit position,     STOP
停止位数 (Number of Stop Bits)，用于选择外围设备发送和接收的每个字符的停止位数。

仅当 UART 空闲时（USR[0] 为 0）此位才可写。0：1 个停止位

1：当 DLS (LCR[1：0]) 为 0 时，1.5 个停止位，否则 2 个停止位。当设为 1 且数据位设为 5 位时 (LCR[1：0]) ，传输 1.5 个停止位，否则传输 2 位停止位。*/
#define UART_LCR_PEN_Msk             ((uint32_t)0x8)   /* bit mask,     PEN
奇偶校验使能 (Parity Enable)，用于使能和未使能发送接收串行字符中的奇偶校验生成与检测。

仅当 UART 空闲时（USR[0] 为 0）此位才可写。
0：奇偶检验未使能
1：奇偶检验使能*/
#define UART_LCR_PEN_Pos             ((uint32_t)3)   /*bit position,     PEN
奇偶校验使能 (Parity Enable)，用于使能和未使能发送接收串行字符中的奇偶校验生成与检测。

仅当 UART 空闲时（USR[0] 为 0）此位才可写。
0：奇偶检验未使能
1：奇偶检验使能*/
#define UART_LCR_EPS_Msk             ((uint32_t)0x10)   /* bit mask,     EPS
偶校验选择 (Even Parity Select)。仅当 UART 空闲时（USR[0] 为 0）此位才可写。当使能奇偶校验时（PEN 设为 1），用于选择奇性或者偶性校验。设置 LCR[5] 可反转 LCR[4]。

0：奇性校验
1：偶性校验*/
#define UART_LCR_EPS_Pos             ((uint32_t)4)   /*bit position,     EPS
偶校验选择 (Even Parity Select)。仅当 UART 空闲时（USR[0] 为 0）此位才可写。当使能奇偶校验时（PEN 设为 1），用于选择奇性或者偶性校验。设置 LCR[5] 可反转 LCR[4]。

0：奇性校验
1：偶性校验*/
#define UART_LCR_SP_Msk             ((uint32_t)0x20)   /* bit mask, SP 0=强制为“0”stick校验，1=强制为“1”stick校验*/
#define UART_LCR_SP_Pos             ((uint32_t)5)   /*bit position, SP 0=强制为“0”stick校验，1=强制为“1”stick校验*/
#define UART_LCR_BC_Msk             ((uint32_t)0x40)   /* bit mask, BC
中断信号控制位 (Break Control Bit)

产生一个中断条件传输到接收端。

若此位设 1，串行输出将强制为逻辑 0 状态。如果处于非回环模式中（取决于 MCR[4]），串行输出线强制为低电平，直到清除此位。*/
#define UART_LCR_BC_Pos             ((uint32_t)6)   /*bit position, BC
中断信号控制位 (Break Control Bit)

产生一个中断条件传输到接收端。

若此位设 1，串行输出将强制为逻辑 0 状态。如果处于非回环模式中（取决于 MCR[4]），串行输出线强制为低电平，直到清除此位。*/
#define UART_LCR_DLAB_Msk             ((uint32_t)0x80)   /* bit mask, DLAB
除数存取位 (Divisor Latch Access Bit)，用于使能除数寄存器（DLL 和 DLH）的读写，以设置 UART 的波特率。

仅当 UART 空闲时 （USR[0] 为 0） 此位才可写。在初始化波特率设置后，必须清除此位，以便访问其他寄存器。
0：选择接收缓冲寄存器（RBR）、发送保持寄存器 (THR) 以及中断使能寄存器 (IER)
1：选择低位除数寄存器 (DLL) 以及高位除数寄存器 (DLH)*/
#define UART_LCR_DLAB_Pos             ((uint32_t)7)   /*bit position, DLAB
除数存取位 (Divisor Latch Access Bit)，用于使能除数寄存器（DLL 和 DLH）的读写，以设置 UART 的波特率。

仅当 UART 空闲时 （USR[0] 为 0） 此位才可写。在初始化波特率设置后，必须清除此位，以便访问其他寄存器。
0：选择接收缓冲寄存器（RBR）、发送保持寄存器 (THR) 以及中断使能寄存器 (IER)
1：选择低位除数寄存器 (DLL) 以及高位除数寄存器 (DLH)*/

/******************  Bit Definition for Register MCR  *********************/
#define UART_MCR_DTR_Msk             ((uint32_t)0x1)   /* bit mask, 选择 Modem 输出管脚 DTR。当 Modem 回写模式激活时，该位读出为 0。*/
#define UART_MCR_DTR_Pos             ((uint32_t)0)   /*bit position, 选择 Modem 输出管脚 DTR。当 Modem 回写模式激活时，该位读出为 0。*/
#define UART_MCR_RTS_Msk             ((uint32_t)0x2)   /* bit mask, 选择 Modem 输出管脚 RTS。当 Modem 回写模式激活时，该位读出为 0。*/
#define UART_MCR_RTS_Pos             ((uint32_t)1)   /*bit position, 选择 Modem 输出管脚 RTS。当 Modem 回写模式激活时，该位读出为 0。*/
#define UART_MCR_LOOPBACK_Msk             ((uint32_t)0x10)   /* bit mask, Modem 回写模式提供了执行回写测试的诊断机制。发送器输出的串行数据在内部连接
到接收器的串行输入端。输入管脚 RXD1 对回写操作无影响，而输出管脚 TXD1 保持
为标记状态。 4 个 Modem 输入端（CTS、 DSR、 RI 和 DCD）与外部断开。从外部看
来， Modem 输出端（RTS、 DTR）无效。而从内部来看， 4 个 Modem 输出都连接到
4 个 Modem 输入上。这样连接的结果将导致 MSR 的高 4 位由 MCR 的低 4 位
驱动，而不是在正常模式下由 4 个 Modem 输入驱动。这样在回写模式下，写 MCR
的低 4 位可产生 Modem 状态中断。*/
#define UART_MCR_LOOPBACK_Pos             ((uint32_t)4)   /*bit position, Modem 回写模式提供了执行回写测试的诊断机制。发送器输出的串行数据在内部连接
到接收器的串行输入端。输入管脚 RXD1 对回写操作无影响，而输出管脚 TXD1 保持
为标记状态。 4 个 Modem 输入端（CTS、 DSR、 RI 和 DCD）与外部断开。从外部看
来， Modem 输出端（RTS、 DTR）无效。而从内部来看， 4 个 Modem 输出都连接到
4 个 Modem 输入上。这样连接的结果将导致 MSR 的高 4 位由 MCR 的低 4 位
驱动，而不是在正常模式下由 4 个 Modem 输入驱动。这样在回写模式下，写 MCR
的低 4 位可产生 Modem 状态中断。*/
#define UART_MCR_SIRE_Msk             ((uint32_t)0x40)   /* bit mask, 0=IrDA SIR模式关闭，1=IrDA SIR模式开启*/
#define UART_MCR_SIRE_Pos             ((uint32_t)6)   /*bit position, 0=IrDA SIR模式关闭，1=IrDA SIR模式开启*/

/******************  Bit Definition for Register LSR  *********************/
#define UART_LSR_DR_Msk             ((uint32_t)0x1)   /* bit mask, DR
数据就绪 (Data Ready)

用于指示在 RBR接收的数据 0：无数据就绪
1：数据就绪*/
#define UART_LSR_DR_Pos             ((uint32_t)0)   /*bit position, DR
数据就绪 (Data Ready)

用于指示在 RBR接收的数据 0：无数据就绪
1：数据就绪*/
#define UART_LSR_OE_Msk             ((uint32_t)0x2)   /* bit mask, OE
溢出错误 (Overrun Error)
0：无溢出错误
1：溢出错误，读取 LSR 清除此位
如果在读取先前数据之前接收到新的数据字符，则出现此错误。*/
#define UART_LSR_OE_Pos             ((uint32_t)1)   /*bit position, OE
溢出错误 (Overrun Error)
0：无溢出错误
1：溢出错误，读取 LSR 清除此位
如果在读取先前数据之前接收到新的数据字符，则出现此错误。*/
#define UART_LSR_PE_Msk             ((uint32_t)0x4)   /* bit mask, PE
奇偶校验错误 (Parity Error)

此位用于指示在接收中发生奇偶校验错误。
0：无奇偶校验错误
1：奇偶校验错误读取 LSR 清除此位。*/
#define UART_LSR_PE_Pos             ((uint32_t)2)   /*bit position, PE
奇偶校验错误 (Parity Error)

此位用于指示在接收中发生奇偶校验错误。
0：无奇偶校验错误
1：奇偶校验错误读取 LSR 清除此位。*/
#define UART_LSR_FE_Msk             ((uint32_t)0x8)   /* bit mask, FE
帧错误 (Framing Error)，用于指示接收器中出现帧错误。

当接收器在接收的数据中没有检测到有效的停止位时，就会发生帧错误。需要注意的是，如果发生 BI，则此位也置 1。

0：无帧错误
1：帧错误读取 LSR 清除此位*/
#define UART_LSR_FE_Pos             ((uint32_t)3)   /*bit position, FE
帧错误 (Framing Error)，用于指示接收器中出现帧错误。

当接收器在接收的数据中没有检测到有效的停止位时，就会发生帧错误。需要注意的是，如果发生 BI，则此位也置 1。

0：无帧错误
1：帧错误读取 LSR 清除此位*/
#define UART_LSR_BI_Msk             ((uint32_t)0x10)   /* bit mask, BI
Break 中断 (Break Interrupt)，用于指示在串行输入数据上检测到中断序列。

break 条件会导致 UART 接收到仅且一个由 0 组成的字符*/
#define UART_LSR_BI_Pos             ((uint32_t)4)   /*bit position, BI
Break 中断 (Break Interrupt)，用于指示在串行输入数据上检测到中断序列。

break 条件会导致 UART 接收到仅且一个由 0 组成的字符*/
#define UART_LSR_THRE_Msk             ((uint32_t)0x20)   /* bit mask, THRE
数据发送寄存器为空 (TX Holding Register Empty)。每当数据发送寄存器为空并且准备接收新数据时，该位被设为 1。CPU 写入数据发送寄存器时，该位被清除。*/
#define UART_LSR_THRE_Pos             ((uint32_t)5)   /*bit position, THRE
数据发送寄存器为空 (TX Holding Register Empty)。每当数据发送寄存器为空并且准备接收新数据时，该位被设为 1。CPU 写入数据发送寄存器时，该位被清除。*/
#define UART_LSR_TEMT_Msk             ((uint32_t)0x40)   /* bit mask, TEMT
发送器为空 (Transmitter Empty)

每当数据发送寄存器以及发送移位寄存器为空时，该位设 1。*/
#define UART_LSR_TEMT_Pos             ((uint32_t)6)   /*bit position, TEMT
发送器为空 (Transmitter Empty)

每当数据发送寄存器以及发送移位寄存器为空时，该位设 1。*/
#define UART_LSR_ADDR_RCVD_Msk             ((uint32_t)0x100)   /* bit mask, 地址接收位。

如果启用了 9 位数据模式 （LCR_EXT[0]=1），则此位用于指示接收数据的第 9 位设置为 1。此位还可用于指示传入字符是 address 还是 data。

1 = 指示字符是地址。

0 = 指示字符是数据。
*/
#define UART_LSR_ADDR_RCVD_Pos             ((uint32_t)8)   /*bit position, 地址接收位。

如果启用了 9 位数据模式 （LCR_EXT[0]=1），则此位用于指示接收数据的第 9 位设置为 1。此位还可用于指示传入字符是 address 还是 data。

1 = 指示字符是地址。

0 = 指示字符是数据。
*/

/******************  Bit Definition for Register MSR  *********************/
#define UART_MSR_DCTS_Msk             ((uint32_t)0x1)   /* bit mask, 当输入端 CTS 的状态改变时，该位置位。读 MSR 会清零该位。 0 没有检测到 Modem 输入端 CTS 上的状态变化。
1 检测到 Modem 输入端 CTS 上的状态变化。*/
#define UART_MSR_DCTS_Pos             ((uint32_t)0)   /*bit position, 当输入端 CTS 的状态改变时，该位置位。读 MSR 会清零该位。 0 没有检测到 Modem 输入端 CTS 上的状态变化。
1 检测到 Modem 输入端 CTS 上的状态变化。*/
#define UART_MSR_DDSR_Msk             ((uint32_t)0x2)   /* bit mask, 当输入端 DSR 的状态改变时，该位置位。读 MSR 会清零该位。 0 没有检测到 Modem 输入端 DSR 上的状态变化。
1 检测到 Modem 输入端 DSR 上的状态变化。*/
#define UART_MSR_DDSR_Pos             ((uint32_t)1)   /*bit position, 当输入端 DSR 的状态改变时，该位置位。读 MSR 会清零该位。 0 没有检测到 Modem 输入端 DSR 上的状态变化。
1 检测到 Modem 输入端 DSR 上的状态变化。*/
#define UART_MSR_TERI_Msk             ((uint32_t)0x4)   /* bit mask, 当输入端 RI 上低电平到高电平的跳变时，该位置位。读 MSR 会清零该位。
0 没有检测到 Modem 输入端 RI 上的状态变化。
1 检测到 RI 上的低电平到高电平跳变的变化。*/
#define UART_MSR_TERI_Pos             ((uint32_t)2)   /*bit position, 当输入端 RI 上低电平到高电平的跳变时，该位置位。读 MSR 会清零该位。
0 没有检测到 Modem 输入端 RI 上的状态变化。
1 检测到 RI 上的低电平到高电平跳变的变化。*/
#define UART_MSR_DDCD_Msk             ((uint32_t)0x8)   /* bit mask, 当输入端 DCD 的状态改变时，该位置位。读1MSR 会清零该位。 0 没有检测到 Modem 输入端 DCD 上的状态变化。*/
#define UART_MSR_DDCD_Pos             ((uint32_t)3)   /*bit position, 当输入端 DCD 的状态改变时，该位置位。读1MSR 会清零该位。 0 没有检测到 Modem 输入端 DCD 上的状态变化。*/
#define UART_MSR_CTS_Msk             ((uint32_t)0x10)   /* bit mask, 清除发送状态。输入信号 CTS 的补码。在 Modem 回写模式下，该位连接到
MCR[1]。*/
#define UART_MSR_CTS_Pos             ((uint32_t)4)   /*bit position, 清除发送状态。输入信号 CTS 的补码。在 Modem 回写模式下，该位连接到
MCR[1]。*/
#define UART_MSR_DSR_Msk             ((uint32_t)0x20)   /* bit mask, 数据设置就绪状态。输入信号 DSR 的补码。 在 Modem 回写模式下，该位连接到
MCR[0]。*/
#define UART_MSR_DSR_Pos             ((uint32_t)5)   /*bit position, 数据设置就绪状态。输入信号 DSR 的补码。 在 Modem 回写模式下，该位连接到
MCR[0]。*/
#define UART_MSR_RI_Msk             ((uint32_t)0x40)   /* bit mask, 铃响指示状态。输入 RI 的补码。在 Modem 回写模式下，该位连接到 MCR[2]。*/
#define UART_MSR_RI_Pos             ((uint32_t)6)   /*bit position, 铃响指示状态。输入 RI 的补码。在 Modem 回写模式下，该位连接到 MCR[2]。*/
#define UART_MSR_DCD_Msk             ((uint32_t)0x80)   /* bit mask, 数据载波检测状态。输入 DCD 的补码。在 Modem 回写模式下，该位连接到
MCR[3]。*/
#define UART_MSR_DCD_Pos             ((uint32_t)7)   /*bit position, 数据载波检测状态。输入 DCD 的补码。在 Modem 回写模式下，该位连接到
MCR[3]。*/

/******************  Bit Definition for Register SCR  *********************/
#define UART_SCR_SCR_Msk             ((uint32_t)0xff)   /* bit mask, SCRATCH_REG
暂存器，为用户提供临时存储空间，UART 中未定义用途。*/
#define UART_SCR_SCR_Pos             ((uint32_t)0)   /*bit position, SCRATCH_REG
暂存器，为用户提供临时存储空间，UART 中未定义用途。*/

/******************  Bit Definition for Register FAR  *********************/
#define UART_FAR_RESERVE_Msk             ((uint32_t)0x1)   /* bit mask, */
#define UART_FAR_RESERVE_Pos             ((uint32_t)0)   /*bit position, */

/******************  Bit Definition for Register USR  *********************/
#define UART_USR_HTX_Msk             ((uint32_t)0x1)   /* bit mask, HALT_TX
停止发送

此位用于停止传输以进行测试，以便在使能 FIFO 时，主控可以填充发送缓冲。
0：停止发送未使能
1：停止发送使能*/
#define UART_USR_HTX_Pos             ((uint32_t)0)   /*bit position, HALT_TX
停止发送

此位用于停止传输以进行测试，以便在使能 FIFO 时，主控可以填充发送缓冲。
0：停止发送未使能
1：停止发送使能*/

/******************  Bit Definition for Register HTX  *********************/
#define UART_HTX_RESERVE_Msk             ((uint32_t)0x1)   /* bit mask, */
#define UART_HTX_RESERVE_Pos             ((uint32_t)0)   /*bit position, */

/******************  Bit Definition for Register DMASA  *********************/
#define UART_DMASA_DMASA_Msk             ((uint32_t)0x1)   /* bit mask, */
#define UART_DMASA_DMASA_Pos             ((uint32_t)0)   /*bit position, */

/******************  Bit Definition for Register DLF  *********************/
#define UART_DLF_DLF_Msk             ((uint32_t)0x3f)   /* bit mask, 除数的小数部分。

小数值被添加到 DLH、DLL 设置的整数值中。分数值由 （Divisor Fraction value）/（2^DLF_SIZE） 确定。*/
#define UART_DLF_DLF_Pos             ((uint32_t)0)   /*bit position, 除数的小数部分。

小数值被添加到 DLH、DLL 设置的整数值中。分数值由 （Divisor Fraction value）/（2^DLF_SIZE） 确定。*/

/******************  Bit Definition for Register RAR  *********************/
#define UART_RAR_RAR_Msk             ((uint32_t)0xff)   /* bit mask, */
#define UART_RAR_RAR_Pos             ((uint32_t)0)   /*bit position, */

/******************  Bit Definition for Register TAR  *********************/
#define UART_TAR_TAR_Msk             ((uint32_t)0xff)   /* bit mask, */
#define UART_TAR_TAR_Pos             ((uint32_t)0)   /*bit position, */

/******************  Bit Definition for Register LCR_EXT  *********************/
#define UART_LCR_EXT_DLS_E_Msk             ((uint32_t)0x1)   /* bit mask, */
#define UART_LCR_EXT_DLS_E_Pos             ((uint32_t)0)   /*bit position, */
#define UART_LCR_EXT_ADDR_MATCH_Msk             ((uint32_t)0x2)   /* bit mask, */
#define UART_LCR_EXT_ADDR_MATCH_Pos             ((uint32_t)1)   /*bit position, */
#define UART_LCR_EXT_SEND_ADDR_Msk             ((uint32_t)0x4)   /* bit mask, */
#define UART_LCR_EXT_SEND_ADDR_Pos             ((uint32_t)2)   /*bit position, */
#define UART_LCR_EXT_TRANSMIT_MODE_Msk             ((uint32_t)0x8)   /* bit mask, */
#define UART_LCR_EXT_TRANSMIT_MODE_Pos             ((uint32_t)3)   /*bit position, */

/******************************************************************************/
/*                    I2C                         */
/******************************************************************************/


/******************  Bit Definition for Register I2C_CR1  *********************/
#define I2C_CR1_PE_Msk             ((uint32_t)0x1)   /* bit mask, PE：I2C模块使能 (Peripheral enable) 注：如果清除该位时通讯正在进行，在当前通讯结束后，I2C模块被禁用并返回空闲状态。由于在通讯结束后发生PE＝0，所有的位被清除。
在主模式下，通讯结束之前，绝不能清除该位。
0: 禁用I2C模块
1: 启用I2C模块：根据SMBus位的设置，相应的I/O口需配置为复用功能
*/
#define I2C_CR1_PE_Pos             ((uint32_t)0)   /*bit position, PE：I2C模块使能 (Peripheral enable) 注：如果清除该位时通讯正在进行，在当前通讯结束后，I2C模块被禁用并返回空闲状态。由于在通讯结束后发生PE＝0，所有的位被清除。
在主模式下，通讯结束之前，绝不能清除该位。
0: 禁用I2C模块
1: 启用I2C模块：根据SMBus位的设置，相应的I/O口需配置为复用功能
*/
#define I2C_CR1_ENPEC_Msk             ((uint32_t)0x20)   /* bit mask, ENPEC：PEC使能 (PEC enable) 
0: 禁止PEC计算；
1: 开启PEC计算
*/
#define I2C_CR1_ENPEC_Pos             ((uint32_t)5)   /*bit position, ENPEC：PEC使能 (PEC enable) 
0: 禁止PEC计算；
1: 开启PEC计算
*/
#define I2C_CR1_ENGC_Msk             ((uint32_t)0x40)   /* bit mask, ENGC：广播呼叫使能 (General call enable) 
0: 禁止广播呼叫。以非应答响应地址00h
1: 允许广播呼叫. 以应答响应地址00h。
*/
#define I2C_CR1_ENGC_Pos             ((uint32_t)6)   /*bit position, ENGC：广播呼叫使能 (General call enable) 
0: 禁止广播呼叫。以非应答响应地址00h
1: 允许广播呼叫. 以应答响应地址00h。
*/
#define I2C_CR1_NOSTRETCH_Msk             ((uint32_t)0x80)   /* bit mask, NOSTRETCH：禁止时钟延长(从模式) (Clock stretching disable (Slave mode))
该位用于当ADDR或BTF标志被置位，在从模式下禁止时钟延长，直到它被软件复位。

0: 允许时钟延长
1: 禁止时钟延长。
*/
#define I2C_CR1_NOSTRETCH_Pos             ((uint32_t)7)   /*bit position, NOSTRETCH：禁止时钟延长(从模式) (Clock stretching disable (Slave mode))
该位用于当ADDR或BTF标志被置位，在从模式下禁止时钟延长，直到它被软件复位。

0: 允许时钟延长
1: 禁止时钟延长。
*/
#define I2C_CR1_START_Msk             ((uint32_t)0x100)   /* bit mask, START：起始条件产生 (Start generation)
软件可以设置或清除该位，或当起始条件发出后或PE=0时，由硬件清除。在主模式下：

0: 主模式下：无起始条件产生； 在从模式下：无起始条件产生；
1: 主模式下：重复产生起始条件； 在从模式下：当总线空闲时，产生起始条件
*/
#define I2C_CR1_START_Pos             ((uint32_t)8)   /*bit position, START：起始条件产生 (Start generation)
软件可以设置或清除该位，或当起始条件发出后或PE=0时，由硬件清除。在主模式下：

0: 主模式下：无起始条件产生； 在从模式下：无起始条件产生；
1: 主模式下：重复产生起始条件； 在从模式下：当总线空闲时，产生起始条件
*/
#define I2C_CR1_STOP_Msk             ((uint32_t)0x200)   /* bit mask, STOP：停止条件产生 (Stop generation)
软件可以设置或清除该位；或当检测到停止条件时，由硬件清除；当检测到超时错误时，硬件将其置位。
注：当设置了STOP、START 或PEC 位，在硬件清除这个位之前，软件不要执行任何对
I2C_CR1的写操作；否则有可能会第2次设置STOP、START或PEC位。
0: 主模式下：无停止条件产生；无停止条件产生；
1: 主模式下：在当前字节传输或在当前起始条件发出后产生停止条件。在从模式下：在当前字节传输或释放SCL和SDA线。
*/
#define I2C_CR1_STOP_Pos             ((uint32_t)9)   /*bit position, STOP：停止条件产生 (Stop generation)
软件可以设置或清除该位；或当检测到停止条件时，由硬件清除；当检测到超时错误时，硬件将其置位。
注：当设置了STOP、START 或PEC 位，在硬件清除这个位之前，软件不要执行任何对
I2C_CR1的写操作；否则有可能会第2次设置STOP、START或PEC位。
0: 主模式下：无停止条件产生；无停止条件产生；
1: 主模式下：在当前字节传输或在当前起始条件发出后产生停止条件。在从模式下：在当前字节传输或释放SCL和SDA线。
*/
#define I2C_CR1_ACK_Msk             ((uint32_t)0x400)   /* bit mask, ACK：应答使能 (Acknowledge enable)
软件可以设置或清除该位，或当PE=0时，由硬件清除。

0: 无应答返回；
1: 在接收到一个字节后返回一个应答(匹配的地址或数据)。
*/
#define I2C_CR1_ACK_Pos             ((uint32_t)10)   /*bit position, ACK：应答使能 (Acknowledge enable)
软件可以设置或清除该位，或当PE=0时，由硬件清除。

0: 无应答返回；
1: 在接收到一个字节后返回一个应答(匹配的地址或数据)。
*/
#define I2C_CR1_POS_Msk             ((uint32_t)0x800)   /* bit mask, POS: 应答/PEC位置(用于数据接收) (Acknowledge/PEC Position (for data reception))
软件可以设置或清除该位，或当PE=0时，由硬件清除。
注：POS位只能用在2字节的接收配置中，必须在接收数据之前配置。为了NACK第2个字节，必须在清除ADDR为之后清除ACK位。
为了检测第2个字节的PEC，必须在配置了POS位之后，拉伸ADDR事件时设置PEC位。
0: ACK位控制当前移位寄存器内正在接收的字节的(N)ACK。 PEC位表明当前移位寄存器内的字节是PEC；
1: ACK位控制在移位寄存器里接收的下一个字节的(N)ACK。PEC位表明在移位寄存器里接收的下一个字节是PEC。
*/
#define I2C_CR1_POS_Pos             ((uint32_t)11)   /*bit position, POS: 应答/PEC位置(用于数据接收) (Acknowledge/PEC Position (for data reception))
软件可以设置或清除该位，或当PE=0时，由硬件清除。
注：POS位只能用在2字节的接收配置中，必须在接收数据之前配置。为了NACK第2个字节，必须在清除ADDR为之后清除ACK位。
为了检测第2个字节的PEC，必须在配置了POS位之后，拉伸ADDR事件时设置PEC位。
0: ACK位控制当前移位寄存器内正在接收的字节的(N)ACK。 PEC位表明当前移位寄存器内的字节是PEC；
1: ACK位控制在移位寄存器里接收的下一个字节的(N)ACK。PEC位表明在移位寄存器里接收的下一个字节是PEC。
*/
#define I2C_CR1_PEC_Msk             ((uint32_t)0x1000)   /* bit mask, PEC：数据包出错检测 (Packet error checking)
软件可以设置或清除该位；当传送PEC后，或起始或停止条件时，或当PE=0时硬件将其清除。

0: 无PEC传输；
1: PEC传输(在发送或接收模式)。注：仲裁丢失时，PEC的计算失效。
*/
#define I2C_CR1_PEC_Pos             ((uint32_t)12)   /*bit position, PEC：数据包出错检测 (Packet error checking)
软件可以设置或清除该位；当传送PEC后，或起始或停止条件时，或当PE=0时硬件将其清除。

0: 无PEC传输；
1: PEC传输(在发送或接收模式)。注：仲裁丢失时，PEC的计算失效。
*/
#define I2C_CR1_SWRST_Msk             ((uint32_t)0x8000)   /* bit mask, SWRST：软件复位 (Software reset)
当被置位时，I2C处于复位状态。在复位该位前确信I2C的引脚被释放，总线是空的。
注：该位可以用于BUSY位为’1’，在总线上又没有检测到停止条件时。
0: I2C模块不处于复位状态；
1: I2C模块处于复位状态。
*/
#define I2C_CR1_SWRST_Pos             ((uint32_t)15)   /*bit position, SWRST：软件复位 (Software reset)
当被置位时，I2C处于复位状态。在复位该位前确信I2C的引脚被释放，总线是空的。
注：该位可以用于BUSY位为’1’，在总线上又没有检测到停止条件时。
0: I2C模块不处于复位状态；
1: I2C模块处于复位状态。
*/

/******************  Bit Definition for Register I2C_CR2  *********************/
#define I2C_CR2_FREQ_Msk             ((uint32_t)0x7f)   /* bit mask, FREQ[6:0]:  I2C模块时钟频率（Peripheral clock frequency）
FREQ[6:0]是对应输入APB时钟的频率，必须设置正确的输入时钟频率以产生正确的时序，允许的范围在2～72MHz之间：
0000000：禁用
0000001：禁用
0000010：2MHz
...
0100100：36MHz
1001000：72MHz
大于1001000：禁用。 
注意： 
在标准I2C模式时，APB的时钟频率必须大于等于2MHz。在快速I2C模式时，APB的时钟频率必须大于等于8MHz。在快速+ 模式下，APB时钟频率需大于或者等于24MHz。
*/
#define I2C_CR2_FREQ_Pos             ((uint32_t)0)   /*bit position, FREQ[6:0]:  I2C模块时钟频率（Peripheral clock frequency）
FREQ[6:0]是对应输入APB时钟的频率，必须设置正确的输入时钟频率以产生正确的时序，允许的范围在2～72MHz之间：
0000000：禁用
0000001：禁用
0000010：2MHz
...
0100100：36MHz
1001000：72MHz
大于1001000：禁用。 
注意： 
在标准I2C模式时，APB的时钟频率必须大于等于2MHz。在快速I2C模式时，APB的时钟频率必须大于等于8MHz。在快速+ 模式下，APB时钟频率需大于或者等于24MHz。
*/
#define I2C_CR2_ITERREN_Msk             ((uint32_t)0x100)   /* bit mask, ITERREN：出错中断使能 (Error interrupt enable) 
0：禁止出错中断；
1：允许出错中断。
在下列条件下，将产生该中断：
–BERR = 1；
–ARLO = 1；
–AF = 1；
–OVR = 1；
–PECERR = 1；
–TIMEOUT = 1；
–SMBAlert = 1。
*/
#define I2C_CR2_ITERREN_Pos             ((uint32_t)8)   /*bit position, ITERREN：出错中断使能 (Error interrupt enable) 
0：禁止出错中断；
1：允许出错中断。
在下列条件下，将产生该中断：
–BERR = 1；
–ARLO = 1；
–AF = 1；
–OVR = 1；
–PECERR = 1；
–TIMEOUT = 1；
–SMBAlert = 1。
*/
#define I2C_CR2_ITEVTEN_Msk             ((uint32_t)0x200)   /* bit mask, ITEVTEN：事件中断使能 (Event interrupt enable) 0：禁止事件中断；
1：允许事件中断。
在下列条件下，将产生该中断：
–SB = 1 (主模式)；
–ADDR = 1 (主/从模式)；
–ADD10= 1 (主模式)；
–STOPF = 1 (从模式)；
–TxSRE=1（FIFO模式下）
–BTF = 1，但是没有TxE或RxNE事件；
–如果ITBUFEN = 1，TxE事件为1；
–如果ITBUFEN = 1，RxNE事件为1。
*/
#define I2C_CR2_ITEVTEN_Pos             ((uint32_t)9)   /*bit position, ITEVTEN：事件中断使能 (Event interrupt enable) 0：禁止事件中断；
1：允许事件中断。
在下列条件下，将产生该中断：
–SB = 1 (主模式)；
–ADDR = 1 (主/从模式)；
–ADD10= 1 (主模式)；
–STOPF = 1 (从模式)；
–TxSRE=1（FIFO模式下）
–BTF = 1，但是没有TxE或RxNE事件；
–如果ITBUFEN = 1，TxE事件为1；
–如果ITBUFEN = 1，RxNE事件为1。
*/
#define I2C_CR2_ITBUFEN_Msk             ((uint32_t)0x400)   /* bit mask, ITBUFEN：缓冲器（发送和接收FIFO）中断使能 (Buffer interrupt enable) 
0：当TxE=1或RxNE=1时，不产生任何中断；
1：当TxE=1或RxNE=1时，产生事件中断(不管DMAEN是何种状态)。
*/
#define I2C_CR2_ITBUFEN_Pos             ((uint32_t)10)   /*bit position, ITBUFEN：缓冲器（发送和接收FIFO）中断使能 (Buffer interrupt enable) 
0：当TxE=1或RxNE=1时，不产生任何中断；
1：当TxE=1或RxNE=1时，产生事件中断(不管DMAEN是何种状态)。
*/
#define I2C_CR2_DMAEN_Msk             ((uint32_t)0x800)   /* bit mask, DMAEN：DMA请求使能 (DMA requests enable) 0：禁止DMA请求；
1：当TxE=1或RxNE =1时，允许DMA请求。
*/
#define I2C_CR2_DMAEN_Pos             ((uint32_t)11)   /*bit position, DMAEN：DMA请求使能 (DMA requests enable) 0：禁止DMA请求；
1：当TxE=1或RxNE =1时，允许DMA请求。
*/
#define I2C_CR2_LAST_Msk             ((uint32_t)0x1000)   /* bit mask, LAST: DMA最后一次传输 (DMA last transfer) 0：下一次DMA的EOT不是最后的传输；
1：下一次DMA的EOT是最后的传输。
注：该位在主接收模式使用， 使得在最后一次接收数据时可以产生一个NACK。
*/
#define I2C_CR2_LAST_Pos             ((uint32_t)12)   /*bit position, LAST: DMA最后一次传输 (DMA last transfer) 0：下一次DMA的EOT不是最后的传输；
1：下一次DMA的EOT是最后的传输。
注：该位在主接收模式使用， 使得在最后一次接收数据时可以产生一个NACK。
*/

/******************  Bit Definition for Register I2C_OAR1  *********************/
#define I2C_OAR1_ADD0_Msk             ((uint32_t)0x1)   /* bit mask, ADD0：接口地址 (Interface address) 
7位地址模式时不用关心。
10位地址模式时为地址第0位。
*/
#define I2C_OAR1_ADD0_Pos             ((uint32_t)0)   /*bit position, ADD0：接口地址 (Interface address) 
7位地址模式时不用关心。
10位地址模式时为地址第0位。
*/
#define I2C_OAR1_ADD_7_1_Msk             ((uint32_t)0xfe)   /* bit mask, ADD[7:1]：接口地址 (Interface address)
地址的7~1位。
*/
#define I2C_OAR1_ADD_7_1_Pos             ((uint32_t)1)   /*bit position, ADD[7:1]：接口地址 (Interface address)
地址的7~1位。
*/
#define I2C_OAR1_ADD_9_8_Msk             ((uint32_t)0x300)   /* bit mask, ADD[9:8]：接口地址 (Interface address) 7位地址模式时不用关心。
10位地址模式时为地址的9~8位。
*/
#define I2C_OAR1_ADD_9_8_Pos             ((uint32_t)8)   /*bit position, ADD[9:8]：接口地址 (Interface address) 7位地址模式时不用关心。
10位地址模式时为地址的9~8位。
*/
#define I2C_OAR1_ADDMODE_Msk             ((uint32_t)0x8000)   /* bit mask, ADDMODE：寻址模式(从模式) (Addressing mode (slave mode)) 0：7位从地址(不响应10位地址)；
1：10位从地址(不响应7位地址)。
*/
#define I2C_OAR1_ADDMODE_Pos             ((uint32_t)15)   /*bit position, ADDMODE：寻址模式(从模式) (Addressing mode (slave mode)) 0：7位从地址(不响应10位地址)；
1：10位从地址(不响应7位地址)。
*/

/******************  Bit Definition for Register I2C_OAR2  *********************/
#define I2C_OAR2_ADD2_Msk             ((uint32_t)0xfe)   /* bit mask, ADD2[7:1]：接口地址 (Interface address)
在双地址模式下地址的7~1位。
*/
#define I2C_OAR2_ADD2_Pos             ((uint32_t)1)   /*bit position, ADD2[7:1]：接口地址 (Interface address)
在双地址模式下地址的7~1位。
*/
#define I2C_OAR2_ENDUAL_Msk             ((uint32_t)0x1)   /* bit mask, ENDUAL：双地址模式使能位 (Dual addressing mode enable) 
：在7位地址模式下，只有OAR1被识别；
1：在7位地址模式下，OAR1和OAR2都被识别。
*/
#define I2C_OAR2_ENDUAL_Pos             ((uint32_t)0)   /*bit position, ENDUAL：双地址模式使能位 (Dual addressing mode enable) 
：在7位地址模式下，只有OAR1被识别；
1：在7位地址模式下，OAR1和OAR2都被识别。
*/

/******************  Bit Definition for Register I2C_DR  *********************/
#define I2C_DR_DR_Msk             ((uint32_t)0xff)   /* bit mask, DR[7:0]：8位数据寄存器 (8-bit data register)
用于存放接收到的数据（或者从接收FIFO读出的数据）或放置用于发送到总线的数据（或者写入到发送FIFO的数据）
发送器模式：当写一个字节至DR寄存器时，自动启动数据传输。一旦传输开始(TxE=1)，如果能及时把下一个需传输的数据写入DR寄存器，（或者发送FIFO非空时），I2C模块将保持连续的数据流。
接收器模式：接收到的字节被拷贝到DR寄存器(RxNE=1)。在接收到下一个字节(RxNE=1)之前读出数据寄存器，（或者接收FIFO非满时），即可实现连续的数据传送。
注：在从模式下，地址不会被拷贝进数据寄存器DR；
注：硬件不管理写冲突(如果TxE=0，仍能写入数据寄存器)；
注：如果在处理ACK脉冲时发生ARLO事件，接收到的字节不会被拷贝到数据寄存器里，因此不能读到它。
*/
#define I2C_DR_DR_Pos             ((uint32_t)0)   /*bit position, DR[7:0]：8位数据寄存器 (8-bit data register)
用于存放接收到的数据（或者从接收FIFO读出的数据）或放置用于发送到总线的数据（或者写入到发送FIFO的数据）
发送器模式：当写一个字节至DR寄存器时，自动启动数据传输。一旦传输开始(TxE=1)，如果能及时把下一个需传输的数据写入DR寄存器，（或者发送FIFO非空时），I2C模块将保持连续的数据流。
接收器模式：接收到的字节被拷贝到DR寄存器(RxNE=1)。在接收到下一个字节(RxNE=1)之前读出数据寄存器，（或者接收FIFO非满时），即可实现连续的数据传送。
注：在从模式下，地址不会被拷贝进数据寄存器DR；
注：硬件不管理写冲突(如果TxE=0，仍能写入数据寄存器)；
注：如果在处理ACK脉冲时发生ARLO事件，接收到的字节不会被拷贝到数据寄存器里，因此不能读到它。
*/

/******************  Bit Definition for Register I2C_SR1  *********************/
#define I2C_SR1_SB_Msk             ((uint32_t)0x1)   /* bit mask, SB：起始位(主模式) (Start bit (Master mode)) –  当发送出起始条件时该位被置’1’。
–  软件读取SR1寄存器后，写数据寄存器的操作将清除该位，或当PE=0时，硬件清除该位。
0: 未发送起始条件；
1: 起始条件已发送。
*/
#define I2C_SR1_SB_Pos             ((uint32_t)0)   /*bit position, SB：起始位(主模式) (Start bit (Master mode)) –  当发送出起始条件时该位被置’1’。
–  软件读取SR1寄存器后，写数据寄存器的操作将清除该位，或当PE=0时，硬件清除该位。
0: 未发送起始条件；
1: 起始条件已发送。
*/
#define I2C_SR1_ADDR_Msk             ((uint32_t)0x2)   /* bit mask, ADDR：地址已被发送(主模式)/地址匹配(从模式) (Address sent (master mode)/matched (slave mode))
在软件读取SR1寄存器后，对SR2寄存器的读操作将清除该位，或当PE=0时，由硬件清除该位。

0: 从模式：地址匹配，地址不匹配或没有收到地址；主模式：地址发送没有结束；
1: 从模式：地址匹配，收到的地址匹配；主模式：地址发送结束；
*/
#define I2C_SR1_ADDR_Pos             ((uint32_t)1)   /*bit position, ADDR：地址已被发送(主模式)/地址匹配(从模式) (Address sent (master mode)/matched (slave mode))
在软件读取SR1寄存器后，对SR2寄存器的读操作将清除该位，或当PE=0时，由硬件清除该位。

0: 从模式：地址匹配，地址不匹配或没有收到地址；主模式：地址发送没有结束；
1: 从模式：地址匹配，收到的地址匹配；主模式：地址发送结束；
*/
#define I2C_SR1_BTF_Msk             ((uint32_t)0x4)   /* bit mask, BTF：字节发送结束 (Byte transfer finished)当NOSTRETCH=0时，在下列情况下硬件将该位置’1’：
–  在接收时，当收到一个新字节(包括ACK脉冲)且数据寄存器还未被读取(RxNE=1)。
–  在发送时，当一个新数据将被发送且数据寄存器还未被写入新的数据(TxE=1)。
–  在软件读取SR1寄存器后，对数据寄存器的读或写操作将清除该位；或在传输中发送一个起始或停止条件后，或当PE=0时，由硬件清除该位。
注：在收到一个NACK后，BTF位不会被置位。
如果下一个要传输的字节是PEC(I2C_SR2寄存器中TRA为’1’，同时I2C_CR1寄存器中PEC 为’1’)，BTF位不会被置位。
0: 字节发送未完成
1: 字节发送结束
*/
#define I2C_SR1_BTF_Pos             ((uint32_t)2)   /*bit position, BTF：字节发送结束 (Byte transfer finished)当NOSTRETCH=0时，在下列情况下硬件将该位置’1’：
–  在接收时，当收到一个新字节(包括ACK脉冲)且数据寄存器还未被读取(RxNE=1)。
–  在发送时，当一个新数据将被发送且数据寄存器还未被写入新的数据(TxE=1)。
–  在软件读取SR1寄存器后，对数据寄存器的读或写操作将清除该位；或在传输中发送一个起始或停止条件后，或当PE=0时，由硬件清除该位。
注：在收到一个NACK后，BTF位不会被置位。
如果下一个要传输的字节是PEC(I2C_SR2寄存器中TRA为’1’，同时I2C_CR1寄存器中PEC 为’1’)，BTF位不会被置位。
0: 字节发送未完成
1: 字节发送结束
*/
#define I2C_SR1_ADD10_Msk             ((uint32_t)0x8)   /* bit mask, 10位头序列已发送(主模式) (10-bit header sent (Master mode)) –  在10位地址模式下，当主设备已经将第一个字节发送出去时，硬件将该位置’1’。
–  软件读取SR1寄存器后，对CR1寄存器的写操作将清除该位，或当PE=0时，硬件清除该位。
注：收到一个NACK后，ADD10位不被置位。
0: 没有ADD10事件发生
1: 主设备已经将第一个地址字节发送出去
*/
#define I2C_SR1_ADD10_Pos             ((uint32_t)3)   /*bit position, 10位头序列已发送(主模式) (10-bit header sent (Master mode)) –  在10位地址模式下，当主设备已经将第一个字节发送出去时，硬件将该位置’1’。
–  软件读取SR1寄存器后，对CR1寄存器的写操作将清除该位，或当PE=0时，硬件清除该位。
注：收到一个NACK后，ADD10位不被置位。
0: 没有ADD10事件发生
1: 主设备已经将第一个地址字节发送出去
*/
#define I2C_SR1_STOPF_Msk             ((uint32_t)0x10)   /* bit mask, STOPF：停止条件检测位(从模式) (Stop detection (slave mode)) –  在一个应答之后(如果ACK=1)，当从设备在总线上检测到停止条件时，硬件将该位置’1’。
–  软件读取SR1寄存器后，对CR1寄存器的写操作将清除该位，或当PE=0时，硬件清除该位。
注：在收到NACK后，STOPF位不被置位。
*/
#define I2C_SR1_STOPF_Pos             ((uint32_t)4)   /*bit position, STOPF：停止条件检测位(从模式) (Stop detection (slave mode)) –  在一个应答之后(如果ACK=1)，当从设备在总线上检测到停止条件时，硬件将该位置’1’。
–  软件读取SR1寄存器后，对CR1寄存器的写操作将清除该位，或当PE=0时，硬件清除该位。
注：在收到NACK后，STOPF位不被置位。
*/
#define I2C_SR1_TXSRE_Msk             ((uint32_t)0x20)   /* bit mask, TxSRE：当FIFO模式使能时的数据发送移位器空标志，读SR1后清除该位
0: 数据发送移位器非空
1: 数据发送移位器空
*/
#define I2C_SR1_TXSRE_Pos             ((uint32_t)5)   /*bit position, TxSRE：当FIFO模式使能时的数据发送移位器空标志，读SR1后清除该位
0: 数据发送移位器非空
1: 数据发送移位器空
*/
#define I2C_SR1_RXNE_Msk             ((uint32_t)0x40)   /* bit mask, RxNE：数据寄存器（或接收FIFO）非空(接收时) (Data register not empty (receivers)) –  在接收时，当数据寄存器不为空，该位被置’1’。在接收地址阶段，该位不被置位。
–  软件对数据寄存器的读写操作清除该位，或当PE=0时由硬件清除。在发生ARLO事件时，RxNE不被置位。
注：当设置了BTF时，读取数据不能清除RxNE位，因为数据寄存器仍然为满。
0: 数据寄存器（或接收FIFO）为空；
1: 数据寄存器（或接收FIFO）非空
*/
#define I2C_SR1_RXNE_Pos             ((uint32_t)6)   /*bit position, RxNE：数据寄存器（或接收FIFO）非空(接收时) (Data register not empty (receivers)) –  在接收时，当数据寄存器不为空，该位被置’1’。在接收地址阶段，该位不被置位。
–  软件对数据寄存器的读写操作清除该位，或当PE=0时由硬件清除。在发生ARLO事件时，RxNE不被置位。
注：当设置了BTF时，读取数据不能清除RxNE位，因为数据寄存器仍然为满。
0: 数据寄存器（或接收FIFO）为空；
1: 数据寄存器（或接收FIFO）非空
*/
#define I2C_SR1_TXE_Msk             ((uint32_t)0x80)   /* bit mask, TxE：数据寄存器（或发送FIFO）为空(发送时) (Data register empty (transmitters)) 如果收到一个NACK，或下一个要发送的字节是PEC(PEC=1)，该位不被置位。
注：在写入第1个要发送的数据后，或设置了BTF时写入数据，都不能清除TxE位，这是因为数据寄存器仍然为空。
0: 数据寄存器（或发送FIFO）非空；
1: 数据寄存器（或发送FIFO）空。
*/
#define I2C_SR1_TXE_Pos             ((uint32_t)7)   /*bit position, TxE：数据寄存器（或发送FIFO）为空(发送时) (Data register empty (transmitters)) 如果收到一个NACK，或下一个要发送的字节是PEC(PEC=1)，该位不被置位。
注：在写入第1个要发送的数据后，或设置了BTF时写入数据，都不能清除TxE位，这是因为数据寄存器仍然为空。
0: 数据寄存器（或发送FIFO）非空；
1: 数据寄存器（或发送FIFO）空。
*/
#define I2C_SR1_BERR_Msk             ((uint32_t)0x100)   /* bit mask, BERR：总线出错 (Bus error) –  当接口检测到错误的起始或停止条件，硬件将该位置’1’。
–  该位由软件写’0’清除，或在PE=0时由硬件清除。
0: 无起始或停止条件出错；
1: 起始或停止条件出错。
*/
#define I2C_SR1_BERR_Pos             ((uint32_t)8)   /*bit position, BERR：总线出错 (Bus error) –  当接口检测到错误的起始或停止条件，硬件将该位置’1’。
–  该位由软件写’0’清除，或在PE=0时由硬件清除。
0: 无起始或停止条件出错；
1: 起始或停止条件出错。
*/
#define I2C_SR1_ARLO_Msk             ((uint32_t)0x200)   /* bit mask, ARLO：仲裁丢失(主模式) (Arbitration lost (master mode)) 当接口失去对总线的控制给另一个主机时，硬件将将置该位为’1’。
– 该位由软件写’0’清除，或在PE=0时由硬件清除。
在ARLO事件之后，I2C接口自动切换回从模式(M/SL=0)。
注：在SMBUS模式下，在从模式下对数据的仲裁仅仅发生在数据阶段，或应答传输区间(不包括地址的应答)。
0: 没有检测到仲裁丢失；
1: 检测到仲裁丢失。
*/
#define I2C_SR1_ARLO_Pos             ((uint32_t)9)   /*bit position, ARLO：仲裁丢失(主模式) (Arbitration lost (master mode)) 当接口失去对总线的控制给另一个主机时，硬件将将置该位为’1’。
– 该位由软件写’0’清除，或在PE=0时由硬件清除。
在ARLO事件之后，I2C接口自动切换回从模式(M/SL=0)。
注：在SMBUS模式下，在从模式下对数据的仲裁仅仅发生在数据阶段，或应答传输区间(不包括地址的应答)。
0: 没有检测到仲裁丢失；
1: 检测到仲裁丢失。
*/
#define I2C_SR1_AF_Msk             ((uint32_t)0x400)   /* bit mask, AF：应答失败 (Acknowledge failure) –  当没有返回应答时，硬件将置该位为’1’。
–  该位由软件写’0’清除，或在PE=0时由硬件清除。
0: 没有应答失败；
1: 应答失败。
*/
#define I2C_SR1_AF_Pos             ((uint32_t)10)   /*bit position, AF：应答失败 (Acknowledge failure) –  当没有返回应答时，硬件将置该位为’1’。
–  该位由软件写’0’清除，或在PE=0时由硬件清除。
0: 没有应答失败；
1: 应答失败。
*/
#define I2C_SR1_OVR_Msk             ((uint32_t)0x800)   /* bit mask, OVR：过载/欠载 (Overrun/Underrun) –  当NOSTRETCH=1时，在从模式下该位被硬件置位，同时：
–  在接收模式中当收到一个新的字节时(包括ACK应答脉冲)，数据寄存器里的内容还未被读出，则新接收的字节将丢失。
–  在发送模式中当要发送一个新的字节时，却没有新的数据写入数据寄存器，同样的字节将被发送两次。
–  该位由软件写’0’清除，或在PE=0时由硬件清除。。
注：如果数据寄存器的写操作发生时间非常接近SCL的上升沿，发送的数据是不确定的，并发生保持时间错误。
0: 无过载/欠载；
1: 出现过载/欠载。
*/
#define I2C_SR1_OVR_Pos             ((uint32_t)11)   /*bit position, OVR：过载/欠载 (Overrun/Underrun) –  当NOSTRETCH=1时，在从模式下该位被硬件置位，同时：
–  在接收模式中当收到一个新的字节时(包括ACK应答脉冲)，数据寄存器里的内容还未被读出，则新接收的字节将丢失。
–  在发送模式中当要发送一个新的字节时，却没有新的数据写入数据寄存器，同样的字节将被发送两次。
–  该位由软件写’0’清除，或在PE=0时由硬件清除。。
注：如果数据寄存器的写操作发生时间非常接近SCL的上升沿，发送的数据是不确定的，并发生保持时间错误。
0: 无过载/欠载；
1: 出现过载/欠载。
*/
#define I2C_SR1_PECERR_Msk             ((uint32_t)0x1000)   /* bit mask, PECERR：在接收时发生PEC错误 (PEC Error in reception) – 该位由软件写’0’清除，或在PE=0时由硬件清除。
0: 无PEC错误：接收到PEC后接收器返回ACK(如果ACK=1)；
1: 有PEC错误：接收到PEC后接收器返回NACK(不管ACK是什么值)。
*/
#define I2C_SR1_PECERR_Pos             ((uint32_t)12)   /*bit position, PECERR：在接收时发生PEC错误 (PEC Error in reception) – 该位由软件写’0’清除，或在PE=0时由硬件清除。
0: 无PEC错误：接收到PEC后接收器返回ACK(如果ACK=1)；
1: 有PEC错误：接收到PEC后接收器返回NACK(不管ACK是什么值)。
*/

/******************  Bit Definition for Register I2C_SR2  *********************/
#define I2C_SR2_MSL_Msk             ((uint32_t)0x1)   /* bit mask, MSL：主从模式 (Master/slave) –  当接口处于主模式(SB=1)时，硬件将该位置位；
–  当总线上检测到一个停止条件、仲裁丢失(ARLO=1时)、或当PE=0时，硬件清除该位。
0: 从模式
1: 主模式
*/
#define I2C_SR2_MSL_Pos             ((uint32_t)0)   /*bit position, MSL：主从模式 (Master/slave) –  当接口处于主模式(SB=1)时，硬件将该位置位；
–  当总线上检测到一个停止条件、仲裁丢失(ARLO=1时)、或当PE=0时，硬件清除该位。
0: 从模式
1: 主模式
*/
#define I2C_SR2_BUSY_Msk             ((uint32_t)0x2)   /* bit mask, BUSY：总线忙 (Bus busy) –  在检测到SDA或SCl为低电平时，硬件将该位置’1’；
–  当检测到一个停止条件时，硬件将该位清除。
该位指示当前正在进行的总线通讯，当接口被禁用(PE=0)时该信息仍然被更新
0: 在总线上无数据通讯；
1: 在总线上正在进行数据通讯
*/
#define I2C_SR2_BUSY_Pos             ((uint32_t)1)   /*bit position, BUSY：总线忙 (Bus busy) –  在检测到SDA或SCl为低电平时，硬件将该位置’1’；
–  当检测到一个停止条件时，硬件将该位清除。
该位指示当前正在进行的总线通讯，当接口被禁用(PE=0)时该信息仍然被更新
0: 在总线上无数据通讯；
1: 在总线上正在进行数据通讯
*/
#define I2C_SR2_TRA_Msk             ((uint32_t)0x4)   /* bit mask, TRA：发送/接收 (Transmitter/receiver) 在整个地址传输阶段的结尾，该位根据地址字节的R/W位来设定。
在检测到停止条件(STOPF=1)、重复的起始条件或总线仲裁丢失(ARLO=1)后，或当PE=0 时，硬件将其清除。
0: 接收到数据；
1: 数据已发送
*/
#define I2C_SR2_TRA_Pos             ((uint32_t)2)   /*bit position, TRA：发送/接收 (Transmitter/receiver) 在整个地址传输阶段的结尾，该位根据地址字节的R/W位来设定。
在检测到停止条件(STOPF=1)、重复的起始条件或总线仲裁丢失(ARLO=1)后，或当PE=0 时，硬件将其清除。
0: 接收到数据；
1: 数据已发送
*/
#define I2C_SR2_GENCALL_Msk             ((uint32_t)0x10)   /* bit mask, GENCALL：广播呼叫地址(从模式) (General call address (Slave mode))，– 在产生一个停止条件或一个重复的起始条件时，或PE=0时，硬件将该位清除。
0: 未收到广播呼叫地址；
1: 当ENGC=1时，收到广播呼叫的地址。
*/
#define I2C_SR2_GENCALL_Pos             ((uint32_t)4)   /*bit position, GENCALL：广播呼叫地址(从模式) (General call address (Slave mode))，– 在产生一个停止条件或一个重复的起始条件时，或PE=0时，硬件将该位清除。
0: 未收到广播呼叫地址；
1: 当ENGC=1时，收到广播呼叫的地址。
*/
#define I2C_SR2_DUALF_Msk             ((uint32_t)0x80)   /* bit mask, 双标志(从模式) (Dual flag (Slave mode)) ，在产生一个停止条件或一个重复的起始条件时，或PE=0时，硬件将该位清除。
0: 接收到的地址与OAR1内的内容相匹配
1: 接收到的地址与OAR2内的内容相匹配。
*/
#define I2C_SR2_DUALF_Pos             ((uint32_t)7)   /*bit position, 双标志(从模式) (Dual flag (Slave mode)) ，在产生一个停止条件或一个重复的起始条件时，或PE=0时，硬件将该位清除。
0: 接收到的地址与OAR1内的内容相匹配
1: 接收到的地址与OAR2内的内容相匹配。
*/
#define I2C_SR2_PEC_Msk             ((uint32_t)0xff00)   /* bit mask, 数据包出错检测 (Packet error checking register)
当ENPEC=1时，PEC[7:0]存放内部的PEC的值。
*/
#define I2C_SR2_PEC_Pos             ((uint32_t)8)   /*bit position, 数据包出错检测 (Packet error checking register)
当ENPEC=1时，PEC[7:0]存放内部的PEC的值。
*/

/******************  Bit Definition for Register I2C_CCR  *********************/
#define I2C_CCR_CLKC_Msk             ((uint32_t)0xfff)   /* bit mask, CLKC[11:0] ： 
主机模式下I2C时钟控制 
标准速度模式下：Thigh=Tlow=CLKC*TPCLK1 
如果DTCY=0，快速模式或快速+模式下： 
Thigh=CLKC*TPCLK1 , Tlow=2*CLKC*TPCLK1 
如果DTCY=1，快速模式或快速+模式下： 
Thigh=9*CLKC*TPCLK1 , Tlow=16*CLKC*TPCLK1
*/
#define I2C_CCR_CLKC_Pos             ((uint32_t)0)   /*bit position, CLKC[11:0] ： 
主机模式下I2C时钟控制 
标准速度模式下：Thigh=Tlow=CLKC*TPCLK1 
如果DTCY=0，快速模式或快速+模式下： 
Thigh=CLKC*TPCLK1 , Tlow=2*CLKC*TPCLK1 
如果DTCY=1，快速模式或快速+模式下： 
Thigh=9*CLKC*TPCLK1 , Tlow=16*CLKC*TPCLK1
*/
#define I2C_CCR_DUTY_Msk             ((uint32_t)0x4000)   /* bit mask, DUTY：快速模式时的占空比 (Fast mode duty cycle) 
0: 快速模式下：Tlow/Thigh = 2；
1: 快速模式下：Tlow/Thigh = 16/9
*/
#define I2C_CCR_DUTY_Pos             ((uint32_t)14)   /*bit position, DUTY：快速模式时的占空比 (Fast mode duty cycle) 
0: 快速模式下：Tlow/Thigh = 2；
1: 快速模式下：Tlow/Thigh = 16/9
*/
#define I2C_CCR_F_S_Msk             ((uint32_t)0x8000)   /* bit mask, F/S：I2C主模式选项 (I2C master mode selection) 
0: 标准模式的I2C
1: 快速模式的I2C
*/
#define I2C_CCR_F_S_Pos             ((uint32_t)15)   /*bit position, F/S：I2C主模式选项 (I2C master mode selection) 
0: 标准模式的I2C
1: 快速模式的I2C
*/

/******************  Bit Definition for Register I2C_TRISE  *********************/
#define I2C_TRISE_TRISE_Msk             ((uint32_t)0x7f)   /* bit mask, TRISE[6:0] ：在快速/ 标准模式下的最大上升时间( 主模式) (Maximum rise time in Fast/Standard mode (Master mode))
这些位必须设置为I2C总线规范里给出的最大的SCL上升时间，增长步幅为1。
例如：标准模式中最大允许SCL上升时间为1000ns。如果在I2C_CR2寄存器中FREQ[6:0]中的值等于0x08且TPCLK1=125ns，故TRISE[6:0]中必须写入09h(1000ns/125 ns = 8+1)。
滤波器的值也可以加到TRISE[6:0]内。
如果结果不是一个整数，则将整数部分写入TRISE[6:0]以确保tHIGH参数。注：只有当I2C被禁用(PE=0)时，才能设置TRISE[6:0]
*/
#define I2C_TRISE_TRISE_Pos             ((uint32_t)0)   /*bit position, TRISE[6:0] ：在快速/ 标准模式下的最大上升时间( 主模式) (Maximum rise time in Fast/Standard mode (Master mode))
这些位必须设置为I2C总线规范里给出的最大的SCL上升时间，增长步幅为1。
例如：标准模式中最大允许SCL上升时间为1000ns。如果在I2C_CR2寄存器中FREQ[6:0]中的值等于0x08且TPCLK1=125ns，故TRISE[6:0]中必须写入09h(1000ns/125 ns = 8+1)。
滤波器的值也可以加到TRISE[6:0]内。
如果结果不是一个整数，则将整数部分写入TRISE[6:0]以确保tHIGH参数。注：只有当I2C被禁用(PE=0)时，才能设置TRISE[6:0]
*/

/******************************************************************************/
/*                    AON                         */
/******************************************************************************/


/******************  Bit Definition for Register BKP_RTCCR  *********************/
#define AON_BKP_RTCCR_CCO_Msk             ((uint32_t)0x80)   /* bit mask, RTC时钟输出*/
#define AON_BKP_RTCCR_CCO_Pos             ((uint32_t)7)   /*bit position, RTC时钟输出*/
#define AON_BKP_RTCCR_ASOE_Msk             ((uint32_t)0x100)   /* bit mask, RTC秒中断或闹钟中断输出使能*/
#define AON_BKP_RTCCR_ASOE_Pos             ((uint32_t)8)   /*bit position, RTC秒中断或闹钟中断输出使能*/
#define AON_BKP_RTCCR_ASOS_Msk             ((uint32_t)0x200)   /* bit mask, RTC秒中断或闹钟中断输出选择*/
#define AON_BKP_RTCCR_ASOS_Pos             ((uint32_t)9)   /*bit position, RTC秒中断或闹钟中断输出选择*/
#define AON_BKP_RTCCR_RESERVE_Msk             ((uint32_t)0x7f)   /* bit mask, 保留*/
#define AON_BKP_RTCCR_RESERVE_Pos             ((uint32_t)0)   /*bit position, 保留*/

/******************************************************************************/
/*                    PWR                         */
/******************************************************************************/


/******************  Bit Definition for Register CR  *********************/
#define PWR_CR_LPDS_Msk             ((uint32_t)0x1)   /* bit mask, 当CPU的deepsleep置起后，该位决定进入深度睡眠1或者深度睡眠2*/
#define PWR_CR_LPDS_Pos             ((uint32_t)0)   /*bit position, 当CPU的deepsleep置起后，该位决定进入深度睡眠1或者深度睡眠2*/
#define PWR_CR_DBP_Msk             ((uint32_t)0x100)   /* bit mask, 取消AON区域的写保护
在复位后，RTC和AON寄存器处于被保护状态以防意外写入。设置这位允许写入这些寄存器。注：如果RTC的时钟是HSE/128，该位必须保持为’1’。
*/
#define PWR_CR_DBP_Pos             ((uint32_t)8)   /*bit position, 取消AON区域的写保护
在复位后，RTC和AON寄存器处于被保护状态以防意外写入。设置这位允许写入这些寄存器。注：如果RTC的时钟是HSE/128，该位必须保持为’1’。
*/
#define PWR_CR_ADC_MSYS_EN_Msk             ((uint32_t)0x200)   /* bit mask, SNOOZE模式使能*/
#define PWR_CR_ADC_MSYS_EN_Pos             ((uint32_t)9)   /*bit position, SNOOZE模式使能*/
#define PWR_CR_ADC_MSYS_TSEL_Msk             ((uint32_t)0x1c00)   /* bit mask, 触发SNOOZE模式条件选择*/
#define PWR_CR_ADC_MSYS_TSEL_Pos             ((uint32_t)10)   /*bit position, 触发SNOOZE模式条件选择*/
#define PWR_CR_PVDE_Msk             ((uint32_t)0x10)   /* bit mask,  programmable voltage detector enable*/
#define PWR_CR_PVDE_Pos             ((uint32_t)4)   /*bit position,  programmable voltage detector enable*/
#define PWR_CR_PVDMODE_Msk             ((uint32_t)0x10000)   /* bit mask, 低电压检测信号选择：0=DVDD5, 1=AVDD5*/
#define PWR_CR_PVDMODE_Pos             ((uint32_t)16)   /*bit position, 低电压检测信号选择：0=DVDD5, 1=AVDD5*/
#define PWR_CR_PSM_VTH_DVDD_Msk             ((uint32_t)0xe0000)   /* bit mask, DVDD低电压检测阈值挡位*/
#define PWR_CR_PSM_VTH_DVDD_Pos             ((uint32_t)17)   /*bit position, DVDD低电压检测阈值挡位*/
#define PWR_CR_PSM_VTH_AVDD_Msk             ((uint32_t)0x700000)   /* bit mask, AVDD低电压检测阈值挡位*/
#define PWR_CR_PSM_VTH_AVDD_Pos             ((uint32_t)20)   /*bit position, AVDD低电压检测阈值挡位*/
#define PWR_CR_PDM_Msk             ((uint32_t)0x2)   /* bit mask, 当配置该bit=1，发起deepsleep1或2操作后进入关断模式*/
#define PWR_CR_PDM_Pos             ((uint32_t)1)   /*bit position, 当配置该bit=1，发起deepsleep1或2操作后进入关断模式*/

/******************  Bit Definition for Register CSR  *********************/
#define PWR_CSR_LVDO_Msk             ((uint32_t)0x4)   /* bit mask, 低电压检测LVD输出状态
当LVD被AFE_MMR模块中的LVDCON_EN位使能后该位才有效
*/
#define PWR_CSR_LVDO_Pos             ((uint32_t)2)   /*bit position, 低电压检测LVD输出状态
当LVD被AFE_MMR模块中的LVDCON_EN位使能后该位才有效
*/
#define PWR_CSR_RESERVED_Msk             ((uint32_t)0x2)   /* bit mask, 保留*/
#define PWR_CSR_RESERVED_Pos             ((uint32_t)1)   /*bit position, 保留*/

/******************************************************************************/
/*                    EXTI                         */
/******************************************************************************/


/******************  Bit Definition for Register EXTI_IMR  *********************/
#define EXTI_IMR_MRX_Msk             ((uint32_t)0x3fff)   /* bit mask, MRx: 线x上的中断屏蔽 (Interrupt Mask on line x) 
0：屏蔽来自线x上的中断请求；
1：开放来自线x上的中断请求。*/
#define EXTI_IMR_MRX_Pos             ((uint32_t)0)   /*bit position, MRx: 线x上的中断屏蔽 (Interrupt Mask on line x) 
0：屏蔽来自线x上的中断请求；
1：开放来自线x上的中断请求。*/

/******************  Bit Definition for Register EXTI_EMR  *********************/
#define EXTI_EMR_MRX_Msk             ((uint32_t)0x3fff)   /* bit mask, MRx: 线x上的事件屏蔽 (Event Mask on line x) 
0：屏蔽来自线x上的事件请求；
1：开放来自线x上的事件请求。*/
#define EXTI_EMR_MRX_Pos             ((uint32_t)0)   /*bit position, MRx: 线x上的事件屏蔽 (Event Mask on line x) 
0：屏蔽来自线x上的事件请求；
1：开放来自线x上的事件请求。*/

/******************  Bit Definition for Register EXTI_RTSR  *********************/
#define EXTI_RTSR_TRX_Msk             ((uint32_t)0x3fff)   /* bit mask, TRx: 线x上的上升沿触发事件配置位 (Rising trigger event configuration bit of line x) 
0：禁止输入线x上的上升沿触发(中断和事件)
1：允许输入线x上的上升沿触发(中断和事件)*/
#define EXTI_RTSR_TRX_Pos             ((uint32_t)0)   /*bit position, TRx: 线x上的上升沿触发事件配置位 (Rising trigger event configuration bit of line x) 
0：禁止输入线x上的上升沿触发(中断和事件)
1：允许输入线x上的上升沿触发(中断和事件)*/

/******************  Bit Definition for Register EXTI_FTSR  *********************/
#define EXTI_FTSR_TRX_Msk             ((uint32_t)0x3fff)   /* bit mask, TRx: 线x上的下降沿触发事件配置位 (Falling trigger event configuration bit of line x) 
0：禁止输入线x上的下降沿触发(中断和事件)
1：允许输入线x上的下降沿触发(中断和事件)*/
#define EXTI_FTSR_TRX_Pos             ((uint32_t)0)   /*bit position, TRx: 线x上的下降沿触发事件配置位 (Falling trigger event configuration bit of line x) 
0：禁止输入线x上的下降沿触发(中断和事件)
1：允许输入线x上的下降沿触发(中断和事件)*/

/******************  Bit Definition for Register EXTI_SWIER  *********************/
#define EXTI_SWIER_SWIERX_Msk             ((uint32_t)0x3fff)   /* bit mask, SWIERx: 线x上的软件中断 (Software interrupt on line x)
当该位为’0’时，写’1’将设置EXTI_PR中相应的挂起位。如果在EXTI_IMR和EXTI_EMR中允许产生该中断，则此时将产生一个中断。
注：通过清除EXTI_PR的对应位(写入’1’)，可以清除该位为’0’。*/
#define EXTI_SWIER_SWIERX_Pos             ((uint32_t)0)   /*bit position, SWIERx: 线x上的软件中断 (Software interrupt on line x)
当该位为’0’时，写’1’将设置EXTI_PR中相应的挂起位。如果在EXTI_IMR和EXTI_EMR中允许产生该中断，则此时将产生一个中断。
注：通过清除EXTI_PR的对应位(写入’1’)，可以清除该位为’0’。*/

/******************  Bit Definition for Register EXTI_PR  *********************/
#define EXTI_PR_PRX_Msk             ((uint32_t)0x3fff)   /* bit mask, 可读/写1清
PRx: 挂起位 (Pending bit) 
0：没有发生触发请求
1：发生了选择的触发请求
当在外部中断线上发生了选择的边沿事件，该位被置’1’。在该位中写入’1’可以清除它，也可以通过改变边沿检测的极性清除。*/
#define EXTI_PR_PRX_Pos             ((uint32_t)0)   /*bit position, 可读/写1清
PRx: 挂起位 (Pending bit) 
0：没有发生触发请求
1：发生了选择的触发请求
当在外部中断线上发生了选择的边沿事件，该位被置’1’。在该位中写入’1’可以清除它，也可以通过改变边沿检测的极性清除。*/

/******************************************************************************/
/*                    GPIO                         */
/******************************************************************************/


/******************  Bit Definition for Register CON0  *********************/
#define GPIO_CON0_PORT0_0_SEL_Msk             ((uint32_t)0xf)   /* bit mask, 复用功能选择*/
#define GPIO_CON0_PORT0_0_SEL_Pos             ((uint32_t)0)   /*bit position, 复用功能选择*/
#define GPIO_CON0_PORT0_1_SEL_Msk             ((uint32_t)0xf0)   /* bit mask, 复用功能选择*/
#define GPIO_CON0_PORT0_1_SEL_Pos             ((uint32_t)4)   /*bit position, 复用功能选择*/
#define GPIO_CON0_PORT0_2_SEL_Msk             ((uint32_t)0xf00)   /* bit mask, 复用功能选择*/
#define GPIO_CON0_PORT0_2_SEL_Pos             ((uint32_t)8)   /*bit position, 复用功能选择*/
#define GPIO_CON0_PORT0_3_SEL_Msk             ((uint32_t)0xf000)   /* bit mask, 复用功能选择*/
#define GPIO_CON0_PORT0_3_SEL_Pos             ((uint32_t)12)   /*bit position, 复用功能选择*/
#define GPIO_CON0_PORT0_4_SEL_Msk             ((uint32_t)0xf0000)   /* bit mask, 复用功能选择*/
#define GPIO_CON0_PORT0_4_SEL_Pos             ((uint32_t)16)   /*bit position, 复用功能选择*/
#define GPIO_CON0_PORT0_5_SEL_Msk             ((uint32_t)0xf00000)   /* bit mask, 复用功能选择*/
#define GPIO_CON0_PORT0_5_SEL_Pos             ((uint32_t)20)   /*bit position, 复用功能选择*/
#define GPIO_CON0_PORT0_6_SEL_Msk             ((uint32_t)0xf000000)   /* bit mask, 复用功能选择*/
#define GPIO_CON0_PORT0_6_SEL_Pos             ((uint32_t)24)   /*bit position, 复用功能选择*/
#define GPIO_CON0_PORT0_7_SEL_Msk             ((uint32_t)0xf0000000)   /* bit mask, 复用功能选择*/
#define GPIO_CON0_PORT0_7_SEL_Pos             ((uint32_t)28)   /*bit position, 复用功能选择*/

/******************  Bit Definition for Register OE  *********************/
#define GPIO_OE_PORT0_OE_Msk             ((uint32_t)0xff)   /* bit mask, 输出使能*/
#define GPIO_OE_PORT0_OE_Pos             ((uint32_t)0)   /*bit position, 输出使能*/

/******************  Bit Definition for Register PUE  *********************/
#define GPIO_PUE_PORT0_PUE_Msk             ((uint32_t)0xff)   /* bit mask, 上拉使能*/
#define GPIO_PUE_PORT0_PUE_Pos             ((uint32_t)0)   /*bit position, 上拉使能*/

/******************  Bit Definition for Register PDE  *********************/
#define GPIO_PDE_PORT0_PDE_Msk             ((uint32_t)0xff)   /* bit mask, 下拉使能*/
#define GPIO_PDE_PORT0_PDE_Pos             ((uint32_t)0)   /*bit position, 下拉使能*/

/******************  Bit Definition for Register OD  *********************/
#define GPIO_OD_PORT0_OD_Msk             ((uint32_t)0xff)   /* bit mask, 漏极开路使能*/
#define GPIO_OD_PORT0_OD_Pos             ((uint32_t)0)   /*bit position, 漏极开路使能*/

/******************  Bit Definition for Register IE  *********************/
#define GPIO_IE_PORT0_OD_Msk             ((uint32_t)0xff)   /* bit mask, 输入使能*/
#define GPIO_IE_PORT0_OD_Pos             ((uint32_t)0)   /*bit position, 输入使能*/

/******************  Bit Definition for Register SMT  *********************/
#define GPIO_SMT_PORT0_SMT_Msk             ((uint32_t)0xff)   /* bit mask, 施密特输入使能*/
#define GPIO_SMT_PORT0_SMT_Pos             ((uint32_t)0)   /*bit position, 施密特输入使能*/

/******************  Bit Definition for Register SL  *********************/
#define GPIO_SL_PORT0_SL_Msk             ((uint32_t)0xff)   /* bit mask, 0:fast 1:slow*/
#define GPIO_SL_PORT0_SL_Pos             ((uint32_t)0)   /*bit position, 0:fast 1:slow*/

/******************  Bit Definition for Register DR  *********************/
#define GPIO_DR_PORT0_0_DR_Msk             ((uint32_t)0x3)   /* bit mask, 驱动能力选择*/
#define GPIO_DR_PORT0_0_DR_Pos             ((uint32_t)0)   /*bit position, 驱动能力选择*/
#define GPIO_DR_PORT0_1_DR_Msk             ((uint32_t)0xc)   /* bit mask, 驱动能力选择*/
#define GPIO_DR_PORT0_1_DR_Pos             ((uint32_t)2)   /*bit position, 驱动能力选择*/
#define GPIO_DR_PORT0_2_DR_Msk             ((uint32_t)0x30)   /* bit mask, 驱动能力选择*/
#define GPIO_DR_PORT0_2_DR_Pos             ((uint32_t)4)   /*bit position, 驱动能力选择*/
#define GPIO_DR_PORT0_3_DR_Msk             ((uint32_t)0xc0)   /* bit mask, 驱动能力选择*/
#define GPIO_DR_PORT0_3_DR_Pos             ((uint32_t)6)   /*bit position, 驱动能力选择*/
#define GPIO_DR_PORT0_4_DR_Msk             ((uint32_t)0x300)   /* bit mask, 驱动能力选择*/
#define GPIO_DR_PORT0_4_DR_Pos             ((uint32_t)8)   /*bit position, 驱动能力选择*/
#define GPIO_DR_PORT0_5_DR_Msk             ((uint32_t)0xc00)   /* bit mask, 驱动能力选择*/
#define GPIO_DR_PORT0_5_DR_Pos             ((uint32_t)10)   /*bit position, 驱动能力选择*/
#define GPIO_DR_PORT0_6_DR_Msk             ((uint32_t)0x3000)   /* bit mask, 驱动能力选择*/
#define GPIO_DR_PORT0_6_DR_Pos             ((uint32_t)12)   /*bit position, 驱动能力选择*/
#define GPIO_DR_PORT0_7_DR_Msk             ((uint32_t)0xc000)   /* bit mask, 驱动能力选择*/
#define GPIO_DR_PORT0_7_DR_Pos             ((uint32_t)14)   /*bit position, 驱动能力选择*/

/******************  Bit Definition for Register DATA_IN  *********************/
#define GPIO_DATA_IN_PORT0_DIN_Msk             ((uint32_t)0xff)   /* bit mask, 输入数据*/
#define GPIO_DATA_IN_PORT0_DIN_Pos             ((uint32_t)0)   /*bit position, 输入数据*/
#define GPIO_DATA_IN_RESERVED_Msk             ((uint32_t)0xffffff00)   /* bit mask, 保留*/
#define GPIO_DATA_IN_RESERVED_Pos             ((uint32_t)8)   /*bit position, 保留*/

/******************  Bit Definition for Register DATA_OUT  *********************/
#define GPIO_DATA_OUT_PORT0_OUT_Msk             ((uint32_t)0xff)   /* bit mask, 输出数据*/
#define GPIO_DATA_OUT_PORT0_OUT_Pos             ((uint32_t)0)   /*bit position, 输出数据*/
#define GPIO_DATA_OUT_RESERVED_Msk             ((uint32_t)0xffffff00)   /* bit mask, 保留*/
#define GPIO_DATA_OUT_RESERVED_Pos             ((uint32_t)8)   /*bit position, 保留*/

/******************  Bit Definition for Register OSET  *********************/
#define GPIO_OSET_PORT0_OSET_Msk             ((uint32_t)0xff)   /* bit mask, 输出置1*/
#define GPIO_OSET_PORT0_OSET_Pos             ((uint32_t)0)   /*bit position, 输出置1*/

/******************  Bit Definition for Register OCLR  *********************/
#define GPIO_OCLR_PORT0_OCLR_Msk             ((uint32_t)0xff)   /* bit mask, 输出清零*/
#define GPIO_OCLR_PORT0_OCLR_Pos             ((uint32_t)0)   /*bit position, 输出清零*/

/******************  Bit Definition for Register OTGL  *********************/
#define GPIO_OTGL_PORT0_OTGL_Msk             ((uint32_t)0xff)   /* bit mask, 输出翻转*/
#define GPIO_OTGL_PORT0_OTGL_Pos             ((uint32_t)0)   /*bit position, 输出翻转*/

/******************  Bit Definition for Register INT_SEL  *********************/
#define GPIO_INT_SEL_BIT_3_0_Msk             ((uint32_t)0xf)   /* bit mask, 3’b000:P0_0作为外中断EXTI0的源
3’b001:P1_0作为外中断EXTI0的源
3’b010:P2_0作为外中断EXTI0的源
3’b011:P3_0作为外中断EXTI0的源
3’b100:P4_0作为外中断EXTI0的源
其他 ：P0_0作为外中断EXTI0的源*/
#define GPIO_INT_SEL_BIT_3_0_Pos             ((uint32_t)0)   /*bit position, 3’b000:P0_0作为外中断EXTI0的源
3’b001:P1_0作为外中断EXTI0的源
3’b010:P2_0作为外中断EXTI0的源
3’b011:P3_0作为外中断EXTI0的源
3’b100:P4_0作为外中断EXTI0的源
其他 ：P0_0作为外中断EXTI0的源*/
#define GPIO_INT_SEL_BIT_7_4_Msk             ((uint32_t)0xf0)   /* bit mask, 3’b000:P0_1作为外中断EXTI1的源
3’b001:P1_1作为外中断EXTI1的源
3’b010:P2_1作为外中断EXTI1的源
3’b011:P3_1作为外中断EXTI1的源
3’b100:P4_1作为外中断EXTI1的源
其他 ：P0_1作为外中断EXTI1的源*/
#define GPIO_INT_SEL_BIT_7_4_Pos             ((uint32_t)4)   /*bit position, 3’b000:P0_1作为外中断EXTI1的源
3’b001:P1_1作为外中断EXTI1的源
3’b010:P2_1作为外中断EXTI1的源
3’b011:P3_1作为外中断EXTI1的源
3’b100:P4_1作为外中断EXTI1的源
其他 ：P0_1作为外中断EXTI1的源*/
#define GPIO_INT_SEL_BIT_11_8_Msk             ((uint32_t)0xf00)   /* bit mask, 3’b000:P0_2作为外中断EXTI2的源
3’b001:P1_2作为外中断EXTI2的源
3’b010:P2_2作为外中断EXTI2的源
3’b011:P3_2作为外中断EXTI2的源
3’b100:P4_2作为外中断EXTI2的源
其他 ：P0_2作为外中断EXTI2的源*/
#define GPIO_INT_SEL_BIT_11_8_Pos             ((uint32_t)8)   /*bit position, 3’b000:P0_2作为外中断EXTI2的源
3’b001:P1_2作为外中断EXTI2的源
3’b010:P2_2作为外中断EXTI2的源
3’b011:P3_2作为外中断EXTI2的源
3’b100:P4_2作为外中断EXTI2的源
其他 ：P0_2作为外中断EXTI2的源*/
#define GPIO_INT_SEL_BIT_15_12_Msk             ((uint32_t)0xf000)   /* bit mask, 3’b000:P0_3作为外中断EXTI3的源
3’b001:P1_3作为外中断EXTI3的源
3’b010:P2_3作为外中断EXTI3的源
3’b011:P3_3作为外中断EXTI3的源

其他 ：P0_3作为外中断EXTI3的源*/
#define GPIO_INT_SEL_BIT_15_12_Pos             ((uint32_t)12)   /*bit position, 3’b000:P0_3作为外中断EXTI3的源
3’b001:P1_3作为外中断EXTI3的源
3’b010:P2_3作为外中断EXTI3的源
3’b011:P3_3作为外中断EXTI3的源

其他 ：P0_3作为外中断EXTI3的源*/
#define GPIO_INT_SEL_BIT_19_16_Msk             ((uint32_t)0xf0000)   /* bit mask, 3’b000:P0_4作为外中断EXTI4的源
3’b001:P1_4作为外中断EXTI4的源
3’b010:P2_4作为外中断EXTI4的源
3’b011:P3_4作为外中断EXTI4的源

其他 ：P0_4作为外中断EXTI4的源*/
#define GPIO_INT_SEL_BIT_19_16_Pos             ((uint32_t)16)   /*bit position, 3’b000:P0_4作为外中断EXTI4的源
3’b001:P1_4作为外中断EXTI4的源
3’b010:P2_4作为外中断EXTI4的源
3’b011:P3_4作为外中断EXTI4的源

其他 ：P0_4作为外中断EXTI4的源*/
#define GPIO_INT_SEL_BIT_23_20_Msk             ((uint32_t)0xf00000)   /* bit mask, 3’b000:P0_5作为外中断EXTI5的源
3’b001:P1_5作为外中断EXTI5的源
3’b010:P2_5作为外中断EXTI5的源
3’b011:P3_5作为外中断EXTI5的源

其他 ：P0_5作为外中断EXTI5的源*/
#define GPIO_INT_SEL_BIT_23_20_Pos             ((uint32_t)20)   /*bit position, 3’b000:P0_5作为外中断EXTI5的源
3’b001:P1_5作为外中断EXTI5的源
3’b010:P2_5作为外中断EXTI5的源
3’b011:P3_5作为外中断EXTI5的源

其他 ：P0_5作为外中断EXTI5的源*/
#define GPIO_INT_SEL_BIT_27_24_Msk             ((uint32_t)0xf000000)   /* bit mask, 3’b000:P0_6作为外中断EXTI6的源
3’b001:P1_6作为外中断EXTI6的源
3’b010:P2_6作为外中断EXTI6的源
3’b011:P3_6作为外中断EXTI6的源

其他 ：P0_6作为外中断EXTI6的源*/
#define GPIO_INT_SEL_BIT_27_24_Pos             ((uint32_t)24)   /*bit position, 3’b000:P0_6作为外中断EXTI6的源
3’b001:P1_6作为外中断EXTI6的源
3’b010:P2_6作为外中断EXTI6的源
3’b011:P3_6作为外中断EXTI6的源

其他 ：P0_6作为外中断EXTI6的源*/
#define GPIO_INT_SEL_BIT_31_28_Msk             ((uint32_t)0xf0000000)   /* bit mask, 3’b000:P0_7作为外中断EXTI7的源
3’b001:P1_7作为外中断EXTI7的源
3’b010:P2_7作为外中断EXTI7的源
3’b011:P3_7作为外中断EXTI7的源

其他 ：P0_7作为外中断EXTI7的源*/
#define GPIO_INT_SEL_BIT_31_28_Pos             ((uint32_t)28)   /*bit position, 3’b000:P0_7作为外中断EXTI7的源
3’b001:P1_7作为外中断EXTI7的源
3’b010:P2_7作为外中断EXTI7的源
3’b011:P3_7作为外中断EXTI7的源

其他 ：P0_7作为外中断EXTI7的源*/

/******************************************************************************/
/*                    AFE                         */
/******************************************************************************/


/******************  Bit Definition for Register NOP  *********************/
#define AFE_NOP_NOP_Msk             ((uint32_t)0x1)   /* bit mask, 空寄存器，没有功能*/
#define AFE_NOP_NOP_Pos             ((uint32_t)0)   /*bit position, 空寄存器，没有功能*/

/******************  Bit Definition for Register PAGE  *********************/
#define AFE_PAGE_PAGE_Msk             ((uint32_t)0xffffff)   /* bit mask, OWI访问寄存器的基地址*/
#define AFE_PAGE_PAGE_Pos             ((uint32_t)0)   /*bit position, OWI访问寄存器的基地址*/

/******************  Bit Definition for Register STATUS  *********************/
#define AFE_STATUS_RDYN1_Msk             ((uint32_t)0x2)   /* bit mask, ADC1转换完成标志*/
#define AFE_STATUS_RDYN1_Pos             ((uint32_t)1)   /*bit position, ADC1转换完成标志*/
#define AFE_STATUS_RDYN2_Msk             ((uint32_t)0x4)   /* bit mask, ADC2转换完成标志*/
#define AFE_STATUS_RDYN2_Pos             ((uint32_t)2)   /*bit position, ADC2转换完成标志*/
#define AFE_STATUS_ERROR_FLAG_Msk             ((uint32_t)0x8)   /* bit mask, 任何一个Error状态置位则置起该位*/
#define AFE_STATUS_ERROR_FLAG_Pos             ((uint32_t)3)   /*bit position, 任何一个Error状态置位则置起该位*/

/******************  Bit Definition for Register AFE_CFG  *********************/
#define AFE_CFG_PSW_EN_Msk             ((uint32_t)0x2)   /* bit mask, Power switch enable*/
#define AFE_CFG_PSW_EN_Pos             ((uint32_t)1)   /*bit position, Power switch enable*/
#define AFE_CFG_FAULT_ON_Msk             ((uint32_t)0x4)   /* bit mask, 错误报警使能*/
#define AFE_CFG_FAULT_ON_Pos             ((uint32_t)2)   /*bit position, 错误报警使能*/
#define AFE_CFG_FAULT_LVL_Msk             ((uint32_t)0x8)   /* bit mask, 错误报警电平配置*/
#define AFE_CFG_FAULT_LVL_Pos             ((uint32_t)3)   /*bit position, 错误报警电平配置*/
#define AFE_CFG_RESERVE_Msk             ((uint32_t)0x10)   /* bit mask, */
#define AFE_CFG_RESERVE_Pos             ((uint32_t)4)   /*bit position, */

/******************  Bit Definition for Register SPI_CFG  *********************/
#define AFE_SPI_CFG_SDO_OE_Msk             ((uint32_t)0x4)   /* bit mask, SDO输出使能，1-使能输出*/
#define AFE_SPI_CFG_SDO_OE_Pos             ((uint32_t)2)   /*bit position, SDO输出使能，1-使能输出*/

/******************  Bit Definition for Register PWM_CTRL  *********************/
#define AFE_PWM_CTRL_PRE_DIV_Msk             ((uint32_t)0x1f)   /* bit mask, PWM预分频系数，PWM周期=Tsys_clk*2*（PRE_DIV+1）*/
#define AFE_PWM_CTRL_PRE_DIV_Pos             ((uint32_t)0)   /*bit position, PWM预分频系数，PWM周期=Tsys_clk*2*（PRE_DIV+1）*/
#define AFE_PWM_CTRL_LACTH_EN_Msk             ((uint32_t)0x20)   /* bit mask, PWM计数开始时锁存输入数据*/
#define AFE_PWM_CTRL_LACTH_EN_Pos             ((uint32_t)5)   /*bit position, PWM计数开始时锁存输入数据*/
#define AFE_PWM_CTRL_OWI2_OUT_EN_Msk             ((uint32_t)0x80)   /* bit mask, 从OWI2引脚输出PWM*/
#define AFE_PWM_CTRL_OWI2_OUT_EN_Pos             ((uint32_t)7)   /*bit position, 从OWI2引脚输出PWM*/
#define AFE_PWM_CTRL_SRC_SEL_Msk             ((uint32_t)0x300)   /* bit mask, PWM数据源选择*/
#define AFE_PWM_CTRL_SRC_SEL_Pos             ((uint32_t)8)   /*bit position, PWM数据源选择*/


/******************  Bit Definition for Register REF_CTRL  *********************/
#define AFE_REF_CTRL_REF0_MODE_Msk             ((uint32_t)0x3)   /* bit mask, REF MODE:4.096/2.5/2.048/1.25*/
#define AFE_REF_CTRL_REF0_MODE_Pos             ((uint32_t)0)   /*bit position, REF MODE:4.096/2.5/2.048/1.25*/
#define AFE_REF_CTRL_REF0_EN_Msk             ((uint32_t)0x8)   /* bit mask, Ref0 enable*/
#define AFE_REF_CTRL_REF0_EN_Pos             ((uint32_t)3)   /*bit position, Ref0 enable*/
#define AFE_REF_CTRL_REF1_MODE_Msk             ((uint32_t)0x30)   /* bit mask, REF MODE:4.096/2.5/2.048/1.25*/
#define AFE_REF_CTRL_REF1_MODE_Pos             ((uint32_t)4)   /*bit position, REF MODE:4.096/2.5/2.048/1.25*/
#define AFE_REF_CTRL_REF1_EN_Msk             ((uint32_t)0x40)   /* bit mask, Ref1 enable*/
#define AFE_REF_CTRL_REF1_EN_Pos             ((uint32_t)6)   /*bit position, Ref1 enable*/
#define AFE_REF_CTRL_TEMP_SENSER_EN_Msk             ((uint32_t)0x80)   /* bit mask, */
#define AFE_REF_CTRL_TEMP_SENSER_EN_Pos             ((uint32_t)7)   /*bit position, */
#define AFE_REF_CTRL_REFBUF0_BOOST_EN_Msk             ((uint32_t)0x100)   /* bit mask, REFBUF0_BOOST_EN*/
#define AFE_REF_CTRL_REFBUF0_BOOST_EN_Pos             ((uint32_t)8)   /*bit position, REFBUF0_BOOST_EN*/
#define AFE_REF_CTRL_REFBUF1_BOOST_EN_Msk             ((uint32_t)0x200)   /* bit mask, REFBUF1_BOOST_EN*/
#define AFE_REF_CTRL_REFBUF1_BOOST_EN_Pos             ((uint32_t)9)   /*bit position, REFBUF1_BOOST_EN*/

/******************  Bit Definition for Register IEXC_RANGE  *********************/
#define AFE_IEXC_RANGE_IEXC0_RANGE_Msk             ((uint32_t)0xf)   /* bit mask, iexc0档位选择*/
#define AFE_IEXC_RANGE_IEXC0_RANGE_Pos             ((uint32_t)0)   /*bit position, iexc0档位选择*/
#define AFE_IEXC_RANGE_IEXC1_RANGE_Msk             ((uint32_t)0xf0)   /* bit mask, iexc1档位选择*/
#define AFE_IEXC_RANGE_IEXC1_RANGE_Pos             ((uint32_t)4)   /*bit position, iexc1档位选择*/

/******************  Bit Definition for Register IEXC_CTRL  *********************/
#define AFE_IEXC_CTRL_IEXC0_CHAN_Msk             ((uint32_t)0xf)   /* bit mask, iexc0通道选择*/
#define AFE_IEXC_CTRL_IEXC0_CHAN_Pos             ((uint32_t)0)   /*bit position, iexc0通道选择*/
#define AFE_IEXC_CTRL_IEXC1_CHAN_Msk             ((uint32_t)0xf0)   /* bit mask, iexc1通道选择*/
#define AFE_IEXC_CTRL_IEXC1_CHAN_Pos             ((uint32_t)4)   /*bit position, iexc1通道选择*/
#define AFE_IEXC_CTRL_IEXC_RES_Msk             ((uint32_t)0x100)   /* bit mask, iexc电阻选择：0=内部电阻，1=外部电阻*/
#define AFE_IEXC_CTRL_IEXC_RES_Pos             ((uint32_t)8)   /*bit position, iexc电阻选择：0=内部电阻，1=外部电阻*/
#define AFE_IEXC_CTRL_IEXC0_EN_Msk             ((uint32_t)0x200)   /* bit mask, iexc 0 使能信号*/
#define AFE_IEXC_CTRL_IEXC0_EN_Pos             ((uint32_t)9)   /*bit position, iexc 0 使能信号*/
#define AFE_IEXC_CTRL_IEXC1_EN_Msk             ((uint32_t)0x400)   /* bit mask, iexc 1 使能信号*/
#define AFE_IEXC_CTRL_IEXC1_EN_Pos             ((uint32_t)10)   /*bit position, iexc 1 使能信号*/

/******************  Bit Definition for Register USERKEY  *********************/
#define AFE_USERKEY_USERKEY_Msk             ((uint32_t)0xff)   /* bit mask, 秘钥：0xAC，解锁成功后，该地址读出数据位1，否则读出为0*/
#define AFE_USERKEY_USERKEY_Pos             ((uint32_t)0)   /*bit position, 秘钥：0xAC，解锁成功后，该地址读出数据位1，否则读出为0*/
/******************************************************************************/
/*                    DAC                         */
/******************************************************************************/


/******************  Bit Definition for Register CTRL  *********************/
#define DAC_CTRL_DAC_EN_Msk             ((uint32_t)0x1)   /* bit mask, DAC使能*/
#define DAC_CTRL_DAC_EN_Pos             ((uint32_t)0)   /*bit position, DAC使能*/
#define DAC_CTRL_DAC_RANGE_Msk             ((uint32_t)0x6)   /* bit mask, DAC输出range选择：0x0=5v range, 0x1=2.5v range, 0x2=1.2v range, 0x1=AVDD range*/
#define DAC_CTRL_DAC_RANGE_Pos             ((uint32_t)1)   /*bit position, DAC输出range选择：0x0=5v range, 0x1=2.5v range, 0x2=1.2v range, 0x1=AVDD range*/
#define DAC_CTRL_DAC_MODE_Msk             ((uint32_t)0x10)   /* bit mask, DAC输出电压电流模式*/
#define DAC_CTRL_DAC_MODE_Pos             ((uint32_t)4)   /*bit position, DAC输出电压电流模式*/
#define DAC_CTRL_OUT_MODE_Msk             ((uint32_t)0xe0)   /* bit mask, DAC使用模式*/
#define DAC_CTRL_OUT_MODE_Pos             ((uint32_t)5)   /*bit position, DAC使用模式*/
#define DAC_CTRL_HARD_TRIG_EN_Msk             ((uint32_t)0x100)   /* bit mask, 引脚触发DAC输出使能*/
#define DAC_CTRL_HARD_TRIG_EN_Pos             ((uint32_t)8)   /*bit position, 引脚触发DAC输出使能*/
#define DAC_CTRL_DAC_FILTER_EN_Msk             ((uint32_t)0x200)   /* bit mask, dac输出滤波使能（HART位置外接电容）*/
#define DAC_CTRL_DAC_FILTER_EN_Pos             ((uint32_t)9)   /*bit position, dac输出滤波使能（HART位置外接电容）*/
#define DAC_CTRL_DAC_PWMDIG_DR_Msk             ((uint32_t)0xc00)   /* bit mask, dac作为数字输出时，驱动强度控制*/
#define DAC_CTRL_DAC_PWMDIG_DR_Pos             ((uint32_t)10)   /*bit position, dac作为数字输出时，驱动强度控制*/
#define DAC_CTRL_LOOPN_DIV_EN_Msk             ((uint32_t)0x1000)   /* bit mask, loopn电阻分压使能*/
#define DAC_CTRL_LOOPN_DIV_EN_Pos             ((uint32_t)12)   /*bit position, loopn电阻分压使能*/
#define DAC_CTRL_CLOAD_MODE_Msk             ((uint32_t)0x6000)   /* bit mask, 负载电容模式控制*/
#define DAC_CTRL_CLOAD_MODE_Pos             ((uint32_t)13)   /*bit position, 负载电容模式控制*/
#define DAC_CTRL_CLOAD_100NF_EN_Msk             ((uint32_t)0x8000)   /* bit mask, 100nF负载电容使能控制*/
#define DAC_CTRL_CLOAD_100NF_EN_Pos             ((uint32_t)15)   /*bit position, 100nF负载电容使能控制*/

/******************  Bit Definition for Register DAC_DATA  *********************/
#define DAC_DATA_DAC_DATA_Msk             ((uint32_t)0xffff)   /* bit mask, DAC数据*/
#define DAC_DATA_DAC_DATA_Pos             ((uint32_t)0)   /*bit position, DAC数据*/
#define DAC_DATA_DAC_KEY_Msk             ((uint32_t)0xffff0000)   /* bit mask, 写DAC_DATA的同时，向DAC_KEY写0x6E94才能使DAC数据生效*/
#define DAC_DATA_DAC_KEY_Pos             ((uint32_t)16)   /*bit position, 写DAC_DATA的同时，向DAC_KEY写0x6E94才能使DAC数据生效*/

/******************  Bit Definition for Register CLAMPH  *********************/
#define DAC_CLAMPH_CLAMPH_Msk             ((uint32_t)0xffff)   /* bit mask, DAC上限钳位电压*/
#define DAC_CLAMPH_CLAMPH_Pos             ((uint32_t)0)   /*bit position, DAC上限钳位电压*/

/******************  Bit Definition for Register CLAMPL  *********************/
#define DAC_CLAMPL_CLAMPL_Msk             ((uint32_t)0xffff)   /* bit mask, DAC下限钳位电压*/
#define DAC_CLAMPL_CLAMPL_Pos             ((uint32_t)0)   /*bit position, DAC下限钳位电压*/

/******************  Bit Definition for Register AOUT_REG0  *********************/
#define DAC_AOUT_REG0_AOUT_REG0_Msk             ((uint32_t)0xffff)   /* bit mask, DAC做OWI输出时逻辑高对应的Code*/
#define DAC_AOUT_REG0_AOUT_REG0_Pos             ((uint32_t)0)   /*bit position, DAC做OWI输出时逻辑高对应的Code*/

/******************  Bit Definition for Register AOUT_REG1  *********************/
#define DAC_AOUT_REG1_AOUT_REG1_Msk             ((uint32_t)0xffff)   /* bit mask, DAC做OWI输出时逻辑高对应的Code*/
#define DAC_AOUT_REG1_AOUT_REG1_Pos             ((uint32_t)0)   /*bit position, DAC做OWI输出时逻辑高对应的Code*/

/******************************************************************************/
/*                    ADC_SUBSYS_USER                         */
/******************************************************************************/


/******************  Bit Definition for Register ERROR_STATUS  *********************/
#define ADC_SUBSYS_USER_ERROR_STATUS_MMR_CRC_ERR_Msk             ((uint32_t)0x1)   /* bit mask, 寄存器校验错误*/
#define ADC_SUBSYS_USER_ERROR_STATUS_MMR_CRC_ERR_Pos             ((uint32_t)0)   /*bit position, 寄存器校验错误*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_0_PGA_OV_ERR_Msk             ((uint32_t)0x2)   /* bit mask, ADC 0 PGA输入溢出标识*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_0_PGA_OV_ERR_Pos             ((uint32_t)1)   /*bit position, ADC 0 PGA输入溢出标识*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINM_0_UV_ERR_Msk             ((uint32_t)0x4)   /* bit mask, ADC 0 AIN负端输入underflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINM_0_UV_ERR_Pos             ((uint32_t)2)   /*bit position, ADC 0 AIN负端输入underflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINM_0_OV_ERR_Msk             ((uint32_t)0x8)   /* bit mask, ADC 0 AIN负端输入overflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINM_0_OV_ERR_Pos             ((uint32_t)3)   /*bit position, ADC 0 AIN负端输入overflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINP_0_UV_ERR_Msk             ((uint32_t)0x10)   /* bit mask, ADC 0 AIN正端输入underflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINP_0_UV_ERR_Pos             ((uint32_t)4)   /*bit position, ADC 0 AIN正端输入underflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINP_0_OV_ERR_Msk             ((uint32_t)0x20)   /* bit mask, ADC 0 AIN正端输入overflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINP_0_OV_ERR_Pos             ((uint32_t)5)   /*bit position, ADC 0 AIN正端输入overflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_0_COMP_OV_ERR_Msk             ((uint32_t)0x40)   /* bit mask, ADC 0 数字比较器超上阈值报警*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_0_COMP_OV_ERR_Pos             ((uint32_t)6)   /*bit position, ADC 0 数字比较器超上阈值报警*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_0_COMP_UV_ERR_Msk             ((uint32_t)0x80)   /* bit mask, ADC 0 数字比较器低于下阈值报警*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_0_COMP_UV_ERR_Pos             ((uint32_t)7)   /*bit position, ADC 0 数字比较器低于下阈值报警*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_1_PGA_OV_ERR_Msk             ((uint32_t)0x100)   /* bit mask, ADC 1 PGA输入溢出标识*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_1_PGA_OV_ERR_Pos             ((uint32_t)8)   /*bit position, ADC 1 PGA输入溢出标识*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINM_1_UV_ERR_Msk             ((uint32_t)0x200)   /* bit mask, ADC 1 AIN负端输入underflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINM_1_UV_ERR_Pos             ((uint32_t)9)   /*bit position, ADC 1 AIN负端输入underflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINM_1_OV_ERR_Msk             ((uint32_t)0x400)   /* bit mask, ADC 1 AIN负端输入overflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINM_1_OV_ERR_Pos             ((uint32_t)10)   /*bit position, ADC 1 AIN负端输入overflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINP_1_UV_ERR_Msk             ((uint32_t)0x800)   /* bit mask, ADC 1 AIN正端输入underflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINP_1_UV_ERR_Pos             ((uint32_t)11)   /*bit position, ADC 1 AIN正端输入underflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINP_1_OV_ERR_Msk             ((uint32_t)0x1000)   /* bit mask, ADC 1 AIN正端输入overflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_AINP_1_OV_ERR_Pos             ((uint32_t)12)   /*bit position, ADC 1 AIN正端输入overflow*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_1_COMP_OV_ERR_Msk             ((uint32_t)0x2000)   /* bit mask, ADC 1 数字比较器超上阈值报警*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_1_COMP_OV_ERR_Pos             ((uint32_t)13)   /*bit position, ADC 1 数字比较器超上阈值报警*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_1_COMP_UV_ERR_Msk             ((uint32_t)0x4000)   /* bit mask, ADC 1 数字比较器低于下阈值报警*/
#define ADC_SUBSYS_USER_ERROR_STATUS_ADC_1_COMP_UV_ERR_Pos             ((uint32_t)14)   /*bit position, ADC 1 数字比较器低于下阈值报警*/

/******************  Bit Definition for Register ERROR_EN  *********************/
#define ADC_SUBSYS_USER_ERROR_EN_MMR_CRC_ERR_EN_Msk             ((uint32_t)0x1)   /* bit mask, 寄存器校验错误-使能；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_MMR_CRC_ERR_EN_Pos             ((uint32_t)0)   /*bit position, 寄存器校验错误-使能；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_0_PGA_OV_ERR_EN_Msk             ((uint32_t)0x2)   /* bit mask, ADC 0 PGA输入溢出标识；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_0_PGA_OV_ERR_EN_Pos             ((uint32_t)1)   /*bit position, ADC 0 PGA输入溢出标识；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINM_0_UV_ERR_EN_Msk             ((uint32_t)0x4)   /* bit mask, ADC 0 AIN负端输入underflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINM_0_UV_ERR_EN_Pos             ((uint32_t)2)   /*bit position, ADC 0 AIN负端输入underflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINM_0_OV_ERR_EN_Msk             ((uint32_t)0x8)   /* bit mask, ADC 0 AIN负端输入overflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINM_0_OV_ERR_EN_Pos             ((uint32_t)3)   /*bit position, ADC 0 AIN负端输入overflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINP_0_UV_ERR_EN_Msk             ((uint32_t)0x10)   /* bit mask, ADC 0 AIN正端输入underflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINP_0_UV_ERR_EN_Pos             ((uint32_t)4)   /*bit position, ADC 0 AIN正端输入underflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINP_0_OV_ERR_EN_Msk             ((uint32_t)0x20)   /* bit mask, ADC 0 AIN正端输入overflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINP_0_OV_ERR_EN_Pos             ((uint32_t)5)   /*bit position, ADC 0 AIN正端输入overflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_0_COMP_OV_ERR_EN_Msk             ((uint32_t)0x40)   /* bit mask, ADC 0 数字比较器超上阈值报警；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_0_COMP_OV_ERR_EN_Pos             ((uint32_t)6)   /*bit position, ADC 0 数字比较器超上阈值报警；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_0_COMP_UV_ERR_EN_Msk             ((uint32_t)0x80)   /* bit mask, ADC 0 数字比较器低于下阈值报警；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_0_COMP_UV_ERR_EN_Pos             ((uint32_t)7)   /*bit position, ADC 0 数字比较器低于下阈值报警；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_1_PGA_OV_ERR_EN_Msk             ((uint32_t)0x100)   /* bit mask, ADC 1 PGA输入溢出标识；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_1_PGA_OV_ERR_EN_Pos             ((uint32_t)8)   /*bit position, ADC 1 PGA输入溢出标识；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINM_1_UV_ERR_EN_Msk             ((uint32_t)0x200)   /* bit mask, ADC 1 AIN负端输入underflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINM_1_UV_ERR_EN_Pos             ((uint32_t)9)   /*bit position, ADC 1 AIN负端输入underflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINM_1_OV_ERR_EN_Msk             ((uint32_t)0x400)   /* bit mask, ADC 1 AIN负端输入overflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINM_1_OV_ERR_EN_Pos             ((uint32_t)10)   /*bit position, ADC 1 AIN负端输入overflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINP_1_UV_ERR_EN_Msk             ((uint32_t)0x800)   /* bit mask, ADC 1 AIN正端输入underflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINP_1_UV_ERR_EN_Pos             ((uint32_t)11)   /*bit position, ADC 1 AIN正端输入underflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINP_1_OV_ERR_EN_Msk             ((uint32_t)0x1000)   /* bit mask, ADC 1 AIN正端输入overflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_AINP_1_OV_ERR_EN_Pos             ((uint32_t)12)   /*bit position, ADC 1 AIN正端输入overflow；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_1_COMP_OV_ERR_EN_Msk             ((uint32_t)0x2000)   /* bit mask, ADC 1 数字比较器超上阈值报警；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_1_COMP_OV_ERR_EN_Pos             ((uint32_t)13)   /*bit position, ADC 1 数字比较器超上阈值报警；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_1_COMP_UV_ERR_EN_Msk             ((uint32_t)0x4000)   /* bit mask, ADC 1 数字比较器低于下阈值报警；0-disable ; 1-Enable*/
#define ADC_SUBSYS_USER_ERROR_EN_ADC_1_COMP_UV_ERR_EN_Pos             ((uint32_t)14)   /*bit position, ADC 1 数字比较器低于下阈值报警；0-disable ; 1-Enable*/

/******************  Bit Definition for Register ADC_DRDY  *********************/
#define ADC_SUBSYS_USER_ADC_DRDY_DRDY_SEL_Msk             ((uint32_t)0xe)   /* bit mask, DRDY_STA 指示的源头*/
#define ADC_SUBSYS_USER_ADC_DRDY_DRDY_SEL_Pos             ((uint32_t)1)   /*bit position, DRDY_STA 指示的源头*/
/******************  Bit Definition for Register DMA_MODE  *********************/
#define ADC_SUBSYS_USER_DMA_MODE_ADC_CTRL_0_Msk             ((uint32_t)0x1)   /* bit mask, ADC 0 通道的DMA请求使能*/
#define ADC_SUBSYS_USER_DMA_MODE_ADC_CTRL_0_Pos             ((uint32_t)0)   /*bit position, ADC 0 通道的DMA请求使能*/
#define ADC_SUBSYS_USER_DMA_MODE_ADC_CTRL_1_Msk             ((uint32_t)0x2)   /* bit mask, ADC 1 通道的DMA请求使能*/
#define ADC_SUBSYS_USER_DMA_MODE_ADC_CTRL_1_Pos             ((uint32_t)1)   /*bit position, ADC 1 通道的DMA请求使能*/
#define ADC_SUBSYS_USER_DMA_MODE_SNOOZE_EXIT_SRC_Msk             ((uint32_t)0x4)   /* bit mask, 如果使能了ADC DMA的请求。在SNOOZE模式下，可以使用DMA的中断作为唤醒Core的源。此位是DMA唤醒core的源的选择。*/
#define ADC_SUBSYS_USER_DMA_MODE_SNOOZE_EXIT_SRC_Pos             ((uint32_t)2)   /*bit position, 如果使能了ADC DMA的请求。在SNOOZE模式下，可以使用DMA的中断作为唤醒Core的源。此位是DMA唤醒core的源的选择。*/

/******************  Bit Definition for Register IO_CONTROL_IOUT  *********************/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE0_Msk             ((uint32_t)0x7)   /* bit mask, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE0_Pos             ((uint32_t)0)   /*bit position, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE1_Msk             ((uint32_t)0x38)   /* bit mask, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE1_Pos             ((uint32_t)3)   /*bit position, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE2_Msk             ((uint32_t)0x1c0)   /* bit mask, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE2_Pos             ((uint32_t)6)   /*bit position, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE3_Msk             ((uint32_t)0xe00)   /* bit mask, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE3_Pos             ((uint32_t)9)   /*bit position, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE4_Msk             ((uint32_t)0x1000)   /* bit mask, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVE4_Pos             ((uint32_t)12)   /*bit position, RESERVED*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_ADC_0_ENABLE_Msk             ((uint32_t)0x2000)   /* bit mask, 对ADC0提供开路电流检测*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_ADC_0_ENABLE_Pos             ((uint32_t)13)   /*bit position, 对ADC0提供开路电流检测*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_ADC_1_ENABLE_Msk             ((uint32_t)0x4000)   /* bit mask, 对ADC1提供开路电流检测*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_ADC_1_ENABLE_Pos             ((uint32_t)14)   /*bit position, 对ADC1提供开路电流检测*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_STRENTH_Msk             ((uint32_t)0x18000)   /* bit mask, 恒流源发生强度*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_BURNOUT_STRENTH_Pos             ((uint32_t)15)   /*bit position, 恒流源发生强度*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVED5_Msk             ((uint32_t)0x20000)   /* bit mask, Reserved*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_RESERVED5_Pos             ((uint32_t)17)   /*bit position, Reserved*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_REF_BUF_PREQ_ENABLE_Msk             ((uint32_t)0x40000)   /* bit mask, 基准源使能选项*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_REF_BUF_PREQ_ENABLE_Pos             ((uint32_t)18)   /*bit position, 基准源使能选项*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_PGA_CALEN_Msk             ((uint32_t)0x200000)   /* bit mask, 内部增益校准使能位*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_PGA_CALEN_Pos             ((uint32_t)21)   /*bit position, 内部增益校准使能位*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_PGA_CAL_RS_Msk             ((uint32_t)0x400000)   /* bit mask, 不同增益下的配置选项*/
#define ADC_SUBSYS_USER_IO_CONTROL_IOUT_PGA_CAL_RS_Pos             ((uint32_t)22)   /*bit position, 不同增益下的配置选项*/

/******************  Bit Definition for Register IO_CONTROL_VBIAS  *********************/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_0_Msk             ((uint32_t)0x1)   /* bit mask, 使能AIN0通道上的偏置电压。置1时，内部偏置电压通过AIN0提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_0_Pos             ((uint32_t)0)   /*bit position, 使能AIN0通道上的偏置电压。置1时，内部偏置电压通过AIN0提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_1_Msk             ((uint32_t)0x2)   /* bit mask, 使能AIN1通道上的偏置电压。置1时，内部偏置电压通过AIN1提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_1_Pos             ((uint32_t)1)   /*bit position, 使能AIN1通道上的偏置电压。置1时，内部偏置电压通过AIN1提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_2_Msk             ((uint32_t)0x4)   /* bit mask, 使能AIN2通道上的偏置电压。置1时，内部偏置电压通过AIN2提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_2_Pos             ((uint32_t)2)   /*bit position, 使能AIN2通道上的偏置电压。置1时，内部偏置电压通过AIN2提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_3_Msk             ((uint32_t)0x8)   /* bit mask, 使能AIN3通道上的偏置电压。置1时，内部偏置电压通过AIN3提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_3_Pos             ((uint32_t)3)   /*bit position, 使能AIN3通道上的偏置电压。置1时，内部偏置电压通过AIN3提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_4_Msk             ((uint32_t)0x10)   /* bit mask, 使能AIN4通道上的偏置电压。置1时，内部偏置电压通过AIN4提供*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_4_Pos             ((uint32_t)4)   /*bit position, 使能AIN4通道上的偏置电压。置1时，内部偏置电压通过AIN4提供*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_5_Msk             ((uint32_t)0x20)   /* bit mask, 使能AIN5通道上的偏置电压。置1时，内部偏置电压通过AIN5提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_5_Pos             ((uint32_t)5)   /*bit position, 使能AIN5通道上的偏置电压。置1时，内部偏置电压通过AIN5提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_6_Msk             ((uint32_t)0x40)   /* bit mask, 使能AIN6通道上的偏置电压。置1时，内部偏置电压通过AIN6提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_6_Pos             ((uint32_t)6)   /*bit position, 使能AIN6通道上的偏置电压。置1时，内部偏置电压通过AIN6提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_7_Msk             ((uint32_t)0x80)   /* bit mask, 使能AIN7通道上的偏置电压。置1时，内部偏置电压通过AIN7提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_7_Pos             ((uint32_t)7)   /*bit position, 使能AIN7通道上的偏置电压。置1时，内部偏置电压通过AIN7提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_8_Msk             ((uint32_t)0x100)   /* bit mask, 使能AIN8通道上的偏置电压。置1时，内部偏置电压通过AIN8提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_8_Pos             ((uint32_t)8)   /*bit position, 使能AIN8通道上的偏置电压。置1时，内部偏置电压通过AIN8提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_9_Msk             ((uint32_t)0x200)   /* bit mask, 使能AIN9通道上的偏置电压。置1时，内部偏置电压通过AIN9提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_9_Pos             ((uint32_t)9)   /*bit position, 使能AIN9通道上的偏置电压。置1时，内部偏置电压通过AIN9提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_10_Msk             ((uint32_t)0x400)   /* bit mask, 使能AIN10通道上的偏置电压。置1时，内部偏置电压通过AIN10提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_10_Pos             ((uint32_t)10)   /*bit position, 使能AIN10通道上的偏置电压。置1时，内部偏置电压通过AIN10提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_11_Msk             ((uint32_t)0x800)   /* bit mask, 使能AIN11通道上的偏置电压。置1时，内部偏置电压通过AIN11提供。*/
#define ADC_SUBSYS_USER_IO_CONTROL_VBIAS_PIN_11_Pos             ((uint32_t)11)   /*bit position, 使能AIN11通道上的偏置电压。置1时，内部偏置电压通过AIN11提供。*/

/******************  Bit Definition for Register ADC_STATUS_0  *********************/
#define ADC_SUBSYS_USER_ADC_STATUS_0_AINP_ACTIVE_Msk             ((uint32_t)0x1f)   /* bit mask, 与ADC 0 转换数据对应的通道P编号*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_AINP_ACTIVE_Pos             ((uint32_t)0)   /*bit position, 与ADC 0 转换数据对应的通道P编号*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_AINN_ACTIVE_Msk             ((uint32_t)0x3e0)   /* bit mask, 与ADC 0 转换数据对应的通道N编号*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_AINN_ACTIVE_Pos             ((uint32_t)5)   /*bit position, 与ADC 0 转换数据对应的通道N编号*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_POR_FLAG_Msk             ((uint32_t)0x400)   /* bit mask, 上电复位指示；读清；*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_POR_FLAG_Pos             ((uint32_t)10)   /*bit position, 上电复位指示；读清；*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_ERROR_FLAG_Msk             ((uint32_t)0x800)   /* bit mask, ADC_0的错误指示。读ERROR_STATUS清零*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_ERROR_FLAG_Pos             ((uint32_t)11)   /*bit position, ADC_0的错误指示。读ERROR_STATUS清零*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_RDYN_Msk             ((uint32_t)0x1000)   /* bit mask, ADC0的数据ready指示。读ADC_DATA清零*/
#define ADC_SUBSYS_USER_ADC_STATUS_0_RDYN_Pos             ((uint32_t)12)   /*bit position, ADC0的数据ready指示。读ADC_DATA清零*/

/******************  Bit Definition for Register ADC_DATA_0  *********************/
#define ADC_SUBSYS_USER_ADC_DATA_0_REG_Msk             ((uint32_t)0xffffff)   /* bit mask, ADC 0 的转换数据*/
#define ADC_SUBSYS_USER_ADC_DATA_0_REG_Pos             ((uint32_t)0)   /*bit position, ADC 0 的转换数据*/

/******************  Bit Definition for Register INTERRUPT_CONTROL_0  *********************/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_0_RDY_INT_Msk             ((uint32_t)0x1)   /* bit mask, ADC 0 数据ready中断的使能*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_0_RDY_INT_Pos             ((uint32_t)0)   /*bit position, ADC 0 数据ready中断的使能*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_0_ERR_INT_Msk             ((uint32_t)0x2)   /* bit mask, ADC 0 错误中断的使能*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_0_ERR_INT_Pos             ((uint32_t)1)   /*bit position, ADC 0 错误中断的使能*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_0_RDY_CNT_Msk             ((uint32_t)0x3fffc)   /* bit mask, 计数当产生多少个数后，才产生数据中断*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_0_RDY_CNT_Pos             ((uint32_t)2)   /*bit position, 计数当产生多少个数后，才产生数据中断*/

/******************  Bit Definition for Register ADC_CONTROL_0  *********************/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Msk             ((uint32_t)0x3c)   /* bit mask, ADC转换模式控制；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_MODE_Pos             ((uint32_t)2)   /*bit position, ADC转换模式控制；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_RESERVED0_Msk             ((uint32_t)0xc0)   /* bit mask, RESERVED0-Do not care*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_RESERVED0_Pos             ((uint32_t)6)   /*bit position, RESERVED0-Do not care*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_RESERVED1_Msk             ((uint32_t)0x300)   /* bit mask, RESERVED1-Do not care*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_RESERVED1_Pos             ((uint32_t)8)   /*bit position, RESERVED1-Do not care*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Msk             ((uint32_t)0x400)   /* bit mask, 同步转换使能；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_SIMU_Pos             ((uint32_t)10)   /*bit position, 同步转换使能；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_TRIG_SRC_SEL_Msk             ((uint32_t)0x1800)   /* bit mask, 选择ADC启动的触发源；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_TRIG_SRC_SEL_Pos             ((uint32_t)11)   /*bit position, 选择ADC启动的触发源；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_START_Msk             ((uint32_t)0x2000)   /* bit mask, 软件启动控制位；进行同步转换前，用户需要保证ADC 配置相同。*/
#define ADC_SUBSYS_USER_ADC_CONTROL_0_START_Pos             ((uint32_t)13)   /*bit position, 软件启动控制位；进行同步转换前，用户需要保证ADC 配置相同。*/

/******************  Bit Definition for Register CHANNEL_CFG_0  *********************/
#define ADC_SUBSYS_USER_CHANNEL_CFG_0_AINM_Msk             ((uint32_t)0x1f)   /* bit mask, AINM端输入选择；*/
#define ADC_SUBSYS_USER_CHANNEL_CFG_0_AINM_Pos             ((uint32_t)0)   /*bit position, AINM端输入选择；*/
#define ADC_SUBSYS_USER_CHANNEL_CFG_0_AINP_Msk             ((uint32_t)0x3e0)   /* bit mask, AINP端输入选择；*/
#define ADC_SUBSYS_USER_CHANNEL_CFG_0_AINP_Pos             ((uint32_t)5)   /*bit position, AINP端输入选择；*/

/******************  Bit Definition for Register CONFIGURATION_0  *********************/
#define ADC_SUBSYS_USER_CONFIGURATION_0_PGA_Msk             ((uint32_t)0x7)   /* bit mask, PGA增益控制；*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_PGA_Pos             ((uint32_t)0)   /*bit position, PGA增益控制；*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_PGA_BYPASS_Msk             ((uint32_t)0x8)   /* bit mask, PGA BYPASS选项*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_PGA_BYPASS_Pos             ((uint32_t)3)   /*bit position, PGA BYPASS选项*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_REF_SEL_Msk             ((uint32_t)0x30)   /* bit mask, 用户也可以 利用这些寄存器选择基准电压源。有四个选项可用：内部 2.5 V基准电压源、连接在REFIN1(+)和REFIN1(−)之间的外部基准电压源、连接在REFIN2(+)和REFIN2(−) 之间的外部基准电压源或AVDD至AVSS。*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_REF_SEL_Pos             ((uint32_t)4)   /*bit position, 用户也可以 利用这些寄存器选择基准电压源。有四个选项可用：内部 2.5 V基准电压源、连接在REFIN1(+)和REFIN1(−)之间的外部基准电压源、连接在REFIN2(+)和REFIN2(−) 之间的外部基准电压源或AVDD至AVSS。*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_RESERVE0_Msk             ((uint32_t)0x40)   /* bit mask, */
#define ADC_SUBSYS_USER_CONFIGURATION_0_RESERVE0_Pos             ((uint32_t)6)   /*bit position, */
#define ADC_SUBSYS_USER_CONFIGURATION_0_RESERVE1_Msk             ((uint32_t)0x80)   /* bit mask, */
#define ADC_SUBSYS_USER_CONFIGURATION_0_RESERVE1_Pos             ((uint32_t)7)   /*bit position, */
#define ADC_SUBSYS_USER_CONFIGURATION_0_REF_BUFM_Msk             ((uint32_t)0x100)   /* bit mask, 基准源M输入缓冲器*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_REF_BUFM_Pos             ((uint32_t)8)   /*bit position, 基准源M输入缓冲器*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_REF_BUFP_Msk             ((uint32_t)0x200)   /* bit mask, 基准源P输入缓冲器*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_REF_BUFP_Pos             ((uint32_t)9)   /*bit position, 基准源P输入缓冲器*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_BIPOLAR_Msk             ((uint32_t)0x400)   /* bit mask, 单极性/双极性控制；*/
#define ADC_SUBSYS_USER_CONFIGURATION_0_BIPOLAR_Pos             ((uint32_t)10)   /*bit position, 单极性/双极性控制；*/

/******************  Bit Definition for Register FILTER_0  *********************/
#define ADC_SUBSYS_USER_FILTER_0_FS_Msk             ((uint32_t)0x1f)   /* bit mask, 输出速率选择；*/
#define ADC_SUBSYS_USER_FILTER_0_FS_Pos             ((uint32_t)0)   /*bit position, 输出速率选择；*/

/******************  Bit Definition for Register OFFSET_0  *********************/
#define ADC_SUBSYS_USER_OFFSET_0_REG_Msk             ((uint32_t)0xffffff)   /* bit mask, 偏移校准寄存器，有符号补码表示*/
#define ADC_SUBSYS_USER_OFFSET_0_REG_Pos             ((uint32_t)0)   /*bit position, 偏移校准寄存器，有符号补码表示*/

/******************  Bit Definition for Register GAIN_0  *********************/
#define ADC_SUBSYS_USER_GAIN_0_REG_Msk             ((uint32_t)0xffffff)   /* bit mask, 增益校准寄存器，会被出厂校准，默认值0x4xxxxx*/
#define ADC_SUBSYS_USER_GAIN_0_REG_Pos             ((uint32_t)0)   /*bit position, 增益校准寄存器，会被出厂校准，默认值0x4xxxxx*/

/******************  Bit Definition for Register ADC_0_HI_COMPARATOR  *********************/
#define ADC_SUBSYS_USER_ADC_0_HI_COMPARATOR_VALUE_Msk             ((uint32_t)0xffffff)   /* bit mask, ADC 0 上门限阈值设置，二进制补码表示，若超阈值，ADC_0_COMP_OV_ERR置位*/
#define ADC_SUBSYS_USER_ADC_0_HI_COMPARATOR_VALUE_Pos             ((uint32_t)0)   /*bit position, ADC 0 上门限阈值设置，二进制补码表示，若超阈值，ADC_0_COMP_OV_ERR置位*/

/******************  Bit Definition for Register ADC_0_LO_COMPARATOR  *********************/
#define ADC_SUBSYS_USER_ADC_0_LO_COMPARATOR_VALUE_Msk             ((uint32_t)0xffffff)   /* bit mask, ADC 0 下门限阈值设置，二进制补码表示，若超阈值，ADC_0_COMP_UV_ERR置位*/
#define ADC_SUBSYS_USER_ADC_0_LO_COMPARATOR_VALUE_Pos             ((uint32_t)0)   /*bit position, ADC 0 下门限阈值设置，二进制补码表示，若超阈值，ADC_0_COMP_UV_ERR置位*/

/******************  Bit Definition for Register ADC_STATUS_1  *********************/
#define ADC_SUBSYS_USER_ADC_STATUS_1_AINP_ACTIVE_Msk             ((uint32_t)0x1f)   /* bit mask, 与ADC 1 转换数据对应的通道P编号*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_AINP_ACTIVE_Pos             ((uint32_t)0)   /*bit position, 与ADC 1 转换数据对应的通道P编号*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_AINN_ACTIVE_Msk             ((uint32_t)0x3e0)   /* bit mask, 与ADC 1 转换数据对应的通道N编号*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_AINN_ACTIVE_Pos             ((uint32_t)5)   /*bit position, 与ADC 1 转换数据对应的通道N编号*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_POR_FLAG_Msk             ((uint32_t)0x400)   /* bit mask, 上电复位指示；读清；*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_POR_FLAG_Pos             ((uint32_t)10)   /*bit position, 上电复位指示；读清；*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_ERROR_FLAG_Msk             ((uint32_t)0x800)   /* bit mask, ADC_0的错误指示。读ERROR_STATUS清零*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_ERROR_FLAG_Pos             ((uint32_t)11)   /*bit position, ADC_0的错误指示。读ERROR_STATUS清零*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_RDYN_Msk             ((uint32_t)0x1000)   /* bit mask, ADC0的数据ready指示。读ADC_DATA清零*/
#define ADC_SUBSYS_USER_ADC_STATUS_1_RDYN_Pos             ((uint32_t)12)   /*bit position, ADC0的数据ready指示。读ADC_DATA清零*/

/******************  Bit Definition for Register ADC_DATA_1  *********************/
#define ADC_SUBSYS_USER_ADC_DATA_1_REG_Msk             ((uint32_t)0xffffff)   /* bit mask, */
#define ADC_SUBSYS_USER_ADC_DATA_1_REG_Pos             ((uint32_t)0)   /*bit position, */

/******************  Bit Definition for Register INTERRUPT_CONTROL_1  *********************/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_1_RDY_INT_Msk             ((uint32_t)0x1)   /* bit mask, ADC 1 数据ready中断的使能*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_1_RDY_INT_Pos             ((uint32_t)0)   /*bit position, ADC 1 数据ready中断的使能*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_1_ERR_INT_Msk             ((uint32_t)0x2)   /* bit mask, ADC 1 错误中断的使能*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_1_ERR_INT_Pos             ((uint32_t)1)   /*bit position, ADC 1 错误中断的使能*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_1_RDY_CNT_Msk             ((uint32_t)0x3fffc)   /* bit mask, 计数当产生多少个数后，才产生数据中断*/
#define ADC_SUBSYS_USER_INTERRUPT_CONTROL_1_RDY_CNT_Pos             ((uint32_t)2)   /*bit position, 计数当产生多少个数后，才产生数据中断*/

/******************  Bit Definition for Register ADC_CONTROL_1  *********************/
#define ADC_SUBSYS_USER_ADC_CONTROL_1_MODE_Msk             ((uint32_t)0x3c)   /* bit mask, ADC转换模式控制；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_1_MODE_Pos             ((uint32_t)2)   /*bit position, ADC转换模式控制；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_1_RESERVED0_Msk             ((uint32_t)0xc0)   /* bit mask, Reserved- Do not care*/
#define ADC_SUBSYS_USER_ADC_CONTROL_1_RESERVED0_Pos             ((uint32_t)6)   /*bit position, Reserved- Do not care*/
#define ADC_SUBSYS_USER_ADC_CONTROL_1_RESERVED1_Msk             ((uint32_t)0x300)   /* bit mask, */
#define ADC_SUBSYS_USER_ADC_CONTROL_1_RESERVED1_Pos             ((uint32_t)8)   /*bit position, */
#define ADC_SUBSYS_USER_ADC_CONTROL_1_RESERVED2_Msk             ((uint32_t)0x400)   /* bit mask, */
#define ADC_SUBSYS_USER_ADC_CONTROL_1_RESERVED2_Pos             ((uint32_t)10)   /*bit position, */
#define ADC_SUBSYS_USER_ADC_CONTROL_1_TRIG_SRC_SEL_Msk             ((uint32_t)0x1800)   /* bit mask, 选择ADC启动的触发源；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_1_TRIG_SRC_SEL_Pos             ((uint32_t)11)   /*bit position, 选择ADC启动的触发源；*/
#define ADC_SUBSYS_USER_ADC_CONTROL_1_START_Msk             ((uint32_t)0x2000)   /* bit mask, 软件启动控制位；进行同步转换前，用户需要保证ADC 配置相同。*/
#define ADC_SUBSYS_USER_ADC_CONTROL_1_START_Pos             ((uint32_t)13)   /*bit position, 软件启动控制位；进行同步转换前，用户需要保证ADC 配置相同。*/

/******************  Bit Definition for Register CHANNEL_CFG_1  *********************/
#define ADC_SUBSYS_USER_CHANNEL_CFG_1_AINM_Msk             ((uint32_t)0x1f)   /* bit mask, AINM端输入选择；*/
#define ADC_SUBSYS_USER_CHANNEL_CFG_1_AINM_Pos             ((uint32_t)0)   /*bit position, AINM端输入选择；*/
#define ADC_SUBSYS_USER_CHANNEL_CFG_1_AINP_Msk             ((uint32_t)0x3e0)   /* bit mask, AINP端输入选择；*/
#define ADC_SUBSYS_USER_CHANNEL_CFG_1_AINP_Pos             ((uint32_t)5)   /*bit position, AINP端输入选择；*/

/******************  Bit Definition for Register CONFIGURATION_1  *********************/
#define ADC_SUBSYS_USER_CONFIGURATION_1_PGA_Msk             ((uint32_t)0x7)   /* bit mask, PGA增益控制；*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_PGA_Pos             ((uint32_t)0)   /*bit position, PGA增益控制；*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_PGA_BYPASS_Msk             ((uint32_t)0x8)   /* bit mask, PGA BYPASS选项*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_PGA_BYPASS_Pos             ((uint32_t)3)   /*bit position, PGA BYPASS选项*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_REF_SEL_Msk             ((uint32_t)0x30)   /* bit mask, 用户也可以 利用这些寄存器选择基准电压源。有四个选项可用：内部 2.5 V基准电压源、连接在REFIN1(+)和REFIN1(−)之间的外部基准电压源、连接在REFIN2(+)和REFIN2(−) 之间的外部基准电压源或AVDD至AVSS。*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_REF_SEL_Pos             ((uint32_t)4)   /*bit position, 用户也可以 利用这些寄存器选择基准电压源。有四个选项可用：内部 2.5 V基准电压源、连接在REFIN1(+)和REFIN1(−)之间的外部基准电压源、连接在REFIN2(+)和REFIN2(−) 之间的外部基准电压源或AVDD至AVSS。*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_RESERVE0_Msk             ((uint32_t)0x40)   /* bit mask, */
#define ADC_SUBSYS_USER_CONFIGURATION_1_RESERVE0_Pos             ((uint32_t)6)   /*bit position, */
#define ADC_SUBSYS_USER_CONFIGURATION_1_RESERVE1_Msk             ((uint32_t)0x80)   /* bit mask, */
#define ADC_SUBSYS_USER_CONFIGURATION_1_RESERVE1_Pos             ((uint32_t)7)   /*bit position, */
#define ADC_SUBSYS_USER_CONFIGURATION_1_REF_BUFM_Msk             ((uint32_t)0x100)   /* bit mask, 基准源M输入缓冲器*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_REF_BUFM_Pos             ((uint32_t)8)   /*bit position, 基准源M输入缓冲器*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_REF_BUFP_Msk             ((uint32_t)0x200)   /* bit mask, 基准源P输入缓冲器*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_REF_BUFP_Pos             ((uint32_t)9)   /*bit position, 基准源P输入缓冲器*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_BIPOLAR_Msk             ((uint32_t)0x400)   /* bit mask, 单极性/双极性控制；*/
#define ADC_SUBSYS_USER_CONFIGURATION_1_BIPOLAR_Pos             ((uint32_t)10)   /*bit position, 单极性/双极性控制；*/

/******************  Bit Definition for Register FILTER_1  *********************/
#define ADC_SUBSYS_USER_FILTER_1_FS_Msk             ((uint32_t)0x1f)   /* bit mask, 输出速率选择；*/
#define ADC_SUBSYS_USER_FILTER_1_FS_Pos             ((uint32_t)0)   /*bit position, 输出速率选择；*/

/******************  Bit Definition for Register OFFSET_1  *********************/
#define ADC_SUBSYS_USER_OFFSET_1_REG_Msk             ((uint32_t)0xffffff)   /* bit mask, 偏移校准寄存器，有符号补码表示*/
#define ADC_SUBSYS_USER_OFFSET_1_REG_Pos             ((uint32_t)0)   /*bit position, 偏移校准寄存器，有符号补码表示*/

/******************  Bit Definition for Register GAIN_1  *********************/
#define ADC_SUBSYS_USER_GAIN_1_REG_Msk             ((uint32_t)0xffffff)   /* bit mask, 增益校准寄存器，会被出厂校准，默认值0x4xxxxx*/
#define ADC_SUBSYS_USER_GAIN_1_REG_Pos             ((uint32_t)0)   /*bit position, 增益校准寄存器，会被出厂校准，默认值0x4xxxxx*/

/******************  Bit Definition for Register ADC_1_HI_COMPARATOR  *********************/
#define ADC_SUBSYS_USER_ADC_1_HI_COMPARATOR_VALUE_Msk             ((uint32_t)0xffffff)   /* bit mask, ADC 1 上门限阈值设置，二进制补码表示，若超阈值，ADC_0_COMP_OV_ERR置位*/
#define ADC_SUBSYS_USER_ADC_1_HI_COMPARATOR_VALUE_Pos             ((uint32_t)0)   /*bit position, ADC 1 上门限阈值设置，二进制补码表示，若超阈值，ADC_0_COMP_OV_ERR置位*/

/******************  Bit Definition for Register ADC_1_LO_COMPARATOR  *********************/
#define ADC_SUBSYS_USER_ADC_1_LO_COMPARATOR_VALUE_Msk             ((uint32_t)0xffffff)   /* bit mask, ADC 1 下门限阈值设置，二进制补码表示，若超阈值，ADC_0_COMP_UV_ERR置位*/
#define ADC_SUBSYS_USER_ADC_1_LO_COMPARATOR_VALUE_Pos             ((uint32_t)0)   /*bit position, ADC 1 下门限阈值设置，二进制补码表示，若超阈值，ADC_0_COMP_UV_ERR置位*/

/******************************************************************************/
/*                    MIO                         */
/******************************************************************************/

/******************  Bit Definition for Register MIO_CTRL  *********************/
#define MIO_CTRL_MIOEN_Msk             ((uint32_t)0x1)   /* bit mask, MIO 全局使能*/
#define MIO_CTRL_MIOEN_Pos             ((uint32_t)0)   /*bit position, MIO 全局使能*/
#define MIO_CTRL_SWRST_Msk             ((uint32_t)0x2)   /* bit mask, MIO软件复位*/
#define MIO_CTRL_SWRST_Pos             ((uint32_t)1)   /*bit position, MIO软件复位*/
#define MIO_CTRL_FASTACC_Msk             ((uint32_t)0x4)   /* bit mask, Reserved*/
#define MIO_CTRL_FASTACC_Pos             ((uint32_t)2)   /*bit position, Reserved*/
#define MIO_CTRL_DBGE_Msk             ((uint32_t)0x8)   /* bit mask, Reserved*/
#define MIO_CTRL_DBGE_Pos             ((uint32_t)3)   /*bit position, Reserved*/
#define MIO_CTRL_DOZEN_Msk             ((uint32_t)0x10)   /* bit mask, Reserved*/
#define MIO_CTRL_DOZEN_Pos             ((uint32_t)4)   /*bit position, Reserved*/

/******************  Bit Definition for Register MIO_PIN  *********************/
#define MIO_PIN_PDI_Msk             ((uint32_t)0xffffffff)   /* bit mask, MIO 引脚输入，返回每个 MIO 引脚上的输入数据
0：对应的引脚输入低电平
1：对应的引脚输入高电平
*/
#define MIO_PIN_PDI_Pos             ((uint32_t)0)   /*bit position, MIO 引脚输入，返回每个 MIO 引脚上的输入数据
0：对应的引脚输入低电平
1：对应的引脚输入高电平
*/

/******************  Bit Definition for Register MIO_SHIFTSTAT  *********************/
#define MIO_SHIFTSTAT_SSF_Msk             ((uint32_t)0xff)   /* bit mask, 移位寄存器状态标志
0：标志位清零
1：标志位置位
当发生以下事件之一时，会更新移位寄存器状态标志位：
当为接收模式时(SMOD = 001b)，当缓冲器(SHIFTBUF) 已经加载了移位寄存器的数据时(缓冲器(SHIFTBUF)非空)，该位置 1。读取缓冲器(SHIFTBUF)寄存器时硬件自
动清除该状态标志位。
当为发送模式时(SMOD = 010b)， 当缓冲器(SHIFTBUF) 的数据已传输到了移位寄存器时(缓冲器(SHIFTBUF)为空)，该位置 1。写入缓冲器(SHIFTBUF)寄存器时硬件自动清除该状态标志位。
当为匹配接收模式时(SMOD = 100b)，当缓冲器(SHIFTBUF)和移位寄存器之间发生数据匹配，并将移位寄存器的数据加载到缓冲器(SHIFTBUF)时(缓冲器(SHIFTBUF)
非空)，该位置 1。读取缓冲器(SHIFTBUF)寄存器时硬件自动清除该状态标志位。
SSF bit3~bit0 分别对应 MIO 的四个移位寄存器 shifter3~shifter0
写“1”清除该标志位
*/
#define MIO_SHIFTSTAT_SSF_Pos             ((uint32_t)0)   /*bit position, 移位寄存器状态标志
0：标志位清零
1：标志位置位
当发生以下事件之一时，会更新移位寄存器状态标志位：
当为接收模式时(SMOD = 001b)，当缓冲器(SHIFTBUF) 已经加载了移位寄存器的数据时(缓冲器(SHIFTBUF)非空)，该位置 1。读取缓冲器(SHIFTBUF)寄存器时硬件自
动清除该状态标志位。
当为发送模式时(SMOD = 010b)， 当缓冲器(SHIFTBUF) 的数据已传输到了移位寄存器时(缓冲器(SHIFTBUF)为空)，该位置 1。写入缓冲器(SHIFTBUF)寄存器时硬件自动清除该状态标志位。
当为匹配接收模式时(SMOD = 100b)，当缓冲器(SHIFTBUF)和移位寄存器之间发生数据匹配，并将移位寄存器的数据加载到缓冲器(SHIFTBUF)时(缓冲器(SHIFTBUF)
非空)，该位置 1。读取缓冲器(SHIFTBUF)寄存器时硬件自动清除该状态标志位。
SSF bit3~bit0 分别对应 MIO 的四个移位寄存器 shifter3~shifter0
写“1”清除该标志位
*/

/******************  Bit Definition for Register MIO_SHIFTERR  *********************/
#define MIO_SHIFTERR_SEF_Msk             ((uint32_t)0xff)   /* bit mask, 移位寄存器错误状态标志
0：错误状态标志位清零
1：错误状态标志位置位
当发生以下事件之一时，会更新移位寄存器错误状态标志位：
当为接收模式时(SMOD = 001b)，如果在移位寄存器的新数据覆盖先前内容之前，未读取缓冲器(SHIFTBUF)(缓冲器(SHIFTBUF)上溢)，则该位置 1。或者当接收到的开始或停止位与预期值不匹配时，该位也会置 1。
当为发送模式时(SMOD = 010b)， 如果当移位器已准备好从缓冲器(SHIFTBUF)加载新数据到移位寄存器时，但未往缓冲器(SHIFTBUF)里面写入新数据(缓冲器(SHIFTBUF)下溢)，则该位置 1。
当为匹配接收模式时(SMOD = 100b)，如果上次匹配的数据未读取，又发生新的数据匹配(缓冲器(SHIFTBUF)上溢)，则该位置 1。读取缓冲器(SHIFTBUF)寄存器时硬件自动清除该状态标志位。
SEF bit3~bit0 分别对应 MIO 的四个移位器 shifter3~shifter0
写“1”清除该标志位
*/
#define MIO_SHIFTERR_SEF_Pos             ((uint32_t)0)   /*bit position, 移位寄存器错误状态标志
0：错误状态标志位清零
1：错误状态标志位置位
当发生以下事件之一时，会更新移位寄存器错误状态标志位：
当为接收模式时(SMOD = 001b)，如果在移位寄存器的新数据覆盖先前内容之前，未读取缓冲器(SHIFTBUF)(缓冲器(SHIFTBUF)上溢)，则该位置 1。或者当接收到的开始或停止位与预期值不匹配时，该位也会置 1。
当为发送模式时(SMOD = 010b)， 如果当移位器已准备好从缓冲器(SHIFTBUF)加载新数据到移位寄存器时，但未往缓冲器(SHIFTBUF)里面写入新数据(缓冲器(SHIFTBUF)下溢)，则该位置 1。
当为匹配接收模式时(SMOD = 100b)，如果上次匹配的数据未读取，又发生新的数据匹配(缓冲器(SHIFTBUF)上溢)，则该位置 1。读取缓冲器(SHIFTBUF)寄存器时硬件自动清除该状态标志位。
SEF bit3~bit0 分别对应 MIO 的四个移位器 shifter3~shifter0
写“1”清除该标志位
*/

/******************  Bit Definition for Register MIO_TIMSTAT  *********************/
#define MIO_TIMSTAT_TSF_Msk             ((uint32_t)0xff)   /* bit mask, 定时器状态标志
0：状态标志位清零
1：状态标志位置位
定时器的状态标志位是根据定时器的模式来置位：
当为 8 位波特率计数器模式时(TMOD = 01b)，当高 8 位计数器为零并递减时，则该位置 1。
当为 8 位高电平 PWM 模式时(TMOD = 10b)，当高 8 位计数器为零并递减时，则该位置 1。
当为 16 位计数器模式时(TMOD = 11b)，当 16 位计数器为零并递减时，则该位置 1。TSF bit3~bit0 分别对应 MIO 的四个定时器 timer3~timer0
写“1”清除该标志位
*/
#define MIO_TIMSTAT_TSF_Pos             ((uint32_t)0)   /*bit position, 定时器状态标志
0：状态标志位清零
1：状态标志位置位
定时器的状态标志位是根据定时器的模式来置位：
当为 8 位波特率计数器模式时(TMOD = 01b)，当高 8 位计数器为零并递减时，则该位置 1。
当为 8 位高电平 PWM 模式时(TMOD = 10b)，当高 8 位计数器为零并递减时，则该位置 1。
当为 16 位计数器模式时(TMOD = 11b)，当 16 位计数器为零并递减时，则该位置 1。TSF bit3~bit0 分别对应 MIO 的四个定时器 timer3~timer0
写“1”清除该标志位
*/

/******************  Bit Definition for Register MIO_SHIFTSIEN  *********************/
#define MIO_SHIFTSIEN_SSIE_Msk             ((uint32_t)0xff)   /* bit mask, 移位状态标志中断使能
0：移位状态标志中断不使能
1：移位状态标志中断使能
如果标志位中断使能，当 SSF 标志位置 1 时，生成 MIO 中断
*/
#define MIO_SHIFTSIEN_SSIE_Pos             ((uint32_t)0)   /*bit position, 移位状态标志中断使能
0：移位状态标志中断不使能
1：移位状态标志中断使能
如果标志位中断使能，当 SSF 标志位置 1 时，生成 MIO 中断
*/

/******************  Bit Definition for Register MIO_SHIFTEIEN  *********************/
#define MIO_SHIFTEIEN_SEIE_Msk             ((uint32_t)0xff)   /* bit mask, 移位错误状态标志中断使能
0：移位错误状态标志中断不使能
1：移位错误状态标志中断使能
如果标志位中断使能，当 SEF 标志位置 1 时，生成 MIO 中断
*/
#define MIO_SHIFTEIEN_SEIE_Pos             ((uint32_t)0)   /*bit position, 移位错误状态标志中断使能
0：移位错误状态标志中断不使能
1：移位错误状态标志中断使能
如果标志位中断使能，当 SEF 标志位置 1 时，生成 MIO 中断
*/

/******************  Bit Definition for Register MIO_TIMIEN  *********************/
#define MIO_TIMIEN_TEIE_Msk             ((uint32_t)0xff)   /* bit mask, 定时器状态标志中断使能
0：定时器状态标志中断不使能
1：定时器状态标志中断使能
如果标志位中断使能，当 TSF 标志位置 1 时，生成 MIO 中断
*/
#define MIO_TIMIEN_TEIE_Pos             ((uint32_t)0)   /*bit position, 定时器状态标志中断使能
0：定时器状态标志中断不使能
1：定时器状态标志中断使能
如果标志位中断使能，当 TSF 标志位置 1 时，生成 MIO 中断
*/

/******************  Bit Definition for Register MIO_SHIFTSDEN  *********************/
#define MIO_SHIFTSDEN_SSDE_Msk             ((uint32_t)0xff)   /* bit mask, 移位状态 DMA 使能
0：移位状态 DMA 不使能
1：移位状态 DMA 使能
如果移位状态 DMA 使能，当 SSF 标志位置 1 时，生成 DMA 请求
*/
#define MIO_SHIFTSDEN_SSDE_Pos             ((uint32_t)0)   /*bit position, 移位状态 DMA 使能
0：移位状态 DMA 不使能
1：移位状态 DMA 使能
如果移位状态 DMA 使能，当 SSF 标志位置 1 时，生成 DMA 请求
*/

/******************  Bit Definition for Register MIO_SHIFTCTL0  *********************/
#define MIO_SHIFTCTL0_SMOD_Msk             ((uint32_t)0x7)   /* bit mask, 移位寄存器模式
000b：不使能
001b：接收模式，在定时器计时到时将移位寄存器的内容加载到缓冲器(SHIFTBUF)中。
010b：发送模式，在定时器计时到时将缓冲器(SHIFTBUF)的内容传输到移位寄存器中。
100b：匹配接收模式，在定时器计时到时将移位寄存器的数据与缓冲器(SHIFTBUF)进行匹配，匹配成功时，将数据加载到缓冲器(SHIFTBUF)里面。
*/
#define MIO_SHIFTCTL0_SMOD_Pos             ((uint32_t)0)   /*bit position, 移位寄存器模式
000b：不使能
001b：接收模式，在定时器计时到时将移位寄存器的内容加载到缓冲器(SHIFTBUF)中。
010b：发送模式，在定时器计时到时将缓冲器(SHIFTBUF)的内容传输到移位寄存器中。
100b：匹配接收模式，在定时器计时到时将移位寄存器的数据与缓冲器(SHIFTBUF)进行匹配，匹配成功时，将数据加载到缓冲器(SHIFTBUF)里面。
*/
#define MIO_SHIFTCTL0_PINPOL_Msk             ((uint32_t)0x80)   /* bit mask, 移位寄存器引脚极性
0：高电平有效
1：低电平有效
*/
#define MIO_SHIFTCTL0_PINPOL_Pos             ((uint32_t)7)   /*bit position, 移位寄存器引脚极性
0：高电平有效
1：低电平有效
*/
#define MIO_SHIFTCTL0_PINSEL_Msk             ((uint32_t)0x1f00)   /* bit mask, 移位寄存器引脚选择
0-3：MIO_Pin0 - MIO_Pin3
*/
#define MIO_SHIFTCTL0_PINSEL_Pos             ((uint32_t)8)   /*bit position, 移位寄存器引脚选择
0-3：MIO_Pin0 - MIO_Pin3
*/
#define MIO_SHIFTCTL0_PINCFG_Msk             ((uint32_t)0x30000)   /* bit mask, 移位寄存器引脚配置
00b：移位寄存器引脚输出不使能，即为输入
01b：移位寄存器引脚开漏输出
10b：保留
11b：移位寄存器引脚输出
*/
#define MIO_SHIFTCTL0_PINCFG_Pos             ((uint32_t)16)   /*bit position, 移位寄存器引脚配置
00b：移位寄存器引脚输出不使能，即为输入
01b：移位寄存器引脚开漏输出
10b：保留
11b：移位寄存器引脚输出
*/
#define MIO_SHIFTCTL0_TIMPOL_Msk             ((uint32_t)0x800000)   /* bit mask, 定时器极性
0：在移位寄存器时钟的上升沿移位
1：在移位寄存器时钟的下降沿移位
*/
#define MIO_SHIFTCTL0_TIMPOL_Pos             ((uint32_t)23)   /*bit position, 定时器极性
0：在移位寄存器时钟的上升沿移位
1：在移位寄存器时钟的下降沿移位
*/
#define MIO_SHIFTCTL0_TIMSEL_Msk             ((uint32_t)0x7000000)   /* bit mask, 定时器选择
0-1：timer0-timer1
选择用于控制移位寄存器和生成移位寄存器时钟的定时器
*/
#define MIO_SHIFTCTL0_TIMSEL_Pos             ((uint32_t)24)   /*bit position, 定时器选择
0-1：timer0-timer1
选择用于控制移位寄存器和生成移位寄存器时钟的定时器
*/

/******************  Bit Definition for Register MIO_SHIFTCTL1  *********************/
#define MIO_SHIFTCTL1_SMOD_Msk             ((uint32_t)0x7)   /* bit mask, 移位寄存器模式
000b：不使能
001b：接收模式，在定时器计时到时将移位寄存器的内容加载到缓冲器(SHIFTBUF)中。
010b：发送模式，在定时器计时到时将缓冲器(SHIFTBUF)的内容传输到移位寄存器中。
100b：匹配接收模式，在定时器计时到时将移位寄存器的数据与缓冲器(SHIFTBUF)进行匹配，匹配成功时，将数据加载到缓冲器(SHIFTBUF)里面。
*/
#define MIO_SHIFTCTL1_SMOD_Pos             ((uint32_t)0)   /*bit position, 移位寄存器模式
000b：不使能
001b：接收模式，在定时器计时到时将移位寄存器的内容加载到缓冲器(SHIFTBUF)中。
010b：发送模式，在定时器计时到时将缓冲器(SHIFTBUF)的内容传输到移位寄存器中。
100b：匹配接收模式，在定时器计时到时将移位寄存器的数据与缓冲器(SHIFTBUF)进行匹配，匹配成功时，将数据加载到缓冲器(SHIFTBUF)里面。
*/
#define MIO_SHIFTCTL1_PINPOL_Msk             ((uint32_t)0x80)   /* bit mask, 移位寄存器引脚极性
0：高电平有效
1：低电平有效
*/
#define MIO_SHIFTCTL1_PINPOL_Pos             ((uint32_t)7)   /*bit position, 移位寄存器引脚极性
0：高电平有效
1：低电平有效
*/
#define MIO_SHIFTCTL1_PINSEL_Msk             ((uint32_t)0x1f00)   /* bit mask, 移位寄存器引脚选择
0-3：MIO_Pin0 - MIO_Pin3
*/
#define MIO_SHIFTCTL1_PINSEL_Pos             ((uint32_t)8)   /*bit position, 移位寄存器引脚选择
0-3：MIO_Pin0 - MIO_Pin3
*/
#define MIO_SHIFTCTL1_PINCFG_Msk             ((uint32_t)0x30000)   /* bit mask, 移位寄存器引脚配置
00b：移位寄存器引脚输出不使能，即为输入
01b：移位寄存器引脚开漏输出
10b：保留
11b：移位寄存器引脚输出
*/
#define MIO_SHIFTCTL1_PINCFG_Pos             ((uint32_t)16)   /*bit position, 移位寄存器引脚配置
00b：移位寄存器引脚输出不使能，即为输入
01b：移位寄存器引脚开漏输出
10b：保留
11b：移位寄存器引脚输出
*/
#define MIO_SHIFTCTL1_TIMPOL_Msk             ((uint32_t)0x800000)   /* bit mask, 定时器极性
0：在移位寄存器时钟的上升沿移位
1：在移位寄存器时钟的下降沿移位
*/
#define MIO_SHIFTCTL1_TIMPOL_Pos             ((uint32_t)23)   /*bit position, 定时器极性
0：在移位寄存器时钟的上升沿移位
1：在移位寄存器时钟的下降沿移位
*/
#define MIO_SHIFTCTL1_TIMSEL_Msk             ((uint32_t)0x7000000)   /* bit mask, 定时器选择
0-1：timer0-timer1
选择用于控制移位寄存器和生成移位寄存器时钟的定时器
*/
#define MIO_SHIFTCTL1_TIMSEL_Pos             ((uint32_t)24)   /*bit position, 定时器选择
0-1：timer0-timer1
选择用于控制移位寄存器和生成移位寄存器时钟的定时器
*/

/******************  Bit Definition for Register MIO_SHIFTCFG0  *********************/
#define MIO_SHIFTCFG0_SSTART_Msk             ((uint32_t)0x3)   /* bit mask, 移位寄存器起始位
00b：禁用起始位，发送寄存器在定时器使能时加载数据
01b：禁用起始位，发送寄存器在第一次移位时加载数据
10b：在第一次移位加载数据之前，发送器输出起始位0，如果起始位不为0，则接收器/
匹配存储设置错误标志
11b：在第一次移位加载数据之前，发送器输出起始位1，如果起始位不为1，则接收器/
匹配存储设置错误标志
当为发送模式时(SMOD = 010b)，如果所选的定时器启用了起始位，则允许自动插入起始位。
当为接收模式 / 匹配接收模式时(SMOD = 001b / SMOD = 100b)，如果所选的定时器启用了起始位，则允许自动检测起始位。
*/
#define MIO_SHIFTCFG0_SSTART_Pos             ((uint32_t)0)   /*bit position, 移位寄存器起始位
00b：禁用起始位，发送寄存器在定时器使能时加载数据
01b：禁用起始位，发送寄存器在第一次移位时加载数据
10b：在第一次移位加载数据之前，发送器输出起始位0，如果起始位不为0，则接收器/
匹配存储设置错误标志
11b：在第一次移位加载数据之前，发送器输出起始位1，如果起始位不为1，则接收器/
匹配存储设置错误标志
当为发送模式时(SMOD = 010b)，如果所选的定时器启用了起始位，则允许自动插入起始位。
当为接收模式 / 匹配接收模式时(SMOD = 001b / SMOD = 100b)，如果所选的定时器启用了起始位，则允许自动检测起始位。
*/
#define MIO_SHIFTCFG0_SSTOP_Msk             ((uint32_t)0x30)   /* bit mask, 移位寄存器停止位
00b：禁用停止位
01b：保留
10b：发送器在存储时输出停止位值 0，如果停止位不为 0，接收器/匹配存储设置错误标志
11b：发送器在存储时输出停止位值 1，如果停止位不是 1，接收器/匹配存储设置错误标志
当为发送模式时(SMOD = 010b)，如果所选的定时器启用了停止位，则允许自动插入停止位。
 
当为接收模式 / 匹配接收模式时(SMOD = 001b / SMOD = 100b)，如果所选的定时器启用了停止位，则允许自动检测停止位。
*/
#define MIO_SHIFTCFG0_SSTOP_Pos             ((uint32_t)4)   /*bit position, 移位寄存器停止位
00b：禁用停止位
01b：保留
10b：发送器在存储时输出停止位值 0，如果停止位不为 0，接收器/匹配存储设置错误标志
11b：发送器在存储时输出停止位值 1，如果停止位不是 1，接收器/匹配存储设置错误标志
当为发送模式时(SMOD = 010b)，如果所选的定时器启用了停止位，则允许自动插入停止位。
 
当为接收模式 / 匹配接收模式时(SMOD = 001b / SMOD = 100b)，如果所选的定时器启用了停止位，则允许自动检测停止位。
*/
#define MIO_SHIFTCFG0_INSRC_Msk             ((uint32_t)0x100)   /* bit mask, 移位寄存器输入源选择
0：输入源选择引脚
1：输入源选择前一个移位寄存器(N+1)的输出
最后一个移位器不支持配置 INSRC=1。
*/
#define MIO_SHIFTCFG0_INSRC_Pos             ((uint32_t)8)   /*bit position, 移位寄存器输入源选择
0：输入源选择引脚
1：输入源选择前一个移位寄存器(N+1)的输出
最后一个移位器不支持配置 INSRC=1。
*/
#define MIO_SHIFTCFG0_LATST_Msk             ((uint32_t)0x200)   /* bit mask, 延迟存储
配置当 receive 或 match shift register 配置为在同一周期上同时 shift 和 store 时发生的情况。
0 - Shift register 存储移位前寄存器状态。
1 - Shift register 存储移位后寄存器状态。
*/
#define MIO_SHIFTCFG0_LATST_Pos             ((uint32_t)9)   /*bit position, 延迟存储
配置当 receive 或 match shift register 配置为在同一周期上同时 shift 和 store 时发生的情况。
0 - Shift register 存储移位前寄存器状态。
1 - Shift register 存储移位后寄存器状态。
*/
#define MIO_SHIFTCFG0_SSIZE_Msk             ((uint32_t)0x1000)   /* bit mask, 移位寄存器大小
配置 Shift Registers 的大小。
24 位移位寄存器仅将数据移位为位 [23：0]，在移位作期间不更新位 [31：24]。
当 shift register 配置为 24 bit shift 时，配置 PWIDTH=8..15 执行 12 bit shift，PWIDTH=16..31 执行 24 bit shift。
0 - 移位寄存器为 32 位。
1 - 移位寄存器为 24 位。
*/
#define MIO_SHIFTCFG0_SSIZE_Pos             ((uint32_t)12)   /*bit position, 移位寄存器大小
配置 Shift Registers 的大小。
24 位移位寄存器仅将数据移位为位 [23：0]，在移位作期间不更新位 [31：24]。
当 shift register 配置为 24 bit shift 时，配置 PWIDTH=8..15 执行 12 bit shift，PWIDTH=16..31 执行 24 bit shift。
0 - 移位寄存器为 32 位。
1 - 移位寄存器为 24 位。
*/
#define MIO_SHIFTCFG0_PWIDTH_Msk             ((uint32_t)0x1f0000)   /* bit mask, 并行宽度
对于所有 shifters，此字段配置每个 shift clock 上要移位的 bits 数，如下所示：
PWIDTH=0 时 1 位移位
PWIDTH=1 时 2 位移
PWIDTH=2...3 时为 4 位偏移
PWIDTH=4...7 时的 8 位移位
PWIDTH=8...15 时为 16 位移位
PWIDTH=16...31 时为 32 位偏移
*/
#define MIO_SHIFTCFG0_PWIDTH_Pos             ((uint32_t)16)   /*bit position, 并行宽度
对于所有 shifters，此字段配置每个 shift clock 上要移位的 bits 数，如下所示：
PWIDTH=0 时 1 位移位
PWIDTH=1 时 2 位移
PWIDTH=2...3 时为 4 位偏移
PWIDTH=4...7 时的 8 位移位
PWIDTH=8...15 时为 16 位移位
PWIDTH=16...31 时为 32 位偏移
*/

/******************  Bit Definition for Register MIO_SHIFTCFG1  *********************/
#define MIO_SHIFTCFG1_SSTART_Msk             ((uint32_t)0x3)   /* bit mask, 移位寄存器起始位
00b：禁用起始位，发送寄存器在定时器使能时加载数据
01b：禁用起始位，发送寄存器在第一次移位时加载数据
10b：在第一次移位加载数据之前，发送器输出起始位0，如果起始位不为0，则接收器/
匹配存储设置错误标志
11b：在第一次移位加载数据之前，发送器输出起始位1，如果起始位不为1，则接收器/
匹配存储设置错误标志
当为发送模式时(SMOD = 010b)，如果所选的定时器启用了起始位，则允许自动插入起始位。
当为接收模式 / 匹配接收模式时(SMOD = 001b / SMOD = 100b)，如果所选的定时器启用了起始位，则允许自动检测起始位。
*/
#define MIO_SHIFTCFG1_SSTART_Pos             ((uint32_t)0)   /*bit position, 移位寄存器起始位
00b：禁用起始位，发送寄存器在定时器使能时加载数据
01b：禁用起始位，发送寄存器在第一次移位时加载数据
10b：在第一次移位加载数据之前，发送器输出起始位0，如果起始位不为0，则接收器/
匹配存储设置错误标志
11b：在第一次移位加载数据之前，发送器输出起始位1，如果起始位不为1，则接收器/
匹配存储设置错误标志
当为发送模式时(SMOD = 010b)，如果所选的定时器启用了起始位，则允许自动插入起始位。
当为接收模式 / 匹配接收模式时(SMOD = 001b / SMOD = 100b)，如果所选的定时器启用了起始位，则允许自动检测起始位。
*/
#define MIO_SHIFTCFG1_SSTOP_Msk             ((uint32_t)0x30)   /* bit mask, 移位寄存器停止位
00b：禁用停止位
01b：保留
10b：发送器在存储时输出停止位值 0，如果停止位不为 0，接收器/匹配存储设置错误标志
11b：发送器在存储时输出停止位值 1，如果停止位不是 1，接收器/匹配存储设置错误标志
当为发送模式时(SMOD = 010b)，如果所选的定时器启用了停止位，则允许自动插入停止位。
 
当为接收模式 / 匹配接收模式时(SMOD = 001b / SMOD = 100b)，如果所选的定时器启用了停止位，则允许自动检测停止位。
*/
#define MIO_SHIFTCFG1_SSTOP_Pos             ((uint32_t)4)   /*bit position, 移位寄存器停止位
00b：禁用停止位
01b：保留
10b：发送器在存储时输出停止位值 0，如果停止位不为 0，接收器/匹配存储设置错误标志
11b：发送器在存储时输出停止位值 1，如果停止位不是 1，接收器/匹配存储设置错误标志
当为发送模式时(SMOD = 010b)，如果所选的定时器启用了停止位，则允许自动插入停止位。
 
当为接收模式 / 匹配接收模式时(SMOD = 001b / SMOD = 100b)，如果所选的定时器启用了停止位，则允许自动检测停止位。
*/
#define MIO_SHIFTCFG1_INSRC_Msk             ((uint32_t)0x100)   /* bit mask, 移位寄存器输入源选择
0：输入源选择引脚
1：输入源选择前一个移位寄存器(N+1)的输出
最后一个移位器不支持配置 INSRC=1。
*/
#define MIO_SHIFTCFG1_INSRC_Pos             ((uint32_t)8)   /*bit position, 移位寄存器输入源选择
0：输入源选择引脚
1：输入源选择前一个移位寄存器(N+1)的输出
最后一个移位器不支持配置 INSRC=1。
*/
#define MIO_SHIFTCFG1_LATST_Msk             ((uint32_t)0x200)   /* bit mask, 延迟存储
配置当 receive 或 match shift register 配置为在同一周期上同时 shift 和 store 时发生的情况。
0 - Shift register 存储移位前寄存器状态。
1 - Shift register 存储移位后寄存器状态。
*/
#define MIO_SHIFTCFG1_LATST_Pos             ((uint32_t)9)   /*bit position, 延迟存储
配置当 receive 或 match shift register 配置为在同一周期上同时 shift 和 store 时发生的情况。
0 - Shift register 存储移位前寄存器状态。
1 - Shift register 存储移位后寄存器状态。
*/
#define MIO_SHIFTCFG1_SSIZE_Msk             ((uint32_t)0x1000)   /* bit mask, 移位寄存器大小
配置 Shift Registers 的大小。
24 位移位寄存器仅将数据移位为位 [23：0]，在移位作期间不更新位 [31：24]。
当 shift register 配置为 24 bit shift 时，配置 PWIDTH=8..15 执行 12 bit shift，PWIDTH=16..31 执行 24 bit shift。
0 - 移位寄存器为 32 位。
1 - 移位寄存器为 24 位。
*/
#define MIO_SHIFTCFG1_SSIZE_Pos             ((uint32_t)12)   /*bit position, 移位寄存器大小
配置 Shift Registers 的大小。
24 位移位寄存器仅将数据移位为位 [23：0]，在移位作期间不更新位 [31：24]。
当 shift register 配置为 24 bit shift 时，配置 PWIDTH=8..15 执行 12 bit shift，PWIDTH=16..31 执行 24 bit shift。
0 - 移位寄存器为 32 位。
1 - 移位寄存器为 24 位。
*/
#define MIO_SHIFTCFG1_PWIDTH_Msk             ((uint32_t)0x1f0000)   /* bit mask, 并行宽度
对于所有 shifters，此字段配置每个 shift clock 上要移位的 bits 数，如下所示：
PWIDTH=0 时 1 位移位
PWIDTH=1 时 2 位移
PWIDTH=2...3 时为 4 位偏移
PWIDTH=4...7 时的 8 位移位
PWIDTH=8...15 时为 16 位移位
PWIDTH=16...31 时为 32 位偏移
*/
#define MIO_SHIFTCFG1_PWIDTH_Pos             ((uint32_t)16)   /*bit position, 并行宽度
对于所有 shifters，此字段配置每个 shift clock 上要移位的 bits 数，如下所示：
PWIDTH=0 时 1 位移位
PWIDTH=1 时 2 位移
PWIDTH=2...3 时为 4 位偏移
PWIDTH=4...7 时的 8 位移位
PWIDTH=8...15 时为 16 位移位
PWIDTH=16...31 时为 32 位偏移
*/

/******************  Bit Definition for Register MIO_SHIFTBUF0  *********************/
#define MIO_SHIFTBUF0_SHIFTBUF_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位缓冲寄存器
当为接收模式时(SMOD = 001b)，在定时器计时到时，移位寄存器的数据被加载到缓冲器(SHIFTBUF)中，并置位相应的移位状态寄存器 SHIFSTAT。
当为发送模式时(SMOD = 010b)， 在定时器开始计时之前，缓冲器(SHIFTBUF)的数据被传输到移位寄存器中。
当为匹配接收模式时(SMOD =  100b)， 缓冲器 SHIFTBUF[15:0] 包含要匹配的数据， SHIFTBUF[31:16] 为 Mask 位，用于屏蔽匹配位(1 无需匹配，0 需匹配）。当
检测到数据匹配时，移位器寄存器数据 [15:0] 被写入 SHIFTBUF[15:0]，并且相应的状态寄存器置位。
说明：接收模式是低位优先，也就是先进来的数据放在移位寄存器低位。匹配模式是高位优先，也就是先进来的数据放在移位寄存器高位。
*/
#define MIO_SHIFTBUF0_SHIFTBUF_Pos             ((uint32_t)0)   /*bit position, 移位缓冲寄存器
当为接收模式时(SMOD = 001b)，在定时器计时到时，移位寄存器的数据被加载到缓冲器(SHIFTBUF)中，并置位相应的移位状态寄存器 SHIFSTAT。
当为发送模式时(SMOD = 010b)， 在定时器开始计时之前，缓冲器(SHIFTBUF)的数据被传输到移位寄存器中。
当为匹配接收模式时(SMOD =  100b)， 缓冲器 SHIFTBUF[15:0] 包含要匹配的数据， SHIFTBUF[31:16] 为 Mask 位，用于屏蔽匹配位(1 无需匹配，0 需匹配）。当
检测到数据匹配时，移位器寄存器数据 [15:0] 被写入 SHIFTBUF[15:0]，并且相应的状态寄存器置位。
说明：接收模式是低位优先，也就是先进来的数据放在移位寄存器低位。匹配模式是高位优先，也就是先进来的数据放在移位寄存器高位。
*/

/******************  Bit Definition for Register MIO_SHIFTBUF1  *********************/
#define MIO_SHIFTBUF1_SHIFTBUF_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位缓冲寄存器
当为接收模式时(SMOD = 001b)，在定时器计时到时，移位寄存器的数据被加载到缓冲器(SHIFTBUF)中，并置位相应的移位状态寄存器 SHIFSTAT。
当为发送模式时(SMOD = 010b)， 在定时器开始计时之前，缓冲器(SHIFTBUF)的数据被传输到移位寄存器中。
当为匹配接收模式时(SMOD =  100b)， 缓冲器 SHIFTBUF[15:0] 包含要匹配的数据， SHIFTBUF[31:16] 为 Mask 位，用于屏蔽匹配位(1 无需匹配，0 需匹配）。当
检测到数据匹配时，移位器寄存器数据 [15:0] 被写入 SHIFTBUF[15:0]，并且相应的状态寄存器置位。
说明：接收模式是低位优先，也就是先进来的数据放在移位寄存器低位。匹配模式是高位优先，也就是先进来的数据放在移位寄存器高位。
*/
#define MIO_SHIFTBUF1_SHIFTBUF_Pos             ((uint32_t)0)   /*bit position, 移位缓冲寄存器
当为接收模式时(SMOD = 001b)，在定时器计时到时，移位寄存器的数据被加载到缓冲器(SHIFTBUF)中，并置位相应的移位状态寄存器 SHIFSTAT。
当为发送模式时(SMOD = 010b)， 在定时器开始计时之前，缓冲器(SHIFTBUF)的数据被传输到移位寄存器中。
当为匹配接收模式时(SMOD =  100b)， 缓冲器 SHIFTBUF[15:0] 包含要匹配的数据， SHIFTBUF[31:16] 为 Mask 位，用于屏蔽匹配位(1 无需匹配，0 需匹配）。当
检测到数据匹配时，移位器寄存器数据 [15:0] 被写入 SHIFTBUF[15:0]，并且相应的状态寄存器置位。
说明：接收模式是低位优先，也就是先进来的数据放在移位寄存器低位。匹配模式是高位优先，也就是先进来的数据放在移位寄存器高位。
*/

/******************  Bit Definition for Register MIO_SHIFTBUFBIS0  *********************/
#define MIO_SHIFTBUFBIS0_SHIFTBUFBIS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位缓冲位交换寄存器
访问 SHIFTBUFBIS 本质上就是访问 SHIFTBUF，但对 SHIFTBUFBIS 的访问是位交换的
例：读取 SHIFTBUFBIS[31:0]，返回的是 SHIFTBUF[0:31]的结果
*/
#define MIO_SHIFTBUFBIS0_SHIFTBUFBIS_Pos             ((uint32_t)0)   /*bit position, 移位缓冲位交换寄存器
访问 SHIFTBUFBIS 本质上就是访问 SHIFTBUF，但对 SHIFTBUFBIS 的访问是位交换的
例：读取 SHIFTBUFBIS[31:0]，返回的是 SHIFTBUF[0:31]的结果
*/

/******************  Bit Definition for Register MIO_SHIFTBUFBIS1  *********************/
#define MIO_SHIFTBUFBIS1_SHIFTBUFBIS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲位交换寄存器1*/
#define MIO_SHIFTBUFBIS1_SHIFTBUFBIS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲位交换寄存器1*/

/******************  Bit Definition for Register MIO_SHIFTBUFBYS0  *********************/
#define MIO_SHIFTBUFBYS0_SHIFTBUFBYS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位缓冲字节交换寄存器
访问 SHIFTBUFBYS 本质上就是访问 SHIFTBUF，但对 SHIFTBUFBYS 的访问是字节交换的
例：读取 SHIFTBUFBYS[31:0]，返回的是 SHIFTBUF[7:0]、SHIFTBUF[15:8]、SHIFTBUF[23:16]、SHIFTBUF[31:24]的结果
*/
#define MIO_SHIFTBUFBYS0_SHIFTBUFBYS_Pos             ((uint32_t)0)   /*bit position, 移位缓冲字节交换寄存器
访问 SHIFTBUFBYS 本质上就是访问 SHIFTBUF，但对 SHIFTBUFBYS 的访问是字节交换的
例：读取 SHIFTBUFBYS[31:0]，返回的是 SHIFTBUF[7:0]、SHIFTBUF[15:8]、SHIFTBUF[23:16]、SHIFTBUF[31:24]的结果
*/

/******************  Bit Definition for Register MIO_SHIFTBUFBYS1  *********************/
#define MIO_SHIFTBUFBYS1_SHIFTBUFBYS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲字节交换寄存器1*/
#define MIO_SHIFTBUFBYS1_SHIFTBUFBYS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲字节交换寄存器1*/

/******************  Bit Definition for Register MIO_SHIFTBUFBBS0  *********************/
#define MIO_SHIFTBUFBBS0_SHIFTBUFBBSN_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位缓冲位字节交换寄存器
访问 SHIFTBUFBYS 本质上就是访问 SHIFTBUF，但对 SHIFTBUFBYS 的访问是位字节交换的
例：读取 SHIFTBUFBBS[31:0]，返回的是 SHIFTBUF[24:31], SHIFTBUF[16:23], SHIFTBUF[8:15], SHIFTBUF[0:7]的结果
*/
#define MIO_SHIFTBUFBBS0_SHIFTBUFBBSN_Pos             ((uint32_t)0)   /*bit position, 移位缓冲位字节交换寄存器
访问 SHIFTBUFBYS 本质上就是访问 SHIFTBUF，但对 SHIFTBUFBYS 的访问是位字节交换的
例：读取 SHIFTBUFBBS[31:0]，返回的是 SHIFTBUF[24:31], SHIFTBUF[16:23], SHIFTBUF[8:15], SHIFTBUF[0:7]的结果
*/

/******************  Bit Definition for Register MIO_SHIFTBUFBBS1  *********************/
#define MIO_SHIFTBUFBBS1_SHIFTBUFBBSN_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲位字节交换寄存器1*/
#define MIO_SHIFTBUFBBS1_SHIFTBUFBBSN_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲位字节交换寄存器1*/

/******************  Bit Definition for Register MIO_TIMCTL0  *********************/
#define MIO_TIMCTL0_TIMOD_Msk             ((uint32_t)0x7)   /* bit mask, 定时器模式
00b：定时器禁用
01b ：双 8 位计数器波特率模式
10b ：双 8 位计数器 PWM 模式
11b ：单 16 位计数器模式
1.    在 8 位波特计数器模式下，计数器和比较寄存器的低 8 位用于配置定时器移位时钟的波特率，高 8 位用于配置移位寄存器的位数。
2.    在8位PWM高电平模式下，计数器和比较寄存器的低8位用于配置定时器移位时钟的高电平周期，高8位用于配置定时器移位时钟的低电平周期。
3.    在 16 位计数器模式下，计数器和比较寄存器的全部 16 位用于配置移位时钟的波特率或移位寄存器位计数。
*/
#define MIO_TIMCTL0_TIMOD_Pos             ((uint32_t)0)   /*bit position, 定时器模式
00b：定时器禁用
01b ：双 8 位计数器波特率模式
10b ：双 8 位计数器 PWM 模式
11b ：单 16 位计数器模式
1.    在 8 位波特计数器模式下，计数器和比较寄存器的低 8 位用于配置定时器移位时钟的波特率，高 8 位用于配置移位寄存器的位数。
2.    在8位PWM高电平模式下，计数器和比较寄存器的低8位用于配置定时器移位时钟的高电平周期，高8位用于配置定时器移位时钟的低电平周期。
3.    在 16 位计数器模式下，计数器和比较寄存器的全部 16 位用于配置移位时钟的波特率或移位寄存器位计数。
*/
#define MIO_TIMCTL0_ONETIM_Msk             ((uint32_t)0x20)   /* bit mask, */
#define MIO_TIMCTL0_ONETIM_Pos             ((uint32_t)5)   /*bit position, */
#define MIO_TIMCTL0_PININS_Msk             ((uint32_t)0x40)   /* bit mask, */
#define MIO_TIMCTL0_PININS_Pos             ((uint32_t)6)   /*bit position, */
#define MIO_TIMCTL0_PINPOL_Msk             ((uint32_t)0x80)   /* bit mask, 定时器引脚极性
0：高电平有效
1：低电平有效
*/
#define MIO_TIMCTL0_PINPOL_Pos             ((uint32_t)7)   /*bit position, 定时器引脚极性
0：高电平有效
1：低电平有效
*/
#define MIO_TIMCTL0_PINSEL_Msk             ((uint32_t)0x1f00)   /* bit mask, 定时器引脚选择
0-3：MIO_Pin0 - MIO_Pin3
选择定时器控制的引脚
*/
#define MIO_TIMCTL0_PINSEL_Pos             ((uint32_t)8)   /*bit position, 定时器引脚选择
0-3：MIO_Pin0 - MIO_Pin3
选择定时器控制的引脚
*/
#define MIO_TIMCTL0_PINCFG_Msk             ((uint32_t)0x30000)   /* bit mask, 定时器引脚配置
00b：定时器引脚输出不使能，即输入
01b：定时器引脚开漏输出
10b：保留
11b：定时器引脚输出
*/
#define MIO_TIMCTL0_PINCFG_Pos             ((uint32_t)16)   /*bit position, 定时器引脚配置
00b：定时器引脚输出不使能，即输入
01b：定时器引脚开漏输出
10b：保留
11b：定时器引脚输出
*/
#define MIO_TIMCTL0_TRGSRC_Msk             ((uint32_t)0x400000)   /* bit mask, 触发源选择
0：外部触发
1：内部触发
*/
#define MIO_TIMCTL0_TRGSRC_Pos             ((uint32_t)22)   /*bit position, 触发源选择
0：外部触发
1：内部触发
*/
#define MIO_TIMCTL0_TRGPOL_Msk             ((uint32_t)0x800000)   /* bit mask, 触发极性
0：高电平有效
1：低电平有效
*/
#define MIO_TIMCTL0_TRGPOL_Pos             ((uint32_t)23)   /*bit position, 触发极性
0：高电平有效
1：低电平有效
*/
#define MIO_TIMCTL0_TRGSEL_Msk             ((uint32_t)0x3f000000)   /* bit mask, 触发选择
对于引脚触发，N=0 到 3
对于移位寄存器触发，N=0 到 1
对于定时器触发，N=0 到 1
说明：Crosslink 触发为外部触发，其它的触发都为内部触发
当配置为外部触发时(TRGSRC = 0)
    N：External trigger N input
当配置为内部触发时(TRGSRC = 1)
    2*N：引脚 N 的触发
    4*N+1 ：移位寄存器 N 的状态标志位
    4*N+3 ：定时器 N 的触发
换种方式描述，内部触发选择为：
    0000 = 引脚 0
    0001 = 移位寄存器 0 标志位
    0010 = 引脚 1
    0011 = 定时器 0 触发
    0100 = 引脚 2
    0101 = 移位寄存器 1 标志位
    0110 = 引脚 3
    0111 = 定时器 1 触发
    ...
*/
#define MIO_TIMCTL0_TRGSEL_Pos             ((uint32_t)24)   /*bit position, 触发选择
对于引脚触发，N=0 到 3
对于移位寄存器触发，N=0 到 1
对于定时器触发，N=0 到 1
说明：Crosslink 触发为外部触发，其它的触发都为内部触发
当配置为外部触发时(TRGSRC = 0)
    N：External trigger N input
当配置为内部触发时(TRGSRC = 1)
    2*N：引脚 N 的触发
    4*N+1 ：移位寄存器 N 的状态标志位
    4*N+3 ：定时器 N 的触发
换种方式描述，内部触发选择为：
    0000 = 引脚 0
    0001 = 移位寄存器 0 标志位
    0010 = 引脚 1
    0011 = 定时器 0 触发
    0100 = 引脚 2
    0101 = 移位寄存器 1 标志位
    0110 = 引脚 3
    0111 = 定时器 1 触发
    ...
*/

/******************  Bit Definition for Register MIO_TIMCTL1  *********************/
#define MIO_TIMCTL1_TIMOD_Msk             ((uint32_t)0x7)   /* bit mask, 定时器模式
00b：定时器禁用
01b ：双 8 位计数器波特率模式
10b ：双 8 位计数器 PWM 模式
11b ：单 16 位计数器模式
1.    在 8 位波特计数器模式下，计数器和比较寄存器的低 8 位用于配置定时器移位时钟的波特率，高 8 位用于配置移位寄存器的位数。
2.    在8位PWM高电平模式下，计数器和比较寄存器的低8位用于配置定时器移位时钟的高电平周期，高8位用于配置定时器移位时钟的低电平周期。
3.    在 16 位计数器模式下，计数器和比较寄存器的全部 16 位用于配置移位时钟的波特率或移位寄存器位计数。
*/
#define MIO_TIMCTL1_TIMOD_Pos             ((uint32_t)0)   /*bit position, 定时器模式
00b：定时器禁用
01b ：双 8 位计数器波特率模式
10b ：双 8 位计数器 PWM 模式
11b ：单 16 位计数器模式
1.    在 8 位波特计数器模式下，计数器和比较寄存器的低 8 位用于配置定时器移位时钟的波特率，高 8 位用于配置移位寄存器的位数。
2.    在8位PWM高电平模式下，计数器和比较寄存器的低8位用于配置定时器移位时钟的高电平周期，高8位用于配置定时器移位时钟的低电平周期。
3.    在 16 位计数器模式下，计数器和比较寄存器的全部 16 位用于配置移位时钟的波特率或移位寄存器位计数。
*/
#define MIO_TIMCTL1_ONETIM_Msk             ((uint32_t)0x20)   /* bit mask, */
#define MIO_TIMCTL1_ONETIM_Pos             ((uint32_t)5)   /*bit position, */
#define MIO_TIMCTL1_PININS_Msk             ((uint32_t)0x40)   /* bit mask, */
#define MIO_TIMCTL1_PININS_Pos             ((uint32_t)6)   /*bit position, */
#define MIO_TIMCTL1_PINPOL_Msk             ((uint32_t)0x80)   /* bit mask, 定时器引脚极性
0：高电平有效
1：低电平有效
*/
#define MIO_TIMCTL1_PINPOL_Pos             ((uint32_t)7)   /*bit position, 定时器引脚极性
0：高电平有效
1：低电平有效
*/
#define MIO_TIMCTL1_PINSEL_Msk             ((uint32_t)0x1f00)   /* bit mask, 定时器引脚选择
0-3：MIO_Pin0 - MIO_Pin3
选择定时器控制的引脚
*/
#define MIO_TIMCTL1_PINSEL_Pos             ((uint32_t)8)   /*bit position, 定时器引脚选择
0-3：MIO_Pin0 - MIO_Pin3
选择定时器控制的引脚
*/
#define MIO_TIMCTL1_PINCFG_Msk             ((uint32_t)0x30000)   /* bit mask, 定时器引脚配置
00b：定时器引脚输出不使能，即输入
01b：定时器引脚开漏输出
10b：保留
11b：定时器引脚输出
*/
#define MIO_TIMCTL1_PINCFG_Pos             ((uint32_t)16)   /*bit position, 定时器引脚配置
00b：定时器引脚输出不使能，即输入
01b：定时器引脚开漏输出
10b：保留
11b：定时器引脚输出
*/
#define MIO_TIMCTL1_TRGSRC_Msk             ((uint32_t)0x400000)   /* bit mask, 触发源选择
0：外部触发
1：内部触发
*/
#define MIO_TIMCTL1_TRGSRC_Pos             ((uint32_t)22)   /*bit position, 触发源选择
0：外部触发
1：内部触发
*/
#define MIO_TIMCTL1_TRGPOL_Msk             ((uint32_t)0x800000)   /* bit mask, 触发极性
0：高电平有效
1：低电平有效
*/
#define MIO_TIMCTL1_TRGPOL_Pos             ((uint32_t)23)   /*bit position, 触发极性
0：高电平有效
1：低电平有效
*/
#define MIO_TIMCTL1_TRGSEL_Msk             ((uint32_t)0x3f000000)   /* bit mask, 触发选择
对于引脚触发，N=0 到 3
对于移位寄存器触发，N=0 到 1
对于定时器触发，N=0 到 1
说明：Crosslink 触发为外部触发，其它的触发都为内部触发
当配置为外部触发时(TRGSRC = 0)
    N：External trigger N input
当配置为内部触发时(TRGSRC = 1)
    2*N：引脚 N 的触发
    4*N+1 ：移位寄存器 N 的状态标志位
    4*N+3 ：定时器 N 的触发
换种方式描述，内部触发选择为：
    0000 = 引脚 0
    0001 = 移位寄存器 0 标志位
    0010 = 引脚 1
    0011 = 定时器 0 触发
    0100 = 引脚 2
    0101 = 移位寄存器 1 标志位
    0110 = 引脚 3
    0111 = 定时器 1 触发
    ...
*/
#define MIO_TIMCTL1_TRGSEL_Pos             ((uint32_t)24)   /*bit position, 触发选择
对于引脚触发，N=0 到 3
对于移位寄存器触发，N=0 到 1
对于定时器触发，N=0 到 1
说明：Crosslink 触发为外部触发，其它的触发都为内部触发
当配置为外部触发时(TRGSRC = 0)
    N：External trigger N input
当配置为内部触发时(TRGSRC = 1)
    2*N：引脚 N 的触发
    4*N+1 ：移位寄存器 N 的状态标志位
    4*N+3 ：定时器 N 的触发
换种方式描述，内部触发选择为：
    0000 = 引脚 0
    0001 = 移位寄存器 0 标志位
    0010 = 引脚 1
    0011 = 定时器 0 触发
    0100 = 引脚 2
    0101 = 移位寄存器 1 标志位
    0110 = 引脚 3
    0111 = 定时器 1 触发
    ...
*/

/******************  Bit Definition for Register MIO_TIMCFG0  *********************/
#define MIO_TIMCFG0_TSTART_Msk             ((uint32_t)0x2)   /* bit mask, 定时器起始位
0：禁用起始位
1：启用起始位
*/
#define MIO_TIMCFG0_TSTART_Pos             ((uint32_t)1)   /*bit position, 定时器起始位
0：禁用起始位
1：启用起始位
*/
#define MIO_TIMCFG0_TSTOP_Msk             ((uint32_t)0x30)   /* bit mask, 定时器停止位
00b：停止位禁用
01b：在定时器产生比较事件时启用停止位
10b：停止位在定时器禁用时启用
11b：在定时器产生比较事件时和定时器禁用时启用停止位
*/
#define MIO_TIMCFG0_TSTOP_Pos             ((uint32_t)4)   /*bit position, 定时器停止位
00b：停止位禁用
01b：在定时器产生比较事件时启用停止位
10b：停止位在定时器禁用时启用
11b：在定时器产生比较事件时和定时器禁用时启用停止位
*/
#define MIO_TIMCFG0_TIMENA_Msk             ((uint32_t)0x700)   /* bit mask, 定时器使能
000b：定时器始终启动
001b：在定时器 N-1 启动时启动定时器
010b：触发为高电平时启动定时器
011b：触发为高电平和引脚输入高电平时启动定时器
100b：在引脚输入上升沿时启动定时器
101b：在引脚输入上升沿和触发为高电平时启动定时器
110b：在触发为上升沿时启动定时器
111b：在触发为上升沿或下降沿时启动定时器
*/
#define MIO_TIMCFG0_TIMENA_Pos             ((uint32_t)8)   /*bit position, 定时器使能
000b：定时器始终启动
001b：在定时器 N-1 启动时启动定时器
010b：触发为高电平时启动定时器
011b：触发为高电平和引脚输入高电平时启动定时器
100b：在引脚输入上升沿时启动定时器
101b：在引脚输入上升沿和触发为高电平时启动定时器
110b：在触发为上升沿时启动定时器
111b：在触发为上升沿或下降沿时启动定时器
*/
#define MIO_TIMCFG0_TIMDIS_Msk             ((uint32_t)0x7000)   /* bit mask, 定时器引脚配置
000b：定时器从不停止
001b：在定时器 N-1 停止时停止定时器
010b：定时器产生比较事件时停止定时器
011b：定时器产生比较事件和触发为低时停止定时器
100b：在定时器引脚输入上升沿或者下降沿时停止定时器
101b：触发为高电平，引脚输入上升沿或者下降沿时停止定时器
110b：触发为下降沿时停止定时器
111b：保留
*/
#define MIO_TIMCFG0_TIMDIS_Pos             ((uint32_t)12)   /*bit position, 定时器引脚配置
000b：定时器从不停止
001b：在定时器 N-1 停止时停止定时器
010b：定时器产生比较事件时停止定时器
011b：定时器产生比较事件和触发为低时停止定时器
100b：在定时器引脚输入上升沿或者下降沿时停止定时器
101b：触发为高电平，引脚输入上升沿或者下降沿时停止定时器
110b：触发为下降沿时停止定时器
111b：保留
*/
#define MIO_TIMCFG0_TIMRST_Msk             ((uint32_t)0x70000)   /* bit mask, 定时器复位
000b：定时器永不复位
001b：保留
010b：当定时器引脚等于定时器输出时，定时器复位
011b：当定时器触发等于定时器输出时，定时器复位
100b：当定时器引脚输入上升沿时，定时器复位
101b：保留
110b：当定时器被上升沿触发时，定时器复位
说明：在 8 位计数器模式下，定时器复位只会复位配置波特率的低 8 位。在所有其他模
式下，定时器复位将重置计数器的全部 16 位
*/
#define MIO_TIMCFG0_TIMRST_Pos             ((uint32_t)16)   /*bit position, 定时器复位
000b：定时器永不复位
001b：保留
010b：当定时器引脚等于定时器输出时，定时器复位
011b：当定时器触发等于定时器输出时，定时器复位
100b：当定时器引脚输入上升沿时，定时器复位
101b：保留
110b：当定时器被上升沿触发时，定时器复位
说明：在 8 位计数器模式下，定时器复位只会复位配置波特率的低 8 位。在所有其他模
式下，定时器复位将重置计数器的全部 16 位
*/
#define MIO_TIMCFG0_TIMDEC_Msk             ((uint32_t)0x700000)   /* bit mask, 定时器递减
00b：定时器在MIO时钟上递减计数，移位时钟等于定时器输出
01b：定时器在触发输入(双边沿)上递减计数，移位时钟等于定时器输出
10b：定时器在引脚输入(双边沿)上递减计数，移位时钟等于引脚输入
11b：定时器在触发输入(双边沿)上递减计数，移位时钟等于触发输入
*/
#define MIO_TIMCFG0_TIMDEC_Pos             ((uint32_t)20)   /*bit position, 定时器递减
00b：定时器在MIO时钟上递减计数，移位时钟等于定时器输出
01b：定时器在触发输入(双边沿)上递减计数，移位时钟等于定时器输出
10b：定时器在引脚输入(双边沿)上递减计数，移位时钟等于引脚输入
11b：定时器在触发输入(双边沿)上递减计数，移位时钟等于触发输入
*/
#define MIO_TIMCFG0_TIMOUT_Msk             ((uint32_t)0x3000000)   /* bit mask, 定时器输出
00b：定时器输出在启用时为逻辑 1，不受定时器复位影响
01b：定时器输出在启用时为逻辑 0，不受定时器复位影响
10b：定时器输出在启用和定时器复位时为逻辑 1
11b：定时器输出在启用和定时器复位时为逻辑 0
*/
#define MIO_TIMCFG0_TIMOUT_Pos             ((uint32_t)24)   /*bit position, 定时器输出
00b：定时器输出在启用时为逻辑 1，不受定时器复位影响
01b：定时器输出在启用时为逻辑 0，不受定时器复位影响
10b：定时器输出在启用和定时器复位时为逻辑 1
11b：定时器输出在启用和定时器复位时为逻辑 0
*/

/******************  Bit Definition for Register MIO_TIMCFG1  *********************/
#define MIO_TIMCFG1_TSTART_Msk             ((uint32_t)0x2)   /* bit mask, 定时器起始位
0：禁用起始位
1：启用起始位
*/
#define MIO_TIMCFG1_TSTART_Pos             ((uint32_t)1)   /*bit position, 定时器起始位
0：禁用起始位
1：启用起始位
*/
#define MIO_TIMCFG1_TSTOP_Msk             ((uint32_t)0x30)   /* bit mask, 定时器停止位
00b：停止位禁用
01b：在定时器产生比较事件时启用停止位
10b：停止位在定时器禁用时启用
11b：在定时器产生比较事件时和定时器禁用时启用停止位
*/
#define MIO_TIMCFG1_TSTOP_Pos             ((uint32_t)4)   /*bit position, 定时器停止位
00b：停止位禁用
01b：在定时器产生比较事件时启用停止位
10b：停止位在定时器禁用时启用
11b：在定时器产生比较事件时和定时器禁用时启用停止位
*/
#define MIO_TIMCFG1_TIMENA_Msk             ((uint32_t)0x700)   /* bit mask, 定时器使能
000b：定时器始终启动
001b：在定时器 N-1 启动时启动定时器
010b：触发为高电平时启动定时器
011b：触发为高电平和引脚输入高电平时启动定时器
100b：在引脚输入上升沿时启动定时器
101b：在引脚输入上升沿和触发为高电平时启动定时器
110b：在触发为上升沿时启动定时器
111b：在触发为上升沿或下降沿时启动定时器
*/
#define MIO_TIMCFG1_TIMENA_Pos             ((uint32_t)8)   /*bit position, 定时器使能
000b：定时器始终启动
001b：在定时器 N-1 启动时启动定时器
010b：触发为高电平时启动定时器
011b：触发为高电平和引脚输入高电平时启动定时器
100b：在引脚输入上升沿时启动定时器
101b：在引脚输入上升沿和触发为高电平时启动定时器
110b：在触发为上升沿时启动定时器
111b：在触发为上升沿或下降沿时启动定时器
*/
#define MIO_TIMCFG1_TIMDIS_Msk             ((uint32_t)0x7000)   /* bit mask, 定时器引脚配置
000b：定时器从不停止
001b：在定时器 N-1 停止时停止定时器
010b：定时器产生比较事件时停止定时器
011b：定时器产生比较事件和触发为低时停止定时器
100b：在定时器引脚输入上升沿或者下降沿时停止定时器
101b：触发为高电平，引脚输入上升沿或者下降沿时停止定时器
110b：触发为下降沿时停止定时器
111b：保留
*/
#define MIO_TIMCFG1_TIMDIS_Pos             ((uint32_t)12)   /*bit position, 定时器引脚配置
000b：定时器从不停止
001b：在定时器 N-1 停止时停止定时器
010b：定时器产生比较事件时停止定时器
011b：定时器产生比较事件和触发为低时停止定时器
100b：在定时器引脚输入上升沿或者下降沿时停止定时器
101b：触发为高电平，引脚输入上升沿或者下降沿时停止定时器
110b：触发为下降沿时停止定时器
111b：保留
*/
#define MIO_TIMCFG1_TIMRST_Msk             ((uint32_t)0x70000)   /* bit mask, 定时器复位
000b：定时器永不复位
001b：保留
010b：当定时器引脚等于定时器输出时，定时器复位
011b：当定时器触发等于定时器输出时，定时器复位
100b：当定时器引脚输入上升沿时，定时器复位
101b：保留
110b：当定时器被上升沿触发时，定时器复位
说明：在 8 位计数器模式下，定时器复位只会复位配置波特率的低 8 位。在所有其他模
式下，定时器复位将重置计数器的全部 16 位
*/
#define MIO_TIMCFG1_TIMRST_Pos             ((uint32_t)16)   /*bit position, 定时器复位
000b：定时器永不复位
001b：保留
010b：当定时器引脚等于定时器输出时，定时器复位
011b：当定时器触发等于定时器输出时，定时器复位
100b：当定时器引脚输入上升沿时，定时器复位
101b：保留
110b：当定时器被上升沿触发时，定时器复位
说明：在 8 位计数器模式下，定时器复位只会复位配置波特率的低 8 位。在所有其他模
式下，定时器复位将重置计数器的全部 16 位
*/
#define MIO_TIMCFG1_TIMDEC_Msk             ((uint32_t)0x700000)   /* bit mask, 定时器递减
00b：定时器在MIO时钟上递减计数，移位时钟等于定时器输出
01b：定时器在触发输入(双边沿)上递减计数，移位时钟等于定时器输出
10b：定时器在引脚输入(双边沿)上递减计数，移位时钟等于引脚输入
11b：定时器在触发输入(双边沿)上递减计数，移位时钟等于触发输入
*/
#define MIO_TIMCFG1_TIMDEC_Pos             ((uint32_t)20)   /*bit position, 定时器递减
00b：定时器在MIO时钟上递减计数，移位时钟等于定时器输出
01b：定时器在触发输入(双边沿)上递减计数，移位时钟等于定时器输出
10b：定时器在引脚输入(双边沿)上递减计数，移位时钟等于引脚输入
11b：定时器在触发输入(双边沿)上递减计数，移位时钟等于触发输入
*/
#define MIO_TIMCFG1_TIMOUT_Msk             ((uint32_t)0x3000000)   /* bit mask, 定时器输出
00b：定时器输出在启用时为逻辑 1，不受定时器复位影响
01b：定时器输出在启用时为逻辑 0，不受定时器复位影响
10b：定时器输出在启用和定时器复位时为逻辑 1
11b：定时器输出在启用和定时器复位时为逻辑 0
*/
#define MIO_TIMCFG1_TIMOUT_Pos             ((uint32_t)24)   /*bit position, 定时器输出
00b：定时器输出在启用时为逻辑 1，不受定时器复位影响
01b：定时器输出在启用时为逻辑 0，不受定时器复位影响
10b：定时器输出在启用和定时器复位时为逻辑 1
11b：定时器输出在启用和定时器复位时为逻辑 0
*/

/******************  Bit Definition for Register MIO_TIMCMP0  *********************/
#define MIO_TIMCMP0_CMP_Msk             ((uint32_t)0xffff)   /* bit mask, 定时器比较值
在 双 8 位波特计数器模式下(TMOD = 01b)，低 8 位配置波特率分频器等于
(CMP[7:0] + 1) * 2。高 8 位配置每个字的位数等于 (CMP [15:8] + 1) / 2。
在 双 8 位 PWM 模式下(TMOD = 10b)，低 8 位将输出的高电平周期配置为
(CMP[7:0] + 1)，高 8 位将输出的低电平周期配置为 (CMP[15: 8] + 1)。
在 单 16 位计数器模式下(TMOD = 11b)，比较值可以用来产生波特率分频器（如果移位时钟源是定时器输出）等于 (CMP[15:0] + 1) * 2。
当移位时钟源是一个引脚或触发输入，比较寄存器用于设置每个字的位数等于（CMP[15:0] + 1）/2。
*/
#define MIO_TIMCMP0_CMP_Pos             ((uint32_t)0)   /*bit position, 定时器比较值
在 双 8 位波特计数器模式下(TMOD = 01b)，低 8 位配置波特率分频器等于
(CMP[7:0] + 1) * 2。高 8 位配置每个字的位数等于 (CMP [15:8] + 1) / 2。
在 双 8 位 PWM 模式下(TMOD = 10b)，低 8 位将输出的高电平周期配置为
(CMP[7:0] + 1)，高 8 位将输出的低电平周期配置为 (CMP[15: 8] + 1)。
在 单 16 位计数器模式下(TMOD = 11b)，比较值可以用来产生波特率分频器（如果移位时钟源是定时器输出）等于 (CMP[15:0] + 1) * 2。
当移位时钟源是一个引脚或触发输入，比较寄存器用于设置每个字的位数等于（CMP[15:0] + 1）/2。
*/

/******************  Bit Definition for Register MIO_TIMCMP1  *********************/
#define MIO_TIMCMP1_CMP_Msk             ((uint32_t)0xffff)   /* bit mask, 定时器比较值
在 双 8 位波特计数器模式下(TMOD = 01b)，低 8 位配置波特率分频器等于
(CMP[7:0] + 1) * 2。高 8 位配置每个字的位数等于 (CMP [15:8] + 1) / 2。
在 双 8 位 PWM 模式下(TMOD = 10b)，低 8 位将输出的高电平周期配置为
(CMP[7:0] + 1)，高 8 位将输出的低电平周期配置为 (CMP[15: 8] + 1)。
在 单 16 位计数器模式下(TMOD = 11b)，比较值可以用来产生波特率分频器（如果移位时钟源是定时器输出）等于 (CMP[15:0] + 1) * 2。
当移位时钟源是一个引脚或触发输入，比较寄存器用于设置每个字的位数等于（CMP[15:0] + 1）/2。
*/
#define MIO_TIMCMP1_CMP_Pos             ((uint32_t)0)   /*bit position, 定时器比较值
在 双 8 位波特计数器模式下(TMOD = 01b)，低 8 位配置波特率分频器等于
(CMP[7:0] + 1) * 2。高 8 位配置每个字的位数等于 (CMP [15:8] + 1) / 2。
在 双 8 位 PWM 模式下(TMOD = 10b)，低 8 位将输出的高电平周期配置为
(CMP[7:0] + 1)，高 8 位将输出的低电平周期配置为 (CMP[15: 8] + 1)。
在 单 16 位计数器模式下(TMOD = 11b)，比较值可以用来产生波特率分频器（如果移位时钟源是定时器输出）等于 (CMP[15:0] + 1) * 2。
当移位时钟源是一个引脚或触发输入，比较寄存器用于设置每个字的位数等于（CMP[15:0] + 1）/2。
*/

/******************  Bit Definition for Register MIO_SHIFTBUFNBS0  *********************/
#define MIO_SHIFTBUFNBS0_SHIFTBUFNBS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲半字节字节交换寄存器0*/
#define MIO_SHIFTBUFNBS0_SHIFTBUFNBS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲半字节字节交换寄存器0*/

/******************  Bit Definition for Register MIO_SHIFTBUFNBS1  *********************/
#define MIO_SHIFTBUFNBS1_SHIFTBUFNBS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲半字节字节交换寄存器1*/
#define MIO_SHIFTBUFNBS1_SHIFTBUFNBS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲半字节字节交换寄存器1*/

/******************  Bit Definition for Register MIO_SHIFTBUFHWS0  *********************/
#define MIO_SHIFTBUFHWS0_SHIFTBUFHWS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲半字交换寄存器0*/
#define MIO_SHIFTBUFHWS0_SHIFTBUFHWS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲半字交换寄存器0*/

/******************  Bit Definition for Register MIO_SHIFTBUFHWS1  *********************/
#define MIO_SHIFTBUFHWS1_SHIFTBUFHWS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲半字交换寄存器1*/
#define MIO_SHIFTBUFHWS1_SHIFTBUFHWS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲半字交换寄存器1*/

/******************  Bit Definition for Register MIO_SHIFTBUFNIS0  *********************/
#define MIO_SHIFTBUFNIS0_SHIFTBUFNIS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲半字节交换寄存器0*/
#define MIO_SHIFTBUFNIS0_SHIFTBUFNIS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲半字节交换寄存器0*/

/******************  Bit Definition for Register MIO_SHIFTBUFNIS1  *********************/
#define MIO_SHIFTBUFNIS1_SHIFTBUFNIS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲半字节交换寄存器1*/
#define MIO_SHIFTBUFNIS1_SHIFTBUFNIS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲半字节交换寄存器1*/

/******************  Bit Definition for Register MIO_SHIFTBUFOES0  *********************/
#define MIO_SHIFTBUFOES0_SHIFTBUFOES_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲偶数奇数交换寄存器0*/
#define MIO_SHIFTBUFOES0_SHIFTBUFOES_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲偶数奇数交换寄存器0*/

/******************  Bit Definition for Register MIO_SHIFTBUFOES1  *********************/
#define MIO_SHIFTBUFOES1_SHIFTBUFOES_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲偶数奇数交换寄存器1*/
#define MIO_SHIFTBUFOES1_SHIFTBUFOES_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲偶数奇数交换寄存器1*/

/******************  Bit Definition for Register MIO_SHIFTBUFEOS0  *********************/
#define MIO_SHIFTBUFEOS0_SHIFTBUFEOS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲奇数偶数交换寄存器0*/
#define MIO_SHIFTBUFEOS0_SHIFTBUFEOS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲奇数偶数交换寄存器0*/

/******************  Bit Definition for Register MIO_SHIFTBUFEOS1  *********************/
#define MIO_SHIFTBUFEOS1_SHIFTBUFEOS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲奇数偶数交换寄存器1*/
#define MIO_SHIFTBUFEOS1_SHIFTBUFEOS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲奇数偶数交换寄存器1*/

/******************  Bit Definition for Register MIO_SHIFTBUFHBS0  *********************/
#define MIO_SHIFTBUFHBS0_SHIFTBUFHBS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲半字字节交换寄存器0*/
#define MIO_SHIFTBUFHBS0_SHIFTBUFHBS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲半字字节交换寄存器0*/

/******************  Bit Definition for Register MIO_SHIFTBUFHBS1  *********************/
#define MIO_SHIFTBUFHBS1_SHIFTBUFHBS_Msk             ((uint32_t)0xffffffff)   /* bit mask, 移位器缓冲半字字节交换寄存器1*/
#define MIO_SHIFTBUFHBS1_SHIFTBUFHBS_Pos             ((uint32_t)0)   /*bit position, 移位器缓冲半字字节交换寄存器1*/

/******************************************************************************/
/*                    CROSSLINK                         */
/******************************************************************************/


/******************  Bit Definition for Register CROSS_LINK0_SEL0  *********************/
#define CROSSLINK_CROSS_LINK0_SEL0_CL0_SEL0_Msk             ((uint32_t)0x1f)   /* bit mask, Cross Link 0 Out 0输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL0_CL0_SEL0_Pos             ((uint32_t)0)   /*bit position, Cross Link 0 Out 0输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL0_RESERVED0_Msk             ((uint32_t)0xe0)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL0_RESERVED0_Pos             ((uint32_t)5)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL0_CL0_SEL1_Msk             ((uint32_t)0x1f00)   /* bit mask, Cross Link 0 Out 1输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL0_CL0_SEL1_Pos             ((uint32_t)8)   /*bit position, Cross Link 0 Out 1输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL0_RESERVED1_Msk             ((uint32_t)0xe000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL0_RESERVED1_Pos             ((uint32_t)13)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL0_CL0_SEL2_Msk             ((uint32_t)0x1f0000)   /* bit mask, Cross Link 0 Out 2输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL0_CL0_SEL2_Pos             ((uint32_t)16)   /*bit position, Cross Link 0 Out 2输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL0_RESERVED2_Msk             ((uint32_t)0xe00000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL0_RESERVED2_Pos             ((uint32_t)21)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL0_CL0_SEL3_Msk             ((uint32_t)0x1f000000)   /* bit mask, Cross Link 0 Out 3输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL0_CL0_SEL3_Pos             ((uint32_t)24)   /*bit position, Cross Link 0 Out 3输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL0_RESERVED3_Msk             ((uint32_t)0xe0000000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL0_RESERVED3_Pos             ((uint32_t)29)   /*bit position, */

/******************  Bit Definition for Register CROSS_LINK0_SEL1  *********************/
#define CROSSLINK_CROSS_LINK0_SEL1_CL0_SEL4_Msk             ((uint32_t)0x1f)   /* bit mask, Cross Link 0 Out 4输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL1_CL0_SEL4_Pos             ((uint32_t)0)   /*bit position, Cross Link 0 Out 4输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL1_RESERVED0_Msk             ((uint32_t)0xe0)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL1_RESERVED0_Pos             ((uint32_t)5)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL1_CL0_SEL5_Msk             ((uint32_t)0x1f00)   /* bit mask, Cross Link 0 Out 5输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL1_CL0_SEL5_Pos             ((uint32_t)8)   /*bit position, Cross Link 0 Out 5输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL1_RESERVED1_Msk             ((uint32_t)0xe000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL1_RESERVED1_Pos             ((uint32_t)13)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL1_CL0_SEL6_Msk             ((uint32_t)0x1f0000)   /* bit mask, Cross Link 0 Out 6输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL1_CL0_SEL6_Pos             ((uint32_t)16)   /*bit position, Cross Link 0 Out 6输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL1_RESERVED2_Msk             ((uint32_t)0xe00000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL1_RESERVED2_Pos             ((uint32_t)21)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL1_CL0_SEL7_Msk             ((uint32_t)0x1f000000)   /* bit mask, Cross Link 0 Out 7输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL1_CL0_SEL7_Pos             ((uint32_t)24)   /*bit position, Cross Link 0 Out 7输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL1_RESERVED3_Msk             ((uint32_t)0xe0000000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL1_RESERVED3_Pos             ((uint32_t)29)   /*bit position, */

/******************  Bit Definition for Register CROSS_LINK0_SEL2  *********************/
#define CROSSLINK_CROSS_LINK0_SEL2_CL0_SEL8_Msk             ((uint32_t)0x1f)   /* bit mask, Cross Link 0 Out 8输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL2_CL0_SEL8_Pos             ((uint32_t)0)   /*bit position, Cross Link 0 Out 8输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL2_RESERVED0_Msk             ((uint32_t)0xe0)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL2_RESERVED0_Pos             ((uint32_t)5)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL2_CL0_SEL9_Msk             ((uint32_t)0x1f00)   /* bit mask, Cross Link 0 Out 9输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL2_CL0_SEL9_Pos             ((uint32_t)8)   /*bit position, Cross Link 0 Out 9输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL2_RESERVED1_Msk             ((uint32_t)0xe000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL2_RESERVED1_Pos             ((uint32_t)13)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL2_CL0_SEL10_Msk             ((uint32_t)0x1f0000)   /* bit mask, Cross Link 0 Out 10输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL2_CL0_SEL10_Pos             ((uint32_t)16)   /*bit position, Cross Link 0 Out 10输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL2_RESERVED2_Msk             ((uint32_t)0xe00000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL2_RESERVED2_Pos             ((uint32_t)21)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL2_CL0_SEL11_Msk             ((uint32_t)0x1f000000)   /* bit mask, Cross Link 0 Out 11输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL2_CL0_SEL11_Pos             ((uint32_t)24)   /*bit position, Cross Link 0 Out 11输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL2_RESERVED3_Msk             ((uint32_t)0xe0000000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL2_RESERVED3_Pos             ((uint32_t)29)   /*bit position, */

/******************  Bit Definition for Register CROSS_LINK0_SEL3  *********************/
#define CROSSLINK_CROSS_LINK0_SEL3_CL0_SEL12_Msk             ((uint32_t)0x1f)   /* bit mask, Cross Link 0 Out 12输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL3_CL0_SEL12_Pos             ((uint32_t)0)   /*bit position, Cross Link 0 Out 12输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL3_RESERVED0_Msk             ((uint32_t)0xe0)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL3_RESERVED0_Pos             ((uint32_t)5)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL3_CL0_SEL13_Msk             ((uint32_t)0x1f00)   /* bit mask, Cross Link 0 Out 13输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL3_CL0_SEL13_Pos             ((uint32_t)8)   /*bit position, Cross Link 0 Out 13输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL3_RESERVED1_Msk             ((uint32_t)0xe000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL3_RESERVED1_Pos             ((uint32_t)13)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL3_CL0_SEL14_Msk             ((uint32_t)0x1f0000)   /* bit mask, Cross Link 0 Out 14输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL3_CL0_SEL14_Pos             ((uint32_t)16)   /*bit position, Cross Link 0 Out 14输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL3_RESERVED2_Msk             ((uint32_t)0xe00000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL3_RESERVED2_Pos             ((uint32_t)21)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_SEL3_CL0_SEL15_Msk             ((uint32_t)0x1f000000)   /* bit mask, Cross Link 0 Out 15输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL3_CL0_SEL15_Pos             ((uint32_t)24)   /*bit position, Cross Link 0 Out 15输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL3_RESERVED3_Msk             ((uint32_t)0xe0000000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL3_RESERVED3_Pos             ((uint32_t)29)   /*bit position, */

/******************  Bit Definition for Register CROSS_LINK0_SEL4  *********************/
#define CROSSLINK_CROSS_LINK0_SEL4_CL0_SEL16_Msk             ((uint32_t)0x1f)   /* bit mask, Cross Link 0 Out 16输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL4_CL0_SEL16_Pos             ((uint32_t)0)   /*bit position, Cross Link 0 Out 16输出的MUX输入选择寄存器*/
#define CROSSLINK_CROSS_LINK0_SEL4_RESERVED0_Msk             ((uint32_t)0xffffffe0)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_SEL4_RESERVED0_Pos             ((uint32_t)5)   /*bit position, */

/******************  Bit Definition for Register CROSS_LINK0_CTR0  *********************/
#define CROSSLINK_CROSS_LINK0_CTR0_DEN0_Msk             ((uint32_t)0x1)   /* bit mask, Cross_Link0_OUT0 的 DMA 启用 该位启用相应Cross_Link0_OUT0 输出上的 DMA 功能。启用时，DMA_REQ0 显示值 STS0。禁用时，DMA_REQ0 输出保持低位。限制：IEN0 和 DEN0 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_DEN0_Pos             ((uint32_t)0)   /*bit position, Cross_Link0_OUT0 的 DMA 启用 该位启用相应Cross_Link0_OUT0 输出上的 DMA 功能。启用时，DMA_REQ0 显示值 STS0。禁用时，DMA_REQ0 输出保持低位。限制：IEN0 和 DEN0 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_IEN0_Msk             ((uint32_t)0x2)   /* bit mask, Cross_Link0_OUT0的中断启用 此位启用相应 Cross_Link0_OUT0 输出上的中断功能。当中断启用时，输出 INT_REQ0反映值 STS0。当中断禁用时，INT_REQ0保持低位。通过将 1 写入 STS0 来清除中断请求。限制：IEN0和 DEN0 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_IEN0_Pos             ((uint32_t)1)   /*bit position, Cross_Link0_OUT0的中断启用 此位启用相应 Cross_Link0_OUT0 输出上的中断功能。当中断启用时，输出 INT_REQ0反映值 STS0。当中断禁用时，INT_REQ0保持低位。通过将 1 写入 STS0 来清除中断请求。限制：IEN0和 DEN0 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_EDGE0_Msk             ((uint32_t)0xc)   /* bit mask, Cross_Link0_OUT0 上边沿检测的有效边沿 此字段选择 Cross_Link0_OUT0 上的哪些边沿导致 STS0 断言。*/
#define CROSSLINK_CROSS_LINK0_CTR0_EDGE0_Pos             ((uint32_t)2)   /*bit position, Cross_Link0_OUT0 上边沿检测的有效边沿 此字段选择 Cross_Link0_OUT0 上的哪些边沿导致 STS0 断言。*/
#define CROSSLINK_CROSS_LINK0_CTR0_STS0_Msk             ((uint32_t)0x10)   /* bit mask, Cross_Link0_OUT0 的边沿检测状态,此位反映Cross_Link0_OUT0的边沿检测结果。 当在 Cross_Link0_OUT0 上检测到与 EDGE0 的当前设置一致的边沿时，此字段设置为 1。可以通过向此字段写入 1 来清除此字段。向此字段写入 0 不起作用。 当为Cross_Link0_OUT0 启用中断或 DMA 功能时，当中断或 DMA 请求被断言时，此字段为 1，当中断或 DMA 请求已被清除时，此字段为 0。*/
#define CROSSLINK_CROSS_LINK0_CTR0_STS0_Pos             ((uint32_t)4)   /*bit position, Cross_Link0_OUT0 的边沿检测状态,此位反映Cross_Link0_OUT0的边沿检测结果。 当在 Cross_Link0_OUT0 上检测到与 EDGE0 的当前设置一致的边沿时，此字段设置为 1。可以通过向此字段写入 1 来清除此字段。向此字段写入 0 不起作用。 当为Cross_Link0_OUT0 启用中断或 DMA 功能时，当中断或 DMA 请求被断言时，此字段为 1，当中断或 DMA 请求已被清除时，此字段为 0。*/
#define CROSSLINK_CROSS_LINK0_CTR0_RESERVE0_Msk             ((uint32_t)0xe0)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_CTR0_RESERVE0_Pos             ((uint32_t)5)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_CTR0_DEN1_Msk             ((uint32_t)0x100)   /* bit mask, Cross_Link0_OUT1 的 DMA 启用 该位启用相应Cross_Link0_OUT1 输出上的 DMA 功能。启用时，DMA_REQ1 显示值 STS1。禁用时，DMA_REQ1 输出保持低位。限制：IEN1 和 DEN1 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_DEN1_Pos             ((uint32_t)8)   /*bit position, Cross_Link0_OUT1 的 DMA 启用 该位启用相应Cross_Link0_OUT1 输出上的 DMA 功能。启用时，DMA_REQ1 显示值 STS1。禁用时，DMA_REQ1 输出保持低位。限制：IEN1 和 DEN1 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_IEN1_Msk             ((uint32_t)0x200)   /* bit mask, Cross_Link0_OUT1的中断启用 此位启用相应 Cross_Link0_OUT1 输出上的中断功能。当中断启用时，输出 INT_REQ3反映值 STS1。当中断禁用时，INT_REQ1保持低位。通过将 1 写入 STS1 来清除中断请求。限制：IEN1和 DEN1 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_IEN1_Pos             ((uint32_t)9)   /*bit position, Cross_Link0_OUT1的中断启用 此位启用相应 Cross_Link0_OUT1 输出上的中断功能。当中断启用时，输出 INT_REQ3反映值 STS1。当中断禁用时，INT_REQ1保持低位。通过将 1 写入 STS1 来清除中断请求。限制：IEN1和 DEN1 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_EDGE1_Msk             ((uint32_t)0xc00)   /* bit mask, Cross_Link0_OUT1 上边沿检测的有效边沿 此字段选择 Cross_Link0_OUT1 上的哪些边沿导致 STS1 断言。*/
#define CROSSLINK_CROSS_LINK0_CTR0_EDGE1_Pos             ((uint32_t)10)   /*bit position, Cross_Link0_OUT1 上边沿检测的有效边沿 此字段选择 Cross_Link0_OUT1 上的哪些边沿导致 STS1 断言。*/
#define CROSSLINK_CROSS_LINK0_CTR0_STS1_Msk             ((uint32_t)0x1000)   /* bit mask, Cross_Link0_OUT1 的边沿检测状态,此位反映Cross_Link0_OUT1的边沿检测结果。 当在 Cross_Link0_OUT1 上检测到与 EDGE3 的当前设置一致的边沿时，此字段设置为 1。可以通过向此字段写入 1 来清除此字段。向此字段写入 0 不起作用。 当为Cross_Link0_OUT1 启用中断或 DMA 功能时，当中断或 DMA 请求被断言时，此字段为 1，当中断或 DMA 请求已被清除时，此字段为 0。*/
#define CROSSLINK_CROSS_LINK0_CTR0_STS1_Pos             ((uint32_t)12)   /*bit position, Cross_Link0_OUT1 的边沿检测状态,此位反映Cross_Link0_OUT1的边沿检测结果。 当在 Cross_Link0_OUT1 上检测到与 EDGE3 的当前设置一致的边沿时，此字段设置为 1。可以通过向此字段写入 1 来清除此字段。向此字段写入 0 不起作用。 当为Cross_Link0_OUT1 启用中断或 DMA 功能时，当中断或 DMA 请求被断言时，此字段为 1，当中断或 DMA 请求已被清除时，此字段为 0。*/
#define CROSSLINK_CROSS_LINK0_CTR0_RESERVE1_Msk             ((uint32_t)0xe000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_CTR0_RESERVE1_Pos             ((uint32_t)13)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_CTR0_DEN2_Msk             ((uint32_t)0x10000)   /* bit mask, Cross_Link0_OUT2 的 DMA 启用 该位启用相应Cross_Link0_OUT2 输出上的 DMA 功能。启用时，DMA_REQ2 显示值 STS2。禁用时，DMA_REQ2 输出保持低位。限制：IEN2 和 DEN2 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_DEN2_Pos             ((uint32_t)16)   /*bit position, Cross_Link0_OUT2 的 DMA 启用 该位启用相应Cross_Link0_OUT2 输出上的 DMA 功能。启用时，DMA_REQ2 显示值 STS2。禁用时，DMA_REQ2 输出保持低位。限制：IEN2 和 DEN2 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_IEN2_Msk             ((uint32_t)0x20000)   /* bit mask, Cross_Link0_OUT2的中断启用 此位启用相应 Cross_Link0_OUT2 输出上的中断功能。当中断启用时，输出 INT_REQ2反映值 STS2。当中断禁用时，INT_REQ2保持低位。通过将 1 写入 STS2 来清除中断请求。限制：IEN2和 DEN2 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_IEN2_Pos             ((uint32_t)17)   /*bit position, Cross_Link0_OUT2的中断启用 此位启用相应 Cross_Link0_OUT2 输出上的中断功能。当中断启用时，输出 INT_REQ2反映值 STS2。当中断禁用时，INT_REQ2保持低位。通过将 1 写入 STS2 来清除中断请求。限制：IEN2和 DEN2 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_EDGE2_Msk             ((uint32_t)0xc0000)   /* bit mask, Cross_Link0_OUT2 上边沿检测的有效边沿 此字段选择 Cross_Link0_OUT2 上的哪些边沿导致 STS2 断言。*/
#define CROSSLINK_CROSS_LINK0_CTR0_EDGE2_Pos             ((uint32_t)18)   /*bit position, Cross_Link0_OUT2 上边沿检测的有效边沿 此字段选择 Cross_Link0_OUT2 上的哪些边沿导致 STS2 断言。*/
#define CROSSLINK_CROSS_LINK0_CTR0_STS2_Msk             ((uint32_t)0x100000)   /* bit mask, Cross_Link0_OUT2 的边沿检测状态,此位反映Cross_Link0_OUT2的边沿检测结果。 当在 Cross_Link0_OUT2 上检测到与 EDGE2 的当前设置一致的边沿时，此字段设置为 1。可以通过向此字段写入 1 来清除此字段。向此字段写入 0 不起作用。 当为Cross_Link0_OUT3 启用中断或 DMA 功能时，当中断或 DMA 请求被断言时，此字段为 1，当中断或 DMA 请求已被清除时，此字段为 0。*/
#define CROSSLINK_CROSS_LINK0_CTR0_STS2_Pos             ((uint32_t)20)   /*bit position, Cross_Link0_OUT2 的边沿检测状态,此位反映Cross_Link0_OUT2的边沿检测结果。 当在 Cross_Link0_OUT2 上检测到与 EDGE2 的当前设置一致的边沿时，此字段设置为 1。可以通过向此字段写入 1 来清除此字段。向此字段写入 0 不起作用。 当为Cross_Link0_OUT3 启用中断或 DMA 功能时，当中断或 DMA 请求被断言时，此字段为 1，当中断或 DMA 请求已被清除时，此字段为 0。*/
#define CROSSLINK_CROSS_LINK0_CTR0_RESERVE2_Msk             ((uint32_t)0xe00000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_CTR0_RESERVE2_Pos             ((uint32_t)21)   /*bit position, */
#define CROSSLINK_CROSS_LINK0_CTR0_DEN3_Msk             ((uint32_t)0x1000000)   /* bit mask, Cross_Link0_OUT3 的 DMA 启用 该位启用相应Cross_Link0_OUT3 输出上的 DMA 功能。启用时，DMA_REQ3 显示值 STS3。禁用时，DMA_REQ3 输出保持低位。限制：IEN3 和 DEN3 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_DEN3_Pos             ((uint32_t)24)   /*bit position, Cross_Link0_OUT3 的 DMA 启用 该位启用相应Cross_Link0_OUT3 输出上的 DMA 功能。启用时，DMA_REQ3 显示值 STS3。禁用时，DMA_REQ3 输出保持低位。限制：IEN3 和 DEN3 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_IEN3_Msk             ((uint32_t)0x2000000)   /* bit mask, Cross_Link0_OUT3的中断启用 此位启用相应 Cross_Link0_OUT3 输出上的中断功能。当中断启用时，输出 INT_REQ3反映值 STS3。当中断禁用时，INT_REQ3保持低位。通过将 1 写入 STS3 来清除中断请求。限制：IEN3和 DEN3 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_IEN3_Pos             ((uint32_t)25)   /*bit position, Cross_Link0_OUT3的中断启用 此位启用相应 Cross_Link0_OUT3 输出上的中断功能。当中断启用时，输出 INT_REQ3反映值 STS3。当中断禁用时，INT_REQ3保持低位。通过将 1 写入 STS3 来清除中断请求。限制：IEN3和 DEN3 不应同时设置为 1。*/
#define CROSSLINK_CROSS_LINK0_CTR0_EDGE3_Msk             ((uint32_t)0xc000000)   /* bit mask, Cross_Link0_OUT3 上边沿检测的有效边沿 此字段选择 Cross_Link0_OUT3 上的哪些边沿导致 STS3 断言。*/
#define CROSSLINK_CROSS_LINK0_CTR0_EDGE3_Pos             ((uint32_t)26)   /*bit position, Cross_Link0_OUT3 上边沿检测的有效边沿 此字段选择 Cross_Link0_OUT3 上的哪些边沿导致 STS3 断言。*/
#define CROSSLINK_CROSS_LINK0_CTR0_STS3_Msk             ((uint32_t)0x10000000)   /* bit mask, Cross_Link0_OUT3 的边沿检测状态,此位反映Cross_Link0_OUT3的边沿检测结果。 当在 Cross_Link0_OUT3 上检测到与 EDGE3 的当前设置一致的边沿时，此字段设置为 1。可以通过向此字段写入 1 来清除此字段。向此字段写入 0 不起作用。 当为Cross_Link0_OUT3 启用中断或 DMA 功能时，当中断或 DMA 请求被断言时，此字段为 1，当中断或 DMA 请求已被清除时，此字段为 0。*/
#define CROSSLINK_CROSS_LINK0_CTR0_STS3_Pos             ((uint32_t)28)   /*bit position, Cross_Link0_OUT3 的边沿检测状态,此位反映Cross_Link0_OUT3的边沿检测结果。 当在 Cross_Link0_OUT3 上检测到与 EDGE3 的当前设置一致的边沿时，此字段设置为 1。可以通过向此字段写入 1 来清除此字段。向此字段写入 0 不起作用。 当为Cross_Link0_OUT3 启用中断或 DMA 功能时，当中断或 DMA 请求被断言时，此字段为 1，当中断或 DMA 请求已被清除时，此字段为 0。*/
#define CROSSLINK_CROSS_LINK0_CTR0_RESERVE3_Msk             ((uint32_t)0xe0000000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK0_CTR0_RESERVE3_Pos             ((uint32_t)29)   /*bit position, */

/******************  Bit Definition for Register CROSS_LINK1_SEL0  *********************/
#define CROSSLINK_CROSS_LINK1_SEL0_CL1_SEL0_Msk             ((uint32_t)0x1f)   /* bit mask, 为LU0_A选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL0_CL1_SEL0_Pos             ((uint32_t)0)   /*bit position, 为LU0_A选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL0_RESERVED0_Msk             ((uint32_t)0xe0)   /* bit mask, */
#define CROSSLINK_CROSS_LINK1_SEL0_RESERVED0_Pos             ((uint32_t)5)   /*bit position, */
#define CROSSLINK_CROSS_LINK1_SEL0_CL1_SEL1_Msk             ((uint32_t)0x1f00)   /* bit mask, 为LU0_B选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL0_CL1_SEL1_Pos             ((uint32_t)8)   /*bit position, 为LU0_B选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL0_RESERVED1_Msk             ((uint32_t)0xe000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK1_SEL0_RESERVED1_Pos             ((uint32_t)13)   /*bit position, */
#define CROSSLINK_CROSS_LINK1_SEL0_CL1_SEL2_Msk             ((uint32_t)0x1f0000)   /* bit mask, 为LU0_C选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL0_CL1_SEL2_Pos             ((uint32_t)16)   /*bit position, 为LU0_C选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL0_RESERVED2_Msk             ((uint32_t)0xe00000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK1_SEL0_RESERVED2_Pos             ((uint32_t)21)   /*bit position, */
#define CROSSLINK_CROSS_LINK1_SEL0_CL1_SEL3_Msk             ((uint32_t)0x1f000000)   /* bit mask, 为LU0_D选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL0_CL1_SEL3_Pos             ((uint32_t)24)   /*bit position, 为LU0_D选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL0_RESERVED3_Msk             ((uint32_t)0xe0000000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK1_SEL0_RESERVED3_Pos             ((uint32_t)29)   /*bit position, */

/******************  Bit Definition for Register CROSS_LINK1_SEL1  *********************/
#define CROSSLINK_CROSS_LINK1_SEL1_CL1_SEL4_Msk             ((uint32_t)0x1f)   /* bit mask, 为LU1_A选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL1_CL1_SEL4_Pos             ((uint32_t)0)   /*bit position, 为LU1_A选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL1_RESERVED0_Msk             ((uint32_t)0xe0)   /* bit mask, */
#define CROSSLINK_CROSS_LINK1_SEL1_RESERVED0_Pos             ((uint32_t)5)   /*bit position, */
#define CROSSLINK_CROSS_LINK1_SEL1_CL1_SEL5_Msk             ((uint32_t)0x1f00)   /* bit mask, 为LU1_B选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL1_CL1_SEL5_Pos             ((uint32_t)8)   /*bit position, 为LU1_B选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL1_RESERVED1_Msk             ((uint32_t)0xe000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK1_SEL1_RESERVED1_Pos             ((uint32_t)13)   /*bit position, */
#define CROSSLINK_CROSS_LINK1_SEL1_CL1_SEL6_Msk             ((uint32_t)0x1f0000)   /* bit mask, 为LU1_C选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL1_CL1_SEL6_Pos             ((uint32_t)16)   /*bit position, 为LU1_C选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL1_RESERVED2_Msk             ((uint32_t)0xe00000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK1_SEL1_RESERVED2_Pos             ((uint32_t)21)   /*bit position, */
#define CROSSLINK_CROSS_LINK1_SEL1_CL1_SEL7_Msk             ((uint32_t)0x1f000000)   /* bit mask, 为LU1_D选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL1_CL1_SEL7_Pos             ((uint32_t)24)   /*bit position, 为LU1_D选择输入源*/
#define CROSSLINK_CROSS_LINK1_SEL1_RESERVED3_Msk             ((uint32_t)0xe0000000)   /* bit mask, */
#define CROSSLINK_CROSS_LINK1_SEL1_RESERVED3_Pos             ((uint32_t)29)   /*bit position, */

/******************  Bit Definition for Register LOGIC_UNION_SEL0  *********************/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC0_A_Msk             ((uint32_t)0x3)   /* bit mask, 与组 0，A 输入配置 此 2 位寄存器定义与组 0 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC0_A_Pos             ((uint32_t)0)   /*bit position, 与组 0，A 输入配置 此 2 位寄存器定义与组 0 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC0_B_Msk             ((uint32_t)0xc)   /* bit mask, 与组 0，B 输入配置 此 2 位寄存器定义与组 0 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC0_B_Pos             ((uint32_t)2)   /*bit position, 与组 0，B 输入配置 此 2 位寄存器定义与组 0 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC0_C_Msk             ((uint32_t)0x30)   /* bit mask, 与组 0，C 输入配置 此 2 位寄存器定义与组 0 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC0_C_Pos             ((uint32_t)4)   /*bit position, 与组 0，C 输入配置 此 2 位寄存器定义与组 0 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC0_D_Msk             ((uint32_t)0xc0)   /* bit mask, 与组 0，D 输入配置 此 2 位寄存器定义与组 0 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC0_D_Pos             ((uint32_t)6)   /*bit position, 与组 0，D 输入配置 此 2 位寄存器定义与组 0 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC1_A_Msk             ((uint32_t)0x300)   /* bit mask, 与组 1，A 输入配置 此 2 位寄存器定义与组 1 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC1_A_Pos             ((uint32_t)8)   /*bit position, 与组 1，A 输入配置 此 2 位寄存器定义与组 1 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC1_B_Msk             ((uint32_t)0xc00)   /* bit mask, 与组 1，B 输入配置 此 2 位寄存器定义与组 1 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC1_B_Pos             ((uint32_t)10)   /*bit position, 与组 1，B 输入配置 此 2 位寄存器定义与组 1 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC1_C_Msk             ((uint32_t)0x3000)   /* bit mask, 与组 1，C 输入配置 此 2 位寄存器定义与组 1 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC1_C_Pos             ((uint32_t)12)   /*bit position, 与组 1，C 输入配置 此 2 位寄存器定义与组 1 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC1_D_Msk             ((uint32_t)0xc000)   /* bit mask, 与组 1，D 输入配置 此 2 位寄存器定义与组 1 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC1_D_Pos             ((uint32_t)14)   /*bit position, 与组 1，D 输入配置 此 2 位寄存器定义与组 1 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC2_A_Msk             ((uint32_t)0x30000)   /* bit mask, 与组 2，A 输入配置 此 2 位寄存器定义与组 2 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC2_A_Pos             ((uint32_t)16)   /*bit position, 与组 2，A 输入配置 此 2 位寄存器定义与组 2 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC2_B_Msk             ((uint32_t)0xc0000)   /* bit mask, 与组 2，B 输入配置 此 2 位寄存器定义与组 2 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC2_B_Pos             ((uint32_t)18)   /*bit position, 与组 2，B 输入配置 此 2 位寄存器定义与组 2 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC2_C_Msk             ((uint32_t)0x300000)   /* bit mask, 与组 2，C 输入配置 此 2 位寄存器定义与组 2 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC2_C_Pos             ((uint32_t)20)   /*bit position, 与组 2，C 输入配置 此 2 位寄存器定义与组 2 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC2_D_Msk             ((uint32_t)0xc00000)   /* bit mask, 与组 2，D 输入配置 此 2 位寄存器定义与组 2 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC2_D_Pos             ((uint32_t)22)   /*bit position, 与组 2，D 输入配置 此 2 位寄存器定义与组 2 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC3_A_Msk             ((uint32_t)0x3000000)   /* bit mask, 与组 3，A 输入配置 此 2 位寄存器定义与组 3 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC3_A_Pos             ((uint32_t)24)   /*bit position, 与组 3，A 输入配置 此 2 位寄存器定义与组 3 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC3_B_Msk             ((uint32_t)0xc000000)   /* bit mask, 与组 3，B 输入配置 此 2 位寄存器定义与组 3 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC3_B_Pos             ((uint32_t)26)   /*bit position, 与组 3，B 输入配置 此 2 位寄存器定义与组 3 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC3_C_Msk             ((uint32_t)0x30000000)   /* bit mask, 与组 3，C 输入配置 此 2 位寄存器定义与组 3 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC3_C_Pos             ((uint32_t)28)   /*bit position, 与组 3，C 输入配置 此 2 位寄存器定义与组 3 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC3_D_Msk             ((uint32_t)0xc0000000)   /* bit mask, 与组 3，D 输入配置 此 2 位寄存器定义与组 3 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL0_LUC3_D_Pos             ((uint32_t)30)   /*bit position, 与组 3，D 输入配置 此 2 位寄存器定义与组 3 中选定的输入D 相关的布尔逻辑。*/

/******************  Bit Definition for Register LOGIC_UNION_SEL1  *********************/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC4_A_Msk             ((uint32_t)0x3)   /* bit mask, 与组 4，A 输入配置 此 2 位寄存器定义与组 4 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC4_A_Pos             ((uint32_t)0)   /*bit position, 与组 4，A 输入配置 此 2 位寄存器定义与组 4 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC4_B_Msk             ((uint32_t)0xc)   /* bit mask, 与组 4，B 输入配置 此 2 位寄存器定义与组 4 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC4_B_Pos             ((uint32_t)2)   /*bit position, 与组 4，B 输入配置 此 2 位寄存器定义与组 4 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC4_C_Msk             ((uint32_t)0x30)   /* bit mask, 与组 4，C 输入配置 此 2 位寄存器定义与组 4 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC4_C_Pos             ((uint32_t)4)   /*bit position, 与组 4，C 输入配置 此 2 位寄存器定义与组 4 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC4_D_Msk             ((uint32_t)0xc0)   /* bit mask, 与组 4，D 输入配置 此 2 位寄存器定义与组 4 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC4_D_Pos             ((uint32_t)6)   /*bit position, 与组 4，D 输入配置 此 2 位寄存器定义与组 4 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC5_A_Msk             ((uint32_t)0x300)   /* bit mask, 与组 5，A 输入配置 此 2 位寄存器定义与组 5 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC5_A_Pos             ((uint32_t)8)   /*bit position, 与组 5，A 输入配置 此 2 位寄存器定义与组 5 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC5_B_Msk             ((uint32_t)0xc00)   /* bit mask, 与组 5，B 输入配置 此 2 位寄存器定义与组 5 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC5_B_Pos             ((uint32_t)10)   /*bit position, 与组 5，B 输入配置 此 2 位寄存器定义与组 5 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC5_C_Msk             ((uint32_t)0x3000)   /* bit mask, 与组 5，C 输入配置 此 2 位寄存器定义与组 5 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC5_C_Pos             ((uint32_t)12)   /*bit position, 与组 5，C 输入配置 此 2 位寄存器定义与组 5 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC5_D_Msk             ((uint32_t)0xc000)   /* bit mask, 与组 5，D 输入配置 此 2 位寄存器定义与组 5 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC5_D_Pos             ((uint32_t)14)   /*bit position, 与组 5，D 输入配置 此 2 位寄存器定义与组 5 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC6_A_Msk             ((uint32_t)0x30000)   /* bit mask, 与组 6，A 输入配置 此 2 位寄存器定义与组 6 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC6_A_Pos             ((uint32_t)16)   /*bit position, 与组 6，A 输入配置 此 2 位寄存器定义与组 6 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC6_B_Msk             ((uint32_t)0xc0000)   /* bit mask, 与组 6，B 输入配置 此 2 位寄存器定义与组 6 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC6_B_Pos             ((uint32_t)18)   /*bit position, 与组 6，B 输入配置 此 2 位寄存器定义与组 6 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC6_C_Msk             ((uint32_t)0x300000)   /* bit mask, 与组 6，C 输入配置 此 2 位寄存器定义与组 6 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC6_C_Pos             ((uint32_t)20)   /*bit position, 与组 6，C 输入配置 此 2 位寄存器定义与组 6 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC6_D_Msk             ((uint32_t)0xc00000)   /* bit mask, 与组 6，D 输入配置 此 2 位寄存器定义与组 6 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC6_D_Pos             ((uint32_t)22)   /*bit position, 与组 6，D 输入配置 此 2 位寄存器定义与组 6 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC7_A_Msk             ((uint32_t)0x3000000)   /* bit mask, 与组 7，A 输入配置 此 2 位寄存器定义与组 7 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC7_A_Pos             ((uint32_t)24)   /*bit position, 与组 7，A 输入配置 此 2 位寄存器定义与组 7 中选定的输入A 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC7_B_Msk             ((uint32_t)0xc000000)   /* bit mask, 与组 7，B 输入配置 此 2 位寄存器定义与组 7 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC7_B_Pos             ((uint32_t)26)   /*bit position, 与组 7，B 输入配置 此 2 位寄存器定义与组 7 中选定的输入B 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC7_C_Msk             ((uint32_t)0x30000000)   /* bit mask, 与组 7，C 输入配置 此 2 位寄存器定义与组 7 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC7_C_Pos             ((uint32_t)28)   /*bit position, 与组 7，C 输入配置 此 2 位寄存器定义与组 7 中选定的输入C 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC7_D_Msk             ((uint32_t)0xc0000000)   /* bit mask, 与组 7，D 输入配置 此 2 位寄存器定义与组 7 中选定的输入D 相关的布尔逻辑。*/
#define CROSSLINK_LOGIC_UNION_SEL1_LUC7_D_Pos             ((uint32_t)30)   /*bit position, 与组 7，D 输入配置 此 2 位寄存器定义与组 7 中选定的输入D 相关的布尔逻辑。*/

/******************  Bit Definition for Register SOFT_SYNC  *********************/
#define CROSSLINK_SOFT_SYNC_RESERVE_Msk             ((uint32_t)0x1)   /* bit mask, */
#define CROSSLINK_SOFT_SYNC_RESERVE_Pos             ((uint32_t)0)   /*bit position, */

/******************************************************************************/
/*                    RCC                         */
/******************************************************************************/


/******************  Bit Definition for Register RCC_CR  *********************/
#define RCC_CR_HSION_Msk             ((uint32_t)0x1)   /* bit mask, 内部高速时钟使能 (Internal high-speed clock enable)，当从待机和停止模式返回或用作系统时钟的外部4-16MHz振荡器发生故障时，该位由硬件置’1’ 来启动内部16MHz的RC振荡器。当内部16MHz振荡器被直接或间接地用作或被选择将要作为系统时钟时，该位不能被清零*/
#define RCC_CR_HSION_Pos             ((uint32_t)0)   /*bit position, 内部高速时钟使能 (Internal high-speed clock enable)，当从待机和停止模式返回或用作系统时钟的外部4-16MHz振荡器发生故障时，该位由硬件置’1’ 来启动内部16MHz的RC振荡器。当内部16MHz振荡器被直接或间接地用作或被选择将要作为系统时钟时，该位不能被清零*/

#define RCC_CR_HSITRIM_Msk             ((uint32_t)0xf8)   /* bit mask, 32M OSC频率细调，默认值可被efuse trim*/
#define RCC_CR_HSITRIM_Pos             ((uint32_t)3)   /*bit position, 32M OSC频率细调，默认值可被efuse trim*/
#define RCC_CR_HSICAL_Msk             ((uint32_t)0x1f00)   /* bit mask, 32M OSC频率粗调，默认值可被efuse trim*/
#define RCC_CR_HSICAL_Pos             ((uint32_t)8)   /*bit position, 32M OSC频率粗调，默认值可被efuse trim*/

/******************  Bit Definition for Register RCC_CFGR  *********************/
#define RCC_CFGR_SW_Msk             ((uint32_t)0x3)   /* bit mask, 系统时钟切换 (System clock switch),在从停止模式中返回时，由硬件强制选择HSI作为系统时钟*/
#define RCC_CFGR_SW_Pos             ((uint32_t)0)   /*bit position, 系统时钟切换 (System clock switch),在从停止模式中返回时，由硬件强制选择HSI作为系统时钟*/
#define RCC_CFGR_SWS_Msk             ((uint32_t)0xc)   /* bit mask, 系统时钟切换状态 (System clock switch status) 。由硬件置’1’或清’0’来指示哪一个时钟源被作为系统时钟。*/
#define RCC_CFGR_SWS_Pos             ((uint32_t)2)   /*bit position, 系统时钟切换状态 (System clock switch status) 。由硬件置’1’或清’0’来指示哪一个时钟源被作为系统时钟。*/
#define RCC_CFGR_HPRE_Msk             ((uint32_t)0xf0)   /* bit mask, AHB预分频 (AHB Prescaler),控制AHB时钟的预分频系数*/
#define RCC_CFGR_HPRE_Pos             ((uint32_t)4)   /*bit position, AHB预分频 (AHB Prescaler),控制AHB时钟的预分频系数*/
#define RCC_CFGR_PPRE1_Msk             ((uint32_t)0x700)   /* bit mask, APB1时钟(PCLK1)的预分频系数*/
#define RCC_CFGR_PPRE1_Pos             ((uint32_t)8)   /*bit position, APB1时钟(PCLK1)的预分频系数*/
#define RCC_CFGR_PPRE2_Msk             ((uint32_t)0x3800)   /* bit mask, APB1时钟(PCLK1)的预分频系数*/
#define RCC_CFGR_PPRE2_Pos             ((uint32_t)11)   /*bit position, APB1时钟(PCLK1)的预分频系数*/
#define RCC_CFGR_MIODIV_Msk             ((uint32_t)0x70000)   /* bit mask, MIO时钟分频系数*/
#define RCC_CFGR_MIODIV_Pos             ((uint32_t)16)   /*bit position, MIO时钟分频系数*/
#define RCC_CFGR_MCO_Msk             ((uint32_t)0xf000000)   /* bit mask, 微控制器时钟输出 (Microcontroller clock output)*/
#define RCC_CFGR_MCO_Pos             ((uint32_t)24)   /*bit position, 微控制器时钟输出 (Microcontroller clock output)*/
#define RCC_CFGR_HSIDIV2_Msk             ((uint32_t)0x4000)   /* bit mask, HSI经过二分频再被作为系统时钟的时钟源*/
#define RCC_CFGR_HSIDIV2_Pos             ((uint32_t)14)   /*bit position, HSI经过二分频再被作为系统时钟的时钟源*/

/******************  Bit Definition for Register RCC_CIR  *********************/
#define RCC_CIR_LSIRDYF_Msk             ((uint32_t)0x1)   /* bit mask, LSI就绪中断标志 (LSI ready interrupt flag)*/
#define RCC_CIR_LSIRDYF_Pos             ((uint32_t)0)   /*bit position, LSI就绪中断标志 (LSI ready interrupt flag)*/
#define RCC_CIR_LSIRDYC_Msk             ((uint32_t)0x10000)   /* bit mask, 清除LSI就绪中断 (LSI ready interrupt clear) ，清除LSI就绪中断标志位LSIRDYF*/
#define RCC_CIR_LSIRDYC_Pos             ((uint32_t)16)   /*bit position, 清除LSI就绪中断 (LSI ready interrupt clear) ，清除LSI就绪中断标志位LSIRDYF*/
#define RCC_CIR_LSIRDYIE_Msk             ((uint32_t)0x100)   /* bit mask, LSI就绪中断使能*/
#define RCC_CIR_LSIRDYIE_Pos             ((uint32_t)8)   /*bit position, LSI就绪中断使能*/

/******************  Bit Definition for Register RCC_APB2RSTR  *********************/
#define RCC_APB2RSTR_ADC0RST_Msk             ((uint32_t)0x200)   /* bit mask, ADC1复位 (ADC 1 interface reset)*/
#define RCC_APB2RSTR_ADC0RST_Pos             ((uint32_t)9)   /*bit position, ADC1复位 (ADC 1 interface reset)*/
#define RCC_APB2RSTR_ADC1RST_Msk             ((uint32_t)0x400)   /* bit mask, ADC2复位 (ADC 2 interface reset)*/
#define RCC_APB2RSTR_ADC1RST_Pos             ((uint32_t)10)   /*bit position, ADC2复位 (ADC 2 interface reset)*/
#define RCC_APB2RSTR_TIM1RST_Msk             ((uint32_t)0x800)   /* bit mask, TIM1复位 (timer 1 reset)*/
#define RCC_APB2RSTR_TIM1RST_Pos             ((uint32_t)11)   /*bit position, TIM1复位 (timer 1 reset)*/
#define RCC_APB2RSTR_SPI0RST_Msk             ((uint32_t)0x1000)   /* bit mask, SPI0复位 (SPI 1 reset)*/
#define RCC_APB2RSTR_SPI0RST_Pos             ((uint32_t)12)   /*bit position, SPI0复位 (SPI 1 reset)*/
#define RCC_APB2RSTR_UART0RST_Msk             ((uint32_t)0x4000)   /* bit mask, UART0复位 (UART0 reset)*/
#define RCC_APB2RSTR_UART0RST_Pos             ((uint32_t)14)   /*bit position, UART0复位 (UART0 reset)*/
#define RCC_APB2RSTR_MIORST_Msk             ((uint32_t)0x20000000)   /* bit mask, Multi-IO复位*/
#define RCC_APB2RSTR_MIORST_Pos             ((uint32_t)29)   /*bit position, Multi-IO复位*/
#define RCC_APB2RSTR_CORSSBARRST_Msk             ((uint32_t)0x40000000)   /* bit mask, crossbar复位*/
#define RCC_APB2RSTR_CORSSBARRST_Pos             ((uint32_t)30)   /*bit position, crossbar复位*/
#define RCC_APB2RSTR_CAM0RST_Msk             ((uint32_t)0x80000000)   /* bit mask, 保留*/
#define RCC_APB2RSTR_CAM0RST_Pos             ((uint32_t)31)   /*bit position, 保留*/
#define RCC_APB2RSTR_GPIORST_Msk             ((uint32_t)0x4)   /* bit mask, GPIO复位*/
#define RCC_APB2RSTR_GPIORST_Pos             ((uint32_t)2)   /*bit position, GPIO复位*/
#define RCC_APB2RSTR_AFERST_Msk             ((uint32_t)0x10000)   /* bit mask, AFE复位*/
#define RCC_APB2RSTR_AFERST_Pos             ((uint32_t)16)   /*bit position, AFE复位*/

/******************  Bit Definition for Register RCC_APB1RSTR  *********************/
#define RCC_APB1RSTR_TIM2RST_Msk             ((uint32_t)0x1)   /* bit mask, 定时器2复位 (Timer 2 reset)*/
#define RCC_APB1RSTR_TIM2RST_Pos             ((uint32_t)0)   /*bit position, 定时器2复位 (Timer 2 reset)*/
#define RCC_APB1RSTR_SPI1RST_Msk             ((uint32_t)0x4000)   /* bit mask, SPI1复位*/
#define RCC_APB1RSTR_SPI1RST_Pos             ((uint32_t)14)   /*bit position, SPI1复位*/
#define RCC_APB1RSTR_UART1RST_Msk             ((uint32_t)0x20000)   /* bit mask, UART1复位*/
#define RCC_APB1RSTR_UART1RST_Pos             ((uint32_t)17)   /*bit position, UART1复位*/
#define RCC_APB1RSTR_I2CRST_Msk             ((uint32_t)0x200000)   /* bit mask, I2C复位*/
#define RCC_APB1RSTR_I2CRST_Pos             ((uint32_t)21)   /*bit position, I2C复位*/
#define RCC_APB1RSTR_BKPRST_Msk             ((uint32_t)0x8000000)   /* bit mask, AON接口复位 (Backup interface reset*/
#define RCC_APB1RSTR_BKPRST_Pos             ((uint32_t)27)   /*bit position, AON接口复位 (Backup interface reset*/
#define RCC_APB1RSTR_PWRRST_Msk             ((uint32_t)0x10000000)   /* bit mask, 电源接口复位 (Power interface reset).*/
#define RCC_APB1RSTR_PWRRST_Pos             ((uint32_t)28)   /*bit position, 电源接口复位 (Power interface reset).*/
#define RCC_APB1RSTR_DACRST_Msk             ((uint32_t)0x20000000)   /* bit mask, DAC复位 (AFE interface reset)*/
#define RCC_APB1RSTR_DACRST_Pos             ((uint32_t)29)   /*bit position, DAC复位 (AFE interface reset)*/

/******************  Bit Definition for Register RCC_AHBENR  *********************/
#define RCC_AHBENR_DMA1EN_Msk             ((uint32_t)0x1)   /* bit mask, DMA1时钟使能 (DMA1 clock enable).*/
#define RCC_AHBENR_DMA1EN_Pos             ((uint32_t)0)   /*bit position, DMA1时钟使能 (DMA1 clock enable).*/
#define RCC_AHBENR_SRAMEN_Msk             ((uint32_t)0x4)   /* bit mask, SRAM时钟使能 (SRAM interface clock enable)*/
#define RCC_AHBENR_SRAMEN_Pos             ((uint32_t)2)   /*bit position, SRAM时钟使能 (SRAM interface clock enable)*/
#define RCC_AHBENR_FLITFEN_Msk             ((uint32_t)0x10)   /* bit mask, 闪存接口电路时钟使能 (FLITF clock enable)*/
#define RCC_AHBENR_FLITFEN_Pos             ((uint32_t)4)   /*bit position, 闪存接口电路时钟使能 (FLITF clock enable)*/
#define RCC_AHBENR_CRCEN_Msk             ((uint32_t)0x40)   /* bit mask, CRC时钟使能*/
#define RCC_AHBENR_CRCEN_Pos             ((uint32_t)6)   /*bit position, CRC时钟使能*/
#define RCC_AHBENR_GPIOEN_Msk             ((uint32_t)0x80)   /* bit mask, GPIO时钟使能*/
#define RCC_AHBENR_GPIOEN_Pos             ((uint32_t)7)   /*bit position, GPIO时钟使能*/
#define RCC_AHBENR_MCALEN_Msk             ((uint32_t)0x100)   /* bit mask, MACL时钟使能*/
#define RCC_AHBENR_MCALEN_Pos             ((uint32_t)8)   /*bit position, MACL时钟使能*/
#define RCC_AHBENR_BTIMEN_Msk             ((uint32_t)0x200)   /* bit mask, Btimer时钟使能*/
#define RCC_AHBENR_BTIMEN_Pos             ((uint32_t)9)   /*bit position, Btimer时钟使能*/

/******************  Bit Definition for Register RCC_APB2ENR  *********************/
#define RCC_APB2ENR_ADC0EN_Msk             ((uint32_t)0x200)   /* bit mask, */
#define RCC_APB2ENR_ADC0EN_Pos             ((uint32_t)9)   /*bit position, */
#define RCC_APB2ENR_ADC1EN_Msk             ((uint32_t)0x400)   /* bit mask, */
#define RCC_APB2ENR_ADC1EN_Pos             ((uint32_t)10)   /*bit position, */
#define RCC_APB2ENR_TIM1EN_Msk             ((uint32_t)0x800)   /* bit mask, */
#define RCC_APB2ENR_TIM1EN_Pos             ((uint32_t)11)   /*bit position, */
#define RCC_APB2ENR_SPI0EN_Msk             ((uint32_t)0x1000)   /* bit mask, */
#define RCC_APB2ENR_SPI0EN_Pos             ((uint32_t)12)   /*bit position, */
#define RCC_APB2ENR_UART0EN_Msk             ((uint32_t)0x4000)   /* bit mask, */
#define RCC_APB2ENR_UART0EN_Pos             ((uint32_t)14)   /*bit position, */
#define RCC_APB2ENR_MIOEN_Msk             ((uint32_t)0x20000000)   /* bit mask, */
#define RCC_APB2ENR_MIOEN_Pos             ((uint32_t)29)   /*bit position, */
#define RCC_APB2ENR_CORSSBAREN_Msk             ((uint32_t)0x40000000)   /* bit mask, */
#define RCC_APB2ENR_CORSSBAREN_Pos             ((uint32_t)30)   /*bit position, */
#define RCC_APB2ENR_CAM0EN_Msk             ((uint32_t)0x80000000)   /* bit mask, 保留*/
#define RCC_APB2ENR_CAM0EN_Pos             ((uint32_t)31)   /*bit position, 保留*/
#define RCC_APB2ENR_AFEEN_Msk             ((uint32_t)0x10000)   /* bit mask, */
#define RCC_APB2ENR_AFEEN_Pos             ((uint32_t)16)   /*bit position, */
#define RCC_APB2ENR_PWMEN_Msk             ((uint32_t)0x20000)   /* bit mask, */
#define RCC_APB2ENR_PWMEN_Pos             ((uint32_t)17)   /*bit position, */

/******************  Bit Definition for Register RCC_APB1ENR  *********************/
#define RCC_APB1ENR_TIM2EN_Msk             ((uint32_t)0x1)   /* bit mask, 定时器2时钟使能*/
#define RCC_APB1ENR_TIM2EN_Pos             ((uint32_t)0)   /*bit position, 定时器2时钟使能*/
#define RCC_APB1ENR_SPI1EN_Msk             ((uint32_t)0x4000)   /* bit mask, */
#define RCC_APB1ENR_SPI1EN_Pos             ((uint32_t)14)   /*bit position, */
#define RCC_APB1ENR_UART1EN_Msk             ((uint32_t)0x20000)   /* bit mask, */
#define RCC_APB1ENR_UART1EN_Pos             ((uint32_t)17)   /*bit position, */
#define RCC_APB1ENR_I2CEN_Msk             ((uint32_t)0x200000)   /* bit mask, */
#define RCC_APB1ENR_I2CEN_Pos             ((uint32_t)21)   /*bit position, */
#define RCC_APB1ENR_BKPEN_Msk             ((uint32_t)0x8000000)   /* bit mask, AON接口时钟使能*/
#define RCC_APB1ENR_BKPEN_Pos             ((uint32_t)27)   /*bit position, AON接口时钟使能*/
#define RCC_APB1ENR_PWREN_Msk             ((uint32_t)0x10000000)   /* bit mask, 电源接口*/
#define RCC_APB1ENR_PWREN_Pos             ((uint32_t)28)   /*bit position, 电源接口*/
#define RCC_APB1ENR_LPT1EN_Msk             ((uint32_t)0x40000000)   /* bit mask, */
#define RCC_APB1ENR_LPT1EN_Pos             ((uint32_t)30)   /*bit position, */
#define RCC_APB1ENR_LPT2EN_Msk             ((uint32_t)0x80000000)   /* bit mask, */
#define RCC_APB1ENR_LPT2EN_Pos             ((uint32_t)31)   /*bit position, */
#define RCC_APB1ENR_FLASHEN_Msk             ((uint32_t)0x8000)   /* bit mask, */
#define RCC_APB1ENR_FLASHEN_Pos             ((uint32_t)15)   /*bit position, */
#define RCC_APB1ENR_DACEN_Msk             ((uint32_t)0x20000000)   /* bit mask, */
#define RCC_APB1ENR_DACEN_Pos             ((uint32_t)29)   /*bit position, */

/******************  Bit Definition for Register RCC_BDCR  *********************/
#define RCC_BDCR_LSEON_Msk             ((uint32_t)0x1)   /* bit mask, 外部低速振荡器使能 (External low-speed oscillator enable)*/
#define RCC_BDCR_LSEON_Pos             ((uint32_t)0)   /*bit position, 外部低速振荡器使能 (External low-speed oscillator enable)*/
#define RCC_BDCR_IWDGCLKSEL_Msk             ((uint32_t)0x8)   /* bit mask, iwdg时钟源选择*/
#define RCC_BDCR_IWDGCLKSEL_Pos             ((uint32_t)3)   /*bit position, iwdg时钟源选择*/
#define RCC_BDCR_RTCSEL_Msk             ((uint32_t)0x300)   /* bit mask, RTC时钟源选择 (RTC clock source selection),一旦RTC时钟源被选定，直到下次AON域被复位，它不能再被改变。可通过设置BDRST位来清除*/
#define RCC_BDCR_RTCSEL_Pos             ((uint32_t)8)   /*bit position, RTC时钟源选择 (RTC clock source selection),一旦RTC时钟源被选定，直到下次AON域被复位，它不能再被改变。可通过设置BDRST位来清除*/
#define RCC_BDCR_RTCEN_Msk             ((uint32_t)0x8000)   /* bit mask, RTC时钟使能 (RTC clock enable)*/
#define RCC_BDCR_RTCEN_Pos             ((uint32_t)15)   /*bit position, RTC时钟使能 (RTC clock enable)*/
#define RCC_BDCR_BDRST_Msk             ((uint32_t)0x10000)   /* bit mask, AON域软件复位 (Backup domain software reset)*/
#define RCC_BDCR_BDRST_Pos             ((uint32_t)16)   /*bit position, AON域软件复位 (Backup domain software reset)*/

#define RCC_BDCR_XOSC_MODE_Msk             ((uint32_t)0x60)   /* bit mask, XOSC驱动能力配置*/
#define RCC_BDCR_XOSC_MODE_Pos             ((uint32_t)5)   /*bit position, XOSC驱动能力配置*/
#define RCC_BDCR_LSERDY_Msk             ((uint32_t)0x2)   /* bit mask, XOSC准备就绪*/
#define RCC_BDCR_LSERDY_Pos             ((uint32_t)1)   /*bit position, XOSC准备就绪*/

/******************  Bit Definition for Register RCC_CSR  *********************/
#define RCC_CSR_LSION_Msk             ((uint32_t)0x1)   /* bit mask, LSI开启*/
#define RCC_CSR_LSION_Pos             ((uint32_t)0)   /*bit position, LSI开启*/
#define RCC_CSR_LSIRDY_Msk             ((uint32_t)0x2)   /* bit mask, 内部低速振荡器就绪 (Internal low-speed oscillator ready)*/
#define RCC_CSR_LSIRDY_Pos             ((uint32_t)1)   /*bit position, 内部低速振荡器就绪 (Internal low-speed oscillator ready)*/
#define RCC_CSR_GPIO_RETAIN_Msk             ((uint32_t)0x4)   /* bit mask, 当看门狗或者软件复位发生后，是否保持GPIO的状态.且该位只能被上电复位或者外部管脚复位*/
#define RCC_CSR_GPIO_RETAIN_Pos             ((uint32_t)2)   /*bit position, 当看门狗或者软件复位发生后，是否保持GPIO的状态.且该位只能被上电复位或者外部管脚复位*/
#define RCC_CSR_ANA_RETAIN_Msk             ((uint32_t)0x8)   /* bit mask, 当看门狗或者软件复位发生后，是否保持ADC和AFE的状态.且该位只能被上电复位或者外部管脚复位*/
#define RCC_CSR_ANA_RETAIN_Pos             ((uint32_t)3)   /*bit position, 当看门狗或者软件复位发生后，是否保持ADC和AFE的状态.且该位只能被上电复位或者外部管脚复位*/
#define RCC_CSR_RMVF_Msk             ((uint32_t)0x1000000)   /* bit mask, 清除复位标志 (Remove reset flag) 由软件置’1’来清除复位标志*/
#define RCC_CSR_RMVF_Pos             ((uint32_t)24)   /*bit position, 清除复位标志 (Remove reset flag) 由软件置’1’来清除复位标志*/
#define RCC_CSR_PINRSTF_Msk             ((uint32_t)0x4000000)   /* bit mask, NRST引脚复位标志 (PIN reset flag)，在NRST引脚复位发生时由硬件置’1’；由软件通过写RMVF位清除。*/
#define RCC_CSR_PINRSTF_Pos             ((uint32_t)26)   /*bit position, NRST引脚复位标志 (PIN reset flag)，在NRST引脚复位发生时由硬件置’1’；由软件通过写RMVF位清除。*/
#define RCC_CSR_PORRSTF_Msk             ((uint32_t)0x8000000)   /* bit mask, 上电/掉电复位标志 (POR/PDR reset flag)
在上电/掉电复位发生时由硬件置’1’；由软件通过写RMVF位清除。
*/
#define RCC_CSR_PORRSTF_Pos             ((uint32_t)27)   /*bit position, 上电/掉电复位标志 (POR/PDR reset flag)
在上电/掉电复位发生时由硬件置’1’；由软件通过写RMVF位清除。
*/
#define RCC_CSR_SFTRSTF_Msk             ((uint32_t)0x10000000)   /* bit mask, 软件复位标志 (Software reset flag)
在软件复位发生时由硬件置’1’；由软件通过写RMVF位清除
*/
#define RCC_CSR_SFTRSTF_Pos             ((uint32_t)28)   /*bit position, 软件复位标志 (Software reset flag)
在软件复位发生时由硬件置’1’；由软件通过写RMVF位清除
*/
#define RCC_CSR_IWDGRSTF_Msk             ((uint32_t)0x20000000)   /* bit mask, 独立看门狗复位标志*/
#define RCC_CSR_IWDGRSTF_Pos             ((uint32_t)29)   /*bit position, 独立看门狗复位标志*/
#define RCC_CSR_RESERVED1_Msk             ((uint32_t)0x40000000)   /* bit mask, 保留*/
#define RCC_CSR_RESERVED1_Pos             ((uint32_t)30)   /*bit position, 保留*/
#define RCC_CSR_RESERVED2_Msk             ((uint32_t)0x80000000)   /* bit mask, 保留*/
#define RCC_CSR_RESERVED2_Pos             ((uint32_t)31)   /*bit position, 保留*/
#define RCC_CSR_CROSSBAR_RETAIN_Msk             ((uint32_t)0x10)   /* bit mask, 当看门狗或者软件复位发生后，是否保持ADC和AFE的状态.且该位只能被上电复位或者外部管脚复位*/
#define RCC_CSR_CROSSBAR_RETAIN_Pos             ((uint32_t)4)   /*bit position, 当看门狗或者软件复位发生后，是否保持ADC和AFE的状态.且该位只能被上电复位或者外部管脚复位*/

/******************************************************************************/
/*                    CRC32                        */
/******************************************************************************/


/******************  Bit Definition for Register DR  *********************/
#define CRC32_DR_DR_Msk             ((uint32_t)0xffffffff)   /* bit mask, 数据寄存器位
写入CRC计算器的新数据时，作为输入寄存器读取时返回CRC计算的结果
*/
#define CRC32_DR_DR_Pos             ((uint32_t)0)   /*bit position, 数据寄存器位
写入CRC计算器的新数据时，作为输入寄存器读取时返回CRC计算的结果
*/

/******************  Bit Definition for Register IDR  *********************/
#define CRC32_IDR_IDR_Msk             ((uint32_t)0xff)   /* bit mask, 通用8位数据寄存器位
可用于临时存放1字节的数据。
寄存器CRC_CR的RESET位产生的CRC复位对本寄存器没有影响, 此寄存器不参与CRC计算，可以存放任何数据。
*/
#define CRC32_IDR_IDR_Pos             ((uint32_t)0)   /*bit position, 通用8位数据寄存器位
可用于临时存放1字节的数据。
寄存器CRC_CR的RESET位产生的CRC复位对本寄存器没有影响, 此寄存器不参与CRC计算，可以存放任何数据。
*/

/******************  Bit Definition for Register CR  *********************/
#define CRC32_CR_RESET_Msk             ((uint32_t)0x1)   /* bit mask, RESET位
复位CRC计算单元，设置数据寄存器为0xFFFF FFFF。只能对该位写’1’，它由硬件自动清’0’。
*/
#define CRC32_CR_RESET_Pos             ((uint32_t)0)   /*bit position, RESET位
复位CRC计算单元，设置数据寄存器为0xFFFF FFFF。只能对该位写’1’，它由硬件自动清’0’。
*/

/******************************************************************************/
/*                    MACL                         */
/******************************************************************************/


/******************  Bit Definition for Register A0  *********************/
#define MACL_A0_A0_Msk             ((uint32_t)0xffffffff)   /* bit mask, 操作数a0*/
#define MACL_A0_A0_Pos             ((uint32_t)0)   /*bit position, 操作数a0*/

/******************  Bit Definition for Register A1  *********************/
#define MACL_A1_A1_Msk             ((uint32_t)0xffffffff)   /* bit mask, 操作数a1*/
#define MACL_A1_A1_Pos             ((uint32_t)0)   /*bit position, 操作数a1*/

/******************  Bit Definition for Register B0  *********************/
#define MACL_B0_B0_Msk             ((uint32_t)0xffffffff)   /* bit mask, 操作数b0*/
#define MACL_B0_B0_Pos             ((uint32_t)0)   /*bit position, 操作数b0*/

/******************  Bit Definition for Register B1  *********************/
#define MACL_B1_B1_Msk             ((uint32_t)0xffffffff)   /* bit mask, 操作数b1*/
#define MACL_B1_B1_Pos             ((uint32_t)0)   /*bit position, 操作数b1*/

/******************  Bit Definition for Register CFS  *********************/
#define MACL_CFS_QN_Msk             ((uint32_t)0xff)   /* bit mask, 定点小数位数 ,二进制码表示。
当ADDR[11]Q位为使能为1时，计算公式会进行定点小数换算。根据QN[7:0]是定点小数位数，计算会按该8bit无符号数的值进行移位计算。此时输出的结果有相同的小数定点位置。
*/
#define MACL_CFS_QN_Pos             ((uint32_t)0)   /*bit position, 定点小数位数 ,二进制码表示。
当ADDR[11]Q位为使能为1时，计算公式会进行定点小数换算。根据QN[7:0]是定点小数位数，计算会按该8bit无符号数的值进行移位计算。此时输出的结果有相同的小数定点位置。
*/
#define MACL_CFS_RESERVE0_Msk             ((uint32_t)0xff00)   /* bit mask, 该字段被保留。

该只读字段被保留并且始终具有值 0。
*/
#define MACL_CFS_RESERVE0_Pos             ((uint32_t)8)   /*bit position, 该字段被保留。

该只读字段被保留并且始终具有值 0。
*/
#define MACL_CFS_ACVF_Msk             ((uint32_t)0x10000)   /* bit mask, 加法溢出标志位*/
#define MACL_CFS_ACVF_Pos             ((uint32_t)16)   /*bit position, 加法溢出标志位*/
#define MACL_CFS_DMVF_Msk             ((uint32_t)0x20000)   /* bit mask, 除/乘溢出标志位*/
#define MACL_CFS_DMVF_Pos             ((uint32_t)17)   /*bit position, 除/乘溢出标志位*/
#define MACL_CFS_DZF_Msk             ((uint32_t)0x40000)   /* bit mask, 除以零标志位*/
#define MACL_CFS_DZF_Pos             ((uint32_t)18)   /*bit position, 除以零标志位*/
#define MACL_CFS_DRDYF_Msk             ((uint32_t)0x80000)   /* bit mask, 计算完成标志位*/
#define MACL_CFS_DRDYF_Pos             ((uint32_t)19)   /*bit position, 计算完成标志位*/
#define MACL_CFS_ACVIE_Msk             ((uint32_t)0x100000)   /* bit mask, 加法溢出中断使能。
该控制位用于使能ACVF标志中断。
*/
#define MACL_CFS_ACVIE_Pos             ((uint32_t)20)   /*bit position, 加法溢出中断使能。
该控制位用于使能ACVF标志中断。
*/
#define MACL_CFS_DMVIE_Msk             ((uint32_t)0x200000)   /* bit mask, 除/乘溢出中断使能。
该控制位用于使能DMVF标志中断。
*/
#define MACL_CFS_DMVIE_Pos             ((uint32_t)21)   /*bit position, 除/乘溢出中断使能。
该控制位用于使能DMVF标志中断。
*/
#define MACL_CFS_DZIE_Msk             ((uint32_t)0x400000)   /* bit mask, 除以零中断使能。
该Bit用于配置MACL在检测到除以零计算时的中断。如果设置了CFR[DZE] 同时发生了CFR[DZF]置位，则MACL会对CPU产生中断。
*/
#define MACL_CFS_DZIE_Pos             ((uint32_t)22)   /*bit position, 除以零中断使能。
该Bit用于配置MACL在检测到除以零计算时的中断。如果设置了CFR[DZE] 同时发生了CFR[DZF]置位，则MACL会对CPU产生中断。
*/
#define MACL_CFS_DIRE_Msk             ((uint32_t)0x800000)   /* bit mask, 数据计算完成中断请求使能。 
该Bit用于配置MACL在检测到计算完成时产生中断。如果设置了CFR[DIRE] 同时发生了CFR[DRDYF]置位，则MACL会对CPU产生中断。
*/
#define MACL_CFS_DIRE_Pos             ((uint32_t)23)   /*bit position, 数据计算完成中断请求使能。 
该Bit用于配置MACL在检测到计算完成时产生中断。如果设置了CFR[DIRE] 同时发生了CFR[DRDYF]置位，则MACL会对CPU产生中断。
*/
#define MACL_CFS_DRE_Msk             ((uint32_t)0x1000000)   /* bit mask, DMA 请求使能。 
MACL为DMA提供配置MACL和启动计算的接口。当MACL完成指令的执行时，它将处于IDLE状态(不忙)。可以将其配置为可选的以生成DMA请求，以便用户可以使用DMA获取结果并编写新的计算指令。
*/
#define MACL_CFS_DRE_Pos             ((uint32_t)24)   /*bit position, DMA 请求使能。 
MACL为DMA提供配置MACL和启动计算的接口。当MACL完成指令的执行时，它将处于IDLE状态(不忙)。可以将其配置为可选的以生成DMA请求，以便用户可以使用DMA获取结果并编写新的计算指令。
*/
#define MACL_CFS_RESERVE1_Msk             ((uint32_t)0xe000000)   /* bit mask, 该字段被保留。

该只读字段被保留并且始终具有值 0
*/
#define MACL_CFS_RESERVE1_Pos             ((uint32_t)25)   /*bit position, 该字段被保留。

该只读字段被保留并且始终具有值 0
*/
#define MACL_CFS_MAC_Msk             ((uint32_t)0x10000000)   /* bit mask, 乘法/乘加计算指示。
 当前或最后一次运算是乘加。该只读指示位表示 MACL 执行的当前或最后一次操作是否为乘加。
*/
#define MACL_CFS_MAC_Pos             ((uint32_t)28)   /*bit position, 乘法/乘加计算指示。
 当前或最后一次运算是乘加。该只读指示位表示 MACL 执行的当前或最后一次操作是否为乘加。
*/
#define MACL_CFS_RESERVE2_Msk             ((uint32_t)0x20000000)   /* bit mask, 该字段被保留。

该只读字段被保留并且始终具有值 0
*/
#define MACL_CFS_RESERVE2_Pos             ((uint32_t)29)   /*bit position, 该字段被保留。

该只读字段被保留并且始终具有值 0
*/
#define MACL_CFS_DIV_Msk             ((uint32_t)0x40000000)   /* bit mask, 除法计算指示。
当前或上次操作是除法。该只读指示位表示 MACL执行的当前或最后一次操作是否为除法。
*/
#define MACL_CFS_DIV_Pos             ((uint32_t)30)   /*bit position, 除法计算指示。
当前或上次操作是除法。该只读指示位表示 MACL执行的当前或最后一次操作是否为除法。
*/
#define MACL_CFS_BUSY_Msk             ((uint32_t)0x80000000)   /* bit mask, BUSY
当 MACL执行计算时(主要为除法)，该只读位被置位。当启动操作时，硬件设置该标志。它保持有效状态，直到操作完成并且硬件自动清除指示器。该位可用于轮询 MACL的执行状态。组合的 CFS [BUSY, DIV, MAC] 指示器提供编码模块状态：
• 如果 0b001，则 MACL空闲，最后计算是乘加
• 如果 0b010，则 MACL空闲，最后计算是除法
• 如果 0b101，则 MACL正忙于处理乘加
• 如果 0b110，则 MACL正忙于处理除法

CFS [BUSY, DIV, MAC] 的其余编码被保留。
*/
#define MACL_CFS_BUSY_Pos             ((uint32_t)31)   /*bit position, BUSY
当 MACL执行计算时(主要为除法)，该只读位被置位。当启动操作时，硬件设置该标志。它保持有效状态，直到操作完成并且硬件自动清除指示器。该位可用于轮询 MACL的执行状态。组合的 CFS [BUSY, DIV, MAC] 指示器提供编码模块状态：
• 如果 0b001，则 MACL空闲，最后计算是乘加
• 如果 0b010，则 MACL空闲，最后计算是除法
• 如果 0b101，则 MACL正忙于处理乘加
• 如果 0b110，则 MACL正忙于处理除法

CFS [BUSY, DIV, MAC] 的其余编码被保留。
*/

/******************  Bit Definition for Register CLR  *********************/
#define MACL_CLR_RESERVE0_Msk             ((uint32_t)0xff)   /* bit mask, */
#define MACL_CLR_RESERVE0_Pos             ((uint32_t)0)   /*bit position, */
#define MACL_CLR_CA0_Msk             ((uint32_t)0x100)   /* bit mask, 写1清除a0寄存器*/
#define MACL_CLR_CA0_Pos             ((uint32_t)8)   /*bit position, 写1清除a0寄存器*/
#define MACL_CLR_CA1_Msk             ((uint32_t)0x200)   /* bit mask, 写1清除a1寄存器*/
#define MACL_CLR_CA1_Pos             ((uint32_t)9)   /*bit position, 写1清除a1寄存器*/
#define MACL_CLR_CB0_Msk             ((uint32_t)0x400)   /* bit mask, 写1清除b0寄存器*/
#define MACL_CLR_CB0_Pos             ((uint32_t)10)   /*bit position, 写1清除b0寄存器*/
#define MACL_CLR_CB1_Msk             ((uint32_t)0x800)   /* bit mask, 写1清除b1寄存器*/
#define MACL_CLR_CB1_Pos             ((uint32_t)11)   /*bit position, 写1清除b1寄存器*/
#define MACL_CLR_RESERVE1_Msk             ((uint32_t)0xf000)   /* bit mask, */
#define MACL_CLR_RESERVE1_Pos             ((uint32_t)12)   /*bit position, */
#define MACL_CLR_CACVF_Msk             ((uint32_t)0x10000)   /* bit mask, 写1，清除CFS[16] ACVF*/
#define MACL_CLR_CACVF_Pos             ((uint32_t)16)   /*bit position, 写1，清除CFS[16] ACVF*/
#define MACL_CLR_CDMVF_Msk             ((uint32_t)0x20000)   /* bit mask, 写1，清除CFS[17] DMVF*/
#define MACL_CLR_CDMVF_Pos             ((uint32_t)17)   /*bit position, 写1，清除CFS[17] DMVF*/
#define MACL_CLR_CDZF_Msk             ((uint32_t)0x40000)   /* bit mask, 写1，清除CFS[18] DZF*/
#define MACL_CLR_CDZF_Pos             ((uint32_t)18)   /*bit position, 写1，清除CFS[18] DZF*/
#define MACL_CLR_CDRDYF_Msk             ((uint32_t)0x80000)   /* bit mask, 写1，清除CFS[19] DRDYF*/
#define MACL_CLR_CDRDYF_Pos             ((uint32_t)19)   /*bit position, 写1，清除CFS[19] DRDYF*/
#define MACL_CLR_RESERVE2_Msk             ((uint32_t)0xfff00000)   /* bit mask, */
#define MACL_CLR_RESERVE2_Pos             ((uint32_t)20)   /*bit position, */

/******************************************************************************/
/*                    BTIM                         */
/******************************************************************************/


/******************  Bit Definition for Register MCR  *********************/
#define BTIM_MCR_FRZ_Msk             ((uint32_t)0x1)   /* bit mask, Freeze允许在设备进入待机模式时停止计时器。*/
#define BTIM_MCR_FRZ_Pos             ((uint32_t)0)   /*bit position, Freeze允许在设备进入待机模式时停止计时器。*/
#define BTIM_MCR_MDIS_Msk             ((uint32_t)0x2)   /* bit mask, 模块禁用-（PIT部分）禁用标准计时器。在完成任何其他设置之前，必须启用此字段*/
#define BTIM_MCR_MDIS_Pos             ((uint32_t)1)   /*bit position, 模块禁用-（PIT部分）禁用标准计时器。在完成任何其他设置之前，必须启用此字段*/

/******************  Bit Definition for Register LDVAL_0  *********************/
#define BTIM_LDVAL_0_TSV_Msk             ((uint32_t)0xffff)   /* bit mask, 定时器开始值设置定时器开始值。定时器将倒计时，直到它达到0，然后它将生成一个中断，并再次加载此寄存器值。写入一个新值到此寄存器不会重新启动定时器;相反，该值将在定时器到期后加载。要中止当前周期并使用新值启动定时器周期，必须禁用并再次启用定时器。*/
#define BTIM_LDVAL_0_TSV_Pos             ((uint32_t)0)   /*bit position, 定时器开始值设置定时器开始值。定时器将倒计时，直到它达到0，然后它将生成一个中断，并再次加载此寄存器值。写入一个新值到此寄存器不会重新启动定时器;相反，该值将在定时器到期后加载。要中止当前周期并使用新值启动定时器周期，必须禁用并再次启用定时器。*/

/******************  Bit Definition for Register CVAL_0  *********************/
#define BTIM_CVAL_0_TVL_Msk             ((uint32_t)0xffffffff)   /* bit mask, 当前计时器值表示当前计时器值（如果启用计时器）。
注意：·如果定时器被禁用，请不要使用此字段，因为其值不可靠。
·定时器使用递减计数器。如果设置了MCR[FRZ]，则定时器值将在休眠模式下冻结。*/
#define BTIM_CVAL_0_TVL_Pos             ((uint32_t)0)   /*bit position, 当前计时器值表示当前计时器值（如果启用计时器）。
注意：·如果定时器被禁用，请不要使用此字段，因为其值不可靠。
·定时器使用递减计数器。如果设置了MCR[FRZ]，则定时器值将在休眠模式下冻结。*/

/******************  Bit Definition for Register TCTRL_0  *********************/
#define BTIM_TCTRL_0_TEN_Msk             ((uint32_t)0x1)   /* bit mask, 定时器启用启用或禁用定时器。*/
#define BTIM_TCTRL_0_TEN_Pos             ((uint32_t)0)   /*bit position, 定时器启用启用或禁用定时器。*/
#define BTIM_TCTRL_0_TIE_Msk             ((uint32_t)0x2)   /* bit mask, 当中断挂起或TFLGn[TIF]被设置时，启用中断将立即导致中断事件。为了避免这种情况，必须首先清除相关的TFLGn[TIF]*/
#define BTIM_TCTRL_0_TIE_Pos             ((uint32_t)1)   /*bit position, 当中断挂起或TFLGn[TIF]被设置时，启用中断将立即导致中断事件。为了避免这种情况，必须首先清除相关的TFLGn[TIF]*/
#define BTIM_TCTRL_0_CHN_Msk             ((uint32_t)0x4)   /* bit mask, 链式模式激活时，定时器n-1需要在定时器n递减1之前到期。
计时器0无法链接*/
#define BTIM_TCTRL_0_CHN_Pos             ((uint32_t)2)   /*bit position, 链式模式激活时，定时器n-1需要在定时器n递减1之前到期。
计时器0无法链接*/

/******************  Bit Definition for Register TFLG_0  *********************/
#define BTIM_TFLG_0_TIF_Msk             ((uint32_t)0x1)   /* bit mask, 定时器中断标志在定时器周期结束时置1。向该标志写入1将其清除。写入0无效。如果使能，或者当TCTRLn[TIE] = 1时，TIF会产生中断请求。*/
#define BTIM_TFLG_0_TIF_Pos             ((uint32_t)0)   /*bit position, 定时器中断标志在定时器周期结束时置1。向该标志写入1将其清除。写入0无效。如果使能，或者当TCTRLn[TIE] = 1时，TIF会产生中断请求。*/

/******************  Bit Definition for Register LDVAL_1  *********************/
#define BTIM_LDVAL_1_TSV_Msk             ((uint32_t)0xffff)   /* bit mask, 定时器开始值设置定时器开始值。定时器将倒计时，直到它达到0，然后它将生成一个中断，并再次加载此寄存器值。写入一个新值到此寄存器不会重新启动定时器;相反，该值将在定时器到期后加载。要中止当前周期并使用新值启动定时器周期，必须禁用并再次启用定时器。*/
#define BTIM_LDVAL_1_TSV_Pos             ((uint32_t)0)   /*bit position, 定时器开始值设置定时器开始值。定时器将倒计时，直到它达到0，然后它将生成一个中断，并再次加载此寄存器值。写入一个新值到此寄存器不会重新启动定时器;相反，该值将在定时器到期后加载。要中止当前周期并使用新值启动定时器周期，必须禁用并再次启用定时器。*/

/******************  Bit Definition for Register CVAL_1  *********************/
#define BTIM_CVAL_1_TVL_Msk             ((uint32_t)0xffffffff)   /* bit mask, 当前计时器值表示当前计时器值（如果启用计时器）。
注意：·如果定时器被禁用，请不要使用此字段，因为其值不可靠。
·定时器使用递减计数器。如果设置了MCR[FRZ]，则定时器值将在休眠模式下冻结。*/
#define BTIM_CVAL_1_TVL_Pos             ((uint32_t)0)   /*bit position, 当前计时器值表示当前计时器值（如果启用计时器）。
注意：·如果定时器被禁用，请不要使用此字段，因为其值不可靠。
·定时器使用递减计数器。如果设置了MCR[FRZ]，则定时器值将在休眠模式下冻结。*/

/******************  Bit Definition for Register TCTRL_1  *********************/
#define BTIM_TCTRL_1_TEN_Msk             ((uint32_t)0x1)   /* bit mask, 定时器启用启用或禁用定时器。*/
#define BTIM_TCTRL_1_TEN_Pos             ((uint32_t)0)   /*bit position, 定时器启用启用或禁用定时器。*/
#define BTIM_TCTRL_1_TIE_Msk             ((uint32_t)0x2)   /* bit mask, 当中断挂起或TFLGn[TIF]被设置时，启用中断将立即导致中断事件。为了避免这种情况，必须首先清除相关的TFLGn[TIF]*/
#define BTIM_TCTRL_1_TIE_Pos             ((uint32_t)1)   /*bit position, 当中断挂起或TFLGn[TIF]被设置时，启用中断将立即导致中断事件。为了避免这种情况，必须首先清除相关的TFLGn[TIF]*/
#define BTIM_TCTRL_1_CHN_Msk             ((uint32_t)0x4)   /* bit mask, 链式模式激活时，定时器n-1需要在定时器n递减1之前到期。
计时器0无法链接*/
#define BTIM_TCTRL_1_CHN_Pos             ((uint32_t)2)   /*bit position, 链式模式激活时，定时器n-1需要在定时器n递减1之前到期。
计时器0无法链接*/

/******************  Bit Definition for Register TFLG_1  *********************/
#define BTIM_TFLG_1_TIF_Msk             ((uint32_t)0x1)   /* bit mask, 定时器中断标志在定时器周期结束时置1。向该标志写入1将其清除。写入0无效。如果使能，或者当TCTRLn[TIE] = 1时，TIF会产生中断请求。*/
#define BTIM_TFLG_1_TIF_Pos             ((uint32_t)0)   /*bit position, 定时器中断标志在定时器周期结束时置1。向该标志写入1将其清除。写入0无效。如果使能，或者当TCTRLn[TIE] = 1时，TIF会产生中断请求。*/

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name CR - Control Register */
/*! @{ */
#define DMA_CR_ACTIVE_Msk                         (0x80000000U)
#define DMA_CR_ACTIVE_Pos                        (31U)

#define DMA_CR_EDBG_Msk                         (0x2U)
#define DMA_CR_EDBG_Pos                        (1U)
/*! EDBG - Enable Debug
 *  0b0..When in debug mode, the DMA continues to operate.
 *  0b1..When in debug mode, the DMA stalls the start of a new channel. Executing channels are allowed to complete. Channel execution resumes when the system exits debug mode or the EDBG bit is cleared.
 */
#define DMA_CR_EDBG(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_EDBG_Pos)) & DMA_CR_EDBG_Msk)
#define DMA_CR_ERCA_Msk                         (0x4U)
#define DMA_CR_ERCA_Pos                        (2U)
/*! ERCA - Enable Round Robin Channel Arbitration
 *  0b0..Fixed priority arbitration is used for channel selection .
 *  0b1..Round robin arbitration is used for channel selection .
 */
#define DMA_CR_ERCA(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_ERCA_Pos)) & DMA_CR_ERCA_Msk)
#define DMA_CR_HOE_Msk                          (0x10U)
#define DMA_CR_HOE_Pos                         (4U)
/*! HOE - Halt On Error
 *  0b0..Normal operation
 *  0b1..Any error causes the HALT bit to set. Subsequently, all service requests are ignored until the HALT bit is cleared.
 */
#define DMA_CR_HOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_HOE_Pos)) & DMA_CR_HOE_Msk)
#define DMA_CR_HALT_Msk                         (0x20U)
#define DMA_CR_HALT_Pos                        (5U)
/*! HALT - Halt DMA Operations
 *  0b0..Normal operation
 *  0b1..Stall the start of any new channels. Executing channels are allowed to complete. Channel execution resumes when this bit is cleared.
 */
#define DMA_CR_HALT(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_HALT_Pos)) & DMA_CR_HALT_Msk)
#define DMA_CR_CLM_Msk                          (0x40U)
#define DMA_CR_CLM_Pos                         (6U)
/*! CLM - Continuous Link Mode
 *  0b0..A minor loop channel link made to itself goes through channel arbitration before being activated again.
 *  0b1..A minor loop channel link made to itself does not go through channel arbitration before being activated again. Upon minor loop completion, the channel activates again if that channel has a minor loop channel link enabled and the link channel is itself. This effectively applies the minor loop offsets and restarts the next minor loop.
 */
#define DMA_CR_CLM(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_CLM_Pos)) & DMA_CR_CLM_Msk)
#define DMA_CR_EMLM_Msk                         (0x80U)
#define DMA_CR_EMLM_Pos                        (7U)
/*! EMLM - Enable Minor Loop Mapping
 *  0b0..Disabled. DESn.word2 is defined as a 32-bit NBYTES field.
 *  0b1..Enabled. DESn.word2 is redefined to include individual enable fields, an offset field, and the NBYTES field. The individual enable fields allow the minor loop offset to be applied to the source address, the destination address, or both. The NBYTES field is reduced when either offset is enabled.
 */
#define DMA_CR_EMLM(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_EMLM_Pos)) & DMA_CR_EMLM_Msk)
#define DMA_CR_ECX_Msk                          (0x10000U)
#define DMA_CR_ECX_Pos                         (16U)
/*! ECX - Error Cancel Transfer
 *  0b0..Normal operation
 *  0b1..Cancel the remaining data transfer in the same fashion as the CX bit. Stop the executing channel and force the minor loop to finish. The cancel takes effect after the last write of the current read/write sequence. The ECX bit clears itself after the cancel is honored. In addition to cancelling the transfer, ECX treats the cancel as an error condition, thus updating the Error Status register (DMAx_ES) and generating an optional error interrupt.
 */
#define DMA_CR_ECX(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_ECX_Pos)) & DMA_CR_ECX_Msk)
#define DMA_CR_CX_Msk                           (0x20000U)
#define DMA_CR_CX_Pos                          (17U)
/*! CX - Cancel Transfer
 *  0b0..Normal operation
 *  0b1..Cancel the remaining data transfer. Stop the executing channel and force the minor loop to finish. The cancel takes effect after the last write of the current read/write sequence. The CX bit clears itself after the cancel has been honored. This cancel retires the channel normally as if the minor loop was completed.
 */
#define DMA_CR_CX(x)                             (((uint32_t)(((uint32_t)(x)) << DMA_CR_CX_Pos)) & DMA_CR_CX_Msk)
/*! @} */

/*! @name ES - Error Status Register */
/*! @{ */
#define DMA_ES_DBE_Msk                          (0x1U)
#define DMA_ES_DBE_Pos                         (0U)
/*! DBE - Destination Bus Error
 *  0b0..No destination bus error
 *  0b1..The last recorded error was a bus error on a destination write
 */
#define DMA_ES_DBE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DBE_Pos)) & DMA_ES_DBE_Msk)
#define DMA_ES_SBE_Msk                          (0x2U)
#define DMA_ES_SBE_Pos                         (1U)
/*! SBE - Source Bus Error
 *  0b0..No source bus error
 *  0b1..The last recorded error was a bus error on a source read
 */
#define DMA_ES_SBE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SBE_Pos)) & DMA_ES_SBE_Msk)
#define DMA_ES_SGE_Msk                          (0x4U)
#define DMA_ES_SGE_Pos                         (2U)
/*! SGE - Scatter/Gather Configuration Error
 *  0b0..No scatter/gather configuration error
 *  0b1..The last recorded error was a configuration error detected in the DESn_DLASTSGA field. This field is checked at the beginning of a scatter/gather operation after major loop completion if DESn_CSR[ESG] is enabled. DESn_DLASTSGA is not on a 32 byte boundary.
 */
#define DMA_ES_SGE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SGE_Pos)) & DMA_ES_SGE_Msk)
#define DMA_ES_NCE_Msk                          (0x8U)
#define DMA_ES_NCE_Pos                         (3U)
/*! NCE - NBYTES/CITER Configuration Error
 *  0b0..No NBYTES/CITER configuration error
 *  0b1..The last recorded error was a configuration error detected in the DESn_NBYTES or DESn_CITER fields. DESn_NBYTES is not a multiple of DESn_ATTR[SSIZE] and DESn_ATTR[DSIZE], or DESn_CITER[CITER] is equal to zero, or DESn_CITER[ELINK] is not equal to DESn_BITER[ELINK]
 */
#define DMA_ES_NCE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_NCE_Pos)) & DMA_ES_NCE_Msk)
#define DMA_ES_DOE_Msk                          (0x10U)
#define DMA_ES_DOE_Pos                         (4U)
/*! DOE - Destination Offset Error
 *  0b0..No destination offset configuration error
 *  0b1..The last recorded error was a configuration error detected in the DESn_DOFF field. DESn_DOFF is inconsistent with DESn_ATTR[DSIZE].
 */
#define DMA_ES_DOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DOE_Pos)) & DMA_ES_DOE_Msk)
#define DMA_ES_DAE_Msk                          (0x20U)
#define DMA_ES_DAE_Pos                         (5U)
/*! DAE - Destination Address Error
 *  0b0..No destination address configuration error
 *  0b1..The last recorded error was a configuration error detected in the DESn_DADDR field. DESn_DADDR is inconsistent with DESn_ATTR[DSIZE].
 */
#define DMA_ES_DAE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DAE_Pos)) & DMA_ES_DAE_Msk)
#define DMA_ES_SOE_Msk                          (0x40U)
#define DMA_ES_SOE_Pos                         (6U)
/*! SOE - Source Offset Error
 *  0b0..No source offset configuration error
 *  0b1..The last recorded error was a configuration error detected in the DESn_SOFF field. DESn_SOFF is inconsistent with DESn_ATTR[SSIZE].
 */
#define DMA_ES_SOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SOE_Pos)) & DMA_ES_SOE_Msk)
#define DMA_ES_SAE_Msk                          (0x80U)
#define DMA_ES_SAE_Pos                         (7U)
/*! SAE - Source Address Error
 *  0b0..No source address configuration error.
 *  0b1..The last recorded error was a configuration error detected in the DESn_SADDR field. DESn_SADDR is inconsistent with DESn_ATTR[SSIZE].
 */
#define DMA_ES_SAE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SAE_Pos)) & DMA_ES_SAE_Msk)
#define DMA_ES_ERRCHN_Msk                       (0x300U)
#define DMA_ES_ERRCHN_Pos                      (8U)
#define DMA_ES_ERRCHN(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ES_ERRCHN_Pos)) & DMA_ES_ERRCHN_Msk)
#define DMA_ES_CPE_Msk                          (0x4000U)
#define DMA_ES_CPE_Pos                         (14U)
/*! CPE - Channel Priority Error
 *  0b0..No channel priority error
 *  0b1..The last recorded error was a configuration error in the channel priorities . Channel priorities are not unique.
 */
#define DMA_ES_CPE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_CPE_Pos)) & DMA_ES_CPE_Msk)
#define DMA_ES_ECX_Msk                          (0x10000U)
#define DMA_ES_ECX_Pos                         (16U)
/*! ECX - Transfer Canceled
 *  0b0..No canceled transfers
 *  0b1..The last recorded entry was a canceled transfer by the error cancel transfer input
 */
#define DMA_ES_ECX(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_ECX_Pos)) & DMA_ES_ECX_Msk)
#define DMA_ES_VLD_Msk                          (0x80000000U)
#define DMA_ES_VLD_Pos                         (31U)
/*! VLD
 *  0b0..No ERR bits are set
 *  0b1..At least one ERR bit is set indicating a valid error exists that has not been cleared
 */
#define DMA_ES_VLD(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_VLD_Pos)) & DMA_ES_VLD_Msk)
/*! @} */

/*! @name ERQ - Enable Request Register */
/*! @{ */
#define DMA_ERQ_ERQ0_Msk                        (0x1U)
#define DMA_ERQ_ERQ0_Pos                       (0U)
/*! ERQ0 - Enable DMA Request 0
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ0_Pos)) & DMA_ERQ_ERQ0_Msk)
#define DMA_ERQ_ERQ1_Msk                        (0x2U)
#define DMA_ERQ_ERQ1_Pos                       (1U)
/*! ERQ1 - Enable DMA Request 1
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ1_Pos)) & DMA_ERQ_ERQ1_Msk)
#define DMA_ERQ_ERQ2_Msk                        (0x4U)
#define DMA_ERQ_ERQ2_Pos                       (2U)
/*! ERQ2 - Enable DMA Request 2
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ2_Pos)) & DMA_ERQ_ERQ2_Msk)
#define DMA_ERQ_ERQ3_Msk                        (0x8U)
#define DMA_ERQ_ERQ3_Pos                       (3U)
/*! ERQ3 - Enable DMA Request 3
 *  0b0..The DMA request signal for the corresponding channel is disabled
 *  0b1..The DMA request signal for the corresponding channel is enabled
 */
#define DMA_ERQ_ERQ3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ3_Pos)) & DMA_ERQ_ERQ3_Msk)
/*! @} */

/*! @name EEI - Enable Error Interrupt Register */
/*! @{ */
#define DMA_EEI_EEI0_Msk                        (0x1U)
#define DMA_EEI_EEI0_Pos                       (0U)
/*! EEI0 - Enable Error Interrupt 0
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI0_Pos)) & DMA_EEI_EEI0_Msk)
#define DMA_EEI_EEI1_Msk                        (0x2U)
#define DMA_EEI_EEI1_Pos                       (1U)
/*! EEI1 - Enable Error Interrupt 1
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI1_Pos)) & DMA_EEI_EEI1_Msk)
#define DMA_EEI_EEI2_Msk                        (0x4U)
#define DMA_EEI_EEI2_Pos                       (2U)
/*! EEI2 - Enable Error Interrupt 2
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI2_Pos)) & DMA_EEI_EEI2_Msk)
#define DMA_EEI_EEI3_Msk                        (0x8U)
#define DMA_EEI_EEI3_Pos                       (3U)
/*! EEI3 - Enable Error Interrupt 3
 *  0b0..The error signal for corresponding channel does not generate an error interrupt
 *  0b1..The assertion of the error signal for corresponding channel generates an error interrupt request
 */
#define DMA_EEI_EEI3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI3_Pos)) & DMA_EEI_EEI3_Msk)
/*! @} */

/*! @name CEEI - Clear Enable Error Interrupt Register */
/*! @{ */
#define DMA_CEEI_CEEI_Msk                       (0x3U)
#define DMA_CEEI_CEEI_Pos                      (0U)
#define DMA_CEEI_CEEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_CEEI_Pos)) & DMA_CEEI_CEEI_Msk)
#define DMA_CEEI_CAEE_Msk                       (0x40U)
#define DMA_CEEI_CAEE_Pos                      (6U)
/*! CAEE - Clear All Enable Error Interrupts
 *  0b0..Clear only the EEI bit specified in the CEEI field
 *  0b1..Clear all bits in EEI
 */
#define DMA_CEEI_CAEE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_CAEE_Pos)) & DMA_CEEI_CAEE_Msk)
#define DMA_CEEI_NOP_Msk                        (0x80U)
#define DMA_CEEI_NOP_Pos                       (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CEEI_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_NOP_Pos)) & DMA_CEEI_NOP_Msk)
/*! @} */

/*! @name SEEI - Set Enable Error Interrupt Register */
/*! @{ */
#define DMA_SEEI_SEEI_Msk                       (0x3U)
#define DMA_SEEI_SEEI_Pos                      (0U)
#define DMA_SEEI_SEEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_SEEI_Pos)) & DMA_SEEI_SEEI_Msk)
#define DMA_SEEI_SAEE_Msk                       (0x40U)
#define DMA_SEEI_SAEE_Pos                      (6U)
/*! SAEE - Sets All Enable Error Interrupts
 *  0b0..Set only the EEI bit specified in the SEEI field.
 *  0b1..Sets all bits in EEI
 */
#define DMA_SEEI_SAEE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_SAEE_Pos)) & DMA_SEEI_SAEE_Msk)
#define DMA_SEEI_NOP_Msk                        (0x80U)
#define DMA_SEEI_NOP_Pos                       (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_SEEI_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_NOP_Pos)) & DMA_SEEI_NOP_Msk)
/*! @} */

/*! @name CERQ - Clear Enable Request Register */
/*! @{ */
#define DMA_CERQ_CERQ_Msk                       (0x3U)
#define DMA_CERQ_CERQ_Pos                      (0U)
#define DMA_CERQ_CERQ(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_CERQ_Pos)) & DMA_CERQ_CERQ_Msk)
#define DMA_CERQ_CAER_Msk                       (0x40U)
#define DMA_CERQ_CAER_Pos                      (6U)
/*! CAER - Clear All Enable Requests
 *  0b0..Clear only the ERQ bit specified in the CERQ field
 *  0b1..Clear all bits in ERQ
 */
#define DMA_CERQ_CAER(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_CAER_Pos)) & DMA_CERQ_CAER_Msk)
#define DMA_CERQ_NOP_Msk                        (0x80U)
#define DMA_CERQ_NOP_Pos                       (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CERQ_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_NOP_Pos)) & DMA_CERQ_NOP_Msk)
/*! @} */

/*! @name SERQ - Set Enable Request Register */
/*! @{ */
#define DMA_SERQ_SERQ_Msk                       (0x3U)
#define DMA_SERQ_SERQ_Pos                      (0U)
#define DMA_SERQ_SERQ(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_SERQ_Pos)) & DMA_SERQ_SERQ_Msk)
#define DMA_SERQ_SAER_Msk                       (0x40U)
#define DMA_SERQ_SAER_Pos                      (6U)
/*! SAER - Set All Enable Requests
 *  0b0..Set only the ERQ bit specified in the SERQ field
 *  0b1..Set all bits in ERQ
 */
#define DMA_SERQ_SAER(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_SAER_Pos)) & DMA_SERQ_SAER_Msk)
#define DMA_SERQ_NOP_Msk                        (0x80U)
#define DMA_SERQ_NOP_Pos                       (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_SERQ_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_NOP_Pos)) & DMA_SERQ_NOP_Msk)
/*! @} */

/*! @name CDNE - Clear DONE Status Bit Register */
/*! @{ */
#define DMA_CDNE_CDNE_Msk                       (0x3U)
#define DMA_CDNE_CDNE_Pos                      (0U)
#define DMA_CDNE_CDNE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_CDNE_Pos)) & DMA_CDNE_CDNE_Msk)
#define DMA_CDNE_CADN_Msk                       (0x40U)
#define DMA_CDNE_CADN_Pos                      (6U)
/*! CADN - Clears All DONE Bits
 *  0b0..Clears only the DESn_CSR[DONE] bit specified in the CDNE field
 *  0b1..Clears all bits in DESn_CSR[DONE]
 */
#define DMA_CDNE_CADN(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_CADN_Pos)) & DMA_CDNE_CADN_Msk)
#define DMA_CDNE_NOP_Msk                        (0x80U)
#define DMA_CDNE_NOP_Pos                       (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CDNE_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_NOP_Pos)) & DMA_CDNE_NOP_Msk)
/*! @} */

/*! @name SSRT - Set START Bit Register */
/*! @{ */
#define DMA_SSRT_SSRT_Msk                       (0x3U)
#define DMA_SSRT_SSRT_Pos                      (0U)
#define DMA_SSRT_SSRT(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_SSRT_Pos)) & DMA_SSRT_SSRT_Msk)
#define DMA_SSRT_SAST_Msk                       (0x40U)
#define DMA_SSRT_SAST_Pos                      (6U)
/*! SAST - Set All START Bits (activates all channels)
 *  0b0..Set only the DESn_CSR[START] bit specified in the SSRT field
 *  0b1..Set all bits in DESn_CSR[START]
 */
#define DMA_SSRT_SAST(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_SAST_Pos)) & DMA_SSRT_SAST_Msk)
#define DMA_SSRT_NOP_Msk                        (0x80U)
#define DMA_SSRT_NOP_Pos                       (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_SSRT_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_NOP_Pos)) & DMA_SSRT_NOP_Msk)
/*! @} */

/*! @name CERR - Clear Error Register */
/*! @{ */
#define DMA_CERR_CERR_Msk                       (0x3U)
#define DMA_CERR_CERR_Pos                      (0U)
#define DMA_CERR_CERR(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERR_CERR_Pos)) & DMA_CERR_CERR_Msk)
#define DMA_CERR_CAEI_Msk                       (0x40U)
#define DMA_CERR_CAEI_Pos                      (6U)
/*! CAEI - Clear All Error Indicators
 *  0b0..Clear only the ERR bit specified in the CERR field
 *  0b1..Clear all bits in ERR
 */
#define DMA_CERR_CAEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERR_CAEI_Pos)) & DMA_CERR_CAEI_Msk)
#define DMA_CERR_NOP_Msk                        (0x80U)
#define DMA_CERR_NOP_Pos                       (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CERR_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CERR_NOP_Pos)) & DMA_CERR_NOP_Msk)
/*! @} */

/*! @name CINT - Clear Interrupt Request Register */
/*! @{ */
#define DMA_CINT_CINT_Msk                       (0x3U)
#define DMA_CINT_CINT_Pos                      (0U)
#define DMA_CINT_CINT(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CINT_CINT_Pos)) & DMA_CINT_CINT_Msk)
#define DMA_CINT_CAIR_Msk                       (0x40U)
#define DMA_CINT_CAIR_Pos                      (6U)
/*! CAIR - Clear All Interrupt Requests
 *  0b0..Clear only the INT bit specified in the CINT field
 *  0b1..Clear all bits in INT
 */
#define DMA_CINT_CAIR(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CINT_CAIR_Pos)) & DMA_CINT_CAIR_Msk)
#define DMA_CINT_NOP_Msk                        (0x80U)
#define DMA_CINT_NOP_Pos                       (7U)
/*! NOP - No Op enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other bits in this register
 */
#define DMA_CINT_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CINT_NOP_Pos)) & DMA_CINT_NOP_Msk)
/*! @} */

/*! @name INT - Interrupt Request Register */
/*! @{ */
#define DMA_INT_INT0_Msk                        (0x1U)
#define DMA_INT_INT0_Pos                       (0U)
/*! INT0 - Interrupt Request 0
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT0_Pos)) & DMA_INT_INT0_Msk)
#define DMA_INT_INT1_Msk                        (0x2U)
#define DMA_INT_INT1_Pos                       (1U)
/*! INT1 - Interrupt Request 1
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT1_Pos)) & DMA_INT_INT1_Msk)
#define DMA_INT_INT2_Msk                        (0x4U)
#define DMA_INT_INT2_Pos                       (2U)
/*! INT2 - Interrupt Request 2
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT2_Pos)) & DMA_INT_INT2_Msk)
#define DMA_INT_INT3_Msk                        (0x8U)
#define DMA_INT_INT3_Pos                       (3U)
/*! INT3 - Interrupt Request 3
 *  0b0..The interrupt request for corresponding channel is cleared
 *  0b1..The interrupt request for corresponding channel is active
 */
#define DMA_INT_INT3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT3_Pos)) & DMA_INT_INT3_Msk)
/*! @} */

/*! @name ERR - Error Register */
/*! @{ */
#define DMA_ERR_ERR0_Msk                        (0x1U)
#define DMA_ERR_ERR0_Pos                       (0U)
/*! ERR0 - Error In Channel 0
 *  0b0..An error in the corresponding channel has not occurred
 *  0b1..An error in the corresponding channel has occurred
 */
#define DMA_ERR_ERR0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR0_Pos)) & DMA_ERR_ERR0_Msk)
#define DMA_ERR_ERR1_Msk                        (0x2U)
#define DMA_ERR_ERR1_Pos                       (1U)
/*! ERR1 - Error In Channel 1
 *  0b0..An error in the corresponding channel has not occurred
 *  0b1..An error in the corresponding channel has occurred
 */
#define DMA_ERR_ERR1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR1_Pos)) & DMA_ERR_ERR1_Msk)
#define DMA_ERR_ERR2_Msk                        (0x4U)
#define DMA_ERR_ERR2_Pos                       (2U)
/*! ERR2 - Error In Channel 2
 *  0b0..An error in the corresponding channel has not occurred
 *  0b1..An error in the corresponding channel has occurred
 */
#define DMA_ERR_ERR2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR2_Pos)) & DMA_ERR_ERR2_Msk)
#define DMA_ERR_ERR3_Msk                        (0x8U)
#define DMA_ERR_ERR3_Pos                       (3U)
/*! ERR3 - Error In Channel 3
 *  0b0..An error in the corresponding channel has not occurred
 *  0b1..An error in the corresponding channel has occurred
 */
#define DMA_ERR_ERR3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR3_Pos)) & DMA_ERR_ERR3_Msk)
/*! @} */

/*! @name HRS - Hardware Request Status Register */
/*! @{ */
#define DMA_HRS_HRS0_Msk                        (0x1U)
#define DMA_HRS_HRS0_Pos                       (0U)
/*! HRS0 - Hardware Request Status Channel 0
 *  0b0..A hardware service request for channel 0 is not present
 *  0b1..A hardware service request for channel 0 is present
 */
#define DMA_HRS_HRS0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS0_Pos)) & DMA_HRS_HRS0_Msk)
#define DMA_HRS_HRS1_Msk                        (0x2U)
#define DMA_HRS_HRS1_Pos                       (1U)
/*! HRS1 - Hardware Request Status Channel 1
 *  0b0..A hardware service request for channel 1 is not present
 *  0b1..A hardware service request for channel 1 is present
 */
#define DMA_HRS_HRS1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS1_Pos)) & DMA_HRS_HRS1_Msk)
#define DMA_HRS_HRS2_Msk                        (0x4U)
#define DMA_HRS_HRS2_Pos                       (2U)
/*! HRS2 - Hardware Request Status Channel 2
 *  0b0..A hardware service request for channel 2 is not present
 *  0b1..A hardware service request for channel 2 is present
 */
#define DMA_HRS_HRS2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS2_Pos)) & DMA_HRS_HRS2_Msk)
#define DMA_HRS_HRS3_Msk                        (0x8U)
#define DMA_HRS_HRS3_Pos                       (3U)
/*! HRS3 - Hardware Request Status Channel 3
 *  0b0..A hardware service request for channel 3 is not present
 *  0b1..A hardware service request for channel 3 is present
 */
#define DMA_HRS_HRS3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS3_Pos)) & DMA_HRS_HRS3_Msk)
/*! @} */

/*! @name EARS - Enable Asynchronous Request in Stop Register */
/*! @{ */
#define DMA_EARS_EDREQ_0_Msk                    (0x1U)
#define DMA_EARS_EDREQ_0_Pos                   (0U)
/*! EDREQ_0 - Enable asynchronous DMA request in stop for channel 0.
 *  0b0..Disable asynchronous DMA request for channel 0.
 *  0b1..Enable asynchronous DMA request for channel 0.
 */
#define DMA_EARS_EDREQ_0(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_0_Pos)) & DMA_EARS_EDREQ_0_Msk)
#define DMA_EARS_EDREQ_1_Msk                    (0x2U)
#define DMA_EARS_EDREQ_1_Pos                   (1U)
/*! EDREQ_1 - Enable asynchronous DMA request in stop for channel 1.
 *  0b0..Disable asynchronous DMA request for channel 1
 *  0b1..Enable asynchronous DMA request for channel 1.
 */
#define DMA_EARS_EDREQ_1(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_1_Pos)) & DMA_EARS_EDREQ_1_Msk)
#define DMA_EARS_EDREQ_2_Msk                    (0x4U)
#define DMA_EARS_EDREQ_2_Pos                   (2U)
/*! EDREQ_2 - Enable asynchronous DMA request in stop for channel 2.
 *  0b0..Disable asynchronous DMA request for channel 2.
 *  0b1..Enable asynchronous DMA request for channel 2.
 */
#define DMA_EARS_EDREQ_2(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_2_Pos)) & DMA_EARS_EDREQ_2_Msk)
#define DMA_EARS_EDREQ_3_Msk                    (0x8U)
#define DMA_EARS_EDREQ_3_Pos                   (3U)
/*! EDREQ_3 - Enable asynchronous DMA request in stop for channel 3.
 *  0b0..Disable asynchronous DMA request for channel 3.
 *  0b1..Enable asynchronous DMA request for channel 3.
 */
#define DMA_EARS_EDREQ_3(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_3_Pos)) & DMA_EARS_EDREQ_3_Msk)
/*! @} */

/*! @name DCHPRI3 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI3_CHPRI_Msk                   (0x3U)
#define DMA_DCHPRI3_CHPRI_Pos                  (0U)
#define DMA_DCHPRI3_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_CHPRI_Pos)) & DMA_DCHPRI3_CHPRI_Msk)
#define DMA_DCHPRI3_DPA_Msk                     (0x40U)
#define DMA_DCHPRI3_DPA_Pos                    (6U)
/*! DPA - Disable Preempt Ability
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI3_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_DPA_Pos)) & DMA_DCHPRI3_DPA_Msk)
#define DMA_DCHPRI3_ECP_Msk                     (0x80U)
#define DMA_DCHPRI3_ECP_Pos                    (7U)
/*! ECP - Enable Channel Preemption
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI3_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_ECP_Pos)) & DMA_DCHPRI3_ECP_Msk)
/*! @} */

/*! @name DCHPRI2 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI2_CHPRI_Msk                   (0x3U)
#define DMA_DCHPRI2_CHPRI_Pos                  (0U)
#define DMA_DCHPRI2_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_CHPRI_Pos)) & DMA_DCHPRI2_CHPRI_Msk)
#define DMA_DCHPRI2_DPA_Msk                     (0x40U)
#define DMA_DCHPRI2_DPA_Pos                    (6U)
/*! DPA - Disable Preempt Ability
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI2_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_DPA_Pos)) & DMA_DCHPRI2_DPA_Msk)
#define DMA_DCHPRI2_ECP_Msk                     (0x80U)
#define DMA_DCHPRI2_ECP_Pos                    (7U)
/*! ECP - Enable Channel Preemption
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI2_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_ECP_Pos)) & DMA_DCHPRI2_ECP_Msk)
/*! @} */

/*! @name DCHPRI1 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI1_CHPRI_Msk                   (0x3U)
#define DMA_DCHPRI1_CHPRI_Pos                  (0U)
#define DMA_DCHPRI1_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_CHPRI_Pos)) & DMA_DCHPRI1_CHPRI_Msk)
#define DMA_DCHPRI1_DPA_Msk                     (0x40U)
#define DMA_DCHPRI1_DPA_Pos                    (6U)
/*! DPA - Disable Preempt Ability
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI1_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_DPA_Pos)) & DMA_DCHPRI1_DPA_Msk)
#define DMA_DCHPRI1_ECP_Msk                     (0x80U)
#define DMA_DCHPRI1_ECP_Pos                    (7U)
/*! ECP - Enable Channel Preemption
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI1_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_ECP_Pos)) & DMA_DCHPRI1_ECP_Msk)
/*! @} */

/*! @name DCHPRI0 - Channel n Priority Register */
/*! @{ */
#define DMA_DCHPRI0_CHPRI_Msk                   (0x3U)
#define DMA_DCHPRI0_CHPRI_Pos                  (0U)
#define DMA_DCHPRI0_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_CHPRI_Pos)) & DMA_DCHPRI0_CHPRI_Msk)
#define DMA_DCHPRI0_DPA_Msk                     (0x40U)
#define DMA_DCHPRI0_DPA_Pos                    (6U)
/*! DPA - Disable Preempt Ability
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI0_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_DPA_Pos)) & DMA_DCHPRI0_DPA_Msk)
#define DMA_DCHPRI0_ECP_Msk                     (0x80U)
#define DMA_DCHPRI0_ECP_Pos                    (7U)
/*! ECP - Enable Channel Preemption
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI0_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_ECP_Pos)) & DMA_DCHPRI0_ECP_Msk)
/*! @} */

/*! @name SADDR - DES Source Address */
/*! @{ */
#define DMA_SADDR_SADDR_Msk                     (0xFFFFFFFFU)
#define DMA_SADDR_SADDR_Pos                    (0U)
#define DMA_SADDR_SADDR(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_SADDR_SADDR_Pos)) & DMA_SADDR_SADDR_Msk)
/*! @} */

/* The count of DMA_SADDR */
#define DMA_SADDR_COUNT                          (4U)

/*! @name SOFF - DES Signed Source Address Offset */
/*! @{ */
#define DMA_SOFF_SOFF_Msk                       (0xFFFFU)
#define DMA_SOFF_SOFF_Pos                      (0U)
#define DMA_SOFF_SOFF(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_SOFF_SOFF_Pos)) & DMA_SOFF_SOFF_Msk)
/*! @} */

/* The count of DMA_SOFF */
#define DMA_SOFF_COUNT                           (4U)

/*! @name ATTR - DES Transfer Attributes */
/*! @{ */
#define DMA_ATTR_DSIZE_Msk                      (0x7U)
#define DMA_ATTR_DSIZE_Pos                     (0U)
#define DMA_ATTR_DSIZE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DSIZE_Pos)) & DMA_ATTR_DSIZE_Msk)
#define DMA_ATTR_DMOD_Msk                       (0xF8U)
#define DMA_ATTR_DMOD_Pos                      (3U)
#define DMA_ATTR_DMOD(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DMOD_Pos)) & DMA_ATTR_DMOD_Msk)
#define DMA_ATTR_SSIZE_Msk                      (0x700U)
#define DMA_ATTR_SSIZE_Pos                     (8U)
/*! SSIZE - Source data transfer size
 *  0b000..8-bit
 *  0b001..16-bit
 *  0b010..32-bit
 *  0b011..Reserved
 *  0b100..16-byte
 *  0b101..32-byte
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define DMA_ATTR_SSIZE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SSIZE_Pos)) & DMA_ATTR_SSIZE_Msk)
#define DMA_ATTR_SMOD_Msk                       (0xF800U)
#define DMA_ATTR_SMOD_Pos                      (11U)
/*! SMOD - Source Address Modulo.
 *  0b00000..Source address modulo feature is disabled
 */
#define DMA_ATTR_SMOD(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SMOD_Pos)) & DMA_ATTR_SMOD_Msk)
/*! @} */

/* The count of DMA_ATTR */
#define DMA_ATTR_COUNT                           (4U)

/*! @name NBYTES_MLNO - DES Minor Byte Count (Minor Loop Disabled) */
/*! @{ */
#define DMA_NBYTES_MLNO_NBYTES_Msk              (0xFFFFFFFFU)
#define DMA_NBYTES_MLNO_NBYTES_Pos             (0U)
#define DMA_NBYTES_MLNO_NBYTES(x)                (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLNO_NBYTES_Pos)) & DMA_NBYTES_MLNO_NBYTES_Msk)
/*! @} */

/* The count of DMA_NBYTES_MLNO */
#define DMA_NBYTES_MLNO_COUNT                    (4U)

/*! @name NBYTES_MLOFFNO - DES Signed Minor Loop Offset (Minor Loop Enabled and Offset Disabled) */
/*! @{ */
#define DMA_NBYTES_MLOFFNO_NBYTES_Msk           (0x3FFFFFFFU)
#define DMA_NBYTES_MLOFFNO_NBYTES_Pos          (0U)
#define DMA_NBYTES_MLOFFNO_NBYTES(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_NBYTES_Pos)) & DMA_NBYTES_MLOFFNO_NBYTES_Msk)
#define DMA_NBYTES_MLOFFNO_DMLOE_Msk            (0x40000000U)
#define DMA_NBYTES_MLOFFNO_DMLOE_Pos           (30U)
/*! DMLOE - Destination Minor Loop Offset enable
 *  0b0..The minor loop offset is not applied to the DADDR
 *  0b1..The minor loop offset is applied to the DADDR
 */
#define DMA_NBYTES_MLOFFNO_DMLOE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_DMLOE_Pos)) & DMA_NBYTES_MLOFFNO_DMLOE_Msk)
#define DMA_NBYTES_MLOFFNO_SMLOE_Msk            (0x80000000U)
#define DMA_NBYTES_MLOFFNO_SMLOE_Pos           (31U)
/*! SMLOE - Source Minor Loop Offset Enable
 *  0b0..The minor loop offset is not applied to the SADDR
 *  0b1..The minor loop offset is applied to the SADDR
 */
#define DMA_NBYTES_MLOFFNO_SMLOE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_SMLOE_Pos)) & DMA_NBYTES_MLOFFNO_SMLOE_Msk)
/*! @} */

/* The count of DMA_NBYTES_MLOFFNO */
#define DMA_NBYTES_MLOFFNO_COUNT                 (4U)

/*! @name NBYTES_MLOFFYES - DES Signed Minor Loop Offset (Minor Loop and Offset Enabled) */
/*! @{ */
#define DMA_NBYTES_MLOFFYES_NBYTES_Msk          (0x3FFU)
#define DMA_NBYTES_MLOFFYES_NBYTES_Pos         (0U)
#define DMA_NBYTES_MLOFFYES_NBYTES(x)            (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_NBYTES_Pos)) & DMA_NBYTES_MLOFFYES_NBYTES_Msk)
#define DMA_NBYTES_MLOFFYES_MLOFF_Msk           (0x3FFFFC00U)
#define DMA_NBYTES_MLOFFYES_MLOFF_Pos          (10U)
#define DMA_NBYTES_MLOFFYES_MLOFF(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_MLOFF_Pos)) & DMA_NBYTES_MLOFFYES_MLOFF_Msk)
#define DMA_NBYTES_MLOFFYES_DMLOE_Msk           (0x40000000U)
#define DMA_NBYTES_MLOFFYES_DMLOE_Pos          (30U)
/*! DMLOE - Destination Minor Loop Offset enable
 *  0b0..The minor loop offset is not applied to the DADDR
 *  0b1..The minor loop offset is applied to the DADDR
 */
#define DMA_NBYTES_MLOFFYES_DMLOE(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_DMLOE_Pos)) & DMA_NBYTES_MLOFFYES_DMLOE_Msk)
#define DMA_NBYTES_MLOFFYES_SMLOE_Msk           (0x80000000U)
#define DMA_NBYTES_MLOFFYES_SMLOE_Pos          (31U)
/*! SMLOE - Source Minor Loop Offset Enable
 *  0b0..The minor loop offset is not applied to the SADDR
 *  0b1..The minor loop offset is applied to the SADDR
 */
#define DMA_NBYTES_MLOFFYES_SMLOE(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_SMLOE_Pos)) & DMA_NBYTES_MLOFFYES_SMLOE_Msk)
/*! @} */

/* The count of DMA_NBYTES_MLOFFYES */
#define DMA_NBYTES_MLOFFYES_COUNT                (4U)

/*! @name SLAST - DES Last Source Address Adjustment */
/*! @{ */
#define DMA_SLAST_SLAST_Msk                     (0xFFFFFFFFU)
#define DMA_SLAST_SLAST_Pos                    (0U)
#define DMA_SLAST_SLAST(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_SLAST_SLAST_Pos)) & DMA_SLAST_SLAST_Msk)
/*! @} */

/* The count of DMA_SLAST */
#define DMA_SLAST_COUNT                          (4U)

/*! @name DADDR - DES Destination Address */
/*! @{ */
#define DMA_DADDR_DADDR_Msk                     (0xFFFFFFFFU)
#define DMA_DADDR_DADDR_Pos                    (0U)
#define DMA_DADDR_DADDR(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DADDR_DADDR_Pos)) & DMA_DADDR_DADDR_Msk)
/*! @} */

/* The count of DMA_DADDR */
#define DMA_DADDR_COUNT                          (4U)

/*! @name DOFF - DES Signed Destination Address Offset */
/*! @{ */
#define DMA_DOFF_DOFF_Msk                       (0xFFFFU)
#define DMA_DOFF_DOFF_Pos                      (0U)
#define DMA_DOFF_DOFF(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_DOFF_DOFF_Pos)) & DMA_DOFF_DOFF_Msk)
/*! @} */

/* The count of DMA_DOFF */
#define DMA_DOFF_COUNT                           (4U)

/*! @name CITER_ELINKNO - DES Current Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
/*! @{ */
#define DMA_CITER_ELINKNO_CITER_Msk             (0x7FFFU)
#define DMA_CITER_ELINKNO_CITER_Pos            (0U)
#define DMA_CITER_ELINKNO_CITER(x)               (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKNO_CITER_Pos)) & DMA_CITER_ELINKNO_CITER_Msk)
#define DMA_CITER_ELINKNO_ELINK_Msk             (0x8000U)
#define DMA_CITER_ELINKNO_ELINK_Pos            (15U)
/*! ELINK - Enable channel-to-channel linking on minor-loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_CITER_ELINKNO_ELINK(x)               (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKNO_ELINK_Pos)) & DMA_CITER_ELINKNO_ELINK_Msk)
/*! @} */

/* The count of DMA_CITER_ELINKNO */
#define DMA_CITER_ELINKNO_COUNT                  (4U)

/*! @name CITER_ELINKYES - DES Current Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
/*! @{ */
#define DMA_CITER_ELINKYES_CITER_Msk            (0x1FFU)
#define DMA_CITER_ELINKYES_CITER_Pos           (0U)
#define DMA_CITER_ELINKYES_CITER(x)              (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_CITER_Pos)) & DMA_CITER_ELINKYES_CITER_Msk)
#define DMA_CITER_ELINKYES_LINKCH_Msk           (0x600U)
#define DMA_CITER_ELINKYES_LINKCH_Pos          (9U)
#define DMA_CITER_ELINKYES_LINKCH(x)             (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_LINKCH_Pos)) & DMA_CITER_ELINKYES_LINKCH_Msk)
#define DMA_CITER_ELINKYES_ELINK_Msk            (0x8000U)
#define DMA_CITER_ELINKYES_ELINK_Pos           (15U)
/*! ELINK - Enable channel-to-channel linking on minor-loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_CITER_ELINKYES_ELINK(x)              (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_ELINK_Pos)) & DMA_CITER_ELINKYES_ELINK_Msk)
/*! @} */

/* The count of DMA_CITER_ELINKYES */
#define DMA_CITER_ELINKYES_COUNT                 (4U)

/*! @name DLAST_SGA - DES Last Destination Address Adjustment/Scatter Gather Address */
/*! @{ */
#define DMA_DLAST_SGA_DLASTSGA_Msk              (0xFFFFFFFFU)
#define DMA_DLAST_SGA_DLASTSGA_Pos             (0U)
#define DMA_DLAST_SGA_DLASTSGA(x)                (((uint32_t)(((uint32_t)(x)) << DMA_DLAST_SGA_DLASTSGA_Pos)) & DMA_DLAST_SGA_DLASTSGA_Msk)
/*! @} */

/* The count of DMA_DLAST_SGA */
#define DMA_DLAST_SGA_COUNT                      (4U)

/*! @name CSR - DES Control and Status */
/*! @{ */
#define DMA_CSR_START_Msk                       (0x1U)
#define DMA_CSR_START_Pos                      (0U)
/*! START - Channel Start
 *  0b0..The channel is not explicitly started
 *  0b1..The channel is explicitly started via a software initiated service request
 */
#define DMA_CSR_START(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_CSR_START_Pos)) & DMA_CSR_START_Msk)
#define DMA_CSR_INTMAJOR_Msk                    (0x2U)
#define DMA_CSR_INTMAJOR_Pos                   (1U)
/*! INTMAJOR - Enable an interrupt when major iteration count completes
 *  0b0..The end-of-major loop interrupt is disabled
 *  0b1..The end-of-major loop interrupt is enabled
 */
#define DMA_CSR_INTMAJOR(x)                      (((uint16_t)(((uint16_t)(x)) << DMA_CSR_INTMAJOR_Pos)) & DMA_CSR_INTMAJOR_Msk)
#define DMA_CSR_INTHALF_Msk                     (0x4U)
#define DMA_CSR_INTHALF_Pos                    (2U)
/*! INTHALF - Enable an interrupt when major counter is half complete.
 *  0b0..The half-point interrupt is disabled
 *  0b1..The half-point interrupt is enabled
 */
#define DMA_CSR_INTHALF(x)                       (((uint16_t)(((uint16_t)(x)) << DMA_CSR_INTHALF_Pos)) & DMA_CSR_INTHALF_Msk)

#define DMA_CSR_DREQ_Msk                        (0x8U)
#define DMA_CSR_DREQ_Pos                       (3U)
/*! DREQ - Disable Request
 *  0b0..The channel's ERQ bit is not affected
 *  0b1..The channel's ERQ bit is cleared when the major loop is complete
 */
#define DMA_CSR_DREQ(x)                          (((uint16_t)(((uint16_t)(x)) << DMA_CSR_DREQ_Pos)) & DMA_CSR_DREQ_Msk)
#define DMA_CSR_ESG_Msk                         (0x10U)
#define DMA_CSR_ESG_Pos                        (4U)
/*! ESG - Enable Scatter/Gather Processing
 *  0b0..The current channel's DES is normal format.
 *  0b1..The current channel's DES specifies a scatter gather format. The DLASTSGA field provides a memory pointer to the next DES to be loaded into this channel after the major loop completes its execution.
 */
#define DMA_CSR_ESG(x)                           (((uint16_t)(((uint16_t)(x)) << DMA_CSR_ESG_Pos)) & DMA_CSR_ESG_Msk)
#define DMA_CSR_MAJORELINK_Msk                  (0x20U)
#define DMA_CSR_MAJORELINK_Pos                 (5U)
/*! MAJORELINK - Enable channel-to-channel linking on major loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_CSR_MAJORELINK(x)                    (((uint16_t)(((uint16_t)(x)) << DMA_CSR_MAJORELINK_Pos)) & DMA_CSR_MAJORELINK_Msk)
#define DMA_CSR_ACTIVE_Msk                      (0x40U)
#define DMA_CSR_ACTIVE_Pos                     (6U)
#define DMA_CSR_ACTIVE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_CSR_ACTIVE_Pos)) & DMA_CSR_ACTIVE_Msk)
#define DMA_CSR_DONE_Msk                        (0x80U)
#define DMA_CSR_DONE_Pos                       (7U)
#define DMA_CSR_DONE(x)                          (((uint16_t)(((uint16_t)(x)) << DMA_CSR_DONE_Pos)) & DMA_CSR_DONE_Msk)
#define DMA_CSR_MAJORLINKCH_Msk                 (0x300U)
#define DMA_CSR_MAJORLINKCH_Pos                (8U)
#define DMA_CSR_MAJORLINKCH(x)                   (((uint16_t)(((uint16_t)(x)) << DMA_CSR_MAJORLINKCH_Pos)) & DMA_CSR_MAJORLINKCH_Msk)
#define DMA_CSR_BWC_Msk                         (0xC000U)
#define DMA_CSR_BWC_Pos                        (14U)
/*! BWC - Bandwidth Control
 *  0b00..No DMA engine stalls
 *  0b01..Reserved
 *  0b10..DMA engine stalls for 4 cycles after each r/w
 *  0b11..DMA engine stalls for 8 cycles after each r/w
 */
#define DMA_CSR_BWC(x)                           (((uint16_t)(((uint16_t)(x)) << DMA_CSR_BWC_Pos)) & DMA_CSR_BWC_Msk)
/*! @} */

/* The count of DMA_CSR */
#define DMA_CSR_COUNT                            (4U)

/*! @name BITER_ELINKNO - DES Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
/*! @{ */
#define DMA_BITER_ELINKNO_BITER_Msk             (0x7FFFU)
#define DMA_BITER_ELINKNO_BITER_Pos            (0U)
#define DMA_BITER_ELINKNO_BITER(x)               (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKNO_BITER_Pos)) & DMA_BITER_ELINKNO_BITER_Msk)
#define DMA_BITER_ELINKNO_ELINK_Msk             (0x8000U)
#define DMA_BITER_ELINKNO_ELINK_Pos            (15U)
/*! ELINK - Enables channel-to-channel linking on minor loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_BITER_ELINKNO_ELINK(x)               (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKNO_ELINK_Pos)) & DMA_BITER_ELINKNO_ELINK_Msk)
/*! @} */

/* The count of DMA_BITER_ELINKNO */
#define DMA_BITER_ELINKNO_COUNT                  (4U)

/*! @name BITER_ELINKYES - DES Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
/*! @{ */
#define DMA_BITER_ELINKYES_BITER_Msk            (0x1FFU)
#define DMA_BITER_ELINKYES_BITER_Pos           (0U)
#define DMA_BITER_ELINKYES_BITER(x)              (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_BITER_Pos)) & DMA_BITER_ELINKYES_BITER_Msk)
#define DMA_BITER_ELINKYES_LINKCH_Msk           (0x600U)
#define DMA_BITER_ELINKYES_LINKCH_Pos          (9U)
#define DMA_BITER_ELINKYES_LINKCH(x)             (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_LINKCH_Pos)) & DMA_BITER_ELINKYES_LINKCH_Msk)
#define DMA_BITER_ELINKYES_ELINK_Msk            (0x8000U)
#define DMA_BITER_ELINKYES_ELINK_Pos           (15U)
/*! ELINK - Enables channel-to-channel linking on minor loop complete
 *  0b0..The channel-to-channel linking is disabled
 *  0b1..The channel-to-channel linking is enabled
 */
#define DMA_BITER_ELINKYES_ELINK(x)              (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_ELINK_Pos)) & DMA_BITER_ELINKYES_ELINK_Msk)
/*! @} */

/* The count of DMA_BITER_ELINKYES */
#define DMA_BITER_ELINKYES_COUNT                 (4U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */

/*----------------------------------------------------
*Regsiter Address Definition for Module TIMER2
*----------------------------------------------------*/
#define ADDR_TIMER2_TIMx_CR1          0x40000000
#define ADDR_TIMER2_TIMx_CR2          0x40000004
#define ADDR_TIMER2_TIMx_SMCR         0x40000008
#define ADDR_TIMER2_TIMx_DIER         0x4000000c
#define ADDR_TIMER2_TIMx_SR           0x40000010
#define ADDR_TIMER2_TIMx_EGR          0x40000014
#define ADDR_TIMER2_TIMx_CCMR1_OP     0x40000018
#define ADDR_TIMER2_TIMx_CCMR1_IC     0x40000018
#define ADDR_TIMER2_TIMx_CCER         0x40000020
#define ADDR_TIMER2_TIMx_CNT          0x40000024
#define ADDR_TIMER2_TIMx_PSC          0x40000028
#define ADDR_TIMER2_TIMx_ARR          0x4000002c
#define ADDR_TIMER2_TIMx_CCR1         0x40000034
#define ADDR_TIMER2_TIMx_CCR2         0x40000038
#define ADDR_TIMER2_TIMx_DCR          0x40000048
#define ADDR_TIMER2_TIMx_DMAR         0x4000004c

/*----------------------------------------------------
*Regsiter Address Definition for Module LPTIM1
*----------------------------------------------------*/
#define ADDR_LPTIM1_CSR               0x40000c00
#define ADDR_LPTIM1_PSR               0x40000c04
#define ADDR_LPTIM1_CMR               0x40000c08
#define ADDR_LPTIM1_CNR               0x40000c0c
#define ADDR_LPTIM1_ARR               0x40000c10

/*----------------------------------------------------
*Regsiter Address Definition for Module LPTIM2
*----------------------------------------------------*/
#define ADDR_LPTIM2_CSR               0x40000c20
#define ADDR_LPTIM2_PSR               0x40000c24
#define ADDR_LPTIM2_CMR               0x40000c28
#define ADDR_LPTIM2_CNR               0x40000c2c
#define ADDR_LPTIM2_ARR               0x40000c30

/*----------------------------------------------------
*Regsiter Address Definition for Module RTC
*----------------------------------------------------*/
#define ADDR_RTC_RTC_CRH           0x40002800
#define ADDR_RTC_RTC_CRL           0x40002804
#define ADDR_RTC_RTC_PRLH          0x40002808
#define ADDR_RTC_RTC_PRLL          0x4000280c
#define ADDR_RTC_RTC_DIVH          0x40002810
#define ADDR_RTC_RTC_DIVL          0x40002814
#define ADDR_RTC_RTC_CNTH          0x40002818
#define ADDR_RTC_RTC_CNTL          0x4000281c
#define ADDR_RTC_RTC_ALRH          0x40002820
#define ADDR_RTC_RTC_ALRL          0x40002824

/*----------------------------------------------------
*Regsiter Address Definition for Module IWDG
*----------------------------------------------------*/
#define ADDR_IWDG_IWDG_KR           0x40003000
#define ADDR_IWDG_IWDG_PR           0x40003004
#define ADDR_IWDG_IWDG_RLR          0x40003008
#define ADDR_IWDG_IWDG_SR           0x4000300c
#define ADDR_IWDG_IWDG_EN           0x40003010
#define ADDR_IWDG_IWDG_LOCK         0x40003014

/*----------------------------------------------------
*Regsiter Address Definition for Module SPI1
*----------------------------------------------------*/
#define ADDR_SPI1_CR1               0x40003800
#define ADDR_SPI1_CR2               0x40003804
#define ADDR_SPI1_SR                0x40003808
#define ADDR_SPI1_DR                0x4000380c
#define ADDR_SPI1_CRCPR             0x40003810
#define ADDR_SPI1_RXCRCR            0x40003814
#define ADDR_SPI1_TXCRCR            0x40003818

/*----------------------------------------------------
*Regsiter Address Definition for Module FLASH
*----------------------------------------------------*/
#define ADDR_FLASH_CTRL              0x40003c00
#define ADDR_FLASH_CMD               0x40003c04
#define ADDR_FLASH_PAGE_ADDR0        0x40003c08
#define ADDR_FLASH_STAT              0x40003c10
#define ADDR_FLASH_USER_WR_PROT      0x40003c14
#define ADDR_FLASH_USERKEY           0x40003c1c

/*----------------------------------------------------
*Regsiter Address Definition for Module UART1
*----------------------------------------------------*/
#define ADDR_UART1_RBR_THR_DLL       0x40004800
#define ADDR_UART1_IER_DLH           0x40004804
#define ADDR_UART1_IIR               0x40004808
#define ADDR_UART1_LCR               0x4000480c
#define ADDR_UART1_MCR               0x40004810
#define ADDR_UART1_LSR               0x40004814
#define ADDR_UART1_MSR               0x40004818
#define ADDR_UART1_SCR               0x4000481c
#define ADDR_UART1_FAR               0x40004870
#define ADDR_UART1_USR               0x4000487c
#define ADDR_UART1_HTX               0x400048a4
#define ADDR_UART1_DMASA             0x400048a8
#define ADDR_UART1_DLF               0x400048c0
#define ADDR_UART1_RAR               0x400048c4
#define ADDR_UART1_TAR               0x400048c8
#define ADDR_UART1_LCR_EXT           0x400048cc

/*----------------------------------------------------
*Regsiter Address Definition for Module I2C
*----------------------------------------------------*/
#define ADDR_I2C_CR1           0x40005400
#define ADDR_I2C_CR2           0x40005404
#define ADDR_I2C_OAR1          0x40005408
#define ADDR_I2C_OAR2          0x4000540c
#define ADDR_I2C_DR            0x40005410
#define ADDR_I2C_SR1           0x40005414
#define ADDR_I2C_SR2           0x40005418
#define ADDR_I2C_CCR           0x4000541c
#define ADDR_I2C_TRISE         0x40005420

/*----------------------------------------------------
*Regsiter Address Definition for Module AON
*----------------------------------------------------*/
#define ADDR_AON_BKP_RTCCR         0x40006c2c

/*----------------------------------------------------
*Regsiter Address Definition for Module PWR
*----------------------------------------------------*/
#define ADDR_PWR_CR                0x40007000
#define ADDR_PWR_CSR               0x40007004

/*----------------------------------------------------
*Regsiter Address Definition for Module EXTI
*----------------------------------------------------*/
#define ADDR_EXTI_EXTI_IMR          0x40010400
#define ADDR_EXTI_EXTI_EMR          0x40010404
#define ADDR_EXTI_EXTI_RTSR         0x40010408
#define ADDR_EXTI_EXTI_FTSR         0x4001040c
#define ADDR_EXTI_EXTI_SWIER        0x40010410
#define ADDR_EXTI_EXTI_PR           0x40010414

/*----------------------------------------------------
*Regsiter Address Definition for Module GPIO0
*----------------------------------------------------*/
#define ADDR_GPIO0_CON0              0x40010800
#define ADDR_GPIO0_OE                0x40010804
#define ADDR_GPIO0_PUE               0x40010808
#define ADDR_GPIO0_PDE               0x4001080c
#define ADDR_GPIO0_OD                0x40010810
#define ADDR_GPIO0_IE                0x40010814
#define ADDR_GPIO0_SMT               0x40010818
#define ADDR_GPIO0_SL                0x4001081c
#define ADDR_GPIO0_DR                0x40010820
#define ADDR_GPIO0_DATA_IN           0x40010824
#define ADDR_GPIO0_DATA_OUT          0x40010828
#define ADDR_GPIO0_OSET              0x4001082c
#define ADDR_GPIO0_OCLR              0x40010830
#define ADDR_GPIO0_OTGL              0x40010834
#define ADDR_GPIO0_INT_SEL           0x4001083c

/*----------------------------------------------------
*Regsiter Address Definition for Module GPIO1
*----------------------------------------------------*/
#define ADDR_GPIO1_CON0              0x40010840
#define ADDR_GPIO1_OE                0x40010844
#define ADDR_GPIO1_PUE               0x40010848
#define ADDR_GPIO1_PDE               0x4001084c
#define ADDR_GPIO1_OD                0x40010850
#define ADDR_GPIO1_IE                0x40010854
#define ADDR_GPIO1_SMT               0x40010858
#define ADDR_GPIO1_SL                0x4001085c
#define ADDR_GPIO1_DR                0x40010860
#define ADDR_GPIO1_DATA_IN           0x40010864
#define ADDR_GPIO1_DATA_OUT          0x40010868
#define ADDR_GPIO1_OSET              0x4001086c
#define ADDR_GPIO1_OCLR              0x40010870
#define ADDR_GPIO1_OTGL              0x40010874
#define ADDR_GPIO1_INT_SEL           0x4001087c

/*----------------------------------------------------
*Regsiter Address Definition for Module GPIO2
*----------------------------------------------------*/
#define ADDR_GPIO2_CON0              0x40010880
#define ADDR_GPIO2_OE                0x40010884
#define ADDR_GPIO2_PUE               0x40010888
#define ADDR_GPIO2_PDE               0x4001088c
#define ADDR_GPIO2_OD                0x40010890
#define ADDR_GPIO2_IE                0x40010894
#define ADDR_GPIO2_SMT               0x40010898
#define ADDR_GPIO2_DR                0x400108a0
#define ADDR_GPIO2_DATA_IN           0x400108a4
#define ADDR_GPIO2_DATA_OUT          0x400108a8
#define ADDR_GPIO2_OSET              0x400108ac
#define ADDR_GPIO2_OCLR              0x400108b0
#define ADDR_GPIO2_OTGL              0x400108b4
#define ADDR_GPIO2_INT_SEL           0x400108bc

/*----------------------------------------------------
*Regsiter Address Definition for Module AFE
*----------------------------------------------------*/
#define ADDR_AFE_NOP               0x40012800
#define ADDR_AFE_PAGE              0x40012804
#define ADDR_AFE_STATUS            0x40012808
#define ADDR_AFE_AFE_CFG           0x4001280c
#define ADDR_AFE_SPI_CFG           0x40012810
#define ADDR_AFE_PWM_CTRL          0x40012814
#define ADDR_AFE_REF_CTRL          0x4001281c
#define ADDR_AFE_IEXC_RANGE        0x40012820
#define ADDR_AFE_IEXC_CTRL         0x40012824
#define ADDR_AFE_USERKEY           0x40012830
#define ADDR_AFE_PAGE_KEY          0x40012838
/*----------------------------------------------------
*Regsiter Address Definition for Module DAC
*----------------------------------------------------*/
#define ADDR_DAC_CTRL              0x40012850
#define ADDR_DAC_DAC_DATA          0x40012854
#define ADDR_DAC_CLAMPH            0x40012858
#define ADDR_DAC_CLAMPL            0x4001285c
#define ADDR_DAC_AOUT_REG0         0x40012860
#define ADDR_DAC_AOUT_REG1         0x40012864

/*----------------------------------------------------
*Regsiter Address Definition for Module ADC_SUBSYS_USER
*----------------------------------------------------*/
#define ADDR_ADC_SUBSYS_USER_ERROR_STATUS      0x40012880
#define ADDR_ADC_SUBSYS_USER_ERROR_EN          0x40012884
#define ADDR_ADC_SUBSYS_USER_ADC_DRDY          0x40012888
#define ADDR_ADC_SUBSYS_USER_DMA_MODE          0x4001288c
#define ADDR_ADC_SUBSYS_USER_IO_CONTROL_IOUT   0x40012890
#define ADDR_ADC_SUBSYS_USER_IO_CONTROL_VBIAS  0x40012894
#define ADDR_ADC_SUBSYS_USER_ADC_STATUS_0      0x40012898
#define ADDR_ADC_SUBSYS_USER_ADC_DATA_0        0x4001289c
#define ADDR_ADC_SUBSYS_USER_INTERRUPT_CONTROL_0  0x400128a0
#define ADDR_ADC_SUBSYS_USER_ADC_CONTROL_0     0x400128a4
#define ADDR_ADC_SUBSYS_USER_CHANNEL_CFG_0     0x400128a8
#define ADDR_ADC_SUBSYS_USER_CONFIGURATION_0   0x400128ac
#define ADDR_ADC_SUBSYS_USER_FILTER_0          0x400128b0
#define ADDR_ADC_SUBSYS_USER_OFFSET_0          0x400128b4
#define ADDR_ADC_SUBSYS_USER_GAIN_0            0x400128b8
#define ADDR_ADC_SUBSYS_USER_ADC_0_HI_COMPARATOR  0x400128bc
#define ADDR_ADC_SUBSYS_USER_ADC_0_LO_COMPARATOR  0x400128c0
#define ADDR_ADC_SUBSYS_USER_ADC_STATUS_1      0x400128c4
#define ADDR_ADC_SUBSYS_USER_ADC_DATA_1        0x400128c8
#define ADDR_ADC_SUBSYS_USER_INTERRUPT_CONTROL_1  0x400128cc
#define ADDR_ADC_SUBSYS_USER_ADC_CONTROL_1     0x400128d0
#define ADDR_ADC_SUBSYS_USER_CHANNEL_CFG_1     0x400128d4
#define ADDR_ADC_SUBSYS_USER_CONFIGURATION_1   0x400128d8
#define ADDR_ADC_SUBSYS_USER_FILTER_1          0x400128dc
#define ADDR_ADC_SUBSYS_USER_OFFSET_1          0x400128e0
#define ADDR_ADC_SUBSYS_USER_GAIN_1            0x400128e4
#define ADDR_ADC_SUBSYS_USER_ADC_1_HI_COMPARATOR  0x400128e8
#define ADDR_ADC_SUBSYS_USER_ADC_1_LO_COMPARATOR  0x400128ec

/*----------------------------------------------------
*Regsiter Address Definition for Module TIMER1
*----------------------------------------------------*/
#define ADDR_TIMER1_TIMx_CR1          0x40012c00
#define ADDR_TIMER1_TIMx_CR2          0x40012c04
#define ADDR_TIMER1_TIMx_SMCR         0x40012c08
#define ADDR_TIMER1_TIMx_DIER         0x40012c0c
#define ADDR_TIMER1_TIMx_SR           0x40012c10
#define ADDR_TIMER1_TIMx_EGR          0x40012c14
#define ADDR_TIMER1_TIMx_CCMR1_OP     0x40012c18
#define ADDR_TIMER1_TIMx_CCMR1_IC     0x40012c18
#define ADDR_TIMER1_TIMx_CCER         0x40012c20
#define ADDR_TIMER1_TIMx_CNT          0x40012c24
#define ADDR_TIMER1_TIMx_PSC          0x40012c28
#define ADDR_TIMER1_TIMx_ARR          0x40012c2c
#define ADDR_TIMER1_TIMx_CCR1         0x40012c34
#define ADDR_TIMER1_TIMx_CCR2         0x40012c38
#define ADDR_TIMER1_TIMx_DCR          0x40012c48
#define ADDR_TIMER1_TIMx_DMAR         0x40012c4c

/*----------------------------------------------------
*Regsiter Address Definition for Module SPI0
*----------------------------------------------------*/
#define ADDR_SPI0_CR1               0x40013000
#define ADDR_SPI0_CR2               0x40013004
#define ADDR_SPI0_SR                0x40013008
#define ADDR_SPI0_DR                0x4001300c
#define ADDR_SPI0_CRCPR             0x40013010
#define ADDR_SPI0_RXCRCR            0x40013014
#define ADDR_SPI0_TXCRCR            0x40013018

/*----------------------------------------------------
*Regsiter Address Definition for Module UART0
*----------------------------------------------------*/
#define ADDR_UART0_RBR_THR_DLL       0x40013800
#define ADDR_UART0_IER_DLH           0x40013804
#define ADDR_UART0_IIR               0x40013808
#define ADDR_UART0_LCR               0x4001380c
#define ADDR_UART0_MCR               0x40013810
#define ADDR_UART0_LSR               0x40013814
#define ADDR_UART0_MSR               0x40013818
#define ADDR_UART0_SCR               0x4001381c
#define ADDR_UART0_FAR               0x40013870
#define ADDR_UART0_USR               0x4001387c
#define ADDR_UART0_HTX               0x400138a4
#define ADDR_UART0_DMASA             0x400138a8
#define ADDR_UART0_DLF               0x400138c0
#define ADDR_UART0_RAR               0x400138c4
#define ADDR_UART0_TAR               0x400138c8
#define ADDR_UART0_LCR_EXT           0x400138cc

/*----------------------------------------------------
*Regsiter Address Definition for Module MIO
*----------------------------------------------------*/
#define ADDR_MIO_MIO_CTRL          0x40018008
#define ADDR_MIO_MIO_PIN           0x4001800c
#define ADDR_MIO_MIO_SHIFTSTAT     0x40018010
#define ADDR_MIO_MIO_SHIFTERR      0x40018014
#define ADDR_MIO_MIO_TIMSTAT       0x40018018
#define ADDR_MIO_MIO_SHIFTSIEN     0x40018020
#define ADDR_MIO_MIO_SHIFTEIEN     0x40018024
#define ADDR_MIO_MIO_TIMIEN        0x40018028
#define ADDR_MIO_MIO_SHIFTSDEN     0x40018030
#define ADDR_MIO_MIO_SHIFTCTL0     0x40018080
#define ADDR_MIO_MIO_SHIFTCTL1     0x40018084
#define ADDR_MIO_MIO_SHIFTCFG0     0x40018100
#define ADDR_MIO_MIO_SHIFTCFG1     0x40018104
#define ADDR_MIO_MIO_SHIFTBUF0     0x40018200
#define ADDR_MIO_MIO_SHIFTBUF1     0x40018204
#define ADDR_MIO_MIO_SHIFTBUFBIS0  0x40018280
#define ADDR_MIO_MIO_SHIFTBUFBIS1  0x40018284
#define ADDR_MIO_MIO_SHIFTBUFBYS0  0x40018300
#define ADDR_MIO_MIO_SHIFTBUFBYS1  0x40018304
#define ADDR_MIO_MIO_SHIFTBUFBBS0  0x40018380
#define ADDR_MIO_MIO_SHIFTBUFBBS1  0x40018384
#define ADDR_MIO_MIO_TIMCTL0       0x40018400
#define ADDR_MIO_MIO_TIMCTL1       0x40018404
#define ADDR_MIO_MIO_TIMCFG0       0x40018480
#define ADDR_MIO_MIO_TIMCFG1       0x40018484
#define ADDR_MIO_MIO_TIMCMP0       0x40018500
#define ADDR_MIO_MIO_TIMCMP1       0x40018504
#define ADDR_MIO_MIO_SHIFTBUFNBS0  0x40018680
#define ADDR_MIO_MIO_SHIFTBUFNBS1  0x40018684
#define ADDR_MIO_MIO_SHIFTBUFHWS0  0x40018700
#define ADDR_MIO_MIO_SHIFTBUFHWS1  0x40018704
#define ADDR_MIO_MIO_SHIFTBUFNIS0  0x40018780
#define ADDR_MIO_MIO_SHIFTBUFNIS1  0x40018784
#define ADDR_MIO_MIO_SHIFTBUFOES0  0x40018800
#define ADDR_MIO_MIO_SHIFTBUFOES1  0x40018804
#define ADDR_MIO_MIO_SHIFTBUFEOS0  0x40018880
#define ADDR_MIO_MIO_SHIFTBUFEOS1  0x40018884
#define ADDR_MIO_MIO_SHIFTBUFHBS0  0x40018900
#define ADDR_MIO_MIO_SHIFTBUFHBS1  0x40018904

/*----------------------------------------------------
*Regsiter Address Definition for Module Crosslink
*----------------------------------------------------*/
#define ADDR_Crosslink_Cross_Link0_Sel0  0x40019000
#define ADDR_Crosslink_Cross_Link0_Sel1  0x40019004
#define ADDR_Crosslink_Cross_Link0_Sel2  0x40019008
#define ADDR_Crosslink_Cross_Link0_Sel3  0x4001900c
#define ADDR_Crosslink_Cross_Link0_Sel4  0x40019010
#define ADDR_Crosslink_Cross_Link0_Ctr0  0x40019014
#define ADDR_Crosslink_Cross_Link1_Sel0  0x40019018
#define ADDR_Crosslink_Cross_Link1_Sel1  0x4001901c
#define ADDR_Crosslink_Logic_Union_Sel0  0x40019020
#define ADDR_Crosslink_Logic_Union_Sel1  0x40019024
#define ADDR_Crosslink_SOFT_SYNC         0x40019028

/*----------------------------------------------------
*Regsiter Address Definition for Module RCC
*----------------------------------------------------*/
#define ADDR_RCC_RCC_CR            0x40021000
#define ADDR_RCC_RCC_CFGR          0x40021004
#define ADDR_RCC_RCC_CIR           0x40021008
#define ADDR_RCC_RCC_APB2RSTR      0x4002100c
#define ADDR_RCC_RCC_APB1RSTR      0x40021010
#define ADDR_RCC_RCC_AHBENR        0x40021014
#define ADDR_RCC_RCC_APB2ENR       0x40021018
#define ADDR_RCC_RCC_APB1ENR       0x4002101c
#define ADDR_RCC_RCC_BDCR          0x40021020
#define ADDR_RCC_RCC_CSR           0x40021024
#define ADDR_RCC_ALL_PD            0x40021028
#define ADDR_RCC_XOSC_BST          0x4002102c

/*----------------------------------------------------
*Regsiter Address Definition for Module CRC32
*----------------------------------------------------*/
#define ADDR_CRC32_DR                0x40023000
#define ADDR_CRC32_IDR               0x40023004
#define ADDR_CRC32_CR                0x40023008

/*----------------------------------------------------
*Regsiter Address Definition for Module MACL
*----------------------------------------------------*/
#define ADDR_MACL_a0                0x40023400
#define ADDR_MACL_a1                0x40023404
#define ADDR_MACL_b0                0x40023408
#define ADDR_MACL_b1                0x4002340c
#define ADDR_MACL_CFS               0x40023410
#define ADDR_MACL_CLR               0x40023414

/*----------------------------------------------------
*Regsiter Address Definition for Module BTIM
*----------------------------------------------------*/
#define ADDR_BTIM_MCR               0x4002a400
#define ADDR_BTIM_LDVAL_0           0x4002a500
#define ADDR_BTIM_CVAL_0            0x4002a504
#define ADDR_BTIM_TCTRL_0           0x4002a508
#define ADDR_BTIM_TFLG_0            0x4002a50c
#define ADDR_BTIM_LDVAL_1           0x4002a510
#define ADDR_BTIM_CVAL_1            0x4002a514
#define ADDR_BTIM_TCTRL_1           0x4002a518
#define ADDR_BTIM_TFLG_1            0x4002a51c

#ifdef __cplusplus
}
#endif

#endif //__LH32M0G3X__H

/*********************************End of File**********************************/
