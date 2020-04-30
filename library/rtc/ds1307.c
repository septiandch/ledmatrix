/**
 *  RTC DS1307 Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.date.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "ds1307.h"

uint8_t bDaysinmonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; 

void rtc_init(uint8_t sqw_mode)
{
	i2c_init();
	rtc_write(RTC_ADDR, 0x07, sqw_mode);
}

uint8_t rtc_dec2bcd(uint8_t val) 
{
	return val + 6 * (val / 10);
}
 
uint8_t rtc_bcd2dec(uint8_t val) 
{
	return val - 6 * (val >> 4);
}

void rtc_write(uint8_t address, uint8_t reg, uint8_t data)
{	
	i2c_start();
	i2c_direction(address << 1, I2C_Direction_Transmitter);
	i2c_transmit(reg);
	i2c_transmit(data);
	i2c_stop();
}

void rtc_read(uint8_t address, uint8_t reg, uint8_t *data)
{	
	i2c_start();
	i2c_direction(address << 1, I2C_Direction_Transmitter);
	i2c_transmit(reg);
	i2c_stop();
	
	i2c_start();
	i2c_direction(address << 1, I2C_Direction_Receiver);
	*data = i2c_read_nack();
	i2c_stop();
}

uint16_t rtc_hour2min(uint8_t hour)
{
	return hour * 60;
}

uint16_t rtc_get_daycount(uint8_t month)
{	
	return bDaysinmonth[month];
}

uint8_t rtc_get_dayofweek(uint8_t year, uint8_t month, uint8_t date)
{
	uint16_t	adjustment	= 0;
	uint16_t	mm			= 0;
	uint16_t	yy			= 0;
 
	adjustment = (14 - month) / 12;
	mm = month + 12 * adjustment - 2;
	yy = year - adjustment;
	
	return ((date + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7) + 1;
}

void rtc_set_time(stRealTimeVar *stRTime)
{
	uint8_t	dayofweek	= 0;
	
	/* Check if the year is a Leap Year */
	if((stRTime->year % 400 == 0) || (stRTime->year % 4 == 0 && stRTime->year % 100 != 0))
	{
		bDaysinmonth[1] = 29;
	}
	
	dayofweek = rtc_get_dayofweek(stRTime->year, stRTime->month, stRTime->date);
	
	i2c_start();
	i2c_direction(RTC_ADDR << 1, I2C_Direction_Transmitter);
	
	i2c_transmit(0x00);
	i2c_transmit(rtc_dec2bcd(stRTime->second));
	i2c_transmit(rtc_dec2bcd(stRTime->minute));
	i2c_transmit(rtc_dec2bcd(stRTime->hour));
	i2c_transmit(rtc_dec2bcd(dayofweek));
	i2c_transmit(rtc_dec2bcd(stRTime->date));
	i2c_transmit(rtc_dec2bcd(stRTime->month));
	i2c_transmit(rtc_dec2bcd(stRTime->year));
	i2c_transmit(0x00);
	
	i2c_stop();
}

void rtc_get_time(stRealTimeVar *stRTime)
{	
	i2c_start();
	i2c_direction(RTC_ADDR << 1, I2C_Direction_Transmitter);
	i2c_transmit(0x00);
	i2c_stop();
	
	i2c_start();
    i2c_direction(RTC_ADDR << 1, I2C_Direction_Receiver);
	stRTime->second	= rtc_bcd2dec(i2c_read_ack());
	stRTime->minute	= rtc_bcd2dec(i2c_read_ack());
	stRTime->hour	= rtc_bcd2dec(i2c_read_ack());
	stRTime->day	= rtc_bcd2dec(i2c_read_ack());
	stRTime->date	= rtc_bcd2dec(i2c_read_ack());
	stRTime->month	= rtc_bcd2dec(i2c_read_ack());
	stRTime->year	= rtc_bcd2dec(i2c_read_nack());
	i2c_stop();
	
	/* Check if the year is a Leap Year */
	if((stRTime->year % 400 == 0) || (stRTime->year % 4 == 0 && stRTime->year % 100 != 0))
	{
		bDaysinmonth[1] = 29;
	}
}
