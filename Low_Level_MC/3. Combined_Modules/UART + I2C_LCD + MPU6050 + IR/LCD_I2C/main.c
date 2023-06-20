#include "Device_Config.h"

#include "MCAL/UART/UART_Interface.h"
#include "HAL/MPU6050/MPU6050.h"
//#include "HAL/LCD/liquid_crystal.h"
#include "HAL/IR/IR.h"
#include "HAL/HX711/hx711.h"
#include "HAL/HMC5883L/HMC588L.h"

#include <string.h>
#include <util/delay.h>

#define SELECTOR 3
/*
1. MPU6050
2. HX711
3. IR
4. HMC
5. LCD
*/


int main(void)
{
	UART_init();
	MPU6050_Init();
	/*	MPU6050 Variables	*/
	extern float Xa, Ya, Za, t;												//	Real Value of MPU6050
	extern float Xg, Yg, Zg;												//	Real Values of MPU6050
	extern float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;		//	Raw Values	


	float Heading; 
	Magneto_init();

	while (1)
	{
		
		#if SELECTOR == 1		//	MPU6050
		/*	///////////////////////////////////////////			MPU6050			*///////////////////////////////////////////
		MPU6050_Read_RealValue();		//	Keeps updating the Readings
		/*		MPU6050	DataPackage	*/
		struct DataPackage UART_MPU6050_Package;
		
		strcpy(UART_MPU6050_Package.labels[0], "Xa = ");
		strcpy(UART_MPU6050_Package.labels[1], "Ya = ");
		strcpy(UART_MPU6050_Package.labels[2], "Za = ");
		strcpy(UART_MPU6050_Package.labels[3], "Xg = ");
		strcpy(UART_MPU6050_Package.labels[4], "Yg = ");
		strcpy(UART_MPU6050_Package.labels[5], "Zg = ");
		strcpy(UART_MPU6050_Package.labels[6], "t = ");

		UART_MPU6050_Package.values[0] = Xa;
		UART_MPU6050_Package.values[1] = Ya;
		UART_MPU6050_Package.values[2] = Za;
		UART_MPU6050_Package.values[3] = Xg;
		UART_MPU6050_Package.values[4] = Yg;
		UART_MPU6050_Package.values[5] = Zg;
		UART_MPU6050_Package.values[6] = t;

		strcpy(UART_MPU6050_Package.formats[0], "\n\r");		//	Next line
		strcpy(UART_MPU6050_Package.formats[1], "\n\n\n\r");	//	Next set


//		/*				CALIBRATION				*/
//		//	Calculate the Average for 100 readings for the raw values -- to calibrate
//		int i;
//		float sum[6] = {0};
//		for (i=0; i<100; i++)
//		{
//			Read_RawValue();
//			sum[0] += Acc_x;
//			sum[1] += Acc_y;
//			sum[2] += Acc_z;
//			
//			sum[3] += Gyro_x;
//			sum[4] += Gyro_y;
//			sum[5] += Gyro_z; 
//		}
//		//	printing the average		
//		for (i=0; i<6; i++)
//		{
//			UART_send_float((float)i); UART_puts("== ");
//			UART_send_float(sum[i]/100);
//			UART_puts("average = \n\r");
//		}
//		UART_puts("average = \n\r");
//		/*				End of CALIBRATION				*/



		/*		Sending over UART		*/
		int i;
		for (i=0; i<7; i++)
		{
			if (i==0 || i==1 || i==2  || i==3 || i==4 || i==6)
				continue;
			UART_send_string(UART_MPU6050_Package.labels[i]);
			UART_send_float(UART_MPU6050_Package.values[i]);
			UART_send_string(UART_MPU6050_Package.formats[0]);
		}
		UART_send_string(UART_MPU6050_Package.formats[1]);	//MPU6050
		#endif

		#if SELECTOR == 2		//	HX711
		/*	///////////////////////////////////////////			HX711			*///////////////////////////////////////////
		HX711_main_function();
		#endif

		#if SELECTOR == 3		//	IR
		/*	///////////////////////////////////////////			IR			*///////////////////////////////////////////
				if (IR_Triggered())
					UART_puts("YES\n\r");
				else
					UART_puts("NO\n\r");
					
				_delay_ms(1000);
		
		#endif

		#if SELECTOR == 4		//HMC
			   
			   Heading = Magneto_GetHeading();
			   UART_puts("\n\rHeading = ");	UART_send_float(Heading);
		#endif

		#if SELECTOR == 5 		//	LCD

		/*	///////////////////////////////////////////			LCD			*///////////////////////////////////////////
		//	/*		LCD Initialization		*/
		//	LiquidCrystalDevice_t device1 = lq_init(0x27, 20, 4, LCD_5x8DOTS);	// intialize 4-lines display
		//	lq_turnOnBacklight(&device1);										// simply turning on the backlight
		//	/*	Printing on LCD	*/
		//	lq_print(&device1, "Hello");
		//	lq_setCursor(&device1, 1, 0);					// moving cursor to the next line
		#endif

		_delay_ms(500);
	}

	return 0;
}