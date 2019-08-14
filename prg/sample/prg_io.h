/**
 *  Led Matrix Display Input/Output Configuration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _IO_H_
#define _IO_H_

#include "stm32f10x_conf.h"
#include "prog/ledmatrix_conf.h"
#include "brdtyp/brd_DMD19.h"

/* DEFINITIONS */
#define BUZZER_APBClockCmd			BRD_BUZZER_APBClockCmd
#define BUZZER_RCC					BRD_BUZZER_RCC
#define BUZZER_PORT					BRD_BUZZER_PORT
#define BUZZER_PIN					BRD_BUZZER_PIN
#define BUZZER_DELAY				250

#define SQW_APBClockCmd				BRD_SQW_APBClockCmd
#define SQW_RCC_EN					BRD_SQW_RCC_EN
#define SQW_PORT					BRD_SQW_PORT
#define SQW_PIN						BRD_SQW_PIN
#define SQW_EXTI_PIN				BRD_SQW_EXTI_PIN
#define SQW_EXTI_IRQn				BRD_SQW_EXTI_IRQn
#define SQW_EXTI_IRQHandler			BRD_SQW_EXTI_IRQHandler
#define SQW_EXTI_Line				BRD_SQW_EXTI_Line

/* FUNCTION PROTOTYPES */
extern void buzzer_init(void);
extern void io_int_init(void);

#endif /* _IO_H_ */