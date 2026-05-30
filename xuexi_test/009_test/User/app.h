#ifndef __APP_H__
#define __APP_H__   
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "Common_Deebug.h"
#include "Int_key.h"
#include "Int_Led.h"
#include"Dri_Systick.h"
#include "Dri_ADC.h"

// #include "Int_Led_pwm.h"

void app_Init(void);

#endif
