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

struct __info
{
	int underflow_value; //(represented value - actual value)*2^32
};

typedef struct __info _Info;



#define init_err(X) int __x;X=(_Error*)&__x; (X)->code=0;
#define init_info(X) int __y;X=(_Info*)&__y; (X)->underflow_value=0;

#define has_error(X) ((X)->code!=0)

#define set_overflow(X) ((X)->code |= MASK_OVERFLOW)
#define reset_overflow(X) ((X)->code &= ~MASK_OVERFLOW)
#define get_overflow(X) ((X)->code &= MASK_OVERFLOW)

#define MASK_OVERFLOW 0x00000001

#define set_underflow(X) ((X)->code |= MASK_UNDERFLOW)
#define reset_underflow(X) ((X)->code &= ~MASK_UNDERFLOW)
#define get_underflow(X) ((X)->code &= MASK_UNDERFLOW)

#define MASK_UNDERFLOW 0x00000010

#define set_underflow_value(X) CURRENT_INFO->underflow_value=(X);
#define reset_underflow_value() CURRENT_INFO->underflow_value=0;
#define get_underflow_value() CURRENT_INFO->underflow_value

#define set_debug() DEBUG=1
#define set_no_debug() DEBUG=0
#define init_current_err() init_err(CURRENT_ERR)
#define init_current_info() init_info(CURRENT_INFO)

#define debug_on() if(1){set_debug();init_current_err();init_current_info();}
#define debug_off() if(1){set_no_debug();init_current_err();init_current_info();}

#define verify_overflow(X) (((X)>=128*256)||((X)<-128*256))?set_overflow(CURRENT_ERR):reset_overflow(CURRENT_ERR);
#define verify_underflow(X) if(1){const float __x = X;int exp=((_float*)(&__x))->exp;int sign=((_float*)(&__x))->sign;int aux=*(int*)(&__x);aux &= 0x007FFFFF; aux |= 0x00800000;aux <<=(exp-127); aux>>=7;if(sign) aux = ~aux + 1;aux &= 0x000000FF;(aux)?set_underflow(CURRENT_ERR):reset_underflow(CURRENT_ERR);aux <<= 24;set_underflow_value(aux);}


int DEBUG;
_Error* CURRENT_ERR;
_Info* CURRENT_INFO;
