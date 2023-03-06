#include "Device_Config.h"

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

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
		struct DataPackage UART;
		UART.Xa = Xa;
		UART.Ya = Ya;
		UART.Za = Za;
	
		UART.Xg = Xg;
		UART.Yg = Yg;
		UART.Zg = Zg;
	

								
	
		strcpy(UART.arr,  "Xa = ");
		send_DataPackege_String(&UART);
		sprintf(UART.arr, "%.3f", Xa);
		send_DataPackege_String(&UART);
		strcpy(UART.arr,  "         \n\r");
		send_DataPackege_String(&UART);
		
		
		strcpy(UART.arr,  "Ya = ");
		send_DataPackege_String(&UART);
		sprintf(UART.arr, "%.3f", Ya);
		send_DataPackege_String(&UART);
		strcpy(UART.arr,  "         \n\r");
		send_DataPackege_String(&UART);
		
		strcpy(UART.arr,  "Za = ");
		send_DataPackege_String(&UART);
		sprintf(UART.arr, "%.3f", Za);
		send_DataPackege_String(&UART);
		strcpy(UART.arr,  "         \n\r");
		send_DataPackege_String(&UART);
		
		strcpy(UART.arr,  "Xg = ");
		send_DataPackege_String(&UART);
		sprintf(UART.arr, "%.3f", Xg);
		send_DataPackege_String(&UART);
		strcpy(UART.arr,  "         \n\r");
		send_DataPackege_String(&UART);
			
		strcpy(UART.arr,  "Yg = ");
		send_DataPackege_String(&UART);
		sprintf(UART.arr, "%.3f", Yg);
		send_DataPackege_String(&UART);
		strcpy(UART.arr,  "         \n\r");
		send_DataPackege_String(&UART);
				
		strcpy(UART.arr,  "Zg = ");
		send_DataPackege_String(&UART);
		sprintf(UART.arr, "%.3f", Zg);
		send_DataPackege_String(&UART);
		strcpy(UART.arr,  "         \n\r");
		send_DataPackege_String(&UART);
		
		strcpy(UART.arr,  "         \n\n\n\n\r");
		send_DataPackege_String(&UART);
		
		 _delay_ms(5000);
		

	
		/*		Send DataPackage		*/
		//send_DataPackage_char(&UART);
		//send_DataPackege_String(&UART);
		//send_DataPackege_String_with_selector(&UART,'a');

	}
	
	return 0;
}