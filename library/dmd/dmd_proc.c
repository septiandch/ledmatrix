/**
 *  DMD Processing Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_proc.h"

/*----- Function Prototypes -----*/
void		dmdproc_set_pixelmap(void);
uint16_t	dmdproc_pixelmapping(int16_t nX, int16_t nY);
uint16_t	dmdproc_get_charwidth(const char letter);

/*----- Global Variables -----*/
const uint8_t	*FONT;
stDisplayFrame	stDispFrame;
eState			eInvertEn = DISABLE;

#ifdef ENABLE_DMA
static uint16_t		wPixelMap[DISPLAY_DATA_SIZE];
#endif

#ifdef ENABLE_DOUBLEBUFFER
uint8_t				pbScreenBuffer[DISPLAY_DATA_SIZE];
#endif

void dmdproc_init()
{
	/* Initialize Display */
	dmdhal_init(DISPLAY_COLOR_MODE, DISPLAY_SCAN_RATE, DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_COUNT_ACCROSS, DISPLAY_COUNT_DOWN);

    dmdproc_clr_screen();
    dmdproc_set_pixelmap();

	dmdproc_init_doublebuffer();
}

void dmdproc_set_font(const uint8_t *font)
{
	FONT = font;
}

void dmdproc_clr_screen(void)
{
	/* Initialize Local Variables */
	uint16_t 	i 	= 0	;
	
	for(i = 0; i < DISPLAY_DATA_SIZE; i++)
	{
#ifdef ENABLE_SPI
		bDisplayBuffer[i] = 0xFF;
#else
		bDisplayBuffer[i] = 0x00;
#endif
	}
}

void dmdproc_init_doublebuffer(void)
{
#ifdef ENABLE_DOUBLEBUFFER
	memcpy(bDisplayBuffer, pbScreenBuffer, DISPLAY_DATA_SIZE);
#endif
}

void dmdproc_set_pixelmap(void)
{
#ifdef ENABLE_DMA
	/* Initialize Local Variables */
	int8_t	x		= 0;
	uint8_t	n		= 0;
	uint8_t	index	= 0;
	
	while(x < stDispProp.bScanrate)
	{
		x++;
		
		for(n = 0; n < stDispProp.bScanrate; n++)
		{
			wPixelMap[index] = (stDispProp.bScanrate - x) + (n * stDispProp.bPanelAcross * stDispProp.bHeight);
			
			index++;
		}
	}
#endif
}

uint16_t dmdproc_pixelmapping(int16_t nX, int16_t nY)
{
	/* Initialize Local Variables */
	uint16_t	bytePos		= 0	;

#ifdef ENABLE_DMA
	bytePos = ((uint16_t) (nX / 8) * stDispProp.bScanrate) + wPixelMap[nY];
#else
	bytePos = (nY * (uint16_t)(stDispProp.bWidth / 8) * stDispProp.bMode * stDispProp.bPanelAcross) + ((uint16_t)(nX / 8) * stDispProp.bMode);
#endif
	
	return bytePos;
}

void dmdproc_set_frame(int16_t nPosStX, int16_t nPosStY, int16_t nPosEnX, int16_t nPosEnY)
{
	stDispFrame.eActive = ENABLE;
	stDispFrame.wStartX = nPosStX;
	stDispFrame.wStartY = nPosStY;
	stDispFrame.wEndX   = nPosEnX;
	stDispFrame.wEndY   = nPosEnY;
}

void dmdproc_clr_frame(void)
{
	stDispFrame.eActive = DISABLE;
	stDispFrame.wStartX = 0;
	stDispFrame.wStartY = 0;
	stDispFrame.wEndX   = 0;
	stDispFrame.wEndY   = 0;
}

void dmdproc_draw_point(int16_t nX, int16_t nY, eColor color)
{
	/* Initialize Local Variables */
	int16_t		bytePos		= 0	;
	int16_t		bitPos		= 0	;
	
	if (nX >= (uint16_t)(stDispProp.bWidth * stDispProp.bPanelAcross) || nY >= (uint16_t)(stDispProp.bHeight * stDispProp.bPanelDown)) return;
	else if (nX < 0 || nY < 0) return;
	
	if(stDispFrame.eActive == ENABLE)
	{
		if (nX >= stDispFrame.wEndX || nY >= stDispFrame.wEndY) return;
		else if (nX < stDispFrame.wStartX || nY < stDispFrame.wStartY) return;
	}

	/* get byte position */
	bytePos = dmdproc_pixelmapping(nX, nY);
	bitPos = nX % 8;

	if(stDispProp.bMode == mode_rgb)
	{
		if(color & eCL_RED) bDisplayBuffer[bytePos + 0] |= (1 << bitPos);
		else bDisplayBuffer[bytePos + 0] &= ~(1 << bitPos);
		
		if(color & eCL_GREEN) bDisplayBuffer[bytePos + 1] |= (1 << bitPos);
		else bDisplayBuffer[bytePos + 1] &= ~(1 << bitPos);
		
		if(color & eCL_BLUE) bDisplayBuffer[bytePos + 2] |= (1 << bitPos);
		else bDisplayBuffer[bytePos + 2] &= ~(1 << bitPos);
	}
	else
	{
#if defined(ENABLE_SPI)
		if(color == eCL_BLACK)
		{
			bDisplayBuffer[bytePos] |= (1 << bitPos);
		}
		else
		{
			bDisplayBuffer[bytePos] &= ~(1 << bitPos);
		}
#else
		if(color != eCL_BLACK)
		{
			bDisplayBuffer[bytePos] |= (1 << bitPos);
		}
		else
		{
			bDisplayBuffer[bytePos] &= ~(1 << bitPos);
		}
#endif
	}
}

