/*
 * FixedPoint.h
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */

#ifndef FIXEDPOINT_H_
#define FIXEDPOINT_H_

#endif /* FIXEDPOINT_H_ */

struct __int8_8
{
	unsigned q:8;
	unsigned p:8;
};

typedef struct __int8_8 int8_8;


#define  _int(X) *(int*)&X

#define  _int8_8(X) *(int8_8*)&X //this is not good because it will keep residues from other formats

#define comp_gt(X,Y) _int(X) > _int(Y)
#define comp_lt(X,Y) _int(X) < _int(Y)
#define comp_eq(X,Y) (_int(X) == _int(Y))
#define comp_gt_eq(X,Y) _int(X) >= _int(Y)
#define comp_lt_eq(X,Y) _int(X) <= _int(Y)

#define add(X,Y) _int(X) + _int(Y)
#define add8_8(X,Y,Z) if(1) {int s = *(int*)(&X) + *(int*)(&Y);Z=_int8_8(s);}

#define sub(X,Y) _int(X) - _int(Y)
#define sub8_8(X,Y,Z) if(1) {int s = *(int*)(&X) - *(int*)(&Y);Z=_int8_8(s);}


#define SIGN_EXP_MASK 0x007fffff;
#define SET_BIT_BEFORE_MANTISSA_MASK 0x00800000;
#define INT8_8_MASK 0x00ffff00;

#define int8_8_new(X,Y) if(1){ int x =(int)(X*256); Y = *(int8_8*)&x;}

struct __float{
	 int mantissa :23;
	 int exp :8;
	 int sign :1;
} ;

typedef struct __float _float;

int8_8 int8_8_new_impl(int integer_part, const float no);
int8_8 int8_8_new_impl2(const float no);

/*static inline int8_8 int8_8_new(const float number)
{
  int x = (int)(number*256);
  int8_8 y = *(int8_8*)&x;
  return y;
};*/

