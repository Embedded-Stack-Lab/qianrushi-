#include "Dri_Systick.h"

static uint8_t us_count = 0; // us延时计数器
static uint8_t ms_count = 0; // ms延时计数器

#define SYSTICK_CLK    72000000UL  // 72MHz系统时钟
#define SYSTICK_CLK_DIV8 (SYSTICK_CLK / 8)  // SysTick时钟 = 9MHz

void Dri_Systick_Init(void)
{
    debuge_printf("Dri_Systick_Init\n");
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // 选择HCLK/8作为SysTick时钟源

    //SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; // 使能SysTick中断

    us_count = SYSTICK_CLK / 8000000; // 9

    // us_count=9;

    debuge_printf("us_count = %d\n", us_count);

    // for(uint32_t i = 0; i < 1000000; i++); 

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭定时器



    //     // 必须在USART初始化之后调用！
    // debuge_printf("Dri_Systick_Init\n");
    
    // SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // HCLK/8 = 9MHz
    // us_count = SYSTICK_CLK_DIV8 / 1000000; // 9MHz / 1MHz = 9
    
    // debuge_printf("us_count = %d\n", us_count);
    
    // SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭定时器

}


void Dri_Systick_Delay_us(uint32_t us)
{

    // uint32_t temp;

    // SysTick->LOAD = us * us_count; // 设置SysTick定时器加载值为us*us_count

    // SysTick->VAL = 0x00; // 将SysTick定时器计数器设为0x00，使定时器从0开始计数

    // SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk; // 启动定时器

    // while ((temp & 0x01) && !(temp & (1 << 16))) // 等待SysTick定时器中断标志位为1
    // {
    //     temp = SysTick->CTRL; // 读取SysTick定时器状态寄存器
    // } // 检查完成的标志位

    // SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk; // 关闭定时器

    // SysTick->VAL = 0x00; // 将SysTick定时器计数器设为0x00，使定时器从0开始计数

	//debuge_printf("us_c = %d\n", us_count);
    uint32_t load = us * us_count  ;
    if (load > 0xFFFFFF)
        load = 0xFFFFFF;

    SysTick->LOAD = load;
    SysTick->VAL = 0;

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
        ;

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0;
}
void Dri_Systick_Delay_ms(uint32_t ms)
{



        while (ms--)
        Dri_Systick_Delay_us(1000);


    // uint32_t temp;

    // SysTick->LOAD = ms * ms_count; // 设置SysTick定时器加载值为ms*ms_count

    // SysTick->VAL = 0x00; // 将SysTick定时器计数器设为0x00，使定时器从0开始计数

    // SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk; // 启动定时器

    // while ((temp & 0x01) && !(temp & (1 << 16))) // 等待SysTick定时器中断标志位为1
    // {
    //     temp = SysTick->CTRL; // 读取SysTick定时器状态寄存器
    // } // 检查完成的标志位

    // SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk; // 关闭定时器

    // SysTick->VAL = 0x00; // 将SysTick定时器计数器设为0x00，使定时器从0开始计数
}
