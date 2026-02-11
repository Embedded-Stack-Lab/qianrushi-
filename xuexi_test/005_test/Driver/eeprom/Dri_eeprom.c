#include "Dri_eeprom.h"

void Dri_EEPROM_Init(void){
    Inf_IIC_Init();
}

void Dri_EEPROM_WriteByte(uint16_t addr, uint8_t data){
    Inf_IIC_Start();
    Inf_I2C_SendByte(DEVICE_WRITE);
    Inf_IIC_WaitAck();

    Inf_I2C_SendByte((uint8_t )addr );
    Inf_IIC_WaitAck();

    Inf_I2C_SendByte(data);
    Inf_IIC_WaitAck();
    Inf_IIC_Stop();

    Dri_Systick_Delay_ms(5); // EEPROM写入需要时间
}

uint8_t Dri_EEPROM_ReadByte(uint16_t addr);

void Dri_EEPROM_WritePage(uint16_t addr, uint8_t* data, uint16_t length);

void Dri_EEPROM_ReadString(uint8_t addr,uint8_t *arr,uint8_t length);
