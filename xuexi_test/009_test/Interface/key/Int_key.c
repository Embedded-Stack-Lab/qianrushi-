#include "Int_key.h"

void Int_key_Init(void)
{
    // GPIO_InitTypeDef(INT_KEY_GPIO_PORT, GPIO_Pin_0, GPIO_Mode_IPU, GPIO_Speed_50MHz);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

     
}

uint8_t Int_key_Scan(void)
{

    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == Bit_SET||GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_SET
    ||GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_RESET||GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == Bit_SET)
        {
            return KEY_ONE;
        }
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_SET)
        {
            return KEY_TWO;
        }       
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_RESET)
        {
            return KEY_THREE;
        }
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET)
        {
            return KEY_FOUR;
        }
    }
    else
    {
        return KEY_NONE;
    }
}
