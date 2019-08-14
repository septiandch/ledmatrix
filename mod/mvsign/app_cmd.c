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
	uint8_t			bCmdStat							= 1;

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

			/* Update Messages Buffer */
			ledmatrix_get_mem();
			break;

		/* RTC Command */
		case '*' :
			if(usart_nIndex - 1 == 13)
			{
				rtc_setTime(((usart_sMessage[ 0] - '0') * 10) + (usart_sMessage[ 1] - '0'),
							((usart_sMessage[ 2] - '0') * 10) + (usart_sMessage[ 3] - '0'),
							((usart_sMessage[ 4] - '0') * 10) + (usart_sMessage[ 5] - '0'),
							((usart_sMessage[ 6] - '0') * 10) + (usart_sMessage[ 7] - '0'),
							((usart_sMessage[ 8] - '0') * 10) + (usart_sMessage[ 9] - '0'),
							((usart_sMessage[10] - '0') * 10) + (usart_sMessage[11] - '0'));

				utils_delay(10);
				rtc_Init(SQW_1HZ);
				
				usart_puts("RTC update OK\n\r");
			}
			else
			{
				usart_puts("NG\n\r");
			}
			
			usart_message_clear();
			break;
				
		/* Brigtness Command */
		case '%' :
			if(usart_nIndex - 1 == 6)
			{
				if(usart_sMessage[0] == 'B' && usart_sMessage[1] == 'R' && usart_sMessage[2] == 'G')
				{
					eeprom_write_byte(MEM_BRIGHTNESS, ((usart_sMessage[3] - '0') * 10) + (usart_sMessage[4] - '0') + 1);
					utils_delay(10);
					
					matrix_set_brightness(eeprom_read_byte(MEM_BRIGHTNESS));
					
					usart_puts("Brightness Update OK\n\r");
				}
			}
			else
			{
				usart_puts("NG\n\r");
			}
					
			usart_message_clear();
			break;		
		
		/* Powersave Command */
		case '$' :
			if(usart_nIndex - 1 == 8)
			{
				ledmatrix_set_powersave(( (usart_sMessage[0] - '0') * 10)	+ usart_sMessage[1] - '0',
									( (usart_sMessage[2] - '0') * 10)	+ usart_sMessage[3] - '0',
									( (usart_sMessage[4] - '0') * 100)	+ ((usart_sMessage[5] - '0') * 10) + usart_sMessage[6] - '0');
				
				ledmatrix_get_powersave(&stPwrSave);
				
				usart_puts("Powersave Update OK\n\r");
			}
			else
			{
				usart_puts("NG\n\r");
			}
			
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

			bCmdStat = 0;
			break;
	}

	if(bCmdStat == 1)
	{
		BUZZER_GPIO->BSRR  = BUZZER_PIN;
		utils_delay(BUZZER_DELAY);
		BUZZER_GPIO->BRR  = BUZZER_PIN;
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
