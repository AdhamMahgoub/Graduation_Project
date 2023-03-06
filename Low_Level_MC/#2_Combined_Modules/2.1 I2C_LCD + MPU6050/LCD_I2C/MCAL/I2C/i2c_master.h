///////////////////////////////////////////////////I2C_LCD Library///////////////////////////////////////////////////////////////////////////////
#ifndef I2CMASTERDEVICE_H_
#define I2CMASTERDEVICE_H_

#include <stdint.h>

#define I2C_SCL_FREQUENCY_100 100000UL // SCL frequency = 100 kHz
#define I2C_SCL_FREQUENCY_400 400000UL // SCL frequency = 400 kHz

#define I2C_READ 0x01
#define I2C_WRITE 0x00

#define I2C_STATUS_SUCCESS 0
#define I2C_STATUS_ERROR_START_WAS_NOT_ACCEPTED 10
#define I2C_STATUS_ERROR_TRANSMIT_OR_READ_WAS_NOT_ACKNOWLEDGED 20
#define I2C_STATUS_ERROR_TRANSMIT_NOT_ACKNOWLEDGED 21
#define I2C_STATUS_ERROR_READ_NOT_ACKNOWLEDGED 22

/**
 * \brief Returns the string representation of I2C error message by I2C_STATUS_ERROR code.
 * 
 * \param errorCode I2C_STATUS_ERROR code
 * 
 * \return const char* String representation of I2C error message.
 */

/*
const char* i2c_getErrorMessage(uint8_t errorCode)
{
	switch(errorCode)
	{
		case I2C_STATUS_ERROR_START_WAS_NOT_ACCEPTED:
			return "Slave device not accepted START condition";
		case I2C_STATUS_ERROR_TRANSMIT_OR_READ_WAS_NOT_ACKNOWLEDGED:
			return "Slave device not acknowledged WRITE (TRANSMIT) or READ conditions";
		case I2C_STATUS_ERROR_TRANSMIT_NOT_ACKNOWLEDGED:
			return "Slave device not acknowledged WRITE (TRANSMIT) condition";
		case I2C_STATUS_ERROR_READ_NOT_ACKNOWLEDGED:
			return "Slave device not acknowledged READ condition";
	};

	return "Unknown I2C_STATUS_ERROR code";
};

*/

/**
 * \brief Performs the initialization routine for I2C device. 
 *		Should be called just once, before any work with I2C device.
 * 
 * \param unsigned long Frequency for I2C device in Hz. Typically - I2C_SCL_FREQUENCY_100 (100 000 Hz) or I2C_SCL_FREQUENCY_400 (400 000 Hz)
 * 
 * \return void
 */
void i2c_master_init(unsigned long frequency);


/**
 * \brief Sends 1 byte of data to Slave device with specified address. Sends START and STOP conditions.
 * 
 * \param address Typical I2C Slave Device address (not shifted)
 * \param data Byte of data
 * 
 * \return uint8_t On success - I2C_STATUS_SUCCESS. Otherwise - one of I2C_STATUS_ERROR codes.
 */
uint8_t i2c_master_sendByte(uint8_t address, uint8_t data);


/**
 * \brief Sends sequence of data bytes to Slave device with specified address. Sends START and STOP conditions.
 * 
 * \param address Typical I2C Slave Device address (not shifted)
 * \param data Array of bytes for sending
 * \param length Length of byte array
 * 
 * \return uint8_t On success - I2C_STATUS_SUCCESS. Otherwise - one of I2C_STATUS_ERROR codes.
 */
uint8_t i2c_master_send(uint8_t address, uint8_t* data, uint16_t length);


/**
 * \brief Receives the sequence of data bytes from Slave device with specified address. Sends START and STOP conditions.
 * 
 * \param address Typical I2C Slave Device address (not shifted)
 * \param data Buffer of bytes for filling
 * \param length Desired number of bytes for receiving
 * 
 * \return uint8_t
 */
uint8_t i2c_master_receive(uint8_t address, uint8_t* data, uint16_t length);


/**
 * \brief Internal method. Initiates the announcing for Slave devices to be ready for receiving bytes (in write mode) or sending bytes (in read mode)
 * 
 * \param address Typical I2C Slave Device address (not shifted)
 * \param mode Read or write mode (use I2C_READ or I2C_WRITE constants)
 * 
 * \return uint8_t On success - I2C_STATUS_SUCCESS. Otherwise - one of I2C_STATUS_ERROR codes.
 */
uint8_t i2c_master_start(uint8_t address, uint8_t mode);


/**
 * \brief Internal method. Still not used. Initiates the announcing for Slave devices to be ready for receiving bytes (in write mode) or sending bytes (in read mode). 
 *		If Slave device is busy, waits until it will be released.
 * 
 * \param address Typical I2C Device address (not shifted)
 * \param mode Read or write mode (use I2C_READ or I2C_WRITE)
 * 
 * \return uint8_t On success - I2C_STATUS_SUCCESS.
 */
uint8_t i2c_master_startWait(uint8_t address, uint8_t mode);


/**
 * \brief Internal method. Transmits one byte of data to Slave device
 * 
 * \param data Byte of data
 * 
 * \return uint8_t
 */
uint8_t i2c_master_write(uint8_t data);


/**
 * \brief Internal method.Reads 1 byte of data from Slave device and sends ACKNOWLEDGE (ACK) - that means that Master are ready to receive more bytes.
 * 
 * \param No parameters
 * 
 * \return uint8_t Byte of data from Slave device
 */
uint8_t i2c_master_readAck(void);


/**
 * \brief Internal method.Reads 1 byte of data from Slave device and sends NOT ACKNOWLEDGE (NACK) - that means that Master don't want to receive any more bytes.
 * 
 * \param No parameters
 * 
 * \return uint8_t Byte of data from Slave device
 */
uint8_t i2c_master_readNack(void);


/**
 * \brief Internal method. Transmits the STOP signal to slave devices
 * 
 * \param No parameters
 * 
 * \return void
 */
void i2c_master_stop(void);





///////////////////////////////////////////////////MPU6050///////////////////////////////////////////////////////////////////////////////

 #ifndef I2C_MASTER_H_FILE_H_					/* Define library H file if not defined */
 #define I2C_MASTER_H_FILE_H_

 #define F_CPU 8000000UL							/* Define CPU clock Frequency e.g. here its 8MHz */
 #include <avr/io.h>								/* Include AVR std. library file */
 #include <util/delay.h>							/* Include delay header file */
 #include <math.h>								/* Include math function */
 #define SCL_CLK 100000L							/* Define SCL clock frequency */
 #define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */

 void I2C_Init();								/* I2C initialize function */
 uint8_t  I2C_Start(char);						/* I2C start function */
 uint8_t  I2C_Repeated_Start(char);				/* I2C repeated start function */
 void I2C_Stop();								/* I2C stop function */
 void I2C_Start_Wait(char);						/* I2C start wait function */
 uint8_t  I2C_Write(char);						/* I2C write function */
 char I2C_Read_Ack();							/* I2C read ack function */
 char I2C_Read_Nack();							/* I2C read nack function */


 #endif											/* I2C_MASTER_H_FILE_H_ */











#endif /* I2CMASTERDEVICE_H_ */