/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_flash.c
 * @version 2025-09-15
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  以Page为单位擦除Flash。内部集成 120KB 用户可访问的 FLASH 存储器，按每页4K字节进行分页管理，共30页。
  * @note   页面擦除过程中会关闭全局中断。
  * @param  StartPage   定义了从此页面开始擦除。
  *         EndPage     定义了擦除到此页面为止；如果仅擦除1个页面，则Endpage与Startpage相同。
  *         Timeout     循环超时参数
  * @retval 页面超范围或循环超次数返回error，之前指令未完成返回busy，擦除成功返回ok
  */
LHL_StatusTypeDef LHL_FLASH_Erase(FLASH_PAGE_t StartPage, FLASH_PAGE_t EndPage, uint32_t Timeout)
{
    uint32_t primask_bit;
    
    if ((StartPage > EndPage) || (EndPage > FLASH_PAGE_29)) 
        return LHL_ERROR;                                                       // 如果超出页面范围返回error
    
    /* 查询等待状态寄存器的PGBUSY为0 */
    if (LHL_FLASH_WaitForLastOperation(Timeout) != LHL_OK)
    {
        return LHL_BUSY;
    }
       
    /* 开始关键任务，关闭中断 */
    primask_bit = __get_PRIMASK();
    __disable_irq();
  
    LHL_FLASH_Unlock();

    while (StartPage <= EndPage)
    {
        pFLASH->PAGE_ADDR0 = StartPage;
        pFLASH->CMD = FLASH_CMD_PAGE_ERASE;
        __LHL_DSB
        __LHL_ISB
        
        StartPage = (FLASH_PAGE_t)((uint32_t)StartPage + FLASH_PAGE_SIZE);
        
        while (LHL_FLASH_GetFlag(FLASH_FLAG_CMDDONE) != SET)
        {
            if ((Timeout--) == 0) 
            {
                LHL_FLASH_Lock();
                __set_PRIMASK(primask_bit);
                return LHL_ERROR;                       // 循环超次数限制返回error
            }
        }
    }
    
    LHL_FLASH_Lock();

    /* Exit critical section: restore previous priority mask */
    __set_PRIMASK(primask_bit);
    
    return LHL_OK;
}

/**
  * @brief  查找Flash地址对应所在的Page，超限则返回Page0或Page29
  * @param  指定的Flash地址
  * @retval FLASH_PAGE_x，其中x从0到29
  */
FLASH_PAGE_t LHL_FLASH_GetPage(uint32_t FlashAddress)
{
    uint32_t pageAddress = FlashAddress & FLASH_PAGE_MASK;
    
    // 验证地址是否在有效范围内
    if (pageAddress < FLASH_PAGE_0)
    {
        return FLASH_PAGE_0;                            // 如果地址太小则返回Page0
    }
    else if (pageAddress >= (FLASH_PAGE_29 + FLASH_PAGE_SIZE))
    {
        return FLASH_PAGE_29;                           // 如果地址太大则返回Page29
    }
    
    return (FLASH_PAGE_t)pageAddress;
}

/**
  * @brief  以word（32位字长）为单位写入Flash
  * @note   写入Flash前，用户应保证待写入地址所在的页面已擦除
  * @note   Falsh写入过程中会关闭全局中断
  * @param  Address     定义了写入起始地址
  *         Data        32位指针，指向了待写入的数据
  *         Size        待写入数据的数量，以word（32位字长）计算
  *         Timeout     循环超时参数
  * @retval Address超范围或循环超次数返回error，之前指令未完成返回busy，写入成功返回ok
  */
LHL_StatusTypeDef LHL_FLASH_Program(uint32_t Address, uint32_t* Data, uint16_t Size, uint32_t Timeout)
{
    uint32_t primask_bit;
    
    if (Address < FLASH_START_ADDRESS) 
        return LHL_ERROR;                                                       //如果地址小于0x08000000返回error
    
    if ((Address + Size * sizeof(uint32_t)) > (FLASH_END_ADDRESS + 1U))
        return LHL_ERROR;                                                       //如果地址超出0x0801DFFF返回error
    
    /* 查询等待状态寄存器的CMDBUSY为0 */
    if (LHL_FLASH_WaitForLastOperation(Timeout) != LHL_OK)
    {
        return LHL_BUSY;                                                        
    }
       
    /* 开始关键任务，关闭中断 */
    primask_bit = __get_PRIMASK();
    __disable_irq();
    
    /* 通过AHB总线写入flash，仅支持32位的数据写入 */
    pFLASH->CTRL |= FLASH_CTRL_PROGRAM_EN_Msk;

    /* 写入数据 */
    while (Size--)
    {
        *(__RW uint32_t *)Address = *Data;        
        Address += sizeof(uint32_t);
        Data++;
    }
    __LHL_DSB
    __LHL_ISB
    
    /* 查询编程是否成功 */
    while (LHL_FLASH_GetFlag(FLASH_FLAG_PGDONE) != SET)
    {
        if ((Timeout--) == 0) 
        {
            pFLASH->CTRL &= ~FLASH_CTRL_PROGRAM_EN_Msk;
            __set_PRIMASK(primask_bit);
            return LHL_TIMEOUT;                                                 // 循环超次数限制返回timeout
        }
    }
    
    /* 编程完成后需要再配置该bit为0 */
    pFLASH->CTRL &= ~FLASH_CTRL_PROGRAM_EN_Msk;

    /* Exit critical section: restore previous priority mask */
    __set_PRIMASK(primask_bit);
    
    return LHL_OK;
}

