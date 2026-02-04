#ifndef __DRI_RTC_H__
#define __DRI_RTC_H__

#include "stm32f10x.h"
#include "stm32f10x_rtc.h"

void Dri_rtc_configuration(void);

void Dri_rtc_TimeShow(void);

extern int TimeDisplay;

void NVIC_Configuration(void);

#endif /* __DRI_RTC_H__ */
