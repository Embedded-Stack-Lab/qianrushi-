#ifndef __DRI_SYSTICK_H__
#define __DRI_SYSTICK_H__

#include "stm32f10x.h"

void Dri_Systick_Init(void);
void Dri_Systick_Delay_us(u32 us);
void Dri_Systick_Delay_ms(u32 ms);
void Dri_Systick_Handler(void);



#endif /* __DRI_SYSTICK_H__ */