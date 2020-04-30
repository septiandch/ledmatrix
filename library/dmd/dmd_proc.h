/**
 *  DMD PROCESSING Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_conf.h"
#include "dmd_hal.h"
#include "common/pgmspace.h"

#ifndef	_DMD_PROC_H_
#define	_DMD_PROC_H_

/*----- Defines -----*/
#define	FONT_LENGTH             0
#define	FONT_FIXED_WIDTH        2
#define	FONT_HEIGHT             3
#define	FONT_FIRST_CHAR         4
#define	FONT_CHAR_COUNT         5
#define	FONT_WIDTH_TABLE        6

#ifdef	ENABLE_DMA
#	define dmdproc_SIZE			stDispProp.bPanelDown * stDispProp.bHeight * stDispProp.bMode
#endif

#ifdef ENABLE_DOUBLEBUFFER
#	define bDisplayBuffer		pbScreenBuffer
#else
#	define bDisplayBuffer		pbDmdBuffer
#endif


/*----- Enumerations -----*/
typedef enum
{
	eCL_BLACK,
	eCL_RED,
	eCL_GREEN,
	eCL_YELLOW,
	eCL_BLUE,
	eCL_PURPLE,
	eCL_TURQUOISE,
	eCL_WHITE
} eColor;


/*----- Structures -----*/
typedef struct
{
	eState		eActive;
	int16_t		wStartX;
	int16_t		wStartY;
	int16_t		wEndX;
	int16_t		wEndY;
} stDisplayFrame;


/*----- Variables -----*/


/*----- Function Prototypes -----*/
extern void 	dmdproc_init();
	
extern void 	dmdproc_set_font(const uint8_t *font);
extern void		dmdproc_set_color(eColor _color);
extern void		dmdproc_set_brightness(uint8_t percentage);

extern uint16_t	dmdproc_get_charwidth(const char letter);
extern uint16_t dmdproc_get_charheight(void);
extern uint16_t	dmdproc_get_textwidth(char *textSource);
	
extern void		dmdproc_invert_color(eState state);

extern void		dmdproc_set_frame(int16_t nPosStX, int16_t nPosStY, int16_t nPosEnX, int16_t nPosEnY);
extern void		dmdproc_clr_frame(void);
	
extern void 	dmdproc_set_screen(void);
extern void 	dmdproc_clr_screen(void);
	
extern void 	dmdproc_draw_point(int16_t pX, int16_t pY, eColor color);
extern void 	dmdproc_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eColor color);
	
extern uint16_t	dmdproc_draw_char(int16_t bX, int16_t bY, const char letter, eColor color);
extern void		dmdproc_draw_string(int16_t nX, int16_t nY, char *bStr, eColor color);
extern void		dmdproc_draw_box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eColor color);
extern void		dmdproc_draw_filledbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eColor color);
extern void		dmdproc_draw_image(uint16_t posX, uint16_t posY, uint8_t *data, eColor color);

#endif	/* _DMD_API_H_ */