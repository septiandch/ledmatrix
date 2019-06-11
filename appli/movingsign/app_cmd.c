/**
 *  Moving Sign Display data processing
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "app_cmd.h"

void app_command_check()
{
	if(usart_get_lastchar() == '#')
	{
		app_command_write();
	}
}

void app_command_write()
{
	volatile char	sMessageTmp[COMMAND_MAX_LEN + 3]	= "";

	switch(usart_sMessage[usart_nIndex - 2])
	{
		/* Message Command */
		case '&' :
			memset(sMessageTmp, '\0', COMMAND_MAX_LEN + 3);
			memcpy(sMessageTmp, usart_sMessage, usart_nIndex - 3);

#ifdef USE_FMEM
			/* String Address --> [usart_nIndex - 3] */
			fmem_WriteString((uint16_t)(usart_sMessage[usart_nIndex - 3] - '0') * COMMAND_MAX_LEN, &sMessageTmp, usart_nIndex - 3);
			fmem_ApplyBuffer();
#else
			eeprom_write_string((uint16_t)(usart_sMessage[usart_nIndex - 3] - '0') * COMMAND_MAX_LEN, &sMessageTmp, usart_nIndex - 3);
#endif

			usart_puts("Message Update OK\n\r");
			usart_message_clear();
			break;

		/* Reset Command */
		case 'T' :
			if(usart_sMessage[0] == 'R' && usart_sMessage[1] == 'S')
			{
				NVIC_SystemReset();
			}
			usart_message_clear();
			break;
			
		/* Unknown Message */
		default :
			usart_puts("NG\n\r");
			usart_message_clear();
			break;
	}
}

void app_command_read(uint8_t task, char *str, uint8_t *mode, uint8_t *delay, uint8_t *iteration)
{
#ifdef USE_FMEM
	uint8_t DataHi = 0;
	uint8_t DataLo = 0;
	
	if(task < COMMAND_MAX_TASK)
	{
		fmem_ReadHalfWord(task * COMMAND_MAX_LEN, &DataHi, &DataLo);
		*mode = DataHi - '0';
		
		fmem_ReadHalfWord((task * COMMAND_MAX_LEN) + 1, &DataHi, &DataLo);
		*delay = (DataHi - '0') * 10;
		
		fmem_ReadHalfWord((task * COMMAND_MAX_LEN) + 2, &DataHi, &DataLo);
		*iteration = DataHi - '0';
		
		fmem_ReadString((task * COMMAND_MAX_LEN) + 3, str);
	}
#else
	if(task < COMMAND_MAX_TASK)
	{
		*mode		= eeprom_read_byte(((uint16_t)task * COMMAND_MAX_LEN) + 0) - '0';
		*delay		= (eeprom_read_byte(((uint16_t)task * COMMAND_MAX_LEN) + 2) - '0') * 5;
		*iteration	= eeprom_read_byte(((uint16_t)task * COMMAND_MAX_LEN) + 4) - '0';

		eeprom_read_string((task * COMMAND_MAX_LEN) + 6, str);
	}
#endif
}