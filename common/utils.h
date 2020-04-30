/**
 *  Utilities Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <string.h>

#define NONE	255

extern uint16_t utils_strlen(const char * str);
extern uint8_t	utils_int2str(uint16_t value, uint8_t padding, char *strout);
extern uint8_t	utils_timestamp(uint16_t n1, uint16_t n2, uint16_t n3, char delimiter, char *strout);
extern uint8_t	utils_concat(char *str1, char *str2, char *str3, char *strout);
extern void		utils_parse(char delimiter, char *strtarget, uint8_t *outputindex);

#endif /* _UTILS_H_ */
