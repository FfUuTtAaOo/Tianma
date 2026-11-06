/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_dac.c
 * @version 2025-09-29
 ******************************************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  Direct模式：初始化DMA寄存器
  * @param  handle      指向包含DMA配置参数的结构体指针 
  * @retval LHL_OK：DMA配置成功
  */
LHL_StatusTypeDef LHL_DMA_Init(DMA_HandleTypeDef* handle)
{
    DMA_DES_N_TypeDef* reg = 0;

    /* 初始化必须确认开启DMA时钟 */
    RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN_Msk, ENABLE);
    
    if (pDMA_CONTROL->DMA_CR & DMA_CR_ACTIVE_Msk) return LHL_BUSY;
    
    //if (handle->Init.Data_Size > UINT32_MAX / (1u << handle->Init.Src_Data_Width)) return LHL_ERROR;
    
    //if ((handle->Init->Repetition < 1)||(handle->Init->Data_Size < 1)) return LHL_ERROR;
    
    /* 清除所有DMA请求位和标志位 */
    pDMA_CONTROL->DMA_CERQ = handle->Channel;
    pDMA_CONTROL->DMA_CINT = handle->Channel;
    pDMA_CONTROL->DMA_CERR = handle->Channel;
    
    /* 默认设置EMLM始终开启 */
    pDMA_CONTROL->DMA_CR = DMA_CR_EMLM_Msk;
    
    if (handle->Mode == DMA_SCATTER_GATHER_MODE)    /* 分散聚合模式，根据初始化参数生成TCD描述符 */
    {
        if ((handle->TCD_Init == NULL) || (handle->TCD_List == NULL)) return LHL_ERROR;
        
        for (uint8_t i=0;i<handle->TCD_Count;i++)
        {
            /* 根据Init结构体参数生成TCD描述符 */
            if ((handle->TCD_Init[i].Repetition < 1)||(handle->TCD_Init[i].Data_Size < 1)) return LHL_ERROR;
            
            LHL_DMA_GenerateTCD(handle, &handle->TCD_Init[i], &handle->TCD_List[i]);
        }
    
        /* 装载首个TCD描述如到DMA物理寄存器 */
        LHL_DMA_CopyTCD(handle, &handle->TCD_List[0]);
    }
    else                                            /* 直接和链式模式，初始化参数直接装载进DMA硬件寄存器 */
    {
        if ((handle->Init.Repetition < 1)||(handle->Init.Data_Size < 1)) return LHL_ERROR;
        
        /* 获取DMA指定Channel的物理地址 */
        reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * handle->Channel);
    
        /* 直接写入DMA寄存器 */
        LHL_DMA_GenerateTCD(handle, &handle->Init, reg);    
    }
        
    return LHL_OK;
}

///**
//  * @brief  SGA模式：初始化DMA寄存器
//  * @param  tcd      指向包含DMA链表描述符的指针 
//  * @retval LHL_OK：DMA配置成功
//  */
//LHL_StatusTypeDef LHL_DMA_SGAInit(DMA_HandleTypeDef* handle, DMA_DES_N_TypeDef* tcd)
//{
//    /* 必须开启DMA时钟 */
//    RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN_Msk, ENABLE);
//    
//    if (pDMA_CONTROL->DMA_CR & DMA_CR_ACTIVE_Msk) return LHL_BUSY;
//    
//    /* 清除所有DMA请求位和标志位 */
//    pDMA_CONTROL->DMA_CERQ = handle->Channel;
//    pDMA_CONTROL->DMA_CINT = handle->Channel;
//    pDMA_CONTROL->DMA_CERR = handle->Channel;
//    
//    /* 默认设置EMLM始终开启 */
//    pDMA_CONTROL->DMA_CR = DMA_CR_EMLM_Msk;    
//    
//    /* 根据Init结构体参数生成TCD描述符 */
//    for (uint8_t i=0;i<handle->Count;i++)
//    {
//        LHL_DMA_GenerateTCD(handle, &handle->Init[i], &tcd[i]);
//        if (i>0)
//        {
//            /* 自动置位START */
//            tcd[i].DMA_DESN_CSR |= DMA_CSR_START_Msk;
//        }
//    }
//    
//    /* 装载首个TCD描述如到DMA物理寄存器 */
//    LHL_DMA_CopyTCD(handle, &tcd[0]);
//    
//    return LHL_OK;
//}

