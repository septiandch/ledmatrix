/**
 *  FLASH EEPROM Emulator Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Site URL    : http://solderingcodes.blogspot.com/
 */

#include "fmem.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile uint16_t fmem_nBuffer[FMEM_PAGE_SIZE / 2];

void fmem_Init(void)
{
	uint16_t i	= 0;
	
	/* Initialize buffer */
	for(i = 0; i < FMEM_PAGE_SIZE / 2; i++)
	{
		fmem_nBuffer[i] = (*(uint16_t*)(FMEM_PAGE_BASE_ADDRESS + FMEM_ADDR_OFFSET(i)));
	}
}

/*****************************************************************************
*  Erase the whole reserved Flash Space used for user Data
******************************************************************************/
void fmem_Erase(void)
{
	uint8_t i = 0;
		
	/* Unlock flash */
	FLASH_Unlock();
	
	/* delete all pages from specified start page to the last page */
	for(i = 0; i < FMEM_DENSITY_PAGES; i++)
	{
		FLASH_ErasePage(FMEM_PAGE_BASE_ADDRESS + (FMEM_PAGE_SIZE * i));
	}
		
	/* Lock flash */
	FLASH_Lock();
}

void fmem_WriteToBuffer(uint16_t addr, uint8_t DataHi, uint8_t DataLo)
{	
	fmem_nBuffer[addr] = (uint16_t)((DataHi << 8) | DataLo);
}

void fmem_WriteString(uint16_t addr, char *str, uint8_t len)
{
	uint16_t	index	= 0;
	
	while(index < len)
	{
		if((index + 1) < len)
		{
			fmem_WriteToBuffer(addr, str[index], str[index + 1]);
		}
		else
		{
			fmem_WriteToBuffer(addr, str[index], '\0');
		}
		addr += 1;
		index += 2;
	}
		
	fmem_WriteToBuffer(addr, '\0', '\0');
}

void fmem_ReadHalfWord(uint16_t addr, uint8_t *dataHi, uint8_t *dataLo)
{
#ifndef FMEM_USE_BUFFER
	uint16_t data = (*(uint16_t*)(FMEM_PAGE_BASE_ADDRESS + FMEM_ADDR_OFFSET(addr)));
#else
	uint16_t data = fmem_nBuffer[addr];
#endif
	
	/* Get Byte from specified address */
	*dataHi = (uint8_t)((data >> 8) & 0xFF);
	*dataLo = (uint8_t)(data & 0xFF);
}

void fmem_ReadString(uint16_t addr, char *str)
{
	uint16_t	index	= 0;
	uint16_t	data	= 0;
	
	do
	{
#ifndef FMEM_USE_BUFFER
		data = (*(uint16_t*)(FMEM_PAGE_BASE_ADDRESS + FMEM_ADDR_OFFSET(addr)));
#else
		data = fmem_nBuffer[addr];
#endif

		str[index]		= (uint8_t)((data >> 8) & 0xFF);
		str[index + 1]	= (uint8_t)(data & 0xFF);
		
		addr += 1;
		index += 2;
	}
	while(str[index - 2] != '\0');
	
	str[index - 1] = '\0';
}

void fmem_ApplyBuffer(void)
{
	FLASH_Status	FLASHStatus	= FLASH_COMPLETE;
	uint32_t 		page		= 0;
	uint16_t		i			= 0;
	
	/* Unlock flash */
	FLASH_Unlock();
	
	/* Clear Flags */
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
	
	FLASH_ErasePage(FMEM_PAGE_BASE_ADDRESS);
	FLASH_ErasePage(FMEM_PAGE_BASE_ADDRESS + FMEM_PAGE_SIZE);
    
	/* Write new data (whole page) to flash if data has beed changed */
	for(i = 0; i < (FMEM_PAGE_SIZE / 2); i++)
	{
		if(fmem_nBuffer[i] != 0xFFFF)
		{
			FLASH_ProgramHalfWord(FMEM_PAGE_BASE_ADDRESS + FMEM_ADDR_OFFSET(i), fmem_nBuffer[i]);
		}
	}
	
	/* Lock flash */
	FLASH_Lock();
}
