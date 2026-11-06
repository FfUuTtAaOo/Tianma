/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_eeprom.c
 * @version 2025-09-23
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
 * @brief     配置EEPROM的初始化参数
 * @note    数据存储格式：高8位->EEPROM Address；低24位-> EPPROM Data
 *          页面第1条目：MagicNumber判定页面是否合法
 *          页面第2条目：Version判断当前页面的版本号（高8位预留给CRC8）
 *          FSM预留
 * @param     EEPROM_Handle   EEPROM句柄
 * @retval     LHL_OK：页面和数据有效；LHL_ERROR：页面非法
 */
LHL_StatusTypeDef LHL_EEPROM_Init(EEPROM_HandleTypeDef* EEPROM_Handle)
{
     uint32_t status_A0 = *(__RW uint32_t*)(EEPROM_Handle->Init.PageA);                         // MagicNumber
     uint32_t status_A1 = *(__RW uint32_t*)(EEPROM_Handle->Init.PageA + EEPROM_MEMORY_SIZE);    // Version
     uint32_t status_B0 = *(__RW uint32_t*)(EEPROM_Handle->Init.PageB);
     uint32_t status_B1 = *(__RW uint32_t*)(EEPROM_Handle->Init.PageB + EEPROM_MEMORY_SIZE);
    
    /* 初始化EEPROM FSM */
    if ((status_A0 == EEPROM_PAGE_ERASE) && (status_B0 == EEPROM_PAGE_ERASE))
    {
        EEPROM_Handle->State = EEPROM_STATE_INIT;           // 状态机首次运行初始化
    }
    else if ((status_A0 == EEPROM_PAGE_VALID) && (status_B0 == EEPROM_PAGE_VALID))
    {
        if (status_A1 > status_B1)                        // 比较版本号，较低者为当前有效页
        {
            EEPROM_Handle->State = EEPROM_STATE_PAGE_B_ACTIVE;
        }
        else
        {
            EEPROM_Handle->State = EEPROM_STATE_PAGE_A_ACTIVE;
        }        
    }
    else if (status_A0 == EEPROM_PAGE_VALID)
    {
        EEPROM_Handle->State = EEPROM_STATE_PAGE_A_ACTIVE;  // 仅PageA有效
    }
    else if (status_B0 == EEPROM_PAGE_VALID)
    {
        EEPROM_Handle->State = EEPROM_STATE_PAGE_B_ACTIVE;  // 仅PageB有效
    }
    else
    {
        EEPROM_Handle->State = EEPROM_STATE_ERROR;          // 初始化失败，未查找到正确MagicNumber或未格式化
    }

    /* 根据FSM初始化EEPROM句柄参数 */
    switch(EEPROM_Handle->State)
    {
        case EEPROM_STATE_INIT:
            EEPROM_Handle->ActivePage = EEPROM_Handle->Init.PageA;  // 首次默认写入PageA
            EEPROM_Handle->BackupPage = EEPROM_Handle->Init.PageB;
            EEPROM_Handle->Version = EEPROM_INITIAL_VERSION;        // 版本号从0xFFFFFF递减
            EEPROM_Handle->Cursor = EEPROM_MEMORY_SIZE * 2;         // 有效数据从第3个条目开始写入

            LHL_EEPROM_InitCallback(EEPROM_Handle);                 // 初始化回调函数：如写入初始参数

            __LHL_FLASH_PROGRAM_ENABLE();                           // 写入Version和MagicNumber
            LHL_FLASH_ProgramWord((uint32_t)status_A1, EEPROM_Handle->Version);
            LHL_FLASH_ProgramWord((uint32_t)status_A0, EEPROM_PAGE_VALID);
            __LHL_FLASH_PROGRAM_DISABLE();
            
            EEPROM_Handle->Cursor = LHL_EEPROM_GetCursor(EEPROM_Handle);    // 更新Cursor            
            break;  
            
        case EEPROM_STATE_SWAP_A_TO_B:    
        case EEPROM_STATE_PAGE_A_ACTIVE:
            EEPROM_Handle->ActivePage = EEPROM_Handle->Init.PageA;
            EEPROM_Handle->BackupPage = EEPROM_Handle->Init.PageB;
            EEPROM_Handle->Version = status_A1;
            EEPROM_Handle->Cursor = LHL_EEPROM_GetCursor(EEPROM_Handle);
            break;
            
        case EEPROM_STATE_SWAP_B_TO_A:  
        case EEPROM_STATE_PAGE_B_ACTIVE:
            EEPROM_Handle->ActivePage = EEPROM_Handle->Init.PageB;
            EEPROM_Handle->BackupPage = EEPROM_Handle->Init.PageA;
            EEPROM_Handle->Version = status_B1;
            EEPROM_Handle->Cursor = LHL_EEPROM_GetCursor(EEPROM_Handle);
            break;
            
        case EEPROM_STATE_ERROR:
            LHL_EEPROM_InitErrorCallback(EEPROM_Handle);            // 错误回调函数：如格式化EEPROM区域
            return LHL_ERROR;
    }
    
    return LHL_OK;
}

