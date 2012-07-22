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

short norm16_16(int16_16 x)
{
	if (!x) return 0;
	short pos = 28;
	char last = 0;
	while (!(last=bits4_most_significant(x >> 28))){
		x <<= 4;
		pos -= 4;
	}
	return (pos + last);
}

int8_8 div8_8_v2(int8_8 n,int8_8 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm8_8(m);
	if (!k) return 0;
	int aaa_nnnew = 1;
	float mm = (float)(m << (32-k))/(1LL<<32);
	uint64_t b =(m << (32-k))&(0x00000000FFFFFFFF);
	unsigned int x_i = 1;
	uint64_t x = (~((b<<1)&(0x00000000FFFFFFFF))+1)&(0x00000000FFFFFFFF);
	uint64_t p = 1LL;
	unsigned int p_i = 1;
    int i = 0;
	for (i=0;i<3;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=0x00000000FFFFFFFF;
	}
    x = (x*n)+(1LL<<32)*n;

	x = (k>8?x>>(k-8):x<<(8-k));
	x >>=32;

	if (sign == -1) x = ~x;
	//printf("---x:%x\n",x);
	return (int8_8)x;
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

int16_16 div16_16(int16_16 n, int16_16 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;


	uint64_t y = -(((int32_t)m) << (32-k));
	uint64_t x = -(((int32_t)m) << (32-k));
	if (y==2147483648) return (k>16?n>>(k-17):n<<(17-k));
	int j;
	uint64_t p=1ULL;

	float mm = (((int32_t)m) << (32-k))/65536.0;
	//printf("m:%f\n",mm);
	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y | (0x0000000100000000);
	uint64_t out = res * n;

    out = (k>16?out>>(k-16):out<<(16-k));
    //out += (1<<15);
    out >>=32;
    if (sign == -1) out = ~out;
    //printf("return:%x\n",out);
	return (int16_16)(out);
};

int16_16 div16_16_v2(int16_16 n,int16_16 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&(0x00000000FFFFFFFF);
	uint64_t x = (~((b<<1)&(0x00000000FFFFFFFF))+1)&(0x00000000FFFFFFFF);
	uint64_t p = 1LL;
    int i = 0;
	for (i=0;i<3;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=0x00000000FFFFFFFF;
	}
    x = (x*n)+(1LL<<32)*n;

	x = (k>16?x>>(k-16):x<<(16-k));
	x >>=32;

	if (sign == -1) x = ~x;
	//printf("---x:%x\n",x);
	return (int16_16)x;
}

int8_24 div8_24(int8_24 n, int8_24 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;


	uint64_t y = -(((int32_t)m) << (32-k));
	uint64_t x = -(((int32_t)m) << (32-k));
	if (y==2147483648) return (k>24?n>>(k-25):n<<(25-k));
	int j;
	uint64_t p=1ULL;

	float mm = (((int32_t)m) << (32-k))/65536.0;
	//printf("m:%f\n",mm);
	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y | (0x0000000100000000);
	uint64_t out = res * n;

    out = (k>24?out>>(k-24):out<<(24-k));
    //out += (1<<15);
    out >>=32;
    if (sign == -1) out = ~out;
    //printf("return:%x\n",out);
	return (int8_24)(out);
};

int8_24 div8_24_v2(int8_24 n,int8_24 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&(0x00000000FFFFFFFF);
	uint64_t x = (~((b<<1)&(0x00000000FFFFFFFF))+1)&(0x00000000FFFFFFFF);
	uint64_t p = 1LL;
    int i = 0;
	for (i=0;i<10;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=0x00000000FFFFFFFF;
	}
    x = (x*n)+(1LL<<32)*n;

	x = (k>24?x>>(k-24):x<<(24-k));
	x >>=32;

	if (sign == -1) x = ~x;
	//printf("---x:%x\n",x);
	return (int8_24)x;
}

inline char bits4_most_significant(char x)
{
	if (!x) return 0;
	return (x&0xC?(x&0x8?4:3):(x&0x2?2:1));
}