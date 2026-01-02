#include "stm32f10x.h" // Device header

int fac_ms; // 毫秒延时倍数
void Delay_init(void)
{

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

void LED_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				// 打开时钟
	GPIO_InitTypeDef GPIO_InitStructure;								// 定义结构体变量
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					// 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8; // 选择引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					// 速度50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);								// 初始化
}

// void Led1_on(void)
// {
// 	GPIO_SetBits(GPIOA, GPIO_Pin_0);
// }
// void Led1_off(void)
// {
// 	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
// }
// void Led2_on(void)
// {
// 	GPIO_SetBits(GPIOA, GPIO_Pin_1);
// }
// void Led2_off(void)
// {
// 	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
// }
// void Led3_on(void)
// {
// 	GPIO_SetBits(GPIOA, GPIO_Pin_8);
// }
// void Led3_off(void)
// {
// 	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
// }

void Led_off(int led)
{
	switch (led)
	{
	case 1:
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		break;
	case 2:
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		break;
	case 3:
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		break;

	default:
		break;
	}
}
void Led_on(int led)
{
	switch (led)
	{
	case 1:
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		break;
	case 2:
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		break;
	case 3:
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		break;

	default:
		break;
	}
}

int main()
{

	LED_Init();
	Delay_init();



	while (1)
	{
		for (int i = 1; i < 4; i++)
		{
		
			
			Led_on(i);
			Delay_s(1);
			Led_off(i);
		}
		
	}
}
