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
uint8_t				bTask					= 0;
volatile uint8_t	bMode					= MODE_BIGMESSAGE;
volatile uint8_t	bDelay					= 10;
volatile uint8_t	bIteration				= 0;
volatile char		str[COMMAND_MAX_LEN]	= "EMPTY MESSAGE";
eTaskStatus			eTaskStat				= IDLE;

/* FUNCTION PROTOTYPES */

/* ENUMERATION */

/* MAIN FUNCTION */
int main(void)
{	
	app_init();

#ifdef USE_FMEM
	fmem_WriteString(0 * COMMAND_MAX_LEN, "0,1,1,AHLAN WA SAHLAN\rSELAMAT DATANG DI MASJID AL-IKHLAS", 57);
	fmem_ApplyBuffer();
	fmem_WriteString(1 * COMMAND_MAX_LEN, "1,1,1,ADAB MASUK MASJID\rMENDAHULUKAN KAKI KANAN\rMEMBACA DOA MASUK MASJID\rBERWUDHU DARI RUMAH\r", 104);
	fmem_ApplyBuffer();
	fmem_WriteString(2 * COMMAND_MAX_LEN, "2,1,1,DOA MASUK MASJID\r\"Ya Allah, bukakanlah untukku pintu-pintu rahmat-Mu\"", 78);
	fmem_ApplyBuffer();
	fmem_WriteString(3 * COMMAND_MAX_LEN, "4,1,1,SELAMAT HARI RAYA IDUL FITRI 1440H, MOHON MAAF LAHIR DAN BATIN", 68);
	fmem_ApplyBuffer();
	fmem_WriteString(4 * COMMAND_MAX_LEN, "3,1,1,PENGUMUMAN\rKAJIAN RUTIN SABTU PAGI UNTUK SEMENTARA DILIBURKAN", 68);
	fmem_ApplyBuffer();
#else
	//eeprom_write_byte(MEM_PWRSAVE_HOUR, 22);
	//eeprom_write_byte(MEM_PWRSAVE_MINUTE, 0);
	//eeprom_write_byte(MEM_PWRSAVE_DURATION, 5);
	//eeprom_write_byte(MEM_BRIGHTNESS, 1);
	//eeprom_write_string(0 * COMMAND_MAX_LEN, "0,1,1,AHLAN WA SAHLAN\rSELAMAT DATANG DI MASJID AL-IKHLAS", 57);
	//eeprom_write_string(1 * COMMAND_MAX_LEN, "1,1,1,ADAB MASUK MASJID\rMENDAHULUKAN KAKI KANAN\rMEMBACA DOA MASUK MASJID\rBERWUDHU DARI RUMAH\r", 104);
	//eeprom_write_string(2 * COMMAND_MAX_LEN, "2,1,1,DOA MASUK MASJID\r\"Ya Allah, bukakanlah untukku pintu-pintu rahmat-Mu\"", 78);
	//eeprom_write_string(3 * COMMAND_MAX_LEN, "4,1,1,SELAMAT HARI RAYA IDUL FITRI 1440H, MOHON MAAF LAHIR DAN BATIN", 68);
	//eeprom_write_string(4 * COMMAND_MAX_LEN, "3,1,1,PENGUMUMAN\rKAJIAN RUTIN SABTU PAGI UNTUK SEMENTARA DILIBURKAN", 68);
#endif

	while(1)
	{
		if(eTaskStat == IDLE)
		{
			/*Powersave Time Check*/
			/* add codes here ! */

			app_command_read(bTask, &str, &bMode, &bDelay, &bIteration);
			if(bMode >= 0 && bMode < 7)
			{
				eTaskStat = WORKING;
			}
			
			bTask++;

			if(bTask >= COMMAND_MAX_TASK)
			{
				bTask = 0;
			}
		}
		else
		{
			eTaskStat = app_set_mode(bMode, str);
			
			if(eTaskStat == IDLE && bIteration > 1)
			{
				bIteration--;
				eTaskStat = WORKING;
			}
		}
		
		/* Check for new incoming command messages */
		app_command_check();

		utils_delay(bDelay);
	}
}
 