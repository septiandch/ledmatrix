/**
 *  Moving Sign Display application
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "app_main.h"

/* INITIALIZE GLOBAL VARIABLES */
const char		sWeekday[7][10]			= {	"AHAD", "SENIN", "SELASA", "RABU",
											"KAMIS", "JUM'AT", "SABTU" };
const char		sJulianMonth[12][10]	= {	"JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI",
											"AGUSTUS", "SEPTEMBER", "OKTOBER", "NOPEMBER", "DESEMBER" };
static char		sMessageBuff[100]		= "";
static char 	bColonState				= ' ';
uint8_t			bMsg					= 0;
uint16_t		nCounter				= 0;
eDisplayMode	eCurrentDispMode		= MODE_BLANK;
stRealTime		stRTime					;
stPowerSave		stPwrSave				;

void app_init(void)
{
	app_hal_init();
	
	
	/* Startup Sequence */
	fmem_Init();
	
	matrix_Init();
	matrix_SetBrightness(1); //eeprom_ReadByte(MEM_BRIGHTNESS));

	//rtc_Init(SQW_1HZ);

	usart_init(9600);

	//app_PowerSaveSetup(&stPwrSave);
}

void app_run()
{

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
			matrix_DrawString(55, 4, sMessageBuff, RED);
			
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
				eTaskStat = FINISHED;
			}

			matrtix_DrawImage((DISPLAY_WIDTH * DISPLAY_ACROSS) - 33, 0, &logo_masjid);
			matrix_DrawBox(0, 0, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 1, (DISPLAY_HEIGHT * DISPLAY_DOWN) - 1, RED);
			break;
			
		case MODE_BIGMESSAGE :
			//rtc_readTime(&stRTime.year, &stRTime.month, &stRTime.date, &stRTime.day, &stRTime.hour, &stRTime.minute, &stRTime.second);
			
			//matrix_DrawBox(0, 6, 42, 26, RED);
			//utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			//matrix_DrawString(3, 8, sMessageBuff, RED);

			matrix_DrawFilledBox(0, 4, 49, 26, RED);
			//utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			matrix_invert_color(ENABLE);
			matrix_SetFont(Unispace18);
			matrix_DrawString(3, 6, "14:30", RED);
			matrix_invert_color(DISABLE);
			matrix_DrawLine(0, 27, 49, 27, RED);
			
			matrix_SetFont(Verdana25);
			if(matrix_DrawMarquee(51, 5, (DISPLAY_WIDTH * DISPLAY_ACROSS) - 51, 28, message, SCROLL_RIGHT_TO_LEFT, RED) == 1)
			{
				eTaskStat = FINISHED;
			}
			break;
			
		case MODE_DOAMESSAGE :
			utils_parse('\r', message, &index);

			matrix_SetFont(ArialBlack16);

			if(nCounter < 100)
			{
				matrtix_DrawImage(12, 8, &doa_masjid);
			}
			else if(nCounter == 100)
			{
				matrix_ScreenClear(BLACK);
			}
			else if(nCounter > 100 && nCounter < 200)
			{
				memset(sMessageTmp, '\0', 50);
				memcpy(sMessageTmp, message + index[0], utils_strlen(message) - index[0] - 1);

				posX = matrix_GetTextCenter(sMessageTmp);
				if(matrix_DrawMarquee(0, 14, DISPLAY_WIDTH * DISPLAY_ACROSS, 16, sMessageTmp, SCROLL_RIGHT_TO_LEFT, RED) == 0)
				{
					nCounter = 100 + 1;
				}
				else
				{
					nCounter = 200;
				}
			}
			else
			{
				matrix_ScreenClear(BLACK);
				nCounter = 0;
				eTaskStat = FINISHED;
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
				eTaskStat = FINISHED;
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
					eTaskStat = FINISHED;
				}
			}

			if(matrix_GetMarqueePos() == 16)
			{
				matrix_PauseMarquee(ENABLE);

				if(nCounter >= 150)
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
	
	nCounter++;
	if(nCounter > 60000)
	{
		nCounter = 0;
	}

	matrix_ScreenApply();

	return eTaskStat;
}