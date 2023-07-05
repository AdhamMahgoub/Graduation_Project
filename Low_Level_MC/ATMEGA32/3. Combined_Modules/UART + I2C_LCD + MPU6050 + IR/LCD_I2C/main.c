#include "Device_Config.h"

#include "MCAL/UART/UART_Interface.h"
#include "HAL/MPU6050/MPU6050.h"
//#include "HAL/LCD/liquid_crystal.h"
#include "HAL/IR/IR.h"
#include "HAL/HX711/hx711.h"
#include "HAL/HMC5883L/HMC588L.h"

#include <string.h>
#include <util/delay.h>

#define SELECTOR 6
/*
1. MPU6050		>> works
2. HX711		>> works
3. IR			>> works
4. HMC
5. LCD
6. HX711 + IR + MPU6050 + HMC 	   --		Final Mode
*/


int main(void)
{
	UART_init();
	MPU6050_Init();
	/*	MPU6050 Variables	*/
	extern float Xa, Ya, Za, t;												//	Real Value of MPU6050
	extern float Xg, Yg, Zg;												//	Real Values of MPU6050
	extern float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;		//	Raw Values

	/*	HMC	*/
	float Heading;
	Magneto_init();
	
	/*	HxX711	*/
	double weight;

	while (1)
	{
		
		#if SELECTOR == 1		//	MPU6050
		/*	///////////////////////////////////////////			MPU6050			*///////////////////////////////////////////
		MPU6050_Read_RealValue();		//	Keeps updating the Readings


		/*		Sending over UART		*/
		UART_send_string("Xa = ");		UART_send_float(Xa);		UART_send_string("\n\r");
		UART_send_string("Ya = ");		UART_send_float(Ya);		UART_send_string("\n\r");
		UART_send_string("Za = ");		UART_send_float(Za);		UART_send_string("\n\r");
		
		UART_send_string("Xg = ");		UART_send_float(Xg);		UART_send_string("\n\r");
		UART_send_string("Yg = ");		UART_send_float(Yg);		UART_send_string("\n\r");
		UART_send_string("Zg = ");		UART_send_float(Zg);		UART_send_string("\n\r");


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




		#endif

		#if SELECTOR == 2		//	HX711
		/*	///////////////////////////////////////////			HX711			*///////////////////////////////////////////
		
		weight = HX711_main_function();
		char printbuff[100];
		snprintf(printbuff, sizeof(printbuff), "%.3lf", weight);
		UART_send_string("Weight: "); UART_send_string(printbuff); UART_send_string("kg"); UART_send_string("\r\n");
		_delay_ms(200);			// delay must be done >=150ms for the communication to occur
		
		#endif

		#if SELECTOR == 3		//	IR
		/*	///////////////////////////////////////////			IR			*///////////////////////////////////////////
		if (IR_Triggered())
		UART_send_string("1\n\r");
		else
		UART_send_string("0\n\r");
		
		_delay_ms(1000);
		
		#endif

		#if SELECTOR == 4		//HMC
		
		Heading = Magneto_GetHeading();
		UART_send_string("\n\rHeading = ");	UART_send_float(Heading);
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
		
		#if SELECTOR == 6		//	HX711 + IR + MPU6050 + HMC
		
		/*	///////////////////////////////////////////			HX711			*///////////////////////////////////////////
		weight = HX711_main_function();
		char printbuff[100];
		snprintf(printbuff, sizeof(printbuff), "%.3lf", weight);
		UART_send_string("Weight: "); UART_send_string(printbuff); UART_send_string("kg"); UART_send_string("\r\n");
		//_delay_ms(200);			// delay must be done >=150ms for the communication to occur
		
		/*	///////////////////////////////////////////			IR			*///////////////////////////////////////////
		if (IR_Triggered())
		UART_send_string("IR = 1\n\r");
		else
		UART_send_string("IR = 0\n\r");
		//_delay_ms(100);
		
		/*	///////////////////////////////////////////			MPU6050			*///////////////////////////////////////////
		MPU6050_Read_RealValue();		//	Keeps updating the Readings

		/*		Sending over UART		*/
		UART_send_string("Xa = ");		UART_send_float(Xa);		UART_send_string("\n\r");
		UART_send_string("Ya = ");		UART_send_float(Ya);		UART_send_string("\n\r");
		UART_send_string("Za = ");		UART_send_float(Za);		UART_send_string("\n\r");
		
		UART_send_string("Xg = ");		UART_send_float(Xg);		UART_send_string("\n\r");
		UART_send_string("Yg = ");		UART_send_float(Yg);		UART_send_string("\n\r");
		UART_send_string("Zg = ");		UART_send_float(Zg);		UART_send_string("\n\r");
		//_delay_ms(100);
		
		/*	///////////////////////////////////////////			HMC			*///////////////////////////////////////////
		Heading = Magneto_GetHeading();
		UART_send_string("\n\rHeading = ");	UART_send_float(Heading);
		//_delay_ms(100);

		_delay_ms(200);

		
		#endif
		
	}

	return 0;
}