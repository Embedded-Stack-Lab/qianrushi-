#include"Delay.h"
int fac_ms; // 毫秒延时倍数
void Delay_Init(void)
{

	SysTick
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // 选择时钟源为HCLK/8
	fac_ms = SystemCoreClock / 8000;					  // 每毫秒的计数次数
}

void Delay_ms(unsigned int ms)
{
	unsigned int temp;
	SysTick->LOAD = ms * fac_ms;			  // 设定计数器的值
	SysTick->VAL = 0x00;					  // 清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开始计数
	do
	{
		temp = SysTick->CTRL; // 读取当前的计数值
	} while ((temp & 0x01) && !(temp & (1 << 16))); // 等待时间到达
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
	SysTick->VAL = 0X00;					   // 清空计数器
}

void Delay_s(unsigned int s)
{
	unsigned int i;
	for (i = 0; i < s; i++)
	{
		Delay_ms(1000);
	}
}
