/*
 *  Prayer Math Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PRAYERMATH_H_
#define _PRAYERMATH_H_

#include "common/pgmspace.h"
#include <math.h>

enum ePTIME
{
	ePTIME_FAJR = 0,
	ePTIME_SUNRISE,
	ePTIME_ZUHR,
	ePTIME_ASHR,
	ePTIME_MAGHRIB,
	ePTIME_ISHA,
	ePTIME_IMSYAK,
	ePTIME_MAX
};

typedef struct
{
	uint8_t hour;
	uint8_t minute;
} stTime;

extern void		pmath_setup(uint16_t year, int8_t _timezone, double _longitude, double _latitude, double _fajrTwilight, double _ishaTwilight);
extern void		pmath_get_prayertimes(int16_t month, int16_t date, stTime *pstTimes);
extern void		pmath_correct_time(stTime *pstTime, int16_t nMinutes);

#endif /* _PRAYERMATH_H_ */
