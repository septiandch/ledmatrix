/*
 *  DMD Controller Board Defines
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _BRDTYP_DEFINED_
#define _BRDTYP_DEFINED_

#include "stm32f10x.h"

/*----- Board Define -----*/
#define BRDTYP_DMD19

/*----- IO Configuration -----*/
#define BRD_GPIO_APBClockCmd		RCC_APB2PeriphClockCmd
#define BRD_GPIO_RCC				RCC_APB2Periph_GPIOA
#define BRD_GPIO_PORT				GPIOA
#define BRD_GPIO_PIN_CLK			GPIO_Pin_5
#define BRD_GPIO_PIN_LAT			GPIO_Pin_6
#define BRD_GPIO_PIN_DAT			GPIO_Pin_7
#define BRD_GPIO_PIN_A     			GPIO_Pin_1
#define BRD_GPIO_PIN_B     			GPIO_Pin_2

#define BRD_GPIO_EN_APBClockCmd		RCC_APB2PeriphClockCmd
#define BRD_GPIO_RCC_EN				RCC_APB2Periph_GPIOB
#define BRD_GPIO_PORT_EN			GPIOB
#define BRD_GPIO_PIN_EN				GPIO_Pin_0

#define BRD_BUZZER_APBClockCmd		RCC_APB2PeriphClockCmd
#define BRD_BUZZER_RCC				RCC_APB2Periph_GPIOA
#define BRD_BUZZER_PORT				GPIOA
#define BRD_BUZZER_PIN				GPIO_Pin_8

#define BRD_SQW_APBClockCmd			RCC_APB2PeriphClockCmd
#define BRD_SQW_RCC_EN				RCC_APB2Periph_GPIOB
#define BRD_SQW_PORT				GPIO_PortSourceGPIOB
#define BRD_SQW_PIN					GPIO_Pin_5
#define BRD_SQW_EXTI_PIN			GPIO_PinSource5
#define BRD_SQW_EXTI_IRQn			EXTI9_5_IRQn
#define BRD_SQW_EXTI_IRQHandler		EXTI9_5_IRQHandler
#define BRD_SQW_EXTI_Line			EXTI_Line5

#define BRD_SPI_APBClockCmd			RCC_APB2PeriphClockCmd
#define BRD_SPI_RCC					RCC_APB2Periph_SPI1
#define BRD_SPI						SPI1

#define BRD_PWM_TIM_APBClockCmd		RCC_APB1PeriphClockCmd
#define BRD_PWM_AFIO_APBClockCmd	RCC_APB2PeriphClockCmd
#define BRD_PWM_TIM_RCC				RCC_APB1Periph_TIM3
#define BRD_PWM_AFIO_RCC			RCC_APB2Periph_AFIO
#define BRD_PWM_TIM					TIM3
#define BRD_PWM_OCChPreloadConf		TIM_OC3PreloadConfig
#define BRD_PWM_OCChInit			TIM_OC3Init
#define BRD_PWM_SetCompare			TIM_SetCompare3

#endif /* _BRDTYP_DEFINED_ */