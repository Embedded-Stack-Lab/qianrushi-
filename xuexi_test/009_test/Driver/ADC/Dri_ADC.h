#ifndef __DRI_ADC_H__
#define __DRI_ADC_H__

#include "stm32f10x.h"
#include "stm32f10x_adc.h"  
//#include "Dri_Common.h"


void Dri_Tim5_Init(void);

void Dri_Tim5_Start(void);

void Dri_Tim5_SetDuty(uint16_t duty);

void Dri_Tim5_Stop(void);

uint16_t Dri_Tim5_GetDuty(void);


void Dri_ADC_DMA_Start(uint32_t memArr, uint32_t pAddr, uint8_t sizes);
void Dri_ADC1_DMA_Start(void);

#define LED1_ON()   GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define LED1_OFF()  GPIO_SetBits(GPIOB, GPIO_Pin_0)

#define LED2_ON()   GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define LED2_OFF()  GPIO_SetBits(GPIOB, GPIO_Pin_1)

#endif
