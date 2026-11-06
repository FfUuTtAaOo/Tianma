
/*
***********************************************************************
Copyright @  2025  苏州领慧立芯科技有限公司

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the “Software”), to deal in the Software without
restriction, including without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***********************************************************************
@file     lh32m0g30x_mcal.c
@version     2025-04-06
*/

#include "lh32m0xx_lhl.h"
    /*!
     * brief Set control/status register into reset state.
     *
     * This function sets control/status register to a known state. This state is
     * defined in Reference Manual, which is power on reset value. This function must
     * execute in a Supervisor Mode
     * param base MACL peripheral address.
     */
void MACL_Reset(void)
    {
        (*(uint32_t *)(MACL_CFR))         = 0;
        (*(uint32_t *)(MACL_CLR))         = 0x000F0F00;//clear a0,a1,b0,b1寄存器;clear CFR寄存器中的DRDYF,DZF,DMVF,ACVF位
        
    }

    /*!
     * @brief    Multiply two 32-bit integer values,
     *            returning a 64-bit integer {b1,b0} register value.
     *
     * @details The @ref MACL_simul function multiplies two 32-bit integer values(a0,a1)
     *            and returning a 64-bit integer {b1,b0} register value.
     * @param    a0  int32_t integer value.
     * @param    a1  int32_t integer value.
     * @return    int64_t integer value after multiply.
     */
void  MACL_simula0a1(register int32_t a0, register int32_t a1)
    {
        uint32_t b0,b1;
        uint64_t result;
        //int64_t temp;
        (*(uint32_t *)(MACL_A0)) = (uint32_t)a0;
        (*(uint32_t *)(MACL_A1 | MACL_MUL_A0A1 | MACL_SIGN_CFG | MACL_INT_CFG)) = (uint32_t)a1;
    

        printf("multa test: a0=0x%08X (%d), a1=0x%08X (%d)\n", a0, a0, a1, a1);

         b1 = *(uint32_t *)(MACL_B1); 
         b0 = *(uint32_t *)(MACL_B0); 
         result = ((uint64_t)b1 << 32) | b0;
        printf("  Result: b1=0x%08X, b0=0x%08X (64-bit: 0x%016llX)\n", b1, b0, result);

    }

   /*!
 * @brief   Multiply two 32-bit integer unsigned values,
 *          returning a 64-bit integer {b1,b0} unsigned value.
 *
 * @details The @ref MACL_uimul function multiplies two 32-bit integer values
 *          and returning saturated 32-bit integer b0 register value.
 * @param   a0  uint32_t integer unsigned value.
 * @param   a1 uint32_t integer unsigned value.
 * @return  uint64_t 64-bit integer {b1,b0} unsigned value.
 */
void MACL_uimula0a1(register uint32_t a0, register uint32_t a1)
{
    uint32_t b0,b1;
    uint64_t result;
    (*(uint32_t *)(MACL_A0)) = a0;
    (*(uint32_t *)(MACL_A1 | MACL_MUL_A0A1 | MACL_UNSIGN_CFG | MACL_INT_CFG)) = a1;

      printf("multa test: a0=0x%08X (%u), a1=0x%08X (%u)\n", a0, a0, a1, a1);

         b1 = *(uint32_t *)(MACL_B1); 
         b0 = *(uint32_t *)(MACL_B0); 
         result = ((uint64_t)b1 << 32) | b0;
        
        printf("  Result: b1=0x%08X, b0=0x%08X (64-bit: 0x%016llX)\n", b1, b0, result);
}

/*!
 * @brief   Multiply two 32-bit fraction values,
 *          returning a 64-bit fraction {b1,b0} register value.
 *
 * @details The @ref MACL_sfmul function multiplies two 32-bit fraction values
 *          and returning a 64-bit fraction {b1,b0} register value.
 * @param   a0  int32_t fraction value.
 * @param   a1  int32_t fraction value.
 * @return  int64_t fraction value after multiply.
 * @PS      The number of decimal places requires the [7:0] digits of MACL CFG 
 *          register to be configured correctly. 
 */
void  MACL_sfmula0a1(register int32_t a0, register int32_t a1)
{
    uint32_t b0, b1;
    uint64_t result;
    (*(uint32_t *)(MACL_CFR))=16;//16位小数
    (*(uint32_t *)(MACL_A0)) = (uint32_t)a0;
    (*(uint32_t *)(MACL_A1 | MACL_MUL_A0A1 | MACL_SIGN_CFG | MACL_FRA_CFG)) = (uint32_t)a1;
    
     b1 = *(uint32_t *)(MACL_B1); 
     b0 = *(uint32_t *)(MACL_B0); 
     result = ((uint64_t)b1 << 32) | b0;
        
    printf("  Result: b1=0x%08X, b0=0x%08X (64-bit: 0x%016llX)\n", b1, b0, result);
}

/*!
 * @brief   Multiply two 32-bit fraction values,
 *          returning a 64-bit fraction {b1,b0} unsigned value.
 *
 * @details The @ref MACL_ufmul function multiplies two 32-bit fraction values
 *          and returning saturated 32-bit fraction b0 register value.
 * @param   a0  uint32_t fraction unsigned value.
 * @param   a1  uint32_t fraction unsigned value.
 * @return  uint64_t 64-bit integer {b1,b0} unsigned fraction value.
 * @PS      The number of decimal places requires the [7:0] digits of MACL CFG 
 *          register to be configured correctly. 
 */
void MACL_ufmula0a1(register uint32_t a0, register uint32_t a1)
{
uint32_t b1,b0;
uint64_t result;
     (*(uint32_t *)(MACL_CFR))=16;//16位小数
    (*(uint32_t *)(MACL_A0)) = a0;
    (*(uint32_t *)(MACL_A1 | MACL_MUL_A0A1 | MACL_UNSIGN_CFG | MACL_FRA_CFG)) = a1;
        b1 = *(uint32_t *)(MACL_B1); 
         b0 = *(uint32_t *)(MACL_B0); 
         result = ((uint64_t)b1 << 32) | b0;
        
        printf("  Result: b1=0x%08X, b0=0x%08X (64-bit: 0x%016llX)\n", b1, b0, result);
}


