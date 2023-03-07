#ifndef UART_INTERFACE
#define UART_INTERFACE

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../Device_Config.h"

struct DataPackage
{
	char Xa; // 1 byte
	char Ya; // 1 byte
	char Za; // 1 byte
	char Xg; // 1 byte
	char Yg; // 1 byte
	char Zg; // 1 byte
	char t; // 1 byte

	char arr[30];
};

void UART_init(void);
u8 UART_RecieveData(void);
void UART_send_byte(u8 Data);
void UART_send_string(char *arr);
void UART_send_float(float x);


void UART_send_DataPackage_char(struct DataPackage *DataPackage_ptr);
void send_DataPackege_String(struct DataPackage *DataPackage_ptr);

#endif
