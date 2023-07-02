#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "uart/uart.h"
#include "xprintf_asm/xprintf_asm.h"
#include "avr-hw-i2c/i2cmaster.h"
#include "qmc5883l/qmc5883l.h"

int main (void)
{
	int16_t mx,my,mz;
	float hdg;

	uart_init(UART_BAUD_SELECT_DOUBLE_SPEED(19200,F_CPU));
	xdev_out(uart_putc);

	xputs(PSTR("AVR QMC5883L demo\n"));
	i2c_init();
	qmc5883l_init();
	sei();
	while(1){
		qmc5883l_getrawdata(&mx,&my,&mz);
		hdg = qmc5883l_calc_heading(mx,my);

		xprintf(PSTR("QMC5883L heading=%3d degr mx=%d my=%d mz=%d  \n"), (int16_t)hdg,mx,my,mz);
		_delay_ms(500);
	}
}

