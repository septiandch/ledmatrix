/**
 *  Program Function Prototypes & Variable Declaration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PRG_FUNC_H_
#define _PRG_FUNC_H_

#include "stm32f10x_conf.h"
#include "common/pgmspace.h"
#include "common/utils.h"
#include "common/usart.h"
#include "common/delay.h"
#include "library/rtc/ds1307.h"
#include "library/eeprom/at24cxx.h"
#include "library/dmd/dmd_proc.h"

/*----- Defines -----*/
#define CODE_SETMSG01	"M01#"
#define CODE_SETMSG02	"M02#"
#define CODE_SETMSG03	"M03#"
#define CODE_SETMSG04	"M04#"
#define CODE_SETMSG05	"M05#"
#define CODE_GETMSG01	"R01#"
#define CODE_GETMSG02	"R02#"
#define CODE_GETMSG03	"R03#"
#define CODE_GETMSG04	"R04#"
#define CODE_GETMSG05	"R05#"
#define CODE_SETCLOCK	"RTC#"
#define CODE_SETBRIGH	"BRG#"
#define CODE_SETPSAVE	"PSV#"
#define CODE_FCTRYRST	"FCT#"
#define CODE_SOFTWRST	"RST#"

/* Memory allocation for message string */
#define MEM_MSG_MAXDAT	(300)
#define MEM_ADDR_MSG01	(  0)
#define MEM_ADDR_MSG02	(MEM_ADDR_MSG01 + MEM_MSG_MAXDAT)
#define MEM_ADDR_MSG03	(MEM_ADDR_MSG02 + MEM_MSG_MAXDAT)
#define MEM_ADDR_MSG04	(MEM_ADDR_MSG03 + MEM_MSG_MAXDAT)
#define MEM_ADDR_MSG05	(MEM_ADDR_MSG04 + MEM_MSG_MAXDAT)

/* Memory allocation for settings */
#define MEM_ADDR_BRGHT	MEM_ADDR_MSG05 + 1


/*----- Enumeration -----*/
typedef enum
{
	EVENT_NONE = 0,
	EVENT_PWRSAVE
} eTimeEvent;

typedef enum
{
	eMARQUEE_LEFT_TO_RIGHT,
	eMARQUEE_RIGHT_TO_LEFT,
	eMARQUEE_BOTTOM_TO_TOP,
	eMARQUEE_TOP_TO_BOTTOM
} eMarqueeDir;

typedef enum
{
	eMARQUEE_STAT_IDLE,
	eMARQUEE_STAT_READY,
	eMARQUEE_STAT_MOVING,
	eMARQUEE_STAT_MOVED,
	eMARQUEE_STAT_ERROR
} eMarqueeStat;

typedef enum
{
	eCMD_NONE,
	eCMD_UPDTMSG01,
	eCMD_UPDTMSG02,
	eCMD_UPDTMSG03,
	eCMD_UPDTMSG04,
	eCMD_UPDTMSG05,
	eCMD_SENDMSG01,
	eCMD_SENDMSG02,
	eCMD_SENDMSG03,
	eCMD_SENDMSG04,
	eCMD_SENDMSG05,
	eCMD_RTCUPDATE,
	eCMD_FACTORYRS,
	eCMD_BRIGHTSET
} eCmdCode;


/*----- Structures -----*/
typedef struct
{
	int16_t		X;
	int16_t		Y;
} stPixPos;

typedef struct
{
	uint8_t			bNextStat;
	int16_t			wDestPos;
	int16_t			wMarqueePos;
	int16_t			wIdleCount;
	uint8_t			bIteration;
	eMarqueeDir		eDir;
	eMarqueeStat	eStat;
} stMarqueeProp;

typedef struct
{
	char				*pcString;
	uint16_t			wStringLen;
	const uint8_t		*pbFont;
	eState				bDispEn;
	eColor				eTextColor;
	stPixPos			stPos;
	stDisplayFrame		stFrame;
	stMarqueeProp		stMarquee;
} stDisplayMsg;


/*----- Variables Declaration -----*/


/*----- Function Prototypes -----*/
extern void io_rtc_init(void);
extern void io_int_init(void *func);
extern void io_get_rtc(void);
extern void io_buzzer_init(void);
extern void io_buzzer_pin(eFlag flag);

extern void cmd_init(void);
extern eCmdCode cmd_check(void);
extern void cmd_get_data(char *pcData);

extern void display_init(uint8_t bBrightness);
extern void display_clear();
extern void display_message_draw(stDisplayMsg *pstDispMsg);
extern void display_message_init(stDisplayMsg *pstDispMsg, char *pcText, uint16_t wStrLength, const char *pbFont, int16_t wPosX, int16_t wPosY, eColor eTextColor);
extern void display_message_set_text(stDisplayMsg *pstDispMsg, char *pcText);
extern void display_message_clr_text(stDisplayMsg *pstDispMsg);
extern void display_message_set_color(stDisplayMsg *pstDispMsg, eColor color);
extern void display_message_draw_static_string(int16_t wPosX, int16_t wPosY, char *pcString, const uint8_t *font, eColor color);
extern void display_message_set_font(stDisplayMsg *pstDispMsg, const uint8_t *font);
extern void display_message_set_pos(stDisplayMsg *pstDispMsg, int16_t wPosX, uint16_t wPosY);
extern int16_t display_message_get_centerpos(stDisplayMsg *pstDispMsg, uint8_t bDirection);
extern uint16_t display_message_get_strwidth(stDisplayMsg *pstDispMsg);
extern uint16_t display_message_get_chrheight(stDisplayMsg *pstDispMsg);

extern void display_frame_set_prop(stDisplayMsg *pstDispMsg, int16_t wPixStartX, int16_t wPixStartY, int16_t wPixEndX, int16_t wPixEndY);
extern void display_frame_set_state(stDisplayMsg *pstDispMsg, eState state);

extern void display_marquee_init(stDisplayMsg *pstDispMsg, eMarqueeDir direction, eState eStartOnCurrPos);
extern uint8_t display_marquee_draw(stDisplayMsg *pstDispMsg);
extern uint8_t display_marquee_checkonpos(stDisplayMsg *pstDispMsg, int16_t wCheckPos);
extern void display_marquee_set_state(stDisplayMsg *pstDispMsg, eMarqueeStat eState);
extern void display_marquee_idle_set(stDisplayMsg *pstDispMsg, int16_t count, uint8_t bNextStat);
extern void display_marquee_iteration_add(stDisplayMsg *pstDispMsg);
extern void display_marquee_iteration_reset(stDisplayMsg *pstDispMsg);

#endif /* _PRG_FUNC_H_ */
