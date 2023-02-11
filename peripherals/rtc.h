/**
 *  RTC Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#include "pgmspace.h"

#ifndef _RTC_H_
#define _RTC_H_

#define SQW_1HZ			0x10
#define SQW_4HZ			0x11
#define SQW_8HZ			0x12
#define SQW_32HZ		0x13
#define SQW_OFF_HIGH	0x80
#define SQW_OFF_LOW		0x00

#define RTC_ADDR		0x68

extern void		rtc_Init(uint8_t sqw_mode);
extern void		rtc_write(uint8_t address, uint8_t reg, uint8_t data);
extern void		rtc_read(uint8_t address, uint8_t reg, uint8_t *data);
extern void		rtc_setTime(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t min, uint8_t sec);
extern void		rtc_readTime(uint8_t *year, uint8_t *month, uint8_t *date, uint8_t *day, uint8_t *hour, uint8_t *min, uint8_t *sec);
extern uint8_t	rtc_dec2bcd(uint8_t val);
extern uint8_t	rtc_bcd2dec(uint8_t val);
extern uint8_t	rtc_getDayOfWeek(uint8_t year, uint8_t month, uint8_t date);
extern uint16_t	rtc_hour2min(uint8_t hour);
extern uint16_t	rtc_getDaysCount(uint8_t month);

#endif /** _RTC_H_ */
