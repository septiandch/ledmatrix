/**
 *  Input/Output Configuration
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "prg_def.h"
#include "prg_func.h"

/* Function to call when interrupt */
void (*pFuncCall)(void);

/* IO Functions */
void io_buzzer_init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	/* Enable GPIO clock */
	BUZZER_APBClockCmd(BUZZER_RCC, ENABLE);
	
	/* Configure Output */
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
}

void io_buzzer_pin(eFlag flag)
{
	if(flag == SET)
	{
		BUZZER_PORT->BSRR = BUZZER_PIN;
	}
	else
	{
		BUZZER_PORT->BRR = BUZZER_PIN;
	}
	
}

void io_rtc_init()
{
	rtc_init(SQW_1HZ);
}

void io_int_init(void *func)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;

	/* Enable GPIOB clock */
	SQW_APBClockCmd(SQW_RCC, ENABLE);

	/* Configure PB.09 pin as input floating */
	GPIO_InitStructure.GPIO_Pin = SQW_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SQW_PORT, &GPIO_InitStructure);

	/* Enable AFIO clock */
	SQW_APBClockCmd_AFIO(SQW_RCC_AFIO, ENABLE);

	/* Connect EXTI Line to pin */
	GPIO_EXTILineConfig(SQW_PORTSOURCE, SQW_PINSOURCE);

	/** Configure EXTI line */
	EXTI_InitStructure.EXTI_Line = SQW_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Set Interrupt priority */
	NVIC_InitStructure.NVIC_IRQChannel = SQW_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Assign Function to call on interrupt */
	pFuncCall = func;
}

void SQW_EXTI_IRQHandler(void)
{
	/* SQW Interrupt Handler */
	if(EXTI_GetITStatus(SQW_EXTI_Line) != RESET)
	{
		/* Assigned Function call */
		pFuncCall();

		/* Clear the  EXTI line 5 pending bit */
		EXTI_ClearITPendingBit(SQW_EXTI_Line);
	}
}
