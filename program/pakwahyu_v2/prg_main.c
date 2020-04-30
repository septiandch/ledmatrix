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
#define MSGDATA_COUNT			2
#define MSGDATA_MIN_SIZE		30
#define MSGDATA_MAX_SIZE		500

#define CUSTOM_DISP_HOUR		15
#define CUSTOM_DISP_MINS		00

/*----- Global Variables -----*/
volatile stRealTimeVar	stRTime;
stDisplayMsg	sMessage[MSGDATA_COUNT];

char	sMsgBuffer1[MSGDATA_MAX_SIZE];
char	sMsgBuffer2[MSGDATA_MAX_SIZE];
char	sMsgBuffer3[MSGDATA_MAX_SIZE];
char	sMsgBuffer4[MSGDATA_MAX_SIZE];

char	sMainText[MSGDATA_MIN_SIZE];
char	sSubText[MSGDATA_MAX_SIZE];

/*----- Enum -----*/
typedef enum
{
	eDISTYP_TITLE1,
	eDISTYP_1,
	eDISTYP_TITLE2,
	eDISTYP_2,
	eDISTYP_TITLE3,
	eDISTYP_3,
	eDISTYP_TITLE4,
	eDISTYP_4,
	eDISTYP_MAX,
	eDISTYP_CLOCK
} eDisplayType;

/*----- Function Prototypes -----*/
void main_mem_init();
void main_message_init(stDisplayMsg *sMsg);
void main_message_prop_set(stDisplayMsg *sMsg, eDisplayType eMode);

uint8_t main_display_draw(stDisplayMsg *sMsg, eDisplayType eMode);
uint8_t main_display_draw_menus(stDisplayMsg *sMsg, eMarqueeDir eDir);
uint8_t main_display_draw_default(stDisplayMsg *sMsg, eMarqueeDir eDir);
uint8_t main_display_draw_title(stDisplayMsg *sMsg, eMarqueeDir eDir);
uint8_t main_display_draw_clock(stDisplayMsg *sMsg, stRealTimeVar *stTime);

void main_rtc_time_set(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second);
void main_rtc_time_get(void);
void main_rtc_tick_add(void);
void main_rtc_tick_reset(void);

void main_factory_reset(void);

/*----- Main Program -----*/
int main(void)
{	
	eMarqueeStat	eStat;
	uint8_t			bDispModeDone = 0;
	eDisplayType	eDispType = eDISTYP_CLOCK;
	eCmdCode		eCommandCode = eCMD_NONE;

	/* Startup delay */
	delay_ms(500);

	/* IO Initialization */
	io_buzzer_init();

	io_buzzer_pin(SET);
	delay_ms(100);
	io_buzzer_pin(RESET);

	/* Command Functions Initialize */
	cmd_init();

	/* Memory initialize */
	main_mem_init();
	
	/* RTC Initialization */
	io_rtc_init();
	io_int_init(&main_rtc_time_get);

#if 0
	main_rtc_time_set(20, 4, 19, 15, 0, 0);
#endif

	/* Wait for RTC first read */
	while(stRTime.date == 0);

	/* Display Initialization */
	display_init(eeprom_read_byte(MEM_ADDR_BRGHT));

	/* First Message Initialization */
	main_message_init(&sMessage);
	main_message_prop_set(&sMessage, eDispType);

	while(1)
	{
		/* Main display drawing function */
		bDispModeDone = main_display_draw(&sMessage, eDispType);

		if(bDispModeDone)
		{
			eDispType++;

			if(eDispType >= eDISTYP_MAX)
			{
				eDispType = eDISTYP_TITLE1;
			}

			main_message_prop_set(&sMessage, eDispType);
		}

		/* Main display drawing function */
		eCommandCode = cmd_check();

		if(eCommandCode != eCMD_NONE)
		{
			main_command_process(eCommandCode);
		}
	}
}

void main_message_init(stDisplayMsg *sMsg)
{
	/* Set default properties */
	display_message_init(&sMsg[0], &sMainText, MSGDATA_MIN_SIZE, System5x7, 0, 0, eCL_RED);
	display_message_init(&sMsg[1], &sSubText, MSGDATA_MAX_SIZE, System5x7, 0, 0, eCL_RED);
}

