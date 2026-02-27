#include "Dri_eeprom.h"

void Dri_EEPROM_Init(void)
{
    Inf_IIC_Init();
}

void Dri_EEPROM_WriteByte(uint16_t addr, uint8_t data)
{
    Inf_IIC_Start();
    Inf_I2C_SendByte(DEVICE_WRITE);
    Inf_IIC_WaitAck();

    Inf_I2C_SendByte((uint8_t)addr);
    Inf_IIC_WaitAck();

    Inf_I2C_SendByte(data);
    Inf_IIC_WaitAck();
    Inf_IIC_Stop();

    Dri_Systick_Delay_ms(5); // EEPROM写入需要时间
}

uint8_t Dri_EEPROM_ReadByte(uint16_t addr)
{
    uint8_t byte = 0;

    // 1.发起广播信号
    Inf_IIC_Start();

    // 2.主设备广播
    Inf_I2C_SendByte(DEVICE_WRITE);
    Inf_I2C_WaitAck();

    // 3.伪写字节
    Inf_IIC_Start();
    Inf_I2C_SendByte(addr); //

    Inf_IIC_Start();
    Inf_I2C_SendByte(DEVICE_READ);
    Inf_I2C_WaitAck();

    Inf_I2C_WaitAck();
    byte = Inf_I2C_ReceiveByte();

    Inf_IIC_NACK();
    Inf_IIC_Stop();

    return byte;
}

void Dri_EEPROM_WritePage(uint16_t addr, uint8_t *data, uint16_t length)
{

    Inf_IIC_Start();
    Inf_I2C_SendByte(DEVICE_WRITE);

    uint8_t ack = Inf_I2C_WaitAck();
    if (ack == 0)
    {

        Inf_I2C_SendByte(addr);
        Inf_I2C_WaitAck();

        for (int i = 0; i < length; i++)
        {
            Inf_I2C_SendByte(data[i]);
            Inf_I2C_WaitAck();
        }

        Inf_IIC_Stop();
    }
    Delay_ms(5); // EEPROM写入需要时间
}

void Dri_EEPROM_ReadString(uint8_t addr, uint8_t *arr, uint8_t length);
