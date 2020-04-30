/*
 *  Prayer Math Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prayermath.h"
#include "library/usart.h"
#include "library/qfpio.h"
#include "library/qfplib.h"

/* Prayertime Parameters */
uint16_t	nFixedYear		= 0;
int8_t		bTimeZone		= 0;
double		dLongitude		= 0.0;
double		dLatitude		= 0.0;
double		dFajrTwilight	= 0.0;
double		dIshaTwilight	= 0.0;

/* Function Prototypes */
double	pmath_deg2rad(double degree);
double	pmath_rad2deg(double radian);
double	pmath_moreless360(double value);
double 	pmath_moreless24(double value);
void	pmath_get_time(double number, stTime *pstTime);

/* Convert Degree to Radian */
double pmath_deg2rad(double degree)
{
	return ((3.1415926 / 180) * degree);
}

/* Vonvert Radian to Degree */
double pmath_rad2deg(double radian)
{
	return (radian * (180/3.1415926));
}

/* Make sure a value is between 0 and 360 */
double pmath_moreless360(double value)
{
    /* While(value > 360 || value < 0) */
    {
        if(value > 360)
            value -= 360;

        else if (value <0)
            value += 360;
    }

    return value;
}

/* Make sure a value is between 0 and 24 */
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

/* Convert the double number to Hours and Minutes */
void pmath_get_time(double number, stTime *pstTime)
{
	pstTime->hour	= (uint8_t) floor(pmath_moreless24(number));
	pstTime->minute	= (uint8_t) floor(pmath_moreless24(number - pstTime->hour) * 60);
}

/* Set time correction */
void pmath_correct_time(stTime *pstTime, int16_t nMinutes)
{
	uint16_t nCorrection = (pstTime->hour * 60) + pstTime->minute + nMinutes;

	pstTime->hour	= (uint8_t)(nCorrection / 60);
	pstTime->minute	= nCorrection - (pstTime->hour * 60);
}

/* Set Prayer Time parameters */
void pmath_setup(uint16_t _year, int8_t _timezone, double _longitude, double _latitude, double _fajrTwilight, double _ishaTwilight)
{
	nFixedYear			= _year;
	bTimeZone			= _timezone;
	dLongitude			= _longitude;
	dLatitude			= _latitude;
	dFajrTwilight		= _fajrTwilight;
	dIshaTwilight		= _ishaTwilight;
}

/* Get Prayer Time */
void pmath_get_prayertimes(int16_t month, int16_t date, stTime *pstTimes)
{
	double dFajrTime = 0.0;
	double dRiseTime = 0.0;
	double dZuhrTime = 0.0;
	double dAshrTime = 0.0;
	double dMagrTime = 0.0;
	double dIshaTime = 0.0;
	
	double D = (367 * nFixedYear) - ((nFixedYear + (int16_t)((month + 9) / 12)) * 7 / 4) + ((int16_t)(275 * month / 9) + date - 730531.5);

	double L = 280.461 + 0.9856474 * D;
	L = pmath_moreless360(L);
	
	double M = 357.528 + (0.9856003) * D;
	M = pmath_moreless360(M);
	
	double Lambda = L + 1.915 * sin(pmath_deg2rad(M)) + 0.02 * sin(pmath_deg2rad(2 * M));
	Lambda = pmath_moreless360(Lambda);
	
	double Obliquity = 23.439 - 0.0000004 * D;
	double Alpha = pmath_rad2deg(atan((cos(pmath_deg2rad(Obliquity)) * tan(pmath_deg2rad(Lambda)))));
	Alpha = pmath_moreless360(Alpha);
	
	Alpha = Alpha - (360 * floor(Alpha / 360));
	Alpha = Alpha + 90 * (floor(Lambda / 90) - floor(Alpha / 90));
	
	double ST = 100.46 + 0.985647352 * D;
	double Dec = pmath_rad2deg(asin(sin(pmath_deg2rad(Obliquity)) * sin(pmath_deg2rad(Lambda))));

	double PreDurinal_Arc	= (sin(pmath_deg2rad(-0.8333)) - sin(pmath_deg2rad(Dec)) * sin(pmath_deg2rad(dLatitude)) / (cos(pmath_deg2rad(Dec)) * cos(pmath_deg2rad(dLatitude))));
	double Durinal_Arc		= pmath_rad2deg(acosc(PreDurinal_Arc));

	double Noon = Alpha - ST;
	Noon = pmath_moreless360(Noon);
	
	double UT_Noon = Noon - dLongitude;
	
	/*-----------------------------------------------------------------*/
	/*------------- Calculating Prayer Times Arcs & Times -------------*/
	/*-----------------------------------------------------------------*/
	
	/* 2) Zuhr Time [Local noon] */
	dZuhrTime = UT_Noon / 15 + bTimeZone;
	
	/* Asr Hanafi */
	/* double Asr_Alt = pmath_rad2deg(atan(2 + tan(pmath_deg2rad(fabs(dLatitude - Dec))))); */
	
	/* Asr Shafii */
	double Asr_Alt = pmath_rad2deg(atan(1 + tan(pmath_deg2rad(fabs(dLatitude - Dec)))));
	double Asr_Arc = pmath_rad2deg(acosc((sin(pmath_deg2rad(90 - Asr_Alt)) - sin(pmath_deg2rad(Dec)) * sin(pmath_deg2rad(dLatitude))) / (cos(pmath_deg2rad(Dec)) * cos(pmath_deg2rad(dLatitude)))));
	Asr_Arc = Asr_Arc / 15;
	
	/* 3) Asr Time */
	dAshrTime = dZuhrTime + Asr_Arc;
	
	/* 1) Shorouq Time */
	dRiseTime = dZuhrTime - (Durinal_Arc / 15);
	
	/* 4) Maghrib Time */
	dMagrTime = dZuhrTime + (Durinal_Arc / 15);
	
	double Esha_Arc = pmath_rad2deg(acosc((sin(pmath_deg2rad(dIshaTwilight)) - sin(pmath_deg2rad(Dec)) * sin(pmath_deg2rad(dLatitude))) / (cos(pmath_deg2rad(Dec)) * cos(pmath_deg2rad(dLatitude)))));
	/* 5) Isha Time */
	dIshaTime = dZuhrTime + (Esha_Arc / 15);
	
	/* 0) Fajr Time */
	double Fajr_Arc = pmath_rad2deg(acosc((sin(pmath_deg2rad(dFajrTwilight)) - sin(pmath_deg2rad(Dec)) * sin(pmath_deg2rad(dLatitude))) / (cos(pmath_deg2rad(Dec)) * cos(pmath_deg2rad(dLatitude)))));
	dFajrTime = dZuhrTime - (Fajr_Arc / 15);

	/* Get Prayer Time in Hour-minutes */
	pmath_get_time(dFajrTime, &pstTimes[ePTIME_FAJR]		); 
	pmath_get_time(dRiseTime, &pstTimes[ePTIME_SUNRISE]	);
	pmath_get_time(dZuhrTime, &pstTimes[ePTIME_ZUHR]		);
	pmath_get_time(dAshrTime, &pstTimes[ePTIME_ASHR]		);
	pmath_get_time(dMagrTime, &pstTimes[ePTIME_MAGHRIB]	);
	pmath_get_time(dIshaTime, &pstTimes[ePTIME_ISHA]		);

	/* Imsyak time (10 minutes before Fajr time) */
	pstTimes[ePTIME_IMSYAK] = pstTimes[ePTIME_FAJR];
	pmath_correct_time(&pstTimes[ePTIME_IMSYAK], -10);
}