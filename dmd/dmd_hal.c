/**
 *  DMD Hardware Access Layer Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_hal.h"

/* GLOBAL VARIABLES */
uint8_t dmd_bDisplayBuffer	[DISPLAY_MAX_SIZE];
uint8_t dmd_bDisplayScan	= 0;

#ifdef ENABLE_TIM
uint16_t CCR_Val = 6000;
#endif

void dmd_init()
{
    GPIO_InitTypeDef		GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
    SPI_InitTypeDef			SPI_InitStructure;
    
#if defined(DMD_HUB12)
	/*  GPIO RCC */
	DMD_APBClockCmd(DMD_RCC, ENABLE);

#	if defined(ENABLE_SPI)
	/*  SPI RCC */
    SPI_APBClockCmd(DMD_SPI_RCC, ENABLE);
	
    /* Initialize GPIO pins for MOSI, MISO, and SCK (Alternate Mode) */
	GPIO_InitStructure.GPIO_Pin		= DMD_PIN_CLK | DMD_PIN_DAT;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
    
    /* GPIO pin for EN, SS (LAT) & A, B (Output Mode) */
	GPIO_InitStructure.GPIO_Pin		= DMD_PIN_LAT | DMD_PIN_A | DMD_PIN_B;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
    
    /* Initialize SPI */
	SPI_InitStructure.SPI_Direction			= SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode				= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize			= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL				= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA				= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS				= SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit			= SPI_FirstBit_LSB;
	SPI_InitStructure.SPI_CRCPolynomial		= 0;
	SPI_Init(DMD_SPI, &SPI_InitStructure);
	
	/* Enable SPI */
	SPI_Cmd(DMD_SPI, ENABLE);

#	else
    /* GPIO pin init for DAT, CLK, SS (LAT) & A, B (Output Mode) */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_CLK | DMD_PIN_DAT | DMD_PIN_LAT | DMD_PIN_A | DMD_PIN_B;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
#	endif

#	if defined(ENABLE_DMA)
	/*  DMA RCC */
	RCC_AHBPeriphClockCmd(SPI_MASTER_DMA_CLK, ENABLE);
	
	/* Enable DMA1 channel IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#	endif

#elif defined(DMD_HUB75)
	/*  GPIO RCC */
	RCC_APB2PeriphClockCmd(DMD_GPIO_SCN_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(DMD_GPIO_RCC, ENABLE);
    
    /* GPIO pin init for Data Port */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_R1 | DMD_PIN_R2 | DMD_PIN_G1 | DMD_PIN_G2 | DMD_PIN_B1 | DMD_PIN_B2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PORT_DAT, &GPIO_InitStructure);
	
    /* GPIO pin init for Scanning Port */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_CLK | DMD_PIN_LAT | DMD_PIN_A | DMD_PIN_B| DMD_PIN_C;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
#endif

#if defined(ENABLE_PWM)
	uint16_t TimerPeriod = PWM_PERIOD;
	uint16_t ChannelPulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);

	/*  GPIO EN RCC */
	DMD_EN_APBClockCmd(DMD_RCC_EN, ENABLE);

	/* PWM_TIM clock enable */
	PWM_TIM_APBClockCmd(PWM_TIM_RCC, ENABLE);
	
	/* Alternative Function IO clock enable */
	PWM_AFIO_APBClockCmd(PWM_AFIO_RCC, ENABLE);
	
    /* GPIO pin init for EN */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_EN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(DMD_PORT_EN, &GPIO_InitStructure);
	
	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStructure);
	
	/* Channel x Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = PWM_START_VAL;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	PWM_OCChInit(PWM_TIM, &TIM_OCInitStructure);
	
	PWM_OCChPreloadConf(PWM_TIM, TIM_OCPreload_Enable);
	
	/* PWM_TIM counter enable */
	TIM_Cmd(PWM_TIM, ENABLE);
	
	/* PWM_TIM Main Output Enable */
	TIM_CtrlPWMOutputs(PWM_TIM, ENABLE);

#else
	/*  GPIO EN RCC */
	RCC_APB2PeriphClockCmd(DMD_GPIO_EN_RCC, ENABLE);

    /* GPIO pin init for EN */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_EN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PIN_EN_PORT, &GPIO_InitStructure);
#endif

#if defined(ENABLE_TIM)
	/* TIM clock enable */
	TIMx_APBClockCmd(TIMx_RCC, ENABLE);
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	/* Enable the TIM global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* TIM Interrupt enable */
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
	
	/* TIM counter enable */
	TIM_Cmd(TIMx, ENABLE);
