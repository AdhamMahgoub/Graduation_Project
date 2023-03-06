///////////////////////////////////////////////////I2C LCD///////////////////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include <util/twi.h>
#include <stdint.h>

#include "../../Device_config.h"

#include "i2c_master.h"
#define I2C_SCL_FREQUENCY_PRESCALER 1
#define I2C_TWBR_VALUE 
#define I2C_PRESCALER_MASK 0xF8

void i2c_master_init(unsigned long frequency)
{
	TWSR = 0;
	TWBR = (uint8_t)((((F_CPU / frequency) / I2C_SCL_FREQUENCY_PRESCALER) - 16 ) / 2);
}

uint8_t i2c_master_start(uint8_t address, uint8_t mode)
{
	uint8_t   twst;

	// reset control register
	TWCR = 0;

	// transmit START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the start condition was successfully transmitted. Mask prescaler bits.
	twst = TW_STATUS & I2C_PRESCALER_MASK;
	if ( (twst != TW_START) && (twst != TW_REP_START))
	{
		return I2C_STATUS_ERROR_START_WAS_NOT_ACCEPTED;
	}
	
	// load shifted slave address into data register with specified mode
	TWDR = (address << 1) | mode;

	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the device has acknowledged the READ / WRITE mode
	twst = TW_STATUS & I2C_PRESCALER_MASK;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) )
	{
		return I2C_STATUS_ERROR_TRANSMIT_OR_READ_WAS_NOT_ACKNOWLEDGED;
	}
	
	return I2C_STATUS_SUCCESS;
};

uint8_t i2c_master_startWait(uint8_t address, uint8_t mode)
{
	uint8_t twst;

	while (1)
	{
		// send START condition
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		
		// wait until transmission completed
		while(!(TWCR & (1<<TWINT)));
		
		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS & I2C_PRESCALER_MASK;
		if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
		
		// send device address
		TWDR = (address << 1) | mode;
		TWCR = (1<<TWINT) | (1<<TWEN);
		
		// wail until transmission completed
		while(!(TWCR & (1<<TWINT)));
		
		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS & I2C_PRESCALER_MASK;
		if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
		{
			/* device busy, send stop condition to terminate write operation */
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
			
			// wait until stop condition is executed and bus released
			while(TWCR & (1<<TWSTO));
			
			continue;
		}
		break;
	}

	return I2C_STATUS_SUCCESS;
};

uint8_t i2c_master_write(uint8_t data)
{
	uint8_t twst;

	// put data into data register
	TWDR = data;

	// start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS & I2C_PRESCALER_MASK;

	// If Slave device not acknowledged transmission - returns an error
	if( twst != TW_MT_DATA_ACK)
	{
		return I2C_STATUS_ERROR_TRANSMIT_NOT_ACKNOWLEDGED;
	}
	
	return I2C_STATUS_SUCCESS;
}

uint8_t i2c_master_readAck(void)
{
	// start TWI module and acknowledge data after reception
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );

	return TWDR;
}

uint8_t i2c_master_readNack(void)
{
	// start receiving without acknowledging reception
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );

	// return received data from TWDR
	return TWDR;
}

uint8_t i2c_master_send(uint8_t address, uint8_t* data, uint16_t length)
{
	// starts the transmitting
	uint8_t status = i2c_master_start(address, I2C_WRITE);

	// in case of error - returns status code
	if (status) return status;
	
	for (uint16_t i = 0; i < length; i++)
	{
		status = i2c_master_write(data[i]);
		if (status) return status;
	}
	
	i2c_master_stop();
	
	return I2C_STATUS_SUCCESS;
}

uint8_t i2c_master_sendByte(uint8_t address, uint8_t data)
{
	uint8_t status = i2c_master_start(address, I2C_WRITE);
	if (status) return status;

	status = i2c_master_write(data);
	if (status) return status;

	i2c_master_stop();
	
	return I2C_STATUS_SUCCESS;
};

uint8_t i2c_master_receive(uint8_t address, uint8_t* data, uint16_t length)
{
	uint8_t status = i2c_master_start(address, I2C_READ);
	if (status) return status;
	
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2c_master_readAck();
	}
	data[(length-1)] = i2c_master_readNack();
	
	i2c_master_stop();
	
	return I2C_STATUS_SUCCESS;
}

void i2c_master_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
};







///////////////////////////////////////////////////MPU6050///////////////////////////////////////////////////////////////////////////////



void I2C_Init()												/* I2C initialize function */
{
	TWBR = BITRATE(TWSR = 0x00);							/* Get bit rate register value by formula */
}


uint8_t I2C_Start(char slave_write_address)						/* I2C start function */
{
	uint8_t status;											/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status != 0x08)										/* Check weather start condition transmitted successfully or not? */
	return 0;												/* If not then return 0 to indicate start condition fail */
	TWDR = slave_write_address;								/* If yes then write SLA+W in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == 0x18)										/* Check weather SLA+W transmitted & ack received or not? */
	return 1;												/* If yes then return 1 to indicate ack received i.e. ready to accept data byte */
	if (status == 0x20)										/* Check weather SLA+W transmitted & nack received or not? */
	return 2;												/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
	return 3;												/* Else return 3 to indicate SLA+W failed */
}

uint8_t I2C_Repeated_Start(char slave_read_address)			/* I2C repeated start function */
{
	uint8_t status;											/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status != 0x10)										/* Check weather repeated start condition transmitted successfully or not? */
	return 0;												/* If no then return 0 to indicate repeated start condition fail */
	TWDR = slave_read_address;								/* If yes then write SLA+R in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == 0x40)										/* Check weather SLA+R transmitted & ack received or not? */
	return 1;												/* If yes then return 1 to indicate ack received */
	if (status == 0x20)										/* Check weather SLA+R transmitted & nack received or not? */
	return 2;												/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
	return 3;												/* Else return 3 to indicate SLA+W failed */
}

void I2C_Stop()												/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/* Enable TWI, generate stop condition and clear interrupt flag */
	while(TWCR & (1<<TWSTO));								/* Wait until stop condition execution */
}

void I2C_Start_Wait(char slave_write_address)				/* I2C start wait function */
{
	uint8_t status;											/* Declare variable */
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				/* Enable TWI, generate start condition and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (start condition) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != 0x08)									/* Check weather start condition transmitted successfully or not? */
		continue;											/* If no then continue with start loop again */
		TWDR = slave_write_address;							/* If yes then write SLA+W in TWI data register */
		TWCR = (1<<TWEN)|(1<<TWINT);						/* Enable TWI and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (Write operation) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != 0x18 )								/* Check weather SLA+W transmitted & ack received or not? */
		{
			I2C_Stop();										/* If not then generate stop condition */
			continue;										/* continue with start loop again */
		}
		break;												/* If yes then break loop */
	}
}

uint8_t I2C_Write(char data)								/* I2C write function */
{
	uint8_t status;											/* Declare variable */
	TWDR = data;											/* Copy data in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == 0x28)										/* Check weather data transmitted & ack received or not? */
	return 0;												/* If yes then return 0 to indicate ack received */
	if (status == 0x30)										/* Check weather data transmitted & nack received or not? */
	return 1;												/* If yes then return 1 to indicate nack received */
	else
	return 2;												/* Else return 2 to indicate data transmission failed */
}

char I2C_Read_Ack()										/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/* Enable TWI, generation of ack and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}

char I2C_Read_Nack()										/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);								/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}
