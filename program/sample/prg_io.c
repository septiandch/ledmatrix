/**
 *  Led Matrix Display Input/Output Configuration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prg_io.h"

void io_buzzer_init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	/** Enable GPIO clock */
	BUZZER_APBClockCmd(BUZZER_RCC, ENABLE);
	
	/** Configure Output */
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
}

void io_buzzer_pin(uint8_t state)
{
	if(state >= 0)
	{
		BUZZER_PORT->BSRR = BUZZER_PIN;
	}
	else
	{
		BUZZER_PORT->BRR = BUZZER_PIN;
	}
	
}

void io_int_init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/** Connect EXTI Line to pin */
	GPIO_EXTILineConfig(SQW_PORT, SQW_PIN);

	/** Configure EXTI line */
	EXTI_InitStructure.EXTI_Line = SQW_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/** Set Interrupt priority */
	NVIC_InitStructure.NVIC_IRQChannel = SQW_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void SQW_EXTI_IRQHandler(void)
{
	/** SQW Interrupt Handler */
	if(EXTI_GetITStatus(SQW_EXTI_Line) != RESET)
	{    		
		if(bColonState == ':')
		{
			bColonState = ' ';
		}
		else
		{
			bColonState = ':';
		}
	
		nCounter++;
		if(nCounter > 1000)
		{
			nCounter = 0;
		}

		rtc_readTime(&stRTime.year, &stRTime.month, &stRTime.date, &stRTime.day, &stRTime.hour, &stRTime.minute, &stRTime.second);

		/* Clear the  EXTI line 5 pending bit */
		EXTI_ClearITPendingBit(EXTI_SQW_Line);
	}
}