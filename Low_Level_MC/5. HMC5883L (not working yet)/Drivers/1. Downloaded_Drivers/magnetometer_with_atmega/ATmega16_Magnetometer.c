/*
 * ATmega16_Magnetometer.c
 * http://www.electronicwings.com
 * 
 */ 

#define F_CPU 8000000UL									/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>										/* Include AVR std. library file */
#include <stdlib.h>										/* Include std. library file */
#include <math.h>										/* Include math header file */
#include "LCD_16x2_H_file.h"							/* Include LCD header file */
#include "I2C_Master_H_file.h"							/* Include I2C header file */
#define PI	3.14159265359								/* Define Pi value */
#define Declination	-0.00669							/* Define declination of location from where measurement going to be done. e.g. here we have added declination from location Pune city,India. we can get it from http://www.magnetic-declination.com */

void Magneto_init()										/* Magneto initialize function */
{
	I2C_Start(0x3C);									/* Start and write SLA+W */
	I2C_Write(0x00);									/* Write memory location address */
	I2C_Write(0x70);									/* Configure register A as 8-average, 15 Hz default, normal measurement */
	I2C_Write(0xA0);									/* Configure register B for gain */
	I2C_Write(0x00);									/* Configure continuous measurement mode in mode register */
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


int main(void)
{
	char buffer[10];
	LCD_Init();											/* Initialize LCD */
	I2C_Init();											/* Initialize I2C */
	Magneto_init();										/* Initialize magneto */
	LCD_String("Magnetometer");							/* Print title on LCD */
	while (1)
	{
		itoa (Magneto_GetHeading(),buffer,10);
		LCD_String_xy(2,0,"Heading = ");				/* Print Heading on 2nd row of LCD */
		LCD_String(buffer);
		LCD_Char(0xDF);									/* ASCII of Degree symbol */
		LCD_String("   ");
	}
}