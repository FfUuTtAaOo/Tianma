/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_flash.h
 * @version 2025-09-15
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_FLASH_H
#define __LH32M0G3x_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"      

/* Define --------------------------------------------------------------------*/
#define FLASH_UNLOCK_KEY                0x789A0123u
#define FLASH_LOCK_KEY                  0x8765FEDCu

#define FLASH_CMD_PAGE_ERASE            1u
#define FLASH_CMD_USER_SPACE_ERASE      16u

#define FLASH_PAGE_SIZE                 0x1000u
#define FLASH_PAGE_MASK                 0xFFFFF000u

#define FLASH_START_ADDRESS             0x08000000u
#define FLASH_END_ADDRESS               0x0801DFFFu

typedef enum {
    FLASH_PAGE_0 = 0x8000000u,
    FLASH_PAGE_1 = 0x8001000u,
    FLASH_PAGE_2 = 0x8002000u,
    FLASH_PAGE_3 = 0x8003000u,
    FLASH_PAGE_4 = 0x8004000u,
    FLASH_PAGE_5 = 0x8005000u,
    FLASH_PAGE_6 = 0x8006000u,
    FLASH_PAGE_7 = 0x8007000u,
    FLASH_PAGE_8 = 0x8008000u,
    FLASH_PAGE_9 = 0x8009000u,    
    FLASH_PAGE_10 = 0x800A000u,
    FLASH_PAGE_11 = 0x800B000u,
    FLASH_PAGE_12 = 0x800C000u,
    FLASH_PAGE_13 = 0x800D000u,
    FLASH_PAGE_14 = 0x800E000u,
    FLASH_PAGE_15 = 0x800F000u,
    FLASH_PAGE_16 = 0x8010000u,
    FLASH_PAGE_17 = 0x8011000u,
    FLASH_PAGE_18 = 0x8012000u,
    FLASH_PAGE_19 = 0x8013000u,    
    FLASH_PAGE_20 = 0x8014000u,
    FLASH_PAGE_21 = 0x8015000u,
    FLASH_PAGE_22 = 0x8016000u,
    FLASH_PAGE_23 = 0x8017000u,
    FLASH_PAGE_24 = 0x8018000u,
    FLASH_PAGE_25 = 0x8019000u,
    FLASH_PAGE_26 = 0x801A000u,
    FLASH_PAGE_27 = 0x801B000u,
    FLASH_PAGE_28 = 0x801C000u,
    FLASH_PAGE_29 = 0x801D000u,
} FLASH_PAGE_t;                     /* Page起始地址 Each page size 4096 BYTES */

typedef enum {
    FLASH_FLAG_CMDBUSY  = FLASH_STAT_CMDBUSY_Msk,
    FLASH_FLAG_PGBUSY   = FLASH_STAT_PGBUSY_Msk,
    FLASH_FLAG_CMDDONE  = FLASH_STAT_CMDDONE_Msk,
    FLASH_FLAG_PGDONE   = FLASH_STAT_PGDONE_Msk,
    FLASH_FLAG_ERASEERROR   = FLASH_STAT_WR_ERASE_ERROR_Msk,
    FALSH_FLAG_VERIFYERROR  = FLASH_STAT_UPLD_VERIFYERR_Msk,
} FLASH_FLAG_t;

#define __LHL_FLASH_PROGRAM_ENABLE()    SET_BIT(pFLASH->CTRL, FLASH_CTRL_PROGRAM_EN_Msk)

#define __LHL_FLASH_PROGRAM_DISABLE()   CLEAR_BIT(pFLASH->CTRL, FLASH_CTRL_PROGRAM_EN_Msk)

/* Declaration ---------------------------------------------------------------*/
LHL_StatusTypeDef   LHL_FLASH_Erase(FLASH_PAGE_t StartPage, FLASH_PAGE_t EndPage, uint32_t Timeout);
LHL_StatusTypeDef   LHL_FLASH_MassErase(uint32_t Timeout);

LHL_StatusTypeDef   LHL_FLASH_Program(uint32_t Address, uint32_t* Data, uint16_t Size, uint32_t Timeout);
void                LHL_FLASH_ProgramWord(uint32_t Address, uint32_t Data);

FlagStatus          LHL_FLASH_GetFlag(FLASH_FLAG_t Flag);
FLASH_PAGE_t        LHL_FLASH_GetPage(uint32_t FlashAddress);

LHL_StatusTypeDef   LHL_FLASH_WaitForLastOperation(uint32_t Timeout);

void                LHL_FLASH_Unlock(void);
void                LHL_FLASH_Lock(void);

#ifdef __cplusplus
}

#endif

#endif 

/*********************************End of File**********************************/
