#define PI 3.14159265359
#define Declination 0.0698132

#include "STD_TYPES.h"
#include "UART_Interface.h"
#include "I2C_Master_H_file.h"
#include <string.h>

#define QMC5883L_ADDR 0x0D
#define QMC5883L_REG_CONFIG 0x09
#define QMC5883L_REG_DATA 0x00

void Magneto_init() {
	I2C_Start(QMC5883L_ADDR << 1);			// Start and write SLA+W
	I2C_Write(QMC5883L_REG_CONFIG);         // Write memory location address
	I2C_Write(0x1D);						// Configure register A, set output data rate to 200Hz, set measurement range to 8G, set mode to continuous measurement
	I2C_Stop();                             // Stop I2C
}

char string[100]; //for printing

int Magneto_GetHeading() {
	int x, y, z;
	double Heading;
	I2C_Start_Wait(QMC5883L_ADDR << 1);      // Start and wait for acknowledgment
	I2C_Write(QMC5883L_REG_DATA);            // Write X register address
	I2C_Repeated_Start(QMC5883L_ADDR << 1 | 1); // Generate repeat start condition with SLA+R
	/* Read 16 bit x,y,z value (2’s complement form) */
	x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());

	
	
	I2C_Stop();                             // Stop I2C
	Heading = atan2((double)y, (double)x) + Declination; // Calculate heading
	if (Heading > 2*PI)                      // Due to declination check for >360 degree
	Heading = Heading - 2*PI;
	if (Heading < 0)                         // Check for sign
	Heading = Heading + 2*PI;
	
	
	
	strcpy(string, "x = ");
	UART_send_string(string);
	UART_send_float((float)x);
	strcpy(string, "\t");
	UART_send_string(string);
		
	strcpy(string, "y = ");
	UART_send_string(string);
	UART_send_float((float)y);
	strcpy(string, "\t");
	UART_send_string(string);
		
	strcpy(string, "z = ");
	UART_send_string(string);
	UART_send_float((float)z);
	strcpy(string, "\t");
	UART_send_string(string);
		
	strcpy(string, "Reading = ");
	UART_send_string(string);
	UART_send_float((float)(Heading * 180 / PI));

		
	strcpy(string, "\n\r");
	UART_send_string(string);
	
	
	
	
	
	return (Heading * 180 / PI);             // Convert into angle and return
}
