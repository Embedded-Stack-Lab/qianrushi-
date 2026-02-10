#include "Inf_IIC.h"

#define SDA_H GPIO_SetBits(GPIOB, GPIO_Pin_7)             // SDA置高
#define SDA_L GPIO_ResetBits(GPIOB, GPIO_Pin_7)           // SDA置低
#define SCL_H GPIO_SetBits(GPIOB, GPIO_Pin_6)             // SCL置高
#define SCL_L GPIO_ResetBits(GPIOB, GPIO_Pin_6)           // SCL置低
#define SDA_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) // 读SDA线状态
#define SCL_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) // 读SCL线状态
#define DELAY_IIC Dri_Systick_Delay_us(10);               // 延时10us来传输数据

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

void Dri_I2C_SendByte(uint8_t byte)
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

uint8_t Dri_I2C_ReceiveCyte(void)
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
