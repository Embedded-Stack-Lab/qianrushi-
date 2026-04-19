#include"Dri_Time.h"


static uint16_t g_current_pulse = 500; 

void Dri_Time_Init(void){
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 999;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void Dri_Time_PWMInit(void){
    Dri_Time_Init();  
    TIM_OCInitTypeDef TIM_OClnitStructure;
    TIM_OClnitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OClnitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OClnitStructure.TIM_Pulse=500;
    TIM_OClnitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);  
    // TIM_ARRPreConfig(TIM2,ENABLE);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_OC1Init(TIM2,&TIM_OClnitStructure);
    TIM_Cmd(TIM2,ENABLE);

}
uint8_t Dri_TIM_GetDuty(void)
{
    return (g_current_pulse*100)/999;
}
void Dri_TIM_SetDuty(uint8_t duty)
{

    uint16_t new_pulse;
    if (duty>100)
    {
        duty=100;
    }
    new_pulse =(duty*999)/100;
    TIM_SetCompare1(TIM2,new_pulse);
     g_current_pulse=new_pulse;
}

extern uint8_t tim2_1s_flag = 1;  

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {   
        

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        //tim2_1s_flag=1;
    }
}

