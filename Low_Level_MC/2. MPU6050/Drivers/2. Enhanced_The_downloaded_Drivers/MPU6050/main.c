#define F_CPU 8000000UL									/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>										/* Include AVR std. library file */
#include <inttypes.h>									/* Include integer type header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>										/* Include standard library file */
#include "HAL/MPU6050/MPU6050_private.h"				/* Include MPU6050 register define file */
#include "HAL/MPU6050/MPU6050_I2C_Master.h"				/* Include I2C Master header file */
#include "HAL/MPU6050/MPU6050.h"						/* Include I2C MPU6050 header file */


extern float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;


int main()
{
	float Xa,Ya,Za,t;
	float Xg=0,Yg=0,Zg=0;
	I2C_Init();											/* Initialize I2C */
	MPU6050_Init();										/* Initialize MPU6050 */
	
	while(1)
	{
		Read_RawValue();

		Xa = Acc_x/16384.0;								/* Divide raw value by sensitivity scale factor to get real values */
		Ya = Acc_y/16384.0;
		Za = Acc_z/16384.0;
		
		Xg = Gyro_x/16.4;
		Yg = Gyro_y/16.4;
		Zg = Gyro_z/16.4;

		t = (Temperature/340.00)+36.53;					/* Convert temperature in °/c using formula */
	}
}
