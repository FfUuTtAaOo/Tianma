/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_eeprom.h
 * @version 2025-09-23
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_EEPROM_H
#define __LH32M0G3x_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Definition ----------------------------------------------------------------*/
#define EEPROM_PAGE_ERASE       0xFFFFFFFFu     /* EEPROM 页面擦除标志 */

#define EEPROM_PAGE_VALID       0xA5A5A5A5u     /* EEPROM 数据有效标志 */

#define EEPROM_MEMORY_SIZE      0x04u           /* EEPROM 条目大小为4BYTE */

#define EEPROM_PAGE_SIZE        0x1000u         /* 单页面包含1000个条目 */

#define EEPROM_INITIAL_VERSION  0x00FFFFFFu     /* EEPROM 初始版本，递减 */

typedef enum {
    EEPROM_STATE_INIT = 0u,
    EEPROM_STATE_PAGE_A_ACTIVE,
    EEPROM_STATE_SWAP_A_TO_B,
    EEPROM_STATE_PAGE_B_ACTIVE,
    EEPROM_STATE_SWAP_B_TO_A,
    EEPROM_STATE_ERROR,
} EEPROM_FSM_t;                                 /*!< EEPROM状态机：Error->Init->[A->SWAP->B->SWAP->A] */

typedef struct {
                                         
    uint8_t             Device_ID;              /*!< 虚拟EEPROM设备ID，由此可实现多个Instance */  
    
    uint8_t             Reserved[3];
  
    FLASH_PAGE_t        PageA;                  /*!< 虚拟EEPROM页面A */

    FLASH_PAGE_t        PageB;                  /*!< 虚拟EEPROM页面B */

} EEPROM_InitTypeDef;

typedef struct {

    EEPROM_FSM_t        State;                  /*!< 虚拟EEPROM Instance FSM */
    
    uint8_t             Reserved[3];
  
    uint32_t            Cursor;                 /*!< 活动页面有效写入地址 */

    uint32_t            Version;                /*!< 活动页面有效数据版本号 */
  
    FLASH_PAGE_t        ActivePage;             /*!< 当前活动页面 */
    
    FLASH_PAGE_t        BackupPage;             /*!< 后台备用页面 */

    EEPROM_InitTypeDef  Init;                   /*!< 初始化参数 */
    
} EEPROM_HandleTypeDef;

/* Declaration ---------------------------------------------------------------*/
void                    LHL_EEPROM_ChipErase(EEPROM_HandleTypeDef* EEPROM_Handle);

void                    LHL_EEPROM_GarbageCollection(EEPROM_HandleTypeDef* EEPROM_Handle);

uint32_t                LHL_EEPROM_GetCursor(EEPROM_HandleTypeDef* EEPROM_Handle);

LHL_StatusTypeDef       LHL_EEPROM_Init(EEPROM_HandleTypeDef* EEPROM_Handle);

void                    LHL_EEPROM_InitCallback(EEPROM_HandleTypeDef *handle);

void                    LHL_EEPROM_InitErrorCallback(EEPROM_HandleTypeDef *handle);

LHL_StatusTypeDef       LHL_EEPROM_Read(EEPROM_HandleTypeDef* EEPROM_Handle, uint8_t address, uint32_t* data, uint8_t size);

LHL_StatusTypeDef       LHL_EEPROM_Write(EEPROM_HandleTypeDef* EEPROM_Handle, uint8_t address, uint32_t* data, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
