/**
 *  Display Main Program
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prg_def.h"
#include "prg_func.h"
#include "prg_rsc.h"

/*----- Defines -----*/
#define PROP_COUNT		12
#define PROP_DATA_SIZE	16

/*----- Global Variables -----*/
stRealTimeVar	stRTime;
stDisplayMsg	sMessage[PROP_COUNT];
char			sText[PROP_COUNT][PROP_DATA_SIZE];
char 			sDispTitle[PROP_COUNT][PROP_DATA_SIZE];
uint16_t		wMainValue[PROP_COUNT];
uint16_t		wTickCount;
uint8_t			bMsgSetCount;
uint8_t			bDispModCount;

/*----- Enum -----*/
typedef enum
{
	eDISTYP_1,
	eDISTYP_TITLE1,
	eDISTYP_2,
	eDISTYP_TITLE2,
	eDISTYP_3,
	eDISTYP_MAX
} eDisplayType;

/*----- Function Prototypes -----*/
void main_message_init(stDisplayMsg *sMsg);
void main_message_prop_set(stDisplayMsg *sMsg, eDisplayType eMode);

void main_value_set(int16_t *addr, int16_t value);

uint8_t main_display_draw(stDisplayMsg *sMsg, int16_t *wValue, eDisplayType eMode);
uint8_t main_display_draw_mode1(stDisplayMsg *sMsg, int16_t *wValue);
uint8_t main_display_draw_mode2(stDisplayMsg *sMsg, int16_t *wValue);
uint8_t main_display_draw_mode3(stDisplayMsg *sMsg, int16_t *wValue);
uint8_t main_display_draw_title1(stDisplayMsg *sMsg, int16_t *wValue);
uint8_t main_display_draw_title2(stDisplayMsg *sMsg, int16_t *wValue);

void main_rtc_time_set(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second);
void main_rtc_time_get(void);
void main_rtc_tick_add(void);
void main_rtc_tick_reset(void);

/*----- Main Program -----*/
int main(void)
{	
	eMarqueeStat	eStat;
	uint8_t			bDispModeDone = 0;
	eDisplayType	eDispType = eDISTYP_1;

	/* Startup delay */
	delay_ms(500);

	/* IO Initialization */
	io_buzzer_init();

	/* Display Initialization */
	display_init();
	
	io_buzzer_pin(SET);
	delay_ms(1);
	io_buzzer_pin(RESET);
	
	main_message_init(&sMessage);

	dmdproc_set_brightness(1);

	main_message_prop_set(&sMessage, eDispType);

	while(1)
	{
		if(bDispModeDone)
		{
			eDispType++;

			if(eDispType >= eDISTYP_MAX)
			{
				eDispType = eDISTYP_1;
			}

			main_message_prop_set(&sMessage, eDispType);
			display_message_draw_static_string(0, 0, "                    ", System5x7, eCL_RED);
			display_message_draw_static_string(0, 8, "                    ", System5x7, eCL_RED);
		}

		bDispModeDone = main_display_draw(&sMessage, &wMainValue, eDispType);
	}
}

void main_message_init(stDisplayMsg *sMsg)
{
	uint8_t i = 0;

	for(i = 0; i < PROP_COUNT; i++)
	{
		display_message_init(&sMessage[i], &sText[i], System5x7, 0, 0, eCL_RED);
	}
}

