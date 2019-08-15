/**
 *  DMD processing Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_proc.h"

/* FUNCTION PROTOTYPES */
uint16_t matrix_pixelmapping(int16_t nX, int16_t nY);
void matrix_set_pixelmap(void);

/* Initialize Global Variables */
const uint8_t		*FONT					;
stMatrixFrame		matrix_stDisplayFrame	;
FunctionalState		matrix_bInvertEn		= DISABLE;
int16_t				matrix_nMarqueeWidth	= 0;
int16_t				matrix_nMarqueePos		= 0;
uint8_t				matrix_bMarqueePause	= 0;

#ifdef ENABLE_DMA
static uint16_t		matrix_nPixelMap[MATRIX_SIZE];
#endif

#ifdef ENABLE_DOUBLEBUFFER
uint8_t				matrix_bDisplayBuffer[DISPLAY_MAX_SIZE];
#endif

void matrix_init(void)
{
	/* Initialize Display */
	dmd_prm_set_display(1, 4, 32, 16, 1, 1);

    matrix_clr_screen(CL_BLACK);
    matrix_set_pixelmap();

	matrix_set_screen();

	dmd_init();
}

void matrix_set_font(const uint8_t *font)
{
	FONT = font;
}

void matrix_clr_screen(eCOLOR color)
{
	/* Initialize Local Variables */
	uint16_t 	i 	= 0	;
	
	for(i = 0; i < stDispParam.nDispsize * stDispParam.bMode; i++)
	{
		bDisplayBuffer[i] = color;
	}
	
	/* matrix_nMarqueeWidth = 0; */
	/* matrix_nMarqueePos = 0; */
}

void matrix_set_screen(void)
{
#ifdef ENABLE_DOUBLEBUFFER
	memcpy(dmd_bDisplayBuffer, matrix_bDisplayBuffer, stDispParam.nDispsize * stDispParam.bMode);
#endif
}

void matrix_invert_color(FunctionalState state)
{
	matrix_bInvertEn = state;
}

void matrix_set_frame(int16_t nPosX, int16_t nPosY, int16_t width, int16_t height)
{
	matrix_stDisplayFrame.active = ENABLE;
	matrix_stDisplayFrame.startX = nPosX;
	matrix_stDisplayFrame.startY = nPosY;
	matrix_stDisplayFrame.endX   = nPosX + width;
	matrix_stDisplayFrame.endY   = nPosY + height;
}

void matrix_clr_frame(void)
{
	matrix_stDisplayFrame.active = DISABLE;
	matrix_stDisplayFrame.startX = 0;
	matrix_stDisplayFrame.startY = 0;
	matrix_stDisplayFrame.endX   = 0;
	matrix_stDisplayFrame.endY   = 0;
}

void matrix_set_pixelmap(void)
{
#ifdef ENABLE_DMA
	/* Initialize Local Variables */
	int8_t	x		= 0;
	uint8_t	n		= 0;
	uint8_t	index	= 0;
	
	while(x < stDispParam.bScanrate)
	{
		x++;
		
		for(n = 0; n < stDispParam.bScanrate; n++)
		{
			matrix_nPixelMap[index] = (stDispParam.bScanrate - x) + (n * stDispParam.bPanelAcross * stDispParam.bHeight);
			
			index++;
		}
	}
#endif
}

uint16_t matrix_pixelmapping(int16_t nX, int16_t nY)
{
	/* Initialize Local Variables */
	uint16_t	bytePos		= 0	;

#ifdef ENABLE_DMA
	bytePos = ((uint16_t) (nX / BYTE_SIZE) * stDispParam.bScanrate) + matrix_nPixelMap[nY];
#else
	bytePos =	((nY % stDispParam.bHeight) * (stDispParam.bWidth / 8) * stDispParam.bPanelCount * stDispParam.bMode) + ((nX / 8) * stDispParam.bMode)
				+ (((nY / stDispParam.bHeight) * stDispParam.bPanelAcross * (stDispParam.bWidth / 8)) * stDispParam.bMode);
#endif
	
	return bytePos;
}

