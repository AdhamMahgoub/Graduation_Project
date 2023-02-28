/*
 * I2C.h
 *
 * Created: 8/12/2021 3:19:26 AM
 *  Author: Kirellos Emad Samir
 */ 


#ifndef I2C_H_
#define I2C_H_
#include "CPU_CONFIGURATION.h"

void I2C_Set_Address(unsigned char address);
unsigned char I2C_Read(unsigned char ack);
void I2C_Write(unsigned char cByte);





#endif /* I2C_H_ */