void main_message_prop_set(stDisplayMsg *sMsg, eDisplayType eMode)
{
	memset(&sMainText, 0, MSGDATA_MIN_SIZE);
	memset(&sSubText, 0, MSGDATA_MAX_SIZE);

	display_clear();

	/* Setup message text */
	switch(eMode)
	{
		case eDISTYP_TITLE1 :
		case eDISTYP_1 :
			main_message_parse(&sMsgBuffer1, &sMainText, &sSubText);
			break;

		case eDISTYP_TITLE2 :
		case eDISTYP_2 :
			main_message_parse(&sMsgBuffer2, &sMainText, &sSubText);
			break;

		case eDISTYP_TITLE3 :
		case eDISTYP_3 :
			main_message_parse(&sMsgBuffer3, &sMainText, &sSubText);
			break;

		case eDISTYP_TITLE4 :
			memcpy(&sMainText, "ROTI BAKAR PRIANGAN\0", 20);
			break;

		case eDISTYP_4 :
			main_message_parse(&sMsgBuffer4, &sMainText, &sSubText);
			break;

		default:
			break;
	}

	/* Setup message properties */
	switch(eMode)
	{
		case eDISTYP_1 :
		case eDISTYP_2 :
		case eDISTYP_3 :
		case eDISTYP_4 :
			/* Set font */
			display_message_set_font(&sMsg[0], System5x7);
			display_message_set_font(&sMsg[1], System5x7);

			/* Set Display Frame */
			display_frame_set_prop(&sMsg[1], 0, 8, 96, 16);

			/* Marquee iteration reset must be done manually */
			display_marquee_iteration_reset(&sMsg[1]);

			/* Set Marquee stat */
			display_marquee_set_state(&sMsg[1], eMARQUEE_STAT_READY);
			break;

		case eDISTYP_TITLE1 :
		case eDISTYP_TITLE2 :
		case eDISTYP_TITLE3 :
		case eDISTYP_TITLE4 :
			/* Set font */
			display_message_set_font(&sMsg[0], ArialBlack16);

			/* Set Display Frame */
			display_frame_set_prop(&sMsg[0], 0, 0, 96, 16);

			/* Marquee iteration reset must be done manually */
			display_marquee_iteration_reset(&sMsg[0]);

			/* Set Marquee stat */
			display_marquee_set_state(&sMsg[0], eMARQUEE_STAT_READY);
			break;

		case eDISTYP_CLOCK :
			/* Set font */
			display_message_set_font(&sMsg[0], ArialBlack16);

			/* Marquee iteration reset must be done manually */
			display_marquee_iteration_reset(&sMsg[0]);
			break;

		default:
			break;
	}
}

void main_mem_init()
{
	uint16_t i;

	eeprom_init();
	delay_ms(10);

#if 0
	/* Initialize EEPROM Data */	
	eeprom_write_string(MEM_ADDR_MSG01, "\0\0", 2);
	eeprom_write_string(MEM_ADDR_MSG02, "\0\0", 2);
	eeprom_write_string(MEM_ADDR_MSG03, "\0\0", 2);
	eeprom_write_string(MEM_ADDR_MSG04, "\0\0", 2);
#endif

	eeprom_read_string(MEM_ADDR_MSG01, &sMsgBuffer1);
	eeprom_read_string(MEM_ADDR_MSG02, &sMsgBuffer2);
	eeprom_read_string(MEM_ADDR_MSG03, &sMsgBuffer3);
	eeprom_read_string(MEM_ADDR_MSG04, &sMsgBuffer4);
}

void main_message_parse(char *sSource, char *sTitle, char *sSubMsg)
{
	uint8_t		bIndex[10];
	uint16_t	i;

	if(sSource[0] != '\0')
	{
		utils_parse(',', sSource, bIndex);

		for(i = 0; i < bIndex[0] - 1; i++)
		{
			sTitle[i] = sSource[i];
		}

		i = bIndex[0]; 
		while(sSource[i] != '\0')
		{
			sSubMsg[i - bIndex[0]] = sSource[i];
			i++;
		}
	}
}

