#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_Interface.h"


#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
		UART_init();
	
	char test = 'b';
	


    while(1)
    {
		 UART_TransmitData(test);	
		 _delay_ms(10);  
    }
	
	
}