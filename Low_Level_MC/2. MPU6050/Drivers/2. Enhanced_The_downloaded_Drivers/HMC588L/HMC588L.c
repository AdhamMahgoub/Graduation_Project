#define PI	3.14159265359								/* Define Pi value */
#define Declination	-0.00669							/* Define declination of location from where measurement going to be done. e.g. here we have added declination from location Pune city,India. we can get it from http://www.magnetic-declination.com */


#include "STD_TYPES.h"
#include "UART_Interface.h"
#include "I2C_Master_H_file.h"

void Magneto_init()										/* Magneto initialize function */
{
	I2C_Start(0x3C);									/* Start and write SLA+W */
	
	I2C_Write(0x00);									/* Write memory location address */
	UART_TransmitData('1');
	I2C_Write(0x70);									/* Configure register A as 8-average, 15 Hz default, normal measurement */
	UART_TransmitData('2');
	I2C_Write(0xA0);									/* Configure register B for gain */
	UART_TransmitData('3');
	I2C_Write(0x00);									/* Configure continuous measurement mode in mode register */
	UART_TransmitData('4');
	I2C_Stop();											/* Stop I2C */
}

int Magneto_GetHeading()
{
	int x, y, z;
	double Heading;
	I2C_Start_Wait(0x3C);								/* Start and wait for acknowledgment */
	I2C_Write(0x03);									/* Write X register address */
	I2C_Repeated_Start(0x3D);							/* Generate repeat start condition with SLA+R */
	/* Read 16 bit x,y,z value (2’s complement form) */
	x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());
	I2C_Stop();											/* Stop I2C */
	Heading = atan2((double)y,(double)x) + Declination;
	if (Heading>2*PI)									/* Due to declination check for >360 degree */
	Heading = Heading - 2*PI;
	if (Heading<0)										/* Check for sign */
	Heading = Heading + 2*PI;
	return (Heading* 180 / PI);							/* Convert into angle and return */
}
