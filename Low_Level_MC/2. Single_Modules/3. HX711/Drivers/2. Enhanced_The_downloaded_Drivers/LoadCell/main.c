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

//defines running modes
#define HX711_MODERUNNING 1
#define HX711_MODECALIBRATION1OF2 2
#define HX711_MODECALIBRATION2OF2 3
#define HX711_MODECURRENT 1

//2 step calibration procedure
//set the mode to calibration step 1
//read the calibration offset leaving the load cell with no weight
//set the offset to value read
//put a know weight on the load cell and set calibrationweight value
//run the calibration stes 2 of 2	   
//read the calibration scale
//set the scale to value read

//set the gain
int8_t gain = HX711_GAINCHANNELA128;

#if HX711_MODECURRENT == HX711_MODERUNNING
//set the offset
int32_t offset =  8365406;
//set the scale
double scale = 280;


#elif HX711_MODECURRENT == HX711_MODECALIBRATION1OF2
//set the offset
int32_t offset = HX711_OFFSETDEFAULT;
//set the scale
double scale = HX711_SCALEDEFAULT;


#elif HX711_MODECURRENT == HX711_MODECALIBRATION2OF2
//set the offset
int32_t offset =  8365406; 	  
//set the scale
double scale = HX711_SCALEDEFAULT;
//set the calibration weight
double calibrationweight = 60;
#endif



int main(void) {

	UART_init();

	char printbuff[100];

	//init hx711
	hx711_init(gain, scale, offset);


#if HX711_MODECURRENT == HX711_MODERUNNING
	for(;;) {
		//get read
		int32_t read = hx711_read();
		snprintf(printbuff, sizeof(printbuff), "%ld", read);		//	Divided by 100 for easier comparison for the number in printf 
		UART_send_string("Read: "); UART_send_string(printbuff); UART_send_string("\r\n");

		
		//get weight
		double weight = hx711_getweight();
		snprintf(printbuff, sizeof(printbuff), "%lf", weight);
		UART_send_string("Weight: "); UART_send_string(printbuff); UART_send_string("kg"); UART_send_string("\r\n");

		UART_send_string("\r\n");
		
		_delay_ms(10);
	
	}
#elif HX711_MODECURRENT == HX711_MODECALIBRATION1OF2
	for(;;) {
		//set calibration offset
		hx711_calibrate1setoffset();
		int32_t calibrationoffset = hx711_getoffset();
		snprintf(printbuff, sizeof(printbuff), "%ld", calibrationoffset);
		UART_send_string("Calibration offset: "); UART_send_string(printbuff); UART_send_string("\r\n");

		UART_send_string("\r\n");

		_delay_ms(500);
	}
#elif HX711_MODECURRENT == HX711_MODECALIBRATION2OF2
	for(;;) {
		//calibrate
		hx711_calibrate2setscale(calibrationweight);

		//get scale
		double scale = hx711_getscale();
		snprintf(printbuff, sizeof(printbuff), "%lf", scale);
		UART_send_string("Calibration scale: "); UART_send_string(printbuff); UART_send_string("\r\n");

		UART_send_string("\r\n");

		_delay_ms(500);
}
#endif
}