void main_message_prop_set(stDisplayMsg *sMsg, eDisplayType eMode)
{
	switch(eMode)
	{
		case eDISTYP_1 :
			display_message_set_pos(&sMsg[0], 33, 0);
			display_message_set_pos(&sMsg[1], 20, 8);
			display_message_set_pos(&sMsg[2], 0, 8);

			display_frame_set_prop(&sMsg[1], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[2], 0, 8, 96, 16);

			display_message_set_text(&sMsg[0], "SEDIA");
			display_message_set_text(&sMsg[1], "BAHAN KUE");
			display_message_set_text(&sMsg[2], "PERLENGKAPAN BAKING");

			display_marquee_init(&sMessage[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[2], eMARQUEE_BOTTOM_TO_TOP, DISABLE);

			bMsgSetCount = 0;
			break;

		case eDISTYP_2 :
			display_message_set_pos(&sMsg[0], 15, 0);
			display_message_set_pos(&sMsg[1], 18, 8);
			display_message_set_pos(&sMsg[2], 6, 8);
			display_message_set_pos(&sMsg[3], 25, 8);
			display_message_set_pos(&sMsg[4], 25, 8);
			display_message_set_pos(&sMsg[5], 17, 8);
			display_message_set_pos(&sMsg[6], 0, 8);

			display_frame_set_prop(&sMsg[1], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[2], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[3], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[4], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[5], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[6], 0, 8, 96, 16);

			display_message_set_text(&sMsg[0], "KIOS BAKERY");
			display_message_set_text(&sMsg[1], "ANEKA ROTI");
			display_message_set_text(&sMsg[2], "PASTRY (DANIS)");
			display_message_set_text(&sMsg[3], "BROWNIS");
			display_message_set_text(&sMsg[4], "PUDDING");
			display_message_set_text(&sMsg[5], "PROLL TAPE");
			display_message_set_text(&sMsg[6], "BOLEN PISANG DAN TAPE");

			display_marquee_init(&sMessage[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[2], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[3], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[4], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[5], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[6], eMARQUEE_BOTTOM_TO_TOP, DISABLE);

			bMsgSetCount = 0;
			break;

		case eDISTYP_3 :
			display_message_set_pos(&sMsg[0], 0, 0);
			display_message_set_pos(&sMsg[1], 18, 8);
			display_message_set_pos(&sMsg[2], 25, 8);
			display_message_set_pos(&sMsg[3], 22, 8);
			display_message_set_pos(&sMsg[4], 22, 8);
			display_message_set_pos(&sMsg[5], 30, 8);
			display_message_set_pos(&sMsg[6], 36, 8);
			display_message_set_pos(&sMsg[7], 31, 8);

			display_frame_set_prop(&sMsg[0], 0, 0, 96, 8);
			display_frame_set_prop(&sMsg[1], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[2], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[3], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[4], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[5], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[6], 0, 8, 96, 16);
			display_frame_set_prop(&sMsg[7], 0, 8, 96, 16);

			display_message_set_text(&sMsg[0], "ROTI BAKAR PRIANGAN");
			display_message_set_text(&sMsg[1], "STRAWBERRY");
			display_message_set_text(&sMsg[2], "BLUEERRY");
			display_message_set_text(&sMsg[3], "TIRAMISSU");
			display_message_set_text(&sMsg[4], "GREEN TEA");
			display_message_set_text(&sMsg[5], "COKLAT");
			display_message_set_text(&sMsg[6], "KEJU");
			display_message_set_text(&sMsg[7], "KACANG");

			display_marquee_init(&sMessage[0], eMARQUEE_RIGHT_TO_LEFT, DISABLE);
			display_marquee_init(&sMessage[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[2], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[3], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[4], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[5], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[6], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[7], eMARQUEE_BOTTOM_TO_TOP, DISABLE);

			bMsgSetCount = 0;
			break;

		case eDISTYP_TITLE1 :
			display_message_set_font(&sMsg[9], ArialBlack16);

			display_message_set_pos(&sMsg[9], 0, 0);

			display_frame_set_prop(&sMsg[9], 0, 8, 96, 8);

			display_message_set_text(&sMsg[9], "KIOS BAKERY");

			bMsgSetCount = 0;
			break;
		
		case eDISTYP_TITLE2 :
			display_message_set_font(&sMsg[9], ArialBlack16);
			display_message_set_font(&sMsg[10], ArialBlack16);

			display_message_set_text(&sMsg[9], "ROTI BAKAR");
			display_message_set_text(&sMsg[10], "PRIANGAN");

			display_message_set_pos(&sMsg[9], 5, 0);
			display_message_set_pos(&sMsg[10], 12, 0);

			display_frame_set_prop(&sMsg[9], 0, 0, 96, 16);
			display_frame_set_prop(&sMsg[10], 0, 0, 96, 16);

			display_marquee_init(&sMessage[9], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			display_marquee_init(&sMessage[10], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			
			bMsgSetCount = 0;
			break;

		default:
			break;
	}
}

uint8_t main_display_draw(stDisplayMsg *sMsg, int16_t *wValue, eDisplayType eMode)
{
	uint8_t bDone = 0;

	switch(eMode)
	{
		case eDISTYP_1 :
			bDone = main_display_draw_mode1(sMsg, wValue);
			break;

		case eDISTYP_2 :
			bDone = main_display_draw_mode2(sMsg, wValue);
			break;

		case eDISTYP_3 :
			bDone = main_display_draw_mode3(sMsg, wValue);
			break;

		case eDISTYP_TITLE1 :
			bDone = main_display_draw_title1(sMsg, wValue);
			break;

		case eDISTYP_TITLE2 :
			bDone = main_display_draw_title2(sMsg, wValue);
			break;
		
		default:
			break;
	}

	return bDone;
}

uint8_t main_display_draw_mode1(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat	eStat;
	uint8_t			bDispModeDone = 0;

	display_message_draw(&sMsg[0]);

	switch(bMsgSetCount)
	{
		case 0:
			eStat = display_marquee_draw(&sMsg[1]);
			break;
		
		case 1:
			eStat = display_marquee_draw(&sMsg[2]);
			break;

		case 2:
			eStat = display_marquee_draw(&sMsg[2]);
			break;

		case 3:
			eStat = display_marquee_draw(&sMsg[2]);
			break;

		default:
			break;
	}
	
	/* Idle based on posiiton */
	if(eStat != eMARQUEE_STAT_IDLE)
	{
		switch(bMsgSetCount)
		{
			case 0:
				if(display_marquee_checkonpos(&sMsg[1], 8))
				{
					display_marquee_idle_set(&sMsg[1], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 1:
				if(display_marquee_checkonpos(&sMsg[2], 8))
				{
					display_marquee_idle_set(&sMsg[2], 10, eMARQUEE_STAT_MOVED);
				}
				break;

			case 2:
				if(display_marquee_checkonpos(&sMsg[2], -20))
				{
					display_marquee_idle_set(&sMsg[2], 15, eMARQUEE_STAT_MOVED);
				}
				break;

			case 3:
				/* Noting to do */
				break;

			default:
				break;
		}
	}

	if(eStat == eMARQUEE_STAT_MOVED)
	{
		bMsgSetCount++;

		switch(bMsgSetCount)
		{
			case 0:
				display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 1:
				display_marquee_init(&sMsg[2], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 2:
				display_message_set_pos(&sMsg[2], sMsg[2].stPos.X, 8);
				display_marquee_init(&sMsg[2], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
				break;

			case 3:
				display_message_set_pos(&sMsg[2], -20, 8);
				display_marquee_init(&sMsg[2], eMARQUEE_BOTTOM_TO_TOP, ENABLE);
				break;

			default:
				display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				display_message_draw_static_string(0, 8, "                    ", System5x7, eCL_RED);
				bMsgSetCount = 0;
				bDispModeDone = 1;
				break;
		}
	}

	delay_ms(50);

	return bDispModeDone;
}

uint8_t main_display_draw_mode2(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat	eStat;
	uint8_t			bDispModeDone = 0;

	display_message_draw(&sMsg[0]);

	switch(bMsgSetCount)
	{
		case 0:
			eStat = display_marquee_draw(&sMsg[1]);
			break;
		
		case 1:
			eStat = display_marquee_draw(&sMsg[2]);
			break;

		case 2:
			eStat = display_marquee_draw(&sMsg[3]);
			break;

		case 3:
			eStat = display_marquee_draw(&sMsg[4]);
			break;

		case 4:
			eStat = display_marquee_draw(&sMsg[5]);
			break;

		case 5:
		case 6:
		case 7:
			eStat = display_marquee_draw(&sMsg[6]);
			break;

		default:
			break;
	}
	
	/* Idle based on posiiton */
	if(eStat != eMARQUEE_STAT_IDLE)
	{
		switch(bMsgSetCount)
		{
			case 0:
				if(display_marquee_checkonpos(&sMsg[1], 8))
				{
					display_marquee_idle_set(&sMsg[1], 10, eMARQUEE_STAT_MOVING);
				}
				break;
			case 1:
				if(display_marquee_checkonpos(&sMsg[2], 8))
				{
					display_marquee_idle_set(&sMsg[2], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 2:
				if(display_marquee_checkonpos(&sMsg[3], 8))
				{
					display_marquee_idle_set(&sMsg[3], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 3:
				if(display_marquee_checkonpos(&sMsg[4], 8))
				{
					display_marquee_idle_set(&sMsg[4], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 4:
				if(display_marquee_checkonpos(&sMsg[5], 8))
				{
					display_marquee_idle_set(&sMsg[5], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 5:
				if(display_marquee_checkonpos(&sMsg[6], 8))
				{
					display_marquee_idle_set(&sMsg[6], 10, eMARQUEE_STAT_MOVED);
				}
				break;

			case 6:
				if(display_marquee_checkonpos(&sMsg[6], -30))
				{
					display_marquee_idle_set(&sMsg[6], 10, eMARQUEE_STAT_MOVED);
				}
				break;

			case 7:
				/* Nothing to do */
				break;

			default:
				break;
		}
	}

	if(eStat == eMARQUEE_STAT_MOVED)
	{
		bMsgSetCount++;

		switch(bMsgSetCount)
		{
			case 0:
				display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 1:
				display_marquee_init(&sMsg[2], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 2:
				display_marquee_init(&sMsg[3], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 3:
				display_marquee_init(&sMsg[4], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 4:
				display_marquee_init(&sMsg[5], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 5:
				display_marquee_init(&sMsg[6], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 6:
				display_message_set_pos(&sMsg[6], sMsg[6].stPos.X, 8);
				display_marquee_init(&sMsg[6], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
				break;
			
			case 7:
				display_message_set_pos(&sMsg[6], -30, 8);
				display_marquee_init(&sMsg[6], eMARQUEE_BOTTOM_TO_TOP, ENABLE);
				break;

			default:
				display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				display_message_draw_static_string(0, 8, "                    ", System5x7, eCL_RED);
				bMsgSetCount = 0;
				bDispModeDone = 1;
				break;
		}
	}

	delay_ms(50);

	return bDispModeDone;
}

uint8_t main_display_draw_mode3(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat	eStat;
	uint8_t			bDispModeDone = 0;

	if(display_marquee_draw(&sMsg[0]) == eMARQUEE_STAT_MOVED)
	{
		display_marquee_init(&sMsg[0], eMARQUEE_RIGHT_TO_LEFT, DISABLE);
	}

	switch(bMsgSetCount)
	{
		case 0:
			eStat = display_marquee_draw(&sMsg[1]);
			break;
		
		case 1:
			eStat = display_marquee_draw(&sMsg[2]);
			break;

		case 2:
			eStat = display_marquee_draw(&sMsg[3]);
			break;

		case 3:
			eStat = display_marquee_draw(&sMsg[4]);
			break;

		case 4:
			eStat = display_marquee_draw(&sMsg[5]);
			break;

		case 5:
			eStat = display_marquee_draw(&sMsg[6]);
			break;

		case 6:
			eStat = display_marquee_draw(&sMsg[7]);
			break;

		default:
			break;
	}
	
	/* Idle based on posiiton */
	if(eStat != eMARQUEE_STAT_IDLE)
	{
		switch(bMsgSetCount)
		{
			case 0:
				if(display_marquee_checkonpos(&sMsg[1], 8))
				{
					display_marquee_idle_set(&sMsg[1], 10, eMARQUEE_STAT_MOVING);
				}
				break;
			case 1:
				if(display_marquee_checkonpos(&sMsg[2], 8))
				{
					display_marquee_idle_set(&sMsg[2], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 2:
				if(display_marquee_checkonpos(&sMsg[3], 8))
				{
					display_marquee_idle_set(&sMsg[3], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 3:
				if(display_marquee_checkonpos(&sMsg[4], 8))
				{
					display_marquee_idle_set(&sMsg[4], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 4:
				if(display_marquee_checkonpos(&sMsg[5], 8))
				{
					display_marquee_idle_set(&sMsg[5], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 5:
				if(display_marquee_checkonpos(&sMsg[6], 8))
				{
					display_marquee_idle_set(&sMsg[6], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			case 6:
				if(display_marquee_checkonpos(&sMsg[7], 8))
				{
					display_marquee_idle_set(&sMsg[7], 10, eMARQUEE_STAT_MOVING);
				}
				break;

			default:
				break;
		}
	}

	if(eStat == eMARQUEE_STAT_MOVED)
	{
		bMsgSetCount++;

		switch(bMsgSetCount)
		{
			case 0:
				display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 1:
				display_marquee_init(&sMsg[2], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 2:
				display_marquee_init(&sMsg[3], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 3:
				display_marquee_init(&sMsg[4], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 4:
				display_marquee_init(&sMsg[5], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 5:
				display_marquee_init(&sMsg[6], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 6:
				display_marquee_init(&sMsg[7], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;
			
			default:
				display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				display_message_draw_static_string(0, 8, "                    ", System5x7, eCL_RED);
				bMsgSetCount = 0;
				bDispModeDone = 1;
				break;
		}
	}

	delay_ms(50);

	return bDispModeDone;
}

uint8_t main_display_draw_title1(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat	eStat;
	uint8_t			bDispModeDone = 0;

	/* Draw string */
	display_frame_set_state(&sMsg[9], ENABLE);
	display_message_draw(&sMsg[9]);
	display_frame_set_state(&sMsg[9], DISABLE);

	/* Clear lines */
	dmdproc_draw_line(sMsg[9].stFrame.wStartX, sMsg[9].stFrame.wStartY, sMsg[9].stFrame.wEndX, sMsg[9].stFrame.wStartY, eCL_BLACK);
	dmdproc_draw_line(sMsg[9].stFrame.wStartX, 16 - sMsg[9].stFrame.wStartY, sMsg[9].stFrame.wEndX, 16 - sMsg[9].stFrame.wStartY, eCL_BLACK);

	switch(bMsgSetCount)
	{
		case 0:
			sMsg[9].stFrame.wStartY--;
			sMsg[9].stFrame.wEndY++;

			if(sMsg[9].stFrame.wStartY == 0)
			{
				bMsgSetCount = 1;
				sMsg[9].stMarquee.wIdleCount = 30;
			}
			break;
		
		case 1:
			sMsg[9].stMarquee.wIdleCount--;
			
			if(sMsg[9].stMarquee.wIdleCount == 0)
			{
				bMsgSetCount = 2;
				sMsg[9].stMarquee.wIdleCount = 20;
			}
			break;
		
		case 2:
			sMsg[9].stFrame.wStartY++;
			sMsg[9].stFrame.wEndY--;

			if(sMsg[9].stFrame.wStartY == 8)
			{
				bMsgSetCount = 4;
			}
			break;
		
		default:
			bDispModeDone = 1;
			break;
	}

	delay_ms(50);

	return bDispModeDone;
}

uint8_t main_display_draw_title2(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat	eStat;
	uint8_t			bDispModeDone = 0;

switch(bMsgSetCount)
	{
		case 0:
			eStat = display_marquee_draw(&sMsg[9]);
			break;
		
		case 1:
			eStat = display_marquee_draw(&sMsg[10]);
			break;

		default:
			break;
	}
	
	/* Idle based on posiiton */
	if(eStat != eMARQUEE_STAT_IDLE)
	{
		switch(bMsgSetCount)
		{
			case 0:
				if(display_marquee_checkonpos(&sMsg[9], 0))
				{
					display_marquee_idle_set(&sMsg[9], 70, eMARQUEE_STAT_MOVING);
				}
				break;

			case 1:
				if(display_marquee_checkonpos(&sMsg[10], 0))
				{
					display_marquee_idle_set(&sMsg[10], 70, eMARQUEE_STAT_MOVING);
				}
				break;

			default:
				break;
		}
	}

	if(eStat == eMARQUEE_STAT_MOVED)
	{
		bMsgSetCount++;

		switch(bMsgSetCount)
		{
			case 0:
				display_marquee_init(&sMsg[9], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;

			case 1:
				display_marquee_init(&sMsg[10], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				break;
			
			default:
				display_marquee_init(&sMsg[9], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
				display_message_draw_static_string(0, 0, "                    ", System5x7, eCL_RED);
				display_message_draw_static_string(0, 8, "                    ", System5x7, eCL_RED);
				bMsgSetCount = 0;
				bDispModeDone = 1;
				break;
		}
	}

#if 0
	/* Draw string */
	display_frame_set_state(&sMsg[9], ENABLE);
	display_message_draw_static_string(18, 0, "ROTI BAKAR", System5x7, eCL_RED);
	display_message_draw_static_string(22, 8, "PRIANGAN", System5x7, eCL_RED);
	display_frame_set_state(&sMsg[9], DISABLE);

	/* Clear lines */
	dmdproc_draw_line(sMsg[9].stFrame.wStartX, 0, sMsg[9].stFrame.wStartX, 16, eCL_BLACK);
	dmdproc_draw_line(96 - sMsg[9].stFrame.wStartX, 0, 96 - sMsg[9].stFrame.wStartX, 16, eCL_BLACK);

	switch(bMsgSetCount)
	{
		case 0:
			sMsg[9].stFrame.wStartX--;
			sMsg[9].stFrame.wEndX++;

			if(sMsg[9].stFrame.wStartX == 0)
			{
				bMsgSetCount = 1;
				sMsg[9].stMarquee.wIdleCount = 30;
			}
			break;
		
		case 1:
			sMsg[9].stMarquee.wIdleCount--;
			
			if(sMsg[9].stMarquee.wIdleCount)
			{
				bMsgSetCount = 2;
				sMsg[9].stMarquee.wIdleCount = 10;
			}
			break;
		
		case 2:
			sMsg[9].stMarquee.wIdleCount--;
			
			if(sMsg[9].stMarquee.wIdleCount)
			{
				bMsgSetCount = 3;
				sMsg[9].stMarquee.wIdleCount = 10;
			}
			break;
		
		case 3:
			sMsg[9].stFrame.wStartX++;
			sMsg[9].stFrame.wEndX--;

			if(sMsg[9].stFrame.wStartX == 48)
			{
				bMsgSetCount = 4;
			}
			break;
		
		default:
			bDispModeDone = 1;
			break;
	}
#endif

	delay_ms(10);

	return bDispModeDone;
}

void main_value_set(int16_t *addr, int16_t value)
{
	*addr = value;
}

void main_rtc_time_set(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second)
{	
	stRealTimeVar _stRTime = {year, month, date, 0, hour, minute, second};

	rtc_set_time(&_stRTime);
}

void main_rtc_time_get(void)
{
	rtc_get_time(&stRTime);
	
	main_rtc_tick_add();
}

void main_rtc_tick_add(void)
{
	wTickCount++;
	if(wTickCount >= 0xFFF0)
	{
		main_rtc_tick_reset();
	}
}

void main_rtc_tick_reset(void)
{
	wTickCount = 0;
}

void main_rtc_tick_totime(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
	*hour	= (uint8_t) (wTickCount / 3600);
	*min	= (uint8_t) ((wTickCount - (*hour * 3600)) / 60);
	*sec	= (uint8_t) (wTickCount - (*min * 60) - (*hour * 3600));
}