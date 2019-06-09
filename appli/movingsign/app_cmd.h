
#include "stm32f10x_conf.h"
#include "peripherals/usart.h"
#include "peripherals/fmem.h"

#ifndef _APP_CMD_H_
#define _APP_CMD_H_

#define COMMAND_MAX_LEN		156
#define COMMAND_MAX_TASK	5

extern void	app_command_check(void);
extern void	app_command_write(void);
extern void	app_command_read(uint8_t task, char *str, uint8_t *mode, uint8_t *delay, uint8_t *iteration);

#endif /* _APP_CMD_H_ */