#ifndef __DRI_ADC_H__
#define __DRI_ADC_H__

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
//#include "Dri_Common.h"

void Dri_ADC_DMA_Start(uint32_t memArr, uint32_t pAddr, uint8_t sizes);
void Dri_ADC1_DMA_Start(void);

#endif