void matrix_draw_point(int16_t nX, int16_t nY, eCOLOR color)
{
	/* Initialize Local Variables */
	int16_t		bytePos		= 0	;
	int16_t		bitPos		= 0	;
	
	if (nX >= stDispParam.bPanelAcross * stDispParam.bWidth || nY >= stDispParam.bPanelDown * stDispParam.bHeight) return;
	else if (nX < 0 || nY < 0) return;
	
	if(matrix_stDisplayFrame.active == ENABLE)
	{
		if (nX >= matrix_stDisplayFrame.endX || nY >= matrix_stDisplayFrame.endY) return;
		else if (nX < matrix_stDisplayFrame.startX || nY < matrix_stDisplayFrame.startY) return;
	}

	/* get byte position */
	bytePos = matrix_pixelmapping(nX, nY);
	bitPos = nX % 8;

	if(stDispParam.bMode == mode_rgb)
	{
		if(color & CL_RED) dmd_bDisplayBuffer[bytePos + 0] |= (1 << bitPos);
		else dmd_bDisplayBuffer[bytePos + 0] &= ~(1 << bitPos);
		
		if(color & CL_GREEN) dmd_bDisplayBuffer[bytePos + 1] |= (1 << bitPos);
		else dmd_bDisplayBuffer[bytePos + 1] &= ~(1 << bitPos);
		
		if(color & CL_BLUE) dmd_bDisplayBuffer[bytePos + 2] |= (1 << bitPos);
		else dmd_bDisplayBuffer[bytePos + 2] &= ~(1 << bitPos);
	}
	else
	{
		if(color != CL_BLACK)
		{
			bDisplayBuffer[bytePos] |= (1 << bitPos);
		}
		else
		{
			bDisplayBuffer[bytePos] &= ~(1 << bitPos);
		}
	}
}

void matrix_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color)
{
	/* Initialize Local Variables */
	int16_t	dy			= y2 - y1;
	int16_t	dx			= x2 - x1;
	int16_t	stepx		= 0;
	int16_t	stepy		= 0;
	int16_t fraction	= 0;
	
	if (dy < 0) 
	{
		dy = -dy;
		stepy = -1;
	} 
	else 
	{
		stepy = 1;
	}
	
	if (dx < 0) 
	{
		dx = -dx;
		stepx = -1;
	} 
	else 
	{
		stepx = 1;
	}
	dy <<= 1;     /* dy is now 2*dy */
	dx <<= 1;     /* dx is now 2*dx */
	
	matrix_draw_point(x1, y1, color);
	
	if (dx > dy) 
	{
		fraction = dy - (dx >> 1);  /* same as 2*dy - dx */
		while (x1 != x2) 
		{
			if (fraction >= 0) 
			{
			y1 += stepy;
			fraction -= dx; /* same as fraction -= 2*dx */
			}
			
			x1 += stepx;
			fraction += dy; /* same as fraction -= 2*dy */
			matrix_draw_point(x1, y1, color);
		}
	} 
	else
	{
		fraction = dx - (dy >> 1);
		while (y1 != y2) 
		{
			if (fraction >= 0) 
			{
			x1 += stepx;
			fraction -= dy;
			}
			
			y1 += stepy;
			fraction += dx;
			matrix_draw_point(x1, y1, color);
		}
	}
}

void matrix_draw_box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color)
{	
	matrix_draw_line(x1, y1, x2, y1, color);
	matrix_draw_line(x1, y1, x1, y2, color);
	matrix_draw_line(x1, y2, x2, y2, color);
	matrix_draw_line(x2, y1, x2, y2, color);
}

void matrix_draw_filledbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color)
{
	/* Initialize Local Variables */
	uint16_t	b = 0;
	
	for (b = x1; b <= x2; b++) 
    {
      matrix_draw_line(b, y1, b, y2, color);
    }
}

uint16_t matrix_get_charwidth(const char letter)
{
	/* Initialize Local Variables */
	char		c			=	letter;
	char		firstChar	=	pgm_read_byte(FONT + FONT_FIRST_CHAR);
	char		charCount	=	pgm_read_byte(FONT + FONT_CHAR_COUNT);
	int16_t		width		=	0;
	
	/* Space is often not included in font so use width of 'n' */
	if (c == ' ') c = ':';
	
	if (c < firstChar || c >= (firstChar + charCount)) 
	{
		return 0;
	}
	c -= firstChar;
	
	if (pgm_read_byte(FONT + FONT_LENGTH) == 0 && pgm_read_byte(FONT + FONT_LENGTH + 1) == 0) 
	{
		/* zero length is flag indicating fixed width font (array does not contain width data entries) */
		width = pgm_read_byte(FONT + FONT_FIXED_WIDTH);
	} 
	else 
	{
		/* variable width font, read width data */
		width = pgm_read_byte(FONT + FONT_WIDTH_TABLE + c);
	}
	return width;
}

