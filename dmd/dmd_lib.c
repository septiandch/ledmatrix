/**
 *  DMD processing Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_lib.h"

/** FUNCTION PROTOTYPES */
uint16_t matrix_PixelMapping(int16_t nX, int16_t nY);
void matrix_PixelMapCreate(void);

/** Initialize Global Variables */
const uint8_t	*FONT;
stMatrixFrame	matrix_stDisplayFrame;
int16_t			matrix_nMarqueeWidth = 0;
int16_t			matrix_nMarqueePos = 0;
	
#ifdef ENABLE_DMA
static uint16_t		matrix_nPixelMap[MATRIX_SIZE];
#endif

void matrix_Init(void)
{
	/* Initialize Display */
	dmd_Init();

    matrix_ScreenClear(BLACK);
    matrix_PixelMapCreate();
}

void matrix_SetFont(const uint8_t *font)
{
	FONT = font;
}

void matrix_ScreenClear(eCOLOR color)
{
	/* Initialize Local Variables */
	uint16_t 	i 	= 0	;
	
	for(i = 0; i < DISPLAY_SIZE * DISPLAY_MODE; i++)
	{
		dmd_bDisplayBuffer[i] = color;
	}
	
	matrix_nMarqueeWidth = 0;
	matrix_nMarqueePos = 0;
}

void matrix_ApplyScreen(void)
{
#ifdef ENABLE_BUFFER
	dmd_eDisplayStatus = DISP_READY;
#endif
}

void matrix_FrameCreate(int16_t nPosX, int16_t nPosY, int16_t width, int16_t height)
{
	matrix_stDisplayFrame.active = 1;
	matrix_stDisplayFrame.startX = nPosX;
	matrix_stDisplayFrame.startY = nPosY;
	matrix_stDisplayFrame.endX   = nPosX + width;
	matrix_stDisplayFrame.endY   = nPosY + height;
}

void matrix_FrameClear(void)
{
	matrix_stDisplayFrame.active = 0;
}

void matrix_PixelMapCreate(void)
{
#ifdef ENABLE_DMA
	/* Initialize Local Variables */
	int8_t	x		= 0;
	uint8_t	n		= 0;
	uint8_t	index	= 0;
	
	while(x < DISPLAY_SCANRATE)
	{
		x++;
		
		for(n = 0; n < DISPLAY_SCANRATE; n++)
		{
			matrix_nPixelMap[index] = (DISPLAY_SCANRATE - x) + (n * DISPLAY_ACROSS * DISPLAY_HEIGHT);
			
			index++;
		}
	}
#endif
}

uint16_t matrix_PixelMapping(int16_t nX, int16_t nY)
{
	/* Initialize Local Variables */
	uint16_t	bytePos		= 0	;

#ifdef ENABLE_DMA
	bytePos = ((uint16_t) (nX / BYTE_SIZE) * DISPLAY_SCANRATE) + matrix_nPixelMap[nY];
#else
	bytePos =	((nY % DISPLAY_HEIGHT) * (DISPLAY_WIDTH / 8) * DISPLAY_TOTAL * DISPLAY_MODE) + ((nX / 8) * DISPLAY_MODE)
				+ (((nY / DISPLAY_HEIGHT) * DISPLAY_ACROSS * (DISPLAY_WIDTH / 8)) * DISPLAY_MODE);
#endif
	
	return bytePos;
}

void matrix_DrawPoint(int16_t nX, int16_t nY, eCOLOR color)
{
	/* Initialize Local Variables */
	int16_t		bytePos		= 0	;
	int16_t		bitPos		= 0	;
	
	if (nX >= DISPLAY_ACROSS * DISPLAY_WIDTH || nY >= DISPLAY_DOWN * DISPLAY_HEIGHT) return;
	else if (nX < 0 || nY < 0) return;
	
	if(matrix_stDisplayFrame.active == 1)
	{
		if (nX >= matrix_stDisplayFrame.endX || nY >= matrix_stDisplayFrame.endY) return;
		else if (nX < matrix_stDisplayFrame.startX || nY < matrix_stDisplayFrame.startY) return;
	}

	/* get byte position */
	bytePos = matrix_PixelMapping(nX, nY);
	bitPos = nX % 8;

#if DISPLAY_MODE == MODE_RGB
	if(color & RED) dmd_bDisplayBuffer[bytePos + 0] |= (1 << bitPos);
	else dmd_bDisplayBuffer[bytePos + 0] &= ~(1 << bitPos);
	
	if(color & GREEN) dmd_bDisplayBuffer[bytePos + 1] |= (1 << bitPos);
	else dmd_bDisplayBuffer[bytePos + 1] &= ~(1 << bitPos);
	
	if(color & BLUE) dmd_bDisplayBuffer[bytePos + 2] |= (1 << bitPos);
	else dmd_bDisplayBuffer[bytePos + 2] &= ~(1 << bitPos);
	
#else
	if(color != BLACK)
	{
		dmd_bDisplayBuffer[bytePos] |= (1 << bitPos);
	}
	else
	{
		dmd_bDisplayBuffer[bytePos] &= ~(1 << bitPos);
	}
#endif
}

