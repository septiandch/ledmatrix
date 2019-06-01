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

/* FUNCTION PROTOTYPES */

/* ENUMERATION */

/* MAIN FUNCTION */
int main(void)
{	
	app_init();


	while(1)
	{
		app_set_mode(MODE_DOAMESSAGE, "DO'A MEMASUKI MASJID");
		utils_Delay(1000);
		app_set_mode(MODE_WELCOME, "SELAMAT DATANG DI\rMASJID AL-IKHLAS");
		utils_Delay(1000);
	}
}
