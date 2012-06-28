/*
 * FixedPoint.h
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */


#ifndef FIXEDPOINTDEBUG_H_
#define FIXEDPOINTDEBUG_H_

/*structures*/
struct __float{
	 int mantissa :23;
	 int exp :8;
	 int sign :1;
} ;

typedef struct __float _float;

struct __int8_8
{
	unsigned q:8;
	unsigned p:8;
};

typedef struct __int8_8 int8_8;

struct __int16_16
{
	unsigned q:16;
	unsigned p:16;
};

typedef struct __int16_16 int16_16;



#define  _int(X) ((int)(((X).p<128)?((*(int*)&X)&0x0000FFFF):((*(int*)&X)|0xFFFF0000)))

#define  _int8_8(X) *(int8_8*)&X

#define print8_8(X) printf("%d : %d\n",(X).p,(X).q)

/*comparison macros*/
#define comp_gt(X,Y) (_int(X)) > (_int(Y))
#define comp_lt(X,Y) (_int(X)) < (_int(Y))
#define comp_eq(X,Y) ((_int(X)) == (_int(Y)))
#define comp_not_eq(X,Y) ((_int(X)) != (_int(Y)))
#define comp_gt_eq(X,Y) (_int(X)) >= (_int(Y))
#define comp_lt_eq(X,Y) (_int(X)) <= (_int(Y))

/*utility macros*/
#define floor(X) ((int)(_int(X)>>8))
/*ceil,trunc,round,fix*/

/*arithmetic macros*/



/*init and alloc macros*/
#define int8_8_alloc(X) if(1){ int __xx=0; X=(int8_8*)&__xx;}

__inline__ int8_8 int8_8_new_d(const float X);
__inline__ int8_8 add8_8_d(int8_8 x,int8_8 y);
__inline__ int8_8 sadd8_8_d(int8_8 x,int8_8 y);
__inline__ int8_8 sub8_8_d(int8_8 x,int8_8 y);
__inline__ int8_8 ssub8_8_d(int8_8 x,int8_8 y);
__inline__ int8_8 mul8_8_d(int8_8 x,int8_8 y);
__inline__ int8_8 smul8_8_d(int8_8 x,int8_8 y);
__inline__ int8_8 fract8_8_d(int8_8 x);
__inline__ int8_8 floor8_8_d(int8_8 x);
#endif

