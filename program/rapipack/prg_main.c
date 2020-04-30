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
#define PROP_COUNT		8
#define PROP_DATA_SIZE	16

/*----- Global Variables -----*/
stRealTimeVar	stRTime;
stDisplayMsg	sMessage[PROP_COUNT];
char			sText[PROP_COUNT][PROP_DATA_SIZE];
char 			sDispTitle[PROP_COUNT][PROP_DATA_SIZE] = {"SPEED", "AVERAGE", "SETTING", "MAINTENANCE"};
uint16_t		wMainValue[PROP_COUNT];
uint16_t		wTickCount;

/*----- Enum -----*/
typedef enum
{
	eDISTYP_TOP,
	eDISTYP_SETUP,
	eDISTYP_MAINTENANCE,
	eDISTYP_PRODUCTIVITY,
	eDISTYP_SETUP_LOG,
	eDISTYP_MAINTENANCE_LOG,
	eDISTYP_PRODUCTIVITY_LOG
} eDisplayType;

/*----- Function Prototypes -----*/
void main_message_init(stDisplayMsg *sMsg);
void main_message_prop_set(stDisplayMsg *sMsg, eDisplayType eMode);

void main_value_set(int16_t *addr, int16_t value);

void main_display_draw(stDisplayMsg *sMsg, int16_t *wValue, eDisplayType eMode);
void main_display_draw_top(stDisplayMsg *sMsg, int16_t *wValue);
void main_display_draw_setup(stDisplayMsg *sMsg, int16_t *wValue);
void main_display_draw_setup_log(stDisplayMsg *sMsg, int16_t *wValue);
void main_display_draw_maintenance(stDisplayMsg *sMsg, int16_t *wValue);
void main_display_draw_maintenance_log(stDisplayMsg *sMsg, int16_t *wValue);
void main_display_draw_productivity(stDisplayMsg *sMsg, int16_t *wValue);
void main_display_draw_productivity_log(stDisplayMsg *sMsg, int16_t *wValue);

void main_rtc_time_set(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second);
void main_rtc_time_get(void);
void main_rtc_tick_add(void);
void main_rtc_tick_reset(void);

