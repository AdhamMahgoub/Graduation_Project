#ifndef 	BIT_MATH_H
#define 	BIT_MATH_H


/* Explanation
SET 	= 1
CLEAR 	= 0
TOGGLE	= Reverse Current
GET		= Read input
*/

/*			SET		particular Bit 				*/
/* 			CLEAR	particular Bit 				*/
/* 			TOGGLE	particular Bit 				*/
/* 			GET		particular Bit 				*/

#define 	SET_BIT(REG,BIT)		REG |= (1<<BIT)
#define 	CLR_BIT(REG,BIT)		REG &= ~(1<<BIT)
#define 	TOG_BIT(REG,BIT)		REG ^= (1<<BIT)
#define 	GET_BIT(REG,BIT)		(REG>>BIT)&1

#endif