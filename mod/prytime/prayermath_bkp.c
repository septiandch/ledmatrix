/*
 *  Prayer Math Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prayermath.h"

/* convert Degree to Radian */
double pmath_degToRad(double degree)
{
	return ((3.1415926 / 180) * degree);
}

/* convert Radian to Degree */
double pmath_radToDeg(double radian)
{
	return (radian * (180/3.1415926));
}

/* make sure a value is between 0 and 360 */
double pmath_moreLess360(double value)
{
	while(value > 360 || value < 0)
	{
		if(value > 360)
			value -= 360;
	
		else if (value <0)
			value += 360;
	}
	
	return value;
}

/* make sure a value is between 0 and 24 */
double pmath_moreLess24(double value)
{
	while(value > 24 || value < 0)
	{
		if(value > 24)
			value -= 24;
	
		else if (value <0)
			value += 24;
	}
	
	return value;
}

/* convert the double number to Hours and Minutes */
void pmath_doubleToHrMin(double number, uint8_t *hours, uint8_t *minutes)
{
	*hours		= (uint8_t) pmath_moreLess24(number);
	*minutes	= (uint8_t) pmath_moreLess24(number - *hours) * 60;
}

/* Get Prayer Time */
void pmath_calcPrayerTimes(	int year, int month, int day,
						double longitude, double latitude, int timeZone,
						double fajrTwilight, double ishaTwilight,
						double *fajrTime, double *sunRiseTime, double *zuhrTime,
						double *asrTime, double *maghribTime, double *ishaTime)
{
	double _fajrTime;
	double _sunRiseTime;
	double _zuhrTime;
	double _asrTime;
	double _maghribTime;
	double _ishaTime;
						
	double D = (367 * year) - ((year + (int)((month + 9) / 12)) * 7 / 4) + (((int)(275 * month / 9)) + day - 730531.5);
	
	double L = 280.461 + 0.9856474 * D;
	L = pmath_moreLess360(L);
	
	double M = 357.528 + (0.9856003) * D;
	M = pmath_moreLess360(M);
	
	double Lambda = L + 1.915 * sin(pmath_degToRad(M)) + 0.02 * sin(pmath_degToRad(2 * M));
	Lambda = pmath_moreLess360(Lambda);
	
	double Obliquity = 23.439 - 0.0000004 * D;
	double Alpha = pmath_radToDeg(atan((cos(pmath_degToRad(Obliquity)) * tan(pmath_degToRad(Lambda)))));
	Alpha = pmath_moreLess360(Alpha);
	
	Alpha = Alpha - (360 * (int)(Alpha / 360));
	Alpha = Alpha + 90 * (floor(Lambda / 90) - floor(Alpha / 90));
	
	double ST = 100.46 + 0.985647352 * D;
	double Dec = pmath_radToDeg(asin(sin(pmath_degToRad(Obliquity)) * sin(pmath_degToRad(Lambda))));
	double Durinal_Arc = pmath_radToDeg(acos((sin(pmath_degToRad(-0.8333)) - sin(pmath_degToRad(Dec)) * sin(pmath_degToRad(latitude))) / (cos(pmath_degToRad(Dec)) * cos(pmath_degToRad(latitude)))));
	
	double Noon = Alpha - ST;
	Noon = pmath_moreLess360(Noon);
	
	
	double UT_Noon = Noon - longitude;
	
	
	/*-----------------------------------------------------------------*/
	/*------------- Calculating Prayer Times Arcs & Times -------------*/
	/*-----------------------------------------------------------------*/
	
	/* 2) Zuhr Time [Local noon] */
	_zuhrTime = UT_Noon / 15 + timeZone;
	
	/* Asr Hanafi */
	/* double Asr_Alt =pmath_radToDeg(atan(2 + tan(pmath_degToRad(abs(latitude - Dec))))); */
	
	/* Asr Shafii */
	double Asr_Alt = pmath_radToDeg(atan(1 + tan(pmath_degToRad(abs(latitude - Dec)))));
	double Asr_Arc = pmath_radToDeg(acos((sin(pmath_degToRad(90 - Asr_Alt)) - sin(pmath_degToRad(Dec)) * sin(pmath_degToRad(latitude))) / (cos(pmath_degToRad(Dec)) * cos(pmath_degToRad(latitude)))));
	Asr_Arc = Asr_Arc / 15;
	/* 3) Asr Time */
	_asrTime = _zuhrTime + Asr_Arc;
	
	/* 1) Shorouq Time */
	_sunRiseTime = _zuhrTime - (Durinal_Arc / 15);
	
	/* 4) Maghrib Time */
	_maghribTime = _zuhrTime + (Durinal_Arc / 15);
	
	
	double Esha_Arc = pmath_radToDeg(acos((sin(pmath_degToRad(ishaTwilight)) - sin(pmath_degToRad(Dec)) * sin(pmath_degToRad(latitude))) / (cos(pmath_degToRad(Dec)) * cos(pmath_degToRad(latitude)))));
	/* 5) Isha Time */
	_ishaTime = _zuhrTime + (Esha_Arc / 15);
	
	/* 0) Fajr Time */
	double Fajr_Arc = pmath_radToDeg(acos((sin(pmath_degToRad(fajrTwilight)) - sin(pmath_degToRad(Dec)) * sin(pmath_degToRad(latitude))) / (cos(pmath_degToRad(Dec)) * cos(pmath_degToRad(latitude)))));
	_fajrTime = _zuhrTime - (Fajr_Arc / 15);
	
	/* Result */
	*fajrTime		= _fajrTime;
	*sunRiseTime	= _sunRiseTime;
	*zuhrTime		= _zuhrTime;
	*asrTime		= _asrTime;
	*maghribTime	= _maghribTime;
	*ishaTime		= _ishaTime;
	
	return;
}
