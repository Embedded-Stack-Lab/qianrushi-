#ifndef __DRI_TIME_H__
#define __DRI_TIME_H__

#include"stm32f10x.h"
#include"stm32f10x_tim.h"
#include"Dri_Usart.h"

void Dri_Time_Init(void);

void Dri_Time_SetDuty(uint8_t duty);


#endif 
