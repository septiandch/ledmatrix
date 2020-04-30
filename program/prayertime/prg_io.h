/**
 *  Input/Output Configuration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _PRG_IO_H_
#define _PRG_IO_H_

#include "stm32f10x_conf.h"
#include "program/prg_api.h"
#include PROG_CONF_H

/* DEFINITIONS */
#define BUZZER_APBClockCmd			BRD_BUZZER_APBClockCmd
#define BUZZER_RCC					BRD_BUZZER_RCC
#define BUZZER_PORT					BRD_BUZZER_PORT
#define BUZZER_PIN					BRD_BUZZER_PIN
#define BUZZER_DELAY				250

#define SQW_APBClockCmd				BRD_SQW_APBClockCmd
#define SQW_APBClockCmd_AFIO		BRD_SQW_APBClockCmd_AFIO
#define SQW_RCC						BRD_SQW_RCC
#define SQW_RCC_AFIO				BRD_SQW_RCC_AFIO
#define SQW_PORT					BRD_SQW_PORT
#define SQW_PORTSOURCE				BRD_SQW_PORTSOURCE
#define SQW_PIN						BRD_SQW_PIN
#define SQW_PINSOURCE				BRD_SQW_PINSOURCE
#define SQW_EXTI_IRQn				BRD_SQW_EXTI_IRQn
#define SQW_EXTI_IRQHandler			BRD_SQW_EXTI_IRQHandler
#define SQW_EXTI_Line				BRD_SQW_EXTI_Line

/* FUNCTION PROTOTYPES */
extern void io_buzzer_init(void);
extern void io_int_init(void *func);
extern void io_buzzer_pin(FlagStatus state);

#endif /* _PRG_IO_H_ */