LHL_StatusTypeDef LHL_DMA_GenerateTCD(DMA_HandleTypeDef* handle, DMA_InitTypeDef* DMA_Init, DMA_DES_N_TypeDef* tcd)
{
    uint16_t srcWidthABS, destWidthABS;
    int16_t srcOffset, destOffset;
    int32_t srcBytes, destBytes;
    uint32_t nBytes;
    
    /* 2025-11-17 Discard 计算带符号偏移量 */
//    if (DMA_Init->Dest_Data_Width >= 0)
//    {
//        destWidthABS = (uint16_t)(DMA_Init->Dest_Data_Width);
//        destOffset = (int16_t)(1u << destWidthABS);
//    }
//    else
//    {
//        destWidthABS = (uint16_t)(-DMA_Init->Dest_Data_Width-1);
//        destOffset = (int16_t)(0xffffu << destWidthABS);
//    }
//    if (DMA_Init->Src_Data_Width >= 0)
//    {
//        srcWidthABS = (uint16_t)(DMA_Init->Src_Data_Width);
//        srcOffset  = (int16_t)(1u << srcWidthABS);
//    }
//    else
//    {
//        srcWidthABS = (uint16_t)(-DMA_Init->Src_Data_Width-1);
//        srcOffset  = (int16_t)(0xffffu << srcWidthABS);
//    }
    destWidthABS = (uint16_t)(DMA_Init->Data_Width);
    srcWidthABS = (uint16_t)(DMA_Init->Data_Width);
    destOffset = (int16_t)(1u << destWidthABS);
    srcOffset  = (int16_t)(1u << srcWidthABS);
    
    /* 写入起始地址和数据宽度 */
    tcd->DMA_DESN_SADDR = (uint32_t)DMA_Init->Src_Address;
    tcd->DMA_DESN_DADDR = (uint32_t)DMA_Init->Dest_Address;
    tcd->DMA_DESN_ATTR = (uint16_t)((srcWidthABS << DMA_ATTR_SSIZE_Pos) | destWidthABS);
    
    /* 小循环传输的源和目的地址增量 */
    if (DMA_Init->Trans_Mode != DMA_INTERVAL_TRANSMISSION)
    {
        tcd->DMA_DESN_SOFF = srcOffset;                         
        tcd->DMA_DESN_DOFF = destOffset; 
    }
    else
    {
        tcd->DMA_DESN_SOFF = srcOffset * (int16_t)DMA_Init->Src_Interval_Factor;                         
        tcd->DMA_DESN_DOFF = destOffset * (int16_t)DMA_Init->Dest_Interval_Factor; 
    }
    
    /* 小循环传输数据量（以Byte为单位） */
    nBytes = (uint32_t)abs(srcOffset * (int32_t)DMA_Init->Data_Size);
    srcBytes = tcd->DMA_DESN_SOFF * (int32_t)DMA_Init->Data_Size;
    destBytes = tcd->DMA_DESN_DOFF * (int32_t)DMA_Init->Data_Size;

    switch (DMA_Init->Direction)
    {
        /* Reserved */
        case DMA_FIFO_TO_MEMORY:
        /* Reserved */
        case DMA_MEMROY_TO_FIFO:
        /* 内存->内存 */
        case DMA_MEMORY_TO_MEMORY:
            /* 最高32位长的小循环传输数据量NBYTES */
            //!!!!!!!!!!!!!!!!!!!2025-11-8 EMLM设为始终开启
            /* 单次DMA小循环传输的字节数量（以源为准，BYTE为计量单位）*/
            tcd->DMA_DESN_NBYTES_MLNO = (nBytes & 0x3FFF);            
            /* 大循环传输完成后回到起始地址 */
            tcd->DMA_DESN_SLAST = -(srcBytes * (int32_t)DMA_Init->Repetition);
            tcd->DMA_DESN_DLASTSGA = -(destBytes * (int32_t)DMA_Init->Repetition); 
            break;            
        /* 内存->外设 */
        case DMA_MEMORY_TO_PERIPH:
            //pDMA_CONTROL->DMA_CR |= DMA_CR_EMLM_Msk;  
            /* 启用目的地址小循环调整；
             * 小循环结束时目的地址返回起始地址；源地址保持增长；
             * 最高10位长的小循环传输数据量（以源为准）。 */            
            tcd->DMA_DESN_NBYTES_MLNO = DMA_NBYTES_MLOFFYES_DMLOE_Msk | \
                                (((uint32_t)(-destBytes) & 0xFFFFF)<< DMA_NBYTES_MLOFFYES_MLOFF_Pos) | \
                                (nBytes & 0x3FF);                               
            /* 大循环传输完成后回到起始地址 */
            tcd->DMA_DESN_SLAST = -(srcBytes * (int32_t)DMA_Init->Repetition); 
            tcd->DMA_DESN_DLASTSGA = -(destBytes);
            break;            
        /* 外设->内存 */
        case DMA_PERIPH_TO_MEMORY:
            //pDMA_CONTROL->DMA_CR |= DMA_CR_EMLM_Msk; 
            /* 启用源地址小循环调整；
             * 小循环结束时源地址返回起始地址；目的地址保持增长；
             * 最高10位长的小循环传输数据量（以源为准）。 */            
            tcd->DMA_DESN_NBYTES_MLNO = DMA_NBYTES_MLOFFYES_SMLOE_Msk | \
                                (((uint32_t)(-srcBytes) & 0xFFFFF)<< DMA_NBYTES_MLOFFYES_MLOFF_Pos) | \
                                (nBytes & 0x3FF);
            /* 大循环传输完成后回到起始地址 */
            tcd->DMA_DESN_SLAST = -(srcBytes);
            tcd->DMA_DESN_DLASTSGA = -(destBytes * (int32_t)DMA_Init->Repetition);    
            break; 
        /* 外设->外设 */
        case DMA_PERIPH_TO_PERIPH:
            /* 启用源和目的地址小循环调整；这种方式要求源外设和目的外设地址增量都是正或者都是负；
             * 小循环结束时源和目的地址返回起始地址；
             * 最高10位长的小循环传输数据量（以源为准）。 */            
            tcd->DMA_DESN_NBYTES_MLNO = DMA_NBYTES_MLOFFYES_DMLOE_Msk | DMA_NBYTES_MLOFFYES_SMLOE_Msk | \
                                (((uint32_t)(-srcBytes) & 0xFFFFF)<< DMA_NBYTES_MLOFFYES_MLOFF_Pos) | \
                                (nBytes & 0x3FF); 
                                
            /* 大循环传输完成后回到起始地址 */
            tcd->DMA_DESN_SLAST = -(srcBytes);
            tcd->DMA_DESN_DLASTSGA = -(destBytes);
            break;
    }
    
    tcd->DMA_DESN_BITER_ELINKYES = DMA_Init->Repetition;  // MAX 15位（ELINK=0）或 MAX 9位（ELINK=1）
    tcd->DMA_DESN_CITER_ELINKYES = DMA_Init->Repetition;
    
    tcd->DMA_DESN_CSR = 0;
    switch (handle->Mode)
    {
        case DMA_DIRECT_MODE:
            /* 普通模式，清零ELINK */
            tcd->DMA_DESN_CSR = (uint16_t)((DMA_Init->Trans_Mode & 0x1) << DMA_CSR_DREQ_Pos);
            tcd->DMA_DESN_BITER_ELINKYES &= ~(DMA_BITER_ELINKYES_ELINK_Msk | DMA_BITER_ELINKYES_LINKCH_Msk);
            tcd->DMA_DESN_CITER_ELINKYES &= ~(DMA_CITER_ELINKYES_ELINK_Msk | DMA_CITER_ELINKYES_LINKCH_Msk);
            break;
        case DMA_CHAINING_MODE:
            /* 链式模式，清零DONE，设置Major Link */            
            tcd->DMA_DESN_CSR = DMA_CSR_MAJORELINK_Msk | \
                            (uint16_t)((DMA_Init->Trans_Mode & 0x1) << DMA_CSR_DREQ_Pos) | \
                            (uint16_t)(DMA_Init->Chaining << DMA_CSR_MAJORLINKCH_Pos); 
                            
            /* 设置Minor Link Biter */
            tcd->DMA_DESN_BITER_ELINKYES &= ~(DMA_BITER_ELINKYES_ELINK_Msk | DMA_BITER_ELINKYES_LINKCH_Msk);
    
            tcd->DMA_DESN_BITER_ELINKYES |= DMA_BITER_ELINKYES_ELINK_Msk | \
                            (uint16_t)(DMA_Init->Chaining << DMA_BITER_ELINKYES_LINKCH_Pos);
                    
            /* 设置Minor Link Citer */
            tcd->DMA_DESN_CITER_ELINKYES &= ~(DMA_CITER_ELINKYES_ELINK_Msk | DMA_CITER_ELINKYES_LINKCH_Msk);
            
            tcd->DMA_DESN_CITER_ELINKYES |= DMA_CITER_ELINKYES_ELINK_Msk | \
                            (uint16_t)(DMA_Init->Chaining << DMA_CITER_ELINKYES_LINKCH_Pos);
            break;
        case DMA_SCATTER_GATHER_MODE:
            /* 分散聚合模式，清零DONE，设置TCD */
            tcd->DMA_DESN_CSR = DMA_CSR_ESG_Msk | \
                            (uint16_t)((DMA_Init->Trans_Mode & 0x1) << DMA_CSR_DREQ_Pos) | \
                            (uint16_t)(DMA_Init->INT_Half << DMA_CSR_INTHALF_Pos) | \
                            (uint16_t)(DMA_Init->INT_Major << DMA_CSR_INTMAJOR_Pos) | \
                            (uint16_t)(DMA_Init->Auto_Start << DMA_CSR_START_Pos);
            /* 指向下一个TCD链表 */
            tcd->DMA_DESN_DLASTSGA = DMA_Init->TCD_Address;
            /* 处理链式模式 */
            tcd->DMA_DESN_BITER_ELINKYES &= ~(DMA_BITER_ELINKYES_ELINK_Msk | DMA_BITER_ELINKYES_LINKCH_Msk);   
            tcd->DMA_DESN_CITER_ELINKYES &= ~(DMA_CITER_ELINKYES_ELINK_Msk | DMA_CITER_ELINKYES_LINKCH_Msk);
            if (DMA_Init->Chaining != TO_DMA_CHANNEL_NONE)
            {        
                tcd->DMA_DESN_BITER_ELINKYES |= DMA_BITER_ELINKYES_ELINK_Msk | \
                            (uint16_t)(DMA_Init->Chaining << DMA_BITER_ELINKYES_LINKCH_Pos);                    
            
                tcd->DMA_DESN_CITER_ELINKYES |= DMA_CITER_ELINKYES_ELINK_Msk | \
                            (uint16_t)(DMA_Init->Chaining << DMA_CITER_ELINKYES_LINKCH_Pos);
                            
                tcd->DMA_DESN_CSR |= DMA_CSR_MAJORELINK_Msk | (uint16_t)(DMA_Init->Chaining << DMA_CSR_MAJORLINKCH_Pos);  
            }
            break;
    }
        
    return LHL_OK;
}

