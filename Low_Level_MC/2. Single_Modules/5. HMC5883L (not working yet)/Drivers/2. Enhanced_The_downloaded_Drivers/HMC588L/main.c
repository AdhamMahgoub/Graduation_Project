#define F_CPU 8000000UL									/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>										/* Include AVR std. library file */
#include <stdlib.h>										/* Include std. library file */
#include <math.h>										/* Include math header file */
#include <util/delay.h>

#include "STD_TYPES.h"
#include "UART_Interface.h"
#include "I2C_Master_H_file.h"					/* Include I2C header file */
#include "HMC588L.h"




int main(void)
{
	UART_init();

	_delay_ms(10);
	
	I2C_Init();											/* Initialize I2C */
	_delay_ms(10);
	
	
	Magneto_init();										/* Initialize magneto */
	_delay_ms(10);
	
	
	int reading; 
	reading = Magneto_GetHeading();				// Has a problemo

	while (1)
	{
		UART_send_float((float)reading);
		
	}
}