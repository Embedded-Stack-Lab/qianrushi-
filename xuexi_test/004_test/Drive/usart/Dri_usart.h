#ifndef __DRI_USART_H__
#define __DRI_USART_H__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stdarg.h"

void Dri_usart_config(void);
void USART1_printf(USART_TypeDef *USARTx, uint8_t *Data, ...);

#endif /* __DRI_USART_H__ */
