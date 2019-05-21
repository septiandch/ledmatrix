/**
 *  DMD HUB08 Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmdhal.h"

/* GLOBAL VARIABLES */
uint8_t dmd_bDisplayBuffer[DISPLAY_SIZE * DISPLAY_MODE];
uint8_t dmd_bDisplayScan		= 0;
uint8_t dmd_bDisplayBrightness	= 0;

#ifdef ENABLE_TIM
uint16_t CCR_Val = 6000;
#endif

void dmd_Init()
{
    GPIO_InitTypeDef		GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
    SPI_InitTypeDef			SPI_InitStructure;
    
#if defined(DMD_HUB12) && defined(ENABLE_SPI)
	/*  SPI RCC */
    RCC_APB2PeriphClockCmd(DMD_SPI_RCC, ENABLE);
	
    /* Initialize GPIO pins for MOSI, MISO, and SCK (Alternate Mode) */
	GPIO_InitStructure.GPIO_Pin = PIN_CLK | PIN_DAT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
    
    /* GPIO pin for EN, SS (LAT) & A, B (Output Mode) */
	GPIO_InitStructure.GPIO_Pin = PIN_EN | PIN_LAT | PIN_A | PIN_B;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
    
    /* Initialize SPI */
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_Init(DMD_SPI, &SPI_InitStructure);
	
	/* Enable SPI */
	SPI_Cmd(DMD_SPI, ENABLE);
	
#elif defined(DMD_HUB12)    
	/*  GPIO RCC */
	RCC_APB2PeriphClockCmd(DMD_GPIO_RCC, ENABLE);
    
    /* GPIO pin init for DAT, CLK, SS (LAT) & A, B (Output Mode) */
	GPIO_InitStructure.GPIO_Pin = PIN_CLK | PIN_DAT | PIN_LAT | PIN_A | PIN_B;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(PIN_PORT, &GPIO_InitStructure);

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

#if defined(DMD_HUB12) && defined(ENABLE_DMA)
	/*  DMA RCC */
	RCC_AHBPeriphClockCmd(SPI_MASTER_DMA_CLK, ENABLE);
	
	/* Enable DMA1 channel IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if defined(DMD_HUB12) && defined(ENABLE_PWM)
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* Alternative Function IO clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
    /* GPIO pin init for EN */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_EN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)(SystemCoreClock / 24000000) - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = PWM_START_VAL;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);

#elif defined(DMD_HUB75) && defined(ENABLE_PWM)

	uint16_t TimerPeriod = (SystemCoreClock / 17570 ) - 1;
	uint16_t Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);

	/* TIM1 clock & Alternative Function IO clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
    /* GPIO pin init for EN */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/* Channel 1, 2,3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = PWM_START_VAL;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	/* TIM1 counter enable */
	TIM_Cmd(TIM1, ENABLE);
	
	/* TIM1 Main Output Enable */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

#else
    /* GPIO pin init for EN */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_EN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
#endif

#if defined(ENABLE_TIM)
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* Prescaler configuration */
	TIM_PrescalerConfig(TIM3, (uint16_t)(SystemCoreClock / 6000000) - 1, TIM_PSCReloadMode_Immediate);
	
	/* Output Compare Timing Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse = CCR_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
	
	/* TIM1 counter enable */
	TIM_Cmd(TIM3, ENABLE);
	
	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
#else
	/* Systick Handler */
	SysTick_Config((SystemCoreClock / 4000) - 1);
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
		
		dmd_DisplayScan();
	}
#endif
}

void SysTick_Handler(void)
{
#if defined(ENABLE_DMA) && defined(DMD_HUB12)
	uint32_t offset = (DISPLAY_WIDTH / BYTE_SIZE) * DISPLAY_TOTAL * DISPLAY_SCANRATE;

	dmd_DMAStart(&dmd_bDisplayBuffer[offset * dmd_bDisplayScan], offset);
#else
	dmd_DisplayScan();
#endif
}

