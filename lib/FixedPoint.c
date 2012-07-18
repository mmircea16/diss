/*
 * FixedPoint.c
 *
 *  Created on: 16 May 2012
 *      Author: moisem
 */
#include "FixedPoint.h"

inline int8_8 int8_8_new(const float X)
{
	int16_t __yy =(int16_t)(X*256);
    return (int8_8)__yy;
}

inline int16_16 int16_16_new(const float X)
{
	int __yy =(int)(X*(1<<16));
    return (int16_16)__yy;
}

inline int8_8 add8_8(int8_8 x,int8_8 y)
{
	int16_t __s = (int16_t)(x) + (int16_t)(y);
	return (int8_8)__s;
}

inline int8_8 sadd8_8(int8_8 x,int8_8 y)
{
	int16_t __s = (int16_t)(x) + (int16_t)(y);

	if ((x & 0x8000)==(y & 0x8000))
	{
		if ((x & 0x8000) && !(__s & 0x8000)) __s = 0x8000;
		if (!(x & 0x8000) && (__s & 0x8000)) __s = 0x7FFF;
	}
	return (int8_8)__s;
}

inline int8_8 sub8_8(int8_8 x,int8_8 y)
{
	int16_t __s = (int16_t)(x) - (int16_t)(y);
    return (int8_8)__s;
}

inline int8_8 ssub8_8(int8_8 x,int8_8 y)
{
	int16_t __s = (int16_t)(x) - (int16_t)(y);

	if ((x & 0x8000)==(~y & 0x8000))
	{
		if ((x & 0x8000) && !(__s & 0x8000)) __s = 0x8000;
		if (!(x & 0x8000) && (__s & 0x8000)) __s = 0x7FFF;
	}
	return (int8_8)__s;
}

inline int8_8 mul8_8(int8_8 x,int8_8 y)
{
 int32_t __s = (int16_t)(x) * (int16_t)(y);
 int16_t r = __s>>8;
 return (int8_8)r;
}

inline int8_8 smul8_8(int8_8 x,int8_8 y)
{
 int32_t __s = (int16_t)(x) * (int16_t)(y);
__s >>= 8;
if ((x^y)&0x8000)
{
	if (~__s & 0xFFFF8000)
	{
		__s = 0x00008000;
	}
}else{
	if (__s & 0xFFFF8000)
	{
		__s = 0x00007FFF;
	}
}
int16_t r = __s;

return (int8_8)r;
}

inline int8_8 fract8_8(int8_8 x)
{
    return (int8_8)(x & 0x00FF);
}

inline int8_8 floor8_8(int8_8 x)
{
	return (int8_8)(x & 0xFF00);
}

inline int16_16 cast8_8_to_16_16(int8_8 x)
{
	return (int16_16)((int32_t)x<<8);
}

inline int16_16 add16_16(int16_16 x,int16_16 y)
{
	return (int16_16)((int32_t)x+(int32_t)y);
}

