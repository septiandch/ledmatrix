/**
 *  Prayer Time Display Modes Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "pdisplay.h"

const char	sPrayerTime[7][10]		= {	"IMSYAK", "SUBUH", "SYURUQ", "DZUHUR",
										"ASHAR", "MAGHRIB", "ISYA" };
const char	sWeekday[7][10]			= {	"AHAD", "SENIN", "SELASA", "RABU",
										"KAMIS", "JUM'AT", "SABTU" };
const char	sHijriMonth[12][14]		= {	"MUHARRAM", "SHAFAR", "RABIUL AWAL", "RABIUL AKHIR", 
										"JUMADIL AWAL", "JUMADIL AKHR", "RAJAB", "SYA'BAN", 
										"RAMADHAN", "SYAWAL", "DZULQAIDAH", "DZULHIJJAH" };
const char	sJulianMonth[12][10]	= {	"JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI",
										"AGUSTUS", "SEPTEMBER", "OKTOBER", "NOPEMBER", "DESEMBER" };
static char	sMessageBuff[100]		= "";

uint16_t	pdisplay_nCounter 		= 0;
char		pdisplay_bColonState	= ' ';

stDispColor	stDisplayColor			= {CL_BLACK, CL_BLACK, CL_BLACK, CL_BLACK};

void pdisplay_Init(void)
{
	stDisplayColor.clock	= pdisplay_GetColor(MEM_CL_CLOCK);
	stDisplayColor.date		= pdisplay_GetColor(MEM_CL_DATE);
	stDisplayColor.text		= pdisplay_GetColor(MEM_CL_TEXT);
	stDisplayColor.ptime	= pdisplay_GetColor(MEM_CL_PTIME);
	stDisplayColor.counter	= pdisplay_GetColor(MEM_CL_COUNT);

	pdisplay_SetBrightness(eeprom_ReadByte(MEM_BRIGHTNESS));
}

void pdisplay_SetMode(eDisplayMode mode, char *message, uint8_t nPTimeList)
{
	volatile char	sMessageTmp[10]		= "";
	volatile char	sMessageTmp2[10]	= "";
	stRealTime		stHTime;
	
	switch(mode)
	{
		case MODE_POWERSAVE :
			matrix_set_font(System5x7);
			utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			matrix_draw_string(55, 4, sMessageBuff, stDisplayColor.clock);
			
			if(pdisplay_bColonState != bColonState)
			{
				pdisplay_bColonState = bColonState;
				pdisplay_nCounter++;
			}
			break;
			
		case MODE_BIGMESSAGE :
			matrix_set_font(Arial16);
			utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			matrix_draw_string(0, 0, sMessageBuff, stDisplayColor.clock);
			
			pdisplay_nCounter += matrix_draw_marquee(40, 0, 120, 15, message, SCROLL_RIGHT_TO_LEFT, stDisplayColor.text);
			break;
			
		case MODE_SMALLMESSAGE :
			matrix_set_font(System5x7);
			utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageBuff);
			matrix_draw_string(0, 0, sMessageBuff, stDisplayColor.clock);
			
			pdisplay_nCounter += matrix_draw_marquee(0, 8, DISPLAY_WIDTH * DISPLAY_ACROSS, 15, message, SCROLL_RIGHT_TO_LEFT, stDisplayColor.text);
						
			utils_Timestamp(stPTime[nPTimeList].hour, stPTime[nPTimeList].minute, NONE, ':', &sMessageBuff);
			matrix_draw_string(130, 0, sMessageBuff, stDisplayColor.ptime);
			
			utils_Concat("   ", sPrayerTime[nPTimeList], "", &sMessageBuff);
			matrix_draw_string(126 - (strlen(sMessageBuff) * 6), 0, sMessageBuff, stDisplayColor.ptime);
			break;
			
		case MODE_DATETIME :
			matrix_set_font(Arial16);
			utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageTmp);
			matrix_draw_string(0, 0, sMessageTmp, stDisplayColor.clock);
						
			matrix_set_font(System5x7);
			utils_Timestamp(stPTime[nPTimeList].hour, stPTime[nPTimeList].minute, NONE, ':', &sMessageTmp);
			utils_Concat("  ", sPrayerTime[nPTimeList], " ", &sMessageBuff);
			utils_Concat(sMessageBuff, sMessageTmp, "  ", &sMessageBuff);
			matrix_draw_string(matrix_get_textcenter(&sMessageBuff) + 20, 0, sMessageBuff, stDisplayColor.ptime);
			
			utils_Timestamp(stRTime.date, stRTime.month, 2000 + stRTime.year, '-', &sMessageTmp);
			utils_Concat(sWeekday[stRTime.day - 1], ",", sMessageTmp, &sMessageBuff);
			matrix_draw_string(matrix_get_textcenter(&sMessageBuff) + 20, 9, sMessageBuff, stDisplayColor.date);
			
			if(pdisplay_bColonState != bColonState)
			{
				pdisplay_bColonState = bColonState;
				pdisplay_nCounter++;
			}
			break;
			
		case MODE_HIJRIDATE :
			matrix_set_font(Arial16);
			utils_Timestamp(stRTime.hour, stRTime.minute, NONE, bColonState, &sMessageTmp);
			matrix_draw_string(0, 0, sMessageTmp, stDisplayColor.clock);
						
			matrix_set_font(System5x7);
			utils_Timestamp(stPTime[nPTimeList].hour, stPTime[nPTimeList].minute, NONE, ':', &sMessageTmp);
			utils_Concat("  ", sPrayerTime[nPTimeList], " ", &sMessageBuff);
			utils_Concat(sMessageBuff, sMessageTmp, "  ", &sMessageBuff);
			matrix_draw_string(matrix_get_textcenter(&sMessageBuff) + 20, 0, sMessageBuff, stDisplayColor.ptime);
			
			ptime_GetHijriah(&stRTime, &stHTime);
			utils_IntToString(stHTime.date, 1, sMessageTmp);
			utils_IntToString((1400 + stHTime.year), 1, sMessageTmp2);
			
			utils_Concat(sMessageTmp, " ", sHijriMonth[stHTime.month], &sMessageBuff);
			utils_Concat(sMessageBuff, " ", sMessageTmp2, &sMessageBuff);
			matrix_draw_string(matrix_get_textcenter(&sMessageBuff) + 20, 9, sMessageBuff, stDisplayColor.date);
			
			if(pdisplay_bColonState != bColonState)
			{
				pdisplay_bColonState = bColonState;
				pdisplay_nCounter++;
			}
			break;
			
		case MODE_PRAYERTIME :
			matrix_set_font(Arial16);
			if(nPTimeList == 0) utils_Concat("MEMASUKI WAKTU ", " ", sPrayerTime[nPTimeList], &sMessageBuff);
			else utils_Concat("MEMASUKI WAKTU ", "SHALAT ", sPrayerTime[nPTimeList], &sMessageBuff);
			
			pdisplay_nCounter += matrix_draw_marquee(0, 0, 160, 15, sMessageBuff, SCROLL_RIGHT_TO_LEFT, stDisplayColor.text);
			break;
			
		case MODE_COUNTDOWN :			
			matrix_set_font(System5x7);
			
			if(nPTimeList != 10)
			{
				matrix_draw_line(3, 2, 10, 2, stDisplayColor.counter);
				matrix_draw_line(3, 2, 3, 13, stDisplayColor.counter);
				matrix_draw_line(3, 13, 56, 13, stDisplayColor.counter);
				
				matrix_draw_line(148, 2, 156, 2, stDisplayColor.counter);
				matrix_draw_line(156, 2, 156, 13, stDisplayColor.counter);
				matrix_draw_line(102, 13, 156, 13, stDisplayColor.counter);
				
				utils_Concat("MEMASUKI WAKTU", " ", sPrayerTime[nPTimeList], &sMessageBuff);
				
				matrix_draw_string(matrix_get_textcenter(sMessageBuff), 0, sMessageBuff, stDisplayColor.counter);
			}
			else
			{
				matrix_draw_line(51, 2, 56, 2, stDisplayColor.counter);
				matrix_draw_line(51, 2, 51, 13, stDisplayColor.counter);
				matrix_draw_line(51, 13, 56, 13, stDisplayColor.counter);
				
				matrix_draw_line(102, 2, 107, 2, stDisplayColor.counter);
				matrix_draw_line(107, 2, 107, 13, stDisplayColor.counter);
				matrix_draw_line(102, 13, 107, 13, stDisplayColor.counter);
				
				matrix_draw_string(matrix_get_textcenter("IQAMAH"), 0, "IQAMAH", stDisplayColor.counter);
			}
			
			utils_Timestamp	((nPTimeCounter / 60), (nPTimeCounter % 60), NONE, bColonState, &sMessageTmp);
			utils_Concat("-", sMessageTmp, "", &sMessageBuff);
			matrix_draw_string(matrix_get_textcenter(&sMessageBuff), 9, sMessageBuff, stDisplayColor.counter);
			
			if(pdisplay_bColonState != bColonState)
			{
				pdisplay_bColonState = bColonState;
				pdisplay_nCounter++;
				nPTimeCounter--;
			}
			break;
			
		case MODE_BLANK :
			if(pdisplay_bColonState != bColonState)
			{
				pdisplay_bColonState = bColonState;
				pdisplay_nCounter++;
			}
			break;
			
		default :
			/* Do something... */
			break;
	}
}