/**
 * @brief     从FLASH有效页最后一个地址往前倒查32位宽数据，查到一个不为0xFFFFFFFF的有效数据为止
 * @note    时间复杂度O(log n)
 * @param     EEPROM_Handle   EEPROM句柄
 * @retval     uint32_t         下一个是0xFFFFFFFF的偏移地址，若整页全为0xFFFFFFFF则返回0x1000
 */
uint32_t LHL_EEPROM_GetCursor(EEPROM_HandleTypeDef* EEPROM_Handle)
{   
    uint32_t low = 0;                                   // 起始偏移
    uint32_t high = FLASH_PAGE_SIZE;                      // 结束偏移（页大小）
    uint32_t mid, page;
    
    page = EEPROM_Handle->ActivePage;    

    /* 二分查找：第1个全FF的数据位置 */
    while (low < high)                                  
    {
        mid = low + (high - low) / 2;        
        mid = (mid / 4) * 4;                            // 确保按4字节对齐        
        if (*(__RO uint32_t*)(page + mid) == 0xFFFFFFFF) 
        {
            high = mid;                                 // 找到全F数据，继续在左侧查找
        } 
        else 
        {
            low = mid + 4;                              // 找到有效数据，继续在右侧查找
        }
    }

    /* low现在指向第一个0xFFFFFFFF的位置（即下一个写入位置）*/
    return low;
}

/**
 * @brief     从EEPROM写入指定地址和长度的数据，依据Cursor立即写入下一条可用地址并同步更新
 * @note    单字写入时间120uS，多字写入时间（120*n）uS
 * @note    注意：若可写空间不足，会立即触发GC机制，此时写入时间（预留50mS）会大幅延长！
 * @param     EEPROM_Handle   EEPROM句柄
 *          address         虚拟地址，0x00~0xFE，注意地址0xFF为保留地址禁止使用
 *          *data           写入的数据，注意数据宽度最大24bit
 *          size            连续写入的数据长度
 * @retval     LHL_OK：写入数据成功；LHL_ERROR：输入参数错误，写入失败
 */
LHL_StatusTypeDef LHL_EEPROM_Write(EEPROM_HandleTypeDef* EEPROM_Handle, uint8_t address, uint32_t* data, uint8_t size)
{    
    if (address == 0xFF) return LHL_ERROR;                  // 禁止写入0xFF地址
    
    /* 可用空间检查 */
    if (EEPROM_Handle->Cursor + size * EEPROM_MEMORY_SIZE > EEPROM_PAGE_SIZE) 
    {
        LHL_EEPROM_GarbageCollection(EEPROM_Handle);        // 进行垃圾回收和页面迁移
    }
    
    /* 写入新的数据 */
    __LHL_FLASH_PROGRAM_ENABLE();
    while(size--)
    {
        LHL_FLASH_ProgramWord(EEPROM_Handle->ActivePage + EEPROM_Handle->Cursor, \
                            (((uint32_t)address++ << 24u) | (*data++ & 0x00FFFFFF)));
        EEPROM_Handle->Cursor += EEPROM_MEMORY_SIZE;
    }
    __LHL_FLASH_PROGRAM_DISABLE();
    
    return LHL_OK;
}

/**
 * @brief     从EEPROM读取指定地址和长度的数据，时间复杂度O(n)
 * @param     EEPROM_Handle   EEPROM句柄
 *          address         虚拟地址，0x00~0xFE，注意地址0xFF为保留地址禁止使用
 *          *data           读取到的数据，注意数据宽度最大24bit
 *          size            连续读取的数据长度
 * @retval     LHL_OK：读取数据保存至*data；LHL_ERROR：输入参数错误，读取失败
 */
LHL_StatusTypeDef LHL_EEPROM_Read(EEPROM_HandleTypeDef* EEPROM_Handle, uint8_t address, uint32_t* data, uint8_t size)
{
    uint32_t addr = EEPROM_Handle->ActivePage + EEPROM_Handle->Cursor - EEPROM_MEMORY_SIZE;
    uint32_t pg = EEPROM_Handle->ActivePage + EEPROM_MEMORY_SIZE;
    __RW uint32_t tmp;
    uint8_t virtual_addr, idx;
    uint8_t found_count = 0;
    
    if (address == 0xFF) return LHL_ERROR;                  // 不可使用地址0xFF
    if ((0xFF - size) <= (address - 0x01)) return LHL_ERROR;// 禁止检索范围超过0xFF
    
    /* 初始化默认返回数据 */
    for (uint8_t i = 0; i < size; i++) 
    {
        data[i] = 0x00FFFFFF;
    }
    
    /* 扫描活动页面获取有效数据 */
    while (addr > pg) 
    {
        tmp = *(__RW uint32_t*)addr;
        virtual_addr = (tmp >> 24) & 0xFF;
        
        if (virtual_addr >= address && virtual_addr < address + size) 
        {
            idx = virtual_addr - address;
            if (data[idx] == 0x00FFFFFF) 
            {
                data[idx] = tmp & 0x00FFFFFF;       // 只记录第1次找到的有效数据
                if (++found_count >= size) break;   // 找到所有数据后立即退出
            }
        }
        addr -= EEPROM_MEMORY_SIZE;
    }
    
    return LHL_OK;
}

