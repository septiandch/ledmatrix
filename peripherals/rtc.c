/**
 *  RTC Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.date.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#include "pgmspace.h"

#include "i2c.h"
#include "rtc.h"

uint8_t bDaysinmonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; 

void rtc_Init(uint8_t sqw_mode)
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

uint16_t rtc_getDaysCount(uint8_t month)
{	
	return bDaysinmonth[month];
}

uint8_t rtc_getDayOfWeek(uint8_t year, uint8_t month, uint8_t date) 
{
	uint16_t	adjustment	= 0;
	uint16_t	mm			= 0;
	uint16_t	yy			= 0;
 
	adjustment = (14 - month) / 12;
	mm = month + 12 * adjustment - 2;
	yy = year - adjustment;
	
	return ((date + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7) + 1;
}

void rtc_setTime(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t min, uint8_t sec)
{
	uint8_t	dayofweek	= 0;
	
	/* Check if the year is a Leap Year */
	if((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
	{
		bDaysinmonth[1] = 29;
	}
	
	dayofweek = rtc_getDayOfWeek(year, month, date);
	
	i2c_start();
	i2c_direction(RTC_ADDR << 1, I2C_Direction_Transmitter);
	
	i2c_transmit(0x00);
	i2c_transmit(rtc_dec2bcd(sec));
	i2c_transmit(rtc_dec2bcd(min));
	i2c_transmit(rtc_dec2bcd(hour));
	i2c_transmit(rtc_dec2bcd(dayofweek));	
	i2c_transmit(rtc_dec2bcd(date));
	i2c_transmit(rtc_dec2bcd(month));
	i2c_transmit(rtc_dec2bcd(year));
	i2c_transmit(0x00);
	
	i2c_stop();
}

void rtc_readTime(uint8_t *year, uint8_t *month, uint8_t *date, uint8_t *day, uint8_t *hour, uint8_t *min, uint8_t *sec)
{	
	i2c_start();
	i2c_direction(RTC_ADDR << 1, I2C_Direction_Transmitter);
	i2c_transmit(0x00);
	i2c_stop();
	
	i2c_start();
    i2c_direction(RTC_ADDR << 1, I2C_Direction_Receiver);
	*sec	= rtc_bcd2dec(i2c_read_ack());
	*min	= rtc_bcd2dec(i2c_read_ack());
	*hour	= rtc_bcd2dec(i2c_read_ack());
	*day	= rtc_bcd2dec(i2c_read_ack());
	*date	= rtc_bcd2dec(i2c_read_ack());
	*month	= rtc_bcd2dec(i2c_read_ack());
	*year	= rtc_bcd2dec(i2c_read_nack());
	i2c_stop();
	
	/* Check if the year is a Leap Year */
	if((*year % 400 == 0) || (*year % 4 == 0 && *year % 100 != 0))
	{
		bDaysinmonth[1] = 29;
	}
}
