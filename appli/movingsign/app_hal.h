/**
 *  Moving Sign HAL
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "stm32f10x_conf.h"
#include "app_main.h"

#ifndef _APP_HAL_H_
#define _APP_HAL_H_

#define BUZZER_GPIO_RCC				RCC_APB2Periph_GPIOB
#define BUZZER_GPIO					GPIOB
#define BUZZER_PIN					GPIO_Pin_0
#define BUZZER_DELAY				500
		
#define SQWOUT_PIN					GPIO_Pin_5
#define GPIO_SQWPORT				GPIO_PortSourceGPIOB
#define GPIO_SQWPIN					GPIO_PinSource5
#define EXTI_SQW_IRQn				EXTI9_5_IRQn
#define EXTI_SQW_IRQHandler			EXTI9_5_IRQHandler
#define EXTI_SQW_Line				EXTI_Line5

extern void	app_hal_init(void);
extern void app_hal_interrupt_init(void);

#endif /* _APP_HAL_H_ */