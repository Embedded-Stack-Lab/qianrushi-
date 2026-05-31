#include "app.h"

#define ADC_WINDOW 8

void app_Init(void)
{

  Common_Debug_Init();

  Dri_Systick_Init();
  Dri_Tim5_Init();
  Dri_Tim5_Start();
  Dri_ADC1_DMA_Start();
  Dri_Tim5_SetDuty(100);
  Dri_ADC1_DMA_Start();
  // debuge_printf("app_Init..\n");
}

uint16_t data[2] = {0};
uint16_t adc_data[ADC_WINDOW] = {0};
static uint32_t adc1_sum = 0;
static uint8_t adc_pos = 0;
static uint8_t adc_cnt = 0;

float v10 = 0.0f;
float v12 = 0.0f;
float duty = 0.0f;

static float Filter_ADC1(uint16_t raw)
{
  if (adc_cnt < ADC_WINDOW)
  {
    adc_data[adc_pos] = raw;
    adc_pos++;
    adc_cnt++;
    adc1_sum += raw;
    return (adc1_sum * 3.3f) / (adc_cnt * 4095.0f);
  }
  adc1_sum -= adc_data[adc_pos];
  adc_data[adc_pos] = raw;
  adc1_sum += raw;

  adc_pos++;
  if (adc_pos >= ADC_WINDOW)
    adc_pos = 0;

  return (adc1_sum * 3.3f) / (ADC_WINDOW * 4095.0f);
}

void app_LED_PWM(void)
{

  /* DMA 只启动一次，不要在循环里 Start */
  // Dri_ADC1_DMA_Start();
 
 Dri_ADC_DMA_Start((uint32_t)data, (uint32_t)&ADC1->DR, 2);
  v12 = Filter_ADC1(data[1]);

  if (v12 < 1.5f)
  {
    duty = 0.0f;
  }
  else if (v12 < 2.8f)
  {
    duty = (v12 - 1.5f) / 1.3f * 100.0f; // 1.5~2.8 → 0%~100%
  }
  else
  {
    duty = 100.0f;
  }

  if (duty > 100.0f)
    duty = 100.0f;
  if (duty < 0.0f)
    duty = 0.0f;

  // Dri_Tim5_SetDuty((uint16_t)duty);
  Dri_Systick_Delay_ms(100);

  debuge_printf("v12=%.2f,duty=%.2f\n", v12, duty);
}

// void app_LED_PWM(void)
// {

//   Dri_ADC_DMA_Start((uint32_t)data, (uint32_t)&ADC1->DR, 2);

//   v10 = 3.3 * data[0] / 4095, v12 = 3.3 * data[1] / 4095;

//   if (v12)
//   {
//     if (v12 < 1.5)
//     {
//       duty = 0;
//     }
//     else if (1.5 < v12 < 2.8)
//     {
//       duty = (v12 - 1.5) / 1.5;
//       duty = duty * 100;
//     }
//     else if (v12 < 2.8)
//     {
//       duty = 50;
//     }
//   }

//   Dri_Tim5_SetDuty(duty * 100);

//   debuge_printf("v10=%.2f,v12=%.2f,duty=%.2f\n", v10, v12, duty);
//   Dri_Systick_Delay_ms(500);
//   // duty=(v10-v12)/v10;

//   // Dri_Tim5_SetDuty(duty*100);

//   // debuge_printf("duty: %f\n", duty);
// }
