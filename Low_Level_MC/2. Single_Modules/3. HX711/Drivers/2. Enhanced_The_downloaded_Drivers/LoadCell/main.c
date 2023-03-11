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
	HX711_main_function();


}
