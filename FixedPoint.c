/*
 * FixedPoint.c
 *
 *  Created on: 16 May 2012
 *      Author: moisem
 */
#include "FixedPoint.h"

inline int8_8 int8_8_new(const float X)
{
	int __yy =(int)(X*256);
    return *(int8_8*)&__yy;
}

inline int16_16 int16_16_new(const float X)
{
	int __yy =(int)(X*(1<<16));
    return *(int16_16*)&__yy;
}

inline int8_8 add8_8(int8_8 x,int8_8 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	return _int8_8(__s);
}

inline int8_8 sadd8_8(int8_8 x,int8_8 y)
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

inline int8_8 sub8_8(int8_8 x,int8_8 y)
{
    int __s = *(int*)(&x) - *(int*)(&y);
    return _int8_8(__s);
}

inline int8_8 ssub8_8(int8_8 x,int8_8 y)
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

inline int8_8 mul8_8(int8_8 x,int8_8 y)
{
int __s = _int(x) * _int(y);
__s>>=8;
return _int8_8(__s);
}

inline int8_8 smul8_8(int8_8 x,int8_8 y)
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

inline int8_8 fract8_8(int8_8 x)
{
 int8_8 s=x;
 int ss = *(int*)&s;
 ss &=0xFFFF00FF;
 return _int8_8(ss);
}

inline int8_8 floor8_8(int8_8 x)
{
 int8_8 s=x;
 int ss = *(int*)&s;
 ss &=0xFFFFFF00;
 return _int8_8(ss);
}

inline int16_16 cast8_8_to_16_16(int8_8 x)
{
	int y = 0;
	int16_16 yy = _int16_16(y);
	yy.p = x.p;
	yy.q = x.q << 8;
	return yy;
}

inline int16_16 add16_16(int16_16 x,int16_16 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	return _int16_16(__s);
}

inline int16_16 sadd16_16(int16_16 x,int16_16 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	int xx = *(int*)(&x);
	int yy = *(int*)(&y);
	if ((xx & 0x80000000)==(yy & 0x80000000))
	{
		if ((xx & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
		if (!(xx & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
	}
	return _int16_16(__s);
}

inline int16_16 sub16_16(int16_16 x,int16_16 y)
{
	int __s = *(int*)(&x) - *(int*)(&y);
	return _int16_16(__s);
}

inline int16_16 ssub16_16(int16_16 x,int16_16 y)
{
    int __s = *(int*)(&x) - *(int*)(&y);
    int xx = *(int*)(&x);
    int yy = *(int*)(&y) * (-1);
    if ((xx & 0x80000000)==(yy & 0x80000000))
    {
        if ((xx & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
    	if (!(xx & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
   	}
    return _int16_16(__s);
}

inline int16_16 mul16_16(int16_16 x,int16_16 y)
{
	//int __s = (((int)x.p*(int)y.p) << 16)+(int)x.p*(int)y.q+(int)x.q*(int)y.p+(((int)x.q*(int)y.q)>> 16);
	long long xx = 0;
	xx = *(long long*)&x;
	if (x.p<1<<15)
		xx &= 0x00000000FFFFFFFF;
	else
	{
		xx &= 0x00000000FFFFFFFF;
		xx |= 0xFFFFFFFF00000000;
	}
	long long yy = 0;
    yy = *(long long*)&y;
    if (y.p<1<<15)
    	yy &= 0x00000000FFFFFFFF;
    else
    {
    	yy &= 0x00000000FFFFFFFF;
    	yy |= 0xFFFFFFFF00000000;
   	}
	int __s = ((xx*yy)>>16);
	return _int16_16(__s);
}
