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


