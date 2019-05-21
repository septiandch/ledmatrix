#ifndef _I2C_H_
#define _I2C_H_

#include <stm32f10x.h>
#include <stm32f10x_i2c.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

#define I2Cx            	I2C2
#define I2Cx_RCC        	RCC_APB1Periph_I2C2
#define I2C_GPIO_RCC    	RCC_APB2Periph_GPIOB

#define I2Cx_ER_IRQn		I2C2_ER_IRQn
#define I2Cx_ER_IRQHandler	I2C2_ER_IRQHandler

#define I2C_GPIO        	GPIOB
#define I2C_PIN_SDA     	GPIO_Pin_11
#define I2C_PIN_SCL     	GPIO_Pin_10

 
extern void		i2c_init(void);
extern void		i2c_start();
extern void		i2c_stop(void);
extern void		i2c_direction(uint8_t address, uint8_t direction);
extern uint8_t	i2c_read_ack(void);
extern uint8_t	i2c_read_nack(void);
extern void		i2c_transmit(uint8_t byte);
extern void		i2c_write(uint8_t address, uint8_t data);
extern void		i2c_read(uint8_t address, uint8_t* data);

#endif /** _I2C_H_ */
