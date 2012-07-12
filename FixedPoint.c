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

inline int16_16 smul16_16(int16_16 x,int16_16 y)
{
	//int __s = (((int)x.p*(int)y.p) << 16)+(int)x.p*(int)y.q+(int)x.q*(int)y.p+(((int)x.q*(int)y.q)>> 16);
	long long xx = 0;
	xx = *(long long*)&x;
	int sign = 1;
	if (x.p<1<<15)
		xx &= 0x00000000FFFFFFFF;
	else
	{
		sign *= -1;
		xx &= 0x00000000FFFFFFFF;
		xx |= 0xFFFFFFFF00000000;
	}
	long long yy = 0;
    yy = *(long long*)&y;
    if (y.p<1<<15)
    	yy &= 0x00000000FFFFFFFF;
    else
    {
    	sign *= -1;
    	yy &= 0x00000000FFFFFFFF;
    	yy |= 0xFFFFFFFF00000000;
   	}
	long long __s = ((xx*yy)>>16);
	int rez = 0;
	if (__s & 0xFFFFFFFF00000000)
	{
		if (sign==1)
			rez = 0x7FFFFFFF;
		else
			rez = 0x80000000;
	}else rez = __s;
	return _int16_16(rez);
}

inline int8_8 cast16_16_to_8_8(int16_16 x)
{
	short aux = 0;
	aux = (*(int*)&x) >> 8;
	return _int8_8(aux);
}

inline int16_16 fract16_16(int16_16 x)
{
 int16_16 s=x;
 int ss = *(int*)&s;
 ss &=0x0000FFFF;
 return _int16_16(ss);
}

inline int16_16 floor16_16(int16_16 x)
{
 int16_16 s=x;
 int ss = *(int*)&s;
 ss &=0xFFFF0000;
 return _int16_16(ss);
}

inline int8_24 int8_24_new(const float X)
{
	int __yy =(int)(X*(1<<24));
	return *(int8_24*)&__yy;
}

inline int8_24 add8_24(int8_24 x,int8_24 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
    return _int8_24(__s);
}

inline int8_24 sadd8_24(int8_24 x,int8_24 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	int xx = *(int*)(&x);
	int yy = *(int*)(&y);
	if ((xx & 0x80000000)==(yy & 0x80000000))
	{
		if ((xx & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
		if (!(xx & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
	}
	return _int8_24(__s);
}

inline int8_24 sub8_24(int8_24 x,int8_24 y)
{
	int __s = *(int*)(&x) - *(int*)(&y);
    return _int8_24(__s);
}

inline int8_24 ssub8_24(int8_24 x,int8_24 y)
{
    int __s = *(int*)(&x) - *(int*)(&y);
    int xx = *(int*)(&x);
    int yy = *(int*)(&y) * (-1);
    if ((xx & 0x80000000)==(yy & 0x80000000))
    {
        if ((xx & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
    	if (!(xx & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
   	}
    return _int8_24(__s);
}

inline int8_24 mul8_24(int8_24 x,int8_24 y)
{
	//int __s = (((int)x.p*(int)y.p) << 16)+(int)x.p*(int)y.q+(int)x.q*(int)y.p+(((int)x.q*(int)y.q)>> 16);
	long long xx = 0;
	xx = *(long long*)&x;
	if (x.p<1<<7)
		xx &= 0x00000000FFFFFFFF;
	else
	{
		xx &= 0x00000000FFFFFFFF;
		xx |= 0xFFFFFFFF00000000;
	}
	long long yy = 0;
    yy = *(long long*)&y;
    if (y.p<1<<7)
    	yy &= 0x00000000FFFFFFFF;
    else
    {
    	yy &= 0x00000000FFFFFFFF;
    	yy |= 0xFFFFFFFF00000000;
   	}
	int __s = ((xx*yy)>>24);
	return _int8_24(__s);
}

inline int8_24 smul8_24(int8_24 x,int8_24 y)
{
	//int __s = (((int)x.p*(int)y.p) << 16)+(int)x.p*(int)y.q+(int)x.q*(int)y.p+(((int)x.q*(int)y.q)>> 16);
	long long xx = 0;
	xx = *(long long*)&x;
	int sign = 1;
	if (x.p<1<<7)
		xx &= 0x00000000FFFFFFFF;
	else
	{
		sign *= -1;
		xx &= 0x00000000FFFFFFFF;
		xx |= 0xFFFFFFFF00000000;
	}
	long long yy = 0;
    yy = *(long long*)&y;
    if (y.p<1<<7)
    	yy &= 0x00000000FFFFFFFF;
    else
    {
    	sign *= -1;
    	yy &= 0x00000000FFFFFFFF;
    	yy |= 0xFFFFFFFF00000000;
   	}
	long long __s = ((xx*yy)>>24);
	int rez = 0;
	long long ok = (sign==1)?(__s & 0xFFFFFFFF80000000):((~__s) & 0xFFFFFFFF80000000);
	if (ok)
	{
		if (sign==1)
			rez = 0x7FFFFFFF;
		else
			rez = 0x80000000;
	}else rez = __s;
	return _int8_24(rez);
}

inline int8_24 floor8_24(int8_24 x)
{
 int8_24 s=x;
 int ss = *(int*)&s;
 ss &=0xFF000000;
 return _int8_24(ss);
}

inline int8_24 fract8_24(int8_24 x)
{
 int8_24 s=x;
 int ss = *(int*)&s;
 ss &=0x00FFFFFF;
 return _int8_24(ss);
}

inline int24_8 int24_8_new(const float X)
{
	int __yy =(int)(X*256);
    return *(int24_8*)&__yy;
}

inline int24_8 add24_8(int24_8 x,int24_8 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	return _int24_8(__s);
}

inline int24_8 sadd24_8(int24_8 x,int24_8 y)
{
	int __s = *(int*)(&x) + *(int*)(&y);
	int xx = *(int*)(&x);
	int yy = *(int*)(&y);
	if ((xx & 0x80000000)==(yy & 0x80000000))
	{
		if ((xx & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
		if (!(xx & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
	}
	return _int24_8(__s);
}

