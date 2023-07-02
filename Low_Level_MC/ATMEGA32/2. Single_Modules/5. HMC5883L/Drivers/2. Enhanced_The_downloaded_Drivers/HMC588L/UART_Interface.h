#ifndef UART_INTERFACE
#define UART_INTERFACE

#include "STD_TYPES.h"
#include "BIT_MATH.h"

struct DataPackage
{
	char arr[30];

	char labels[7][10];
	char formats[7][10];
	float values [7];
};


void UART_init(void);
u8 UART_RecieveData(void);
void UART_send_byte(u8 Data);
void UART_send_string(char *arr);
void UART_send_float(float x);


//void UART_send_DataPackage_char(struct DataPackage *DataPackage_ptr);
//void send_DataPackege_String(struct DataPackage *DataPackage_ptr);

#endif
