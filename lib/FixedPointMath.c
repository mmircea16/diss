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
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm8_8(m);
	if (!k) return 0;


	uint64_t y = -(((int16_t)m) << (32-k));
	uint64_t x = -(((int16_t)m) << (32-k));
	if (y==2147483648) return (k>8?n>>(k-9):n<<(9-k));
	int j;
	uint64_t p=1ULL;

	float mm = (((int16_t)m) << (16-k))/65536.0;
	//printf("m:%f\n",mm);
	for (j=0;j<3;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y | (0x0000000100000000);
	uint64_t out = res * n;

    out = (k>8?out>>(k-8):out<<(8-k));
    //out += (1<<15);
    out >>=32;
    if (sign == -1) out = ~out;
   // printf("return:%x %d\n",(out),out);
	return (int8_8)(out);
};

inline char bits4_most_significant(char x)
{
	if (!x) return 0;
	return (x&0xC?(x&0x8?4:3):(x&0x2?2:1));
}
