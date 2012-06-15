/*
 * FixedPoint.h
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */


#ifndef FIXEDPOINT_H_
#define FIXEDPOINT_H_

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


#define  _int(X) ((int)(((X).p<128)?((*(int*)&X)&0x0000FFFF):((*(int*)&X)|0xFFFF0000)))

#define  _int8_8(X) *(int8_8*)&X //this is not good because it will keep residues from other formats

#define print8_8(X) printf("%d : %d\n",(X).p,(X).q)

/*comparison macros*/
#define comp_gt(X,Y) (_int(X)) > (_int(Y))
#define comp_lt(X,Y) (_int(X)) < (_int(Y))
#define comp_eq(X,Y) ((_int(X)) == (_int(Y)))
#define comp_gt_eq(X,Y) (_int(X)) >= (_int(Y))
#define comp_lt_eq(X,Y) (_int(X)) <= (_int(Y))

/*utility macros*/
#define floor8_8(X) ((int)(_int(X)>>8))
#define fract8_8(X,Y) (Y)=(X);(Y).p=0; //use mask to return res
/*ceil,trunc,round,fix*/

/*arithmetic macros*/

#define sub8_8(X,Y,Z) if(1) {int __s = *(int*)(&X) - *(int*)(&Y);Z=_int8_8(__s);}
#define mul8_8(X,Y,Z) if(1) {int __s = _int(X) * _int(Y);__s>>=8;Z=_int8_8(__s);}



/*init and alloc macros*/
#define int8_8_alloc(X) if(1){ int __xx=0; X=(int8_8*)&__xx;}

int8_8 int8_8_new(const float X);
int8_8 add8_8(int8_8 x,int8_8 y);
#endif

