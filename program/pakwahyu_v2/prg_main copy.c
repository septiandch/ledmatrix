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
#define MSGDATA_MIN_SIZE		20
#define MSGDATA_MAX_SIZE		500

#define CUSTOM_DISP_HOUR		15
#define CUSTOM_DISP_MINS		0

/*----- Global Variables -----*/
stRealTimeVar	stRTime;
stDisplayMsg	sMessage[MSGDATA_COUNT];

char	sShortText[MSGDATA_MIN_SIZE];
char	sLongText[MSGDATA_MAX_SIZE];

char	sTitle[][MSGDATA_MIN_SIZE]	= {	"BAHAN KUE", "ALAT BAKING", "KIOS BAKERY", "ROTI BAKAR PRIANGAN", "ROTI BAKAR-KUKUS"};
char	sSubMsg1[MSGDATA_MAX_SIZE]	= {	"MARGARINE - TEPUNG - BUTTER - GULA HALUS - ANEKA COKLAT - SELAI - KACANG - KEJU - PEWARNA - DAN LAINNYA"};
char	sSubMsg2[MSGDATA_MAX_SIZE]	= {	"ANEKA LOYANG - OVEN - KLAKAT - SPATULA - JELLY ART - TRAY CAKE - SPUITS - RING CUTTER - ROLLING PIN - PISAU KUE - WIRE COOLING - TROPER - TOPLES - HIASAN ULANG TAHUN - LILIN - DAN LAINNYA"};
char	sSubMsg3[MSGDATA_MAX_SIZE]	= {	"ANEKA ROTI MANIS TAWAR - BROWNIS - PUDING - CROISSANT - BOLEN PISANG - BOLEN PEUYEUM - KUE PIA - CAKE ULANG TAHUN - KUE SUS - PIE BROWNIES - ANEKA COOKIES - CHEESE CAKE - STRUDEL - DAN LAINNYA"};
char	sSubMsg4[MSGDATA_MAX_SIZE]	= {	"COKELAT - SUSU - KEJU - KACANG - STRAWBERRY - BLUEBERRY - CREAM MOCCA - TIRAMISSU - GREEN TEA"};

volatile char	sMsgBuffer[MSGDATA_COUNT][MSGDATA_MAX_SIZE];


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
uint8_t main_display_draw_menus(stDisplayMsg *sMsg, char *sMainTitle, char *sSubMsgList, eMarqueeDir eDir);
uint8_t main_display_draw_default(stDisplayMsg *sMsg, char *sMainTitle, char *sSubMsgList, eMarqueeDir eDir);
uint8_t main_display_draw_title(stDisplayMsg *sMsg, char *sTitle, eMarqueeDir eDir);
uint8_t main_display_draw_clock(stDisplayMsg *sMsg, stRealTimeVar *stTime);

void main_rtc_time_set(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second);
void main_rtc_time_get(void);
void main_rtc_tick_add(void);
void main_rtc_tick_reset(void);

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

	/* RTC Initialization */
	io_rtc_init();
	io_int_init(&main_rtc_time_get);

	/* Command Functions Initialize */
	cmd_init();

	/* Memory initialize */
	main_mem_init();

	delay_ms(500);

#if 0
	main_rtc_time_set(20, 4, 15, 22, 00, 0);
#endif

	/* Display Initialization */
	display_init(1);
	
	io_buzzer_pin(SET);
	delay_ms(100);
	io_buzzer_pin(RESET);
	
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
			display_message_draw_static_string(0, 0, "                    ", System5x7, eCL_RED);
			display_message_draw_static_string(0, 8, "                    ", System5x7, eCL_RED);
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
	display_message_init(&sMsg[0], &sShortText, MSGDATA_MIN_SIZE, System5x7, 0, 0, eCL_RED);
	display_message_init(&sMsg[1], &sLongText, MSGDATA_MAX_SIZE, System5x7, 0, 0, eCL_RED);
}

