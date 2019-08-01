/**
 *  Moving Sign Display application
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "app_main.h"

/* INITIALIZE GLOBAL VARIABLES */
static char		sMessageBuff[100]							= "";
char		 	bColonState									= ' ';
uint8_t			bMsg										= 0;
uint16_t		nCounter									= 0;
eDisplayMode	eCurrentDispMode							= MODE_BLANK;
stRealTime		stRTime										;
stPowerSave		stPwrSave									;
static uint8_t	bMsgMode[COMMAND_MAX_TASK]					;
static uint8_t	bMsgDelay[COMMAND_MAX_TASK]					;
static uint8_t	bMsgIteration[COMMAND_MAX_TASK]				;
static char		sMsgStr[COMMAND_MAX_TASK][COMMAND_MAX_LEN]	;

void app_init(void)
{
	app_hal_init();
	
#ifdef USE_FMEM
	fmem_Init();
#else
	eeprom_init();
#endif

	utils_delay(100);
	rtc_Init(SQW_1HZ);
	/* rtc_setTime(19, 6, 10, 18, 52, 0); */

	utils_delay(100);
	matrix_Init();
	matrix_SetBrightness(eeprom_read_byte(MEM_BRIGHTNESS));

	usart_init(9600);

	utils_delay(100);
	app_mem_read();

	app_get_powersave(&stPwrSave);
}

void app_set_powersave(uint8_t StartHour, uint8_t StartMinute, uint16_t Duration)
{
	eeprom_write_byte(MEM_PWRSAVE_HOUR, StartHour);
	eeprom_write_byte(MEM_PWRSAVE_MINUTE, StartMinute);
	eeprom_write_byte(MEM_PWRSAVE_DURATION, (uint8_t)((Duration >> 8) & 0xFF));
	eeprom_write_byte(MEM_PWRSAVE_DURATION + 1, (uint8_t)(Duration & 0xFF));
}

void app_get_powersave(stPowerSave *stPwrSv)
{
	stPwrSv->StartHour		= eeprom_read_byte(MEM_PWRSAVE_HOUR);
	stPwrSv->StartMinute	= eeprom_read_byte(MEM_PWRSAVE_MINUTE);
	stPwrSv->Duration		= ((uint16_t) eeprom_read_byte(MEM_PWRSAVE_DURATION) << 8) | eeprom_read_byte(MEM_PWRSAVE_DURATION + 1);
}

