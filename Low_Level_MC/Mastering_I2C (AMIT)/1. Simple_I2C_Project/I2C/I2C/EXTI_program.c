#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"  

/*		Adjusting the global pointer to function (EXTI0_CallBack)								
		This is a Global Pointer to function 													
		will be used here to communicate between 2 functions (EXTI0_SetCallBack	&& __vector_1)	*/
#ifndef 	NULL
#define 	NULL	(void *)0
#endif
static void (*EXTI0_CallBack) (void) = NULL; 


void EXTI0_SetCallBack(void(*pf)(void)) 
{
	/*		Function to communicate between 2 .c files (EXT_program.c && main.c)	*/
	/*		Takes address of function from the main.c w and retrieves it here		*/
	/*		Will containt the Address of  EXTI0_fun 								*/
	/*		pf is a pointer to function 											*/
	EXTI0_CallBack = pf; 
}
void GIE_voidInterruptEnable(void)
{
	SET_BIT(SREG,7);
}
void GIE_voidInterruptDisable(void)
{
	CLR_BIT(SREG,7);
}
void EXTI0_voidInit(void)
{
	/*		EXTI0 => Falling or Rising or both or Low Level		*/
	#if 	SENSE_MODE == EXTI_FALLING
			CLR_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
	#elif 	SENSE_MODE == EXTI_RISING
			SET_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
	#elif 	SENSE_MODE == EXTI_IOC
			SET_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
	#elif 	SENSE_MODE == EXTI_LOW_LEVEL
			CLR_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
	#else 
			#error	"Wrong choice of Sense Mode!"
	#endif 
	
	/*	Disable interrupt 0		*/
	CLR_BIT(GICR,6);
	/*	Clear INT0 flag (INTF0)	*/
	SET_BIT(GIFR,6);
	
}
void EXTI0_voidEnableInterrupt(void)
{
	SET_BIT(GICR,6);

}
void EXTI0_voidDisableInterrupt(void)
{
	CLR_BIT(GICR,6); //hwa katebha set 
}
void __vector_1	(void)
{
	/* 	This is the ISR																*/
	/* 	EXTI0_CallBack() is a global pointer to function							*/
	/* 	EXTI0_CallBack() points to/executes the EXTI0_fun function in the main.c	*/
	
	/*	Solutions that weren't possible -- only for illustration					*/
	/*	pf();		 	-- address of the function 									*/
	/*	EXTI0_fun(); 	-- can't call the function here -- it's in the main.c 		*/
	
	EXTI0_CallBack();
}

