#include "Dri_key.h"


void Dri_Key_Init(void){
    GPIO_InitTypeDef GPIO_InitStruture;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
    GPIO_InitStruture.GPIO_Mode =GPIO_Mode_IPU;
    GPIO_InitStruture.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_Init(GPIOF,&GPIO_InitStruture);
         
}

uint8_t Dri_Key_Scan(void)
{
    uint8_t key_state=KEY_NONE;
    

    if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)==Bit_RESET)
    {
        key_state=KEY_ONE;
    }
    else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9)==Bit_RESET)
    {
        key_state=KEY_TWO;
    }
    else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)==Bit_RESET)
    {
        key_state=KEY_THREE;
    }

    return key_state;
}


