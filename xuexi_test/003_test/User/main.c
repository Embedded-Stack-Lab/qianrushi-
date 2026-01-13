#include "Inf/Inf_key.h"
#include "Inf/Inf_led.h"
#include"stm32f10x_gpio.h"
int main()
{

    LED_Init();
    Delay_Init();
    SystemInit();
    Inf_Key_Init();

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
         //Inf_Key_Checkswitch(GPIOF, GPIO_Pin_9);
        // Inf_Key_Checkswitch(GPIOF, GPIO_Pin_10);
        // Inf_Key_Checkswitch(GPIOF, GPIO_Pin_11);

        if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)==SET){
            Delay_ms(15);
            GPIO_WriteBit(GPIOA,GPIO_Pin_8,1);
        }

     
    }
}
