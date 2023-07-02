#include "MPU6050_private.h"
#include "MPU6050.h"

#include "../../MCAL/I2C/I2C_Master.h"
#include "../../MCAL/UART/UART_Interface.h"


float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;	/* Raw Values	*/
float Xa,Ya,Za,t;			/*	Real Values	*/														
float Xg=0,Yg=0,Zg=0;		/*	Real Values	*/


void MPU6050_Init()										/* Gyro initialization function */
{
	I2C_Init();

	_delay_ms(150);										/* Power up time >100ms */
	
	I2C_Start_Wait(0xD0);								/* Start with device write address */

	I2C_Write(SMPLRT_DIV);								/* Write to sample rate register */
	I2C_Write(0x07);									/* 1KHz sample rate */
	I2C_Stop();


	I2C_Start_Wait(0xD0);
	I2C_Write(PWR_MGMT_1);								/* Write to power management register */
	I2C_Write(0x01);									/* X axis gyroscope reference frequency */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(CONFIG);									/* Write to Configuration register */
	I2C_Write(0x00);									/* Fs = 8KHz */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(GYRO_CONFIG);								/* Write to Gyro configuration register */
	I2C_Write(0x18);									/* Full scale range +/- 2000 degree/C */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_ENABLE);								/* Write to interrupt enable register */
	I2C_Write(0x01);
	I2C_Stop();
}

void MPU_Start_Loc()
{
	I2C_Start_Wait(0xD0);								/* I2C start with device write address */
	I2C_Write(ACCEL_XOUT_H);							/* Write start location address from where to read */
	I2C_Repeated_Start(0xD1);							/* I2C start with device read address */
}

void Read_RawValue()
{
	MPU_Start_Loc();		/* Read Gyro values */
	Acc_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Temperature = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());
	I2C_Stop();
	
	
	/*	Calibration to Compensate for the Offset -- Done by me	*/
	Acc_x += 213;
	Acc_y += 485;
	Acc_z -= 17077;
	
	Gyro_x += 5.33; 	// leave as it is
	Gyro_y -= 63.04;
	Gyro_z -= 1.7;
	
//	UART_puts("Xa_raw = ");		UART_send_float(Acc_x);		UART_puts("\t\t");
//	UART_puts("Ya_raw = ");		UART_send_float(Acc_y);		UART_puts("\t\t");
//	UART_puts("Za_raw = ");		UART_send_float(Acc_z);		UART_puts("\t\t");
//	
//	UART_puts("\n\r");
//	
//	UART_puts("Xg_raw = ");		UART_send_float(Gyro_x);		UART_puts("\t\t");
//	UART_puts("Yg_raw = ");		UART_send_float(Gyro_y);		UART_puts("\t\t");
//	UART_puts("Zg_raw = ");		UART_send_float(Gyro_z);		UART_puts("\t\t");
//	
//	UART_puts("\n\n\r");
	/*	End of Calibration	*/
	
}

void MPU6050_Read_RealValue()
{
	Read_RawValue();								/*	Gets the RawValue in order to make calculations to get Real Values	*/
	
		
	Xa = Acc_x/16384.0;								/* Divide raw value by sensitivity scale factor to get real values */
	Ya = Acc_y/16384.0;
	Za = Acc_z/16384.0;
	
	Xg = Gyro_x/16.4;
	Yg = Gyro_y/16.4;
	Zg = Gyro_z/16.4;

	t = (Temperature/340.00)+36.53;					/* Convert temperature in °/c using formula */
	
	

}


