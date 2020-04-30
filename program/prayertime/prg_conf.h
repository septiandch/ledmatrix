/**
 *  Program Hardware Configuration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _PRG_CONF_H_
#define _PRG_CONF_H_

/* BOARD SELECT */
#include "board/brd_DMD19.h"

/*----- Buffer Option -----*/
/* #define ENABLE_DOUBLEBUFFER */

/*----- Maximum Display Size -----*/
#define DISPLAY_DATA_SIZE	(64 * 3 * 4)

/*----- HUB Type -----*/
#define DMD_HUB75_SUPPORT
/* #define DMD_HUB12_SUPPORT */

/*-----  Peripherals Configuration ----- */
/* #define ENABLE_BCM */
#define ENABLE_PWM
/*#define ENABLE_TIM */
/* #define ENABLE_SPI */
/* #define ENABLE_DMA */

#endif	/* _PRG_CONF_H_ */
