/**
 *  Led Matrix Display R/W Command Task
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _CMD_H_
#define _CMD_H_

#include "stm32f10x_conf.h"
#include "prog/ledmatrix.h"
#include "lib/usart.h"
#include "lib/rtc.h"
#include "lib/fmem.h"

/* #define USE_FMEM */

#ifndef ENABLE_EEPROM
# include "lib/at24cxx.h"
#endif

#define COMMAND_MAX_LEN		126
#define COMMAND_MAX_TASK	5

extern void	cmd_check(void);
extern void	cmd_write(void);
extern void	cmd_read(uint8_t task, char *str, uint8_t *mode, uint8_t *delay, uint8_t *iteration);

#endif /* _CMD_H_ */