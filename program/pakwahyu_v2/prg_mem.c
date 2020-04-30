/**
 *  Display Command
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prg_def.h"
#include "prg_func.h"

/*----- Defines -----*/


/*----- Function Prototypes -----*/


/*----- Global Variables -----*/


void mem_init()
{
	i2c_init();	
}

void mem_write_str(uint16_t wAddress, char *pcData)
{
	uint16_t wStrLen = utils_strlen(pcData);

	eeprom_write_string(wAddress, pcData, wStrLen);
}

void mem_read_str(uint16_t wAddress, char *pcData)
{
	eeprom_read_string(wAddress, pcData);
}