uint16_t matrix_draw_char(int16_t nX, int16_t nY, const char letter, eCOLOR color)
{
	/* Initialize local variables */
	unsigned char	c			= letter;
	unsigned int	i			= 0;
	unsigned int	j			= 0;
	unsigned int	k			= 0;
	unsigned char	height		= pgm_read_byte(FONT + FONT_HEIGHT);
	eCOLOR			eFgColor	= (matrix_bInvertEn == ENABLE) ? CL_BLACK : color;
	eCOLOR			eBgColor	= (matrix_bInvertEn == ENABLE) ? color : CL_BLACK;
	
	if (nX >= (stDispParam.bWidth * stDispParam.bPanelAcross) || nY >= (stDispParam.bHeight * stDispParam.bPanelDown) ) return -1;
	
	if (c == ' ') 
	{
		unsigned char charWide = matrix_get_charwidth(':');
		matrix_draw_filledbox(nX, nY, nX + charWide, nY + height - 1, eBgColor);
		return charWide;
	}
	
	unsigned char width = 0;
	unsigned int bytes = (height + 7) / 8;
	
	unsigned char firstChar = pgm_read_byte(FONT + FONT_FIRST_CHAR);
	unsigned char charCount = pgm_read_byte(FONT + FONT_CHAR_COUNT);
	
	unsigned int index = 0;
	
	if (c < firstChar || c >= (firstChar + charCount)) return 0;
	c -= firstChar;
	
	if (pgm_read_byte(FONT + FONT_LENGTH) == 0 && pgm_read_byte(FONT + FONT_LENGTH + 1) == 0) 
	{
		/* zero length is flag indicating fixed width font (array does not contain width data entries) */
		width = pgm_read_byte(FONT + FONT_FIXED_WIDTH);
		index = c * bytes * width + FONT_WIDTH_TABLE;
	} 
	else 
	{
		/* variable width font, read width data, to get the index */
		for (i = 0; i < c; i++) 
		{
			index += pgm_read_byte(FONT + FONT_WIDTH_TABLE + i);
		}
		index = index * bytes + charCount + FONT_WIDTH_TABLE;
		width = pgm_read_byte(FONT + FONT_WIDTH_TABLE + c);
	}
    if (nX < -width || nY < -height) return width;
	
	/* last but not least, draw the character */
	for (j = 0; j < width; j++)
	{
		/* Vertical Bytes */
		for (i = bytes - 1; i < 254; i--)
		{
			unsigned int offset = (i * 8);
			unsigned char data = pgm_read_byte(FONT + index + j + (i * width));
			
			if ((i == bytes - 1) && bytes > 1) 
			{
				offset = height - 8;
			}
			
			/* Vertical bits */
			for (k = 0; k < 8; k++)
			{ 
				if ((offset + k >= i * 8) && (offset + k <= height)) 
				{
					if (data & (1 << k)) 
					{
						matrix_draw_point(nX + j, nY + offset + k, eFgColor);
					}
					else 
					{
						matrix_draw_point(nX + j, nY + offset + k, eBgColor);
					}
				}
			}
		}
	}
	
	return width;
}

uint16_t matrix_get_textcenter(char *textSource)
{
	uint16_t	width	= 1;
	uint16_t	x		= 0;
    
	for(x = 0; x < utils_strlen(textSource); x++)
	{
		width += matrix_get_charwidth(textSource[x]);
		
		/* Line gap */
		width++;
	}

 	return (int16_t)(((stDispParam.bPanelAcross * stDispParam.bWidth) - width) / 2);
}

void matrix_draw_string(int16_t nX, int16_t nY, char *bStr, eCOLOR color)
{
	uint16_t	i 			= 0;
	uint16_t	strWidth	= 0;
	uint16_t	charWide	= 0;
	int16_t		length		= utils_strlen(bStr);
	uint16_t	height		= pgm_read_byte(FONT + FONT_HEIGHT);
	eCOLOR		eBgColor	= (matrix_bInvertEn == ENABLE) ? color : CL_BLACK;
	
	if (nX >= stDispParam.bPanelAcross * stDispParam.bWidth || nY >= stDispParam.bPanelDown * stDispParam.bHeight) return;
	
	if (nY + height < 0) return;
	
	matrix_draw_line(nX - 1 , nY, nX - 1 , nY + height - 1, eBgColor);
	
	for(i = 0; i < length; i++) 
	{
		charWide = matrix_draw_char(nX + strWidth, nY, bStr[i], color);
		if (charWide > 0) 
		{
			strWidth += charWide ;
			matrix_draw_line(nX + strWidth , nY, nX + strWidth , nY + height - 1, eBgColor);
			strWidth++;
		} 
		else if (charWide < 0) 
		{
			return;
		}
	
		if ((nX + strWidth) >= stDispParam.bWidth * stDispParam.bPanelAcross || nY >= stDispParam.bHeight * stDispParam.bPanelDown) return;
	}
}

void matrix_marquee_pause(FunctionalState state)
{
	matrix_bMarqueePause = state;
}

uint16_t matrix_get_marqueepos(void)
{
	return matrix_nMarqueePos;
}

void matrix_clr_marqueepos(void)
{
	matrix_nMarqueePos = 0;
}

