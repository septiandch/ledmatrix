/**
 *  DMD Hardware Access Layer Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _DMD_HAL_H_
#define _DMD_HAL_H_

#include "dmd_prm.h"
#include "dmd_conf.h"
#include "lib/utils.h"

/* DISPLAY MACROS */
#define DMD_ENABLE_LO()				DMD_PORT_EN->BRR 	= DMD_PIN_EN
#define DMD_ENABLE_HI()				DMD_PORT_EN->BSRR	= DMD_PIN_EN
#define DMD_LATCH_LO()				DMD_PORT->BRR   	= DMD_PIN_LAT
#define DMD_LATCH_HI()				DMD_PORT->BSRR  	= DMD_PIN_LAT
#define DMD_CLOCK_LO()				DMD_PORT->BRR   	= DMD_PIN_CLK
#define DMD_CLOCK_HI()				DMD_PORT->BSRR  	= DMD_PIN_CLK
#define DMD_CLOCK()					DMD_CLOCK_HI(); DMD_CLOCK_LO();
#define DMD_LATCH()					DMD_ENABLE_LO(); DMD_LATCH_HI(); DMD_LATCH_LO(); DMD_ENABLE_HI();

/* GLOBAL VARIABLES */
extern uint8_t	dmd_bDisplayBuffer[];

/* FUNCTIONS */
extern void		dmd_init();
extern void		dmd_display_scan();
extern void		dmd_send_data(uint8_t _data);
extern void		dmd_send_data_rgb(uint16_t nBufferHi, uint16_t nBufferLo);
extern void     dmd_set_brightness(uint8_t percentage);

#endif	/* _DMD_HAL_H */




