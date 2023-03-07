#include "Device_Config.h"

#include "MCAL/UART/UART_Interface.h"
#include "HAL/MPU6050/MPU6050.h"

#include <string.h>
#include <util/delay.h>

extern float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;  // Raw Values of MPU6050	(won't use it) 

extern float Xa,Ya,Za,t;			/*	Real Value of MPU6050s	*/
extern float Xg,Yg,Zg;				/*	Real Values of MPU6050	*/

int main(void)
{
	UART_init();
	MPU6050_Init();

	char string[100] = "Xa = "; 

	while(1)
	{
		
		Read_RealValue();

		UART_send_byte('a');
		
		UART_send_string(string);
		UART_send_float(Xa);





//		/*  Initialize the DataPackage  */
//		struct DataPackage UART_MPU6050;
//		UART_MPU6050.Xa = Xa;
//		UART_MPU6050.Ya = Ya;
//		UART_MPU6050.Za = Za;
//	
//		UART_MPU6050.Xg = Xg;
//		UART_MPU6050.Yg = Yg;
//		UART_MPU6050.Zg = Zg;
//		
//		UART_MPU6050.t = t;
//
//								
//	
//		strcpy(UART_MPU6050.arr,  "Xa = ");
//		send_DataPackege_String(&UART_MPU6050);
//		sprintf(UART_MPU6050.arr, "%.3f", Xa);
//		send_DataPackege_String(&UART_MPU6050);
//		strcpy(UART_MPU6050.arr,  "         \n\r");
//		send_DataPackege_String(&UART_MPU6050);
//		
//		
//		strcpy(UART_MPU6050.arr,  "Ya = ");
//		send_DataPackege_String(&UART_MPU6050);
//		sprintf(UART_MPU6050.arr, "%.3f", Ya);
//		send_DataPackege_String(&UART_MPU6050);
//		strcpy(UART_MPU6050.arr,  "         \n\r");
//		send_DataPackege_String(&UART_MPU6050);
//		
//		strcpy(UART_MPU6050.arr,  "Za = ");
//		send_DataPackege_String(&UART_MPU6050);
//		sprintf(UART_MPU6050.arr, "%.3f", Za);
//		send_DataPackege_String(&UART_MPU6050);
//		strcpy(UART_MPU6050.arr,  "         \n\r");
//		send_DataPackege_String(&UART_MPU6050);
//		
//		strcpy(UART_MPU6050.arr,  "Xg = ");
//		send_DataPackege_String(&UART_MPU6050);
//		sprintf(UART_MPU6050.arr, "%.3f", Xg);
//		send_DataPackege_String(&UART_MPU6050);
//		strcpy(UART_MPU6050.arr,  "         \n\r");
//		send_DataPackege_String(&UART_MPU6050);
//			
//		strcpy(UART_MPU6050.arr,  "Yg = ");
//		send_DataPackege_String(&UART_MPU6050);
//		sprintf(UART_MPU6050.arr, "%.3f", Yg);
//		send_DataPackege_String(&UART_MPU6050);
//		strcpy(UART_MPU6050.arr,  "         \n\r");
//		send_DataPackege_String(&UART_MPU6050);
//				
//		strcpy(UART_MPU6050.arr,  "Zg = ");
//		send_DataPackege_String(&UART_MPU6050);
//		sprintf(UART_MPU6050.arr, "%.3f", Zg);
//		send_DataPackege_String(&UART_MPU6050);
//		strcpy(UART_MPU6050.arr,  "         \n\r");
//		send_DataPackege_String(&UART_MPU6050);
//
//		strcpy(UART_MPU6050.arr,  "t = ");
//		send_DataPackege_String(&UART_MPU6050);
//		sprintf(UART_MPU6050.arr, "%.3f", t);
//		send_DataPackege_String(&UART_MPU6050);
//		strcpy(UART_MPU6050.arr,  "         \n\r");
//		send_DataPackege_String(&UART_MPU6050);
//
//		strcpy(UART_MPU6050.arr,  "         \n\n\n\n\r");
//		send_DataPackege_String(&UART_MPU6050);
//		
//		 _delay_ms(5000);
		

	
		/*		Send DataPackage		*/
		//UART_send_DataPackage_char(&UART_MPU6050);
		//send_DataPackege_String(&UART_MPU6050);
		//send_DataPackege_String_with_selector(&UART_MPU6050,'a');

	}
	
	return 0;
}