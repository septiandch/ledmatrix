/*
 *  Prayer Math Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prayermath.h"

/* convert Degree to Radian */
float pmath_degToRad(float degree)
{
	return ((3.1415926 / 180) * degree);
}

/* convert Radian to Degree */
float pmath_radToDeg(float radian)
{
	return (radian * (180/3.1415926));
}

/* make sure a value is between 0 and 360 */
double pmath_moreLess360(double value)
{
	//while(value > 360.0 || value < 0.0)
	{
		if(value > 360.0)
			value -= 360.0;
	
		else if (value < 0.0)
			value += 360.0;
	}
	
	return value;
}

/* make sure a value is between 0 and 24 */
uint8_t pmath_moreLess24(int32_t value)
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

/* convert the float number to Hours and Minutes */
void pmath_GetHourMin(int32_t number, uint8_t *hours, uint8_t *minutes)
{
	*hours		= pmath_moreLess24(number);
	*minutes	= pmath_moreLess24(number - *hours) * 60;
}

/* Get Prayer Time */
void pmath_calcPrayerTimes(	int8_t year, int8_t month, int8_t day,
							int32_t *fajrTime, int32_t *sunRiseTime, int32_t *zuhrTime,
							int32_t *asrTime, int32_t *maghribTime, int32_t *ishaTime)
{
	int8_t timeZone = 7;
	float longitude = 107.1093097;
	float latitude = -6.3406152;
	float fajrTwilight = 20.0;
	float ishaTwilight = 18.0;
	float _fajrTime;
	float _sunRiseTime;
	float _zuhrTime;
	float _asrTime;
	float _maghribTime;
	float _ishaTime;
						
	float D = (367 * year) - ((year + (int)((month + 9) / 12)) * 7 / 4) + (((int)(275 * month / 9)) + day - 730531.5);
	
	float L = 280.461 + 0.9856474 * D;
	
	L = pmath_moreLess360(L);
	
	float M = 357.528 + (0.9856003) * D;
	M = pmath_moreLess360(M);
	
	float Lambda = L + 1.915 * sinf(pmath_degToRad(M)) + 0.02 * sinf(pmath_degToRad(2 * M));
	Lambda = pmath_moreLess360(Lambda);
	
	float Obliquity = 23.439 - 0.0000004 * D;
	float Alpha = pmath_radToDeg(atanf((cos(pmath_degToRad(Obliquity)) * tanf(pmath_degToRad(Lambda)))));
	Alpha = pmath_moreLess360(Alpha);
	
	Alpha = Alpha - (360 * (int)(Alpha / 360));
	Alpha = Alpha + 90 * (floorf(Lambda / 90) - floorf(Alpha / 90));
	
	float ST = 100.46 + 0.985647352 * D;
	float Dec = sinf(pmath_degToRad(Obliquity)) * sinf(pmath_degToRad(Lambda));
		  Dec = asinf(Dec);
		  Dec = pmath_radToDeg(Dec);
	//double Durinal_Arc = pmath_radToDeg(acos((sin(pmath_degToRad(-0.8333)) - sin(pmath_degToRad(Dec)) * sin(pmath_degToRad(latitude))) / (cos(pmath_degToRad(Dec)) * cos(pmath_degToRad(latitude)))));
	//
	//double Noon = Alpha - ST;
	//Noon = pmath_moreLess360(Noon);
	//
	//
	//double UT_Noon = Noon - longitude;
	//
	//
	///*-----------------------------------------------------------------*/
	///*------------- Calculating Prayer Times Arcs & Times -------------*/
	///*-----------------------------------------------------------------*/
	//
	///* 2) Zuhr Time [Local noon] */
	//_zuhrTime = UT_Noon / 15 + timeZone;
	//
	///* Asr Hanafi */
	///* float Asr_Alt =pmath_radToDeg(atan(2 + tan(pmath_degToRad(abs(latitude - Dec))))); */
	//
	///* Asr Shafii */
	//double Asr_Alt = pmath_radToDeg(atan(1 + tan(pmath_degToRad(abs(latitude - Dec)))));
	//double Asr_Arc = pmath_radToDeg(acos((sin(pmath_degToRad(90 - Asr_Alt)) - sin(pmath_degToRad(Dec)) * sin(pmath_degToRad(latitude))) / (cos(pmath_degToRad(Dec)) * cos(pmath_degToRad(latitude)))));
	//Asr_Arc = Asr_Arc / 15;
	///* 3) Asr Time */
	//_asrTime = _zuhrTime + Asr_Arc;
	//
	///* 1) Shorouq Time */
	//_sunRiseTime = _zuhrTime - (Durinal_Arc / 15);
	//
	///* 4) Maghrib Time */
	//_maghribTime = _zuhrTime + (Durinal_Arc / 15);
	//
	//
	//double Esha_Arc = pmath_radToDeg(acos((sin(pmath_degToRad(ishaTwilight)) - sin(pmath_degToRad(Dec)) * sin(pmath_degToRad(latitude))) / (cos(pmath_degToRad(Dec)) * cos(pmath_degToRad(latitude)))));
	///* 5) Isha Time */
	//_ishaTime = _zuhrTime + (Esha_Arc / 15);
	//
	///* 0) Fajr Time */
	//double Fajr_Arc = pmath_radToDeg(acos((sin(pmath_degToRad(fajrTwilight)) - sin(pmath_degToRad(Dec)) * sin(pmath_degToRad(latitude))) / (cos(pmath_degToRad(Dec)) * cos(pmath_degToRad(latitude)))));
	//_fajrTime = _zuhrTime - (Fajr_Arc / 15);
	//
	///* Result */
	//*fajrTime		= round(_fajrTime);
	//*sunRiseTime	= round(_sunRiseTime);
	//*zuhrTime		= round(_zuhrTime);
	//*asrTime		= round(_asrTime);
	//*maghribTime	= round(_maghribTime);
	//*ishaTime		= round(_ishaTime);
	//
	return;
}
