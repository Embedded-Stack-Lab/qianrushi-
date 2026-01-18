#include "Dri_exti.h"

/*
* NVIC 配置函数
*
*/

static void NVIC_Configuration(void){
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 配置 EXTI9_5 中断 */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//使能 EXTI9_5 中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;//抢占优先级 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;//响应优先级 0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断通道
    NVIC_Init(&NVIC_InitStructure);//根据 NVIC_InitStructure 结构体初始化 NVIC
    
}

void Dri_EXT8_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    // 使能 GPIOF 和 AFIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_AFIO,ENABLE);

    // 配置 PF8 为上拉输入
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOF,&GPIO_InitStructure);//初始化 GPIOF8
   
    // 连接 EXTI8 到 PF8
    NVIC_Configuration();

    /*
    * 配置 EXTI Line8
    *   选择 EXTI8
    *   中断模式
    *  下降沿触发
    *  使能 EXTI8
    *  GPIO_EXTILineConfig();
    *    
    *   
    */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource8);
    EXTI_InitStructure.EXTI_Line=EXTI_Line8;//选择 EXTI8
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;//使能 EXTI8     
    EXTI_Init(&EXTI_InitStructure);//根据 EXTI_InitStructure 结构体初始化 EXTI8

    // GPIO_InitTypeDef GPIO_InitStructure;
    // EXTI_InitTypeDef EXTI_InitStructure;
    // NVIC_InitTypeDef NVIC_InitStructure;

    // // Enable clock for GPIOF and AFIO
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_AFIO, ENABLE);

    // // Configure PF8 as input floating
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    // GPIO_Init(GPIOF, &GPIO_InitStructure);

    // // Connect EXTI Line8 to PF8
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource8);

    // // Configure EXTI Line8
    // EXTI_InitStructure.EXTI_Line = EXTI_Line8;
    // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Trigger on falling edge
    // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    // EXTI_Init(&EXTI_InitStructure);

    // // Enable and set EXTI Line8 Interrupt to the lowest priority
    // NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_Init(&NVIC_InitStructure);
}


