/**
 *  Display Interfacing
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prg_def.h"
#include "prg_func.h"
#include "prg_rsc.h"

void display_init(uint8_t bBrightness)
{
	dmdproc_init();
	dmdproc_set_brightness(bBrightness);
}

void display_clear()
{
	dmdproc_clr_screen();
}

void display_message_init(stDisplayMsg *pstDispMsg, char *pcText, uint16_t wStrLength, const char *pbFont, int16_t stPosX, int16_t stPosY, eColor eTextColor)
{
	pstDispMsg->pcString		= pcText;
	pstDispMsg->wStringLen		= wStrLength;
	pstDispMsg->pbFont			= pbFont;
	pstDispMsg->eTextColor		= eTextColor;

	pstDispMsg->stPos.X			= stPosX;
	pstDispMsg->stPos.Y			= stPosY;

	pstDispMsg->stFrame.eActive	= DISABLE;
	pstDispMsg->stFrame.wStartX	= 0;
	pstDispMsg->stFrame.wStartY	= 0;
	pstDispMsg->stFrame.wEndX	= 0;
	pstDispMsg->stFrame.wEndY	= 0;
}

void display_message_set_text(stDisplayMsg *pstDispMsg, char *pcText)
{
	pstDispMsg->pcString = pcText;
}

void display_frame_set_prop(stDisplayMsg *pstDispMsg, int16_t wPixStartX, int16_t wPixStartY, int16_t wPixEndX, int16_t wPixEndY)
{
	pstDispMsg->stFrame.wStartX	= wPixStartX;
	pstDispMsg->stFrame.wStartY	= wPixStartY;
	pstDispMsg->stFrame.wEndX	= wPixEndX;
	pstDispMsg->stFrame.wEndY	= wPixEndY;
}

void display_frame_set_state(stDisplayMsg *pstDispMsg, eState state)
{
	pstDispMsg->stFrame.eActive	= state;

	if(state == ENABLE)
	{
		dmdproc_set_frame(pstDispMsg->stFrame.wStartX, pstDispMsg->stFrame.wStartY, pstDispMsg->stFrame.wEndX, pstDispMsg->stFrame.wEndY);
	}
	else
	{
		dmdproc_clr_frame();
	}
}

void display_message_set_font(stDisplayMsg *pstDispMsg, const uint8_t *font)
{
	pstDispMsg->pbFont = font;
}

void display_message_clr_text(stDisplayMsg *pstDispMsg)
{
	char *pcStr = pstDispMsg->pcString;

	memset(&pcStr, 0, pstDispMsg->wStringLen);
}

void display_message_set_pos(stDisplayMsg *pstDispMsg, int16_t wPosX, uint16_t wPosY)
{
	pstDispMsg->stPos.X = wPosX;
	pstDispMsg->stPos.Y = wPosY;
}

int16_t display_message_get_centerpos(stDisplayMsg *pstDispMsg, uint8_t bDirection)
{
	int16_t wRetVal = 0;

	dmdproc_set_font(pstDispMsg->pbFont);

	if(bDirection == 0)
	{
		wRetVal = (int16_t)(((DISPLAY_WIDTH * DISPLAY_COUNT_ACCROSS) / 2) - (dmdproc_get_textwidth(pstDispMsg->pcString) / 2));
	}
	else
	{
		wRetVal = (int16_t)(((DISPLAY_HEIGHT * DISPLAY_COUNT_DOWN) / 2) - (dmdproc_get_charheight() / 2));
	}

	return wRetVal;
}

uint16_t display_message_get_strwidth(stDisplayMsg *pstDispMsg)
{
	int16_t wRetVal = 0;

	dmdproc_set_font(pstDispMsg->pbFont);

	wRetVal = dmdproc_get_textwidth(pstDispMsg->pcString);

	return wRetVal;
}

uint16_t display_message_get_chrheight(stDisplayMsg *pstDispMsg)
{
	int16_t wRetVal = 0;

	dmdproc_set_font(pstDispMsg->pbFont);

	wRetVal = dmdproc_get_charheight();

	return wRetVal;
}

void display_message_set_color(stDisplayMsg *pstDispMsg, eColor color)
{
	pstDispMsg->eTextColor = color;
}

void display_message_draw(stDisplayMsg *pstDispMsg)
{
	dmdproc_set_font(pstDispMsg->pbFont);

	dmdproc_draw_string(pstDispMsg->stPos.X, pstDispMsg->stPos.Y, pstDispMsg->pcString, pstDispMsg->eTextColor);
}

void display_message_draw_static_string(int16_t wPosX, int16_t wPosY, char *pcString, const uint8_t *font, eColor color)
{
	dmdproc_set_font(font);
	dmdproc_draw_string(wPosX, wPosY, pcString, color);
} 

void display_marquee_init(stDisplayMsg *pstDispMsg, eMarqueeDir direction, eState eStartOnCurrPos)
{
	int16_t width	= pstDispMsg->stFrame.wEndX - pstDispMsg->stFrame.wStartX;
	int16_t height	= pstDispMsg->stFrame.wEndY - pstDispMsg->stFrame.wStartY;
	int16_t i		= 0;

	pstDispMsg->stMarquee.wMarqueePos	= 0;
	pstDispMsg->stMarquee.wDestPos		= 0;
	pstDispMsg->stMarquee.eStat			= eMARQUEE_STAT_READY;
	pstDispMsg->stMarquee.eDir			= direction;

	/* Set initial Marquee params */
	if(pstDispMsg->stMarquee.eDir == eMARQUEE_TOP_TO_BOTTOM)
	{
		pstDispMsg->stMarquee.wDestPos = height * 2;
		pstDispMsg->stMarquee.wMarqueePos = pstDispMsg->stFrame.wStartY - height - 2;
	
		if(eStartOnCurrPos == ENABLE)
		{	/* If enabled, start Marquee from current position */
			pstDispMsg->stMarquee.wMarqueePos = pstDispMsg->stPos.Y;
		}
	}
	else if(pstDispMsg->stMarquee.eDir == eMARQUEE_BOTTOM_TO_TOP)
	{
		pstDispMsg->stMarquee.wDestPos = height * 2;
		pstDispMsg->stMarquee.wMarqueePos = pstDispMsg->stFrame.wEndY + 2;
	
		if(eStartOnCurrPos == ENABLE)
		{	/* If enabled, start Marquee from current position () */
			pstDispMsg->stMarquee.wMarqueePos = pstDispMsg->stPos.Y;
		}
	}
	else
	{
		/* Set font to get font */
		dmdproc_set_font(pstDispMsg->pbFont);

		for(i = 0; i < utils_strlen(pstDispMsg->pcString); i++)
		{
			pstDispMsg->stMarquee.wDestPos += dmdproc_get_charwidth(pstDispMsg->pcString[i]);
			
			/* Plus char gap */
			pstDispMsg->stMarquee.wDestPos += 1;
		}
		
		if(pstDispMsg->stMarquee.eDir == eMARQUEE_LEFT_TO_RIGHT)
		{
			pstDispMsg->stMarquee.wMarqueePos = pstDispMsg->stFrame.wStartX - pstDispMsg->stMarquee.wDestPos - 2;
		}
		else if(pstDispMsg->stMarquee.eDir == eMARQUEE_RIGHT_TO_LEFT)
		{
			pstDispMsg->stMarquee.wMarqueePos = pstDispMsg->stFrame.wEndX + 2;
		}
	
		if(eStartOnCurrPos == ENABLE)
		{	/* If enabled, start Marquee from current position () */
			pstDispMsg->stMarquee.wMarqueePos = pstDispMsg->stPos.X;
		}
	}
}

