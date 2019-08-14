/**
 *  DMD Parameter Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_prm.h"

/* GLOBAL VARIABLES */
stDisplayParam	stDispParam;

void dmd_prm_set_display(eDisplayMode mode, uint8_t scanrate, uint8_t width, uint8_t height, uint8_t panelAcross, uint8_t panelDown)
{
	stDispParam.bMode			= mode;
	stDispParam.bScanrate		= scanrate;
	stDispParam.bWidth			= width;
	stDispParam.bHeight			= height;
	stDispParam.bPanelAcross	= panelAcross;
	stDispParam.bPanelDown		= panelDown;
}

uint8_t dmd_prm_get_rowsize()
{ 
	return (uint8_t)(stDispParam.bWidth / 8);
}

uint16_t dmd_prm_get_totalpanel()
{
	return (uint16_t)(stDispParam.bPanelAcross * stDispParam.bPanelDown);
}

uint16_t dmd_prm_get_dispsize()
{
	return (uint16_t)(dmd_prm_get_totalpanel() * dmd_prm_get_rowsize() * stDispParam.bHeight);
}