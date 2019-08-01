/**
 *  DMD Hardware Configuration Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _DMD_CONF_H_
#define _DMD_CONF_H_

/*----- Display Configuration -----*/
#define DISPLAY_MODE				MODE_MONO	/* Mono = 1 , Tri = 2, RGB = 3 */
#define DISPLAY_SCANRATE			4	/* 4 = 1/4 , 8 = 1/8, 16 = 1/16 */
#define DISPLAY_WIDTH       		32
#define DISPLAY_HEIGHT      		16
#define DISPLAY_ACROSS      		1
#define DISPLAY_DOWN        		1
#define DISPLAY_ROWSIZE        		(DISPLAY_WIDTH / 8) /* 1 byte = 8 bit */
#define DISPLAY_TOTAL       		(DISPLAY_ACROSS * DISPLAY_DOWN)
#define DISPLAY_SIZE        		(DISPLAY_ROWSIZE * DISPLAY_HEIGHT * DISPLAY_TOTAL) /* Size in Bytes */

/*----- HUB type -----*/
/* #define DMD_HUB75 */
#define DMD_HUB12

/*-----  Peripherals Configuration ----- */
#define ENABLE_PWM
#define ENABLE_TIM
/* #define ENABLE_SPI */
/* #define ENABLE_DMA */

#ifdef	ENABLE_PWM
#   if defined(DMD_HUB75)
#       define PWM_TIM              TIM1
#       define PWM_TIM_RCC  	    RCC_APB2Periph_TIM1
#		define PWM_AFIO_RCC			RCC_APB2Periph_AFIO
#       define PWM_OCChInit         TIM_OC1Init
#       define PWM_OCChPreloadConf  TIM_OC1PreloadConfig
#		define PWM_SetCompare		TIM_SetCompare4
#   elif defined(DMD_HUB12)
#       define PWM_TIM              TIM3
#       define PWM_TIM_RCC   	    RCC_APB1Periph_TIM3
#		define PWM_AFIO_RCC			RCC_APB2Periph_AFIO
#       define PWM_OCChPreloadConf  TIM_OC3PreloadConfig
#       define PWM_OCChInit         TIM_OC3Init
#		define PWM_SetCompare		TIM_SetCompare3
#   endif

#	define PWM_PERIOD				((SystemCoreClock / 17570) - 1)
#	define PWM_START_VAL			100
#endif

#ifdef ENABLE_TIM
#	define TIMx							TIM3
#	define TIMx_RCC						RCC_APB1Periph_TIM3
#	define TIMx_IRQn					TIM3_IRQn
#	define TIMx_IRQHandler				TIM3_IRQHandler
#endif

/*-----  Port Configuration ----- */
#if defined (DMD_HUB12)
#	define DMD_PIN_PORT				GPIOA
#	define DMD_GPIO_RCC				RCC_APB2Periph_GPIOA
#	define DMD_PIN_CLK				GPIO_Pin_5
#	define DMD_PIN_LAT				GPIO_Pin_6
#	define DMD_PIN_DAT				GPIO_Pin_7
#	define DMD_PIN_A     			GPIO_Pin_1
#	define DMD_PIN_B     			GPIO_Pin_2

#	define DMD_PIN_EN_PORT			GPIOB
#	define DMD_GPIO_EN_RCC			RCC_APB2Periph_GPIOB
#	define DMD_PIN_EN				GPIO_Pin_0

#	define DMD_PORT_MASK			(0xFFFFFFFF & ~(DMD_PIN_A | DMD_PIN_B))

#   if defined(ENABLE_SPI)
#       define DMD_SPI              SPI1
#       define DMD_SPI_RCC			RCC_APB2Periph_SPI1
#   endif

#elif defined (DMD_HUB75)
#	define DMD_PORT_DAT				GPIOA
#	define DMD_GPIO_RCC				RCC_APB2Periph_GPIOA
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

#endif	/* _DMD_CONF_H */