#include "Inf_Key.h"
void Inf_Key_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;//

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//

    GPIO_Init(GPIOF,&GPIO_InitStructure);
}

uint8_t Inf_Key_Scan(void){
    // if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
    // {
    //     Delay_ms(10);
    //     if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
    //     {
    //         // GPIO_Write();
    //         if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
    //         {
    //             if (GPIO_Pin==GPIO_Pin_8)
    //             {
    //                 Led_on(1);
    //                 return KEY_1;
    //             }
    //             if (GPIO_Pin==GPIO_Pin_9)
    //             {
    //                 Led_on(2);
    //                 return KEY_2;
    //             }
    //             if (GPIO_Pin==GPIO_Pin_10)
    //             {
    //                // Led_on(3);
	// 								GPIO_WriteBit(GPIOA,GPIO_Pin_8,1);
									
    //                 return KEY_3;
    //             }
    //             if (GPIO_Pin==GPIO_Pin_11)
    //             {
    //                 Led_off(1);
    //                 Led_off(2);
    //                 Led_off(3);
    //                 return KEY_4;
    //             }

    //         }
    //     }

        
    // }
    return KEY_OFF;

}


