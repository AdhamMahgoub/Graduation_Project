#ifndef IR_H_
#define IR_H_

//#include "../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"



#define IR_Port PORTD
#define IR_Pin 6

int IR_Triggered(void);



#endif /* IR_H_ */