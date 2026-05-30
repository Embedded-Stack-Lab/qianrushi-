#include "Dri_Basetime.h"
volatile uint32_t sysTick=0;

void Dri_BaseTime_Init(void)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
    TIM_TimeBaseStructure.TIM_Period=1000-1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM6, TIM_FLAG_Update);

    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM6,ENABLE);
    
}

void TIM6_IRQHandler(void){
    if (TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
    {
        TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
        sysTick++;

    }
    
}

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 1. 开时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* 2. 配置 PB0 / PB1 为推挽输出 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* 3. 默认熄灭（高电平） */
    GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
}


