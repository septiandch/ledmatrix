/**
 *  DMD Parameter Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_prm.h"

/* GLOBAL VARIABLES */
stDisplayParam	stDispParam;

void dmd_prm_set_display(uint8_t mode, uint8_t scanrate, uint8_t width, uint8_t height, uint8_t panelAcross, uint8_t panelDown)
{
	stDispParam.bMode			= mode;
	stDispParam.bScanrate		= scanrate;
	stDispParam.bWidth			= width;
	stDispParam.bHeight			= height;
	stDispParam.bRowSize		= (uint8_t)(stDispParam.bWidth / 8);
	stDispParam.bPanelAcross	= panelAcross;
	stDispParam.bPanelDown		= panelDown;
	stDispParam.bPanelCount		= stDispParam.bPanelAcross * stDispParam.bPanelDown;
	stDispParam.nDispsize		= stDispParam.bPanelCount * stDispParam.bRowSize * stDispParam.bHeight;
}

uint8_t dmd_prm_get_rowsize()
{ 
	return stDispParam.bRowSize;
}

uint16_t dmd_prm_get_totalpanel()
{
	return stDispParam.bPanelCount;
}

uint16_t dmd_prm_get_dispsize()
{
	return stDispParam.nDispsize;
}