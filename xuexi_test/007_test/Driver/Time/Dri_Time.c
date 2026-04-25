#include"Dri_Time.h"


 static uint16_t g_current_pulse =  0; 

void Dri_Time_LedInit(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
}


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
   Dri_Time_LedInit();
    TIM_OCInitTypeDef TIM_OClnitStructure;
    TIM_OClnitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OClnitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OClnitStructure.TIM_Pulse=0;
    TIM_OClnitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);  
    // TIM_ARRPreConfig(TIM2,ENABLE);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_OC1Init(TIM2,&TIM_OClnitStructure);
    TIM_Cmd(TIM2,ENABLE);
     

}


uint8_t Dri_TIM_GetDuty(void)
{
    return (uint8_t)((g_current_pulse*100)/999);
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

// void TIM2_IRQHandler(void)
// {
//     if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//     {   
        

//         TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

//         //tim2_1s_flag=1;
//     }
// }



void Driver_Tim5_Init(void)
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
    TIM_TimeBaseStructure.TIM_Period            = 100 - 1;    // 自动重装载值 (ARR)
    TIM_TimeBaseStructure.TIM_Prescaler         = 72 - 1;     // 预分频器 (PSC)
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    // 4. 配置输出比较 (Output Compare) - 用于 PWM
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;    // PWM 模式 1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; // 使能输出
    TIM_OCInitStructure.TIM_Pulse        = 100;                // 比较值 (CCR2), 初始占空比
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
void Driver_Tim5_Start(void)
{
    TIM_Cmd(TIM5, ENABLE);
}

/**
 * @brief 停止定时器
 */
void Driver_Tim5_Stop(void)
{
    TIM_Cmd(TIM5, DISABLE);
}

/**
 * @brief 设置占空比
 * @param duty 占空比数值 (写入 CCR2)
 */
void Driver_Tim5_SetDuty(uint16_t duty)
{
    TIM_SetCompare2(TIM5, duty);
}

