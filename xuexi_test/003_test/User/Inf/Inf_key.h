#ifndef __INF_KEY_H__
#define __INF_KEY_H__

#include"stm32f10x.h"
#include"Delay.h"
#include"Inf_led.h"
enum KEY_STATUS{

    KEY_ON=1,
    KEY_OFF

};


enum KEY_NUM{
    KEY_1=1,
    KEY_2,
    KEY_3,
    KEY_4,
}
;



void Inf_Key_Init(void);
// void Inf_Key_Checkswitch(void);
int8_t Inf_Key_Checkswitch(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

#endif /* __INF_KEY_H__ */
