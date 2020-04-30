/**
 *  DMD Hardware Access Layer Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _DMD_HAL_H_
#define _DMD_HAL_H_

#include "stm32f10x.h"
#include "dmd_conf.h"

/* DISPLAY MACROS */
#define DMD_ENABLE_LO()			DMD_PORT_EN->BRR 	= DMD_PIN_EN
#define DMD_ENABLE_HI()			DMD_PORT_EN->BSRR	= DMD_PIN_EN
#define DMD_LATCH_LO()			DMD_PORT->BRR   	= DMD_PIN_LAT
#define DMD_LATCH_HI()			DMD_PORT->BSRR  	= DMD_PIN_LAT
#define DMD_CLOCK_LO()			DMD_PORT->BRR   	= DMD_PIN_CLK
#define DMD_CLOCK_HI()			DMD_PORT->BSRR  	= DMD_PIN_CLK
#define DMD_CLOCK()				DMD_CLOCK_HI(); DMD_CLOCK_LO();
#define DMD_LATCH()				DMD_ENABLE_HI(); DMD_LATCH_HI(); DMD_LATCH_LO(); DMD_ENABLE_LO();

/* ENUMERATIONS */
typedef enum
{
	mode_mono	= 1,
	mode_tri	= 2,
	mode_rgb	= 3
} eDisplayMode;

/* STRUCTURES */
typedef struct
{
	eDisplayMode	bMode;					/* Mono = 1 , Tri = 2, RGB = 3 */
	uint8_t			bScanrate;				/* 4 = 1/4 , 8 = 1/8, 16 = 1/16 */
	uint8_t			bWidth;					/* Pixel width per panel */
	uint8_t			bHeight;				/* Pixel height per panel */
	uint8_t			bPanelAcross;			/* Total panel across */
	uint8_t			bPanelDown;				/* Total panel down */
	uint8_t			bPanelCount;			/* Total panel */
	uint8_t			nRowSize;				/* Row size in bytes */
} stDisplayProp;

/* GLOBAL VARIABLES */
extern uint8_t			pbDmdBuffer[];
extern stDisplayProp	stDispProp;

/* FUNCTIONS */
extern void		dmdhal_init(uint8_t mode, uint8_t scanrate, uint8_t width, uint8_t height, uint8_t panelAcross, uint8_t panelDown);
extern void     dmdhal_set_brightness(uint8_t percentage);

#endif	/* _DMD_HAL_H */




