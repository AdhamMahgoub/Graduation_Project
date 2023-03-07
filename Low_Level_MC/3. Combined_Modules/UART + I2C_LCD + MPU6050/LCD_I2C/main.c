#include "Device_Config.h"


#include "MCAL/UART/UART_Interface.h"
#include "MCAL/I2C/MPU6050_I2C_Master.h"

#include "HAL/MPU6050/MPU6050.h"
#include <string.h>

#include <util/delay.h>


extern float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;


int main(void)
{
	UART_init();
	I2C_Init();
	MPU6050_Init();

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


		/*  Initialize the DataPackage  */
		struct DataPackage UART_MPU6050;
		UART_MPU6050.Xa = Xa;
		UART_MPU6050.Ya = Ya;
		UART_MPU6050.Za = Za;
	
		UART_MPU6050.Xg = Xg;
		UART_MPU6050.Yg = Yg;
		UART_MPU6050.Zg = Zg;
		
		UART_MPU6050.t = t;

								
	
		strcpy(UART_MPU6050.arr,  "Xa = ");
		send_DataPackege_String(&UART_MPU6050);
		sprintf(UART_MPU6050.arr, "%.3f", Xa);
		send_DataPackege_String(&UART_MPU6050);
		strcpy(UART_MPU6050.arr,  "         \n\r");
		send_DataPackege_String(&UART_MPU6050);
		
		
		strcpy(UART_MPU6050.arr,  "Ya = ");
		send_DataPackege_String(&UART_MPU6050);
		sprintf(UART_MPU6050.arr, "%.3f", Ya);
		send_DataPackege_String(&UART_MPU6050);
		strcpy(UART_MPU6050.arr,  "         \n\r");
		send_DataPackege_String(&UART_MPU6050);
		
		strcpy(UART_MPU6050.arr,  "Za = ");
		send_DataPackege_String(&UART_MPU6050);
		sprintf(UART_MPU6050.arr, "%.3f", Za);
		send_DataPackege_String(&UART_MPU6050);
		strcpy(UART_MPU6050.arr,  "         \n\r");
		send_DataPackege_String(&UART_MPU6050);
		
		strcpy(UART_MPU6050.arr,  "Xg = ");
		send_DataPackege_String(&UART_MPU6050);
		sprintf(UART_MPU6050.arr, "%.3f", Xg);
		send_DataPackege_String(&UART_MPU6050);
		strcpy(UART_MPU6050.arr,  "         \n\r");
		send_DataPackege_String(&UART_MPU6050);
			
		strcpy(UART_MPU6050.arr,  "Yg = ");
		send_DataPackege_String(&UART_MPU6050);
		sprintf(UART_MPU6050.arr, "%.3f", Yg);
		send_DataPackege_String(&UART_MPU6050);
		strcpy(UART_MPU6050.arr,  "         \n\r");
		send_DataPackege_String(&UART_MPU6050);
				
		strcpy(UART_MPU6050.arr,  "Zg = ");
		send_DataPackege_String(&UART_MPU6050);
		sprintf(UART_MPU6050.arr, "%.3f", Zg);
		send_DataPackege_String(&UART_MPU6050);
		strcpy(UART_MPU6050.arr,  "         \n\r");
		send_DataPackege_String(&UART_MPU6050);

		strcpy(UART_MPU6050.arr,  "t = ");
		send_DataPackege_String(&UART_MPU6050);
		sprintf(UART_MPU6050.arr, "%.3f", t);
		send_DataPackege_String(&UART_MPU6050);
		strcpy(UART_MPU6050.arr,  "         \n\r");
		send_DataPackege_String(&UART_MPU6050);

		strcpy(UART_MPU6050.arr,  "         \n\n\n\n\r");
		send_DataPackege_String(&UART_MPU6050);
		
		 _delay_ms(5000);
		

	
		/*		Send DataPackage		*/
		//send_DataPackage_char(&UART_MPU6050);
		//send_DataPackege_String(&UART_MPU6050);
		//send_DataPackege_String_with_selector(&UART_MPU6050,'a');

	}
	
	return 0;
}