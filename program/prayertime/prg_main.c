/**
 *  Display Application Program
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prg_def.h"
#include "library/usart.h"
#include "library/delay.h"
#include "prayermath.h"

/* GLOBAL VARIABLES */
stRealTimeVar	stRTime;
stTime			stPrayerTime[7];
char			sMessage[128];
char			sPrayer[6][6];

void prg_init(void)
{	
	/* Startup delay */
	delay_ms(500);

	/* IO Initialization */
	io_buzzer_init();
	//io_int_init(&prg_get_rtc);

	/* RTC Initialization */
	//rtc_init(SQW_1HZ);

	/* USART Initialization */
	//usart_init(9600);

	/* Display Initialization */
	dmd_init(mode_rgb, 4, 32, 16, 2, 2);
	dmd_set_brightness(5);
	dmd_set_font(System5x7);
	
	//int16_t h, m;
	char msg[10];
	char text[10];
	uint16_t i = 0; 
	uint16_t j = 0;
	
	//pmath_setup(2019, 7, 107.1093097, -6.3406152, -20.0, -18.0);

	//pmath_get_prayertimes(10, 30, &stPrayerTime);

	//utils_int2str(stPrayerTime[ePTIME_FAJR].hour, 1, &s1);
	//utils_int2str(stPrayerTime[ePTIME_FAJR].minute, 1, &s2);
	//utils_concat(s1, ":", s2, &sMessage);
	//dmd_draw_string(0, 0, sMessage, eCL_RED);
	
	//utils_int2str(stPrayerTime[ePTIME_IMSYAK].hour, 1, &s1);
	//utils_int2str(stPrayerTime[ePTIME_IMSYAK].minute, 1, &s2);
	//utils_concat(s1, ":", s2, &sMessage);
	
	uint8_t speed_tbl[] = {94, 85, 86, 91, 90, 88, 90, 92, 89, 93, 94, 92, 90, 89, 89, 90, 91, 90, 88, 92};
	
	//dmd_draw_line(0, 0, 0, 5, eCL_RED);

	while(1)
	{
		for(i = 0; i < 20; i++)
		{
			utils_int2str(speed_tbl[i], 1, &msg);
			
			dmd_set_font(ArialBlack16);
			dmd_draw_string(0,  0, "SPD", eCL_GREEN);
			dmd_draw_string(0,  16, "AVE ", eCL_GREEN);
			dmd_draw_char(29,  0, ':', eCL_GREEN);
			dmd_draw_char(29,  16, ':', eCL_GREEN);

			dmd_draw_string(37,  0, msg, eCL_RED);
			dmd_draw_string(37,  16, "90", eCL_RED);

			delay_ms(500);
		}
		dmd_clr_screen();
		delay_ms(20);

		for(i = 0; i < 22; i++)
		{
			utils_int2str(i, 1, &msg);
			utils_concat("00", ":", msg, &text);
			
			dmd_draw_string(2,  0, "SETTING", eCL_GREEN);
			dmd_draw_string(15,  16, text, eCL_RED);

			delay_ms(500);
		}
		dmd_clr_screen();
		delay_ms(20);

		dmd_set_font(System5x7);
		dmd_draw_string(0,  0, "SET1", eCL_GREEN);
		dmd_draw_string(0,  8, "SET2", eCL_GREEN);
		dmd_draw_string(0, 16, "SET3", eCL_GREEN);
		dmd_draw_string(0, 24, "SET4", eCL_GREEN);

		dmd_draw_char(29,  0, ':', eCL_GREEN);
		dmd_draw_char(29,  8, ':', eCL_GREEN);
		dmd_draw_char(29, 16, ':', eCL_GREEN);
		dmd_draw_char(29, 24, ':', eCL_GREEN);

		dmd_draw_string(34,  0, "11:30", eCL_RED);
		dmd_draw_string(34,  8, "10:25", eCL_RED);
		dmd_draw_string(34, 16, "11:43", eCL_RED);
		dmd_draw_string(34, 24, "10:57", eCL_RED);
		
		delay_ms(1000);
		dmd_clr_screen();
		delay_ms(20);

		dmd_draw_string(0,  0, "SET5", eCL_GREEN);
		dmd_draw_string(0,  8, "SET6", eCL_GREEN);
		dmd_draw_string(0, 16, "SET7", eCL_GREEN);
		dmd_draw_string(0, 24, "SET8", eCL_GREEN);

		dmd_draw_char(29,  0, ':', eCL_GREEN);
		dmd_draw_char(29,  8, ':', eCL_GREEN);
		dmd_draw_char(29, 16, ':', eCL_GREEN);
		dmd_draw_char(29, 24, ':', eCL_GREEN);

		dmd_draw_string(34,  0, "10:30", eCL_RED);
		dmd_draw_string(34,  8, "10:12", eCL_RED);
		dmd_draw_string(34, 16, "09:59", eCL_RED);
		dmd_draw_string(34, 24, "11:24", eCL_RED);
		
		delay_ms(1000);
		dmd_clr_screen();
		delay_ms(20);
	}

	/*
	uint8_t state = 0;

	while(1)
	{
		dmd_set_font(System5x7);
		dmd_draw_string(13,  0, "SEDIA :", eCL_RED);
		dmd_draw_line(12, 8, 52, 8, eCL_RED);
		dmd_draw_string(5,  11, "BAHAN KUE", eCL_RED);

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 21, 64, 10, "PERLENGKAPAN BAKING", eMARQUEE_RIGHT_TO_LEFT, eCL_RED);
			delay_ms(5);
		}

		state = 0;
		dmd_clr_screen();


		dmd_set_font(System5x7);
		dmd_draw_string(0,  0, "KIOS BAKERY", eCL_RED);
		dmd_draw_line(0, 8, 63, 8, eCL_RED);

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "ANEKA ROTI", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "PASTRY (DANIS)", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, " BROWNIS  ", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, " PUDDING  ", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "PROLL TAPE", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "BOLEN PISANG", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;
		
		dmd_clr_screen();



		dmd_set_font(System5x7);
		dmd_draw_string(0,  0, "ROTI BAKAR PRIANGAN", eCL_RED);
		dmd_draw_line(0, 8, 63, 8, eCL_RED);

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "STRAWBERRY", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "BLUEBERRY", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "TIRAMISSU", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "GREEN TEA", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, " COKELAT  ", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "   KEJU   ", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;

		while(state != 1)
		{
			state = dmd_draw_marquee(0, 11, 64, 20, "  KACANG  ", eMARQUEE_BOTTOM_TO_TOP, eCL_RED);
			delay_ms(5);
		}
		state = 0;
		
		dmd_clr_screen();
	}
	*/

	/*
	//for(j = 1; j <= 12; j++)
	{
	usart_puts("Month: ");
	usart_puti(j);
	usart_puts(" =====================================================");
	//for(i = 1; i <= 30; i++)
	{
		pmath_get_prayertimes(j, i, &stPrayerTimes);
		
		usart_puts("=====================================================");

		pmath_hourmin(prtime[0], &h, &m);
		utils_int2str(h, 1, &s1);
		utils_int2str(m, 1, &s2);
		utils_concat(s1, ":", s2, &sPrayer[0]);
		//usart_puts(sMessage);
		//usart_putc('\n');
		pmath_hourmin(prtime[1], &h, &m);
		utils_int2str(h, 1, &s1);
		utils_int2str(m, 1, &s2);
		utils_concat(s1, ":", s2, &sPrayer[1]);
		//usart_puts(sMessage);
		//usart_putc('\n');
		pmath_hourmin(prtime[2], &h, &m);
		utils_int2str(h, 1, &s1);
		utils_int2str(m, 1, &s2);
		utils_concat(s1, ":", s2, &sPrayer[2]);
		//usart_puts(sMessage);
		//usart_putc('\n');
		pmath_hourmin(prtime[3], &h, &m);
		utils_int2str(h, 1, &s1);
		utils_int2str(m, 1, &s2);
		utils_concat(s1, ":", s2, &sPrayer[3]);
		//usart_puts(sMessage);
		//usart_putc('\n');
		pmath_hourmin(prtime[4], &h, &m);
		utils_int2str(h, 1, &s1);
		utils_int2str(m, 1, &s2);
		utils_concat(s1, ":", s2, &sPrayer[4]);
		//usart_puts(sMessage);
		//usart_putc('\n');
		pmath_hourmin(prtime[5], &h, &m);
		utils_int2str(h, 1, &s1);
		utils_int2str(m, 1, &s2);
		utils_concat(s1, ":", s2, &sPrayer[5]);
		//usart_puts(sMessage);
		//usart_putc('\n');

		utils_concat(sPrayer[0], "", "", &sMessage);
		utils_concat(sMessage, "\t", sPrayer[1], &sMessage);
		utils_concat(sMessage, "\t", sPrayer[2], &sMessage);
		utils_concat(sMessage, "\t", sPrayer[3], &sMessage);
		utils_concat(sMessage, "\t", sPrayer[4], &sMessage);
		utils_concat(sMessage, "\t", sPrayer[5], &sMessage);
		usart_puts(sMessage);
	}

	usart_puts("\n");
	usart_puts("\n");
	}
	*/

	//io_buzzer_pin(SET);
	//delay_ms(50);
	//io_buzzer_pin(RESET);
}

void prg_set_rtc(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second)
{	
	stRealTimeVar _stRTime = {year, month, date, 0, hour, minute, second};

	rtc_set_time(&_stRTime);
}

void prg_get_rtc(void)
{
	rtc_get_time(&stRTime);

	//utils_timestamp(stRTime.hour, stRTime.minute, stRTime.second, ':', &sMessage);
	//dmd_draw_string(0, 8, "                ", eCL_RED);
	//dmd_draw_string(-15, 8, sMessage, eCL_RED);
	//dmd_init_doublebuffer();
}