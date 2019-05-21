#include "i2c.h"

void i2c_init()
{
    // Initialization struct
    I2C_InitTypeDef I2C_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
 
    // Step 1: Initialize I2C
	RCC_APB1PeriphClockCmd(I2Cx_RCC, ENABLE);
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_Mode = I2C_Mode_SMBusHost;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2Cx, &I2C_InitStruct);
	I2C_Cmd(I2Cx, ENABLE);
    
	// Step 2: Initialize GPIO as open drain alternate function
	RCC_APB2PeriphClockCmd(I2C_GPIO_RCC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = I2C_PIN_SCL | I2C_PIN_SDA;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_GPIO, &GPIO_InitStruct);
	
	i2c_NVICConfig();
}

void i2c_NVICConfig(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Re-configure and enable I2Cx error interrupt to have the higher priority */
  NVIC_InitStructure.NVIC_IRQChannel = I2Cx_ER_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void I2Cx_ER_IRQHandler(void)
{
	/* Check on I2C2 SMBALERT flag and clear it */
	if (I2C_GetITStatus(I2Cx, I2C_IT_SMBALERT))
	{
		I2C_ClearITPendingBit(I2Cx, I2C_IT_SMBALERT);
	}
	
	/* Check on I2C2 Time out flag and clear it */
	if (I2C_GetITStatus(I2Cx, I2C_IT_TIMEOUT))
	{
		I2C_ClearITPendingBit(I2Cx, I2C_IT_TIMEOUT);
	}
	
	/* Check on I2C2 Arbitration Lost flag and clear it */
	if (I2C_GetITStatus(I2Cx, I2C_IT_ARLO))
	{
		I2C_ClearITPendingBit(I2Cx, I2C_IT_ARLO);
	} 
	
	/* Check on I2C2 PEC error flag and clear it */
	if (I2C_GetITStatus(I2Cx, I2C_IT_PECERR))
	{
		I2C_ClearITPendingBit(I2Cx, I2C_IT_PECERR);
	} 
	
	/* Check on I2C2 Overrun/Underrun error flag and clear it */
	if (I2C_GetITStatus(I2Cx, I2C_IT_OVR))
	{
		I2C_ClearITPendingBit(I2Cx, I2C_IT_OVR);
	} 
	
	/* Check on I2C2 Acknowledge failure error flag and clear it */
	if (I2C_GetITStatus(I2Cx, I2C_IT_AF))
	{
		I2C_ClearITPendingBit(I2Cx, I2C_IT_AF);
	}
	
	/* Check on I2C2 Bus error flag and clear it */
	if (I2C_GetITStatus(I2Cx, I2C_IT_BERR))
	{
		I2C_ClearITPendingBit(I2Cx, I2C_IT_BERR);
	}  
}

void i2c_start()
{
	// Wait until I2Cx is not busy anymore
    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
 
    // Generate start condition
    I2C_GenerateSTART(I2Cx, ENABLE);
 
    // Wait for I2C EV5. 
    // It means that the start condition has been correctly released 
    // on the I2C bus (the bus is free, no other devices is communicating))
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
}
 
void i2c_stop()
{
    // Generate I2C stop condition
    I2C_GenerateSTOP(I2Cx, ENABLE);
    
    // Wait until I2C stop condition is finished
    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));
}
 
void i2c_direction(uint8_t address, uint8_t direction)
{
    // Send slave address
    I2C_Send7bitAddress(I2Cx, address, direction);
 
    // Wait for I2C EV6
    // It means that a slave acknowledges his address
    if (direction == I2C_Direction_Transmitter)
    {
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    }
    else if (direction == I2C_Direction_Receiver)
    { 
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    }
}
 
uint8_t i2c_read_ack()
{
    // Enable ACK of received data
    I2C_AcknowledgeConfig(I2Cx, ENABLE);
    // Wait for I2C EV7
    // It means that the data has been received in I2C data register
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
 
    // Read and return data byte from I2C data register
    return I2C_ReceiveData(I2Cx);
}
 
uint8_t i2c_read_nack()
{
    // Disable ACK of received data
    I2C_AcknowledgeConfig(I2Cx, DISABLE);
    // Wait for I2C EV7
    // It means that the data has been received in I2C data register
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
 
    // Read and return data byte from I2C data register
    return I2C_ReceiveData(I2Cx);
}

void i2c_transmit(uint8_t byte)
{
    // Send data byte
    I2C_SendData(I2Cx, byte);
    // Wait for I2C EV8_2.
    // It means that the data has been physically shifted out and
    // output on the bus)
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

void i2c_write(uint8_t address, uint8_t data)
{
	i2c_start();
    i2c_direction(address << 1, I2C_Direction_Transmitter);
    i2c_transmit(data);
    i2c_stop();
}
 
void i2c_read(uint8_t address, uint8_t* data)
{
	i2c_start();
    i2c_direction(address << 1, I2C_Direction_Receiver);
    *data = i2c_read_nack();
    i2c_stop();
}
