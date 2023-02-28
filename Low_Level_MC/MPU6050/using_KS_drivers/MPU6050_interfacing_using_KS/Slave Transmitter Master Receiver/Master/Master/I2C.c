/*
 * I2C.c
 *
 * Created: 8/12/2021 2:57:30 AM
 *  Author: Kirellos Emad Samir
 */ 

#include "I2C.h"
#define prescaler 1 //1 4 16 64
void I2C_Init(unsigned long SCL_Clock)
{
	TWBR=(unsigned char) (((F_CPU/SCL_Clock)-16)/(2*prescaler));
	if (prescaler == 0)
	TWSR=0;
	
	else if (prescaler == 4)
	TWSR=1;
	
	else if (prescaler == 16)
	TWSR=2;
	
	else if (prescaler == 64)
	TWSR=3;
}

void I2C_Start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (((TWCR &(1<<7))==0));             // wait to finish
	while ((TWSR)!=0x08);                   //Start Condition has Been Transmitted
}
void I2C_Write(unsigned char cByte)
{
	TWDR = cByte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & 0x80)==0);               //wait to finish
}
unsigned char I2C_Read(unsigned char ack)
{
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while ((TWCR & 0x80)==0);     
	return TWDR;
	
}
void I2C_Stop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}