/* 提供直接写入DMA寄存器的功能 */
LHL_StatusTypeDef LHL_DMA_CopyTCD(DMA_HandleTypeDef* handle, DMA_DES_N_TypeDef* tcd)
{
    __RW DMA_DES_N_TypeDef* reg = 0;

    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + sizeof(DMA_DES_N_TypeDef) * handle->Channel);    
    
    /* Copy TCD mapping into hardware DES register */
    reg->DMA_DESN_SADDR             = tcd->DMA_DESN_SADDR;
    reg->DMA_DESN_SOFF              = tcd->DMA_DESN_SOFF;
    reg->DMA_DESN_ATTR              = tcd->DMA_DESN_ATTR;
    reg->DMA_DESN_NBYTES_MLNO       = tcd->DMA_DESN_NBYTES_MLNO;
    reg->DMA_DESN_SLAST             = tcd->DMA_DESN_SLAST;
    reg->DMA_DESN_DADDR             = tcd->DMA_DESN_DADDR;
    reg->DMA_DESN_DOFF              = tcd->DMA_DESN_DOFF;
    reg->DMA_DESN_CITER_ELINKYES    = tcd->DMA_DESN_CITER_ELINKYES;
    reg->DMA_DESN_DLASTSGA          = tcd->DMA_DESN_DLASTSGA;
    /* Clear DONE bit first, otherwise ESG cannot be set */
    reg->DMA_DESN_CSR               = 0;
    reg->DMA_DESN_CSR               = tcd->DMA_DESN_CSR;
    reg->DMA_DESN_BITER_ELINKYES    = tcd->DMA_DESN_BITER_ELINKYES;

    return LHL_OK;
}