void main_message_prop_set(stDisplayMsg *sMsg, eDisplayType eMode)
{
	/* Clear text buffer */
	display_message_clr_text(&sMsg[0]);
	display_message_clr_text(&sMsg[1]);

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
	for(i = 0; i < 32000; i++)
	{
		eeprom_write_byte(i, '\0');
	}
#endif

	eeprom_read_string(MEM_ADDR_MSG01, &sMsgBuffer[0]);
	eeprom_read_string(MEM_ADDR_MSG02, &sMsgBuffer[1]);
	eeprom_read_string(MEM_ADDR_MSG03, &sMsgBuffer[2]);
	eeprom_read_string(MEM_ADDR_MSG04, &sMsgBuffer[3]);
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
	uint8_t	bDone			= 0;
	char	sMainText[20]	= "";
	char	sSubText[300]	= "";

	switch(eMode)
	{
		case eDISTYP_TITLE1 :
			main_message_parse(&sMsgBuffer[0], &sMainText, &sSubText);
			if(sMainText[0] == '\0' && sSubText[0] == '\0')
			{
				memcpy(&sMainText, &sTitle[0], utils_strlen(&sMainText));
				memcpy(&sSubText, &sSubMsg1, utils_strlen(&sSubText));
			}

			bDone = main_display_draw_title(sMsg, sMainText, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_1 :
			main_message_parse(&sMsgBuffer[0], &sMainText, &sSubText);
			if(sMainText[0] == '\0' && sSubText[0] == '\0')
			{
				memcpy(&sMainText, &sTitle[0], utils_strlen(&sMainText));
				memcpy(&sSubText, &sSubMsg1, utils_strlen(&sSubText));
			}

			bDone = main_display_draw_menus(sMsg, sMainText, sSubText, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE2 :
			main_message_parse(&sMsgBuffer[1], &sMainText, &sSubText);
			if(sMainText[0] == '\0' && sSubText[0] == '\0')
			{
				memcpy(&sMainText, &sTitle[1], utils_strlen(&sMainText));
				memcpy(&sSubText, &sSubMsg2, utils_strlen(&sSubText));
			}

			bDone = main_display_draw_title(sMsg, sTitle[1], eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_2 :
			main_message_parse(&sMsgBuffer[1], &sMainText, &sSubText);
			if(sMainText[0] == '\0' && sSubText[0] == '\0')
			{
				memcpy(&sMainText, &sTitle[1], utils_strlen(&sMainText));
				memcpy(&sSubText, &sSubMsg2, utils_strlen(&sSubText));
			}

			bDone = main_display_draw_menus(sMsg, sTitle[1], sSubMsg2, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE3 :
			main_message_parse(&sMsgBuffer[2], &sMainText, &sSubText);
			if(sMainText[0] == '\0' && sSubText[0] == '\0')
			{
				memcpy(&sMainText, &sTitle[2], utils_strlen(&sMainText));
				memcpy(&sSubText, &sSubMsg3, utils_strlen(&sSubText));
			}

			bDone = main_display_draw_title(sMsg, sTitle[2], eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_3 :
			main_message_parse(&sMsgBuffer[2], &sMainText, &sSubText);
			if(sMainText[0] == '\0' && sSubText[0] == '\0')
			{
				memcpy(&sMainText, &sTitle[2], utils_strlen(&sMainText));
				memcpy(&sSubText, &sSubMsg3, utils_strlen(&sSubText));
			}

			bDone = main_display_draw_menus(sMsg, sTitle[2], sSubMsg3, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE4 :
			main_message_parse(&sMsgBuffer[3], &sMainText, &sSubText);
			if(sMainText[0] == '\0' && sSubText[0] == '\0')
			{
				memcpy(&sMainText, &sTitle[4], utils_strlen(&sMainText));
				memcpy(&sSubText, &sSubMsg4, utils_strlen(&sSubText));
			}

			if(stRTime.hour >= CUSTOM_DISP_HOUR && stRTime.minute >= CUSTOM_DISP_MINS)
			{
				bDone = main_display_draw_title(sMsg, sTitle[3], eMARQUEE_RIGHT_TO_LEFT);
			}
			else
			{
				bDone = 1;
			}
			break;

		case eDISTYP_4 :
			main_message_parse(&sMsgBuffer[3], &sMainText, &sSubText);
			if(sMainText[0] == '\0' && sSubText[0] == '\0')
			{
				memcpy(&sMainText, &sTitle[4], utils_strlen(&sMainText));
				memcpy(&sSubText, &sSubMsg4, utils_strlen(&sSubText));
			}

			if(stRTime.hour >= CUSTOM_DISP_HOUR && stRTime.minute >= CUSTOM_DISP_MINS)
			{				
				bDone = main_display_draw_menus(sMsg, sTitle[4], sSubMsg4, eMARQUEE_RIGHT_TO_LEFT);
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

uint8_t main_display_draw_bkp(stDisplayMsg *sMsg, eDisplayType eMode)
{
	uint8_t bDone = 0;

	switch(eMode)
	{
		case eDISTYP_TITLE1 :
			bDone = main_display_draw_title(sMsg, sTitle[0], eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_1 :
			bDone = main_display_draw_menus(sMsg, sTitle[0], sSubMsg1, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE2 :
			bDone = main_display_draw_title(sMsg, sTitle[1], eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_2 :
			bDone = main_display_draw_menus(sMsg, sTitle[1], sSubMsg2, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE3 :
			bDone = main_display_draw_title(sMsg, sTitle[2], eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_3 :
			bDone = main_display_draw_menus(sMsg, sTitle[2], sSubMsg3, eMARQUEE_RIGHT_TO_LEFT);
			break;

		case eDISTYP_TITLE4 :
			if(stRTime.hour >= CUSTOM_DISP_HOUR && stRTime.minute >= CUSTOM_DISP_MINS)
			{
				bDone = main_display_draw_title(sMsg, sTitle[3], eMARQUEE_RIGHT_TO_LEFT);
			}
			else
			{
				bDone = 1;
			}
			break;

		case eDISTYP_4 :
			if(stRTime.hour >= CUSTOM_DISP_HOUR && stRTime.minute >= CUSTOM_DISP_MINS)
			{				
				bDone = main_display_draw_menus(sMsg, sTitle[4], sSubMsg4, eMARQUEE_RIGHT_TO_LEFT);
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

uint8_t main_display_draw_menus(stDisplayMsg *sMsg, char *sMainTitle, char *sSubMsgList, eMarqueeDir eDir)
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
		/* Setup Title text */
		display_message_set_text(&sMsg[0], sMainTitle);
		
		/* Setup menu lists */
		display_message_set_text(&sMsg[1], sSubMsgList);

		/* Draw Title Text */
		wMsgPos = display_message_get_centerpos(&sMsg[0], 0);
		display_message_set_pos(&sMsg[0], wMsgPos, 0);
		display_message_draw(&sMsg[0]);

		/* Set Sub Menu Marquee */
		display_message_set_pos(&sMsg[1], 0, (DISPLAY_HEIGHT / 2));
		display_marquee_init(&sMsg[1], eMARQUEE_RIGHT_TO_LEFT, DISABLE);
		
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

uint8_t main_display_draw_default(stDisplayMsg *sMsg, char *sMainTitle, char *sSubMsgList, eMarqueeDir eDir)
{
	uint8_t			bDispModeDone = 0;
	int16_t			wMsgPos = 0;
	eMarqueeStat	eStat;
	
	eStat = display_marquee_draw(&sMsg[1]);
	
	if(eStat == eMARQUEE_STAT_MOVED)
	{
		display_marquee_iteration_add(&sMsg[1]);
		display_marquee_set_state(&sMsg[1], eMARQUEE_STAT_READY);
	}
	
	if(eStat == eMARQUEE_STAT_READY)
	{
		/* Set Title and Sub Text */
		display_message_set_text(&sMsg[0], sMainTitle);
		display_message_set_text(&sMsg[1], sSubMsgList[sMsg[1].stMarquee.bIteration]);
		
		if	(	sMsg[1].pcString[0] == '[' && 
				sMsg[1].pcString[1] == 'e' &&
				sMsg[1].pcString[2] == ']' )
		{
			bDispModeDone = 1;
			display_clear();
		}
		else
		{
			/* Draw Title Text */
			wMsgPos = display_message_get_centerpos(&sMsg[0], 0);
			display_message_set_pos(&sMsg[0], wMsgPos, 0);
			display_message_draw(&sMsg[0]);

			if(eDir == eMARQUEE_BOTTOM_TO_TOP)
			{
				wMsgPos = display_message_get_centerpos(&sMsg[1], 0);
				display_message_set_pos(&sMsg[1], wMsgPos, 0);
				display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);
			}
			else if(eMARQUEE_RIGHT_TO_LEFT)
			{
				display_message_set_pos(&sMsg[1], 0, (DISPLAY_HEIGHT / 2));
				display_marquee_init(&sMsg[1], eMARQUEE_RIGHT_TO_LEFT, DISABLE);
			}
			
			display_marquee_set_state(&sMsg[1], eMARQUEE_STAT_MOVING);
		}
	}
	
	/* Idle based on posiiton */
	if(eStat != eMARQUEE_STAT_IDLE)
	{
		int16_t wLen = display_message_get_strwidth(&sMsg[1]);
		int16_t wPos = display_message_get_centerpos(&sMsg[1], 0);

		if(sMsg[1].stMarquee.eDir == eMARQUEE_BOTTOM_TO_TOP && display_marquee_checkonpos(&sMsg[1], (DISPLAY_HEIGHT / 2)))
		{
			display_marquee_idle_set(&sMsg[1], 10, eMARQUEE_STAT_MOVING);
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
	}

	delay_ms(30);

	return bDispModeDone;
}

uint8_t main_display_draw_title(stDisplayMsg *sMsg, char *sTitle, eMarqueeDir eDir)
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
		/* Set Title Text */
		display_message_set_text(&sMsg[0], sTitle);
		
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

uint8_t main_display_draw_autodir(stDisplayMsg *sMsg, char *sMainTitle, char sSubMsgList[][MSGDATA_MIN_SIZE])
{
	uint8_t			bDispModeDone = 0;
	int16_t			wMsgPos = 0;
	eMarqueeStat	eStat;
	
	eStat = display_marquee_draw(&sMsg[1]);
	
	if(eStat == eMARQUEE_STAT_MOVED)
	{
		if(sMsg[1].stMarquee.eDir == eMARQUEE_BOTTOM_TO_TOP)
		{
			display_marquee_iteration_add(&sMsg[1]);
			display_marquee_set_state(&sMsg[1], eMARQUEE_STAT_READY);
		}
	}
	
	if(eStat == eMARQUEE_STAT_READY)
	{
		/* Set Title and Sub Text */
		display_message_set_text(&sMsg[0], sMainTitle);
		display_message_set_text(&sMsg[1], sSubMsgList[sMsg[1].stMarquee.bIteration]);
		
		if	(	sMsg[1].pcString[0] == '[' && 
				sMsg[1].pcString[1] == 'e' &&
				sMsg[1].pcString[2] == ']' )
		{
			bDispModeDone = 1;
			display_clear();
		}
		else
		{
			/* Draw Title Text */
			wMsgPos = display_message_get_centerpos(&sMsg[0], 0);
			display_message_set_pos(&sMsg[0], wMsgPos, 0);
			display_message_draw(&sMsg[0]);

			/* Setup Sub Text */
			display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, DISABLE);

			wMsgPos = display_message_get_centerpos(&sMsg[1].pcString, 0);
			if(wMsgPos >= 0)
			{
				display_message_set_pos(&sMsg[1], wMsgPos, 0);
			}
			else
			{
				display_message_set_pos(&sMsg[1], 0, 0);
			}
			
			display_marquee_set_state(&sMsg[1], eMARQUEE_STAT_MOVING);
		}
	}
	
	/* Idle based on posiiton */
	if(eStat != eMARQUEE_STAT_IDLE)
	{
		int16_t wLen = display_message_get_strwidth(&sMsg[1]);
		int16_t wPos = display_message_get_centerpos(&sMsg[1], 0);

		if(sMsg[1].stMarquee.eDir == eMARQUEE_BOTTOM_TO_TOP && display_marquee_checkonpos(&sMsg[1], (DISPLAY_HEIGHT / 2)))
		{
			if(wPos >= 0)
			{
				display_marquee_idle_set(&sMsg[1], 10, eMARQUEE_STAT_MOVING);
			}
			else
			{
				display_message_set_pos(&sMsg[1], sMsg[1].stPos.X, (DISPLAY_HEIGHT / 2));
				display_marquee_init(&sMsg[1], eMARQUEE_RIGHT_TO_LEFT, ENABLE);
				display_marquee_idle_set(&sMsg[1], 10, eMARQUEE_STAT_MOVING);
			}
		}
		else if(sMsg[1].stMarquee.eDir == eMARQUEE_RIGHT_TO_LEFT && display_marquee_checkonpos(&sMsg[1], (DISPLAY_WIDTH * DISPLAY_COUNT_ACCROSS) - wLen))
		{
			display_message_set_pos(&sMsg[1], ((DISPLAY_WIDTH * DISPLAY_COUNT_ACCROSS) - wLen), (DISPLAY_HEIGHT / 2));
			display_marquee_init(&sMsg[1], eMARQUEE_BOTTOM_TO_TOP, ENABLE);
			display_marquee_idle_set(&sMsg[1], 10, eMARQUEE_STAT_MOVING);
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

	display_message_set_text(&sMsg[0], sTime);

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
	switch(eCommandCode)
	{
		case eCMD_UPDTMSG01:
			memset(&sMsgBuffer[0], 0, MSGDATA_MAX_SIZE);
			cmd_get_data(&sMsgBuffer[0]);

			eeprom_write_string(MEM_ADDR_MSG01, &sMsgBuffer[0], utils_strlen(&sMsgBuffer[0]));
			break;

		case eCMD_UPDTMSG02:
			memset(&sMsgBuffer[1], 0, MSGDATA_MAX_SIZE);
			cmd_get_data(&sMsgBuffer[1]);

			eeprom_write_string(MEM_ADDR_MSG02, &sMsgBuffer[1], utils_strlen(&sMsgBuffer[1]));
			break;

		case eCMD_UPDTMSG03:
			memset(&sMsgBuffer[2], 0, MSGDATA_MAX_SIZE);
			cmd_get_data(&sMsgBuffer[2]);

			eeprom_write_string(MEM_ADDR_MSG03, &sMsgBuffer[2], utils_strlen(&sMsgBuffer[2]));
			break;

		case eCMD_UPDTMSG04:
			memset(&sMsgBuffer[3], 0, MSGDATA_MAX_SIZE);
			cmd_get_data(&sMsgBuffer[3]);

			eeprom_write_string(MEM_ADDR_MSG04, &sMsgBuffer[3], utils_strlen(&sMsgBuffer[3]));
			break;

		case eCMD_SENDMSG01:
			usart_puts(&sMsgBuffer[0]);
			usart_putc('\n');
			break;

		case eCMD_SENDMSG02:
			usart_puts(&sMsgBuffer[1]);
			usart_putc('\n');
			break;

		case eCMD_SENDMSG03:
			usart_puts(&sMsgBuffer[2]);
			usart_putc('\n');
			break;

		case eCMD_SENDMSG04:
			usart_puts(&sMsgBuffer[3]);
			usart_putc('\n');
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