#ifndef __DRI_TIME_H__
#define __DRI_TIME_H__

#include"stm32f10x.h"
#include"stm32f10x_tim.h"
#include"Dri_Usart.h"

void Dri_Time_Init(void);

void Dri_TIM_SetDuty(uint8_t duty);

void Dri_Time_PWMInit(void);
 
void Dri_Time_LedInit(void);

uint8_t Dri_TIM_GetDuty(void);

void Driver_Tim5_Init(void);

void Driver_Tim5_Start(void);

void Driver_Tim5_SetDuty(uint16_t duty);

#endif 