void LHL_DMA_ITConfig(DMA_HandleTypeDef* handle, uint32_t DMA_IT, FunctionalState NewState)
{
    DMA_DES_N_TypeDef* reg = 0;
    
    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * handle->Channel);
    
    /* 使能或禁用指定中断 */
    if (NewState == ENABLE)
    {
        reg->DMA_DESN_CSR |= DMA_IT;
    }
    else
    {
        reg->DMA_DESN_CSR &= DMA_IT;
    }
}



void LHL_DMA_Start(DMA_HandleTypeDef* handle)
{    
    pDMA_CONTROL->DMA_SERQ = handle->Channel;
    
    if (handle->Request == DMA_SOFTWARE_REQUEST)
    {
        pDMA_CONTROL->DMA_SSRT = handle->Channel;
    }
}

void LHL_DMA_Stop(DMA_HandleTypeDef* handle)
{
    pDMA_CONTROL->DMA_CERQ = handle->Channel;
}

void LHL_DMA_ClearPending(DMA_CHANNEL_t channel)
{
    pDMA_CONTROL->DMA_CINT = channel;
}

DMA_IT_t LHL_DMA_GetPending(DMA_CHANNEL_t channel)
{
    DMA_DES_N_TypeDef* reg;
    uint32_t citer, biter;
    
    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * channel);
    
    if (reg->DMA_DESN_CSR & DMA_CSR_INTHALF_Msk)
    {    
        citer = reg->DMA_DESN_CITER_ELINKYES & DMA_CITER_ELINKYES_CITER_Msk;
        
        biter = reg->DMA_DESN_BITER_ELINKYES & DMA_BITER_ELINKYES_BITER_Msk;
        
        if (citer <= biter/2)
        {
            return DMA_IT_HALF;
        }
        else
        {
            return DMA_IT_MAJOR;
        }
    }
    else
    {
        return DMA_IT_MAJOR;
    }
}

