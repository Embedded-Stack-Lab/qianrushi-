#include "Dri_Systick.h"

static __IO uint32_t TimingDelay = 0; // 这里定义一个全局变量，用于延时函数

void Dri_systick_init(void)
{
    if (SysTick_Config(SystemCoreClock / 1000)) // 每1ms中断一次
    {
        while (1)
            ;
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 先关闭滴答定时器
}

// void Dri_systick_delay_us(uint32_t us)
// {
//     SysTick->LOAD=us* (SystemCoreClock/10000) -1; // 设置重装载寄存器
//     SysTick->VAL=0; // 清空当前值寄存器
//     SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; // 使能滴答定时器
//     while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)==0); // 等待计数到达0
//     SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; // 关闭滴答定时器

// }

void Delay_us(__IO uint32_t nTime)
{
    TimingDelay = nTime;

    // 使能 SysTick 计数（中断已经在 SysTick_Config 里使能过）
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    // 等待 TimingDelay 被减到 0
    while (TimingDelay != 0)
        ;

    // 用完就关掉 SysTick
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void Delay_ms(__IO uint32_t nTime)
{
    while (nTime--)
    {
        Delay_us(100); // 100 × 10us = 1000us = 1ms
    }
}

/*
 * 在中断中调用，每进一次 SysTick 中断（10us），TimingDelay--。
 */
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}
