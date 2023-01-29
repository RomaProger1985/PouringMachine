
#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);
void EEPROM_write_2bit(unsigned int uiAddress, uint16_t ucData);
uint16_t EEPROM_read_2bit(unsigned int uiAddress);
uint32_t EEPROM_read_int(unsigned int uiAddress);
void EEPROM_write_int(unsigned int uiAddress, uint32_t ucData);

#endif /* EEPROM_H_ */