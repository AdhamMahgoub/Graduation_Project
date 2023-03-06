#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#define 	PORTA		0
#define 	PORTB		1
#define 	PORTC		2
#define 	PORTD		3

#define 	OUTPUT 		1
#define 	INPUT 		0

#define 	HIGH		1
#define 	LOW			0

#define 	PIN0		0
#define 	PIN1		1
#define 	PIN2		2
#define 	PIN3		3
#define 	PIN4		4
#define 	PIN5		5
#define 	PIN6		6
#define 	PIN7		7

/* Explanation -- Examples
		example: DIO_voidSetPinDirection	(PORTA, PIN0, OUTPUT)	
		example: DIO_voidSetPinValue		(PORTA, PIN0, HIGH)			
		example: DIO_u8GetPinValue			(PORTA, PIN0)	
		example: DIO_voidSetPortValue		(PORTA, NUMBER 'BINARY')
		example: DIO_voidSetPortDirection	(PORTA, 'BINARY')
*/		

void DIO_voidSetPinDirection (u8 PORTID, u8 PINID, u8 Direction);
void DIO_voidSetPinValue (u8 PORTID, u8 PINID, u8 value);
u8 DIO_u8GetPinValue (u8 PORTID, u8 PINID);


void DIO_voidSetPortValue(u8 PORTID, u8 Value);
void DIO_voidSetPortDirection(u8 PORTID, u8 Direction);


 

#endif