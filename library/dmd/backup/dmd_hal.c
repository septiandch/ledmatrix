/**
 *  DMD Hardware Access Layer Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "dmd_hal.h"

/* FUNCTION PROTOTYPES */
void	dmdhal_scan(void);
void	dmdhal_send_data(uint8_t _data);
void	dmdhal_send_datargb(uint16_t nBufferHi, uint16_t nBufferLo);

/* GLOBAL VARIABLES */
stDisplayProp	stDispProp;
uint8_t 		pbDmdBuffer[DISPLAY_DATA_SIZE];
uint8_t 		bDisplayScan;

void dmdhal_init(uint8_t mode, uint8_t scanrate, uint8_t width, uint8_t height, uint8_t panelAcross, uint8_t panelDown)
{
    GPIO_InitTypeDef		GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
    SPI_InitTypeDef			SPI_InitStructure;

	/* Display Parameter Initialization */
	stDispProp.bMode			= mode;
	stDispProp.bScanrate		= scanrate;
	stDispProp.bWidth			= width;
	stDispProp.bHeight			= height;
	stDispProp.bPanelAcross		= panelAcross;
	stDispProp.bPanelDown		= panelDown;
	stDispProp.bPanelCount		= panelAcross * panelDown;
	stDispProp.nRowSize			= (uint16_t)(width / 8) ;

	bDisplayScan			= 0;

#if defined(DMD_HUB12_SUPPORT)
	/*  GPIO RCC */
	RCC_APB2PeriphClockCmd(DMD_RCC, ENABLE);

#	if defined(ENABLE_SPI)
	/*  GPIO & SPI RCC */
    RCC_APB2PeriphClockCmd(DMD_SPI_RCC, ENABLE);
	
	/* Alternative Function IO clock enable */
	RCC_APB2PeriphClockCmd(DMD_SPI_AFIO_RCC, ENABLE);
	
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
	SPI_InitStructure.SPI_Direction	= SPI_Direction_1Line_Tx;
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

#	else
    /* GPIO pin init for DAT, CLK, SS (LAT) & A, B (Output Mode) */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_CLK | DMD_PIN_DAT | DMD_PIN_LAT | DMD_PIN_A | DMD_PIN_B;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PORT, &GPIO_InitStructure);
#	endif

#	if defined(ENABLE_DMA)
	/*  DMA RCC */
	RCC_AHBPeriphClockCmd(DMD_DMA_SPI_RCC, ENABLE);
	
	/* Enable DMA1 channel IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMD_DMA_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#	endif

#elif defined(DMD_HUB75_SUPPORT)
	/*  GPIO RCC */
	DMD_SCN_APBClockCmd(DMD_GPIO_SCN_RCC, ENABLE);
	DMD_APBClockCmd(DMD_RCC, ENABLE);
        
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
	TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD;
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
	RCC_APB2PeriphClockCmd(DMD_RCC_EN, ENABLE);

    /* GPIO pin init for EN */
	GPIO_InitStructure.GPIO_Pin = DMD_PIN_EN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DMD_PORT_EN, &GPIO_InitStructure);
#endif

#if defined(ENABLE_TIM)
	/* TIM clock enable */
	TIMx_APBClockCmd(TIMx_RCC, ENABLE);
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 5000;
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
#elif defined(ENABLE_PWM)
	/* Systick Handler */
	SysTick_Config((SystemCoreClock / 500) - 1);
#else
	/* Systick Handler */
	SysTick_Config((SystemCoreClock / 17570) - 1);
#endif
}

void dmdhal_DMAConfig(uint8_t *data, uint32_t data_size)
{	
#ifdef ENABLE_DMA
	DMA_InitTypeDef  DMA_InitStructure;
	
	DMA_DeInit(DMD_DMA_SPI_CH);
	
	/* DMA1 channel3 configuration */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) DMD_SPI_MASTER_DR_Base;
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
	DMA_Init(DMD_DMA_SPI_CH, &DMA_InitStructure);
	
	/* Enable DMAx Channeln Transfer Complete interrupt */
	DMA_ITConfig(DMD_DMA_SPI_CH, DMA_IT_TC, ENABLE);
#endif
}

