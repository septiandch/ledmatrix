/**
  ******************************************************************************
  * @file    main.c 
  * @author  Septian D. Chandra
  * @stRTime.date    17-January-2018
  * @brief   Main program.
  ******************************************************************************
  */

#include "dmd/dmdproc.h"
#include "fonts/SystemFont.h"

/* GLOBAL VARIABLES */

/* FUNCTION PROTOTYPES */

/* ENUMERATION */

/* MAIN FUNCTION */
int main(void)
{	
	/* Startup Delay */
	utils_Delay(300);
	matrix_Init();
	
	matrix_SetBrightness(10);
	utils_Delay(10);

	matrix_SetFont(System5x7);

	matrix_SetBrightness(1);

	while(1)
	{
		utils_Delay(5);
		matrix_DrawMarquee(0, 0, 32*14, 16, "TESTING BISMILLAAH SUBHANALLAH MASYAALLAH ALLAHUAKBAR ALHAMDULILLAAH", SCROLL_RIGHT_TO_LEFT, RED);
	}
}
