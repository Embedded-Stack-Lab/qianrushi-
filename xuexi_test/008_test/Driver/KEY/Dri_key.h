#ifndef __DRI_KEY_H__
#define __DRI_KEY_H__

#include "stm32f10x.h"
#include "Com_Debug.h"
#include"Dri_Systick.h"

void Dri_Key_Init(void);

uint8_t Dri_Key_Scan(void);

typedef enum
{
    KEY_NONE = 0,
    KEY_ONE ,
    KEY_TWO ,
    KEY_THREE ,
    KEY_FOUR,

}KEY_STATE;

#endif

  