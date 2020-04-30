/**
 *  USART Library
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include "utils.h"

/*----- Defines -----*/
#define USARTx				USART1
#define USARTx_IRQn			USART1_IRQn
#define USARTx_IRQHandler	USART1_IRQHandler
#define	USART_GPIO			GPIOA
#define USART_TX_PIN		GPIO_Pin_9
#define USART_RX_PIN		GPIO_Pin_10
#define USART_RCC			RCC_APB2Periph_USART1
#define AFIO_RCC			RCC_APB2Periph_AFIO
	
#define USART_DATA_SIZE		500

/*----- Global Variables -----*/
extern volatile char		usart_sMessage[USART_DATA_SIZE];
extern volatile uint8_t		usart_nIndex;

/*----- Function Prototypes -----*/
extern void	usart_init(const uint16_t baudrate);
extern void	usart_putc(char chr);
extern void	usart_puts(char *str);
extern void	usart_puti(uint32_t x);
extern void usart_message_retrieve(char *pcString);
extern void usart_message_clear(void);
extern char usart_get_lastchar(void);

#endif	/* _USART_H_ */
