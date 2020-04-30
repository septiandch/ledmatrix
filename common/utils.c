/**
 *  Utilities Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "utils.h"
#include <stdio.h>
#include <string.h>

uint8_t utils_int2str(uint16_t value, uint8_t padding, char *strout)
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

uint8_t utils_concat(char *str1, char *str2, char *str3, char *strout)
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

uint8_t utils_timestamp(uint16_t n1, uint16_t n2, uint16_t n3, char delimiter, char *strout)
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
		
		len = utils_int2str(data[i], 1, &strout[index]);
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

void utils_parse(char delimiter, char *strtarget, uint8_t *outputindex)
{
	int8_t	i		= 0;
	int8_t	index	= 0;
	
	while(strtarget[index] != '\0')
	{
		if(strtarget[index] == delimiter)
		{
			outputindex[i] = index + 1;
			i++;
		}

		index++;
	}
}

uint16_t utils_strlen(const char * str)
{
    uint16_t i = 0;

    while(str[i++] != '\0');

    return(i);
}