void TIM3_IRQHandler(void)
{
#ifdef ENABLE_TIM
  if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
	TIM_Cmd(TIM3, DISABLE);
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);

#	if defined(ENABLE_DMA) && defined(DMD_HUB12)
	uint32_t offset = (DISPLAY_WIDTH / BYTE_SIZE) * DISPLAY_TOTAL * DISPLAY_SCANRATE;

	dmd_DMAStart(&dmd_bDisplayBuffer[offset * dmd_bDisplayScan], offset);
	
#	else
	dmd_DisplayScan();
#	endif
  }
#endif
}

void dmd_SendData(uint8_t data)
{	
#if defined(ENABLE_SPI) && defined(DMD_HUB12)
	SPI_I2S_SendData(HUB_SPI, data);
	
	/* Wait for SPI Transfer End */
    while (SPI_I2S_GetFlagStatus(HUB_SPI, SPI_I2S_FLAG_TXE) == RESET);
    
#elif defined(DMD_HUB12)
	int 	i = 0;
	
    for(i = 0; i < 8; i++)
    {
        if(data & 0x01)
        {
			PIN_PORT->BRR  = PIN_DAT;
		}
        else
        {
			PIN_PORT->BSRR = PIN_DAT;
		}
        data >>= 1;
        
        DMD_CLOCK();
    }
#endif
}

void dmd_SendData75(uint16_t nBufferHi, uint16_t nBufferLo)
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

void dmd_DisplayScan()
{	    
#if !defined(ENABLE_DMA) && defined(DMD_HUB12)
    uint16_t 	i = 0;
    uint16_t 	rowsize = (DISPLAY_WIDTH / BYTE_SIZE) * DISPLAY_TOTAL;
    uint16_t 	offsetRow1 = rowsize * dmd_bDisplayScan;
    uint16_t 	offsetRow2 = offsetRow1 + (rowsize * DISPLAY_SCANRATE);
    uint16_t 	offsetRow3 = offsetRow2 + (rowsize * DISPLAY_SCANRATE);
    uint16_t 	offsetRow4 = offsetRow3 + (rowsize * DISPLAY_SCANRATE);
    
    for (i = 0; i < rowsize; i++) 
    {
		dmd_SendData(dmd_bDisplayBuffer[offsetRow4 + i]);
		dmd_SendData(dmd_bDisplayBuffer[offsetRow3 + i]);
		dmd_SendData(dmd_bDisplayBuffer[offsetRow2 + i]);
		dmd_SendData(dmd_bDisplayBuffer[offsetRow1 + i]);
    }

#elif defined(DMD_HUB_12)
	uint32_t	wGpio_Temp	= 0;

#elif defined(DMD_HUB75)
	uint16_t	offsetHi	= DISPLAY_ROWSIZE * DISPLAY_ACROSS * DISPLAY_MODE * dmd_bDisplayScan;
    uint16_t	offsetLo	= DISPLAY_ROWSIZE * DISPLAY_ACROSS * DISPLAY_MODE * (dmd_bDisplayScan + 8);
    uint16_t 	i			= 0;
	uint32_t	wGpio_Temp	= 0;

    for (i = 0; i < DISPLAY_ROWSIZE * DISPLAY_ACROSS * DISPLAY_MODE; i += DISPLAY_MODE) 
    {
		dmd_SendData75(offsetHi + i, offsetLo + i);
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
			
#ifdef DISPLAY_SCANRATE >= 4
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
#endif
	}
	
	DMD_PORT->ODR = (DMD_PORT->ODR & DMD_PORT_MASK) | wGpio_Temp;
	
	DMD_LATCH();
	
	dmd_bDisplayScan++;
    if(dmd_bDisplayScan >= DISPLAY_SCANRATE)
    {
		dmd_bDisplayScan = 0;
	
		dmd_bDisplayBrightness++;
		if(dmd_bDisplayBrightness >= 20)
		{
			dmd_bDisplayBrightness = 0;
		}
	}
}
