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
#include "library/dmd/dmd_proc.h"

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
	eMARQUEE_STAT_MOVING,
	eMARQUEE_STAT_MOVED,
	eMARQUEE_STAT_ERROR
} eMarqueeStat;


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
	eMarqueeDir		eDir;
	eMarqueeStat	eStat;
} stMarqueeProp;

typedef struct
{
	char				*pcString;
	const uint8_t		*pbFont;
	eState				bMoveEn;
	eColor				eTextColor;
	stPixPos			stPos;
	stDisplayFrame		stFrame;
	stMarqueeProp		stMarquee;
} stDisplayMsg;


/*----- Variables Declaration -----*/
extern stRealTimeVar	stRTime;
extern char				bColonState;


/*----- Function Prototypes -----*/
extern void io_rtc_init(void);
extern void io_int_init(void *func);
extern void io_get_rtc(void);
extern void io_buzzer_init(void);
extern void io_buzzer_pin(eFlag flag);

extern void display_message_init(stDisplayMsg *pstDispMsg, char *pcText, const char *pbFont, int16_t wPosX, int16_t wPosY, eColor eTextColor);
extern void display_message_draw(stDisplayMsg *pstDispMsg);
extern void display_message_set_text(stDisplayMsg *pstDispMsg, char *pcText);
extern void display_message_set_color(stDisplayMsg *pstDispMsg, eColor color);
extern void display_message_draw_static_string(int16_t wPosX, int16_t wPosY, char *pcString, const uint8_t *font, eColor color);
extern void display_message_set_font(stDisplayMsg *pstDispMsg, const uint8_t *font);
extern void display_message_set_pos(stDisplayMsg *pstDispMsg, int16_t wPosX, uint16_t wPosY);

extern void display_frame_set_prop(stDisplayMsg *pstDispMsg, int16_t wPixStartX, int16_t wPixStartY, int16_t wPixEndX, int16_t wPixEndY);
extern void display_frame_set_state(stDisplayMsg *pstDispMsg, eState state);

extern void display_marquee_init(stDisplayMsg *pstDispMsg, eMarqueeDir direction, eState eStartOnCurrPos);
extern uint8_t display_marquee_draw(stDisplayMsg *pstDispMsg);
extern uint8_t display_marquee_checkonpos(stDisplayMsg *pstDispMsg, int16_t wCheckPos);
extern void display_marquee_idle_set(stDisplayMsg *pstDispMsg, int16_t count, uint8_t bNextStat);

#endif /* _PRG_FUNC_H_ */
