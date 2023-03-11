#include "Device_Config.h"

#include "MCAL/UART/UART_Interface.h"
#include "HAL/MPU6050/MPU6050.h"
#include "HAL/LCD/liquid_crystal.h"
#include "HAL/IR/IR.h"

#include <string.h>
#include <util/delay.h>

/*	MPU6050 Variables	*/
extern float Acc_x, Acc_y, Acc_z, Temperature, Gyro_x, Gyro_y, Gyro_z;	// Raw Values of MPU6050	(won't use it)
extern float Xa, Ya, Za, t;												//	Real Value of MPU6050s	
extern float Xg, Yg, Zg;												//	Real Values of MPU6050	

//extern struct DataPackage;	 //	Datatype -- used to define a struct with the type DataPackage inside the main function 

int main(void)
{
	
	/*		LCD Initialization		*/
	LiquidCrystalDevice_t device1 = lq_init(0x27, 20, 4, LCD_5x8DOTS);	// intialize 4-lines display
	lq_turnOnBacklight(&device1);										// simply turning on the backlight
	/*	Printing on LCD	*/
	lq_print(&device1, "Hello");
	lq_setCursor(&device1, 1, 0);					// moving cursor to the next line
	
	
	
	UART_init();
	MPU6050_Init();

	char string[] = "Besm Allah";
	UART_send_string(string);

	while (1)
	{

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


		/*		Sending over UART		*/
		int i; 
		for (i=0; i<7; i++)
		{
			UART_send_string(UART_MPU6050_Package.labels[i]);
			UART_send_float(UART_MPU6050_Package.values[i]);
			UART_send_string(UART_MPU6050_Package.formats[0]);
		}
		 UART_send_string(UART_MPU6050_Package.formats[1]);



		_delay_ms(2000);

//		if (IR_Triggered())
//			lq_print(&device1, "YES");
//		else 
//			lq_print(&device1, "NO");
//			
//		lq_clear(&device1);
//	

	}

	return 0;
}