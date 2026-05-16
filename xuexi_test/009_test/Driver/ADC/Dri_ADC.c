#include "Dri_ADC.h"

void Dri_ADC_Init(void)
{
    ADC_InitTypeDef ADC_InitStruct;
    // 初始化ADC
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2;

    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;

    GPIO_Init(GPIOC, &GPIO_InitStruct);
    

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;

    ADC_InitStruct.ADC_ScanConvMode=ENABLE;

    ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;

    ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;

    ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;

    ADC_InitStruct.ADC_NbrOfChannel=2;

    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_10,1,ADC_SampleTime_55Cycles5);

    ADC_RegularChannelConfig(ADC1,ADC_Channel_12,2,ADC_SampleTime_55Cycles5);

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);

    while(ADC_GetCalibrationStatus(ADC1));

    ADC_StartCalibration(ADC1);

    while(ADC_GetCalibrationStatus(ADC1));

}


static void Dri_DMA_Init(uint32_t pAddr, uint32_t mAddr, uint16_t size)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* 1. 开启 DMA1 时钟 */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* 2. 复位通道1（ADC1 固定使用 DMA1 Channel1） */
    DMA_DeInit(DMA1_Channel1);

    /* 3. DMA 配置 */
    DMA_InitStructure.DMA_PeripheralBaseAddr = pAddr;
    DMA_InitStructure.DMA_MemoryBaseAddr     = mAddr;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = size;

    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;

    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    /* 4. 使能 DMA */
    DMA_Cmd(DMA1_Channel1, ENABLE);
}

uint16_t Dri_ADC_Read(void)
{
    // 读取ADC值
    return 0;
}