/**
  * @brief  等待PGBUSY和CMDBUSY都清0，为1表示flash正在执行编程或擦除操作
  * @param  FLASH_FLAG_t定义的FLASH Flag标志位，可选参数：
  *         @arg    FLASH_FLAG_CMDBUSY
  *         @arg    FLASH_FLAG_PGBUSY
  *         @arg    FLASH_FLAG_CMDDONE
  *         @arg    FLASH_FLAG_PGDONE
  *         @arg    FLASH_FLAG_ERASEERROR
  *         @arg    FALSH_FLAG_VERIFYERROR
  * @retval 置1返回set，清0返回reset
  */
FlagStatus LHL_FLASH_GetFlag(FLASH_FLAG_t Flag)
{
    FlagStatus stat = RESET;
    if (pFLASH->STAT & Flag)
    {
        stat = SET;
    }
    else
    {
        stat = RESET;
    }
    
    return stat;   
}

/**
  * @brief  等待PGBUSY和CMDBUSY都清0，为1表示flash正在执行编程或擦除操作
  * @param  None
  * @retval 超时未清0返回busy，都已清0返回ok
  */
LHL_StatusTypeDef LHL_FLASH_WaitForLastOperation(uint32_t Timeout)
{
    /* Wait if any operation is ongoing */
    while (pFLASH->STAT & (FLASH_FLAG_CMDBUSY | FLASH_FLAG_PGBUSY))
    {
        if ((Timeout--) == 0) return LHL_BUSY;
    }
    
    return LHL_OK;
}

/**
  * @brief  写入0x789A0123可解锁userkey，命令完成userkey再次上锁
  * @param  None
  * @retval None
  */
void LHL_FLASH_Unlock(void)
{
    pFLASH->USERKEY = FLASH_UNLOCK_KEY;
}

/**
  * @brief  锁定Flash
  * @param  None
  * @retval None
  */
void LHL_FLASH_Lock(void)
{
    pFLASH->USERKEY = FLASH_LOCK_KEY;
}

/**
  * @brief  写入1个Word数据到指定Flash地址
  * @note   写入Flash前，用户应保证待写入的地址有效且已擦除
  * @param  Address     定义写入地址
  *         Data        32位待写入的数据
  * @retval 
  */
void LHL_FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    /* 通过AHB总线写入flash，仅支持32位的数据写入 */
    *(__RW uint32_t *)Address = Data;
        
    while ((pFLASH->STAT & FLASH_FLAG_PGDONE) == 0u);
}

/**
  * @brief  全片擦除Flash。
  * @note   页面擦除过程中会关闭全局中断。
  * @param  Timeout     循环超时参数
  * @retval 页面超范围或循环超次数返回error，之前指令未完成返回busy，擦除成功返回ok
  */
LHL_StatusTypeDef LHL_FLASH_MassErase(uint32_t Timeout)
{
    uint32_t primask_bit;
        
    if (LHL_FLASH_WaitForLastOperation(Timeout) != LHL_OK)
    {
        return LHL_BUSY;                                                        // 如果之前指令未完成返回busy
    }
       
    /* 开始关键任务，关闭中断 */
    primask_bit = __get_PRIMASK();
    __disable_irq();
  
    LHL_FLASH_Unlock();
    pFLASH->CMD = 16;
    __LHL_DSB
    __LHL_ISB
                
    while (LHL_FLASH_GetFlag(FLASH_FLAG_CMDBUSY) != RESET)
    {
        if ((Timeout--) == 0) 
        {
            LHL_FLASH_Lock();
            __set_PRIMASK(primask_bit);
            return LHL_ERROR;                       // 循环超次数限制返回error
        }
    }
    
    LHL_FLASH_Lock();

    /* Exit critical section: restore previous priority mask */
    __set_PRIMASK(primask_bit);
    
    return LHL_OK;
}

/*********************************End of File**********************************/
