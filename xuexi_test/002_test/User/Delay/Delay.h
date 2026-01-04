#ifndef __DELAY_H__
#define __DELAY_H__

#include"stm32f10x.h"
void Delay_Init(void);
void Delay_ms(unsigned int nms);
void Delay_s(unsigned int s);

#endif /* __DELAY_H__ */
