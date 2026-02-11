#ifndef __INF_IIC_H__
#define __INF_IIC_H__

#include"stm32f10x.h"
#include"stm32f10x_i2c.h"
#include "Dri_Systick.h"

#define SDA_H GPIO_SetBits(GPIOB, GPIO_Pin_7)             // SDA置高
#define SDA_L GPIO_ResetBits(GPIOB, GPIO_Pin_7)           // SDA置低
#define SCL_H GPIO_SetBits(GPIOB, GPIO_Pin_6)             // SCL置高
#define SCL_L GPIO_ResetBits(GPIOB, GPIO_Pin_6)           // SCL置低
#define SDA_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) // 读SDA线状态
#define SCL_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) // 读SCL线状态
#define DELAY_IIC Dri_Systick_Delay_us(10);               // 延时10us来传输数据

void Inf_IIC_Init(void);

void Inf_IIC_Start(void);

void Inf_IIC_Stop(void);

void Inf_IIC_ACK(void);

void Inf_IIC_NACK(void);

uint8_t Inf_I2C_ReceiveByte(void);

void Inf_I2C_SendByte(uint8_t byte);

// 主设备向外部从设备发送数据,主设备需要等待人家应答
uint8_t Inf_I2C_WaitAck(void);

#endif /* __INF_IIC_H__ */