#include "stm32f10x.h" // Device header
#include "Dri_usart.h"
#include "Dri_ADC1.h"

extern __IO uint16_t ADC_ConvertedValue;
float ADC_ConvertedValueLocal;

int main()
{

	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 打开时钟，
	// GPIO_InitTypeDef GPIO_InitStructure;				  // 定义结构体变量
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  // 推挽输出
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  // 选择引脚
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  // 速度50MHz
	// GPIO_Init(GPIOA, &GPIO_InitStructure);				  // 初始化
	// GPIO_ResetBits(GPIOA, GPIO_Pin_0);					  // PA0置低
	Dri_usart_config();
	Dri_systick_init();
	Dri_adc_init();

	USART1_printf(USART1, "\r\n This is a USART1_printf demo \r\n");
	Delay_ms(20);
	USART1_printf(USART1, "\r\n (" __DATE__ " - " __TIME__ ") \r\n ");

	while (1)
	{
		ADC_ConvertedValueLocal = (float)ADC_ConvertedValue / 4096 * 3.3;
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue);
		printf("\r\n The current AD value = %f V \r\n", ADC_ConvertedValueLocal);

		Delay_ms(500);
	}
}
