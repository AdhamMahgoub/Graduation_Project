#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"I2C_private.h"

void I2C_Init_Master(void)
{
	//bit rate = 400.000 kbps, F_CPU = 16M   SCL freq= F_CPU/(16+2(TWBR).4^TWPS), TWBR=0x03
	TWBR = 0x03;
	
    //setting prescaller to 1
	CLR_BIT(TWSR,TWPS1);
	CLR_BIT(TWSR,TWPS0);
	
	//Enable I2C
	SET_BIT(TWCR,TWEN);
}

void I2C_Init_Slave(void)
{
	//provide slave address, my address will be 0x01
	TWAR = 0X06;
	
	//Enable I2C
	SET_BIT(TWCR,TWEN);
}

void I2C_Start(void)
{
	//	Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	CLR_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEN);
	
	//	Wait till start condition is transmitted
	while(GET_BIT(TWCR,TWINT)!=1);
	
	//	Check value of TWI Status Register equal to start
	while((TWSR& 0XF8)!=START_Transmit);
}

void I2C_Repeated_Start(void)
{
	//	Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	CLR_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEN);
	
	//	Wait till start condition is transmitted
	while(GET_BIT(TWCR,TWINT)!=1);
	
	//	Check value of TWI Status Register equal to start
	while((TWSR& 0XF8)!=R_Start_Transmit);
}

void I2C_Write_data(u8 data)
{
	// put data in TWDR
	TWDR = data;
	
	//Clear TWI interrupt flag, Enable TWI
	CLR_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	
	//	Wait till complete TWDR byte transmitted
	while(GET_BIT(TWCR,TWINT)!=1);
	
	// Check for the acknowledgment
	while((TWSR& 0XF8)!=Data_transmit_Ack);
}

u8   I2C_Read_data(void)
{
	//	Clear TWI interrupt flag, Enable TWI
	CLR_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	
	//	Wait till complete TWDR byte transmitted
	while(GET_BIT(TWCR,TWINT)!=1);
	
	// Check for the acknowledgment
	while((TWSR& 0XF8)!=Data_recieve_Ack);
	
	// return data
	return TWDR;
}

void I2C_Stop(void)
{
	//	Clear TWI interrupt flag,Put stop condition, Enable TWI
	CLR_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTO);
	SET_BIT(TWCR,TWEN);
}

void I2C_Send_slave_address_with_write_req(u8 slave_address)
{
	//	Address and write instruction
	TWDR=(slave_address<<1);
	CLR_BIT(TWDR,0);
	
	//	Clear TWI interrupt flag, Enable TWI
	CLR_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	
	//	Wait till complete TWDR byte transmitted
	while(GET_BIT(TWCR,TWINT)!=1);
	
	// Check for the acknowledgment
	while((TWSR& 0XF8)!=SlaveAdd_Write_Ack);
}

void I2C_Send_slave_address_with_read_req(u8 slave_address)
{
	//	Address and write instruction
	TWDR=(slave_address<<1);
	SET_BIT(TWDR,0);
	
	//	Clear TWI interrupt flag, Enable TWI
	CLR_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	
	//	Wait till complete TWDR byte transmitted
	while(GET_BIT(TWCR,TWINT)!=1);
	
	// Check for the acknowledgment
	while((TWSR& 0XF8)!=SlaveAdd_Read_Ack);
}
