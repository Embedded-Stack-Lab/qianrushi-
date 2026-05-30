#include "app.h"

void app_Init(void)
{
    Dri_Systick_Init();
    Common_Debug_Init();
    Dri_Tim5_Init();
    Dri_ADC1_Init();
    Dri_Tim5_Start();
    Dri_Tim5_SetDuty(100);
}

uint16_t data[2] = {0};

float v10 = 0.0f;
float v12 = 0.0f;
float duty = 0.0f;

void app_LED_PWM(void)
{

    Dri_ADC1_DMA_Start();

    Dri_ADC_DMA_Start((uint32_t)data, (uint32_t)&ADC1->DR, 2);

  v10= 3.3 * data[0] / 4095, v12=3.3 * data[1] / 4095;

  duty=(v10-v12)/v10;
   
  Dri_Tim5_SetDuty(duty*100);
}

