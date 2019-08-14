/**
  ******************************************************************************
  * @file    main.c 
  * @author  Septian D. Chandra
  * @stRTime.date    17-January-2018
  * @brief   Main program.
  ******************************************************************************
  */

#include "prg/prg_conf.h"
#include "dmd/dmd_proc.h"
#include "fonts/SystemFont.h"
#include "fonts/ArialBlack16.h"

/* GLOBAL VARIABLES */

/* FUNCTION PROTOTYPES */

/* ENUMERATION */

/* MAIN FUNCTION */
int main(void)
{	
	matrix_init();
	matrix_set_brightness(40);
	matrix_set_font(System5x7);
	
	matrix_draw_string(0, 0, "Test", CL_RED);
	matrix_draw_string(0, 8, "123", CL_RED);
	matrix_set_screen();

	while(1)
	{

	}
}
 