/*
 * Info.h
 *
 *  Created on: 30 May 2012
 *      Author: moisem
 */

#ifndef INFO_H_
#define INFO_H_


#endif /* INFO_H_ */

struct __error
{
   int code;
};

typedef struct __error _Error;

#define init_err(X) int __x;X=(_Error*)&__x; (X)->code=0

#define has_error(X) ((X)->code!=0)

#define set_overflow(X) ((X)->code |= MASK_OVERFLOW)
#define reset_overflow(X) ((X)->code &= ~MASK_OVERFLOW)
#define get_overflow(X) ((X)->code &= MASK_OVERFLOW)

#define MASK_OVERFLOW 0x00000001

#define set_debug() DEBUG=1
#define set_no_debug() DEBUG=0
#define init_current_err() init_err(CURRENT_ERR)

#define debug_on() if(1){set_debug();init_current_err();}
#define debug_off() if(1){set_no_debug();init_current_err();}

int DEBUG;
_Error* CURRENT_ERR;
