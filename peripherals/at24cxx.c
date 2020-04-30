/**
 *  AT24Cxx EEPROM Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "at24cxx.h"

void eeprom_Init()
{
	i2c_init();
}

void eeprom_Wait()
{
	volatile int16_t x = 5971;
    while (x-- > 0) 
    {
        __asm("nop");
    }
}

void eeprom_WriteByte(uint16_t address, uint8_t data)
{
	i2c_start();
	i2c_direction(AT24C_ADDR << 1, I2C_Direction_Transmitter);
	i2c_transmit((uint8_t) (address >> 8) & 0xFF);
	i2c_transmit((uint8_t) (address & 0xFF));
	i2c_transmit(data);
	i2c_stop();
	
	eeprom_Wait();
}

uint8_t eeprom_ReadByte(uint16_t address)
{
	uint8_t data;
	
	i2c_start();
	i2c_direction(AT24C_ADDR << 1, I2C_Direction_Transmitter);
	i2c_transmit((uint8_t) (address >> 8) & 0xFF);
	i2c_transmit((uint8_t) (address & 0xFF));
	i2c_stop();
	
	i2c_start();
	i2c_direction(AT24C_ADDR << 1, I2C_Direction_Receiver);
	data = i2c_read_nack();
	i2c_stop();
	
	eeprom_Wait();
	return data;
}
