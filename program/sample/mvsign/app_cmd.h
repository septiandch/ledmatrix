#include "app_main.h"
#include "stm32f10x_conf.h"
#include "peripherals/usart.h"
#include "peripherals/rtc.h"
#include "peripherals/fmem.h"

#ifndef _APP_CMD_H_
#define _APP_CMD_H_

/* #define USE_FMEM */

#ifndef USE_FMEM
# include "peripherals/at24cxx.h"
#endif

#define COMMAND_MAX_LEN		126
#define COMMAND_MAX_TASK	5

extern void	app_command_check(void);
extern void	app_command_write(void);
extern void	app_command_read(uint8_t task, char *str, uint8_t *mode, uint8_t *delay, uint8_t *iteration);

#endif /* _APP_CMD_H_ */