inline int16_16 sadd16_16(int16_16 x,int16_16 y)
{
	int32_t __s = (int32_t)(x) + (int32_t)(y);
	if ((x & 0x80000000)==(y & 0x80000000))
	{
		if ((x & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
		if (!(x & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
	}
	return (int16_16)(__s);
}

inline int16_16 sub16_16(int16_16 x,int16_16 y)
{
	int32_t __s = (int32_t)(x) - (int32_t)(y);
	return (int16_16)(__s);
}

inline int16_16 ssub16_16(int16_16 x,int16_16 y)
{
	int32_t __s = (int32_t)(x) - (int32_t)(y);
    if ((x & 0x80000000)==(~y & 0x80000000))
    {
        if ((x & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
    	if (!(x & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
   	}
    return (int16_16)(__s);
}

inline int16_16 mul16_16(int16_16 x,int16_16 y)
{
	 int64_t __s = (int64_t)(x) * (int64_t)(y);
	 int32_t r = __s>>16;
	 return (int16_16)r;
}

inline int16_16 smul16_16(int16_16 x,int16_16 y)
{
	int64_t __s = (int64_t)(x) * (int64_t)(y);
	int32_t r;
	__s >>= 16;
	if ((x^y)&0x80000000)
	{
		if (~__s & 0xFFFFFFFF80000000)
		{
			r = 0x80000000;
		}else
			r = __s;
	}else{
		if (__s & 0xFFFFFFFF8000000)
		{
			r = 0x7FFFFFFF;
		}else
			r = __s;
	}

	return (int16_16)r;
}

inline int8_8 cast16_16_to_8_8(int16_16 x)
{
  return (int8_8)(x>>8);
}

inline int16_16 fract16_16(int16_16 x)
{
	return (int16_16)(x & 0x0000FFFF);
}

inline int16_16 floor16_16(int16_16 x)
{
	return (int16_16)(x & 0xFFFF0000);
}

inline int8_24 int8_24_new(const float X)
{
	int32_t __yy =(int32_t)(X*(1<<24));
	return (int8_24)__yy;
}

inline int8_24 add8_24(int8_24 x,int8_24 y)
{
	int32_t __s = (int32_t)(x) + (int32_t)(y);
    return (int8_24)__s;
}

inline int8_24 sadd8_24(int8_24 x,int8_24 y)
{
	int32_t __s = (int32_t)(x) + (int32_t)(y);
	if ((x & 0x80000000)==(y & 0x80000000))
	{
		if ((x & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
		if (!(x & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
	}
	return (int8_24)__s;
}

inline int8_24 sub8_24(int8_24 x,int8_24 y)
{
	int32_t __s = (int32_t)(x) - (int32_t)(y);
    return (int8_24)__s;
}

inline int8_24 ssub8_24(int8_24 x,int8_24 y)
{
	int32_t __s = (int32_t)(x) - (int32_t)(y);

    if ((x & 0x80000000)==(~y & 0x80000000))
    {
        if ((x & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
    	if (!(x & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
   	}
    return (int8_24)__s;
}

inline int8_24 mul8_24(int8_24 x,int8_24 y)
{
    int64_t __s = (int64_t)(x) * (int64_t)(y);
    int32_t r = __s>>24;
    return (int8_24)r;
}

inline int8_24 smul8_24(int8_24 x,int8_24 y)
{
	int64_t __s = (int64_t)(x) * (int64_t)(y);
	int32_t r;
	__s >>= 24;
	if ((x^y)&0x80000000)
	{
		if (~__s & 0xFFFFFFFF80000000)
		{
			r = 0x80000000;
		}else
			r = __s;
	}else{
		if (__s & 0xFFFFFFFF80000000)
		{
			r = 0x7FFFFFFF;
		}else
			r = __s;
	}

	return (int8_24)r;
}

inline int8_24 floor8_24(int8_24 x)
{
	return (int8_24)(x & 0xFF000000);
}

inline int8_24 fract8_24(int8_24 x)
{

	return (int8_24)(x & 0x00FFFFFF);
}

inline int24_8 int24_8_new(const float X)
{
	int32_t __yy =(int32_t)(X*256);
    return (int24_8)__yy;
}

inline int24_8 add24_8(int24_8 x,int24_8 y)
{
	int32_t __s =(int32_t)x + (int32_t)y;
	return (int24_8)__s;
}

inline int24_8 sadd24_8(int24_8 x,int24_8 y)
{
	int32_t __s = (int32_t)(x) + (int32_t)(y);
	if ((x & 0x80000000)==(y & 0x80000000))
	{
		if ((x & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
		if (!(x & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
	}
	return (int24_8)__s;
}

inline int24_8 sub24_8(int24_8 x,int24_8 y)
{
	int32_t __s =(int32_t)x - (int32_t)y;
	return (int24_8)__s;
}

inline int24_8 ssub24_8(int24_8 x,int24_8 y)
{
	int32_t __s = (int32_t)(x) - (int32_t)(y);
	if ((x & 0x80000000)==(~y & 0x80000000))
	{
		if ((x & 0x80000000) && !(__s & 0x80000000)) __s = 0x80000000;
		if (!(x & 0x80000000) && (__s & 0x80000000)) __s = 0x7FFFFFFF;
	}
	return (int24_8)__s;
}

inline int24_8 mul24_8(int24_8 x,int24_8 y)
{
    int64_t __s = (int64_t)(x) * (int64_t)(y);
    int32_t r = __s>>8;
    return (int8_24)r;
}

inline int24_8 smul24_8(int24_8 x,int24_8 y)
{
	int64_t __s = (int64_t)(x) * (int64_t)(y);
	int32_t r;
	__s >>= 8;
	if ((x^y)&0x80000000)
	{
		if (~__s & 0xFFFFFFFF80000000)
		{
			r = 0x80000000;
		}else
			r = __s;
	}else{
		if (__s & 0xFFFFFFFF80000000)
		{
			r = 0x7FFFFFFF;
		}else
			r = __s;
	}

	return (int8_24)r;
}

inline int24_8 floor24_8(int24_8 x)
{
	return (int8_24)(x & 0xFFFFFF00);
}

inline int24_8 fract24_8(int24_8 x)
{
	return (int8_24)(x & 0x000000FF);
}

