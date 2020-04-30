/**
 *  Led Matrix Display Parameter & Variables
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PRG_DEF_H_
#define _PRG_DEF_H_

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
} stTime;

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

#endif /* _PRG_DEF_H_ */
