/**
 *  Moving Sign Display application
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_

#include "dmd/dmdproc.h"
#include "peripherals/fmem.h"
#include "peripherals/at24cxx.h"
#include "peripherals/rtc.h"
#include "peripherals/usart.h"
#include "utils.h"
#include "pgmspace.h"
#include "fonts/SystemFont.h"
#include "fonts/ArialBlack16.h"
#include "fonts/Unispace18.h"
#include "fonts/MonoFonto16.h"
#include "fonts/Verdana25.h"
#include "img/logo_masjid.h"
#include "img/doa_masjid.h"
#include "app_hal.h"
#include "app_cmd.h"

/* DEFINITIONS */
#define MEM_BASE					0x0EA0
#define MEM_PWRSAVE_HOUR			(uint16_t)	(MEM_BASE + 0x00)
#define MEM_PWRSAVE_MINUTE			(uint16_t)	(MEM_BASE + 0x01)
#define MEM_PWRSAVE_DURATION		(uint16_t)	(MEM_BASE + 0x02)
#define MEM_BRIGHTNESS				(uint16_t)	(MEM_BASE + 0x04)

/* ENUMERATION */
typedef enum
{
	PARAM_NG = 0,
	PARAM_OK
} eParamStatus;

typedef enum
{
	MODE_WELCOMEMESSAGE = 0,
	MODE_REPORTMESSAGE,
	MODE_DOAMESSAGE,
	MODE_TITLEDMESSAGE,
	MODE_BIGMESSAGE,
	MODE_POWERSAVE,
	MODE_BLANK
} eDisplayMode;

typedef enum
{
	EVENT_NONE = 0,
	EVENT_PWRSAVE
} eTimeEvent;

typedef enum
{
	IDLE = 0,
	WORKING
} eTaskStatus;

/* STRUCTURES */
typedef struct
{
	uint8_t			hour;
	uint8_t			minute;
} stPrayerTime;

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
extern char				bColonState;

/* Function Prototypes */
extern void			app_init(void);
extern void			app_mem_read(void);
extern void			app_get_message(uint8_t task, char *str, uint8_t *mode, uint8_t *delay, uint8_t *iteration);
extern eTaskStatus	app_set_mode(eDisplayMode mode, char *message);
extern eTimeEvent	app_check_event(void);
extern void			app_set_powersave(uint8_t StartHour, uint8_t StartMinute, uint16_t Duration);
extern void			app_get_powersave(stPowerSave *stPwrSv);

#endif /* _APP_MAIN_H_ */
