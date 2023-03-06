#include "HAL/LCD/liquid_crystal_i2c.h"
#include "HAL/LCD/liquid_crystal_i2c_master.h"



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
	
    while(1)
    {
		//
    }
}