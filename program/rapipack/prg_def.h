/**
 *  Program Definitions
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#ifndef _PRG_DEF_H_
#define _PRG_DEF_H_

#include "common/pgmspace.h"

#include "../prg_conf.h"
#include BOARD_DEF_H

/*----- Buffer Option -----*/
/* #define ENABLE_DOUBLEBUFFER */

/*----- HUB Type -----*/
#define DMD_HUB75_SUPPORT
/* #define DMD_HUB12_SUPPORT */

/*----- Display Configuration -----*/
#define DISPLAY_COUNT_ACCROSS   2   
#define DISPLAY_COUNT_DOWN      2
#define DISPLAY_COLOR_MODE      3   /* 1: Mono, 2: Tri-Color, 3: RGB */
#define DISPLAY_HEIGHT          16
#define DISPLAY_WIDTH           32
#define DISPLAY_SCAN_RATE       4   /* 4: 1/4scan, 8: 1/8scan, 16: 1/16scan */

/*-----  Peripherals Configuration ----- */
#define ENABLE_PWM
/*#define ENABLE_TIM */
/* #define ENABLE_SPI */
/* #define ENABLE_DMA */

/*----- Memory Mapping -----*/
#define MEM_BASE					0x0EA0
#define MEM_PWRSAVE_HOUR			(uint16_t)	(MEM_BASE + 0x00)
#define MEM_PWRSAVE_MINUTE			(uint16_t)	(MEM_BASE + 0x01)
#define MEM_PWRSAVE_DURATION		(uint16_t)	(MEM_BASE + 0x02)
#define MEM_BRIGHTNESS				(uint16_t)	(MEM_BASE + 0x04)

/*----- Input-Output Definition -----*/
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

#endif /* _PRG_DEF_H_ */
