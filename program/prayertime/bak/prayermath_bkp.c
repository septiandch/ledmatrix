/*
 *  Prayer Math Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prayermath.h"

/* convert Degree to Radian */
double pmath_radians(double degree)
{
	return ((3.1415926 / 180) * degree);
}

/* convert Radian to Degree */
double pmath_degrees(double radian)
{
	return (radian * (180/3.1415926));
}

/* make sure a value is between 0 and 360 */
double pmath_moreless360(double value)
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
double pmath_moreless24(double value)
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
	*hours		= (uint8_t) pmath_moreless24(number);
	*minutes	= (uint8_t) pmath_moreless24(number - *hours) * 60;
}

/* Get Prayer Time */
void pmath_get_prayertimes(	int year, int month, int day,
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
	L = pmath_moreless360(L);
	
	double M = 357.528 + (0.9856003) * D;
	M = pmath_moreless360(M);
	
	double Lambda = L + 1.915 * sin(pmath_radians(M)) + 0.02 * sin(pmath_radians(2 * M));
	Lambda = pmath_moreless360(Lambda);
	
	double Obliquity = 23.439 - 0.0000004 * D;
	double Alpha = pmath_degrees(atan((cos(pmath_radians(Obliquity)) * tan(pmath_radians(Lambda)))));
	Alpha = pmath_moreless360(Alpha);
	
	Alpha = Alpha - (360 * (int)(Alpha / 360));
	Alpha = Alpha + 90 * (floor(Lambda / 90) - floor(Alpha / 90));
	
	double ST = 100.46 + 0.985647352 * D;
	double Dec = pmath_degrees(asin(sin(pmath_radians(Obliquity)) * sin(pmath_radians(Lambda))));
	double Durinal_Arc = pmath_degrees(acos((sin(pmath_radians(-0.8333)) - sin(pmath_radians(Dec)) * sin(pmath_radians(latitude))) / (cos(pmath_radians(Dec)) * cos(pmath_radians(latitude)))));
	
	double Noon = Alpha - ST;
	Noon = pmath_moreless360(Noon);
	
	
	double UT_Noon = Noon - longitude;
	
	
	/*-----------------------------------------------------------------*/
	/*------------- Calculating Prayer Times Arcs & Times -------------*/
	/*-----------------------------------------------------------------*/
	
	/* 2) Zuhr Time [Local noon] */
	_zuhrTime = UT_Noon / 15 + timeZone;
	
	/* Asr Hanafi */
	/* double Asr_Alt =pmath_degrees(atan(2 + tan(pmath_radians(abs(latitude - Dec))))); */
	
	/* Asr Shafii */
	double Asr_Alt = pmath_degrees(atan(1 + tan(pmath_radians(abs(latitude - Dec)))));
	double Asr_Arc = pmath_degrees(acos((sin(pmath_radians(90 - Asr_Alt)) - sin(pmath_radians(Dec)) * sin(pmath_radians(latitude))) / (cos(pmath_radians(Dec)) * cos(pmath_radians(latitude)))));
	Asr_Arc = Asr_Arc / 15;
	/* 3) Asr Time */
	_asrTime = _zuhrTime + Asr_Arc;
	
	/* 1) Shorouq Time */
	_sunRiseTime = _zuhrTime - (Durinal_Arc / 15);
	
	/* 4) Maghrib Time */
	_maghribTime = _zuhrTime + (Durinal_Arc / 15);
	
	
	double Esha_Arc = pmath_degrees(acos((sin(pmath_radians(ishaTwilight)) - sin(pmath_radians(Dec)) * sin(pmath_radians(latitude))) / (cos(pmath_radians(Dec)) * cos(pmath_radians(latitude)))));
	/* 5) Isha Time */
	_ishaTime = _zuhrTime + (Esha_Arc / 15);
	
	/* 0) Fajr Time */
	double Fajr_Arc = pmath_degrees(acos((sin(pmath_radians(fajrTwilight)) - sin(pmath_radians(Dec)) * sin(pmath_radians(latitude))) / (cos(pmath_radians(Dec)) * cos(pmath_radians(latitude)))));
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
