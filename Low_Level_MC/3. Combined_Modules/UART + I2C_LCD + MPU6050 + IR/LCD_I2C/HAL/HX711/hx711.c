#include "hx711.h"

#define F_CPU 8000000UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "../../MCAL/UART/UART_Interface.h"

////////////////////////////////////////////////////////////////START of what was in main.c///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//defines running modes							//	Those was in the main.c 
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
int8_t gain = HX711_GAINCHANNELA64; //HX711_GAINCHANNELA128;			//	When this is increased, sensitivity increases

#if HX711_MODECURRENT == HX711_MODERUNNING
//set the offset
int32_t offset =  8371500;
//set the scale
double scale = 227;


#elif HX711_MODECURRENT == HX711_MODECALIBRATION1OF2
//set the offset
int32_t offset = HX711_OFFSETDEFAULT;
//set the scale
double scale = HX711_SCALEDEFAULT;


#elif HX711_MODECURRENT == HX711_MODECALIBRATION2OF2
//set the offset
int32_t offset =  8371500;
//set the scale
double scale = HX711_SCALEDEFAULT;
//set the calibration weight
double calibrationweight = 60;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HX711_main_function(void)		//	What was in the main.c 
{
		char printbuff[100];

	
		//init hx711
		hx711_init(gain, scale, offset);


		#if HX711_MODECURRENT == HX711_MODERUNNING
		//for(;;) {		Removed the infinite loop 
			//get read
			int32_t read = hx711_read();
			snprintf(printbuff, sizeof(printbuff), "%ld", read);		//	Divided by 100 for easier comparison for the number in printf
			UART_puts("Read: "); UART_send_string(printbuff); UART_puts("\r\n");

			
			//get weight
			double weight = hx711_getweight();
			snprintf(printbuff, sizeof(printbuff), "%lf", weight);
			UART_puts("Weight: "); UART_send_string(printbuff); UART_puts("kg"); UART_puts("\r\n");

			UART_puts("\r\n");
			
			_delay_ms(10);
			
		//}
		#elif HX711_MODECURRENT == HX711_MODECALIBRATION1OF2
		for(;;) { 
			//set calibration offset
			hx711_calibrate1setoffset();
			int32_t calibrationoffset = hx711_getoffset();
			snprintf(printbuff, sizeof(printbuff), "%ld", calibrationoffset);
			UART_puts("Calibration offset: "); UART_send_string(printbuff); UART_puts("\r\n");

			UART_puts("\r\n");

			_delay_ms(500);
		}
		#elif HX711_MODECURRENT == HX711_MODECALIBRATION2OF2
		for(;;) { 
			//calibrate
			hx711_calibrate2setscale(calibrationweight);

			//get scale
			double scale = hx711_getscale();
			snprintf(printbuff, sizeof(printbuff), "%lf", scale);
			UART_puts("Calibration scale: "); UART_send_string(printbuff); UART_puts("\r\n");

			UART_puts("\r\n");

			_delay_ms(500);
		}
		#endif
}		 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////Enf of what was in main.c/////////////////////////////////////////////////////////////////////////////////////////////////////////

//actual gain
static uint8_t hx711_gain = 0;
//actual scale
static double hx711_scale = 0;
//actual offset
static int32_t hx711_offset = 0;




/**
 * read raw value
 */
int32_t hx711_read() {
	uint32_t count = 0;
	uint8_t i = 0;

	//wait for the chip to became ready
	while (HX711_DTPIN & (1<<HX711_DTPINNUM));

#if HX711_ATOMICMODEENABLED == 1
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
#endif
	//read data with a 24 shift
	for(i=0;i<24;i++) {
		HX711_SCKPORT |= (1<<HX711_SCKPINNUM);			//	This sets the corresponding bit of the port to 1, which likely triggers a clock cycle in the external device connected to the port.
		asm volatile("nop");							//	"nop" instruction is executed, likely to allow time for the external device to respond.
		count=count<<1;
		HX711_SCKPORT &= ~(1<<HX711_SCKPINNUM);			//	The value of HX711_SCKPORT is ANDed with the negation of (1<<HX711_SCKPINNUM). This clears the corresponding bit of the port to 0.
		asm volatile("nop");
		if(HX711_DTPIN & (1<<HX711_DTPINNUM))			//	The if statement checks if the HX711_DTPIN has a set bit at the HX711_DTPINNUM position. If true, count is incremented by 1.
			count++;
	}
	count ^= 0x800000;

	//set the channel and the gain			
	for (i=0; i<hx711_gain; i++) {						//	A loop is started where i is incremented from 0 to the value of hx711_gain.
		HX711_SCKPORT |= (1<<HX711_SCKPINNUM);			//	value of HX711_SCKPORT is ORed with (1<<HX711_SCKPINNUM). This sets the corresponding bit of the port to 1, which likely triggers a clock cycle in the external device connected to the port.
		asm volatile("nop");
		HX711_SCKPORT &= ~(1<<HX711_SCKPINNUM);			//	The value of HX711_SCKPORT is ANDed with the negation of (1<<HX711_SCKPINNUM). This clears the corresponding bit of the port to 0. This likely marks the end of the clock cycle.
	}
#if HX711_ATOMICMODEENABLED == 1
	}
