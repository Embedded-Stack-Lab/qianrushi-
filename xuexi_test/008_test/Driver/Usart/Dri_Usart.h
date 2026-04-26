#ifndef __DRI_USART_H__
#define __DRI_USART_H__

#include "stdio.h"
#include "stdarg.h"
#include "stdlib.h"
#include "stm32f10x.h"
#include "Dri_Systick.h"
#include "stm32f10x_usart.h"

void Dri_usart_Init(void);

void USART_printf1(USART_TypeDef *USARTx, uint8_t *Data, ...);

#endif /* __DRI_USART_H__ */
