#ifndef __INF_IIC_H__
#define __INF_IIC_H__

#include"stm32f10x.h"
#include"stm32f10x_i2c.h"
#include "Dri_Systick.h"

void Inf_IIC_Init(void);

void Inf_IIC_Start(void);

void Inf_IIC_Stop(void);

void Inf_IIC_ACK(void);

void Inf_IIC_NACK(void);

uint8_t Dri_I2C_ReceiveCyte(void);

void Dri_I2C_SendByte(uint8_t byte);

#endif /* __INF_IIC_H__ */