/*----- Main Program -----*/
int main(void)
{	
	eMarqueeStat eStat;

	/* Startup delay */
	delay_ms(500);

	/* IO Initialization */
	io_buzzer_init();

	/* RTC Initialization */
	io_rtc_init();
	io_int_init(&main_rtc_time_get);

	//main_rtc_time_set(20, 4, 5, 17, 29, 0);

	/* USART Initialization */
	//usart_init(9600);

	/* Display Initialization */
	display_init();
	
	uint8_t speed_tbl[] = {94, 85, 86, 91, 90, 88, 90, 92, 89, 93, 94, 92, 90, 89, 89, 90, 91, 90, 88, 92};
	
	io_buzzer_pin(SET);
	delay_ms(100);
	io_buzzer_pin(RESET);
	
	main_message_init(&sMessage);
	main_message_prop_set(&sMessage, eDISTYP_MAINTENANCE);

	main_value_set(&wMainValue[0], 103);
	main_value_set(&wMainValue[1], 93);
	
	while(1)
	{
		main_display_draw(&sMessage, &wMainValue, eDISTYP_MAINTENANCE);
#if 0
		for(i = 0; i < 20; i++)
		{
			utils_int2str(speed_tbl[i], 1, &msg);
			
			dmdproc_set_font(ArialBlack16);
			dmdproc_draw_string(0,  0, "SPD", eCL_GREEN);
			dmdproc_draw_string(0,  16, "AVE ", eCL_GREEN);
			dmdproc_draw_char(29,  0, ':', eCL_GREEN);
			dmdproc_draw_char(29,  16, ':', eCL_GREEN);

			dmdproc_draw_string(37,  0, msg, eCL_RED);
			dmdproc_draw_string(37,  16, "90", eCL_RED);

			delay_ms(500);
		}
		dmdproc_clr_screen();
		delay_ms(20);

		for(i = 0; i < 22; i++)
		{
			utils_int2str(i, 1, &msg);
			utils_concat("00", ":", msg, &text);
			
			dmdproc_draw_string(2,  0, "SETTING", eCL_GREEN);
			dmdproc_draw_string(15,  16, text, eCL_RED);

			delay_ms(500);
		}
		dmdproc_clr_screen();
		delay_ms(20);

		dmdproc_set_font(System5x7);
		dmdproc_draw_string(0,  0, "SET1", eCL_GREEN);
		dmdproc_draw_string(0,  8, "SET2", eCL_GREEN);
		dmdproc_draw_string(0, 16, "SET3", eCL_GREEN);
		dmdproc_draw_string(0, 24, "SET4", eCL_GREEN);

		dmdproc_draw_char(29,  0, ':', eCL_GREEN);
		dmdproc_draw_char(29,  8, ':', eCL_GREEN);
		dmdproc_draw_char(29, 16, ':', eCL_GREEN);
		dmdproc_draw_char(29, 24, ':', eCL_GREEN);

		dmdproc_draw_string(34,  0, "11:30", eCL_RED);
		dmdproc_draw_string(34,  8, "10:25", eCL_RED);
		dmdproc_draw_string(34, 16, "11:43", eCL_RED);
		dmdproc_draw_string(34, 24, "10:57", eCL_RED);
		
		delay_ms(1000);
		dmdproc_clr_screen();
		delay_ms(20);

		dmdproc_draw_string(0,  0, "SET5", eCL_GREEN);
		dmdproc_draw_string(0,  8, "SET6", eCL_GREEN);
		dmdproc_draw_string(0, 16, "SET7", eCL_GREEN);
		dmdproc_draw_string(0, 24, "SET8", eCL_GREEN);

		dmdproc_draw_char(29,  0, ':', eCL_GREEN);
		dmdproc_draw_char(29,  8, ':', eCL_GREEN);
		dmdproc_draw_char(29, 16, ':', eCL_GREEN);
		dmdproc_draw_char(29, 24, ':', eCL_GREEN);

		dmdproc_draw_string(34,  0, "10:30", eCL_RED);
		dmdproc_draw_string(34,  8, "10:12", eCL_RED);
		dmdproc_draw_string(34, 16, "09:59", eCL_RED);
		dmdproc_draw_string(34, 24, "11:24", eCL_RED);
		
		delay_ms(1000);
		dmdproc_clr_screen();
		delay_ms(20);
#endif
	}
}

void main_message_init(stDisplayMsg *sMsg)
{
	uint8_t i = 0;

	for(i = 0; i < PROP_COUNT; i++)
	{
		display_message_init(&sMessage[i], &sText[i], ArialBlack16, 0, 0, eCL_RED);
	}
}