void matrix_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color)
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
	
	matrix_DrawPoint(x1, y1, color);
	
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
			matrix_DrawPoint(x1, y1, color);
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
			matrix_DrawPoint(x1, y1, color);
		}
	}
}

void matrix_DrawBox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color)
{	
	matrix_DrawLine(x1, y1, x2, y1, color);
	matrix_DrawLine(x1, y1, x1, y2, color);
	matrix_DrawLine(x1, y2, x2, y2, color);
	matrix_DrawLine(x2, y1, x2, y2, color);
}

void matrix_DrawFilledBox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, eCOLOR color)
{
	/* Initialize Local Variables */
	uint16_t	b = 0;
	
	for (b = x1; b <= x2; b++) 
    {
      matrix_DrawLine(b, y1, b, y2, color);
    }
}

uint16_t matrix_GetCharWidth(const char letter)
{
	/* Initialize Local Variables */
	char		c			=	letter;
	char		firstChar	=	pgm_read_byte(FONT + FONT_FIRST_CHAR);
	char		charCount	=	pgm_read_byte(FONT + FONT_CHAR_COUNT);
	int16_t		width		=	0;
	
	/* Space is often not included in font so use width of 'n' */
	if (c == ' ') c = 'n';
	
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

uint16_t matrix_DrawChar(int16_t nX, int16_t nY, const char letter, eCOLOR color)
{
	unsigned char c = letter;
	unsigned int i, j, k;
	unsigned char height = pgm_read_byte(FONT + FONT_HEIGHT);
	
	if (nX >= (DISPLAY_WIDTH * DISPLAY_ACROSS) || nY >= (DISPLAY_HEIGHT * DISPLAY_DOWN) ) return -1;
	
	if (c == ' ') 
	{
		unsigned char charWide = matrix_GetCharWidth(':');
		matrix_DrawFilledBox(nX, nY, nX + charWide, nY + height, BLACK);
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
						matrix_DrawPoint(nX + j, nY + offset + k, color);
					}
					else 
					{
						matrix_DrawPoint(nX + j, nY + offset + k, BLACK);
					}
				}
			}
		}
	}
	
	return width;
}

uint16_t matrix_GetTextCenter(char *textSource)
{
  uint8_t	width	= 0;
  uint16_t	x		= 0;
    
  for(x = 0; x < strlen(textSource); x++)
  {
	/* Line gap +1 */
	width++;
  
    width += matrix_GetCharWidth(textSource[x]);
  }

  return ((int16_t)(DISPLAY_ACROSS * DISPLAY_WIDTH)/2) - (int16_t)(width/2);
}

void matrix_DrawString(int16_t nX, int16_t nY, char *bStr, eCOLOR color)
{
	uint16_t	i 			= 0;
	uint16_t	strWidth	= 0;
	uint16_t	charWide	= 0;
	int16_t		length		= utils_strlen(bStr);
	uint16_t	height		= pgm_read_byte(FONT + FONT_HEIGHT);
	
	if (nX >= DISPLAY_ACROSS * DISPLAY_WIDTH || nY >= DISPLAY_DOWN * DISPLAY_HEIGHT) return;
	
	if (nY + height < 0) return;
	
	matrix_DrawLine(nX - 1 , nY, nX - 1 , nY + height, BLACK);
	
	for(i = 0; i < length; i++) 
	{
		charWide = matrix_DrawChar(nX + strWidth, nY, bStr[i], color);
		if (charWide > 0) 
		{
			strWidth += charWide ;
			matrix_DrawLine(nX + strWidth , nY, nX + strWidth , nY + height, BLACK);
			strWidth++;
		} 
		else if (charWide < 0) 
		{
			return;
		}
	
		if ((nX + strWidth) >= DISPLAY_WIDTH * DISPLAY_ACROSS || nY >= DISPLAY_HEIGHT * DISPLAY_DOWN) return;
	}
}

uint8_t matrix_DrawMarquee(int16_t nPosX, int16_t nPosY, int16_t width, int16_t height, char *bStr, eMARQUEEDIR direction, eCOLOR color)
{
	int16_t i = 0;
	
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
				matrix_nMarqueeWidth += matrix_GetCharWidth(bStr[i]);
				
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
	matrix_FrameCreate(nPosX, nPosY, width, height);
	
	if(direction == SCROLL_RIGHT_TO_LEFT || direction == SCROLL_LEFT_TO_RIGHT)
	{
		matrix_DrawString(matrix_nMarqueePos, nPosY, bStr, color);
	}
	else if(direction == SCROLL_TOP_TO_BOTTOM || direction == SCROLL_BOTTOM_TO_TOP)
	{
		matrix_DrawString(nPosX, matrix_nMarqueePos, bStr, color);
	}
	
	matrix_FrameClear();
	
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
	
	return 0;
}

void matrix_SetBrightness(uint8_t percentage)
{
	if(percentage > 99)
	{
		percentage = 99;
	}

	dmd_SetBrightness(percentage);
}