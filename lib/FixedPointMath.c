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


	int0_16 y = -(((int16_t)m) << (16-k));
	int0_16 x = -(((int16_t)m) << (16-k));
	if (y==-32768) return (k>8?n>>(k-9):n<<(9-k));
	int j;
	int0_32 p;
	float mm = (((int16_t)m) << (16-k))/65536.0;
	printf("m:%f\n",mm);
	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 16;
    p = x*y + (x<<16) + (y<<16);
    y = p >> 16;
	}

	uint32_t res = y+(1<<16);
	float rres = res / 65536.0;
	printf("rres:%f\n",rres);
	uint32_t out = res * n;

    out = (k>8?out>>(k-8):out<<(8-k));
    //out += (1<<15);
    out >>=16;
    printf("return:%x %d\n",(out),out);
	return (int8_8)(out);
};

inline char bits4_most_significant(char x)
{
	if (!x) return 0;
	return (x&0xC?(x&0x8?4:3):(x&0x2?2:1));
}
