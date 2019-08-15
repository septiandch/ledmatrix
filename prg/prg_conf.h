/**
 *  Ledmatrix Program Configuration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _PRG_CONF_H_
#define _PRG_CONF_H_

/* BOARD SELECT */
#include "brd/brd_DMD19.h"

/*----- Buffer Option -----*/
#define ENABLE_DOUBLEBUFFER

/*----- HUB Type -----*/
/* #define DMD_HUB75 */
#define DMD_HUB12

/*-----  Peripherals Configuration ----- */
#define ENABLE_PWM
#define ENABLE_TIM
/* #define ENABLE_SPI */
/* #define ENABLE_DMA */

#endif	/* _PRG_CONF_H_ */