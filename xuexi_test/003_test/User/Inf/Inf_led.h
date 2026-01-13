#ifndef __INF_LED_H__
#define __INF_LED_H__

#include"Delay.h"
void LED_Init(void);
void Led_on(u8 led_num);
void Led_off(u8 led_num);

void LED_ToggleBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* __INF_LED_H__ */
