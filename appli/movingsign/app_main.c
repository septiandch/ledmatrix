/**
 *  Moving Sign Display application
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "app_main.h"
#include "app_hal.h"

/* INITIALIZE GLOBAL VARIABLES */
const char		sWeekday[7][10]			= {	"AHAD", "SENIN", "SELASA", "RABU",
											"KAMIS", "JUM'AT", "SABTU" };
const char		sJulianMonth[12][10]	= {	"JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI",
											"AGUSTUS", "SEPTEMBER", "OKTOBER", "NOPEMBER", "DESEMBER" };
static char		sMessageBuff[100]		= "";
static char 	bColonState				= ' ';
uint16_t		nCounter				= 0;
eDisplayMode	eCurrentDispMode		= MODE_BLANK;
stRealTime		stRTime					;
stPowerSave		stPwrSave				;

void app_init(void)
{
	app_hal_init();
	
	/* Startup Sequence */
	matrix_Init();
	matrix_SetBrightness(1); //eeprom_ReadByte(MEM_BRIGHTNESS));

	//rtc_Init(SQW_1HZ);

	//app_PowerSaveSetup(&stPwrSave);
}

void app_set_mode(eDisplayMode mode, char *message)
{
	/* Local Variables */
	uint8_t			index[10]			;
	uint16_t		posX				= 0;
	uint16_t		posY				= 0;
	volatile char	sMessageTmp[50]		= "";
	volatile char	sMessageTmp2[10]	= "";

	/* Clear Screen when change mode */
	if(eCurrentDispMode != mode)
	{
		matrix_ScreenClear(BLACK);
		eCurrentDispMode = mode;
	}

	switch(mode)
	{
		case MODE_POWERSAVE :
			matrix_SetFont(System5x7);
			utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			matrix_DrawString(55, 4, sMessageBuff, RED);
			
			if(bColonState != bColonState)
			{
				bColonState = bColonState;
				nCounter++;
			}
			break;
			
		case MODE_WELCOME :
			matrtix_DrawImage(5, 0, &logo_masjid);

			utils_StringParse('\r', message, &index);

			matrix_SetFont(ArialBlack16);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = matrix_GetTextCenter(sMessageTmp);
			matrix_DrawString(posX + 5, 0, sMessageTmp, RED);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);			
			posX = matrix_GetTextCenter(sMessageTmp);
			matrix_DrawString(posX + 5, 16, sMessageTmp, RED);

			matrtix_DrawImage((DISPLAY_WIDTH * DISPLAY_ACROSS) - 33, 0, &logo_masjid);

			matrix_DrawBox(0, 0, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 1, (DISPLAY_HEIGHT * DISPLAY_DOWN) - 1, RED);
			break;
			
		case MODE_BIGMESSAGE :
			//rtc_readTime(&stRTime.year, &stRTime.month, &stRTime.date, &stRTime.day, &stRTime.hour, &stRTime.minute, &stRTime.second);
			
			//matrix_DrawBox(0, 6, 42, 26, RED);
			//utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			//matrix_DrawString(3, 8, sMessageBuff, RED);

			matrix_DrawFilledBox(0, 5, 49, 26, RED);
			//utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			matrix_invert_color(ENABLE);
			matrix_SetFont(Unispace18);
			matrix_DrawString(3, 6, "14:30", RED);
			matrix_invert_color(DISABLE);
			matrix_DrawLine(0, 27, 49, 27, RED);
			
			matrix_SetFont(SansSerif25);
			nCounter += matrix_DrawMarquee(51, 6, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 51, 28, message, SCROLL_RIGHT_TO_LEFT, RED);
			break;
			
		case MODE_DOAMESSAGE :
			matrtix_DrawImage(12, 8, &doa_masjid);

			matrix_SetFont(System5x7);
			posX = matrix_GetTextCenter(message);
			matrix_DrawString(posX, 2, message, RED);
			break;
			
		case MODE_DATETIME :
			break;
		
		case MODE_BLANK :
			if(bColonState != bColonState)
			{
				bColonState = bColonState;
				nCounter++;
			}
			break;
			
		default :
			/* Do something... */
			break;
	}
	
	matrix_ScreenApply();
}

void app_get_param(uint8_t _task, char *_str, uint8_t *_mode, uint8_t *_delay, uint8_t *_iteration)
{
	uint8_t DataHi = 0;
	uint8_t DataLo = 0;
	
	if(_task < PARAM_MAX_TASK)
	{
		fmem_ReadHalfWord(_task * PARAM_MAX_LEN, &DataHi, &DataLo);
		*_mode = DataHi - '0';
		
		fmem_ReadHalfWord((_task * PARAM_MAX_LEN) + 1, &DataHi, &DataLo);
		*_delay = (DataHi - '0') * 10;
		
		fmem_ReadHalfWord((_task * PARAM_MAX_LEN) + 2, &DataHi, &DataLo);
		*_iteration = DataHi - '0';
		
		fmem_ReadString((_task * PARAM_MAX_LEN) + 3, _str);
	}
}
