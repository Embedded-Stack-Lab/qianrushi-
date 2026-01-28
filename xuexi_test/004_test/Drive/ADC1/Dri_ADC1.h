#ifndef __DRI_ADC1_H__
#define __DRI_ADC1_H__

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Dri_adc_init(void);
extern __IO u16 ADC_ConvertedValue;

#endif /* __DRI_ADC1_H__ */