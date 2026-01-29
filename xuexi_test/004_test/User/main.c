#include "stm32f10x.h" // Device header
#include "Dri_usart.h"
#include "Dri_ADC1.h"

// extern __IO u16 ADC_ConvertedValue;
extern __IO u16 ADC_ConvertedValue2;
float ADC_ConvertedValueLocal;

// __IO u16 ADC_TempvalueLocal;
// __IO u16 Current_Temp;
// __IO u16 v25 = 0x6E2;
// __IO u16 Avg_Slope = 0x05;

// int main()
// {

// 	SystemInit();
// 	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 打开时钟，
// 	// GPIO_InitTypeDef GPIO_InitStructure;				  // 定义结构体变量
// 	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  // 推挽输出
// 	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  // 选择引脚
// 	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  // 速度50MHz
// 	// GPIO_Init(GPIOA, &GPIO_InitStructure);				  // 初始化
// 	// GPIO_ResetBits(GPIOA, GPIO_Pin_0);					  // PA0置低
// 	Dri_usart_config();
// 	Dri_systick_init();
// 	// Dri_adc_init();
// 	Dri_adc_Temp();

// 	USART1_printf(USART1, "\r\n Print current Temperature \r\n");
// 	// USART1_printf(USART1, "\r\n This is a USART1_printf demo \r\n");
// 	// Delay_ms(20);
// 	// USART1_printf(USART1, "\r\n (" __DATE__ " - " __TIME__ ") \r\n ");

// 	while (1)
// 	{
// 		// ADC_ConvertedValueLocal = (float)ADC_ConvertedValue / 4096 * 3.3;
// 		// printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue);
// 		// printf("\r\n The current AD value = %f V \r\n", ADC_ConvertedValueLocal);

// 		ADC_TempvalueLocal = ADC_ConvertedValue2; // 读取转换的 AD 值
// 		// Delay_ms(50);																	  // 延时
// 		ADC_ConvertedValueLocal = ((v25 - ADC_TempvalueLocal) / Avg_Slope + 25);
// 		Current_Temp = (u16)ADC_ConvertedValueLocal;										   // 温度转换计算
// 		USART1_printf(USART1, "\r\n The current temperature = %03d C\r\n", (int)Current_Temp); // 10 进制显示

// 		Delay_ms(500);
// 	}
// }

float v25 = 1790.0;	   // 0x6FE 对应的十进制大约是 1790 (1.43V / 3.3V * 4096)
float Avg_Slope = 5.3; // 4.3mV / 3.3V * 4096 ≈ 5.3

int main()
{
	SystemInit();
	Dri_usart_config();
	Dri_systick_init();

	// 初始化 ADC
	Dri_adc_Temp();

	USART1_printf(USART1, "\r\n Start Temperature Measure... \r\n");

	while (1)
	{
		// 1. 获取原始 ADC 值
		u16 ad_value = ADC_ConvertedValue2;

		// 2. 打印原始值（调试用，非常重要！）
		// 如果这里打印出来是 0，说明 DMA 没工作；如果是 1700~1800 左右，说明正常
		USART1_printf(USART1, "Raw AD: %d ", (int)ad_value);

		// 3. 计算温度（使用 float 避免所有负数溢出问题）
		// 公式：Temp = (1.43 - Vsense) / 0.0043 + 25
		// 转换为 ADC 值计算：(V25_ADC - Current_ADC) / Slope + 25
		float temp_f = ((v25 - (float)ad_value) / Avg_Slope) + 25.0f;

		// 4. 打印温度
		// 注意：使用 %d 打印整数部分
		USART1_printf(USART1, "Temp: %d C\r\n", (int)temp_f);

		Delay_ms(1000);
	}
}
