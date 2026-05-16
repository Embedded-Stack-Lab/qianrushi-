#include "Dri_Systick.h"

static uint8_t us_count = 0; // us延时计数器
static uint8_t ms_count = 0; // ms延时计数器

void Dri_Systick_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // 选择HCLK/8作为SysTick时钟源

    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; // 使能SysTick中断

    SysTick->CTRL = ~SysTick_CTRL_ENABLE_Msk; // 关闭定时器
}

void Dri_Systick_Delay_us(uint32_t us)
{

    uint32_t temp;

    SysTick->LOAD = us * us_count; // 设置SysTick定时器加载值为us*us_count

    SysTick->VAL = 0x00; // 将SysTick定时器计数器设为0x00，使定时器从0开始计数

    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk; // 启动定时器

    while ((temp & 0x01)&& !(temp &(1<<16)))//等待SysTick定时器中断标志位为1
    {
        temp= SysTick->CTRL;//读取SysTick定时器状态寄存器
    }//检查完成的标志位


    SysTick->CTRL &=~SysTick_CTRL_CLKSOURCE_Msk;//关闭定时器

    SysTick->VAL=0x00;//将SysTick定时器计数器设为0x00，使定时器从0开始计数

  }
void Dri_Systick_Delay_ms(uint32_t ms){
    uint32_t temp;

    SysTick->LOAD = ms * ms_count; // 设置SysTick定时器加载值为ms*ms_count

    SysTick->VAL= 0x00;//将SysTick定时器计数器设为0x00，使定时器从0开始计数

    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk; // 启动定时器

    while ((temp & 0x01)&& !(temp &(1<<16)))//等待SysTick定时器中断标志位为1
    {
        temp= SysTick->CTRL;//读取SysTick定时器状态寄存器
    }//检查完成的标志位

    SysTick->CTRL &=~SysTick_CTRL_CLKSOURCE_Msk;//关闭定时器

    SysTick->VAL=0x00;//将SysTick定时器计数器设为0x00，使定时器从0开始计数

}
