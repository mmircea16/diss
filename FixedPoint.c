/*
 * FixedPoint.c
 *
 *  Created on: 16 May 2012
 *      Author: moisem
 */
#include "FixedPoint.h"

int8_8 int8_8_new_impl(int integer_part, const float no)
{
	int8_8* x=(int8_8*) malloc(sizeof(int8_8));
	*(int*)x = 0;
	x->p = integer_part;
	_float* ff=&no;
	x->q = ff->mantissa >> 15;
	return *x;
}

int8_8 int8_8_new_impl2(const float no)
{
	int8_8* x=(int8_8*) malloc(sizeof(int8_8));
	*(int*)x = 0;
	_float* ff=&no;
	int exp = ff->exp;
	int aux = *(int*)ff;
	printf("%d %x\n",exp,aux);
	aux &= SIGN_EXP_MASK;
	aux |= SET_BIT_BEFORE_MANTISSA_MASK;
	printf("%d %x\n",exp,aux);
	aux <<= (exp-127);
	aux >>= 7; //move decimal point to middle
	aux &= INT8_8_MASK;
	*x = _int8_8(aux);

	return *x;
}



