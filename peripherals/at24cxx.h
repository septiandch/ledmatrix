/**
 *  AT24Cxx EEPROM Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _AT24CXX_H_
#define _AT24CXX_H_

#include "i2c.h"
#include "utils.h"

#define AT24C_ADDR	0x50

extern void		eeprom_init();
extern void		eeprom_write_byte(uint16_t address, uint8_t data);
extern uint8_t	eeprom_read_byte(uint16_t address);
extern void		eeprom_write_string(uint16_t addr, char *str, uint16_t len);
extern void		eeprom_read_string(uint16_t addr, char *str);

#endif /** _AT24CXX_H_ */
