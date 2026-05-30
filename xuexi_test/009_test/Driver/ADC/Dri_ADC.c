#include "Dri_ADC.h"

// static void Dri_ADC1_Init(void)
// {
//     ADC_InitTypeDef ADC_InitStruct;
//     // 初始化ADC
//     GPIO_InitTypeDef GPIO_InitStruct;

//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC, ENABLE);

//     GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2;

//     GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;

//     GPIO_Init(GPIOC, &GPIO_InitStruct);
    

//     RCC_ADCCLKConfig(RCC_PCLK2_Div6);

//     ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;

//     ADC_InitStruct.ADC_ScanConvMode=ENABLE;

//     ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;

//     ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;

//     ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;

//     ADC_InitStruct.ADC_NbrOfChannel=2;

//     ADC_Init(ADC1, &ADC_InitStruct);

//     ADC_RegularChannelConfig(ADC1, ADC_Channel_10,1,ADC_SampleTime_7Cycles5);

//     ADC_RegularChannelConfig(ADC1,ADC_Channel_12,2,ADC_SampleTime_7Cycles5);

//     ADC_DMACmd(ADC1, ENABLE);

// }


// static void Dri_DMA_Init(void)
// {
//     DMA_InitTypeDef DMA_InitStructure;

//     /* 1. 开启 DMA1 时钟 */
//     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

//     /* 2. 复位通道1（ADC1 固定使用 DMA1 Channel1） */
//     DMA_DeInit(DMA1_Channel1);

//     /* 3. DMA 配置 */
//     // DMA_InitStructure.DMA_PeripheralBaseAddr = pAddr;
//     // DMA_InitStructure.DMA_MemoryBaseAddr     = mAddr;
//     // DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
//     // DMA_InitStructure.DMA_BufferSize         = size;

//     DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;
//     DMA_InitStructure.DMA_MemoryBaseAddr     = 0;
//     DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
//     // DMA_InitStructure.DMA_BufferSize         = size;

//     DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
//     DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
//     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//     DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;

//     DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
//     DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
//     DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;

//     DMA_Init(DMA1_Channel1, &DMA_InitStructure);

//     /* 4. 使能 DMA */
//     DMA_Cmd(DMA1_Channel1, ENABLE);
// }

// void Dri_ADC1_DMA_Start(void)
// {
//     Dri_ADC1_Init();

//     Dri_DMA_Init();

// }

// void Dri_ADC_DMA_Start(uint32_t pAddr, uint32_t mAddr, uint16_t size)
// {
    
//         // 1. 设置DMA内存地址和传输数量
//     DMA1_Channel1->CMAR = mAddr;
//     DMA1_Channel1->CNDTR = size;
    
//     // 2. 使能DMA通道
//     DMA_Cmd(DMA1_Channel1, ENABLE);
    
//     // 3. 使能ADC并校准
//     ADC_Cmd(ADC1, ENABLE);
    
//     // 4. 执行ADC校准
//     ADC_ResetCalibration(ADC1);
//     while(ADC_GetResetCalibrationStatus(ADC1));
//     ADC_StartCalibration(ADC1);
//     while(ADC_GetCalibrationStatus(ADC1));
    
//     // 5. 启动ADC转换
//     ADC_SoftwareStartConvCmd(ADC1, ENABLE);

//     // ADC_Cmd(ADC1, ENABLE);
// }


#include "Dri_ADC.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

static void Dri_ADC1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    // 1. 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE);
    
    // 2. 配置PC0和PC2为模拟输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    // 3. 设置ADC分频（ADCCLK = PCLK2/6 = 12MHz）
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    
    // 4. 配置ADC参数
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;          // 扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   // 单次转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 2;               // 转换通道数
    ADC_Init(ADC1, &ADC_InitStructure);
    
    // 5. 配置通道采样时间
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_7Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_7Cycles5);
    
    // 6. 使能ADC DMA请求
    ADC_DMACmd(ADC1, ENABLE);
}

static void Dri_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    
    // 1. 开启DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    // 2. 配置DMA参数
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = 0;      // 后续由Dri_ADC_DMA_Start设置
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 0;          // 后续设置
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
}

void Dri_ADC1_DMA_Start(void)
{
    Dri_ADC1_Init();
    Dri_DMA_Init();
}

void Dri_ADC_DMA_Start(uint32_t memArr, uint32_t pAddr, uint8_t sizes)
{
    // 设置DMA内存地址和传输数量
    DMA1_Channel1->CMAR = memArr;
    DMA1_Channel1->CNDTR = sizes;
    
    // 使能DMA通道
    DMA_Cmd(DMA1_Channel1, ENABLE);
    
    // 使能ADC并校准
    ADC_Cmd(ADC1, ENABLE);
    
    // 执行ADC校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    
    // 启动ADC转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


static uint16_t g_arr_value = 0;  /* 自动重装载值 */

void Dri_Tim5_Init(void)
{
    // 1. 开启时钟 [ TIM5 + GPIOA ]
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 2. 配置 PA1 引脚模式 [复用推挽输出]
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. 配置定时器基本单元 (Time Base)
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period            = 100-1;    // 自动重装载值 (ARR)
    TIM_TimeBaseStructure.TIM_Prescaler         = 7200 - 1;     // 预分频器 (PSC)
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    // 4. 配置输出比较 (Output Compare) - 用于 PWM
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;    // PWM 模式 1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; // 使能输出
    TIM_OCInitStructure.TIM_Pulse        = 50;                // 比较值 (CCR2), 初始占空比
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; // 高电平为有效极性
    
    // 初始化 TIM5 Channel 2
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);

    // 5. 使能预装载寄存器 (对应寄存器版里的 OC2PE 和 ARPE)
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM5, ENABLE);
}

/**
 * @brief 开启定时器
 */
void Dri_Tim5_Start(void)
{
    TIM_Cmd(TIM5, ENABLE);
}

/**
 * @brief 停止定时器
 */
void Dri_Tim5_Stop(void)
{
    TIM_Cmd(TIM5, DISABLE);
}

/**
 * @brief 设置占空比
 * @param duty 占空比数值 (写入 CCR2)
 */
void Dri_Tim5_SetDuty(uint16_t duty)
{
    TIM_SetCompare2(TIM5, duty);

}

/**
 * @brief 获取占空比
 * @return 占空比数值 (读取 CCR2)
 */
uint16_t Dri_Tim5_GetDuty(void)
{
    return TIM_GetCapture2(TIM5);
}

