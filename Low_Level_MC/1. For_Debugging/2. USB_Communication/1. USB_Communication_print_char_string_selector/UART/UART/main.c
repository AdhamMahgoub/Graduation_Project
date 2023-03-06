#include "System_Config.h"

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/UART/UART_Interface.h"
#include <string.h>

#include <util/delay.h>


int main(void)
{

	UART_init();
	
	 /*  Initialize the DataPackage  */
	 struct DataPackage UART;
	 UART.x = 'a';
	 UART.y = 'b';
	 strcpy(UART.arr, "Adham Mahgoub\n\rEmbedded Systems\n\rSiemens Digital Industries\n\rGraduation Project 2023");

	 //send_DataPackage_char(&UART);
	 //send_DataPackege_String(&UART);
	 send_DataPackege_String_with_selector(&UART,'a');

	 

	
    while(1)
    {
		 //  
    }
	
	return 0;
}