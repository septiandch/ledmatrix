/**
 *  DMD Hardware Configuration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _DMD_CONF_H_
#define _DMD_CONF_H_

#include "program/prg_conf.h"
#include PROG_DEF_H

#define DISPLAY_COUNT_TOTAL			(DISPLAY_COUNT_ACCROSS * DISPLAY_COUNT_DOWN * DISPLAY_COLOR_MODE)
#define DISPLAY_DATA_SIZE			(DISPLAY_COUNT_TOTAL * DISPLAY_HEIGHT * (DISPLAY_WIDTH / 8))

#if defined(BRDTYP_DMD19)

#ifdef ENABLE_TIM
#	define TIMx_APBClockCmd			RCC_APB1PeriphClockCmd
#	define TIMx_RCC					RCC_APB1Periph_TIM4
#	define TIMx						TIM4
#	define TIMx_IRQn				TIM4_IRQn
#	define TIMx_IRQHandler			TIM4_IRQHandler
#	define TIMx_GetCapture			TIM_GetCapture4
#	define TIMx_SetCompare			TIM_SetCompare4
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
#	define PWM_PERIOD				((SystemCoreClock / 3000000) - 1)
#	define PWM_START_VAL			100
#endif

#if defined(ENABLE_SPI)
#	define DMD_SPI_APBClockCmd		BRD_SPI_APBClockCmd
#	define DMD_SPI_RCC				BRD_SPI_RCC
#	define DMD_SPI_AFIO_RCC			BRD_SPI_AFIO_RCC
#	define DMD_SPI					BRD_SPI
#endif

#if defined(ENABLE_DMA)
#	define DMD_DMA_SPI_RCC			RCC_AHBPeriph_DMA1
#	define DMD_DMA_MASTER			DMA1
#	define DMD_DMA_IT_TC			DMA1_IT_TC3
#	define DMD_DMA_SPI_CH			DMA1_Channel3
#	define DMD_DMA_IRQn				DMA1_Channel3_IRQn
#	define DMD_DMA_IRQHandler		DMA1_Channel3_IRQHandler
#	define DMD_SPI_MASTER_DR_Base	0x4001300C
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
#	define DMD_PIN_C     			(0) /* Not available */

#	define DMD_EN_APBClockCmd		BRD_GPIO_EN_APBClockCmd
#	define DMD_RCC_EN				BRD_GPIO_RCC_EN
#	define DMD_PORT_EN				BRD_GPIO_PORT_EN
#	define DMD_PIN_EN				BRD_GPIO_PIN_EN

#	define DMD_PORT_MASK			(0xFFFFFFFF & ~(DMD_PIN_A | DMD_PIN_B))

#elif defined (DMD_HUB75_SUPPORT)
#	define DMD_APBClockCmd	        BRD_GPIO_APBClockCmd_HUB75
#	define DMD_PORT_DAT				BRD_GPIO_PORT_HUB75
#	define DMD_RCC					BRD_GPIO_RCC_HUB75

#	define DMD_PIN_R1     			BRD_GPIO_PIN_R1
#	define DMD_PIN_G1     			BRD_GPIO_PIN_G1
#	define DMD_PIN_B1     			BRD_GPIO_PIN_B1
#	define DMD_PIN_R2     			BRD_GPIO_PIN_R2
#	define DMD_PIN_G2     			BRD_GPIO_PIN_G2
#	define DMD_PIN_B2     			BRD_GPIO_PIN_B2
#	define DMD_PIN_EN				BRD_GPIO_RCC_EN

#	define DMD_SCN_APBClockCmd      BRD_GPIO_APBClockCmd
#	define DMD_PORT					BRD_GPIO_PORT
#	define DMD_GPIO_SCN_RCC			BRD_GPIO_RCC

#	define DMD_PIN_CLK				BRD_GPIO_PIN_CLK
#	define DMD_PIN_LAT				BRD_GPIO_PIN_LAT
#	define DMD_PIN_A     			BRD_GPIO_PIN_A
#	define DMD_PIN_B     			BRD_GPIO_PIN_B
#	define DMD_PIN_C     			BRD_GPIO_PIN_C

#	define DMD_EN_APBClockCmd		BRD_GPIO_EN_APBClockCmd
#	define DMD_RCC_EN				BRD_GPIO_RCC_EN
#	define DMD_PORT_EN				BRD_GPIO_PORT_EN
#	define DMD_PIN_EN				BRD_GPIO_PIN_EN

#	define DMD_PORT_DAT_MASK		(0xFFFFFFFF & ~(DMD_PIN_R1 | DMD_PIN_G1 | DMD_PIN_B1 | DMD_PIN_R2 | DMD_PIN_G2 | DMD_PIN_B2))
#	define DMD_PORT_MASK			(0xFFFFFFFF & ~(DMD_PIN_A | DMD_PIN_B | DMD_PIN_C))
#endif

#endif /* #ifdef BRDTYP_DMD19 */

#endif	/* _DMD_CONF_H_ */
