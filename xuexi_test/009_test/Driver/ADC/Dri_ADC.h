#ifndef __DRI_ADC_H__
#define __DRI_ADC_H__

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "Dri_Common.h"

void Dri_ADC_Init(void);
uint16_t Dri_ADC_Read(void);

#endif
