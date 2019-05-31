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
#include "appli/movingsign/app_main.h"

/* GLOBAL VARIABLES */
char text1[] = "SELAMAT DATANG DI";
char text2[] = "MASJID AL-IKHLAS";

/* FUNCTION PROTOTYPES */

/* ENUMERATION */

/* MAIN FUNCTION */
int main(void)
{	
	app_Init();

	while(1)
	{
		app_SetMode(MODE_BIGMESSAGE, "SELAMAT DATANG DI\rMASJID AL-IKHLAS");
		utils_Delay(10);
	}
}
