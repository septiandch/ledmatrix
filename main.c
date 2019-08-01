/**
  ******************************************************************************
  * @file    main.c 
  * @author  Septian D. Chandra
  * @stRTime.date    17-January-2018
  * @brief   Main program.
  ******************************************************************************
  */

#include "dmd/dmd_lib.h"
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

	matrix_SetFont(System5x7);

	matrix_DrawString(0, 0, "123", RED);

	while(1)
	{
	}
}
