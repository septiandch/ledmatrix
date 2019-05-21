/**
 *  AT24Cxx EEPROM Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _AT24CXX_H_
#define _AT24CXX_H_

#include "i2c.h"

#define AT24C_ADDR	0x50

extern void eeprom_Init();
extern void eeprom_WriteByte(uint16_t address, uint8_t data);
extern uint8_t eeprom_ReadByte(uint16_t address);

#endif /** _AT24CXX_H_ */
