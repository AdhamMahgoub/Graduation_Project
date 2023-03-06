#ifndef					EXTI_INTERFACE_H
#define 				EXTI_INTERFACE_H


void GIE_voidInterruptEnable(void);
void GIE_voidInterruptDisable(void);

void EXTI0_voidInit(void);

void EXTI0_voidEnableInterrupt(void);
void EXTI0_voidDisableInterrupt(void);

void EXTI0_SetCallBack(void(*pf)(void));
void __vector_1	(void)		__attribute__((signal,	used)); //to avoid compiler optimization 


#endif