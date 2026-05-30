#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "Common_Deebug.h"


enum KEY_NUM
{
    KEY_NONE,
    KEY_ONE,
    KEY_TWO,
    KEY_THREE,
    KEY_FOUR,
};

void Int_key_Init(void);

uint8_t Int_key_Scan(void);

#endif
