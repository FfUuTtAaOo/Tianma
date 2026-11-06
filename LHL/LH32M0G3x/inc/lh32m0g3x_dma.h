/******************************************************************************
 * 版权所有：苏州领慧立芯科技有限公司
 * Copyright (c) 2020-2025 Suzhou Legendsemi Technology Co., Ltd.
 ******************************************************************************
 * All rights reserved. Distributed under MIT license.
 * The file is encoded in UTF-8 without signature.
 * @file    lh32m0g30x_dac.h
 * @version 2025-09-22
 ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LH32M0G3x_DMA_H
#define __LH32M0G3x_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lh32m0xx_lhl.h"

/* Defines -------------------------------------------------------------------*/
/**
  * @brief  DMA传输模式
  * @note   EMLM默认始终开启，以实现多种地址调节方式
  */
typedef enum {

    DMA_MEMORY_TO_MEMORY = 0u,      /*!< 源地址和目的地址主循环内自动递增，结束后自动恢复起始地址 */
    
    DMA_PERIPH_TO_MEMORY,           /*!< 源地址次循环内递增，次/主循环结束后自动恢复起始地址；
                                     * 目的地址主循环内递增，主循环结束后自动恢复起始地址 */
                                     
    DMA_MEMORY_TO_PERIPH,           /*!< 源地址主循环内递增，主循环结束后自动恢复起始地址；
                                     * 目的地址次循环内递增，次/主循环结束后自动恢复起始地址 */
                                     
    DMA_PERIPH_TO_PERIPH,           /*!< 源地址和目的地址次循环内递增，次/主循环结束后自动恢复起始地址 */
                                     
    DMA_FIFO_TO_MEMORY,             /*!< 源地址始终固定不变；目的地址主循环内自动递增，结束后自动恢复起始地址 */
    
    DMA_MEMROY_TO_FIFO,             /*!< 源地址主循环内自动递增，结束后自动恢复起始地址；目的地址始终固定不变 */
    
} DMA_TRANS_TYPE_t;

/**
  * @brief  DMA_Memory_data_size DMA Memory data size
  * @note   为了与正数区分，负数定义为正数加1取反，实际使用时注意额外计算
  */
typedef enum {
    DMA_DATA_WIDTH_1B   = 0,        /*!< Memory data alignment : Byte, 8-bit     */
    DMA_DATA_WIDTH_2B   = 1,        /*!< Memory data alignment : HalfWord, 16-bit */
    DMA_DATA_WIDTH_4B   = 2,        /*!< Memory data alignment : Word, 32-bit     */
    DMA_DATA_WIDTH_16B  = 4,        /*!< Memory data alignment : 16-byte     */
    DMA_DATA_WIDTH_32B  = 5,        /*!< Memory data alignment : 32-byte     */
//    DMA_DATA_WIDTH_N1B  = -1,       /*!< Memory data alignment : Negtive Byte, 8-bit     */
//    DMA_DATA_WIDTH_N2B  = -2,       /*!< Memory data alignment : Negtive HalfWord, 16-bit */
//    DMA_DATA_WIDTH_N4B  = -3,       /*!< Memory data alignment : Negtive Word, 32-bit     */
//    DMA_DATA_WIDTH_N16B = -5,       /*!< Memory data alignment : Negtive 16-byte     */
//    DMA_DATA_WIDTH_N32B = -6,       /*!< Memory data alignment : Negtive 32-byte     */
} DMA_DATA_WIDTH_t;

typedef enum {
    DMA_HARDWARE_REQUEST        =   0x0u,
    DMA_SOFTWARE_REQUEST        =   0x1u,
} DMA_REQ_t;

typedef enum {
    DMA_CHANNEL_0               =   0x0u,
    DMA_CHANNEL_1               =   0x1u,
    DMA_CHANNEL_2               =   0x2u,
    DMA_CHANNEL_3               =   0x3u,
} DMA_CHANNEL_t;

typedef enum {
    TO_DMA_CHANNEL_0            =   0x0u,
    TO_DMA_CHANNEL_1            =   0x1u,
    TO_DMA_CHANNEL_2            =   0x2u,
    TO_DMA_CHANNEL_3            =   0x3u,
    TO_DMA_CHANNEL_NONE         =   0x10u,  /* 参数NONE仅供Chaining_Channel调用 */
} DMA_CHAINING_t;

typedef enum {
    DMA_BANDWIDTH_FULL          =   0x0u,
    DMA_BANDWIDTH_MEDIUM        =   0x2u,
    DMA_BANDWIDTH_LOW           =   0x3u,
} DMA_BANDWIDTH_LIMIT_t;

typedef enum {
    DMA_IT_MAJOR                =   0x2u,
    DMA_IT_HALF                 =   0x4u,
} DMA_IT_t;

typedef enum {
    DMA_DIRECT_MODE             =   0x1u,   /*!< 直接模式 */
    
    DMA_CHAINING_MODE           =   0x2u,   /*!< 链式模式 */
    
    DMA_SCATTER_GATHER_MODE     =   0x4u,   /*!< 分散聚合模式 */
} DMA_MODE_t;

