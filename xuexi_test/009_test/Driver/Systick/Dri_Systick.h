#ifndef __DRI_SYSTICK_H
#define __DRI_SYSTICK_H
#include "stm32f10x.h"
#include"system_stm32f10x.h"

void Dri_Systick_Init(void);
void Dri_Systick_Delay_us(uint32_t us);
void Dri_Systick_Delay_ms(uint32_t ms);
#endif


