#include "../../System_Config.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "UART_Private.h"

#include <avr/io.h>
#include <avr/fuse.h>

#define USART_BAUDRATE  2400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


// A function to initialize UART Communication
void UART_init(void){

	UBRRH = (unsigned char)(BAUD_PRESCALE>>8);
	UBRRL = (unsigned char)BAUD_PRESCALE;
	
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);

	// Set frame format: 8data, 1stop bit
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

//A function to Transmit Data
void UART_TransmitData(u8 Data){
	while(GET_BIT(UCSRA,UDRE)==0);	//Wait until all data is transmitted
	UDR=Data;
}

//A function to Receive Data
u8 UART_RecieveData(void){
	while(GET_BIT(UCSRA,RXC)==0);	//wait until all data is received
	return UDR;
}