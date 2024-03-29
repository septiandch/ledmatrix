/**
 *  Prayer Time Display Modes Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PTIME_DISPLAY_H_
#define _PTIME_DISPLAY_H_

#include "../dmd/dmdproc.h"
#include "../peripherals/fmem.h"
#include "../utils.h"
#include "prayertime.h"
#include "common/pgmspace.h"
#include "fonts/SystemFont.h"
#include "fonts/ArialBlack16.h"

/* DEFINITIONS */
#define PARAM_MAX_TASK		5
#define PARAM_MAX_LEN		81

#define MEM_eCL_BASE			(MEM_BASE + 0x0F)
#define MEM_eCL_CLOCK		(MEM_eCL_BASE + 0x01)
#define MEM_eCL_DATE			(MEM_eCL_BASE + 0x02)
#define MEM_eCL_TEXT			(MEM_eCL_BASE + 0x03)
#define MEM_eCL_PTIME		(MEM_eCL_BASE + 0x04)
#define MEM_eCL_COUNT		(MEM_eCL_BASE + 0x05)

/* ENUMERATION */
typedef enum
{
	PARAM_NG = 0,
	PARAM_OK
} eParamStatus;

typedef enum
{
	MODE_POWERSAVE = 0,
	MODE_SMALLMESSAGE,
	MODE_BIGMESSAGE,
	MODE_DATETIME,
	MODE_HIJRIDATE,
	MODE_PRAYERTIME,
	MODE_WAITPRAYER,
	MODE_COUNTDOWN,
	MODE_IQAMAH,
	MODE_BLANK
} eDisplayMode;

typedef enum
{
	IDLE = 0,
	RUN
} eDisplayStatus;


/* STRUCTURES */
typedef struct
{
	eColor clock;
	eColor date;
	eColor text;
	eColor ptime;
	eColor counter;
} stDispColor;

/* Global Variables */
extern uint16_t	pdisplay_nCounter;

/* Function Prototypes */
extern void		pdisplay_Init(void);
extern void		pdisplay_SetBrightness(uint8_t percentage);
extern void		pdisplay_SetColor(uint8_t addr, eColor color);
extern eColor	pdisplay_GetColor(uint8_t addr);
extern void		pdisplay_SetMode(eDisplayMode _mode, char *message, uint8_t nPTimeList);
extern void		pdisplay_GetParam(uint8_t addr, char *_str, uint8_t *_mode, uint8_t *_delay, uint8_t *_iteration);

#endif /* _PTIME_DISPLAY_H_ */
