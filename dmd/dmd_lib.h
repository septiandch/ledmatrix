/**
 *  DMD processing Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include <stdio.h>
#include <string.h>
#include "dmd_hal.h"
#include "utils.h"
#include "pgmspace.h"

#ifndef	_DMD_LIB_H_
#define	_DMD_LIB_H_

#define ENABLE_DOUBLEBUFFER

/** Font Indices */
#define	FONT_LENGTH             0
#define	FONT_FIXED_WIDTH        2
#define	FONT_HEIGHT             3
#define	FONT_FIRST_CHAR         4
#define	FONT_CHAR_COUNT         5
#define	FONT_WIDTH_TABLE        6

#ifdef	ENABLE_DMA
#	define MATRIX_SIZE				DISPLAY_DOWN * DISPLAY_HEIGHT * DISPLAY_MODE
#endif

#ifdef ENABLE_DOUBLEBUFFER
#	define bDisplayBuffer	matrix_bDisplayBuffer
#else
#	define bDisplayBuffer	dmd_bDisplayBuffer
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
	BLACK = 0,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	TURQUOISE,
	WHITE
} eCOLOR;

/** VARIABLES */
extern int16_t		matrix_nMarqueeWidth;
extern int16_t		matrix_nMarqueePos;

/** FUNCTIONS */

extern void 		matrix_Init(void);
	
extern void 		matrix_SetFont(const uint8_t *font);
extern void			matrix_SetColor(eCOLOR _color);
extern void			matrix_SetBrightness(uint8_t percentage);

extern uint16_t		matrix_GetCharWidth(const char letter);
extern uint16_t		matrix_GetTextCenter(char *textSource);
	
extern void			matrix_invert_color(FunctionalState state);

extern void			matrix_FrameCreate(int16_t nPosX, int16_t nPosY, int16_t width, int16_t height);
extern void			matrix_FrameClear(void);
	
extern void 		matrix_ScreenApply(void);
extern void 		matrix_ScreenClear(eCOLOR color);
	
extern void 		matrix_DrawPoint(int16_t pX, int16_t pY, eCOLOR color);
extern void 		matrix_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color);
	
extern uint16_t		matrix_DrawChar(int16_t bX, int16_t bY, const char letter, eCOLOR color);
extern void			matrix_DrawString(int16_t nX, int16_t nY, char *bStr, eCOLOR color);
extern void			matrix_DrawBox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color);
extern void			matrix_DrawFilledBox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color);
extern void			matrtix_DrawImage(uint16_t posX, uint16_t posY, uint8_t *data);

extern uint16_t		matrix_GetMarqueePos(void);
extern void			matrix_ResetMarqueePos(void);
extern void			matrix_PauseMarquee(FunctionalState state);
extern uint8_t		matrix_DrawMarquee(int16_t nPosX, int16_t nPosY, int16_t width, int16_t height, char *bStr, eMARQUEEDIR direction, eCOLOR color);


unsigned int 		matrix_TextCenter(char *textSource);
extern int			matrix_ScrollText(const char *text, int delay);

#endif	/** _DMD_LIB_H_ */
