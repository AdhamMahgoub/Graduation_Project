#ifndef				EXTI_PRIVATE_H
#define 			EXTI_PRIVATE_H
	
	
#define 			SREG				*((volatile u8 *)0x5F)  
#define 			GICR				*((volatile u8 *)0x5B)
#define 			GIFR				*((volatile u8 *)0x5A)
#define 			MCUCR				*((volatile u8 *)0x55)
#define 			MCUCSR				*((volatile u8 *)0x54)


#define 			EXTI_FALLING		0
#define 			EXTI_RISING			1
#define 			EXTI_IOC			2
#define 			EXTI_LOW_LEVEL		3


#endif 