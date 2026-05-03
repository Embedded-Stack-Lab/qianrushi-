#include "Dri_key.h"

void Dri_Key_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruture;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruture.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIOF, &GPIO_InitStruture);
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruture.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_Init(GPIOF, &GPIO_InitStruture);
}

uint8_t Dri_Key_Scan(void)
{
    static uint8_t key_release = 1;
    uint8_t key_state = KEY_NONE;

    uint8_t is_pass = (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == Bit_RESET || GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9) == Bit_RESET ||
                       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10) == Bit_SET || GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_11) == Bit_SET);

    if (key_release == 1 && is_pass)
    {
        Dri_Systick_Delay_ms(20);
        key_release = 0;

        if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == Bit_RESET)
        {
            key_state = KEY_ONE;
        }
        else if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9) == Bit_RESET)
        {
            key_state = KEY_TWO;
        }
        else if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10) == Bit_SET)
        {
            key_state = KEY_THREE;
            // Dri_Systick_Delay_ms(20);
        }
        else if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_11) == Bit_SET)
        {
            key_state = KEY_FOUR;
        }
    }
    else if (!is_pass)
    {
        key_release = 1;
    }

    // debuge_printfln("key_state=%d",key_state);

    return key_state;
}
