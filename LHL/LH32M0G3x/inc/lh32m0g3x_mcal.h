/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_lptim.h
 * @version 2025-09-08
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_MCAL_H
#define __LH32M0G3x_MCAL_H


#ifdef __cplusplus
 extern "C" {
#endif

#include "lh32m0xx_lhl.h"

//#define MACL_BASE         0x40024000   //Macl Base Address 
#define MACL_A0           0x40024000   //Macl Accumulator register A0
#define MACL_A1           0x40024004   //Macl Accumulator register A1
#define MACL_B0           0x40024008   //Macl Accumulator register B0
#define MACL_B1           0x4002400C   //Macl Accumulator register B1
#define MACL_CFR          0x40024010   //Macl Configuration register
#define MACL_CLR          0x40024014   //Macl Flag and Accumulator register clear Register
//end

  
//CFG_ADDR begin
#define MACL_SIGN_CFG     0x00000000
#define MACL_UNSIGN_CFG   0x00000400
#define MACL_FRA_CFG      0x00000800
#define MACL_INT_CFG      0x00000000
//end


//FUNC_ADDR begin
//Multiplication
#define MACL_MUL_A0A1     0x00000020 
#define MACL_MUL_B0A0     0x00000040 
#define MACL_MUL_B0A1     0x00000060 
#define MACL_MULC_A0A1B0  0x00000080 
#define MACL_MULC_B0A0B0  0x000000A0 
#define MACL_MULC_B0A1B0  0x000000C0 
//Square
#define MACL_SQU_A0       0x00000300 
#define MACL_SQU_A1       0x00000320 
#define MACL_SQU_B0       0x00000340 
#define MACL_SQU_B1       0x00000360 
#define MACL_SQUC_A0      0x00000380 
#define MACL_SQUC_A1      0x000003A0
//Division
#define MACL_DIV_A0       0x00000100 
#define MACL_DIV_A1       0x00000120 
#define MACL_DIV_B0A0     0x00000140 
#define MACL_DIV_B1A0     0x00000160 
#define MACL_DIV_B0A1     0x00000180 
#define MACL_DIV_B1A1     0x000001A0 
#define MACL_DIV_BA0      0x000001C0 
#define MACL_DIV_BA1      0x000001E0 
//end

void MACL_Reset(void);
void  MACL_simula0a1(register int32_t a0, register int32_t a1);
void MACL_uimula0a1(register uint32_t a0, register uint32_t a1);
void  MACL_sfmula0a1(register int32_t a0, register int32_t a1);
void MACL_ufmula0a1(register uint32_t a0, register uint32_t a1);





#ifdef __cplusplus
}
#endif




#endif 

