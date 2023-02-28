#include <xc.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_interface.h"


#define F_CPU 8000000UL

int main(void)
{
	 DDRD = 0xFF;
	 I2C_Init_Master();
	 I2C_Start();
	 I2C_Send_slave_address_with_write_req(0x32);			// Argument = Address in hexadecimal / 2
															// if the address is 0x80, the hexadecimal argument will be 0x40
	 I2C_Write_data(0x59);									// The Proteus I2C Debugger shows hexadecimal values
	 I2C_Stop();
	
    while(1)
    {
       
    }
}