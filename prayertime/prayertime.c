 /*
 *  Prayer Time Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#include "prayertime.h"

stRealTime		stRTime;
stPrayerTime	stPTime[MAX_PRAYERTIME];
stPowerSave		stPwrSave;
ePTimeEvent		eEvent = EVENT_NONE;
volatile char	bColonState = ':';
static uint8_t	bPTimeSequence = 0;
uint8_t			nIqamahList[MAX_PRAYERTIME];
uint8_t			bPTimeIdle[2];
uint16_t		nPTimeCounter;
volatile char	bButtonState = '\0';

void ptime_Init()
{		
	rtc_Init(SQW_1HZ);
	
	ptime_GetRTCTime(&stRTime);
	
	ptime_GetPrayerTime(stRTime, &stPTime);
	ptime_GetIqamahTime(&nIqamahList);
	ptime_GetIqamahTime(&nIqamahList);
	ptime_GetIdleTime(&bPTimeIdle[0], &bPTimeIdle[1]);
	
	ptime_PowerSaveSetup(&stPwrSave);
	
	ptime_GPIOConfig();
	ptime_ITConfig();
}

void ptime_GPIOConfig()
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	/** Enable GPIO clock */
	RCC_APB2PeriphClockCmd(BUTTON_GPIO_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(BUZZER_GPIO_RCC, ENABLE);
	
	/** Configure input */
	GPIO_InitStructure.GPIO_Pin = SQWOUT_PIN | BUTTON_PIN_A | BUTTON_PIN_B /* | BUTTON_PIN_C */;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(BUTTON_GPIO, &GPIO_InitStructure);
	
	/** Configure Output */
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BUZZER_GPIO, &GPIO_InitStructure);
}

void ptime_ITConfig()
{
	/** SQW Interrupt Configuration */
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/** Enable AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/** Connect EXTI Line to pin */
	GPIO_EXTILineConfig(GPIO_SQWPORT, GPIO_SQWPIN);
	
	/** Configure EXTI line */
	EXTI_InitStructure.EXTI_Line = EXTI_SQW_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/** Set Interrupt priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI_SQW_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{   
		bButtonState = 'C';
		
		/* Clear the  EXTI line 13 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	
	if(EXTI_GetITStatus(EXTI_Line14) != RESET)
	{    		
		bButtonState = 'B';
		
		/* Clear the  EXTI line 14 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	
	if(EXTI_GetITStatus(EXTI_Line15) != RESET)
	{    		
		bButtonState = 'A';
		
		/* Clear the  EXTI line 15 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}

void EXTI_SQW_IRQHandler(void)
{
	/** SQW Interrupt Handler */
	if(EXTI_GetITStatus(EXTI_SQW_Line) != RESET)
	{    		
		if(bColonState == ':')
		{
			bColonState = ' ';
		}
		else
		{
			bColonState = ':';
		}
		
		/* Clear the  EXTI line 5 pending bit */
		EXTI_ClearITPendingBit(EXTI_SQW_Line);
	}
}

void ptime_SetBuzzer(uint8_t state)
{
	if(state == 1)
	{
		BUZZER_GPIO->BSRR = BUZZER_PIN;
	}
	else
	{	
		BUZZER_GPIO->BRR = BUZZER_PIN;
	}
}


uint16_t ptime_TimeToMins(uint8_t hour, uint8_t minute)
{
	return (hour * 60) + minute;
}

uint16_t ptime_BytesToPTime(uint8_t _high, uint8_t _low)
{
	/** Null char input */
	if(_high == 100) _high = 0;
	if(_low == 100) _low = 0;
	
	return (_high * 100) + _low;
}

void ptime_GetRTCTime(stRealTime *pstRealTime)
{
	rtc_readTime(	&pstRealTime->year, 
					&pstRealTime->month, 
					&pstRealTime->date, 
					&pstRealTime->day, 
					&pstRealTime->hour, 
					&pstRealTime->minute, 
					&pstRealTime->second	);				
}

void ptime_SetPrayerTime(stRealTime pstRealTime, stPrayerTime *pstPrayerTime)
{
	int16_t		nTotaldays	= pstRealTime.date - 1;
	int16_t		i			= 0;
	
	for(i = 0; i < pstRealTime.month - 1; i++)
	{
		nTotaldays += rtc_getDaysCount(i);
	}
	
#ifndef USE_32KMEM    
	nTotaldays *= 14;
	                   
	for(i = 0; i < MAX_PRAYERTIME; i++)
	{
		eeprom_WriteByte(nTotaldays + (i * 2) + 0, pstPrayerTime[i].hour);
		eeprom_WriteByte(nTotaldays + (i * 2) + 1, pstPrayerTime[i].minute);
	}

#else
	nTotaldays *= 10;
		
	eeprom_WriteByte(nTotaldays + 0, pstPrayerTime[1].hour);
	eeprom_WriteByte(nTotaldays + 1, pstPrayerTime[1].minute);
	eeprom_WriteByte(nTotaldays + 2, pstPrayerTime[3].hour);
	eeprom_WriteByte(nTotaldays + 3, pstPrayerTime[3].minute);
	eeprom_WriteByte(nTotaldays + 4, pstPrayerTime[4].hour);
	eeprom_WriteByte(nTotaldays + 5, pstPrayerTime[4].minute);
	eeprom_WriteByte(nTotaldays + 6, pstPrayerTime[5].hour);
	eeprom_WriteByte(nTotaldays + 7, pstPrayerTime[5].minute);
	eeprom_WriteByte(nTotaldays + 8, pstPrayerTime[6].hour);
	eeprom_WriteByte(nTotaldays + 9, pstPrayerTime[6].minute);
#endif
}

