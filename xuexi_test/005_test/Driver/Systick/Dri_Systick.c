#include"Dri_Systick.h"

static u8 fac_us=0;//us延时倍数
static u16 fac_ms=0;//ms延时倍数

void Dri_Systick_Init(void){

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//选择时钟源HCLK/8
    SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//开启中断
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//先关闭定时器
    // while ();
    
}
void Dri_Systick_Delay_us(u32 us){
      u32 temp;
    // 第1步：设置定时器要计数多少个数（延时时间 × 系数）
    SysTick->LOAD = us * fac_us;
    
    // 第2步：清空计数器（重新开始计数）
    SysTick->VAL = 0x00;
    
    // 第3步：启动定时器（开始工作）
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    
    // 第4步：等待（一直检查定时器是否计数完成）

     while ((temp & 0x01) && !(temp & (1 << 16)))
     {
        temp = SysTick->CTRL;  // 读取定时器状态
    } // 检查完成标志
    
    // 第5步：定时器计数完成了，关闭它
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    
    // 第6步：清空计数器（清理现场）
    SysTick->VAL = 0x00;
}
void Dri_Systick_Delay_ms(u32 ms){
    u32 temp;
    // 第1步：设置定时器要计数多少个数（延时时间 × 系数）
    SysTick->LOAD = ms * fac_ms;
    
    // 第2步：清空计数器（重新开始计数）
    SysTick->VAL = 0x00;
    
    // 第3步：启动定时器（开始工作）
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    
    // 第4步：等待（一直检查定时器是否计数完成）
     while ((temp & 0x01) && !(temp & (1 << 16)))
     {
        temp = SysTick->CTRL;  // 读取定时器状态
    }// 检查完成标志
    
    // 第5步：定时器计数完成了，关闭它
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    
    // 第6步：清空计数器（清理现场）
    SysTick->VAL = 0x00;
}
void Dri_Systick_Handler(void);

