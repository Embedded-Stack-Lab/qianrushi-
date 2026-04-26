#include "Dri_Time5.h"

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

