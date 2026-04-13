#ifndef __INF_KEY_H__
#define __INF_KEY_H__

#include "stm32f10x.h"

typedef enum
{
    KEY_ON ,
    KEY_OFF
}KEY_STATUS;

typedef enum
{
    KEY_1 = 1,
    KEY_2,
    KEY_3,
    KEY_4,
} KEY_NUM;

void Inf_Key_Init(void);
uint8_t Inf_Key_Scan(void);

#endif

