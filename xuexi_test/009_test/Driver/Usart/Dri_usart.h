#ifndef __DRI_USART_H
#define __DRI_USART_H

#include "stm32f10x.h"
#include"stm32f10x_usart.h"

void Dri_USART_Init(void);
void Dri_USART_SendByte(uint8_t byte);
uint8_t Dri_USART_ReceiveByte(void);

#endif