#else
	/* Systick Handler */
	SysTick_Config((SystemCoreClock / 1000) - 1);
#endif
}

void dmd_DMAConfig(uint8_t *data, uint32_t data_size)
{	
#ifdef ENABLE_DMA
	DMA_InitTypeDef  DMA_InitStructure;
	
	DMA_DeInit(SPI_MASTER_Tx_DMA_Channel);
	
	/* DMA1 channel3 configuration */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) SPI_MASTER_DR_Base;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) data;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = data_size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(SPI_MASTER_Tx_DMA_Channel, &DMA_InitStructure);
	
	/* Enable DMA1 Channel3 Transfer Complete interrupt */
	DMA_ITConfig(SPI_MASTER_Tx_DMA_Channel, DMA_IT_TC, ENABLE);
#endif
}

void dmd_DMAStart(uint8_t *data, uint32_t data_size)
{
#ifdef ENABLE_DMA
	dmd_DMAConfig(data, data_size);
	
	SPI_I2S_DMACmd(SPI_MASTER, SPI_I2S_DMAReq_Tx, ENABLE);
	DMA_Cmd(SPI_MASTER_Tx_DMA_Channel, ENABLE);

#	ifdef ENABLE_TIM
	TIM_Cmd(TIM3, ENABLE);
	TIM_SetCompare1(TIM3, TIM_GetCapture1(TIM3) + CCR_Val);
#	endif
#endif
}

void DMA1_Channel3_IRQHandler(void)
{
#ifdef ENABLE_DMA
	//DMA1 Channel3 Transfer Complete interrupt
	if(DMA_GetITStatus(DMA1_IT_TC3))
	{
		//Clear DMA1 Channel3 Half Transfer, Transfer Complete and Global interrupt pending bits
		DMA_ClearITPendingBit(DMA1_IT_TC3);
		DMA_Cmd(SPI_MASTER_Tx_DMA_Channel, DISABLE);
		
		dmd_display_scan();
	}
#endif
}

void SysTick_Handler(void)
{
#if defined(ENABLE_DMA) && defined(DMD_HUB12)
	uint32_t offset = (stDispParam.bWidth / BYTE_SIZE) * dmd_prm_get_totalpanel() * stDispParam.bScanrate;

	dmd_DMAStart(&dmd_bDisplayBuffer[offset * dmd_bDisplayScan], offset);
#else
	dmd_display_scan();
#endif
}

void TIMx_IRQHandler(void)
{
#ifdef ENABLE_TIM
 	if(TIM_GetITStatus(TIMx, TIM_IT_Update) != RESET)
	{
    	TIM_ClearITPendingBit(TIMx, TIM_IT_Update);

#	if defined(ENABLE_DMA) && defined(DMD_HUB12)
		uint32_t offset = (stDispParam.bWidth / BYTE_SIZE) * dmd_prm_get_totalpanel() * stDispParam.bScanrate;

		dmd_DMAStart(&dmd_bDisplayBuffer[offset * dmd_bDisplayScan], offset);
	
#	else
		dmd_display_scan();
#	endif
	}
#endif
}

void dmd_send_data(uint8_t data)
{	
#if defined(ENABLE_SPI) && defined(DMD_HUB12)
	SPI_I2S_SendData(DMD_SPI, data);
	
	/* Wait for SPI Transfer End */
    while (SPI_I2S_GetFlagStatus(DMD_SPI, SPI_I2S_FLAG_TXE) == RESET);
    
#elif defined(DMD_HUB12)
	int 	i = 0;
	
    for(i = 0; i < 8; i++)
    {
        if(data & 0x01)
        {
			DMD_PORT->BRR  = DMD_PIN_DAT;
		}
        else
        {
			DMD_PORT->BSRR = DMD_PIN_DAT;
		}

        data >>= 1;
        DMD_CLOCK();
    }
#endif
}

