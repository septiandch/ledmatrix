/**
 *  Moving Sign HAL
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */
 
#include "app_hal.h"

void app_hal_init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	/** Enable GPIO clock */
	RCC_APB2PeriphClockCmd(BUZZER_GPIO_RCC, ENABLE);
	
	/** Configure Output */
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BUZZER_GPIO, &GPIO_InitStructure);
}

void app_hal_interrupt_init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/** Enable AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/** Connect EXTI Line to pin */
	GPIO_EXTILineConfig(GPIO_SQWPORT, GPIO_SQWPIN);

	/** Configure EXTI line */
	EXTI_InitStructure.EXTI_Line = EXTI_SQW_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/** Set Interrupt priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI_SQW_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}