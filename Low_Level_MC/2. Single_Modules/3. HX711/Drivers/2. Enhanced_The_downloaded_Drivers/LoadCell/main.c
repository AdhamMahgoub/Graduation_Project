//hx711 lib example

#define F_CPU 8000000UL

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//include uart
#define UART_BAUD_RATE 2400
#include "UART_Interface.h"

#include "hx711/hx711.h"


int main(void) {

	UART_init();
	double weight; 
	
	while (1)
	{
		weight = HX711_main_function();
		
		char printbuff[100];
		snprintf(printbuff, sizeof(printbuff), "%.3lf", weight);
		UART_send_string("Weight: "); UART_send_string(printbuff); UART_send_string("kg"); UART_send_string("\r\n");
		_delay_ms(200);			// delay must be done >=150ms for the communication to occur
	}
	
	

}
