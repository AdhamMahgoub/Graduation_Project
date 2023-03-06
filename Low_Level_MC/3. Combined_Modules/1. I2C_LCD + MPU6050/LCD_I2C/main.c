/*			LCD				*/
#include "HAL/LCD/liquid_crystal_i2c.h"
#include "HAL/LCD/liquid_crystal_i2c_master.h"
/*			MPU	6050		*/
#define F_CPU 8000000UL									/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>										/* Include AVR std. library file */
#include <inttypes.h>									/* Include integer type header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>										/* Include standard library file */
#include "HAL/MPU6050/MPU6050_private.h"				/* Include MPU6050 register define file */
#include "HAL/MPU6050/MPU6050_I2C_Master.h"				/* Include I2C Master header file */
#include "HAL/MPU6050/MPU6050.h"						/* Include I2C MPU6050 header file */
extern float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;

int main(void)
{
	
	/*		LCD Initialization		*/
	LiquidCrystalDevice_t device = lq_init(0x27, 20, 4, LCD_5x8DOTS); // intialize 4-lines display
	lq_turnOnBacklight(&device); // simply turning on the backlight

	//lq_print(&device, "Adham Mahgoub!");
	//lq_setCursor(&device, 1, 0); // moving cursor to the next line
	
	/*	To Convert a Number from float to array of characters "string"	
	float n=3.14; 
	char str[20]; 
	sprintf(str, "%.3f", n);
	lq_print(&device, str);
	*/
	
	
	float Xa,Ya,Za,t;
	float Xg=0,Yg=0,Zg=0;
	float Xa_arr[5], Ya_arr[5],Za_arr[5],t_arr[5];						//	making arrays to be able to print float
	float Xg_arr[5], Yg_arr[5],Zg_arr[5];							//	making arrays to be able to print float
	
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
	
		
		sprintf(Xa_arr, "%.1f", Xa);
		sprintf(Ya_arr, "%.1f", Ya);
		sprintf(Za_arr, "%.1f", Za);
		sprintf(Xg_arr, "%.1f", Xg);
		sprintf(Yg_arr, "%.1f", Yg);
		sprintf(Zg_arr, "%.1f", Zg);
		sprintf(t_arr, "%.1f", t);
		
		/*	printing on lcd		*/		
		lq_print(&device, "xa=");		
		lq_print(&device, Xa_arr);	 
		lq_print(&device, "Ya=");
		lq_print(&device, Ya_arr);
		lq_setCursor(&device, 1, 0); // moving cursor to the next line
		lq_print(&device, "Za=");
		lq_print(&device, Za_arr);
		
		_delay_ms(1000);
		lq_clear(&device);
    }
}