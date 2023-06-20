#ifndef IR_H_
#define IR_H_

//#include "../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"



#define IR_Port PORTC
#define IR_Pin 7

int IR_Triggered(void);



#endif /* IR_H_ */