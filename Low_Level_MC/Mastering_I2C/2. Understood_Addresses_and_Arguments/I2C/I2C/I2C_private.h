#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

#define TWBR *((volatile u8*)0x20)
#define TWCR *((volatile u8*)0x56)
#define TWSR *((volatile u8*)0x21)
#define TWDR *((volatile u8*)0x23)
#define TWAR *((volatile u8*)0x22)

//TWCR Bits

	#define TWINT   7
	#define TWEA    6
	#define TWSTA   5
	#define TWSTO   4 
	#define TWWC    3
	#define TWEN    2
	#define TWIE    0

//TWSR Bits
	//Bits from 7 to 3 are Status bits "TWS"
	//Bit 2 is a Reserved Bit
	#define TWPS1   1
	#define TWPS0   0

//TWAR Bits
	//Bit from 7 to 1 are Address Bits
	#define TWGCE   0
	
//Status
	#define START_Transmit 		0x08
	#define R_Start_Transmit    0x10
	#define SlaveAdd_Write_Ack  0x18
	#define SlaveAdd_Read_Ack   0x40
	#define Data_transmit_Ack   0x28
	#define Data_recieve_Ack    0x50
	
	
#endif