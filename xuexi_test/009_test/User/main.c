#include "stm32f10x.h"
#include "string.h"
#include "Dri_usart.h"
#include "Common_Deebug.h"

uint16_t touch_data_start[10] = {0};

uint16_t touch_data_read[5] = {0x06, 0x08};

void EXTI_PA0_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 1. 使能时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    /* 2. 配置 PA0 为输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 3. 连接 EXTI0 到 PA0 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    /* 4. 配置 EXTI0 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* 5. 配置 NVIC */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

int main()
{

    // uint8_t recv_data;

    // 初始化USART
    // Dri_USART_Init();
    Common_Debug_Init();
    EXTI_PA0_Init();

    debuge_printf("%d", GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));

    debuge_printf("opkj");
    while (1)
    {
        // 循环发送测试字符串
        // char *test_str = "Hello, UART!\r\n";
        // for(uint8_t i = 0; test_str[i] != '\0'; i++)
        // {
        //     // Dri_USART_SendByte(test_str[i]);
        //     debuge_printf("%c",test_str[i]);
        // }

        // // 延时约1秒（简单延时）
        // for(uint32_t delay = 0; delay < 72000000; delay++);

        // if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_SET)
        // {
        //     debuge_printf("touch");
        //     // 处理触摸事件
        //     debuge_printf("%d",touch_data_start[0]);
        //     for (uint8_t i = 0; i < 5; i++)
        //     {
        //        debuge_printf("%x02",touch_data_read[i]);
        //        debuge_printf("%d", GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9));
               
        //     }
            
           
        // }
    }
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        /* 用户处理代码 */
        // ...

        /* 清除中断标志位（必须） */
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
