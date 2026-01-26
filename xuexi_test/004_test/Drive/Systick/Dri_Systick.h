#ifndef __DRI_SYSTICK_H__
#define __DRI_SYSTICK_H__

#include"stm32f10x.h"

void Dri_systick_init(void);

// void Dri_systick_delay_ms(uint32_t ms);

// void Dri_systick_delay_us(uint32_t us);

void TimingDelay_Decrement(void);

void Delay_us(__IO uint32_t nTime);

#endif /* __DRI_SYSTICK_H__ */