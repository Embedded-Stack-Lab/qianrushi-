#include "Inf_uart.h"

void Inf_uart_config(void)
{

    GPIO_InitTypeDef GPIO_Initstructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_9;

    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;

    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_Initstructure);

    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10;

    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_Initstructure);

    USART_InitStructure.USART_BaudRate = 115200;

    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    USART_InitStructure.USART_StopBits = USART_StopBits_1;

    USART_InitStructure.USART_Parity = USART_Parity_No;

    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

uint8_t Inf_uart_sendchar(USART_TypeDef *USARTx, uint8_t ch)
{

    // 等待发送数据寄存器为空
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        ;

    // 发送字符
    USART_SendData(USARTx, ch);

    return ch; // 返回发送的字符
}

uint8_t Inf_uart_receive(USART_TypeDef *USARTx)
{

    // 等待接收到数据
    while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
        ;

    // 返回接收到的数据
    return (uint8_t)USART_ReceiveData(USARTx);
}

void Inf_uart_sendstring(USART_TypeDef *USARTx, const char *str)
{
        // 遍历字符串直到遇到结束符'\0'
    while(*str != '\0')
    {
        Inf_uart_sendchar(USARTx, (uint8_t)*str);
        str++;
    }

}
