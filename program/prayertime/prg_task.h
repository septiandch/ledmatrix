/**
 *  Ledmatrix Hardware Configuration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _DMD_CONF_H_
#define _DMD_CONF_H_

#include "brdtyp/brd_DMD19.h"

/*----- Display Configuration -----*/
#define stDispProp.bMode				MODE_MONO	/* Mono = 1 , Tri = 2, RGB = 3 */
#define stDispProp.bScanrate			4	/* 4 = 1/4 , 8 = 1/8, 16 = 1/16 */
#define DISPLAY_WIDTH       		    32
#define stDispProp.bHeight      		16
#define DISPLAY_ACROSS      		    1
#define DISPLAY_DOWN        		    1
#define DISPLAY_ROWSIZE        		    (DISPLAY_WIDTH / 8) /* 1 byte = 8 bit */
#define DISPLAY_TOTAL       		    (DISPLAY_ACROSS * DISPLAY_DOWN)
#define DISPLAY_SIZE        		    (DISPLAY_ROWSIZE * stDispProp.bHeight * DISPLAY_TOTAL) /* Size in Bytes */

/*----- HUB type -----*/
#define DMD_HUB75_SUPPORT
/* #define DMD_HUB12_SUPPORT */

/*-----  Peripherals Configuration ----- */
#define ENABLE_PWM
#define ENABLE_TIM
/* #define ENABLE_SPI */
/* #define ENABLE_DMA */

#ifdef ENABLE_TIM
#	define TIMx_APBClockCmd			RCC_APB1PeriphClockCmd
#	define TIMx_RCC					RCC_APB1Periph_TIM3
#	define TIMx						TIM3
#	define TIMx_IRQn				TIM3_IRQn
#	define TIMx_IRQHandler			TIM3_IRQHandler
#endif

#ifdef	ENABLE_PWM
#	define PWM_TIM_APBClockCmd		BRD_PWM_TIM_APBClockCmd
#	define PWM_AFIO_APBClockCmd		BRD_PWM_AFIO_APBClockCmd
#	define PWM_TIM_RCC   	    	BRD_PWM_TIM_RCC
#	define PWM_AFIO_RCC				BRD_PWM_AFIO_RCC
#	define PWM_TIM              	BRD_PWM_TIM
#	define PWM_OCChPreloadConf  	BRD_PWM_OCChPreloadConf
#	define PWM_OCChInit         	BRD_PWM_OCChInit
#	define PWM_SetCompare			BRD_PWM_SetCompare
#	define PWM_PERIOD				((SystemCoreClock / 17570) - 1)
#	define PWM_START_VAL			100
#endif

/*-----  DMD IO Configuration ----- */
#if defined (DMD_HUB12_SUPPORT)
#	define DMD_APBClockCmd			BRD_GPIO_APBClockCmd
#	define DMD_RCC					BRD_GPIO_RCC
#	define DMD_PORT					BRD_GPIO_PORT
#	define DMD_PIN_CLK				BRD_GPIO_PIN_CLK
#	define DMD_PIN_LAT				BRD_GPIO_PIN_LAT
#	define DMD_PIN_DAT				BRD_GPIO_PIN_DAT
#	define DMD_PIN_A     			BRD_GPIO_PIN_A
#	define DMD_PIN_B     			BRD_GPIO_PIN_B

#	define DMD_EN_APBClockCmd		BRD_GPIO_EN_APBClockCmd
#	define DMD_RCC_EN				BRD_GPIO_RCC_EN
#	define DMD_PORT_EN				BRD_GPIO_PORT_EN
#	define DMD_PIN_EN				BRD_GPIO_PIN_EN

#	define DMD_PORT_MASK			(0xFFFFFFFF & ~(DMD_PIN_A | DMD_PIN_B))

#elif defined (DMD_HUB75_SUPPORT)
#	define DMD_PORT_DAT				GPIOA
#	define DMD_RCC				    RCC_APB2Periph_GPIOA
#	define DMD_GPIO_SCN_RCC			RCC_APB2Periph_GPIOB

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

#if defined(ENABLE_SPI)
#	define DMI_SPI_APBClockCmd		BRD_SPI_APBClockCmd
#	define DMD_SPI_RCC				BRD_SPI_RCC
#	define DMD_SPI					BRD_SPI
#endif

#endif	/* _DMD_CONF_H */