/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to Learn in depth:Mastering embedded systems as an assignment 	*
 *                                                                					*
 *     				these are utility macros for bit manipulation					*
 *                                                                  				*
 * 			this might not be the best way to do it, but it does the job     		*
 *                     				for a beginner                             		*
/*==================================================================================*/




#ifndef UTILITY_MACROS_H_
#define UTILITY_MACROS_H_


#define SET_BIT(register, offset)		register |= (1 << offset)
#define RESET_BIT(register, offset)		register &= ~(1 << offset)
#define TOGGLE_BIT(register, offset)	register ^= (1 << offset)
#define READ_BIT(register, offset)		((register >> offset) & 1)


#endif