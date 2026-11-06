#include "lh32_adc.h"

/* Private Define ------------------------------------------------------------*/
#define TCD_COUNT 2

/* Global Variable -----------------------------------------------------------*/
DMA_HandleTypeDef hDMA0;

/* Dual ADC data buffer
 * 注意: 必须是全局变量, 不能是 adc_init() 的局部变量。
 * DMA 会持续向该地址写数据, 若放在栈上, 函数返回后栈空间被复用,
 * 采样结果会丢失/破坏调用栈。 */
ADC_DoubleData_t dADCBuffer;

/* 每完成一组双通道采样 +1(在 DMA1_CH0_IRQHandler 中自增) */
volatile uint32_t g_adc_seq;

/* LHL_DMA_Init(&hDMA0) 的返回值(供 Debug 观察):
 *   0 = LHL_OK    -> ch0 配置成功
 *   2 = LHL_BUSY  -> 调用时 DMA 控制器已 ACTIVE(有通道在跑), ch0 根本没配上,
 *                    说明还有人在 adc_init() 之前就 LHL_DMA_Start 了 */
volatile uint32_t g_dma0_init_ret;

void adc_init(void)
{
    REF_InitTypeDef REF_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    DMAMUX_InitTypeDef DMAMUX_InitStructure;
    static DMA_InitTypeDef DMA_InitStructure[TCD_COUNT];       /* Multiple initialization structure parameters of the decentralized aggregation mode */
    static DMA_DES_N_TypeDef TCD_Quene[TCD_COUNT] __ALIGN(32); /* The DMA TCD descriptor must be 32-bit aligned.*/

    REF_InitStructure.VREF = REF_INTERNAL_2P5V;
    REF_InitStructure.VREF_Boost = DISABLE;
    REF_InitStructure.VDRIVE = REF_INTERNAL_OFF;                    // Disable VDrive output
    LHL_REF_Init(&REF_InitStructure);

    /* Initialize ADC0 and ADC1, set synchronization, and enable DMA */
    ADC_InitStructure.AINP = ADC0_AINP_AIN0;                            // ADC0 = AIN0 = FZ
    ADC_InitStructure.AINM = ADC0_AINP_AIN1;
    ADC_InitStructure.FS = ADC_SPS_50;                              // Output rate
    ADC_InitStructure.PGA = SENSOR_PGA;                             // 与外部调理电路输出范围匹配(见 lh32_adc.h)
    ADC_InitStructure.Code = ADC_CODE_BIPOLAR;                      // 力是双向的, 必须用双极性码(单极性会削掉负向力)
    ADC_InitStructure.Mode = ADC_MODE_CONTINUOUS_CONVERSION;        // Continuous conversion mode
    ADC_InitStructure.Trigger = ADC_TRIGGER_SOFTWARE;               // software trigger
    ADC_InitStructure.ReferenceSelect = ADC_REF_REFP_to_REFN;       // Internal benchmark
    ADC_InitStructure.REF_BUFP = ENABLE;                            // Enable reference buffer
    ADC_InitStructure.REF_BUFM = ENABLE;
    ADC_InitStructure.REF_Precharge = DISABLE;
    ADC_InitStructure.Reference = ADC_VREF_MV;
    LHL_ADC_Init(ADC_0, &ADC_InitStructure);

    ADC_InitStructure.AINP = ADC0_AINP_AIN2;                            // ADC1 = AIN1 = FX
    ADC_InitStructure.AINM = ADC0_AINP_AIN3;
    LHL_ADC_Init(ADC_1, &ADC_InitStructure);                        // Apart from the channel, the configurations of ADC1 and ADC0 are exactly the same.

    LHL_ADC_SetSync(ENABLE);

    LHL_ADC_DMACmd(ADC_0, ENABLE);                                  // Enable the DMA function of ADC0

    /* Configure DMAUX: The request source for DMA channel 0 is from ADC0. */
    DMAMUX_InitStructure.DMA_Channel = DMA_CHANNEL_0;
    DMAMUX_InitStructure.Request_Source = REQUEST_SOURCE_ADC0;
    DMAMUX_InitStructure.Periodic_Trigger = DISABLE;
    DMAMUX_InitStructure.Cmd = ENABLE;
    LHL_DMAMUX_Init(&DMAMUX_InitStructure);

    /* Configure DMA channel 0: Transfer data from ADC0 and ADC1 */
    hDMA0.Channel = DMA_CHANNEL_0;
    hDMA0.Mode = DMA_SCATTER_GATHER_MODE;
    hDMA0.Request = DMA_HARDWARE_REQUEST;
    hDMA0.TCD_Count = TCD_COUNT;                                        // Two TCDs are respectively used for ADC0 and ADC1.
    hDMA0.TCD_List = TCD_Quene;                                         // TCD linked list
    hDMA0.TCD_Init = DMA_InitStructure;                                 // TCD initialization queue

    DMA_InitStructure[0].Direction = DMA_PERIPH_TO_MEMORY;              // TCD0 is used for ADC0
    DMA_InitStructure[0].Src_Address = (uint32_t)(&pADC->ADC_DATA_0);
    DMA_InitStructure[0].Dest_Address = (uint32_t)&dADCBuffer.ADC0_Data;// Point to the cache area ADC0
    DMA_InitStructure[0].Data_Width = DMA_DATA_WIDTH_4B;
    DMA_InitStructure[0].Data_Size = 1;
    DMA_InitStructure[0].Repetition = 1;
    DMA_InitStructure[0].Trans_Mode = DMA_CYCLIC_TRANSMISSION;
    DMA_InitStructure[0].TCD_Address = (int32_t)&TCD_Quene[1];          // After completion, load TCD1
    DMA_InitStructure[0].Auto_Start = DISABLE;
    DMA_InitStructure[0].INT_Major = DISABLE;
    DMA_InitStructure[0].INT_Half = DISABLE;
    DMA_InitStructure[0].Chaining = TO_DMA_CHANNEL_NONE;

    DMA_InitStructure[1].Direction = DMA_PERIPH_TO_MEMORY;              // TCD1 is used for ADC1
    DMA_InitStructure[1].Src_Address = (uint32_t)(&pADC->ADC_DATA_1);
    DMA_InitStructure[1].Dest_Address = (uint32_t)&dADCBuffer.ADC1_Data;// Point to the cache area ADC1
    DMA_InitStructure[1].Data_Width = DMA_DATA_WIDTH_4B;
    DMA_InitStructure[1].Data_Size = 1;
    DMA_InitStructure[1].Repetition = 1;
    DMA_InitStructure[1].Trans_Mode = DMA_CYCLIC_TRANSMISSION;
    DMA_InitStructure[1].TCD_Address = (int32_t)&TCD_Quene[0];          // After completion, load TCD0
    DMA_InitStructure[1].Auto_Start = ENABLE;
    DMA_InitStructure[1].INT_Major = ENABLE;                            // Trigger the DMA0 main interrupt upon completion
    DMA_InitStructure[1].INT_Half = DISABLE;
    DMA_InitStructure[1].Chaining = TO_DMA_CHANNEL_NONE;
    g_dma0_init_ret = (uint32_t)LHL_DMA_Init(&hDMA0);

    /* LHL_DMA_Init 在控制器 ACTIVE 时直接返回 LHL_BUSY(2) 且什么都不配,
     * 此时 ch0 的 TCD 还是复位值, 再 Start 也只会空转/报配置错误,
     * 所以失败就直接返回, 让问题暴露在 g_dma0_init_ret 上。 */
    if (g_dma0_init_ret != (uint32_t)LHL_OK)
    {
        return;
    }

    /* 使能 DMA 通道0 中断: TCD1 已置 INT_Major, 但 CPU 侧 NVIC 也必须打开 */
    NVIC_ClearPendingIRQ(DMA1_CH0_IRQn);
    NVIC_EnableIRQ(DMA1_CH0_IRQn);
    NVIC_SetPriority(DMA1_CH0_IRQn, 0);                                            // 设置NVIC优先级为1

    /* 使能 DMA 通道0 的请求 (ADC0 触发请求源) */
    LHL_DMA_Start(&hDMA0);

    /* 启动 ADC 转换: 软件触发 + 连续转换模式, 启动后即持续采样。
     * 不调用则 ADC 永远不转换, DMA 也就永远收不到请求。 */
    adc_start();
}

/**
  * @brief  启动 ADC0/ADC1 转换
  * @param  None
  * @retval None
  */
void adc_start(void)
{
    LHL_ADC_Start(ADC_0);
    LHL_ADC_Start(ADC_1);
}