#endif

	return count;	 //	Returns Count
}

/**
 * read raw value using average
 */
int32_t hx711_readaverage(uint8_t times) {
	int32_t sum = 0;
	uint8_t i = 0;
	for (i=0; i<times; i++) {
		sum += hx711_read();
	}
	return (int32_t)(sum/times);		//	Correspondes to (sum of counts returned/times) == average of count (what is returned from the read function)
}

/**
 * perform a read excluding tare
 */
double hx711_readwithtare() {
#if HX711_USEAVERAGEONREAD == 1
	return (double)hx711_readaverage(HX711_READTIMES)-(double)hx711_offset;		//	The function returns the difference between the average hx711 output and the hx711_offset value.	 //	This is the Actual Reading
#else
	return (double)hx711_read()-(double)hx711_offset;	//	This is the Actual Reading 
#endif
}

/**
 * get the weight
 */
double hx711_getweight() {
	return hx711_readwithtare()/hx711_scale;			//	in order to convert the raw reading value returned by hx711_read() into a weight measurement in a specific unit (e.g. grams, kilograms, pounds, etc.), we need to divide the raw reading value by the scale factor.
}

/**
 * set the gain
 */
void hx711_setgain(uint16_t gain) {
	//	The function then sets the hx711_gain variable according to the gain value. The gain values are predefined constants HX711_GAINCHANNELA128, HX711_GAINCHANNELA64, and HX711_GAINCHANNELB32.
	if (gain == HX711_GAINCHANNELA128)
		hx711_gain = 1;
	else if (gain == HX711_GAINCHANNELA64)
		hx711_gain = 3;
	else if (gain == HX711_GAINCHANNELB32)
		hx711_gain = 2;
	else
		hx711_gain = 1;

	HX711_SCKPORT &= ~(1<<HX711_SCKPINNUM);
	hx711_read();
}

/**
 * get the actual gain
 */
uint16_t hx711_getgain() {
	return hx711_gain;		//	The hx711_getgain() function returns the gain value, which is used to calculate the Weight value.
							//	Scale is used in hx711_getweight()
}

/**
 * set the scale to use
 */
void hx711_setscale(double scale) {
	hx711_scale = scale;
}

/**
 * get the actual scale
 */
double hx711_getscale() {
	return hx711_scale;
}

/**
 * set the offset raw value
 */
void hx711_setoffset(int32_t offset) {
	hx711_offset = offset;
}

/**
 * get the actual offset
 */
int32_t hx711_getoffset() {
	return hx711_offset;
}

/**
 * set tare to zero
 */
void hx711_taretozero() {
#if HX711_USEAVERAGEONREAD == 1
	double sum = hx711_readaverage(HX711_READTIMES);
#else
	double sum = hx711_read();
#endif
	hx711_setoffset(sum);
}

/**
 * power down the chip
 */
void hx711_powerdown() {
	HX711_SCKPORT &= ~(1<<HX711_SCKPINNUM);
	HX711_SCKPORT |= (1<<HX711_SCKPINNUM);
}

/**
 * power up the chip
 */
void hx711_powerup() {
	HX711_SCKPORT &= ~(1<<HX711_SCKPINNUM);
}

/**
 * calibration step 1 of 2, set the offset for tare zero
 */
void hx711_calibrate1setoffset() {
	hx711_setoffset(hx711_readaverage(HX711_CALIBRATIONREADTIMES));
}

/**
 * calibration step 2 of 2, set the scale
 */
void hx711_calibrate2setscale(double weight) {
	hx711_setscale((hx711_readaverage(HX711_CALIBRATIONREADTIMES)-hx711_offset)/weight);
}

/**
 * initialize chip
 */
void hx711_init(uint8_t gain, double scale, int32_t offset) {
	//set sck as output
	HX711_SCKDDR |= (1<<HX711_SCKPINNUM);
	HX711_SCKPORT &= ~(1<<HX711_SCKPINNUM);
	
	//set dt as input
	HX711_DTDDR &=~ (1<<HX711_DTPINNUM);

	//set gain
	hx711_setgain(gain);
	//set scale
	hx711_setscale(scale);
	//set offset
	hx711_setoffset(offset);
}
