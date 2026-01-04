#include"Inf_led.h"

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

void Led_off(u8 led_num)
{
	switch (led_num)
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
void Led_on(u8 led_num)
{
	switch (led_num)
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
