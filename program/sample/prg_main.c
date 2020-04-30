/**
 *  Moving Sign Display application
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "program/prg_api.h"
#include "program/prayertime/prytime/prayermath.h"

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

void prg_init(void)
{
	io_init();
	
#ifdef ENABLE_FMEM
	fmem_Init();
#else
	eeprom_init();
#endif

	utils_delay(100);
	rtc_Init(SQW_1HZ);
	/* rtc_setTime(19, 6, 10, 18, 52, 0); */

	utils_delay(100);

	dmd_init();
	dmd_set_brightness(eeprom_read_byte(MEM_BRIGHTNESS));

	usart_init(9600);

	utils_delay(100);
	prg_get_mem();

	prg_get_powersave(&stPwrSave);
}

void prg_set_powersave(uint8_t StartHour, uint8_t StartMinute, uint16_t Duration)
{
	eeprom_write_byte(MEM_PWRSAVE_HOUR, StartHour);
	eeprom_write_byte(MEM_PWRSAVE_MINUTE, StartMinute);
	eeprom_write_byte(MEM_PWRSAVE_DURATION, (uint8_t)((Duration >> 8) & 0xFF));
	eeprom_write_byte(MEM_PWRSAVE_DURATION + 1, (uint8_t)(Duration & 0xFF));
}

void prg_get_powersave(stPowerSave *stPwrSv)
{
	stPwrSv->StartHour		= eeprom_read_byte(MEM_PWRSAVE_HOUR);
	stPwrSv->StartMinute	= eeprom_read_byte(MEM_PWRSAVE_MINUTE);
	stPwrSv->Duration		= ((uint16_t) eeprom_read_byte(MEM_PWRSAVE_DURATION) << 8) | eeprom_read_byte(MEM_PWRSAVE_DURATION + 1);
}

eTaskStatus prg_set_mode(eDisplayMode mode, char *message)
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
		dmd_clr_screen(eCL_BLACK);
		eCurrentDispMode	= mode;
		nCounter			= 0;
		bMsg				= 0;
	}
	
	switch(mode)
	{
		case MODE_POWERSAVE :
			dmd_set_font(System5x7);
			utils_timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			posX = dmd_get_textcenter(sMessageBuff);
			dmd_draw_string(posX, 11, sMessageBuff, eCL_RED);
			
			if(bColonState != bColonState)
			{
				bColonState = bColonState;
				nCounter++;
			}
			break;
			
		case MODE_WELCOMEMESSAGE :
			dmd_draw_image(1, 0, &logo_masjid);

			utils_parse('\r', message, &index);

			dmd_set_font(ArialBlack16);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = dmd_get_textcenter(sMessageTmp);
			dmd_draw_string(posX + 5, 0, sMessageTmp, eCL_RED);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);
			if(dmd_draw_marquee(34, 16, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 34, 32, sMessageTmp, eMARQUEE_RIGHT_TO_LEFT, eCL_RED) == 1)
			{
				eTaskStat = IDLE;
			}

			dmd_draw_image((DISPLAY_WIDTH * DISPLAY_ACROSS) - 33, 0, &logo_masjid);
			dmd_draw_box(0, 0, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 1, (stDispProp.bHeight * DISPLAY_DOWN) - 1, eCL_RED);
			break;
			
		case MODE_BIGMESSAGE :
			//dmd_draw_filledbox(0, 4, 49, 26, eCL_RED);
			utils_timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			dmd_set_font(Unispace18);
			dmd_draw_string(3, 6, sMessageBuff, eCL_RED);
			dmd_draw_line(50, 5, 50, 25, eCL_RED);
			
			dmd_set_font(Verdana25);
			if(dmd_draw_marquee(55, 4, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 55, 28, message, eMARQUEE_RIGHT_TO_LEFT, eCL_RED) == 1)
			{
				eTaskStat = IDLE;
			}
			break;
			
		case MODE_DOAMESSAGE :
			utils_parse('\r', message, &index);

			dmd_set_font(ArialBlack16);

			if(nCounter < 10)
			{
				dmd_draw_image(12, 8, &doa_masjid);
			}
			else if(nCounter == 10)
			{
				dmd_clr_screen(eCL_BLACK);
			}
			else if(nCounter > 10)
			{
				memset(sMessageTmp, '\0', 50);
				memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);

				posX = dmd_get_textcenter(sMessageTmp);
				if(dmd_draw_marquee(0, 14, DISPLAY_WIDTH * DISPLAY_ACROSS, 16, sMessageTmp, eMARQUEE_RIGHT_TO_LEFT, eCL_RED) == 1)
				{
					dmd_clr_screen(eCL_BLACK);
					nCounter = 0;
					eTaskStat = IDLE;
				}
			}
			
			dmd_set_font(System5x7);
			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = dmd_get_textcenter(sMessageTmp);
			dmd_draw_string(posX, 2, sMessageTmp, eCL_RED);
			break;
			
		case MODE_TITLEDMESSAGE :
			utils_parse('\r', message, &index);

			dmd_set_font(ArialBlack16);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = dmd_get_textcenter(sMessageTmp);
			dmd_draw_string(posX + 5, 0, sMessageTmp, eCL_RED);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);	

			if(dmd_draw_marquee(0, 16, DISPLAY_WIDTH * DISPLAY_ACROSS, 32, sMessageTmp, eMARQUEE_RIGHT_TO_LEFT, eCL_RED) == 1)
			{
				eTaskStat = IDLE;
			}
			break;
		
		case MODE_REPORTMESSAGE :
			memset(index, 0, 10);
			utils_parse('\r', message, &index);

			dmd_clr_screen(eCL_BLACK);

			dmd_set_font(ArialBlack16);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = dmd_get_textcenter(sMessageTmp);
			dmd_draw_string(posX + 5, 0, sMessageTmp, eCL_RED);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message + index[bMsg], index[bMsg + 1] - index[bMsg] - 1);		
			posX = dmd_get_textcenter(sMessageTmp);
			if(posX < 0) posX = 0;

			if(dmd_draw_marquee(posX, 16, DISPLAY_WIDTH * DISPLAY_ACROSS, 31, sMessageTmp, eMARQUEE_BOTTOM_TO_TOP, eCL_RED) == 1)
			{
				bMsg++;

				if(index[bMsg + 1] == 0)
				{
					bMsg = 0;
					eTaskStat = IDLE;
				}
			}

			if(dmd_get_marqueepos() == 16)
			{
				dmd_marquee_pause(ENABLE);

				if(nCounter >= 5)
				{
					dmd_marquee_pause(DISABLE);
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

	dmd_init_doublebuffer();

	return eTaskStat;
}

void prg_chk_event(eTimeEvent	*eEventRet)
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

void prg_get_message(uint8_t task, char *str, uint8_t *mode, uint8_t *delay, uint8_t *iteration)
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

void prg_get_mem(void)
{
	uint8_t	i	= 0;

	for(i = 0; i < COMMAND_MAX_TASK; i++)
	{
		cmd_read(i, &sMsgStr[i], &bMsgMode[i], &bMsgDelay[i], &bMsgIteration[i]);
	}
}
