#include "eeprom.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	while(EECR & (1<<EEPE)) //ждем освобождения флага окончания последней операцией с памятью
	{}
	EEARH = ((uiAddress & 0xf0) << 2); //Устанавливаем адрес
	EEARL = uiAddress & 0x0f;
	EEDR = ucData; //Пищем данные в регистр
	EECR |= (1<<EEMPE); //Разрешаем запись
	EECR |= (1<<EEPE); //Пишем байт в память
}

unsigned char EEPROM_read(unsigned int uiAddress)

{
	while(EECR & (1<<EEPE)); //ждем освобождения флага окончания последней операцией с памятью
	EEARH = ((uiAddress & 0xf0) << 2); //Устанавливаем адрес
	EEARL = uiAddress & 0x0f;
	EECR |= (1<<EERE); //Запускаем операцию считывания из памяти в регистр данных
	return EEDR; //Возвращаем результат
}

void EEPROM_write_2bit(unsigned int uiAddress, uint16_t ucData)
{
	EEPROM_write(uiAddress, (unsigned char) ucData);
	unsigned char dt = ucData>>8;
	EEPROM_write(uiAddress+1, dt);
}

uint16_t EEPROM_read_2bit(unsigned int uiAddress)
{
	uint16_t dt = EEPROM_read(uiAddress+1)*256;
	asm("nop");
	dt += EEPROM_read(uiAddress);
	return dt;
}

void EEPROM_write_int(unsigned int uiAddress, uint32_t ucData)
{
	EEPROM_write_2bit(uiAddress, (uint16_t) ucData);
	uint16_t dt = ucData>>16;
	EEPROM_write_2bit(uiAddress+2, dt);
}

uint32_t EEPROM_read_int(unsigned int uiAddress)
{
	uint32_t dt = EEPROM_read_2bit(uiAddress+2)*65536;
	asm("nop");
	dt += EEPROM_read_2bit(uiAddress);
	return dt;
}