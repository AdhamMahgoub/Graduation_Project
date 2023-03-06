#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_Interface.h"
#include <string.h>


#define F_CPU 8000000UL
#include <util/delay.h>


struct DataPackage
{
	char x; // 1 byte
	char y; // 1 byte
	char arr[30];
};

void send_DataPackage_char(struct DataPackage *DataPackage_ptr)
{
	UART_TransmitData(DataPackage_ptr->x);
	UART_TransmitData(DataPackage_ptr->y);
}

void send_DataPackege_String(struct DataPackage *DataPackage_ptr)
{
	int i = 0;
	while (DataPackage_ptr->arr[i] != '\0')
	{
		UART_TransmitData(DataPackage_ptr->arr[i]);
		i++;
	}
}

void send_DataPackege_String_with_selector(struct DataPackage *DataPackage_ptr, char selector)
{
	int i = 0;
	char error_message [20] = "incorrect selector";

	switch (selector)
	{
		case 'a':
		while (DataPackage_ptr->arr[i] != '\0')
		{
			UART_TransmitData(DataPackage_ptr->arr[i]);
			i++;
		}
		break;
		default:
			while (error_message[i] != '\0')
			{
				UART_TransmitData(error_message[i]);
				i++;
			}
		break;
	}
}


int main(void)
{

	UART_init();
	
	 /*  Initialize the DataPackage  */
	 struct DataPackage UART;
	 UART.x = 'a';
	 UART.y = 'b';
	 strcpy(UART.arr, "Adham Mahgoub\nEmbedded Systems");

	 //send_DataPackage_char(&UART);
	 //send_DataPackege_String(&UART);
	 send_DataPackege_String_with_selector(&UART,'a');

	 return 0;

	
    while(1)
    {
		 //  
    }
	
	
}