void main_message_prop_set(stDisplayMsg *sMsg, eDisplayType eMode)
{
	switch(eMode)
	{
		case eDISTYP_TOP :
			display_message_set_pos(&sMsg[0], 0, 0);
			display_message_set_pos(&sMsg[1], 0, 16);
			display_message_set_pos(&sMsg[2], 31, 0);
			display_message_set_pos(&sMsg[3], 31, 16);

			display_frame_set_prop(&sMsg[0], sMsg[0].stPos.X, sMsg[0].stPos.Y, 24, 16);
			display_frame_set_prop(&sMsg[1], sMsg[1].stPos.X, sMsg[1].stPos.Y, 24, 32);
			display_frame_set_prop(&sMsg[2], sMsg[3].stPos.X, sMsg[2].stPos.Y, 64, 16);
			display_frame_set_prop(&sMsg[2], sMsg[3].stPos.X, sMsg[3].stPos.Y, 64, 32);

			display_message_set_text(&sMsg[0], &sDispTitle[0]);
			display_message_set_text(&sMsg[1], &sDispTitle[1]);

			display_message_set_color(&sMsg[0], eCL_GREEN);
			display_message_set_color(&sMsg[1], eCL_GREEN);
			display_message_set_color(&sMsg[2], eCL_RED);
			display_message_set_color(&sMsg[3], eCL_RED);

			display_marquee_init(&sMessage[0], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
			display_marquee_init(&sMessage[1], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
			break;
		
		case eDISTYP_SETUP :
			display_message_set_pos(&sMsg[0], 2, 0);
			display_message_set_pos(&sMsg[1], 4, 16);

			display_message_set_text(&sMsg[0], &sDispTitle[2]);

			display_message_set_color(&sMsg[0], eCL_GREEN);
			display_message_set_color(&sMsg[1], eCL_RED);

			main_rtc_tick_reset();
			break;
		
		case eDISTYP_MAINTENANCE :
			display_message_set_pos(&sMsg[0], 0, 0);
			display_message_set_pos(&sMsg[1], 4, 16);

			display_frame_set_prop(&sMsg[0], sMsg[0].stPos.X, sMsg[0].stPos.Y, 64, 16);

			display_message_set_text(&sMsg[0], &sDispTitle[3]);

			display_message_set_color(&sMsg[0], eCL_GREEN);
			display_message_set_color(&sMsg[1], eCL_RED);

			display_marquee_init(&sMessage[0], eMARQUEE_RIGHT_TO_LEFT, ENABLE);

			main_rtc_tick_reset();
			break;
		
		case eDISTYP_SETUP_LOG :
			display_message_set_pos(&sMsg[0], 2, 0);
			display_message_set_pos(&sMsg[1], 4, 16);

			display_message_set_text(&sMsg[0], &sDispTitle[2]);

			display_message_set_color(&sMsg[0], eCL_GREEN);
			display_message_set_color(&sMsg[1], eCL_RED);

			main_rtc_tick_reset();
			break;
		
		default:
			break;
	}
}

void main_display_draw(stDisplayMsg *sMsg, int16_t *wValue, eDisplayType eMode)
{
	switch(eMode)
	{
		case eDISTYP_TOP :
			main_display_draw_top(sMsg, wValue);
			break;

		case eDISTYP_SETUP :
			main_display_draw_setup(sMsg, wValue);
			break;

		case eDISTYP_MAINTENANCE :
			main_display_draw_maintenance(sMsg, wValue);
			break;

		case eDISTYP_SETUP_LOG :
			main_display_draw_setup_log(sMsg, wValue);
			break;
		
		default:
			break;
	}
}

void main_display_draw_top(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat eStat;

	display_message_draw_static_string(sMsg[0].stFrame.wEndX + 2, sMsg[0].stPos.Y, ":", sMsg[0].pbFont, sMsg[0].eTextColor);
	display_message_draw_static_string(sMsg[1].stFrame.wEndX + 2, sMsg[1].stPos.Y, ":", sMsg[1].pbFont, sMsg[1].eTextColor);

	utils_int2str(wValue[0], 2, sMsg[2].pcString);
	utils_int2str(wValue[1], 2, sMsg[3].pcString);

	display_message_draw(&sMsg[2]);
	display_message_draw(&sMsg[3]);
			
	eStat = display_marquee_draw(&sMsg[0]);
	if(eStat == eMARQUEE_STAT_MOVED)
	{
		display_marquee_init(&sMsg[0], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
	}

	if(eStat != eMARQUEE_STAT_IDLE)
	{
		if(display_marquee_checkonpos(&sMsg[0], sMsg[0].stPos.X))
		{
			display_marquee_idle_set(&sMsg[0], 20, eMARQUEE_STAT_MOVING);
		}
		else if(display_marquee_checkonpos(&sMsg[0], -17))
		{
			display_marquee_idle_set(&sMsg[0], 10, eMARQUEE_STAT_MOVED);
		}
	}

	eStat = display_marquee_draw(&sMsg[1]);
	if(eStat == eMARQUEE_STAT_MOVED)
	{
		display_marquee_init(&sMsg[1], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
	}
		
	if(eStat != eMARQUEE_STAT_IDLE)
	{
		if(display_marquee_checkonpos(&sMsg[1], sMsg[1].stPos.X))
		{
			display_marquee_idle_set(&sMsg[1], 20, eMARQUEE_STAT_MOVING);
		}
		else if(display_marquee_checkonpos(&sMsg[1], -42))
		{
			display_marquee_idle_set(&sMsg[1], 10, eMARQUEE_STAT_MOVED);
		}
	}

	delay_ms(50);
}

void main_display_draw_setup(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat	eStat;
	uint8_t			bHour;
	uint8_t			bMin;
	uint8_t			bSec;
	char			pcTemp[3][3];

	main_rtc_tick_totime(&bHour, &bMin, &bSec);

	utils_int2str(bHour, 1, pcTemp[0]);
	utils_int2str(bMin, 1, pcTemp[1]);
	utils_int2str(bSec, 1, pcTemp[2]);

	utils_concat(pcTemp[0], ":" , pcTemp[1], sMsg[1].pcString);
	utils_concat(sMsg[1].pcString, ":" , pcTemp[2], sMsg[1].pcString);
	utils_concat(sMsg[1].pcString, " " , "", sMsg[1].pcString);

	display_message_draw(&sMsg[0]);
	display_message_draw(&sMsg[1]);

	delay_ms(50);
}

void main_display_draw_maintenance(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat	eStat;
	uint8_t			bHour;
	uint8_t			bMin;
	uint8_t			bSec;
	char			pcTemp[3][3];

	main_rtc_tick_totime(&bHour, &bMin, &bSec);

	utils_int2str(bHour, 1, pcTemp[0]);
	utils_int2str(bMin, 1, pcTemp[1]);
	utils_int2str(bSec, 1, pcTemp[2]);

	utils_concat(pcTemp[0], ":" , pcTemp[1], sMsg[1].pcString);
	utils_concat(sMsg[1].pcString, ":" , pcTemp[2], sMsg[1].pcString);
	utils_concat(sMsg[1].pcString, " " , "", sMsg[1].pcString);
	
	eStat = display_marquee_draw(&sMsg[0]);
	if(eStat == eMARQUEE_STAT_MOVED)
	{
		display_marquee_init(&sMsg[0], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
	}

	if(eStat != eMARQUEE_STAT_IDLE)
	{
		if(display_marquee_checkonpos(&sMsg[0], sMsg[0].stPos.X))
		{
			display_marquee_idle_set(&sMsg[0], 20, eMARQUEE_STAT_MOVING);
		}
		else if(display_marquee_checkonpos(&sMsg[0], -35))
		{
			display_marquee_idle_set(&sMsg[0], 10, eMARQUEE_STAT_MOVED);
		}
	}

	display_message_draw(&sMsg[1]);

	delay_ms(50);
}

void main_display_draw_setup_log(stDisplayMsg *sMsg, int16_t *wValue)
{
	eMarqueeStat	eStat;
	uint8_t			bHour;
	uint8_t			bMin;
	uint8_t			bSec;
	char			pcTemp[3][3];

	main_rtc_tick_totime(&bHour, &bMin, &bSec);

	utils_int2str(bHour, 1, pcTemp[0]);
	utils_int2str(bMin, 1, pcTemp[1]);
	utils_int2str(bSec, 1, pcTemp[2]);

	utils_concat(pcTemp[0], ":" , pcTemp[1], sMsg[1].pcString);
	utils_concat(sMsg[1].pcString, ":" , pcTemp[2], sMsg[1].pcString);
	utils_concat(sMsg[1].pcString, " " , "", sMsg[1].pcString);
	
	eStat = display_marquee_draw(&sMsg[0]);
	if(eStat == eMARQUEE_STAT_MOVED)
	{
		display_marquee_init(&sMsg[0], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
	}

	if(eStat != eMARQUEE_STAT_IDLE)
	{
		if(display_marquee_checkonpos(&sMsg[0], sMsg[0].stPos.X))
		{
			display_marquee_idle_set(&sMsg[0], 20, eMARQUEE_STAT_MOVING);
		}
		else if(display_marquee_checkonpos(&sMsg[0], -35))
		{
			display_marquee_idle_set(&sMsg[0], 10, eMARQUEE_STAT_MOVED);
		}
	}

	display_message_draw(&sMsg[1]);

	delay_ms(50);
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