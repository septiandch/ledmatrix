/**
 *  Utilities Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "delay.h"

void delay_ms(uint16_t millis)
{
    while (millis-- > 0)
    {
        volatile int16_t x = 5971;
        while (x-- > 0) 
        {
            __asm("nop");
        }
    }
}