void pdisplay_GetParam(uint8_t _task, char *_str, uint8_t *_mode, uint8_t *_delay, uint8_t *_iteration)
{
	uint8_t DataHi = 0;
	uint8_t DataLo = 0;
	
	if(_task < PARAM_MAX_TASK)
	{
		fmem_ReadHalfWord(_task * PARAM_MAX_LEN, &DataHi, &DataLo);
		*_mode = DataHi - '0';
		
		fmem_ReadHalfWord((_task * PARAM_MAX_LEN) + 1, &DataHi, &DataLo);
		*_delay = (DataHi - '0') * 10;
		
		fmem_ReadHalfWord((_task * PARAM_MAX_LEN) + 2, &DataHi, &DataLo);
		*_iteration = DataHi - '0';
		
		fmem_ReadString((_task * PARAM_MAX_LEN) + 3, _str);
	}
	else
	{
		if(_task % 2 == 0)
		{
			*_mode =  MODE_HIJRIDATE;
		}
		else
		{
			*_mode =  MODE_DATETIME;
		}
		
		*_delay = 1;
		*_iteration = 2;
		_str[0] = '\0';
	}
}

void pdisplay_SetColor(uint8_t addr, eCOLOR color)
{
	eeprom_WriteByte(addr, (uint8_t) color);
}

eCOLOR pdisplay_GetColor(uint8_t addr)
{
	return (eCOLOR) eeprom_ReadByte(addr);
}

void pdisplay_SetBrightness(uint8_t percentage)
{
#ifdef ENABLE_PWM
	uint16_t value = ((uint16_t)percentage  * PWM_PERIOD) / 100;
	
	TIM_SetCompare1(TIM1, value);
#endif
}