void LHL_DMA_SetChainingChannel(DMA_HandleTypeDef* handle, DMA_CHANNEL_t ChainingChannel, FunctionalState NewState)
{
    DMA_DES_N_TypeDef* reg = 0;
    
    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * handle->Channel);
    
    /* 设置Minor Link Biter */
    reg->DMA_DESN_BITER_ELINKYES &= ~(DMA_BITER_ELINKYES_ELINK_Msk | DMA_BITER_ELINKYES_LINKCH_Msk);
    
    reg->DMA_DESN_BITER_ELINKYES |= (NewState << DMA_BITER_ELINKYES_ELINK_Pos) | \
                    (uint16_t)(ChainingChannel << DMA_BITER_ELINKYES_LINKCH_Pos);
                    
    /* 设置Minor Link Citer */
    reg->DMA_DESN_CITER_ELINKYES &= ~(DMA_CITER_ELINKYES_ELINK_Msk | DMA_CITER_ELINKYES_LINKCH_Msk);
    
    reg->DMA_DESN_CITER_ELINKYES |= (NewState << DMA_CITER_ELINKYES_ELINK_Pos) | \
                    (uint16_t)(ChainingChannel << DMA_CITER_ELINKYES_LINKCH_Pos);
                    
    /* 设置Major Link */
    reg->DMA_DESN_CSR &= ~(DMA_CSR_MAJORELINK_Msk | DMA_CSR_MAJORLINKCH_Msk);
    
    reg->DMA_DESN_CSR |= (NewState << DMA_CSR_MAJORELINK_Pos) | \
                    (uint16_t)(ChainingChannel << DMA_CSR_MAJORLINKCH_Pos);                 
}


