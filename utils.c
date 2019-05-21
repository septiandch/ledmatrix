/**
 *  Utilities Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "utils.h"
#include <stdio.h>
#include <string.h>

void utils_Delay(uint16_t millis)
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

uint8_t utils_IntToString(uint16_t value, uint8_t padding, char *strout)
{
	uint16_t	npad	= 1;
	uint16_t	num		= 10000;
	uint8_t		index	= 0;
	
	if(value > 0)
	{
		while(padding--)
		{
			npad *= 10;
		}
	
		do
		{
			if(value >= num)
			{
				strout[index] = (uint8_t) ( (value / num) % 10) + '0';
				index++;
			}
			else if(num <= npad)
			{
				strout[index] = '0';
				index++;
			}
			
			num = (uint16_t) num / 10;
		}
		while(num > 0);
		
		strout[index] = '\0';
	}
	else
	{
		/** In case if the value is zero */
		for(index = 0; index <= padding; index++)
		{
			strout[index] = '0';
		}
		
		strout[index] = '\0';
	}
	
	return index;
}

uint8_t utils_Concat(char *str1, char *str2, char *str3, char *strout)
{
	uint8_t	i			= 0;
	uint8_t	j			= 0;
	uint8_t	index		= 0;
	uint8_t	len[3]		= {strlen(str1), strlen(str2), strlen(str3)};
	
	for(i = 0; i < 3; i++)
	{
		j = 0;
		
		while(j < len[i])
		{
			switch(i)
			{
				case 0: strout[index] = str1[j]; break;
				case 1: strout[index] = str2[j]; break;
				case 2: strout[index] = str3[j]; break;
			}
			
			index++;
			j++;
		}
	}
	
	strout[index] = '\0';
	return index;
}

uint8_t utils_Timestamp(uint16_t n1, uint16_t n2, uint16_t n3, char delimiter, char *strout)
{
	uint8_t	i		= 0;
	uint8_t	index	= 0;
	uint8_t	len		= 0;
	uint16_t	data[3]	= {n1, n2, n3};
	
	for(i = 0; i < 3; i++)
	{
		if(data[i] == NONE) 
		{
			index--;
			break;
		}
		
		len = utils_IntToString(data[i], 1, &strout[index]);
		index += len;
		
		if(i < 2)
		{
			strout[index] = delimiter;
			index++;
		}
	}
	
	strout[index] = '\0';
	
	return index;
}

void utils_StringParse(char *str, uint8_t *index)
{
	uint8_t	i = 0;
			
	do
	{
		if(str[i] == ',')
		{
			index[i] = i + 1;
			i++;
		}
	}
	while(str[i - 1] != '\0');
}