void dmdproc_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eColor color)
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
	
	dmdproc_draw_point(x1, y1, color);
	
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
			dmdproc_draw_point(x1, y1, color);
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
			dmdproc_draw_point(x1, y1, color);
		}
	}
}

void dmdproc_draw_box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eColor color)
{	
	dmdproc_draw_line(x1, y1, x2, y1, color);
	dmdproc_draw_line(x1, y1, x1, y2, color);
	dmdproc_draw_line(x1, y2, x2, y2, color);
	dmdproc_draw_line(x2, y1, x2, y2, color);
}

void dmdproc_draw_filledbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eColor color)
{
	/* Initialize Local Variables */
	uint16_t	b = 0;
	
	for (b = x1; b <= x2; b++) 
    {
      dmdproc_draw_line(b, y1, b, y2, color);
    }
}

uint16_t dmdproc_get_charwidth(const char letter)
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

uint16_t dmdproc_get_charheight()
{
	return pgm_read_byte(FONT + FONT_HEIGHT);
}

uint16_t dmdproc_draw_char(int16_t nX, int16_t nY, const char letter, eColor color)
{
	/* Initialize local variables */
	unsigned char	c			= letter;
	unsigned int	i			= 0;
	unsigned int	j			= 0;
	unsigned int	k			= 0;
	unsigned char	height		= pgm_read_byte(FONT + FONT_HEIGHT);
	eColor			eFgColor	= (eInvertEn == ENABLE) ? eCL_BLACK : color;
	eColor			eBgColor	= (eInvertEn == ENABLE) ? color : eCL_BLACK;
	
	if (nX >= (uint16_t)(stDispProp.bWidth * stDispProp.bPanelAcross) || nY >= (uint16_t)(stDispProp.bHeight * stDispProp.bPanelDown)) return -1;
	
	if (c == ' ') 
	{
		unsigned char charWide = dmdproc_get_charwidth(':');
		dmdproc_draw_filledbox(nX, nY, nX + charWide, nY + height - 1, eBgColor);
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
						dmdproc_draw_point(nX + j, nY + offset + k, eFgColor);
					}
					else 
					{
						dmdproc_draw_point(nX + j, nY + offset + k, eBgColor);
					}
				}
			}
		}
	}
	
	return width;
}

void dmdproc_draw_string(int16_t nX, int16_t nY, char *bStr, eColor color)
{
	uint16_t	i 			= 0;
	uint16_t	strWidth	= 0;
	uint16_t	charWide	= 0;
	int16_t		length		= utils_strlen(bStr);
	uint16_t	height		= pgm_read_byte(FONT + FONT_HEIGHT);
	eColor		eBgColor	= (eInvertEn == ENABLE) ? color : eCL_BLACK;
	
	if (nX >= (uint16_t)(stDispProp.bWidth * stDispProp.bPanelAcross) || nY >= (uint16_t)(stDispProp.bHeight * stDispProp.bPanelDown)) return;
	
	if (nY + height < 0) return;
	
	dmdproc_draw_line(nX - 1 , nY, nX - 1 , nY + height - 1, eBgColor);
	
	for(i = 0; i < length; i++) 
	{
		charWide = dmdproc_draw_char(nX + strWidth, nY, bStr[i], color);
		if (charWide > 0) 
		{
			strWidth += charWide ;
			dmdproc_draw_line(nX + strWidth , nY, nX + strWidth , nY + height - 1, eBgColor);
			strWidth++;
		} 
		else if (charWide < 0) 
		{
			return;
		}
	
		if (nX >= (uint16_t)(stDispProp.bWidth * stDispProp.bPanelAcross) || nY >= (uint16_t)(stDispProp.bHeight * stDispProp.bPanelDown)) return;
	}
}

uint16_t dmdproc_get_textwidth(char *textSource)
{
	uint16_t	width	= 0;
	uint16_t	x		= 0;
    
	for(x = 0; x < utils_strlen(textSource); x++)
	{
		width += dmdproc_get_charwidth(textSource[x]);
		
		/* Line gap */
		width++;
	}
	width--;

 	return width;
}

void dmdproc_draw_image(uint16_t posX, uint16_t posY, uint8_t *data, eColor color)
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
					dmdproc_draw_point(posX + hpos + bitpos, posY + vpos, color);
				}
        		else
        		{
					dmdproc_draw_point(posX + hpos + bitpos, posY + vpos, eCL_BLACK);
				}

        		bitval >>= 1;
			}
			hpos += 8;
		}
		hpos = 0;
	}
}

void dmdproc_set_brightness(uint8_t percentage)
{
	uint8_t bLimit = 90;

	percentage = 100 - percentage;

	if(percentage > bLimit)
	{
		percentage = bLimit;
	}

	dmdhal_set_brightness(percentage);
}