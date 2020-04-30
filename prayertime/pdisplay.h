/**
 *  Prayer Time Display Modes Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PTIME_DISPLAY_H_
#define _PTIME_DISPLAY_H_

#include "../ledmatrix/ledmatrix.h"
#include "../peripherals/fmem.h"
#include "../utils.h"
#include "prayertime.h"
#include "pgmspace.h"
#include "fonts/SystemFont.h"
#include "fonts/ArialBlack16.h"

/* DEFINITIONS */
#define PARAM_MAX_TASK		6
#define PARAM_MAX_LEN		81

#define MEM_CL_BASE			(uint16_t)(MEM_BASE		+ 0x000F)
#define MEM_CL_CLOCK		(uint16_t)(MEM_CL_BASE	+ 0x0001)
#define MEM_CL_DATE			(uint16_t)(MEM_CL_BASE	+ 0x0002)
#define MEM_CL_TEXT			(uint16_t)(MEM_CL_BASE	+ 0x0003)
#define MEM_CL_PTIME		(uint16_t)(MEM_CL_BASE	+ 0x0004)
#define MEM_CL_COUNT		(uint16_t)(MEM_CL_BASE	+ 0x0005)

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
	MODE_BIGMESSAGE2,
	MODE_DATETIME,
	MODE_HIJRIDATE,
	MODE_PRAYERTIME,
	MODE_WAITPRAYER,
	MODE_COUNTDOWN,
	MODE_IQAMAH,
	MODE_BLANK,
	MODE_JUMUAH,
	MODE_MAXNUM
} eDisplayMode;

typedef enum
{
	IDLE = 0,
	RUN
} eDisplayStatus;


/* STRUCTURES */
typedef struct
{
	eCOLOR clock;
	eCOLOR date;
	eCOLOR text;
	eCOLOR ptime;
	eCOLOR counter;
} stDispColor;

/* Global Variables */
extern uint16_t	pdisplay_nCounter;

/* Function Prototypes */
extern void		pdisplay_Init(void);
extern void		pdisplay_SetBrightness(uint8_t percentage);
extern void		pdisplay_SetColor(uint16_t addr, eCOLOR color);
extern eCOLOR	pdisplay_GetColor(uint16_t addr);
extern void		pdisplay_SetMode(eDisplayMode _mode, char *message, uint8_t nPTimeList);
extern void		pdisplay_GetParam(uint8_t addr, char *_str, uint8_t *_mode, uint8_t *_delay, uint8_t *_iteration);

#endif /* _PTIME_DISPLAY_H_ */