void dmd_send_data_rgb(uint16_t nBufferHi, uint16_t nBufferLo)
{	
#if defined(DMD_HUB75)
	uint8_t		i			= 0;
	uint8_t		dataMask	= 0x01;
	uint32_t	wGpio_Temp	= 0x00000000;
	
	for(i = 0; i < BYTE_SIZE; i++)
	{
		wGpio_Temp = 0x00000000;
		
		//if(dmd_bDisplayBrightness < 10)
		{
			if(dmd_bDisplayBuffer[nBufferHi + 0] & dataMask) wGpio_Temp |= DMD_PIN_R1;
			if(dmd_bDisplayBuffer[nBufferHi + 1] & dataMask) wGpio_Temp |= DMD_PIN_G1;
			if(dmd_bDisplayBuffer[nBufferHi + 2] & dataMask) wGpio_Temp |= DMD_PIN_B1;
			
			if(dmd_bDisplayBuffer[nBufferLo + 0] & dataMask) wGpio_Temp |= DMD_PIN_R2;
			if(dmd_bDisplayBuffer[nBufferLo + 1] & dataMask) wGpio_Temp |= DMD_PIN_G2;
			if(dmd_bDisplayBuffer[nBufferLo + 2] & dataMask) wGpio_Temp |= DMD_PIN_B2;
		}
		
		DMD_PORT_DAT->ODR = (DMD_PORT_DAT->ODR & DMD_PORT_DAT_MASK) | wGpio_Temp;
		
		dataMask <<= 1;
	
		DMD_CLOCK();
	}
#endif
}

void dmd_set_brightness(uint8_t percentage)
{
#ifdef ENABLE_PWM
	uint32_t value = (uint32_t)((uint32_t)(PWM_PERIOD * percentage) / 100);
	
	PWM_SetCompare(PWM_TIM, value);
#endif
}

void dmd_display_scan()
{	    
#if !defined(ENABLE_DMA) && defined(DMD_HUB12)
    uint16_t 	i = 0;
    uint16_t 	rowsize = (stDispParam.bWidth / 8) * dmd_prm_get_totalpanel();
    uint16_t 	offsetRow1 = rowsize * dmd_bDisplayScan;
    uint16_t 	offsetRow2 = offsetRow1 + (rowsize * stDispParam.bScanrate);
    uint16_t 	offsetRow3 = offsetRow2 + (rowsize * stDispParam.bScanrate);
    uint16_t 	offsetRow4 = offsetRow3 + (rowsize * stDispParam.bScanrate);
	uint32_t	wGpio_Temp	= 0;
    
    for (i = 0; i < rowsize; i++) 
    {
		dmd_send_data(dmd_bDisplayBuffer[offsetRow4 + i]);
		dmd_send_data(dmd_bDisplayBuffer[offsetRow3 + i]);
		dmd_send_data(dmd_bDisplayBuffer[offsetRow2 + i]);
		dmd_send_data(dmd_bDisplayBuffer[offsetRow1 + i]);
    }

#elif defined(DMD_HUB75)
	uint16_t	offsetHi	= dmd_prm_get_rowsize() * stDispParam.bPanelAcross * stDispParam.bMode * dmd_bDisplayScan;
    uint16_t	offsetLo	= dmd_prm_get_rowsize() * stDispParam.bPanelAcross * stDispParam.bMode * (dmd_bDisplayScan + 8);
    uint16_t 	i			= 0;
	uint32_t	wGpio_Temp	= 0;

    for (i = 0; i < dmd_prm_get_rowsize() * stDispParam.bPanelAcross * stDispParam.bMode; i += stDispParam.bMode) 
    {
		dmd_send_data_rgb(offsetHi + i, offsetLo + i);
    }
#endif
	
	switch (dmd_bDisplayScan)
	{
		case 0 :
			wGpio_Temp = 0x00000000;
			break;
		case 1 :
			wGpio_Temp = DMD_PIN_A;
			break;
		case 2 :
			wGpio_Temp = DMD_PIN_B;
			break;
		case 3 :
			wGpio_Temp = DMD_PIN_A | DMD_PIN_B;
			break;
		case 4 :
			wGpio_Temp = DMD_PIN_C;
			break;
		case 5 :
			wGpio_Temp = DMD_PIN_A | DMD_PIN_C;
			break;
		case 6 :
			wGpio_Temp = DMD_PIN_B | DMD_PIN_C;
			break;
		case 7 :
			wGpio_Temp = DMD_PIN_A | DMD_PIN_B | DMD_PIN_C;
			break;
	}
	
	DMD_PORT->ODR = (DMD_PORT->ODR & DMD_PORT_MASK) | wGpio_Temp;
	
	DMD_LATCH();

	dmd_bDisplayScan++;
	if(dmd_bDisplayScan >= stDispParam.bScanrate)
	{
		dmd_bDisplayScan = 0;
	}
}
