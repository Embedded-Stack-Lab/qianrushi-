#ifndef __DRI_KEY_H__
#define __DRI_KEY_H__

#include "stm32f10x.h"

void Dri_Key_Init(void);

uint8_t Dri_Key_Scan(void);

typedef enum
{
    KEY_NONE = 0,
    KEY_ONE = 1,
    KEY_TWO = 2,
    KEY_THREE = 3,

}KEY_STATE;

#endif

  