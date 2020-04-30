/**
  ******************************************************************************
  * @file    main.c 
  * @author  Septian D. Chandra
  * @date    17-January-2018
  * @brief   Main program.
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "platform_config.h"
#include "utils.h"
#include "ledmatrix/dmdhal.h"
#include "ledmatrix/ledmatrix.h"
#include "ledmatrix/dmdhal.h"
#include "peripherals/rtc.h"
#include "peripherals/fmem.h"
#include "peripherals/usart.h"
#include "prayertime/prayertime.h"
#include "prayertime/pdisplay.h"

/* GLOBAL VARIABLES */
uint8_t			nTask			= 0;
uint8_t			nPTimeSel		= 0;
uint16_t		nCounter		= 0;
eParamStatus	eParStatus		= PARAM_NG;
eDisplayStatus	eDispStatus		= IDLE;
static uint8_t	bCurrentDate	= 0;
static uint8_t	bCmdState		= 0;

uint8_t			param_message[PARAM_MAX_LEN * 2];
uint8_t			param_mode			= 0;
uint8_t			param_delay			= 0;
uint8_t			param_iteration		= 0;

/* FUNCTION PROTOTYPES */

/* ENUMERATION */
enum
{
	SEQ_ENTER_EVENT = 30,
	SEQ_SET_ADZANCOUNTER,
	SEQ_RUN_ADZANCOUNTER,
	SEQ_RUN_ADZANMESSAGE,
	SEQ_RUN_ADZANIDLE,
	SEQ_SET_IQAMAHCOUNTER,
	SEQ_RUN_IQAMAHCOUNTER,
	SEQ_RUN_IQAMAHIDLE,
	SEQ_RUN_PRAYERIDLE,
	SEQ_SET_PREJUMUAHMESSAGE,
	SEQ_RUN_PREJUMUAHMESSAGE,
	SEQ_RUN_JUMUAHCOUNTER,
	SEQ_SET_JUMUAHMESSAGE,
	SEQ_RUN_JUMUAHMESSAGE,
	SEQ_QUIT_EVENT,
	SEQ_POWERSAVE
};

