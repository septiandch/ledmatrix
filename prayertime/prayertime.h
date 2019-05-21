 /*
 *  Prayer Time Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _PRAYERTIME_H
#define _PRAYERTIME_H

#include "pgmspace.h"
#include "stm32f10x.h"
#include "../peripherals/usart.h"
#include "../peripherals/rtc.h"
#include "../peripherals/at24cxx.h"

#ifdef TIMECOMPACT_DEBUG
#	define MINUTES_TO_ADZAN			1
#	define MINUTES_WAIT_ADZAN		1
#	define MINUTES_TO_JUMUAH		1
#	define MINUTES_PRAYER_TIME		1 
#	define SECONDS_TO_ADZAN			10
#	define SECONDS_TO_IQAMAH		1
#else
#	define MINUTES_TO_ADZAN			1
#	define MINUTES_WAIT_ADZAN		10
#	define MINUTES_TO_JUMUAH		40
#	define MINUTES_PRAYER_TIME		10 
#	define SECONDS_TO_ADZAN			6
#	define SECONDS_TO_IQAMAH		2
#endif

#define	USE_32KMEM

#define MEM_BASE					0x0EA6
#define MEM_PWRSAVE_HOUR			(uint16_t) (MEM_BASE + 0x00)
#define MEM_PWRSAVE_MINUTE			(uint16_t) (MEM_BASE + 0x01)
#define MEM_PWRSAVE_DURATION		(uint16_t) (MEM_BASE + 0x02)
#define MEM_IQAMAH_SUB				(uint8_t)  (MEM_BASE + 0x04)
#define MEM_IQAMAH_DZU				(uint8_t)  (MEM_BASE + 0x05)
#define MEM_IQAMAH_ASH				(uint8_t)  (MEM_BASE + 0x06)
#define MEM_IQAMAH_MAG				(uint8_t)  (MEM_BASE + 0x07)
#define MEM_IQAMAH_ISY				(uint8_t)  (MEM_BASE + 0x08)
#define MEM_ADZAN_IDLE				(uint8_t)  (MEM_BASE + 0x09)
#define MEM_PRAYER_IDLE				(uint8_t)  (MEM_BASE + 0x0A)
#define MEM_HIJRI_ADJUST			(uint8_t)  (MEM_BASE + 0x0B)
#define MEM_BRIGHTNESS				(uint8_t)  (MEM_BASE + 0x0C)

#define BUTTON_GPIO_RCC				RCC_APB2Periph_GPIOA
#define BUTTON_GPIO					GPIOA
#define BUTTON_PIN_A				GPIO_Pin_6
#define BUTTON_PIN_B				GPIO_Pin_7
/* #define BUTTON_PIN_C				GPIO_Pin_13 */
		
#define BUZZER_GPIO_RCC				RCC_APB2Periph_GPIOB
#define BUZZER_GPIO					GPIOB
#define BUZZER_PIN					GPIO_Pin_0
#define BUZZER_DELAY				500
		
#define SQWOUT_PIN					GPIO_Pin_1
#define GPIO_SQWPORT				GPIO_PortSourceGPIOB
#define GPIO_SQWPIN					GPIO_PinSource1
#define EXTI_SQW_IRQn				EXTI1_IRQn
#define EXTI_SQW_IRQHandler			EXTI1_IRQHandler
#define EXTI_SQW_Line				EXTI_Line1

#define MAX_PRAYERTIME				7

typedef enum
{
	EVENT_NONE = 0,
	EVENT_IMSYAK,
	EVENT_SUBUH,
	EVENT_SYURUQ,
	EVENT_DZUHUR,
	EVENT_ASHAR,
	EVENT_MAGHRIB,
	EVENT_ISYA,
	EVENT_JUMUAH,
	EVENT_PWRSAVE
} ePTimeEvent;

typedef enum
{
	PTIME_DISABLE = 0,
	PTIME_ENABLE
} ePTimeState;

typedef struct
{
	int8_t		year;
	int8_t		month;
	int8_t		date;
	int8_t		day;
	int8_t		hour;
	int8_t		minute;
	int8_t		second;
} stRealTime;

typedef struct
{
	uint8_t			hour;
	uint8_t			minute;
} stPrayerTime;

typedef struct
{
	uint8_t		StartHour;
	uint8_t		StartMinute;
	uint16_t	Duration;
} stPowerSave;

extern stRealTime		stRTime;
extern stPrayerTime		stPTime[MAX_PRAYERTIME];
extern stPowerSave		stPwrSave;
extern ePTimeEvent		eEvent;
extern volatile char	bColonState;
extern uint8_t			nIqamahList[MAX_PRAYERTIME];
extern uint16_t			nPTimeCounter;
extern volatile char	bButtonState;
extern uint8_t			bPTimeIdle[2];

extern void 	ptime_Init(void);
extern void 	ptime_GPIOConfig(void);
extern void 	ptime_ITConfig(void);
extern void		ptime_SetBuzzer(uint8_t state);
extern void 	ptime_ReadEvent(void);
extern void 	ptime_SetupMode(void);
extern void 	ptime_GetRTCTime(stRealTime *pstRealTime);
extern void 	ptime_PowerSaveSetup(stPowerSave *_stPwrSave);
extern void		ptime_SetPowerSave(uint8_t StartHour, uint8_t StartMinute, uint16_t Duration);
extern void 	ptime_GetPrayerTime(stRealTime pstRealTime, stPrayerTime *pstPrayerTime);
extern void 	ptime_SetPrayerTime(stRealTime pstRealTime, stPrayerTime *pstPrayerTime);
extern void		ptime_GetIdleTime(uint8_t *nAdzanIdle, uint8_t *nPrayerIdle);
extern void		ptime_SetIdleTime(uint8_t nAdzanIdle, uint8_t nPrayerIdle);
extern void 	ptime_GetIqamahTime(uint8_t * nIqamahMins);
extern void 	ptime_GetHijriah(stRealTime *pstRealTime, stRealTime *pstHijriTime);
extern uint16_t ptime_TimeToMins(uint8_t hour, uint8_t minute);

#endif // _PRAYERTIME_H
