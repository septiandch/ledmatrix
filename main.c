/**
  ******************************************************************************
  * @file    main.c 
  * @author  Septian D. Chandra
  * @stRTime.date    17-January-2018
  * @brief   Main program.
  ******************************************************************************
  */

#include "dmd/dmdproc.h"
#include "peripherals/usart.h"
#include "fonts/SystemFont.h"
#include "fonts/ArialBlack16.h"
#include "appli/movingsign/app_main.h"

/* GLOBAL VARIABLES */
uint8_t		bTask					= 0;
uint8_t		bMode					= 0;
uint8_t		bDelay					= 0;
uint8_t		bIteration				= 0;
char		str[COMMAND_MAX_LEN]	= "";
eTaskStatus	eTaskStat				= WORKING;

/* FUNCTION PROTOTYPES */

/* ENUMERATION */

/* MAIN FUNCTION */
int main(void)
{	
	app_init();

	app_command_read(0, &str, &bMode, &bDelay, &bIteration);

	usart_puti(bMode);
	usart_putc(',');
	usart_puti(bDelay);
	usart_putc(',');
	usart_puti(bIteration);
	usart_putc(',');
	usart_puts(str);
	usart_putc('\r');

	while(1)
	{
		switch(bTask)
		{
			case 0:
				eTaskStat = app_set_mode(MODE_WELCOMEMESSAGE, "AHLAN WA SAHLAN\rSELAMAT DATANG DI MASJID AL-IKHLAS");
				break;

			case 1:
				eTaskStat = app_set_mode(MODE_REPORTMESSAGE, "ADAB MASUK MASJID\rMENDAHULUKAN KAKI KANAN\rMEMBACA DOA MASUK MASJID\rBERWUDHU SEBELUM BERANGKAT\r");
				break;

			case 2:
				eTaskStat = app_set_mode(MODE_DOAMESSAGE, "DOA MASUK MASJID\r\"Ya Allah, bukakanlah untukku pintu-pintu rahmat-Mu\"");
				break;
				
			case 3:
				eTaskStat = app_set_mode(MODE_BIGMESSAGE, "SELAMAT HARI RAYA IDUL FITRI 1440H, MOHON MAAF LAHIR DAN BATIN");
				break;

			case 4:
				eTaskStat = app_set_mode(MODE_TITLEDMESSAGE, "PENGUMUMAN\rKAJIAN RUTIN SABTU PAGI UNTUK SEMENTARA DILIBURKAN");
				break;
		}

		if(eTaskStat == FINISHED)
		{
			bTask++;
			if(bTask > 4)
			{
				bTask = 0;
			}
		}

		utils_delay(10); 
		
		app_command_check();
	}
}
 