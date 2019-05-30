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
#include "fonts/ArialBlack16.h"

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

	matrix_SetFont(ArialBlack16);

	matrix_SetBrightness(1);

	matrix_DrawString(0, 0, "TOTAL INFAQ BULAN MEI 2019", RED);

	while(1)
	{
		matrix_DrawMarquee(0, 16, 32*7, 16, "Rp. 52.754.000", SCROLL_RIGHT_TO_LEFT, RED);
		utils_Delay(10);
	}
}