typedef enum {
    DMA_CYCLIC_TRANSMISSION     =   0x0u,   /*!< 循环模式，传输Repetition次数后重新开始，
                                            * 源和目的地址指针自动恢复到初始值*/                                            
    DMA_SINGLE_TRANSMISSION     =   0x1u,   /*!< 单次模式，传输Repetition次数后自动停止，
                                            * 源和目的地址指针自动恢复到初始值 */
    DMA_INTERVAL_TRANSMISSION   =   0x10u,  /*!< 间隔模式，传输Repetition次数后重新开始，
                                            * 传输间隔由参数Interval决定，完成后源和目的地址指针自动恢复到初始值 */
} DMA_TRANS_MODE_t;

/**
  * @brief  DMA 初始化参数结构体
  */
typedef struct {
                                       
    uint32_t                Src_Address;        /*!< 源地址 */
    
    uint32_t                Dest_Address;       /*!< 目标地址 */
        
    uint16_t                Data_Size;          /*!< 以源数据宽度为单位的DMA传输数据量 Max=256Word/1024Byte */                                     

    uint16_t                Repetition;         /*!< 当DMA为重复模式下的循环次数：Min=1；Max=2^9（ELINK=1）/2^15（ELINK=0）*/
    
    int32_t                 TCD_Address;        /*!< DMA_SCATTER_GATHER_MODE下，向下一个加载的TCD链表 */
            
    FunctionalState         INT_Major;          /*!< DMA_SCATTER_GATHER_MODE下，使能或禁用主中断 */
                            
    FunctionalState         INT_Half;           /*!< DMA_SCATTER_GATHER_MODE下，使能或禁用半中断 */
                            
    FunctionalState         Auto_Start;         /*!< DMA_SCATTER_GATHER_MODE下，使能或禁用通道自启动功能*/
    
    DMA_BANDWIDTH_LIMIT_t   Bandwidth;          /*!< DMA_SCATTER_GATHER_MODE下，带宽控制位 */    
                            
    DMA_CHAINING_t          Chaining;           /*!< DMA_CHAINING_MODE下，指向下一个链式启动的通道 */
    
    DMA_TRANS_MODE_t        Trans_Mode;         /*!< DMA传输模式：单次，重复，间隔 */
    
    DMA_DATA_WIDTH_t        Data_Width;         /*!< 数据宽度 */
    
    DMA_TRANS_TYPE_t        Direction;          /*!< 传输方式：外设<->内存等六种方式，地址偏移由Direction和DataWidth共同决定 */   
    
    int16_t                 Src_Interval_Factor;    /*!< 在间隔模式下，单次DMA操作后，源地址偏移量的系数 */
    
    int16_t                 Dest_Interval_Factor;   /*!< 在间隔模式下，单次DMA操作后，目的地址偏移量的系数 */
    
} DMA_InitTypeDef;

/**
  * @brief  DMA Handle 操作句柄
  */
typedef struct {

    DMA_CHANNEL_t           Channel;            /*!< DMA Channel Instance */
    
    DMA_MODE_t              Mode;               /*!< DMA模式选择 */
    
    DMA_REQ_t               Request;            /*!< DMA请求源 */
    
    uint8_t                 TCD_Count;          /*!< DMA_SCATTER_GATHER_MODE下，TCD描述符数量 */
        
    DMA_DES_N_TypeDef*      TCD_List;           /*!< DMA_SCATTER_GATHER_MODE下，TCD描述符指针 */
    
    DMA_InitTypeDef*        TCD_Init;           /*!< DMA_SCATTER_GATHER_MODE下，DMA初始化参数结构体指针 */    
        
    DMA_InitTypeDef         Init;               /*!< DMA初始化参数结构体 */    

} DMA_HandleTypeDef;

/* Declaration ---------------------------------------------------------------*/

LHL_StatusTypeDef LHL_DMA_Init(DMA_HandleTypeDef* handle);

void LHL_DMA_Start(DMA_HandleTypeDef* handle);

void LHL_DMA_Stop(DMA_HandleTypeDef* handle);

void LHL_DMA_SetChainingChannel(DMA_HandleTypeDef* handle, DMA_CHANNEL_t ChainingChannel, FunctionalState NewState);

void LHL_DMA_SetELink(DMA_HandleTypeDef* handle, DMA_CHANNEL_t LinkedChannel, FunctionalState NewState);

void LHL_DMA_SetMLink(DMA_HandleTypeDef* handle, DMA_CHANNEL_t LinkedChannel, FunctionalState NewState);

void LHL_DMA_ITConfig(DMA_HandleTypeDef* handle, uint32_t DMA_IT, FunctionalState NewState);

DMA_IT_t LHL_DMA_GetPending(DMA_CHANNEL_t channel);

void LHL_DMA_ClearPending(DMA_CHANNEL_t channel);

LHL_StatusTypeDef LHL_DMA_GenerateTCD(DMA_HandleTypeDef* handle, DMA_InitTypeDef* DMA_Init, DMA_DES_N_TypeDef* tcd);

LHL_StatusTypeDef LHL_DMA_CopyTCD(DMA_HandleTypeDef* handle, DMA_DES_N_TypeDef* tcd);

LHL_StatusTypeDef LHL_DMA_SGAInit(DMA_HandleTypeDef* handle, DMA_DES_N_TypeDef* tcd);

uint32_t LHL_DMA_GetDestAddress(DMA_CHANNEL_t channel);

uint16_t LHL_DMA_GetCiter(DMA_CHANNEL_t channel);

uint16_t LHL_DMA_GetBiter(DMA_CHANNEL_t channel);

#ifdef __cplusplus
}
#endif

#endif

/*********************************End of File**********************************/
