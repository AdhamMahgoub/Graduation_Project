#include "Device_config.h"

#include "HAL/LCD/liquid_crystal.h"
#include "MCAL/I2C/i2c_master.h"

#include "HAL/MPU6050/MPU6050_private.h"				/* Include MPU6050 register define file */
#include "HAL/MPU6050/MPU6050_I2C_Master.h"				/* Include I2C Master header file */
#include "HAL/MPU6050/MPU6050.h"						/* Include I2C MPU6050 header file */

#include <avr/io.h>										/* Include AVR std. library file */
#include <inttypes.h>									/* Include integer type header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>										/* Include standard library file */

void print_float (LiquidCrystalDevice_t device, float reading)
{
	char str[20];
	sprintf(str, "%.3f", reading);
	lq_print(&device, str);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;

int main(void)
{

	/*		 Initialization	(LCD + MPU6050)		*/
	I2C_Init();															/* Initialize I2C */
	LiquidCrystalDevice_t device = lq_init(0x27, 20, 4, LCD_5x8DOTS);	// intialize 4-lines display
	lq_turnOnBacklight(&device);										// simply turning on the backlight
	
	lq_print(&device, "MPU6050");

	MPU6050_Init();														/* Initialize MPU6050 */

	float Xa,Ya,Za,t;
	float Xg=0,Yg=0,Zg=0;

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
	
	
		/*	printing on lcd		*/	
		lq_print(&device, "Xa=");
		print_float(device, Xa);
		
		lq_print(&device, "Ya=");
		print_float(device, Ya);
		
		lq_print(&device, "Za=");
		print_float(device, Za);

		print_float(device, Xg);
		print_float(device, Yg);
		print_float(device, Zg);
		
		lq_print(&device, "T=");
		print_float(device, t);

		
		_delay_ms(1000);
		lq_clear(&device);
    }
}