/**
 *  AT24Cxx EEPROM Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "at24cxx.h"

void eeprom_init()
{
	i2c_init();
}

void eeprom_wait()
{
	volatile int16_t x = 5971;
    while (x-- > 0) 
    {
        __asm("nop");
    }
}

void eeprom_write_byte(uint16_t address, uint8_t data)
{
	i2c_start();
	i2c_direction(AT24C_ADDR << 1, I2C_Direction_Transmitter);
	i2c_transmit((uint8_t) (address >> 8) & 0xFF);
	i2c_transmit((uint8_t) (address & 0xFF));
	i2c_transmit(data);
	i2c_stop();
	
	delay_ms(3);
}

uint8_t eeprom_read_byte(uint16_t address)
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
	
	delay_ms(3);

	return data;
}

void eeprom_write_string(uint16_t addr, char *str, uint16_t len)
{
	uint16_t	i	= 0;
	
	for(i = 0; i < len; i++)
	{
		eeprom_write_byte(addr + i, str[i]);
	}

	eeprom_write_byte(addr + len, '\0');
}

void eeprom_read_string(uint16_t addr, char *str)
{
	uint16_t	i	= 0;
	
	do
	{
		str[i] = eeprom_read_byte(addr + i);
		i++;
	}
	while(str[i - 1] != '\0');

	str[i] = '\0';
}