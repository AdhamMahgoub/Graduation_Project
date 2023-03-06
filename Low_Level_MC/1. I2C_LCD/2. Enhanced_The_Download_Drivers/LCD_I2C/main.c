#include "HAL/LCD/liquid_crystal.h"
#include "MCAL/I2C/i2c_master.h"

void print_float (float reading, LiquidCrystalDevice_t device)
{
	char str[20];
	sprintf(str, "%.3f", reading);
	lq_print(&device, str);
}


int main(void)
{
	
	/*		LCD Initialization		*/
	LiquidCrystalDevice_t device1 = lq_init(0x27, 20, 4, LCD_5x8DOTS);	// intialize 4-lines display
	lq_turnOnBacklight(&device1);										// simply turning on the backlight

	/*	Printing on LCD	*/
	lq_print(&device1, "Adham Mahgoub!");
	lq_setCursor(&device1, 1, 0);					// moving cursor to the next line	
	print_float(3.14567, device1);
	

	
    while(1)
    {
		//
    }
}


