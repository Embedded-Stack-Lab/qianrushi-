#include "stm32f10x.h"
#include "string.h"
#include "Dri_usart.h"
#include "Common_Deebug.h"
#include "Dri_ADC.h"
#include "Dri_Basetime.h"
#include "Dri_Systick.h"
#include "app.h"

uint16_t touch_data_start[10] = {0};

uint16_t touch_data_read[5] = {0x06, 0x08};

// uint16_t data[2] = {0};

 int main()
{

    app_Init();
  	//debuge_printf(".....");  
	
    while (1)
    {
        app_LED_PWM();
			//debuge_printf(".....");
        // Dri_BaseTime_DelayMs(10);
        Dri_Systick_Delay_ms(100);
    }
    
}



// void EXTI_PA0_Init(void)
// {
//     GPIO_InitTypeDef GPIO_InitStructure;
//     EXTI_InitTypeDef EXTI_InitStructure;
//     NVIC_InitTypeDef NVIC_InitStructure;

//     /* 1. 使能时钟 */
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

//     /* 2. 配置 PA0 为输入 */
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOA, &GPIO_InitStructure);

//     /* 3. 连接 EXTI0 到 PA0 */
//     GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

//     /* 4. 配置 EXTI0 */
//     EXTI_InitStructure.EXTI_Line = EXTI_Line0;
//     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿
//     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//     EXTI_Init(&EXTI_InitStructure);

//     /* 5. 配置 NVIC */
//     NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//     NVIC_Init(&NVIC_InitStructure);
// }

// int main()
// {
//     Common_Debug_Init();

//     // uint8_t recv_data;

//     // Dri_Systick_Init();
//     Dri_BaseTime_Init();
//     // 初始化USART
//     // Dri_USART_Init();

//     // EXTI_PA0_Init();
//     // Dri_ADC1_DMA_Start();

//     // Dri_ADC_DMA_Start((uint32_t)data, (uint32_t)&ADC1->DR, 2);

//     // debuge_printf("%d", GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));

//     // printf("%d\n", SystemCoreClock);
//     // debuge_printf("opkj");
//     while (1)
//     {
//         // 循环发送测试字符串
//         // char *test_str = "Hello, UART!\r\n";
//         // for(uint8_t i = 0; test_str[i] != '\0'; i++)
//         // {
//         //     // Dri_USART_SendByte(test_str[i]);
//         //     debuge_printf("%c",test_str[i]);
//         // }

//         // // 延时约1秒（简单延时）
//         // for(uint32_t delay = 0; delay < 72000000; delay++);

//         // if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_SET)
//         // {
//         //     debuge_printf("touch");
//         //     // 处理触摸事件
//         //     debuge_printf("%d",touch_data_start[0]);
//         //     for (uint8_t i = 0; i < 5; i++)
//         //     {
//         //        debuge_printf("%x02",touch_data_read[i]);
//         //        debuge_printf("%d", GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9));

//         //     }

//         if (sysTick >= 1000)
//         {
//             debuge_printf("sysTick = %d\n", sysTick);
//             sysTick = 0;
//             // 每 1s 执行一次
//         }

//         debuge_printf("v10=%.2f,v12=%.2f", 3.3 * data[0] / 4095, 3.3 * data[1] / 4095);
//         // Dri_Systick_Delay_ms(1000);
//         //     debuge_printf("Loop...\r\n");
//         //  Dri_Systick_Delay_ms(1000);  // 先注释掉延时，测试是否能循环打印
//         // for(uint32_t i = 0; i < 1000000; i++);  // 使用简单延时

//         // }
//     }
// }

// void EXTI0_IRQHandler(void)
// {
//     if (EXTI_GetITStatus(EXTI_Line0) != RESET)
//     {
//         /* 用户处理代码 */
//         // ...

//         /* 清除中断标志位（必须） */
//         EXTI_ClearITPendingBit(EXTI_Line0);
//     }
// }
