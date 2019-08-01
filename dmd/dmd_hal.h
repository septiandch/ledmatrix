/**
 *  DMD Hardware Access Layer Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _DMD_HAL_H_
#define _DMD_HAL_H_

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "platform_config.h"
#include "dmd_conf.h"

/* DISPLAY MACROS */
#define DMD_ENABLE_LO()				DMD_PIN_EN_PORT->BRR 	= DMD_PIN_EN
#define DMD_ENABLE_HI()				DMD_PIN_EN_PORT->BSRR	= DMD_PIN_EN
#define DMD_LATCH_LO()				DMD_PIN_PORT->BRR   	= DMD_PIN_LAT
#define DMD_LATCH_HI()				DMD_PIN_PORT->BSRR  	= DMD_PIN_LAT
#define DMD_CLOCK_LO()				DMD_PIN_PORT->BRR   	= DMD_PIN_CLK
#define DMD_CLOCK_HI()				DMD_PIN_PORT->BSRR  	= DMD_PIN_CLK
#define DMD_CLOCK()					DMD_CLOCK_HI(); DMD_CLOCK_LO();
#define DMD_LATCH()					DMD_ENABLE_LO(); DMD_LATCH_HI(); DMD_LATCH_LO(); DMD_ENABLE_HI();

/* DISPLAY MODE */
#define MODE_MONO					1
#define MODE_TRI					2
#define MODE_RGB					3

/* GLOBAL VARIABLES */
extern uint8_t	dmd_bDisplayBuffer[];

/* FUNCTIONS */
extern void		dmd_Init();
extern void		dmd_DisplayScan();
extern void		dmd_SendData(uint8_t _data);
extern void		dmd_SendData75(uint16_t nBufferHi, uint16_t nBufferLo);
extern void     dmd_SetBrightness(uint8_t percentage);

#endif	/* _DMD_HAL_H */




