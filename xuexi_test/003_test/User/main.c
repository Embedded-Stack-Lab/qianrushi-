#include "Inf/Inf_key.h"
#include "Inf/Inf_led.h"
#include "stm32f10x_gpio.h"
#include "common_debug.h"
int main()
{

    Common_debug_init();
    LED_Init();
    Delay_Init();
    SystemInit();
    Inf_Key_Init();
    
    // Inf_uart_sendchar(USART1,'o');
	
	
	// Inf_uart_sendstring(USART1,"JLKJKLJ;L");

    //  Inf_uart_receive(USART1);

    debug_printf("opipio--");
    Led_off(1);
    Led_off(2);
    Led_off(3);
    while (1)
    {

        //    for (int i = 1; i < 4; i++) {

        //     // Led_on(i);
        //     // Delay_s(1);
        //     Led_off(i);
        // }
        // Inf_Key_Checkswitch(GPIOF, GPIO_Pin_8);
        // Inf_Key_Checkswitch(GPIOF, GPIO_Pin_9);
        // Inf_Key_Checkswitch(GPIOF, GPIO_Pin_10);
        // Inf_Key_Checkswitch(GPIOF, GPIO_Pin_11);

        if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == RESET)
        {

            Delay_ms(15);
           
            GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);
					 debug_printf("°´¼ü°´ÏÂ-----\r\n");
        }
    }
}
