#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_Private.h"

#include <avr/io.h>
#include <avr/fuse.h>

#define F_CPU 8000000UL
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
	
	/*
	//Enable RX and TX
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	
	//Setting frame format
	SET_BIT(UCSRC,URSEL);		//Set to select the UCSRC Register instead of UBRRH
	CLR_BIT(UCSRC,UMSEL);		//Asynchronous Mode
	CLR_BIT(UCSRC,UPM1);
	CLR_BIT(UCSRC,UPM0);		//Disable Parity
	CLR_BIT(UCSRC,USBS);		//Selecting 1 BIT for Stop Bits
	CLR_BIT(UCSRB,UCSZ2);
	SET_BIT(UCSRC,UCSZ1);
	SET_BIT(UCSRC,UCSZ0);		//Setting Character size to 8 bits
	
	
	//Setting Baudrate to 9600
	UBRRL = 51;
	CLR_BIT(UCSRC,URSEL);		//Cleared to select the UBRRH Register instead of UCSRC
	UBRRH = 0;
	*/
	
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
