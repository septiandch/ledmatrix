/**
 *  Led Matrix Display program
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _LEDMATRIX_H_
#define _LEDMATRIX_H_

#include "pgmspace.h"
#include "dmd/dmd_proc.h"
#include "lib/fmem.h"
#include "lib/at24cxx.h"
#include "lib/rtc.h"
#include "lib/usart.h"
#include "lib/utils.h"
#include "fonts/SystemFont.h"
#include "fonts/ArialBlack16.h"
#include "fonts/Unispace18.h"
#include "fonts/MonoFonto16.h"
#include "fonts/Verdana25.h"
#include "img/logo_masjid.h"
#include "img/doa_masjid.h"
#include "ledmatrix_io.h"
#include "ledmatrix_cmd.h"

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
extern void			ledmatrix_init(void);
extern void			ledmatrix_get_mem(void);
extern void			ledmatrix_get_message(uint8_t task, char *str, uint8_t *mode, uint8_t *delay, uint8_t *iteration);
extern eTaskStatus	ledmatrix_set_mode(eDisplayMode mode, char *message);
extern void			ledmatrix_chk_event(eTimeEvent *eEventRet);
extern void			ledmatrix_set_powersave(uint8_t StartHour, uint8_t StartMinute, uint16_t Duration);
extern void			ledmatrix_get_powersave(stPowerSave *stPwrSv);

#endif /* _LEDMATRIX_H_ */
