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

	UART_TransmitData('a');	
	_delay_ms(10);
	
	I2C_Init();											/* Initialize I2C */
	_delay_ms(10);
	
	UART_TransmitData('b');
	_delay_ms(10);
	
	Magneto_init();										/* Initialize magneto */
	_delay_ms(10);
	
	UART_TransmitData('c');
	UART_TransmitData('d');
	
	while (1)
	{

		
		//UART_TransmitData((char)Magneto_GetHeading());
	}
}