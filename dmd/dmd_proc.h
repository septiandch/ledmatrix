/**
 *  DMD processing Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_hal.h"
#include "pgmspace.h"

#ifndef	_DMD_PROC_H_
#define	_DMD_PROC_H_

/** Font Indices */
#define	FONT_LENGTH             0
#define	FONT_FIXED_WIDTH        2
#define	FONT_HEIGHT             3
#define	FONT_FIRST_CHAR         4
#define	FONT_CHAR_COUNT         5
#define	FONT_WIDTH_TABLE        6

#ifdef	ENABLE_DMA
#	define MATRIX_SIZE			stDispParam.bPanelDown * stDispParam.bHeight * stDispParam.bMode
#endif

#ifdef ENABLE_DOUBLEBUFFER
#	define bDisplayBuffer		matrix_bDisplayBuffer
#else
#	define bDisplayBuffer		dmd_bDisplayBuffer
#endif

/** STRUCTURES */
typedef struct
{
	FunctionalState	active;
	int16_t			startX;
	int16_t			startY;
	int16_t			endX;
	int16_t			endY;
} stMatrixFrame;

/** ENUMERATIONS */
typedef enum
{
	SCROLL_LEFT_TO_RIGHT = 0,
	SCROLL_RIGHT_TO_LEFT,
	SCROLL_BOTTOM_TO_TOP,
	SCROLL_TOP_TO_BOTTOM
} eMARQUEEDIR;

typedef enum
{
	CL_BLACK = 0,
	CL_RED,
	CL_GREEN,
	CL_YELLOW,
	CL_BLUE,
	CL_PURPLE,
	CL_TURQUOISE,
	CL_WHITE
} eCOLOR;

/** VARIABLES */
extern int16_t		matrix_nMarqueeWidth;
extern int16_t		matrix_nMarqueePos;

/** FUNCTIONS */

extern void 		matrix_init(void);
	
extern void 		matrix_set_font(const uint8_t *font);
extern void			matrix_set_color(eCOLOR _color);
extern void			matrix_set_brightness(uint8_t percentage);

extern uint16_t		matrix_get_charwidth(const char letter);
extern uint16_t		matrix_get_textcenter(char *textSource);
	
extern void			matrix_invert_color(FunctionalState state);

extern void			matrix_set_frame(int16_t nPosX, int16_t nPosY, int16_t width, int16_t height);
extern void			matrix_clr_frame(void);
	
extern void 		matrix_set_screen(void);
extern void 		matrix_clr_screen(eCOLOR color);
	
extern void 		matrix_draw_point(int16_t pX, int16_t pY, eCOLOR color);
extern void 		matrix_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color);
	
extern uint16_t		matrix_draw_char(int16_t bX, int16_t bY, const char letter, eCOLOR color);
extern void			matrix_draw_string(int16_t nX, int16_t nY, char *bStr, eCOLOR color);
extern void			matrix_draw_box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color);
extern void			matrix_draw_filledbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color);
extern void			matrix_draw_image(uint16_t posX, uint16_t posY, uint8_t *data);

extern uint16_t		matrix_get_marqueepos(void);
extern void			matrix_clr_marqueepos(void);
extern void			matrix_marquee_pause(FunctionalState state);
extern uint8_t		matrix_draw_marquee(int16_t nPosX, int16_t nPosY, int16_t width, int16_t height, char *bStr, eMARQUEEDIR direction, eCOLOR color);

#endif	/** _DMD_PROC_H_ */