uint8_t display_marquee_draw(stDisplayMsg *pstDispMsg)
{
	int16_t		i				= 0;
	uint8_t		bMarqueeRetStat	= eMARQUEE_STAT_MOVING;
	
	if(pstDispMsg->stFrame.wEndX == 0 && pstDispMsg->stFrame.wEndY == 0)
	{
		dmdproc_draw_point(0, 0, eCL_RED);
		pstDispMsg->stMarquee.eStat = eMARQUEE_STAT_ERROR;
	}
	else
	{
		display_frame_set_state(pstDispMsg, ENABLE);

		dmdproc_set_font(pstDispMsg->pbFont);

		if(pstDispMsg->stMarquee.eStat != eMARQUEE_STAT_ERROR && pstDispMsg->stMarquee.eStat != eMARQUEE_STAT_READY)
		{
			if(pstDispMsg->stMarquee.eDir == eMARQUEE_RIGHT_TO_LEFT || pstDispMsg->stMarquee.eDir == eMARQUEE_LEFT_TO_RIGHT)
			{
				dmdproc_draw_string(pstDispMsg->stMarquee.wMarqueePos, pstDispMsg->stPos.Y, pstDispMsg->pcString, pstDispMsg->eTextColor);
			}
			else if(pstDispMsg->stMarquee.eDir == eMARQUEE_TOP_TO_BOTTOM || pstDispMsg->stMarquee.eDir == eMARQUEE_BOTTOM_TO_TOP)
			{
				dmdproc_draw_string(pstDispMsg->stPos.X, pstDispMsg->stMarquee.wMarqueePos, pstDispMsg->pcString, pstDispMsg->eTextColor);
			}
		}

		display_frame_set_state(pstDispMsg, DISABLE);
	}

	if(pstDispMsg->stMarquee.eStat == eMARQUEE_STAT_ERROR || pstDispMsg->stMarquee.eStat == eMARQUEE_STAT_MOVED || pstDispMsg->stMarquee.eStat == eMARQUEE_STAT_READY)
	{
		bMarqueeRetStat = pstDispMsg->stMarquee.eStat;
	}
	else if(pstDispMsg->stMarquee.eStat == eMARQUEE_STAT_IDLE)
	{
		pstDispMsg->stMarquee.wIdleCount--;

		if(pstDispMsg->stMarquee.wIdleCount <= 0)
		{
			bMarqueeRetStat = pstDispMsg->stMarquee.bNextStat;
		}
		else
		{
			bMarqueeRetStat = eMARQUEE_STAT_IDLE;
		}

		pstDispMsg->stMarquee.eStat = bMarqueeRetStat;
	}

	/* Move Marquee Pos */
	if(pstDispMsg->stMarquee.eStat == eMARQUEE_STAT_MOVING)
	{
		switch(pstDispMsg->stMarquee.eDir)
		{		
			case eMARQUEE_TOP_TO_BOTTOM :
				pstDispMsg->stMarquee.wMarqueePos++;

				if(pstDispMsg->stMarquee.wMarqueePos >= pstDispMsg->stFrame.wEndY + 2)
				{
					bMarqueeRetStat = eMARQUEE_STAT_MOVED;
				}
				break;

			case eMARQUEE_BOTTOM_TO_TOP :
				pstDispMsg->stMarquee.wMarqueePos--;

				if(pstDispMsg->stMarquee.wMarqueePos <= (pstDispMsg->stMarquee.wDestPos + 2) * -1)
				{
					bMarqueeRetStat = eMARQUEE_STAT_MOVED;
				}
				break;

			case eMARQUEE_RIGHT_TO_LEFT :
				pstDispMsg->stMarquee.wMarqueePos--;

				if(pstDispMsg->stMarquee.wMarqueePos <= (pstDispMsg->stFrame.wStartX - pstDispMsg->stMarquee.wDestPos))
				{
					bMarqueeRetStat = eMARQUEE_STAT_MOVED;
				}
				break;

			case eMARQUEE_LEFT_TO_RIGHT :
				pstDispMsg->stMarquee.wMarqueePos++;

				if(pstDispMsg->stMarquee.wMarqueePos >= pstDispMsg->stFrame.wEndX + 2)
				{
					bMarqueeRetStat = eMARQUEE_STAT_MOVED;
				}
				break;
			
			default:
				break;
		}
		
		pstDispMsg->stMarquee.eStat = bMarqueeRetStat;
	}
	
	return bMarqueeRetStat;
}

uint8_t display_marquee_checkonpos(stDisplayMsg *pstDispMsg, int16_t wCheckPos)
{
	uint8_t retval = 0;

	if(pstDispMsg->stMarquee.wMarqueePos == wCheckPos)
	{
		retval = 1;
	}

	return retval;
}

void display_marquee_set_state(stDisplayMsg *pstDispMsg, eMarqueeStat eState)
{
	pstDispMsg->stMarquee.eStat = eState;
}

void display_marquee_idle_set(stDisplayMsg *pstDispMsg, int16_t count, uint8_t bNextStat)
{
	pstDispMsg->stMarquee.eStat = eMARQUEE_STAT_IDLE;
	pstDispMsg->stMarquee.wIdleCount = count;
	pstDispMsg->stMarquee.bNextStat = bNextStat;
}

void display_marquee_iteration_add(stDisplayMsg *pstDispMsg)
{
	pstDispMsg->stMarquee.bIteration++;
}

void display_marquee_iteration_reset(stDisplayMsg *pstDispMsg)
{
	pstDispMsg->stMarquee.bIteration = 0;
}