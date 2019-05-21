/**
 *  DMD HUB08 Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _DMDHAL_H_
#define _DMDHAL_H_

#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"
#include "ledmatrix.h"
#include "platform_config.h"
#include "misc.h"

/* PERIPHHERALS CONFIGURATION */
/* #define DMD_HUB75 */
#define DMD_HUB12

/* #define ENABLE_SPI */
/* #define ENABLE_DMA */
#define ENABLE_PWM
/* #define ENABLE_TIM */

#if defined (DMD_HUB12)
#	define DMD_PIN_PORT				GPIOA
#	define DMD_PIN_CLK				GPIO_Pin_5
#	define DMD_PIN_LAT				GPIO_Pin_6
#	define DMD_PIN_DAT				GPIO_Pin_7
#	define DMD_PIN_A     			GPIO_Pin_1
#	define DMD_PIN_B     			GPIO_Pin_2
#	define DMD_PIN_EN				GPIO_Pin_3

#	define DMD_PORT_MASK			(0xFFFFFFFF & ~(DMD_PIN_A | DMD_PIN_B)

#elif defined (DMD_HUB75)
#	define DMD_GPIO_RCC				RCC_APB2Periph_GPIOA
#	define DMD_GPIO_SCN_RCC			RCC_APB2Periph_GPIOB

#	define DMD_PORT_DAT				GPIOA
#	define DMD_PIN_R1     			GPIO_Pin_0
#	define DMD_PIN_G1     			GPIO_Pin_1
#	define DMD_PIN_B1     			GPIO_Pin_2
#	define DMD_PIN_R2     			GPIO_Pin_3
#	define DMD_PIN_G2     			GPIO_Pin_4
#	define DMD_PIN_B2     			GPIO_Pin_5
#	define DMD_PIN_EN				GPIO_Pin_8
		
#	define DMD_PORT					GPIOB
#	define DMD_PIN_CLK				GPIO_Pin_6
#	define DMD_PIN_LAT				GPIO_Pin_7
#	define DMD_PIN_A     			GPIO_Pin_12
#	define DMD_PIN_B     			GPIO_Pin_13
#	define DMD_PIN_C     			GPIO_Pin_14

#	define DMD_PORT_DAT_MASK		(0xFFFFFFFF & ~(DMD_PIN_R1 | DMD_PIN_G1 | DMD_PIN_B1 | DMD_PIN_R2 | DMD_PIN_G2 | DMD_PIN_B2))
#	define DMD_PORT_MASK			(0xFFFFFFFF & ~(DMD_PIN_A | DMD_PIN_B | DMD_PIN_C))
#endif

#ifdef	ENABLE_PWM
#	define PWM_PERIOD				(SystemCoreClock / 17570 ) - 1
#	define PWM_START_VAL			100
#endif

/* DISPLAY MACROS */
#define DMD_ENABLE_LO()				DMD_PORT_DAT->BRR  = DMD_PIN_EN
#define DMD_ENABLE_HI()				DMD_PORT_DAT->BSRR = DMD_PIN_EN
#define DMD_LATCH_LO()				DMD_PORT->BRR  = DMD_PIN_LAT
#define DMD_LATCH_HI()				DMD_PORT->BSRR = DMD_PIN_LAT
#define DMD_CLOCK_LO()				DMD_PORT->BRR  = DMD_PIN_CLK
#define DMD_CLOCK_HI()				DMD_PORT->BSRR = DMD_PIN_CLK
#define DMD_CLOCK()					DMD_CLOCK_HI(); DMD_CLOCK_LO();
#define DMD_LATCH()					DMD_ENABLE_LO(); DMD_LATCH_HI(); DMD_LATCH_LO(); DMD_ENABLE_HI();

/* DISPLAY MODE */
#define MODE_MONO					1
#define MODE_TRI					2
#define MODE_RGB					3
	
/* DISPLAY PARAMETER */	
#define DISPLAY_MODE				MODE_RGB	/* 1 = Mono , 2 = Trii-Color, 3 = RGB */
#define DISPLAY_SCANRATE			8	/* 4 = 1/4 , 8 = 1/8, 16 = 1/16 */
#define DISPLAY_WIDTH       		32
#define DISPLAY_HEIGHT      		16
#define DISPLAY_ACROSS      		5
#define DISPLAY_DOWN        		1
#define DISPLAY_ROWSIZE        		(DISPLAY_WIDTH / BYTE_SIZE)
#define DISPLAY_TOTAL       		(DISPLAY_ACROSS * DISPLAY_DOWN)
#define DISPLAY_SIZE        		(DISPLAY_ROWSIZE * DISPLAY_HEIGHT * DISPLAY_TOTAL) /* Size in Bytes */

/* GLOBAL VARIABLES */
extern uint8_t	dmd_bDisplayBuffer[];

/* FUNCTIONS */
extern void		dmd_Init();
extern void		dmd_DisplayScan();
extern void		dmd_SendData(uint8_t _data);
extern void		dmd_SendData75(uint16_t nBufferHi, uint16_t nBufferLo);

#endif	/* _DMDHAL_H */