eTaskStatus app_set_mode(eDisplayMode mode, char *message)
{
	/* Local Variables */
	uint8_t			index[10]			;
	int16_t			posX				= 0;
	int16_t			posY				= 0;
	uint16_t		nCurCounter			= nCounter;
	eTaskStatus		eTaskStat			= WORKING;
	volatile char	sMessageTmp[100]	= "";
	volatile char	sMessageTmp2[10]	= "";

	/* Clear Screen when change mode */
	if(eCurrentDispMode != mode)
	{
		matrix_ScreenClear(BLACK);
		eCurrentDispMode	= mode;
		nCounter			= 0;
		bMsg				= 0;
	}
	
	switch(mode)
	{
		case MODE_POWERSAVE :
			matrix_SetFont(System5x7);
			utils_timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			posX = matrix_GetTextCenter(sMessageBuff);
			matrix_DrawString(posX, 11, sMessageBuff, RED);
			
			if(bColonState != bColonState)
			{
				bColonState = bColonState;
				nCounter++;
			}
			break;
			
		case MODE_WELCOMEMESSAGE :
			matrtix_DrawImage(1, 0, &logo_masjid);

			utils_parse('\r', message, &index);

			matrix_SetFont(ArialBlack16);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = matrix_GetTextCenter(sMessageTmp);
			matrix_DrawString(posX + 5, 0, sMessageTmp, RED);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);
			if(matrix_DrawMarquee(34, 16, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 34, 32, sMessageTmp, SCROLL_RIGHT_TO_LEFT, RED) == 1)
			{
				eTaskStat = IDLE;
			}

			matrtix_DrawImage((DISPLAY_WIDTH * DISPLAY_ACROSS) - 33, 0, &logo_masjid);
			matrix_DrawBox(0, 0, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 1, (DISPLAY_HEIGHT * DISPLAY_DOWN) - 1, RED);
			break;
			
		case MODE_BIGMESSAGE :
			//matrix_DrawFilledBox(0, 4, 49, 26, RED);
			utils_timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			matrix_SetFont(Unispace18);
			matrix_DrawString(3, 6, sMessageBuff, RED);
			matrix_DrawLine(50, 5, 50, 25, RED);
			
			matrix_SetFont(Verdana25);
			if(matrix_DrawMarquee(55, 4, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 55, 28, message, SCROLL_RIGHT_TO_LEFT, RED) == 1)
			{
				eTaskStat = IDLE;
			}
			break;
			
		case MODE_DOAMESSAGE :
			utils_parse('\r', message, &index);

			matrix_SetFont(ArialBlack16);

			if(nCounter < 10)
			{
				matrtix_DrawImage(12, 8, &doa_masjid);
			}
			else if(nCounter == 10)
			{
				matrix_ScreenClear(BLACK);
			}
			else if(nCounter > 10)
			{
				memset(sMessageTmp, '\0', 50);
				memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);

				posX = matrix_GetTextCenter(sMessageTmp);
				if(matrix_DrawMarquee(0, 14, DISPLAY_WIDTH * DISPLAY_ACROSS, 16, sMessageTmp, SCROLL_RIGHT_TO_LEFT, RED) == 1)
				{
					matrix_ScreenClear(BLACK);
					nCounter = 0;
					eTaskStat = IDLE;
				}
			}
			
			matrix_SetFont(System5x7);
			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = matrix_GetTextCenter(sMessageTmp);
			matrix_DrawString(posX, 2, sMessageTmp, RED);
			break;
			
		case MODE_TITLEDMESSAGE :
			utils_parse('\r', message, &index);

			matrix_SetFont(ArialBlack16);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = matrix_GetTextCenter(sMessageTmp);
			matrix_DrawString(posX + 5, 0, sMessageTmp, RED);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);	

			if(matrix_DrawMarquee(0, 16, DISPLAY_WIDTH * DISPLAY_ACROSS, 32, sMessageTmp, SCROLL_RIGHT_TO_LEFT, RED) == 1)
			{
				eTaskStat = IDLE;
			}
			break;
		
		case MODE_REPORTMESSAGE :
			memset(index, 0, 10);
			utils_parse('\r', message, &index);

			matrix_ScreenClear(BLACK);

			matrix_SetFont(ArialBlack16);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = matrix_GetTextCenter(sMessageTmp);
			matrix_DrawString(posX + 5, 0, sMessageTmp, RED);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message + index[bMsg], index[bMsg + 1] - index[bMsg] - 1);		
			posX = matrix_GetTextCenter(sMessageTmp);
			if(posX < 0) posX = 0;

			if(matrix_DrawMarquee(posX, 16, DISPLAY_WIDTH * DISPLAY_ACROSS, 31, sMessageTmp, SCROLL_BOTTOM_TO_TOP, RED) == 1)
			{
				bMsg++;

				if(index[bMsg + 1] == 0)
				{
					bMsg = 0;
					eTaskStat = IDLE;
				}
			}

			if(matrix_GetMarqueePos() == 16)
			{
				matrix_PauseMarquee(ENABLE);

				if(nCounter >= 5)
				{
					matrix_PauseMarquee(DISABLE);
					nCounter = 0;
				}
			}

			break;

		case MODE_BLANK :
			break;
			
		default :
			/* Do something... */
			break;
	}

	matrix_ScreenApply();

	return eTaskStat;
}

void app_check_event(eTimeEvent	*eEventRet)
{
	uint16_t	nCurrentTime	= 0;

	/* Current time plus MINUTES_TO_ADZAN for countdown */
	nCurrentTime = (uint16_t)(stRTime.hour * 60) + stRTime.minute;

	if(nCurrentTime == ((uint16_t)(stPwrSave.StartHour * 60) +  stPwrSave.StartMinute))
	{
		*eEventRet = EVENT_PWRSAVE;
	}
	else if(nCurrentTime == ((uint16_t)(stPwrSave.StartHour * 60) +  stPwrSave.StartMinute) + stPwrSave.Duration)
	{
		*eEventRet = EVENT_NONE;
	}
}

void app_get_message(uint8_t task, char *str, uint8_t *mode, uint8_t *delay, uint8_t *iteration)
{
	uint16_t	i	= 0;
	
	*mode		= bMsgMode[task];
	*delay		= bMsgDelay[task];
	*iteration	= bMsgIteration[task];
	
	do
	{
		str[i] = sMsgStr[task][i];
		i++;
	}
	while(str[i - 1] != '\0');

	str[i] = '\0';
}

void app_mem_read(void)
{
	uint8_t	i	= 0;

	for(i = 0; i < COMMAND_MAX_TASK; i++)
	{
		app_command_read(i, &sMsgStr[i], &bMsgMode[i], &bMsgDelay[i], &bMsgIteration[i]);
	}
}
