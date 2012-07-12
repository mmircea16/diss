/*
 * FixedPoint.c
 *
 *  Created on: 16 May 2012
 *      Author: moisem
 */
#include "FixedPointDebug.h"

inline int8_8 int8_8_new_d(const float X)
{
	int __yy =(int)(X*256);
	verify_overflow(__yy);
	verify_misrepresentation(__yy);
    return *(int8_8*)&__yy;
}

inline int8_8 add8_8_d(int8_8 x,int8_8 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	return _int8_8(__s);
}

inline int8_8 sadd8_8_d(int8_8 x,int8_8 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	int xx = *(int*)(&x);
	int yy = *(int*)(&y);
	if ((xx & 0x00008000)==(yy & 0x00008000))
	{
		if ((xx & 0x00008000) && !(__s & 0x00008000)) __s = 0x00008000;
		if (!(xx & 0x00008000) && (__s & 0x00008000)) __s = 0x00007FFF;
	}
	return _int8_8(__s);
}

inline int8_8 sub8_8_d(int8_8 x,int8_8 y)
{
    int __s = *(int*)(&x) - *(int*)(&y);
    return _int8_8(__s);
}

inline int8_8 ssub8_8_d(int8_8 x,int8_8 y)
{
    int __s = *(int*)(&x) - *(int*)(&y);
    int xx = *(int*)(&x);
    int yy = *(int*)(&y) * (-1);
    if ((xx & 0x00008000)==(yy & 0x00008000))
    {
        if ((xx & 0x00008000) && !(__s & 0x00008000)) __s = 0x00008000;
    	if (!(xx & 0x00008000) && (__s & 0x00008000)) __s = 0x00007FFF;
   	}
    return _int8_8(__s);
}

inline int8_8 mul8_8_d(int8_8 x,int8_8 y)
{
int __s = _int(x) * _int(y);
__s>>=8;
return _int8_8(__s);
}

inline int8_8 smul8_8_d(int8_8 x,int8_8 y)
{
int sign = 1;
int xx = _int(x);
if (xx<0)
{
  xx = (-1)* xx;
  sign *= -1;
}
int yy = _int(y);
if (yy<0)
{
 yy = (-1)*yy;
 sign *= -1;
}
int __s = xx * yy;
__s>>=8;
int rez = (sign == -1? (1<<15) : ((1<<15) -1));
if (__s > 1<<15)
{
	__s = rez;
}else sign==-1?__s=__s*sign-1:0;
return _int8_8(__s);
}

inline int8_8 fract8_8_d(int8_8 x)
{
 int8_8 s=x;
 int ss = *(int*)&s;
 ss &=0xFFFF00FF;
 return _int8_8(ss);
}

inline int8_8 floor8_8_d(int8_8 x)
{
 int8_8 s=x;
 int ss = *(int*)&s;
 ss &=0xFFFFFF00;
 return _int8_8(ss);
}
