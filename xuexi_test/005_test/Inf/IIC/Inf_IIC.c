#include "Inf_IIC.h"



void Inf_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruture;
    RCC_APB2PeriphClockCmd(GPIOB, ENABLE);                // 开时钟
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_Out_OD;       // 开漏输出
    GPIO_InitStruture.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 选择引脚
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;      // 速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStruture);                 // 初始化
}

void Inf_IIC_Start(void)
{
    SDA_H;
    SCL_H;
    DELAY_IIC;

    SDA_L;
    DELAY_IIC;
}

void Inf_IIC_Stop(void)
{
    SDA_L;
    SCL_H;
    DELAY_IIC;

    SDA_H;
    DELAY_IIC;
}

void Inf_IIC_ACK(void)
{
    // 主设备接收应答信号
    SDA_H;
    SCL_L;
    DELAY_IIC;

    SDA_L;
    DELAY_IIC;

    SCL_H;
    DELAY_IIC;

    SCL_L;
    DELAY_IIC;

    SDA_H;
    DELAY_IIC;
}

void Inf_IIC_NACK(void)
{

    SDA_H;
    SCL_L;
    DELAY_IIC;

    SCL_L;
    DELAY_IIC;
}

void Inf_I2C_SendByte(uint8_t byte)
{

    for (uint8_t i = 0; i < 8; i++)
    {
        SDA_L;
        SCL_L;
        DELAY_IIC;

        if (byte & 0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }
        DELAY_IIC;
        SCL_L;
        DELAY_IIC;

        SCL_L;
        DELAY_IIC;

        byte <<= 1;
    }
}


uint8_t Inf_I2C_ReceiveByte(void)
{
    uint8_t byte = 0;

    SDA_H;
    DELAY_IIC;

    SCL_H;

    for (size_t i = 0; i < 8; i++)
    {
        SCL_L;
        DELAY_IIC;

        SCL_H;
        DELAY_IIC;
        byte <<= 1;
        if (SDA_READ)
        {
            byte|=0x01;

        }
        SCL_L;
        DELAY_IIC;
        
    }

    return byte;
}

uint8_t Inf_I2C_WaitAck(void)
{
    SDA_H;
    DELAY_IIC;

    SCL_L;
    DELAY_IIC;

    SCL_H;
    DELAY_IIC;

    if(SDA_READ)
    {
        SCL_L;
        DELAY_IIC;
        return 1; // 没有收到应答
    }

    SCL_L;
    DELAY_IIC;

    return 0;
}

