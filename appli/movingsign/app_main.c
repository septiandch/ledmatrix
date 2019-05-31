/**
 *  Prayer Time Display Modes Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "app_main.h"

const char		sWeekday[7][10]			= {	"AHAD", "SENIN", "SELASA", "RABU",
											"KAMIS", "JUM'AT", "SABTU" };
const char		sJulianMonth[12][10]	= {	"JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI",
											"AGUSTUS", "SEPTEMBER", "OKTOBER", "NOPEMBER", "DESEMBER" };
static char		sMessageBuff[100]		= "";
static char 	bColonState	= ' ';
uint16_t		nCounter;
stRealTime		stRTime;
stPowerSave		stPwrSave;

void app_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	/** Enable GPIO clock */
	RCC_APB2PeriphClockCmd(BUZZER_GPIO_RCC, ENABLE);
	
	/** Configure Output */
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BUZZER_GPIO, &GPIO_InitStructure);
	
	/* Startup Sequence */
	matrix_Init();
	matrix_SetBrightness(1); //eeprom_ReadByte(MEM_BRIGHTNESS));

	//rtc_Init(SQW_1HZ);

	//app_PowerSaveSetup(&stPwrSave);
}

void app_SetMode(eDisplayMode mode, char *message)
{
	/* Local Variables */
	uint8_t			index[10]			;
	uint16_t		posX				= 0;
	uint16_t		posY				= 0;
	volatile char	sMessageTmp[50]		= "";
	volatile char	sMessageTmp2[10]	= "";
	
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
			matrix_SetFont(ArialBlack16);
			
			matrtix_DrawImage(5, 0, &icon);

			utils_StringParse('\r', message, &index);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message, index[0]);
			posX = matrix_GetTextCenter(sMessageTmp);
			matrix_DrawString(posX + 5, 0, sMessageTmp, RED);

			memset(sMessageTmp, '\0', 50);
			memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);			
			posX = matrix_GetTextCenter(sMessageTmp);
			matrix_DrawString(posX + 5, 16, sMessageTmp, RED);

			matrtix_DrawImage((DISPLAY_WIDTH * DISPLAY_ACROSS) - 33, 0, &icon);

			matrix_DrawBox(0, 0, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 1, (DISPLAY_HEIGHT * DISPLAY_DOWN) - 1, RED);
			break;
			
		case MODE_BIGMESSAGE :
			matrix_SetFont(ArialBlack16);

			//rtc_readTime(&stRTime.year, &stRTime.month, &stRTime.date, &stRTime.day, &stRTime.hour, &stRTime.minute, &stRTime.second);
			
			//matrix_DrawBox(0, 6, 42, 26, RED);
			//utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			//matrix_DrawString(3, 8, sMessageBuff, RED);

			matrix_DrawBox(0, 6, 42, 26, RED);
			utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			matrix_DrawString(3, 8, sMessageBuff, RED);
			
			matrix_SetFont(SansSerif25);
			nCounter += matrix_DrawMarquee(44, 6, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 44, 28, message, SCROLL_RIGHT_TO_LEFT, RED);
			break;
			
		case MODE_TITLEDMESSAGE :
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
}

void app_GetParam(uint8_t _task, char *_str, uint8_t *_mode, uint8_t *_delay, uint8_t *_iteration)
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
