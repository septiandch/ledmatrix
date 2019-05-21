/**
 *  FLASH EEPROM Emulator Library
 *  Written By  : Artur F.
 *  E-mail      : 
 *  Site URL    : http://engsta.com/stm32-flash-memory-eeprom-emulator/
 */

#ifndef _FMEM_H
#define _FMEM_H

#include <stdio.h>
#include <string.h>
#include "stm32f10x_usart.h"
#include "stm32f10x_flash.h"

/* Read-Write Memory indirectly using Buffer */
#define FMEM_USE_BUFFER

/* CAN BE CHANGED */
#define FMEM_DENSITY_PAGES		2	    	/* how many pages are used */
#define FMEM_PAGE_SIZE			0x0400	    /* can be 1k or 2k check manual for used device */
#define FMEM_PAGE_BASE_ADDRESS 	0x800FC00	/* choose location for the first EEPROMPage address on the top of flash */

/* DONT CHANGE */
#define FMEM_DENSITY_BYTES			((FMEM_PAGE_SIZE / 2) * FMEM_DENSITY_PAGES - 1)
#define FMEM_LAST_PAGE_ADDRESS 		(FMEM_PAGE_BASE_ADDRESS + (FMEM_PAGE_SIZE * FMEM_DENSITY_PAGES))
#define FMEM_EMPTY_WORD				((uint16_t)0xFFFF)
#define FMEM_ADDR_OFFSET(Address)	(Address * 2) /* 1Byte per Word will be saved to preserve Flash */

/* use this function to initialize the functionality */
extern void		fmem_Erase(void);
extern void		fmem_Init(void);
extern void		fmem_ApplyBuffer(void);
extern void		fmem_WriteToBuffer(uint16_t addr, uint8_t DataHi, uint8_t DataLo);
extern void		fmem_ReadHalfWord(uint16_t addr, uint8_t *DataHi, uint8_t *DataLo);
extern void		fmem_ReadString(uint16_t addr, char *str);
extern void		fmem_WriteString(uint16_t addr, char *str, uint8_t len);
	
#endif /* _FMEM_H */
