#include"Inf_led.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;								
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					
	GPIO_Init(GPIOA, &GPIO_InitStructure);								
}
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
