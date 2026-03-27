#include "stm32f10x.h" // Device header
#include "Dri_eeprom.h"
#include "Dri_usart.h"

/* * main.c
 *
 *  Created on: 2026年2月3日ADC转换
int main()
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 打开时钟，
    GPIO_InitTypeDef GPIO_InitStructure;				  // 定义结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  // 推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  // 选择引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  // 速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);				  // 初始化
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);					  // PA0置低

    while (1)
    {
    }
}
*/

uint8_t g_arr[100];

int main()
{
    SystemInit(); // 系统初始化

    Dri_EEPROM_Init();

    Dri_usart_Init();

	
	//USART_Sendch(USART1,'a');
	//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	

    // USART_printf1(USART1, "\r\n This is a usart1 printf demo \r\n");

    Dri_EEPROM_WritePage(0, "sdhogosjg!", 15);

    Dri_EEPROM_ReadString(0, g_arr, 15);

    USART_printf1(USART1, "%s\n", g_arr);

    while (1) {
    }
}
