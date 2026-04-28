#include "Dri_Usart.h"

void Dri_usart_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    // GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    // GPIO_InitStructure.GPIO_Speed=
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStruture;
    USART_InitStruture.USART_BaudRate            = 115200;
    USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruture.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruture.USART_Parity              = USART_Parity_No;
    USART_InitStruture.USART_StopBits            = USART_StopBits_1;
    USART_InitStruture.USART_WordLength          = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruture);
    USART_Cmd(USART1, ENABLE); //
}

