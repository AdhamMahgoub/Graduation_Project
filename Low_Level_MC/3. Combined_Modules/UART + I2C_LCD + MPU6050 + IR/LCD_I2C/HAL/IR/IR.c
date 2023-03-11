#include "IR.h"


int IR_Triggered(void)
{
	
	//	set pin to output 
	DIO_voidSetPinDirection(IR_Port,IR_Pin,INPUT);
	if (DIO_u8GetPinValue(IR_Port, IR_Pin) == 1)
		return 1; 
	else 
		return 0; 
}