/**
 * @brief     EEPROM所使用的两个页面全片擦除，最大时间2*4mS
 * @param     EEPROM_Handle   EEPROM句柄
 * @retval     None
 */
void LHL_EEPROM_ChipErase(EEPROM_HandleTypeDef* EEPROM_Handle)
{
    LHL_FLASH_Erase(EEPROM_Handle->Init.PageA, EEPROM_Handle->Init.PageA, LHL_MAX_TIMEOUT);    
    LHL_FLASH_Erase(EEPROM_Handle->Init.PageB, EEPROM_Handle->Init.PageB, LHL_MAX_TIMEOUT);
}

/**
 * @brief     EEPROM垃圾回收机制，重写所有有效数据（最大时间简单估算约为50mS）
 * @note    建议用户在适当时间手动调用GarbageCollection，保证系统正常读写操作都在最佳状态
 * @note    回收时间由三部分组成：
 *          1. 擦除目标页面，页擦除时间8mS;
 *          2. 读取旧数据，时间复杂度O(n);
 *          3. 写入新数据，单字写入时间120uS，最大时间（120*n）uS
 * @param     EEPROM_Handle   EEPROM句柄
 * @retval     None
 */
void LHL_EEPROM_GarbageCollection(EEPROM_HandleTypeDef* EEPROM_Handle)
{
    uint32_t bitmap[8] = {0};                               // EEPROM 256bit位图
    uint8_t addr;
    uint32_t tmp;
    uint32_t tmpCursor;
    
    /* 写入目标为备用页面，首先格式化，然后从第3个条目开始写入 */
    LHL_FLASH_Erase(EEPROM_Handle->BackupPage, EEPROM_Handle->BackupPage, LHL_MAX_TIMEOUT);
    tmpCursor = EEPROM_Handle->BackupPage + EEPROM_MEMORY_SIZE + EEPROM_MEMORY_SIZE;    

    __LHL_FLASH_PROGRAM_ENABLE();
    for (uint32_t scan_addr = (EEPROM_Handle->ActivePage + EEPROM_Handle->Cursor - EEPROM_MEMORY_SIZE); \
        scan_addr > (EEPROM_Handle->ActivePage + EEPROM_MEMORY_SIZE); \
        scan_addr -= EEPROM_MEMORY_SIZE) 
    {
        /* 从活动页面中逐条读取当前条目的数据及虚拟地址 */
        tmp = *(__RW uint32_t*)scan_addr;
        addr = (uint8_t)(tmp >> 24u);

        /* 检查这个虚拟地址是否已经在位图中被标记（即是否已经找到了它的最新值）*/
        if (!BITMAP_GET(bitmap, addr)) {
            LHL_FLASH_ProgramWord(tmpCursor, tmp);          // 写入备用页面最新值
            tmpCursor += EEPROM_MEMORY_SIZE;
            BITMAP_SET(bitmap, addr);                       // 标记此地址已写入
        }
    }
    
    /* 全部写入后交换活动页面 */
    tmp = EEPROM_Handle->BackupPage;                
    EEPROM_Handle->BackupPage = EEPROM_Handle->ActivePage;
    EEPROM_Handle->ActivePage = (FLASH_PAGE_t)tmp;
    
    /* 重设最后条目指针 */
    EEPROM_Handle->Cursor = tmpCursor - EEPROM_Handle->ActivePage;
    
    /* 写入Version，减1 */
    EEPROM_Handle->Version--;
    LHL_FLASH_ProgramWord(EEPROM_Handle->ActivePage + EEPROM_MEMORY_SIZE, EEPROM_Handle->Version);

    /* 写入MagicNumber激活页面 */
    LHL_FLASH_ProgramWord(EEPROM_Handle->ActivePage, EEPROM_PAGE_VALID);
    
    __LHL_FLASH_PROGRAM_DISABLE();
}

/**
 * @brief     EEPROM首次运行初始化时，会调用此函数
 */
__WEAK void LHL_EEPROM_InitCallback(EEPROM_HandleTypeDef *handle)
{   
    __UNUSED(handle);
}

/**
 * @brief     EEPROM每次初始化失败时，会调用此函数
 */
__WEAK void LHL_EEPROM_InitErrorCallback(EEPROM_HandleTypeDef *handle)
{
    __UNUSED(handle);
}

/*********************************End of File**********************************/
