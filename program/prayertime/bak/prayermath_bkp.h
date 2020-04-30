/*
 *  Prayer Math Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PRAYERMATH_H_
#define _PRAYERMATH_H_

#include <math.h>
#include "stm32f10x.h"
#include "../common/pgmspace.h"

extern double	pmath_radians(double degree);
extern double	pmath_degrees(double radian);
extern double	pmath_moreless360(double value);
extern double	pmath_moreless24(double value);
extern void		pmath_doubleToHrMin(double number, uint8_t *hours, uint8_t *minutes);
extern void		pmath_get_prayertimes(int year, int month, int day, double longitude, double latitude, int timeZone,
									  double fajrTwilight, double ishaTwilight, double *fajrTime, double *sunRiseTime, 
									  double *zuhrTime, double *asrTime, double *maghribTime, double *ishaTime);

#endif /* _PRAYERMATH_H_ */
