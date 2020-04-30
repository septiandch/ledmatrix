/**
 *  Program Parameter & Variables
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PRG_DEF_H_
#define _PRG_DEF_H_

#include "program/prg_api.h"
#include "device/rtc/ds1307.h"
#include "device/dmd/dmdhal_api.h"
#include "library/utils.h"
#include "resources/fonts/SystemFont.h"
#include "resources/fonts/ArialBlack16.h"

/* DEFINITIONS */
#define MEM_BASE					0x0EA0
#define MEM_PWRSAVE_HOUR			(uint16_t)	(MEM_BASE + 0x00)
#define MEM_PWRSAVE_MINUTE			(uint16_t)	(MEM_BASE + 0x01)
#define MEM_PWRSAVE_DURATION		(uint16_t)	(MEM_BASE + 0x02)
#define MEM_BRIGHTNESS				(uint16_t)	(MEM_BASE + 0x04)

/* ENUMERATION */
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

/* VARIABLES */
extern stRealTimeVar	stRTime;
extern char				bColonState;

#endif /* _PRG_DEF_H_ */