void ptime_GetPrayerTime(stRealTime pstRealTime, stPrayerTime *pstPrayerTime)
{		
	int16_t		nTotaldays	= pstRealTime.date - 1;
	int16_t		i			= 0;
	
	for(i = 0; i < pstRealTime.month - 1; i++)
	{
		nTotaldays += rtc_getDaysCount(i);
	}
	
#ifndef USE_32KMEM     
	nTotaldays *= 14;
	
	for(i = 0; i < MAX_PRAYERTIME; i++)
	{
		pstPrayerTime[i].hour		= (uint8_t) eeprom_ReadByte(nTotaldays + (i * 2) + 0);
		pstPrayerTime[i].minute		= (uint8_t) eeprom_ReadByte(nTotaldays + (i * 2) + 1);
	}
	
#else  
	nTotaldays *= 10;
	
	pstPrayerTime[1].hour		= (uint8_t) eeprom_ReadByte(nTotaldays + 0);
	pstPrayerTime[1].minute		= (uint8_t) eeprom_ReadByte(nTotaldays + 1);
	pstPrayerTime[3].hour		= (uint8_t) eeprom_ReadByte(nTotaldays + 2);
	pstPrayerTime[3].minute		= (uint8_t) eeprom_ReadByte(nTotaldays + 3);
	pstPrayerTime[4].hour		= (uint8_t) eeprom_ReadByte(nTotaldays + 4);
	pstPrayerTime[4].minute		= (uint8_t) eeprom_ReadByte(nTotaldays + 5);
	pstPrayerTime[5].hour		= (uint8_t) eeprom_ReadByte(nTotaldays + 6);
	pstPrayerTime[5].minute		= (uint8_t) eeprom_ReadByte(nTotaldays + 7);
	pstPrayerTime[6].hour		= (uint8_t) eeprom_ReadByte(nTotaldays + 8);
	pstPrayerTime[6].minute		= (uint8_t) eeprom_ReadByte(nTotaldays + 9);
		
	/* Set Imsyak time */
	i = (pstPrayerTime[1].hour * 60) + pstPrayerTime[1].minute - 10;
	pstPrayerTime[0].hour		= (uint8_t) (i / 60);
	pstPrayerTime[0].minute		= (uint8_t) (i - (pstPrayerTime[0].hour * 60));
	
	/* Set Sunrise time */
	i = (pstPrayerTime[1].hour * 60) + pstPrayerTime[1].minute + 90;
	pstPrayerTime[2].hour		= (uint8_t) (i / 60);
	pstPrayerTime[2].minute		= (uint8_t) (i - (pstPrayerTime[2].hour * 60));
#endif
}

void ptime_GetIdleTime(uint8_t *nAdzanIdle, uint8_t *nPrayerIdle)
{
	*nAdzanIdle		= eeprom_ReadByte(MEM_ADZAN_IDLE);
	*nPrayerIdle	= eeprom_ReadByte(MEM_PRAYER_IDLE);
}

void ptime_SetIdleTime(uint8_t nAdzanIdle, uint8_t nPrayerIdle)
{
	eeprom_WriteByte(MEM_ADZAN_IDLE, nAdzanIdle);
	eeprom_WriteByte(MEM_PRAYER_IDLE, nPrayerIdle);
}

void ptime_SetPowerSave(uint8_t StartHour, uint8_t StartMinute, uint16_t Duration)
{
	eeprom_WriteByte(MEM_PWRSAVE_HOUR, StartHour);
	eeprom_WriteByte(MEM_PWRSAVE_MINUTE, StartMinute);
	eeprom_WriteByte(MEM_PWRSAVE_DURATION, (uint8_t)((Duration >> 8) & 0xFF));
	eeprom_WriteByte(MEM_PWRSAVE_DURATION + 1, (uint8_t)(Duration & 0xFF));
}

void ptime_PowerSaveSetup(stPowerSave *_stPwrSave)
{
	_stPwrSave->StartHour		= eeprom_ReadByte(MEM_PWRSAVE_HOUR);
	_stPwrSave->StartMinute		= eeprom_ReadByte(MEM_PWRSAVE_MINUTE);
	_stPwrSave->Duration		= (uint16_t) (eeprom_ReadByte(MEM_PWRSAVE_DURATION) << 8) | eeprom_ReadByte(MEM_PWRSAVE_DURATION + 1);
}

