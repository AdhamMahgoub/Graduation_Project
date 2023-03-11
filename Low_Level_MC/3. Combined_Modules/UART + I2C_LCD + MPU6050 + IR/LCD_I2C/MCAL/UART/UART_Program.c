#include "UART_Private.h"
#include "UART_Interface.h"

#define USART_BAUDRATE  2400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


void UART_init(void)					// A function to initialize UART Communication
{

	UBRRH = (unsigned char)(BAUD_PRESCALE>>8);
	UBRRL = (unsigned char)BAUD_PRESCALE;
	
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);

	// Set frame format: 8data, 1stop bit
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

u8 UART_RecieveData(void)				//A function to Receive Data
{
	while(GET_BIT(UCSRA,RXC)==0);	//wait until all data is received
	return UDR;
}

void UART_send_byte(u8 Data)			//A function to Transmit Char (1 Byte)
{
	while(GET_BIT(UCSRA,UDRE)==0);	//Wait until all data is transmitted
	UDR=Data;
}

void UART_send_string(char *arr)		//A function to Transmit String
{
	int i = 0;
	while (arr[i] != '\0')
	{
		UART_send_byte(arr[i]);
		i++;
	}
}

void UART_send_float(float x)			//A function to Transmit float 
{
	char arr[10] = {0}; 
	sprintf(arr, "%.3f", x);
	UART_send_string(arr);
}







///*		DataPackage Functions		*/
//void UART_send_DataPackage_char(struct DataPackage *DataPackage_ptr)
//{
//	UART_send_byte(DataPackage_ptr->Xa);
//}
//
//void send_DataPackege_String(struct DataPackage *DataPackage_ptr)
//{
//	int i = 0;
//	while (DataPackage_ptr->arr[i] != '\0')
//	{
//		UART_send_byte(DataPackage_ptr->arr[i]);
//		i++;
//	}
//}