/* MAIN FUNCTION */
int main(void)
{
	static char		_bColonState = ' ';
	stRealTime		_stRTime;
	stPrayerTime 	_stPTime[7];
	char			_message[122];
	
	/* Log */
	uint8_t			monthIndex = 0;
	uint16_t		readIndex = 0;
	uint16_t		iteration = 0;
	
	ptime_Init();
	fmem_Init();
	
	/* Startup Delay */
	utils_Delay(3000);
	
	matrix_Init();
	
	usart_Init(9600);
	
	pdisplay_Init();
	pdisplay_SetBrightness(eeprom_ReadByte(MEM_BRIGHTNESS));
	utils_Delay(10);

	/* -- Manual Prayer time input --
	_stRTime =	(stRealTime) {19, 1, 18, 0, 0, 0};
									
	_stPTime[0] = (stPrayerTime) { 4, 17 };
	_stPTime[1] = (stPrayerTime) { 4, 27 };
	_stPTime[2] = (stPrayerTime) { 5, 48 };
	_stPTime[3] = (stPrayerTime) { 12, 4 };
	_stPTime[4] = (stPrayerTime) { 15, 28 };
	_stPTime[5] = (stPrayerTime) { 18, 18 };
	_stPTime[6] = (stPrayerTime) { 19, 32 };
						
	ptime_SetPrayerTime(_stRTime, &_stPTime);

	_stRTime =	(stRealTime) {19, 1, 19, 0, 0, 0};
									
	_stPTime[0] = (stPrayerTime) { 4, 17 };
	_stPTime[1] = (stPrayerTime) { 4, 27 };
	_stPTime[2] = (stPrayerTime) { 5, 48 };
	_stPTime[3] = (stPrayerTime) { 12, 4 };
	_stPTime[4] = (stPrayerTime) { 15, 28 };
	_stPTime[5] = (stPrayerTime) { 18, 18 };
	_stPTime[6] = (stPrayerTime) { 19, 32 };
						
	ptime_SetPrayerTime(_stRTime, &_stPTime);
	*/

	while(1)
	{			
		/*--------------------------------------------*/
		/*----------- MAIN DISPLAY SECTION -----------*/
		/*--------------------------------------------*/
		
		if(eDispStatus == RUN)
		{
			switch(param_mode)
			{
				/*--------------------------------------------*/
				/*---------- MAIN DISPLAY SEQUENCE -----------*/
				/*--------------------------------------------*/
				
				case MODE_SMALLMESSAGE :
					pdisplay_SetMode(MODE_SMALLMESSAGE, param_message, nPTimeSel);
					utils_Delay(param_delay);
					
					if(pdisplay_nCounter >= param_iteration)
					{
						eDispStatus = IDLE;
						pdisplay_nCounter = 0;
						
						matrix_ScreenClear(BLACK);
					}
					break;
					
				case MODE_BIGMESSAGE :
					pdisplay_SetMode(MODE_BIGMESSAGE, param_message, NULL);
					utils_Delay(param_delay);
					
					if(pdisplay_nCounter >= param_iteration)
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						
						eDispStatus = IDLE;
					}
					break;
				
				case MODE_DATETIME :
					pdisplay_SetMode(MODE_DATETIME, NULL, nPTimeSel);
					utils_Delay(param_delay);
					
					if(pdisplay_nCounter >= param_iteration * 5)
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
											
						eDispStatus = IDLE;
					}
					break;
					
				case MODE_HIJRIDATE :
					pdisplay_SetMode(MODE_HIJRIDATE, NULL, nPTimeSel);
					utils_Delay(param_delay);
					
					if(pdisplay_nCounter >= param_iteration * 5)
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
											
						eDispStatus = IDLE; 
					}
					break;

				/* Skip for Jumuah Text */
				case MODE_JUMUAH :
					/* Quit event */
					param_mode = SEQ_QUIT_EVENT;
					break;
				
				/*--------------------------------------------*/
				/*------- PRAYER TIME DISPLAY SEQUENCE -------*/
				/*--------------------------------------------*/
				
				case SEQ_ENTER_EVENT :
					matrix_ScreenClear(BLACK);
					
					/* Enter Adzan Counter Setup */
					param_mode = SEQ_SET_ADZANCOUNTER;
					break;
				
				case SEQ_SET_ADZANCOUNTER :
					/* Initialize Counter for Adzan */
					nPTimeCounter = 60;
					
					/* Enter Adzan Countdown */
					param_mode = SEQ_RUN_ADZANCOUNTER;
					break;
					
				case SEQ_RUN_ADZANCOUNTER :
					pdisplay_SetMode(MODE_COUNTDOWN, NULL, nPTimeSel);
					utils_Delay(15);
					
					if(pdisplay_nCounter >= 60 || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						bButtonState = '\0';
						
						ptime_SetBuzzer(1);
						utils_Delay(BUZZER_DELAY);
						ptime_SetBuzzer(0);
						
						/* Enter Adzan Message */
						param_mode = SEQ_RUN_ADZANMESSAGE;
					}
					break;
					
				case SEQ_RUN_ADZANMESSAGE :
					pdisplay_SetMode(MODE_PRAYERTIME, NULL, nPTimeSel);
					utils_Delay(15);
					
					if(pdisplay_nCounter >= 3 || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						
						if(nPTimeSel == 0 || nPTimeSel == 2) 
						{
							/* If Imsyak or Isyraq */
							param_mode = SEQ_QUIT_EVENT;
						}
#if 0
						/* EVENT_JUMUAH handle updated below */
						else if(eEvent == EVENT_JUMUAH)
						{
							nCounter = (30 * 60);
							
							/* If Jumuah */
							param_mode = SEQ_POWERSAVE;
						}
#endif
						else
						{
							/* Enter Adzan Idle */
							param_mode = SEQ_RUN_ADZANIDLE;
						}
					}
					break;
				
				case SEQ_RUN_ADZANIDLE :
					pdisplay_SetMode(MODE_BLANK, NULL, NULL);
					utils_Delay(15);
					
					if(pdisplay_nCounter >= (bPTimeIdle[0] * 60) || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						bButtonState = '\0';
						
						ptime_SetBuzzer(1);
						utils_Delay(BUZZER_DELAY);
						ptime_SetBuzzer(0);
						
						/* Enter Iqamah Counter */
						param_mode = SEQ_SET_IQAMAHCOUNTER;
					}
					break;
				
				case SEQ_SET_IQAMAHCOUNTER :	
					/* Initialize Counter for Iqamah */
					nPTimeCounter = (nIqamahList[nPTimeSel] * 60);
										
					/* Enter Iqamah Countdown */
					param_mode = SEQ_RUN_IQAMAHCOUNTER;
					break;
				
				case SEQ_RUN_IQAMAHCOUNTER:
					pdisplay_SetMode(MODE_COUNTDOWN, NULL, 10);
					utils_Delay(15);
					
					if(pdisplay_nCounter >= (nIqamahList[nPTimeSel] * 60) || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						bButtonState = '\0';
						
						ptime_SetBuzzer(1);
						utils_Delay(BUZZER_DELAY);
						ptime_SetBuzzer(0);
						
						param_mode = SEQ_RUN_PRAYERIDLE;
					}
					break;
					
				case SEQ_RUN_PRAYERIDLE:
					pdisplay_SetMode(MODE_BLANK, NULL, NULL);
					utils_Delay(15);
					
					if(pdisplay_nCounter >= (bPTimeIdle[1] * 60) || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						bButtonState = '\0';
						
						/* Quit event */
						param_mode = SEQ_QUIT_EVENT;
					}
					break;
					
				case SEQ_POWERSAVE:
					pdisplay_SetMode(MODE_POWERSAVE, NULL, NULL);
					utils_Delay(15);
					
					if(pdisplay_nCounter >= nCounter || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_SetBrightness(eeprom_ReadByte(MEM_BRIGHTNESS));
						pdisplay_nCounter = 0;
						bButtonState = '\0';
						
						/* Quit event */
						param_mode = SEQ_QUIT_EVENT;
					}
					break;
				
				case SEQ_SET_PREJUMUAHMESSAGE:
					/* Read Jumuah message */
					memset(&_message, '\0', PARAM_MAX_LEN);
						
					fmem_ReadString(((PARAM_MAX_TASK - 1) * PARAM_MAX_LEN) + 3, &param_message);
					
					param_delay = 10;
					pdisplay_nCounter = 0;

					nCounter = (MINUTES_TO_JUMUAH - 1) * 60;

					matrix_ScreenClear(BLACK);

					/* Run Pre-Jumuah message */
					eDispStatus = RUN;
					param_mode	= SEQ_RUN_PREJUMUAHMESSAGE;
					break;
				
				case SEQ_RUN_PREJUMUAHMESSAGE:
					pdisplay_SetMode(MODE_BIGMESSAGE2, param_message, NULL);
					utils_Delay(param_delay);
					
					if(pdisplay_nCounter >= nCounter || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						bButtonState = '\0';
						
						nCounter = 60;
						nPTimeCounter = nCounter;
						param_mode = SEQ_RUN_JUMUAHCOUNTER;
					}
					break;

				case SEQ_RUN_JUMUAHCOUNTER:
					pdisplay_SetMode(MODE_COUNTDOWN, NULL, 3);
					utils_Delay(15);
					
					if(pdisplay_nCounter >= nCounter || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						bButtonState = '\0';
						
						ptime_SetBuzzer(1);
						utils_Delay(BUZZER_DELAY);
						ptime_SetBuzzer(0);
						
						/* Enter Jumuah Adzan Message */
						param_mode = SEQ_SET_JUMUAHMESSAGE;
					}
					break;

				case SEQ_SET_JUMUAHMESSAGE:
					pdisplay_SetMode(MODE_PRAYERTIME, NULL, 3);
					utils_Delay(15);
					
					if(pdisplay_nCounter >= 3 || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						
						nCounter = 15;
						pdisplay_nCounter = 0;

						param_mode = SEQ_RUN_JUMUAHMESSAGE;
					}
					break;

				case SEQ_RUN_JUMUAHMESSAGE:
					pdisplay_SetMode(MODE_BIGMESSAGE, param_message, NULL);
					utils_Delay(param_delay);
					
					if(pdisplay_nCounter >= nCounter || GPIO_ReadInputData(BUTTON_GPIO) & (BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */ ))
					{
						matrix_ScreenClear(BLACK);
						pdisplay_nCounter = 0;
						bButtonState = '\0';
						
						nCounter = MINUTES_TO_JUMUAH * 60;
						param_mode = SEQ_POWERSAVE;
						pdisplay_SetBrightness(1);
					}
					break;
				
				case SEQ_QUIT_EVENT:
					/* Reset Task */
					nTask = 0;
					eDispStatus = IDLE;
					eEvent = EVENT_NONE;
					break;
				
				default:
					nTask = 0;
					pdisplay_nCounter = 0;
					eDispStatus = IDLE;
					break;
			}
		}
		
		/*--------------------------------------------*/
		/*---------- DISPLAY PARAMETER SCAN ----------*/
		/*--------------------------------------------*/
		
		if(eEvent == EVENT_NONE)
		{
			/* Switch to next task when display is idle */
			if(eDispStatus == IDLE)
			{
				/* Load Display Parameters */
				pdisplay_GetParam(nTask, &param_message, &param_mode, &param_delay, &param_iteration);
				
				if(param_mode >= MODE_MAXNUM)
				{
					param_mode = 1;
					param_delay = 15;
					param_iteration = 1;
					
					utils_Concat("EMPTY MESSAGE", "", "", &param_message);
				}
				
				/* Assign next Task */
				nTask++;
				if(nTask > PARAM_MAX_TASK)
				{
					/* Reset Task */
					nTask = 0;
				}
				
				/* Run Display */
				eDispStatus = RUN;
			}
		}
		else if(param_mode < SEQ_ENTER_EVENT)
		{
			/*--------------------------------------------*/
			/*-------------- EVENT HANDLING --------------*/
			/*--------------------------------------------*/
						
			switch(eEvent)
			{
				case EVENT_IMSYAK :
					param_mode = SEQ_ENTER_EVENT;
					nPTimeSel = 0;
					break;
					
				case EVENT_SUBUH :
					param_mode = SEQ_ENTER_EVENT;
					nPTimeSel = 1;
					break;
					
				case EVENT_SYURUQ :
					param_mode = SEQ_ENTER_EVENT;
					nPTimeSel = 2;
					break;
					
				case EVENT_JUMUAH :
					param_mode = SEQ_SET_PREJUMUAHMESSAGE;
					nPTimeSel = 3;
					break;

				case EVENT_DZUHUR :
					param_mode = SEQ_ENTER_EVENT;
					nPTimeSel = 3;
					break;
					
				case EVENT_ASHAR :
					param_mode = SEQ_ENTER_EVENT;
					nPTimeSel = 4;
					break;
					
				case EVENT_MAGHRIB :
					param_mode = SEQ_ENTER_EVENT;
					nPTimeSel = 5;
					break;
					
				case EVENT_ISYA :
					param_mode = SEQ_ENTER_EVENT;
					nPTimeSel = 6;
					break;
					
				case EVENT_PWRSAVE :
					nCounter = (stPwrSave.Duration  * 60);
					param_mode = SEQ_POWERSAVE;
					matrix_ScreenClear(BLACK);
					pdisplay_SetBrightness(1);
					break;
			}
			
			/* Run Display */
			eDispStatus = RUN;
		}
		
		/*--------------------------------------------*/
		/*------- TIME UPDATE & EVENT CHECK ----------*/
		/*--------------------------------------------*/
		
		if(_bColonState != bColonState)
		{
			/* Toggle colon state */
			_bColonState = bColonState;
			
			/* Update Time Data */
			ptime_GetRTCTime(&stRTime);
				
			/* Check Event */
			ptime_ReadEvent();
			
			/* Check for New Day */
			if(bCurrentDate != stRTime.date)
			{
				ptime_GetPrayerTime(stRTime, &stPTime);
				
				bCurrentDate = stRTime.date;
			}
			
			/* Change Prayer Time Selector every 3 second */
			if(stRTime.second % 3 == 0 && eEvent == EVENT_NONE)
			{
				nPTimeSel = (nPTimeSel + 1) % MAX_PRAYERTIME;
			}
		}
		
		/*--------------------------------------------*/
		/*---------- SERIAL COMMAND CHECK ------------*/
		/*--------------------------------------------*/
		
		if(usart_GetLastChar() == '#')
		{
			bCmdState = 0;
			
			switch(usart_sMessage[usart_nIndex - 2])
			{
				/* Message Write Command */
				case '&' :
					memset(&_message, '\0', PARAM_MAX_LEN);
					memcpy(&_message, &usart_sMessage, usart_nIndex - 3);
					
					/* String Address --> [usart_nIndex - 3] */
					fmem_WriteString((uint16_t)(usart_sMessage[usart_nIndex - 3] - '0') * PARAM_MAX_LEN, &_message, usart_nIndex - 3);
					
					fmem_ApplyBuffer();
					
					nTask = usart_sMessage[usart_nIndex - 3] - '0';
					eDispStatus = IDLE;
					pdisplay_nCounter = 0;
					matrix_ScreenClear(BLACK);
					
					bCmdState = 1;
					/* usart_puts("Message Update OK\n\r"); */ /* Notification disabled for Message Read from Application */
					usart_ClearMessage();
					break;
					
				/* Message Read Command */
				case '"' :
					if(usart_sMessage[0] == 'R')
					{
						memset(&_message, '\0', PARAM_MAX_LEN);
						
						fmem_ReadString((usart_sMessage[1] - '0') * PARAM_MAX_LEN, &_message);
						
						bCmdState = 1;

						/* Send current stored message */
						usart_puts(_message);
					}
					else
					{
						usart_puts("NG");
					}

					usart_ClearMessage();
					break;
				
				/* Prayer Time Command */
				case '!' :
					if(usart_nIndex - 1 == 18)
					{
						_stRTime =	(stRealTime) {usart_sMessage[0], usart_sMessage[1], usart_sMessage[2], 0, 0, 0};
									
						_stPTime[0] = (stPrayerTime) { usart_sMessage[ 3], usart_sMessage[ 4] - 1 };
						_stPTime[1] = (stPrayerTime) { usart_sMessage[ 5], usart_sMessage[ 6] - 1 };
						_stPTime[2] = (stPrayerTime) { usart_sMessage[ 7], usart_sMessage[ 8] - 1 };
						_stPTime[3] = (stPrayerTime) { usart_sMessage[ 9], usart_sMessage[10] - 1 };
						_stPTime[4] = (stPrayerTime) { usart_sMessage[11], usart_sMessage[12] - 1 };
						_stPTime[5] = (stPrayerTime) { usart_sMessage[13], usart_sMessage[14] - 1 };
						_stPTime[6] = (stPrayerTime) { usart_sMessage[15], usart_sMessage[16] - 1 };
						
						ptime_SetPrayerTime(_stRTime, &_stPTime);
						
						ptime_GetPrayerTime(stRTime, &stPTime);
						utils_Delay(3);
						
						usart_puts("Prayer Time Update OK\n\r");
					}
					else
					{
						usart_puts("NG");
					}
					
					usart_ClearMessage();
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
						
						nTask = PARAM_MAX_TASK + 1;
						rtc_Init(SQW_1HZ);
						ptime_GetRTCTime(&stRTime);
						ptime_GetPrayerTime(stRTime, &stPTime);
						utils_Delay(10);
						
						bCmdState = 1;
						usart_puts("RTC update OK\n\r");
				
						usart_puts("\n\rDay: ");
						usart_puti(stRTime.day);
						usart_puts("\n\r");
					}
					else
					{
						usart_puts("NG\n\r");
					}
					
					usart_ClearMessage();
					break;
				
				/* Brigtness Command */
				case '%' :
					if(usart_nIndex - 1 == 6)
					{
						if(usart_sMessage[0] == 'B' && usart_sMessage[1] == 'R' && usart_sMessage[2] == 'G')
						{
							eeprom_WriteByte(MEM_BRIGHTNESS, ((usart_sMessage[3] - '0') * 10) + (usart_sMessage[4] - '0') + 1);
							utils_Delay(10);
							
							pdisplay_SetBrightness(eeprom_ReadByte(MEM_BRIGHTNESS));
							
							bCmdState = 1;
							usart_puts("Brightness Update OK\n\r");
						}
					}
					else
					{
						usart_puts("NG\n\r");
					}
					
					usart_ClearMessage();
					break;
				
				/* Iqamah Command */
				case '^' :
					if(usart_nIndex - 1 == 11)
					{
						eeprom_WriteByte(MEM_IQAMAH_SUB, ((usart_sMessage[0] - '0') * 10) + (usart_sMessage[1] - '0'));
						eeprom_WriteByte(MEM_IQAMAH_DZU, ((usart_sMessage[2] - '0') * 10) + (usart_sMessage[3] - '0'));
						eeprom_WriteByte(MEM_IQAMAH_ASH, ((usart_sMessage[4] - '0') * 10) + (usart_sMessage[5] - '0'));
						eeprom_WriteByte(MEM_IQAMAH_MAG, ((usart_sMessage[6] - '0') * 10) + (usart_sMessage[7] - '0'));
						eeprom_WriteByte(MEM_IQAMAH_ISY, ((usart_sMessage[8] - '0') * 10) + (usart_sMessage[9] - '0'));
						
						ptime_GetIqamahTime(&nIqamahList);
						
						bCmdState = 1;
						usart_puts("Iqamah Update OK\n\r");
					}
					else
					{
						usart_puts("NG\n\r");
					}
					
					usart_ClearMessage();
					break;
				
				/* Powersave Command */
				case '$' :
					if(usart_nIndex - 1 == 8)
					{
						ptime_SetPowerSave(	( (usart_sMessage[0] - '0') * 10)	+ usart_sMessage[1] - '0',
											( (usart_sMessage[2] - '0') * 10)	+ usart_sMessage[3] - '0',
											( (usart_sMessage[4] - '0') * 100)	+ ((usart_sMessage[5] - '0') * 10) + usart_sMessage[6] - '0');
						
						ptime_PowerSaveSetup(&stPwrSave);
						
						bCmdState = 1;
						usart_puts("Powersave Update OK\n\r");
					}
					else
					{
						usart_puts("NG\n\r");
					}
					
					usart_ClearMessage();
					break;
				
				/* Hijri Adjust Command */
				case '+' :
					if(usart_nIndex - 1 == 5)
					{
						if(usart_sMessage[0] == 'H' && usart_sMessage[1] == 'I')
						{
							eeprom_WriteByte(MEM_HIJRI_ADJUST, ((usart_sMessage[2] - '0') * 10) + (usart_sMessage[3] - '0'));
						}
						
						bCmdState = 1;
						usart_puts("Hijri Correction Update OK\n\r");
					}
					else
					{
						usart_puts("NG\n\r");
					}
					
					usart_ClearMessage();
					break;
				
				/* Idle Time Command */
				case '~' :
					if(usart_nIndex - 1 == 5)
					{
						ptime_SetIdleTime(	((usart_sMessage[0] - '0') * 10) + (usart_sMessage[1] - '0'),
											((usart_sMessage[2] - '0') * 10) + (usart_sMessage[3] - '0'));
						
						ptime_GetIdleTime(&bPTimeIdle[0], &bPTimeIdle[1]);
						
						bCmdState = 1;
						usart_puts("Idle Time update OK\n\r");
					}
					else
					{
						usart_puts("NG\n\r");
					}
					
					usart_ClearMessage();
					break;
				
				/* Color Change Command */
				case '}' :
					if(usart_nIndex - 1 == 7)
					{
						if(usart_sMessage[0] == '{')
						pdisplay_SetColor(MEM_CL_CLOCK, usart_sMessage[1] - '0');
						pdisplay_SetColor(MEM_CL_DATE,	usart_sMessage[2] - '0');
						pdisplay_SetColor(MEM_CL_TEXT,	usart_sMessage[3] - '0');
						pdisplay_SetColor(MEM_CL_PTIME, usart_sMessage[4] - '0');
						pdisplay_SetColor(MEM_CL_COUNT, usart_sMessage[5] - '0');
						
						pdisplay_Init();
						
						bCmdState = 1;
						usart_puts("Color update OK\n\r");
					}
					else
					{
						usart_puts("NG\n\r");
					}
					
					usart_ClearMessage();
					break;
				
				/* EEPROM Dump Command */
				case '>' :
					if(usart_sMessage[0] == 'R' && usart_sMessage[1] == 'D')
					{			
						monthIndex = ((usart_sMessage[2] - '0') * 10) + (usart_sMessage[3] - '0');
						
						readIndex = 0;
						for(iteration = 0; iteration < monthIndex - 1; iteration++)
						{
							readIndex += rtc_getDaysCount(iteration);
						}
						
						readIndex *= 10;
						
						usart_puts("\n\r\n\r-----EEPROM DUMP-----\n\r");
						for(iteration = readIndex; iteration < readIndex + (10 * rtc_getDaysCount(monthIndex)); iteration += 10)
						{
							usart_puti(eeprom_ReadByte(iteration + 0));
							usart_putc(':');
							usart_puti(eeprom_ReadByte(iteration + 1));
							usart_putc(',');
							usart_puti(eeprom_ReadByte(iteration + 2));
							usart_putc(':');
							usart_puti(eeprom_ReadByte(iteration + 3));
							usart_putc(',');
							usart_puti(eeprom_ReadByte(iteration + 4));
							usart_putc(':');
							usart_puti(eeprom_ReadByte(iteration + 5));
							usart_putc(',');
							usart_puti(eeprom_ReadByte(iteration + 6));
							usart_putc(':');
							usart_puti(eeprom_ReadByte(iteration + 7));
							usart_putc(',');
							usart_puti(eeprom_ReadByte(iteration + 8));
							usart_putc(':');
							usart_puti(eeprom_ReadByte(iteration + 9));
							usart_puts("\n\r");
						}				
					}
					
					usart_ClearMessage();
					break;
				
				/* Reset Command */
				case 'T' :
					if(usart_sMessage[0] == 'R' && usart_sMessage[1] == 'S')
					{
						NVIC_SystemReset();
					}
					
					usart_ClearMessage();
					break;
				
				/* Unknown Message */
				default :
					usart_puts("NG\n\r");
					
					usart_ClearMessage();
					break;
			}
			
			if(bCmdState == 1)
			{
				ptime_SetBuzzer(1);
				utils_Delay(100);
				ptime_SetBuzzer(0);
			}
		}

#ifdef ENABLE_BUTTON_DEBUG
		/*--------------------------------------------*/
		/*------------- READ BUTTON INPUT ------------*/
		/*--------------------------------------------*/
		if(GPIO_ReadInputData(BUTTON_GPIO) & BUTTON_PIN_A) //bButtonState == 'A' || 
		{
			usart_puts("A\n\r");
			utils_Delay(50);
			
			bButtonState = '\0';
		}
		if(GPIO_ReadInputData(BUTTON_GPIO) & BUTTON_PIN_B) //bButtonState == 'B')
		{
			usart_puts("B\n\r");
			utils_Delay(50);
			
			bButtonState = '\0';
		}
		//if(GPIO_ReadInputData(BUTTON_GPIO) & BUTTON_PIN_C) //bButtonState == 'C')
		//{
		//	usart_puts("C\n\r");
		//	utils_Delay(50);
		//	
		//	bButtonState = '\0';
		//}
#endif
	}
}
