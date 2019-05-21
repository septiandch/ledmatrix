/**
 *  USART Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#include "usart.h"

/* GLOBAL VARIABLES */
volatile char 		usart_sMessage[MESSAGE_MAX_LEN];
volatile uint8_t	usart_nIndex = 0;

/* FUNCTIONS */
void usart_Init(const uint16_t baudrate)
{
    GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	
	/* Configure USART RCC */
	RCC_APB2PeriphClockCmd(USART_RCC | AFIO_RCC, ENABLE);
	
    /* Setup USART NVIC */
    usart_NVICConfig();

	/* Configure PA9 as USART1 TX */
    /* PA9 = alternate function push/pull output */
    GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(USART_GPIO, &GPIO_InitStructure);
    
	/* Configure PA10 as USART1 RX */
    /* PA10 = floating input */
    GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART_GPIO, &GPIO_InitStructure);
    
    /* Configure and initialize usart */
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        
    USART_Init(USARTx, &USART_InitStructure);
    
    /* Enable USART1 */
    USART_Cmd(USARTx, ENABLE);
    
	/* Enable USARTx Receive interrupts */
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
}

void usart_NVICConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USARTx_IRQHandler(void)
{
	if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
	{
		/* Read one byte from the receive data register */
		usart_sMessage[usart_nIndex++] = USART_ReceiveData(USARTx);
		
		if(usart_nIndex >= MESSAGE_MAX_LEN || usart_sMessage[usart_nIndex - 1] == '\0')
		{
			usart_ClearMessage();
		}
		
		USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
	}
}

void usart_ClearMessage(void)
{
	usart_nIndex = 0;
	memset(usart_sMessage, '\0', MESSAGE_MAX_LEN);
}

char usart_GetLastChar(void)
{
	return usart_sMessage[usart_nIndex - 1];
}

void usart_putc(char chr)
{
	USART_SendData(USARTx, chr);
		
	/* Wait until the byte has been transmitted */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

void usart_puts(char *str)
{
	unsigned int	i		= 0;
	unsigned int	len		= strlen(str);
	
	for(i = 0; i < len; i++)
	{
		usart_putc(str[i]);
	}
}

void usart_puti(uint32_t x)
{
  char	value[10]		;
  int	i 			= 0	;
  
  do
  {
    value[i++] = (char)(x % 10) + '0';
    x /= 10;
  } while(x);
  
  /* Send data */
  while(i)
  {
    usart_putc(value[--i]); 
  }
}
