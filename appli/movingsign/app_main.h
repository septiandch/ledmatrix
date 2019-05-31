/**
 *  Prayer Time Display Modes Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_

#include "dmd/dmdproc.h"
#include "peripherals/fmem.h"
#include "peripherals/rtc.h"
#include "utils.h"
#include "pgmspace.h"
#include "fonts/SystemFont.h"
#include "fonts/ArialBlack16.h"
#include "fonts/SansSerif25.h"
#include "img/icon.h"

/* DEFINITIONS */
#define PARAM_MAX_TASK				5
#define PARAM_MAX_LEN				81

#define MEM_BASE					0x0EA6
#define MEM_PWRSAVE_HOUR			(uint8_t)	(MEM_BASE + 0x00)
#define MEM_PWRSAVE_MINUTE			(uint8_t)	(MEM_BASE + 0x01)
#define MEM_PWRSAVE_DURATION		(uint16_t)	(MEM_BASE + 0x02)
#define MEM_BRIGHTNESS				(uint8_t)	(MEM_BASE + 0x04)

#define BUZZER_GPIO_RCC				RCC_APB2Periph_GPIOB
#define BUZZER_GPIO					GPIOB
#define BUZZER_PIN					GPIO_Pin_0

/* ENUMERATION */
typedef enum
{
	PARAM_NG = 0,
	PARAM_OK
} eParamStatus;

typedef struct
{
	uint8_t			hour;
	uint8_t			minute;
} stPrayerTime;

typedef enum
{
	MODE_POWERSAVE = 0,
	MODE_WELCOME,
	MODE_BIGMESSAGE,
	MODE_TITLEDMESSAGE,
	MODE_DATETIME,
	MODE_BLANK
} eDisplayMode;

typedef enum
{
	IDLE = 0,
	RUN
} eDisplayStatus;

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
	uint8_t		StartHour;
	uint8_t		StartMinute;
	uint16_t	Duration;
} stPowerSave;

/* STRUCTURES */

/* Global Variables */
extern uint16_t			nCounter;
extern stRealTime		stRTime;
extern stPowerSave		stPwrSave;

/* Function Prototypes */
extern void		app_Init(void);
extern void		app_SetMode(eDisplayMode mode, char *message);
extern void		app_GetParam(uint8_t addr, char *_str, uint8_t *_mode, uint8_t *_delay, uint8_t *_iteration);

#endif /* _APP_MAIN_H_ */