void dmdhal_DMAStart(uint8_t *data, uint32_t data_size)
{
#ifdef ENABLE_DMA
	dmdhal_DMAConfig(data, data_size);
	
	SPI_I2S_DMACmd(DMD_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
	DMA_Cmd(DMD_DMA_SPI_CH, ENABLE);
#endif
}

void DMD_DMA_IRQHandler(void)
{
#ifdef ENABLE_DMA
	//DMAx Channelx Transfer Complete interrupt
	if(DMA_GetITStatus(DMD_DMA_IT_TC))
	{
		//Clear DMAx Channelx Half Transfer, Transfer Complete and Global interrupt pending bits
		DMA_ClearITPendingBit(DMD_DMA_IT_TC);
		DMA_Cmd(DMD_DMA_SPI_CH, DISABLE);
		
		dmdhal_scan();
	}
#endif
}

void SysTick_Handler(void)
{
#if defined(ENABLE_DMA) && defined(DMD_HUB12_SUPPORT)
	uint32_t offset	= (stDispProp.bWidth / 8) * stDispProp.bPanelCount * stDispProp.bScanrate;

	dmdhal_DMAStart(&pbDmdBuffer[offset * bDisplayScan], offset);
#else
	dmdhal_scan();
#endif
}

void TIMx_IRQHandler(void)
{
#ifdef ENABLE_TIM
 	if(TIM_GetITStatus(TIMx, TIM_IT_Update) != RESET)
	{
    	TIM_ClearITPendingBit(TIMx, TIM_IT_Update);

#	if defined(ENABLE_DMA) && defined(DMD_HUB12_SUPPORT)
		uint32_t offset	= (stDispProp.bWidth / 8) * stDispProp.bPanelCount * stDispProp.bScanrate;

		dmdhal_DMAStart(&pbDmdBuffer[offset * bDisplayScan], offset);
#	else
		dmdhal_scan();
#	endif
	}
#endif
}

void dmdhal_send_data(uint8_t data)
{	
#if defined(ENABLE_SPI) && defined(DMD_HUB12_SUPPORT)
	SPI_I2S_SendData(DMD_SPI, data);
	
	/* Wait for SPI Transfer End */
    while (SPI_I2S_GetFlagStatus(DMD_SPI, SPI_I2S_FLAG_TXE) == RESET);
    
#elif defined(DMD_HUB12_SUPPORT)
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

void dmdhal_send_datargb(uint16_t nBufferHi, uint16_t nBufferLo)
{
#if defined(DMD_HUB75_SUPPORT)
	uint8_t		i			= 0;
	uint8_t		dataMask	= 0x01;
	uint32_t	wGpio_Temp	= 0x00000000;
	
	for(i = 0; i < 8; i++)
	{
		wGpio_Temp = 0x00000000;
		
		if(pbDmdBuffer[nBufferHi + 0] & dataMask) wGpio_Temp |= DMD_PIN_R1;
		if(pbDmdBuffer[nBufferHi + 1] & dataMask) wGpio_Temp |= DMD_PIN_G1;
		if(pbDmdBuffer[nBufferHi + 2] & dataMask) wGpio_Temp |= DMD_PIN_B1;
		
		if(pbDmdBuffer[nBufferLo + 0] & dataMask) wGpio_Temp |= DMD_PIN_R2;
		if(pbDmdBuffer[nBufferLo + 1] & dataMask) wGpio_Temp |= DMD_PIN_G2;
		if(pbDmdBuffer[nBufferLo + 2] & dataMask) wGpio_Temp |= DMD_PIN_B2;

		DMD_PORT_DAT->ODR = (DMD_PORT_DAT->ODR & DMD_PORT_DAT_MASK) | wGpio_Temp;
		
		dataMask <<= 1;

		DMD_CLOCK();
	}
#endif
}

void dmdhal_set_brightness(uint8_t percentage)
{
#if defined(ENABLE_PWM)
	uint16_t value = ((uint16_t)(PWM_PERIOD * (100 - percentage)) / 100);
	
	PWM_SetCompare(PWM_TIM, value);
#elif defined(ENABLE_BCM)
	dmdhal_bBrightnessValue = (uint8_t)((uint16_t)(255 * (percentage + 1)) / 100);
#endif
}

void dmdhal_scan(void)
{
	uint32_t	wGpio_Temp	= 0;
	
#if !defined(ENABLE_DMA) && defined(DMD_HUB12_SUPPORT)
	uint16_t	i = 0;
    uint16_t 	offsetRow1	= (uint16_t)(stDispProp.nRowSize * bDisplayScan);
    uint16_t 	offsetRow2	= offsetRow1 + (uint16_t)(stDispProp.nRowSize * stDispProp.bScanrate);
    uint16_t 	offsetRow3	= offsetRow2 + (uint16_t)(stDispProp.nRowSize * stDispProp.bScanrate);
    uint16_t 	offsetRow4	= offsetRow3 + (uint16_t)(stDispProp.nRowSize * stDispProp.bScanrate);
    
    for (i = 0; i < stDispProp.nRowSize; i++) 
    {
		dmdhal_send_data(pbDmdBuffer[offsetRow4 + i]);
		dmdhal_send_data(pbDmdBuffer[offsetRow3 + i]);
		dmdhal_send_data(pbDmdBuffer[offsetRow2 + i]);
		dmdhal_send_data(pbDmdBuffer[offsetRow1 + i]);
    }

#elif defined(DMD_HUB75_SUPPORT)
	uint16_t 	i			= 0;
	uint16_t 	j			= 0;
	uint16_t	offsBase	= stDispProp.nRowSize * stDispProp.bPanelAcross * stDispProp.bMode;
	uint8_t		offsCount	= (uint8_t)(stDispProp.bHeight / stDispProp.bScanrate);
	uint8_t		offsMapHi[]	= {0, 4, 16, 20};
	uint8_t		offsMapLo[]	= {8, 12, 24, 28};

	uint16_t	offsHi[offsCount];
	uint16_t	offsLo[offsCount];

	/* Offset value setup */
	for(i = 0; i < offsCount; i++)
    {
		offsHi[i] = offsBase * (bDisplayScan + offsMapHi[i]);
		offsLo[i] = offsBase * (bDisplayScan + offsMapLo[i]);
	}

	/* Send out data */
	for(j = offsCount; j > 0; j-=2)
    {
		for (i = 0; i < stDispProp.nRowSize * stDispProp.bPanelAcross * stDispProp.bMode; i += stDispProp.bMode) 
    	{
			dmdhal_send_datargb(offsHi[j-1] + i, offsLo[j-1] + i);
			dmdhal_send_datargb(offsHi[j-2] + i, offsLo[j-2] + i);
    	}
	}
#endif
	
	switch (bDisplayScan)
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

	bDisplayScan++;
	if(bDisplayScan >= stDispProp.bScanrate)
	{
		bDisplayScan = 0;
	}
}