uint8_t main_display_draw(stDisplayMsg *sMsg, eDisplayType eMode)
{
	uint8_t	bDone = 0;

	switch(eMode)
	{
		case eDISTYP_TITLE1 :
			bDone = main_display_draw_title(sMsg, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_1 :
			bDone = main_display_draw_menus(sMsg, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE2 :
			bDone = main_display_draw_title(sMsg, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_2 :
			bDone = main_display_draw_menus(sMsg, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE3 :
			bDone = main_display_draw_title(sMsg, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_3 :
			bDone = main_display_draw_menus(sMsg, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE4 :
			if(stRTime.hour >= CUSTOM_DISP_HOUR && stRTime.minute >= CUSTOM_DISP_MINS)
			{
				bDone = main_display_draw_title(sMsg, eMARQUEE_RIGHT_TO_LEFT);
			}
			else
			{
				bDone = 1;
			}
			break;

		case eDISTYP_4 :
			if(stRTime.hour >= CUSTOM_DISP_HOUR && stRTime.minute >= CUSTOM_DISP_MINS)
			{				
				bDone = main_display_draw_menus(sMsg, eMARQUEE_RIGHT_TO_LEFT);
			}
			else
			{
				bDone = 1;
			}
			break;

		case eDISTYP_CLOCK :
			bDone = main_display_draw_clock(sMsg, &stRTime);
			break;
		
		default:
			break;
	}

	return bDone;
}

uint8_t main_display_draw_menus(stDisplayMsg *sMsg, eMarqueeDir eDir)
{
	uint8_t			bDispModeDone	= 0;
	uint8_t			bTextCount		= 0;
	int16_t			wMsgPos			= 0;
	eMarqueeStat	eStat;
	
	eStat = display_marquee_draw(&sMsg[1]);
	
	if(eStat == eMARQUEE_STAT_MOVED)
	{
		bDispModeDone = 1;
	}
	
	if(eStat == eMARQUEE_STAT_READY)
	{
		/* Draw Title Text */
		wMsgPos = display_message_get_centerpos(&sMsg[0], 0);
		display_message_set_pos(&sMsg[0], wMsgPos, 0);
		display_message_draw(&sMsg[0]);

		/* Set Sub Menu Marquee */
		display_message_set_pos(&sMsg[1], 0, (DISPLAY_HEIGHT / 2));
		display_marquee_init(&sMsg[1], eMARQUEE_RIGHT_TO_LEFT, DISABLE);
		
		display_clear();

		display_marquee_set_state(&sMsg[1], eMARQUEE_STAT_MOVING);
	}
	
	/* Blinking Title */
	if(sMsg[1].stMarquee.wMarqueePos % 16 == 0)
	{
		sMsg[0].bDispEn = (sMsg[0].bDispEn != ENABLE) ? ENABLE : DISABLE;
	}

	if(sMsg[0].bDispEn == ENABLE)
	{
		display_message_draw(&sMsg[0]);
	}
	else
	{
		display_message_draw_static_string(0, 0, "                 ", System5x7, eCL_BLUE);
	}

	delay_ms(30);

	return bDispModeDone;
}

uint8_t main_display_draw_title(stDisplayMsg *sMsg, eMarqueeDir eDir)
{
	uint8_t			bDispModeDone = 0;
	int16_t			wMsgPos = 0;
	eMarqueeStat	eStat;

	eStat = display_marquee_draw(&sMsg[0]);

	if(eStat == eMARQUEE_STAT_MOVED)
	{
		bDispModeDone = 1;
	}
	
	if(eStat == eMARQUEE_STAT_READY)
	{		
		if(eDir == eMARQUEE_BOTTOM_TO_TOP)
		{
			wMsgPos = display_message_get_centerpos(&sMsg[0], 0);
			display_message_set_pos(&sMsg[0], wMsgPos, 0);
			display_marquee_init(&sMsg[0], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
		}
		else if(eDir == eMARQUEE_RIGHT_TO_LEFT)
		{
			wMsgPos = display_message_get_centerpos(&sMsg[0], 1);
			display_message_set_pos(&sMsg[0], 0, wMsgPos);
			display_marquee_init(&sMsg[0], eMARQUEE_RIGHT_TO_LEFT, DISABLE);
		}
		
		display_marquee_set_state(&sMsg[0], eMARQUEE_STAT_MOVING);
	}
	
	/* Idle based on posiiton */
	if(eStat != eMARQUEE_STAT_IDLE)
	{
		int16_t wCenter = display_message_get_centerpos(&sMsg[0], 1);

		if(sMsg[0].stMarquee.eDir == eMARQUEE_BOTTOM_TO_TOP && display_marquee_checkonpos(&sMsg[0], wCenter))
		{
			display_marquee_idle_set(&sMsg[0], 20, eMARQUEE_STAT_MOVING);
		}
	}

	delay_ms(50);

	return bDispModeDone;
}

uint8_t main_display_draw_clock(stDisplayMsg *sMsg, stRealTimeVar *stTime)
{
	char	sHour[2];
	char	sMin[2];
	char	sSec[2];
	char	sTime[8];
	uint8_t	bDispModeDone = 0;
	int16_t	wMsgPosX = 0;
	int16_t	wMsgPosY = 0;

	utils_int2str(stTime->hour, 1, &sHour);
	utils_int2str(stTime->minute, 1, &sMin);
	utils_int2str(stTime->second, 1, &sSec);

	utils_concat(sHour, ":", sMin, &sTime);
	utils_concat(sTime, ":", sSec, &sTime);

	memcpy(sMsg[0].pcString, sTime, 8);

	/* Draw Title Text */
	wMsgPosX = display_message_get_centerpos(&sMsg[0], 0);
	wMsgPosY = display_message_get_centerpos(&sMsg[0], 1);
	display_message_set_pos(&sMsg[0], wMsgPosX, wMsgPosY);
	display_message_draw(&sMsg[0]);

	sMsg[0].stMarquee.bIteration++;
	if(sMsg[0].stMarquee.bIteration >= 100)
	{
		display_clear();
		bDispModeDone = 1;
	}

	delay_ms(50);

	return bDispModeDone;
}

void main_command_process(eCmdCode eCommandCode)
{
	char sTmpBuffer[USART_DATA_SIZE];

	switch(eCommandCode)
	{
		case eCMD_UPDTMSG01:
			memset(&sMsgBuffer1, 0, MSGDATA_MAX_SIZE);
			cmd_get_data(&sMsgBuffer1);

			eeprom_write_string(MEM_ADDR_MSG01, &sMsgBuffer1, utils_strlen(&sMsgBuffer1));
			break;

		case eCMD_UPDTMSG02:
			memset(&sMsgBuffer2, 0, MSGDATA_MAX_SIZE);
			cmd_get_data(&sMsgBuffer2);

			eeprom_write_string(MEM_ADDR_MSG02, &sMsgBuffer2, utils_strlen(&sMsgBuffer2));
			break;

		case eCMD_UPDTMSG03:
			memset(&sMsgBuffer3, 0, MSGDATA_MAX_SIZE);
			cmd_get_data(&sMsgBuffer3);

			eeprom_write_string(MEM_ADDR_MSG03, &sMsgBuffer3, utils_strlen(&sMsgBuffer3));
			break;

		case eCMD_UPDTMSG04:
			memset(&sMsgBuffer4, 0, MSGDATA_MAX_SIZE);
			cmd_get_data(&sMsgBuffer4);

			eeprom_write_string(MEM_ADDR_MSG04, &sMsgBuffer4, utils_strlen(&sMsgBuffer4));
			break;

		case eCMD_SENDMSG01:
			usart_puts(&sMsgBuffer1);
			usart_putc('\n');
			break;

		case eCMD_SENDMSG02:
			usart_puts(&sMsgBuffer2);
			usart_putc('\n');
			break;

		case eCMD_SENDMSG03:
			usart_puts(&sMsgBuffer3);
			usart_putc('\n');
			break;

		case eCMD_SENDMSG04:
			usart_puts(&sMsgBuffer4);
			usart_putc('\n');
			break;

		case eCMD_RTCUPDATE:
			cmd_get_data(&sTmpBuffer);
			main_rtc_time_set(	((sTmpBuffer[ 0] - '0') * 10) + (sTmpBuffer[ 1] - '0'),
								((sTmpBuffer[ 2] - '0') * 10) + (sTmpBuffer[ 3] - '0'),
								((sTmpBuffer[ 4] - '0') * 10) + (sTmpBuffer[ 5] - '0'),
								((sTmpBuffer[ 6] - '0') * 10) + (sTmpBuffer[ 7] - '0'),
								((sTmpBuffer[ 8] - '0') * 10) + (sTmpBuffer[ 9] - '0'),
								((sTmpBuffer[10] - '0') * 10) + (sTmpBuffer[11] - '0')
							);
			break;
		
		case eCMD_BRIGHTSET:
			cmd_get_data(&sTmpBuffer);
			eeprom_write_byte(MEM_ADDR_BRGHT, ((sTmpBuffer[ 0] - '0') * 10) + (sTmpBuffer[ 1] - '0'));
			
			dmdproc_set_brightness(eeprom_read_byte(MEM_ADDR_BRGHT));
			break;
		
		case eCMD_FACTORYRS:
			main_factory_reset();
			break;

		default:
			break;
	}

	io_buzzer_pin(SET);
	delay_ms(100);
	io_buzzer_pin(RESET);
}

void main_rtc_time_set(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second)
{	
	stRealTimeVar _stRTime = {year, month, date, 0, hour, minute, second};

	rtc_set_time(&_stRTime);
}

void main_rtc_time_get(void)
{
	rtc_get_time(&stRTime);
}

void main_factory_reset()
{
	/*	M01#BAHAN KUE,MARGARINE - TEPUNG - BUTTER - GULA HALUS - ANEKA COKLAT - SELAI - KACANG - KEJU - PEWARNA - DAN LAINNYA */
	/*	M02#ALAT BAKING,ANEKA LOYANG - OVEN - KLAKAT - SPATULA - JELLY ART - TRAY CAKE - SPUITS - RING CUTTER - ROLLING PIN - PISAU KUE - WIRE COOLING - TROPER - TOPLES - HIASAN ULANG TAHUN - LILIN - DAN LAINNYA */
	/*	M03#KIOS BAKERY,ANEKA ROTI MANIS TAWAR - BROWNIS - PUDING - CROISSANT - BOLEN PISANG - BOLEN PEUYEUM - KUE PIA - CAKE ULANG TAHUN - KUE SUS - PIE BROWNIES - ANEKA COOKIES - CHEESE CAKE - STRUDEL - DAN LAINNYA */
	/*	M04#ROTI BAKAR-KUKUS,COKELAT - SUSU - KEJU - KACANG - STRAWBERRY - BLUEBERRY - CREAM MOCCA - TIRAMISSU - GREEN TEA */

	eeprom_write_string(	MEM_ADDR_MSG01, 
							"BAHAN KUE,MARGARINE - TEPUNG - BUTTER - GULA HALUS - ANEKA COKLAT - SELAI - KACANG - KEJU - PEWARNA - DAN LAINNYA",
							113 );

	eeprom_write_string(	MEM_ADDR_MSG02, 
							"ALAT BAKING,ANEKA LOYANG - OVEN - KLAKAT - SPATULA - JELLY ART - TRAY CAKE - SPUITS - RING CUTTER - ROLLING PIN - PISAU KUE - WIRE COOLING - TROPER - TOPLES - HIASAN ULANG TAHUN - LILIN - DAN LAINNYA",
							119 );

	eeprom_write_string(	MEM_ADDR_MSG03, 
							"KIOS BAKERY,ANEKA ROTI MANIS TAWAR - BROWNIS - PUDING - CROISSANT - BOLEN PISANG - BOLEN PEUYEUM - KUE PIA - CAKE ULANG TAHUN - KUE SUS - PIE BROWNIES - ANEKA COOKIES - CHEESE CAKE - STRUDEL - DAN LAINNYA",
							204 );

	eeprom_write_string(	MEM_ADDR_MSG04, 
							"ROTI BAKAR-KUKUS,COKELAT - SUSU - KEJU - KACANG - STRAWBERRY - BLUEBERRY - CREAM MOCCA - TIRAMISSU - GREEN TEA",
							110 );
}