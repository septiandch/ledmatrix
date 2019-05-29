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

	uint8_t i;

	matrix_DrawPoint(0, 15, RED);
	matrix_DrawPoint(0, 16, RED);
	//matrix_DrawString(0, 10, "TESTING", RED);

	while(1)
	{
		//for(i = 0; i < 32; i++)
		//{
		//	matrix_DrawPoint(32*7, i, RED);
		//	utils_Delay(100);
		//	matrix_DrawPoint(32*7, i, BLACK);
		//}
		matrix_DrawMarquee(0, 13, 32*7, 16, "TESTING BISMILLAAH SUBHANALLAH MASYAALLAH ALLAHUAKBAR ALHAMDULILLAAH", SCROLL_RIGHT_TO_LEFT, RED);
		utils_Delay(10);
	}
}
