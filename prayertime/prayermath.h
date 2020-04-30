/*
 *  Prayer Math Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PRAYERMATH_H_
#define _PRAYERMATH_H_

#include <math.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "../pgmspace.h"

#define RAD_TO_DEG(x)	(x*(180/3.1415926))

extern float	pmath_degToRad(float degree);
extern float	pmath_radToDeg(float radian);
extern double	pmath_moreLess360(double value);
extern uint8_t 	pmath_moreLess24(int32_t value);
extern void		pmath_GetHourMin(int32_t number, uint8_t *hours, uint8_t *minutes);
extern void		pmath_calcPrayerTimes(	int8_t year, int8_t month, int8_t day,
										int32_t *fajrTime, int32_t *sunRiseTime, int32_t *zuhrTime,
										int32_t *asrTime, int32_t *maghribTime, int32_t *ishaTime);

#endif /* _PRAYERMATH_H_ */
