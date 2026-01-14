#ifndef __INF_UART_H__
#define __INF_UART_H__
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

void Inf_uart_config(void);

uint8_t Inf_uart_sendchar(USART_TypeDef *USARTx, uint8_t ch);

uint8_t Inf_uart_receive(USART_TypeDef *USARTx);

void Inf_uart_sendstring(USART_TypeDef *USARTx, const char *str);

#endif /* __INF_UART_H__ */
