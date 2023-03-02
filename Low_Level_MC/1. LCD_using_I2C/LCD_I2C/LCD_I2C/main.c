#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "liquid_crystal_i2c.h"
#include "i2c_master.h"


int main(void)
{
	LiquidCrystalDevice_t device = lq_init(0x27, 20, 4, LCD_5x8DOTS); // intialize 4-lines display

	lq_turnOnBacklight(&device); // simply turning on the backlight

	lq_print(&device, "Adham Mahgoub!");
	lq_setCursor(&device, 1, 0); // moving cursor to the next line
	lq_print(&device, "How are you?");
	
	
	
    while(1)
    {
		//
    }
}