uint8_t matrix_draw_marquee(int16_t nPosX, int16_t nPosY, int16_t width, int16_t height, char *bStr, eMARQUEEDIR direction, eCOLOR color)
{
	int16_t		i				= 0;
	int16_t		nMarqueePosTmp	= matrix_nMarqueePos;
	
	/* Set initial Marquee params */
	if(matrix_nMarqueeWidth == 0)
	{
		if(direction == SCROLL_TOP_TO_BOTTOM)
		{
			matrix_nMarqueeWidth = height;
			matrix_nMarqueePos = nPosY - height - 2;
		}
		else if(direction == SCROLL_BOTTOM_TO_TOP)
		{
			matrix_nMarqueeWidth = height;
			matrix_nMarqueePos = nPosY + height + 2;
		}
		else
		{
			for(i = 0; i < utils_strlen(bStr); i++)
			{
				matrix_nMarqueeWidth += matrix_get_charwidth(bStr[i]);
				
				/* Plus char gap */
				matrix_nMarqueeWidth += 1;
			}
			
			if(direction == SCROLL_RIGHT_TO_LEFT)
			{
				matrix_nMarqueePos = nPosX + width + 2;
			}
			else if(direction == SCROLL_LEFT_TO_RIGHT)
			{
				matrix_nMarqueePos = nPosX - matrix_nMarqueeWidth - 2;
			}
		}
	}
	
	/* Draw String in frame */
	matrix_set_frame(nPosX, nPosY, width, height);
	
	if(direction == SCROLL_RIGHT_TO_LEFT || direction == SCROLL_LEFT_TO_RIGHT)
	{
		matrix_draw_string(matrix_nMarqueePos, nPosY, bStr, color);
	}
	else if(direction == SCROLL_TOP_TO_BOTTOM || direction == SCROLL_BOTTOM_TO_TOP)
	{
		matrix_draw_string(nPosX, matrix_nMarqueePos, bStr, color);
	}
	
	matrix_clr_frame();
	
	/* Set marquee limit and returns ends value */
	switch(direction)
	{			
		case SCROLL_TOP_TO_BOTTOM :
			matrix_nMarqueePos++;
	
			if(matrix_nMarqueePos >= nPosY + matrix_nMarqueeWidth + 2)
			{
				matrix_nMarqueeWidth = 0;
				return 1;
			}
			break;
			
		case SCROLL_BOTTOM_TO_TOP :
			matrix_nMarqueePos--;
	
			if(matrix_nMarqueePos <= (matrix_nMarqueeWidth + 2) * -1)
			{
				matrix_nMarqueeWidth = 0;
				return 1;
			}
			break;
			
		case SCROLL_RIGHT_TO_LEFT :
			matrix_nMarqueePos--;
	
			if(matrix_nMarqueePos <= (matrix_nMarqueeWidth + 2) * -1)
			{
				matrix_nMarqueeWidth = 0;
				return 1;
			}
			break;
			
		case SCROLL_LEFT_TO_RIGHT :
			matrix_nMarqueePos++;
	
			if(matrix_nMarqueePos >= nPosX + width + 2)
			{
				matrix_nMarqueeWidth = 0;
				return 1;
			}
			break;
	}

	if(matrix_bMarqueePause == ENABLE)
	{
		matrix_nMarqueePos = nMarqueePosTmp;
	}
	
	return 0;
}

void matrix_draw_image(uint16_t posX, uint16_t posY, uint8_t *data)
{
	/* Initialize Local Variables */
	int16_t		img_width	= pgm_read_byte(data + 0);
	int16_t		img_height	= pgm_read_byte(data + 1);
	uint8_t		bytecount	= (img_width % 8 == 0) ? (img_width / 8) : (((img_width + (8 - (img_width % 8)))) / 8);
	uint8_t 	vpos		= 0;
	uint8_t 	hpos		= 0;
	uint8_t 	bitval		= 0;
	uint8_t 	bitpos		= 0;
	int16_t		bytepos		= 0;

	for(vpos = 0; vpos < img_height; vpos++)
	{
		for(bytepos = (vpos * bytecount); bytepos < ((vpos * bytecount) + bytecount); bytepos++)
		{
			bitval = pgm_read_byte(data + bytepos + 2);

			for(bitpos = 0; bitpos < 8; bitpos++)
			{
				if(bitval & 0x01)
        		{
					matrix_draw_point(posX + hpos + bitpos, posY + vpos, CL_RED);
				}
        		else
        		{
					matrix_draw_point(posX + hpos + bitpos, posY + vpos, CL_BLACK);
				}

        		bitval >>= 1;
			}
			hpos += 8;
		}
		hpos = 0;
	}
}

void matrix_set_brightness(uint8_t percentage)
{
	if(percentage > 99)
	{
		percentage = 99;
	}

	dmd_set_brightness(percentage);
}