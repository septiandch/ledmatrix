/**
 *  DMD Parameter Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _DMD_PRM_H_
#define _DMD_PRM_H_

#include "stm32f10x.h"

/* DEFINES */
#define DISPLAY_MAX_SIZE	(64 * 20)

/* ENUMERATIONS */
typedef enum
{
	mode_mono	= 1,
	mode_tri	= 2,
	mode_rgb	= 3
} eDisplayMode;

/* STRUCTURES*/
typedef struct
{
	eDisplayMode bMode;				/* Mono = 1 , Tri = 2, RGB = 3 */
	uint8_t bScanrate;				/* 4 = 1/4 , 8 = 1/8, 16 = 1/16 */
	uint8_t bWidth;					/* Pixel width per panel */
	uint8_t bHeight;				/* Pixel height per panel */
	uint8_t bPanelAcross;			/* Total panel across */
	uint8_t bPanelDown;				/* Total panel down */
} stDisplayParam;

/* VARIABLES */
extern stDisplayParam stDispParam;

/* FUNCTION PROTOTYPES */
extern void		dmd_prm_set_display(uint8_t mode, uint8_t scanrate, uint8_t width, uint8_t height, uint8_t panelAcross, uint8_t panelDown);
extern uint8_t	dmd_prm_get_rowsize();
extern uint16_t	dmd_prm_get_totalpanel();
extern uint16_t	dmd_prm_get_dispsize();

#endif	/* _DMD_PRM_H */