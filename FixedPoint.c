/*
 * FixedPoint.c
 *
 *  Created on: 16 May 2012
 *      Author: moisem
 */
#include "FixedPoint.h"

int8_8 int8_8_new(const float X)
{
	int __yy =(int)(X*256);
    return *(int8_8*)&__yy;
}

int8_8 add8_8(int8_8 x,int8_8 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	return _int8_8(__s);
}
