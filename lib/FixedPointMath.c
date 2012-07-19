/*
 * FixedPointMath.c
 *
 *  Created on: 18 Jul 2012
 *      Author: moisem
 */
#include "FixedPointMath.h"

short norm8_8(int8_8 x)
{
	if (!x) return 0;
	short pos = 12;
	char last = 0;
	while (!(last=bits4_most_significant(x >> 12))){
		x <<= 4;
		pos -= 4;
	}
	return (pos + last);
}

int8_8 div8_8(int8_8 n, int8_8 m)
{
	short k = norm8_8(m);
	if (!k) return 0;


	int0_32 y = -(((int16_t)m) << (32-k));
	int0_32 x = -((int16_t)m) << (32-k);
	if (y==-32768) return (k>8?n>>(k-9):n<<(9-k));
	int j;
	int0_64 p;
	for (j=0;j<8;j++){
    p = x*x;
	x = p >> 32;
    p = x*y;
    y = (p >> 32) + y;

	}

	int16_16 res = ((uint64_t)(y) >> 32)+(1<<16);
	int64_t out = res * m;

	return (int8_8)(out >> 16);
};

inline char bits4_most_significant(char x)
{
	if (!x) return 0;
	return (x&0xC?(x&0x8?4:3):(x&0x2?2:1));
}
