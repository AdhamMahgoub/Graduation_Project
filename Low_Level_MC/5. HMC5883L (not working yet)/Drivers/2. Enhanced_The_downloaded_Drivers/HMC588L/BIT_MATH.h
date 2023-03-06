#ifndef		BIT_MATH_H
#define		BIT_MATH_H

/*	SET 	 particular Bit	*/
#define		 SET_BIT(REG,BIT)		(REG |= (1<<BIT))	

/*	CLEAR 	 particular Bit	*/
#define		 CLR_BIT(REG,BIT)		(REG &= ~(1<<BIT))

/*	TOGGLE	 particular Bit	*/
#define		 TOG_BIT(REG,BIT)		(REG ^= (1<<BIT))

/*	GET		 particular Bit	*/
#define		 GET_BIT(REG,BIT)		((REG>>BIT)&1)

#endif
