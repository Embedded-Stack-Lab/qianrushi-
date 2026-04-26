#ifndef __DRI_TIME5_H__
#define __DRI_TIME5_H__

#include"stm32f10x.h"
#include"stm32f10x_tim.h"
#include"Dri_Usart.h"

void Dri_Tim5_Init(void);

void Dri_Tim5_Start(void);

void Dri_Tim5_SetDuty(uint16_t duty);

void Dri_Tim5_Stop(void);





#endif