void LHL_DMA_SetELink(DMA_HandleTypeDef* handle, DMA_CHANNEL_t LinkedChannel, FunctionalState NewState)
{
    DMA_DES_N_TypeDef* reg = 0;
    
    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * handle->Channel);
    
    reg->DMA_DESN_BITER_ELINKYES &= ~(DMA_BITER_ELINKYES_ELINK_Msk | DMA_BITER_ELINKYES_LINKCH_Msk);
    
    reg->DMA_DESN_BITER_ELINKYES |= (NewState << DMA_BITER_ELINKYES_ELINK_Pos) | \
                    (uint16_t)(LinkedChannel << DMA_BITER_ELINKYES_LINKCH_Pos);
    
    reg->DMA_DESN_CITER_ELINKYES &= ~(DMA_CITER_ELINKYES_ELINK_Msk | DMA_CITER_ELINKYES_LINKCH_Msk);
    
    reg->DMA_DESN_CITER_ELINKYES |= (NewState << DMA_CITER_ELINKYES_ELINK_Pos) | \
                    (uint16_t)(LinkedChannel << DMA_CITER_ELINKYES_LINKCH_Pos);                             
}

void LHL_DMA_SetMLink(DMA_HandleTypeDef* handle, DMA_CHANNEL_t LinkedChannel, FunctionalState NewState)
{
    DMA_DES_N_TypeDef* reg = 0;
    
    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * handle->Channel);
    
    reg->DMA_DESN_CSR &= ~(DMA_CSR_MAJORELINK_Msk | DMA_CSR_MAJORLINKCH_Msk);
    
    reg->DMA_DESN_CSR |= (NewState << DMA_CSR_MAJORELINK_Pos) | \
                    (uint16_t)(LinkedChannel << DMA_CSR_MAJORLINKCH_Pos);
}

uint32_t LHL_DMA_GetDestAddress(DMA_CHANNEL_t channel)
{
    DMA_DES_N_TypeDef* reg = 0;
    
    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * channel);
    
    return reg->DMA_DESN_DADDR;
}

uint16_t LHL_DMA_GetCiter(DMA_CHANNEL_t channel)
{
    DMA_DES_N_TypeDef* reg = 0;
    
    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * channel);
    
    return reg->DMA_DESN_CITER_ELINKYES & 0x1FF;
}

uint16_t LHL_DMA_GetBiter(DMA_CHANNEL_t channel)
{
    DMA_DES_N_TypeDef* reg = 0;
    
    /* 获取DESn地址 */
    reg = (DMA_DES_N_TypeDef *)(DMA_DES_N_BASE + 32u * channel);
    
    return reg->DMA_DESN_BITER_ELINKYES & 0x1FF;
}

/*********************************End of File**********************************/