void ptime_GetIqamahTime(uint8_t * nIqamahMins)
{
#ifdef TIMECOMPACT_DEBUG
	nIqamahMins[1] = 1;
	nIqamahMins[3] = 1;
	nIqamahMins[4] = 1;
	nIqamahMins[5] = 1;
	nIqamahMins[6] = 1;
#else
	nIqamahMins[1] = eeprom_ReadByte(MEM_IQAMAH_SUB);
	nIqamahMins[3] = eeprom_ReadByte(MEM_IQAMAH_DZU);
	nIqamahMins[4] = eeprom_ReadByte(MEM_IQAMAH_ASH);
	nIqamahMins[5] = eeprom_ReadByte(MEM_IQAMAH_MAG);
	nIqamahMins[6] = eeprom_ReadByte(MEM_IQAMAH_ISY);
#endif
}

void ptime_GetHijriah(stRealTime *pstRealTime, stRealTime *pstHijriTime)
{
	/* Reff: https://www.academia.edu/23484476/CARA_MEMBUAT_KALENDER_MASEHI_DAN_KONVERSI */
	
	uint32_t	dayCount			= 0;
	uint32_t	cycle				= (uint16_t)((pstRealTime->year + 1999) / 4);
	uint32_t	remains				= (uint16_t)(pstRealTime->year + 1999) % 4;
	uint16_t	i					= 0;
	uint8_t		month_count[12]		= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	uint8_t		hmonth_count[12]	= {30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29};
	
	*pstHijriTime = *pstRealTime;
	
	/* Normalize Month */
	pstHijriTime->month--;
	
	/* Cycle to day count */
	dayCount = cycle * 1461;
	
	/* Remains to day count */
	dayCount = dayCount + (remains * 365);
	
	//Days int month count */
	for(i = 0; i < pstHijriTime->month; i++) 
	{
		dayCount = dayCount + month_count[i];	
	}
	
	/* Add date count */
	dayCount = dayCount + (pstHijriTime->date + (eeprom_ReadByte(MEM_HIJRI_ADJUST) - 5));
	
	/* Check if the year is a leap year */
	if((pstHijriTime->year % 400 == 0) || (pstHijriTime->year % 4 == 0 && pstHijriTime->year % 100 != 0))
	{
		dayCount++;
	}
	
	/* Hijriah-Gregorian Gap (Tafawut) correction */
	dayCount = dayCount - 227016;
	
	/* Gregorian correction (13) */
	dayCount = dayCount - 13;
	
	/* Hijri year leap */
	remains = dayCount % 10631;
	
	/* Calculate Hijri Year, mod 1400 to fit in 1 byte */
	pstHijriTime->year = ((((uint16_t)(dayCount / 10631) * 30) + (remains / 354)) % 1400) + 1;
	
	/* Get Hijri Date */
	remains = (uint32_t)((remains * 100 % (1063100 / 30)) / 100);
	
	dayCount = 0;
	for(i = 0; i < 12; i++)
	{
		dayCount = dayCount + hmonth_count[i];
		pstHijriTime->month = i;
		
		if(dayCount >= remains)
		{
			dayCount = dayCount - hmonth_count[i];
			break;
		}
	}
	
	pstHijriTime->date = remains - dayCount;
	
	/* If the Date is 00 */
	if(pstHijriTime->date == 0)
	{
		pstHijriTime->date = 1;
	}
}

void ptime_ReadEvent()
{	
	uint16_t	nCurrentTime = 0;
		
	/* Current time plus MINUTES_TO_ADZAN for countdown */
	nCurrentTime = ptime_TimeToMins(stRTime.hour, stRTime.minute) + MINUTES_TO_ADZAN;
	
	if(nCurrentTime == ptime_TimeToMins(stPTime[0].hour, stPTime[0].minute))
	{
		eEvent = EVENT_IMSYAK;
	}
	else if(nCurrentTime == ptime_TimeToMins(stPTime[1].hour, stPTime[1].minute))
	{
		eEvent = EVENT_SUBUH;
	}
	else if(nCurrentTime == ptime_TimeToMins(stPTime[2].hour, stPTime[2].minute))
	{
		eEvent = EVENT_SYURUQ;
	}
	else if(nCurrentTime == ptime_TimeToMins(stPTime[3].hour, stPTime[3].minute))
	{
		/** Check if current time entering jumuah time */
		if(stRTime.day == 5)
		{
			eEvent = EVENT_JUMUAH;
		}
		else eEvent = EVENT_DZUHUR;
	}
	else if(nCurrentTime == ptime_TimeToMins(stPTime[4].hour, stPTime[4].minute))
	{
		eEvent = EVENT_ASHAR;
	}
	else if(nCurrentTime == ptime_TimeToMins(stPTime[5].hour, stPTime[5].minute))
	{
		 eEvent = EVENT_MAGHRIB;
	}
	else if(nCurrentTime == ptime_TimeToMins(stPTime[6].hour, stPTime[6].minute))
	{
		eEvent = EVENT_ISYA;
	}
	else if(nCurrentTime - MINUTES_TO_ADZAN == ptime_TimeToMins(stPwrSave.StartHour, stPwrSave.StartMinute))
	{
		eEvent = EVENT_PWRSAVE;
	}
	else
	{
		/* Commented Out, need to reset event manually */
		/* eEvent = EVENT_NONE; */
	}
}
