#ifndef __DRI_EEPROM_H__
#define __DRI_EEPROM_H__

#include "Inf_IIC.h"

#define DEVICE_WRITE 0xA0
#define DEVICE_READ 0xA1

void Dri_EEPROM_Init(void);

void Dri_EEPROM_WriteByte(uint16_t addr, uint8_t data);

uint8_t Dri_EEPROM_ReadByte(uint16_t addr);

void Dri_EEPROM_WritePage(uint16_t addr, uint8_t* data, uint16_t length);

void Dri_EEPROM_ReadString(uint8_t addr,uint8_t *arr,uint8_t length);

#endif /* __DRI_EEPROM_H__ */