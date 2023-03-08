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
	I2C_Init();											/* Initialize I2C */
	
	
	int reading; 
	char string[10] = "\n\r"; 
	while (1)
	{
		Magneto_init();										/* Initialize magneto */
		reading = Magneto_GetHeading();
		UART_send_float((float)reading);
		UART_send_string(string);
		
	}
}