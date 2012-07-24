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

int24_8 div24_8(int24_8 n, int24_8 m)
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

    out = (k>8?out>>(k-8):out<<(8-k));
    //out += (1<<15);
    out >>=32;
    if (sign == -1) out = ~out;
    //printf("return:%x\n",out);
	return (int24_8)(out);
};

int24_8 div24_8_v2(int24_8 n,int24_8 m)
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

	x = (k>8?x>>(k-8):x<<(8-k));
	x >>=32;

	if (sign == -1) x = ~x;
	//printf("---x:%x\n",x);
	return (int24_8)x;
}

int8_8 sqrt8_8(int8_8 a)
{
    if (a<=0) return 0;
    short k = norm8_8(a);
    uint64_t aa = ((uint64_t)a<<(32-k))&0x00000000FFFFFFFF;
    uint64_t c1 = 0x00000001C9A8AC5C; //1.77
    uint64_t c2 = 0x00000000CF5B8130;//0.80
    uint64_t x = (c1 - ((c2*aa)>>32));
    if (x<(1ll<<32)) x = 0;
    else x = x & 0x00000000FFFFFFFF;

    float xx = ((1LL<<32)+x)/(65536LL*65536LL);
    float faa =(float) aa/(65536LL*65536LL);
    //x =0x00000000555097e1;
    int i;
    int p_i;
    uint64_t p = 1ULL;
    for (i=0;i<3;i++)
    {
    	p = ((x*x)>>32)+(x << 1) + (1LL << 32);
    	p_i = p>>32;
    	p = p & 0x00000000FFFFFFFF;
    	p = ((p*aa)>>32) + aa*p_i;
    	p = (3LL << 32) - p;
    	p_i = (p>>32);
    	p = p & 0x00000000FFFFFFFF;
        x = ((p * x) >> 33) + ((p_i * x) >> 1)+(p>>1)+(p_i<<31);
        x = x & 0x00000000FFFFFFFF;
        xx =(float) ((1LL<<32)+x)/(65536LL*65536LL);
        faa =(float) aa/(65536LL*65536LL);
    }
    x = ((x * aa)>>32)+aa;

    uint64_t c3 = 0x000000006A09E668; //sqrt(2)
    if (k%2) {x = ((x*c3)>>32)+x; }
    x = (k>8?x << ((k-8)/2) : x >> ((9-k)/2));
	return (int8_8)(x>>24);
}

int16_16 sqrt16_16(int16_16 a)
{
    if (a<=0) return 0;
    short k = norm16_16(a);
    uint64_t aa = ((uint64_t)a<<(32-k))&0x00000000FFFFFFFF;
    uint64_t c1 = 0x00000001C9A8AC5C; //1.77
    uint64_t c2 = 0x00000000CF5B8130;//0.80
    uint64_t x = (c1 - ((c2*aa)>>32));
    if (x<(1ll<<32)) x = 0;
    else x = x & 0x00000000FFFFFFFF;

    //x =0x00000000555097e1;
    int i;
    int p_i;
    uint64_t p = 1ULL;
    for (i=0;i<3;i++)
    {
    	p = ((x*x)>>32)+(x << 1) + (1LL << 32);
    	p_i = p>>32;
    	p = p & 0x00000000FFFFFFFF;
    	p = ((p*aa)>>32) + aa*p_i;
    	p = (3LL << 32) - p;
    	p_i = (p>>32);
    	p = p & 0x00000000FFFFFFFF;
        x = ((p * x) >> 33) + ((p_i * x) >> 1)+(p>>1)+(p_i<<31);
        x = x & 0x00000000FFFFFFFF;

    }
    x = ((x * aa)>>32)+aa;

    uint64_t c3 = 0x000000006A09E668; //sqrt(2)
    if (k%2) {x = ((x*c3)>>32)+x; }
    x = (k>16?x << ((k-16)/2) : x >> ((17-k)/2));
	return (int16_16)(x>>16);
}

int8_24 sqrt8_24(int8_24 a)
{
    if (a<=0) return 0;
    short k = norm16_16(a);
    uint64_t aa = ((uint64_t)a<<(32-k))&0x00000000FFFFFFFF;
    uint64_t c1 = 0x00000001C9A8AC5C; //1.77
    uint64_t c2 = 0x00000000CF5B8130;//0.80
    uint64_t x = (c1 - ((c2*aa)>>32));
    if (x<(1ll<<32)) x = 0;
    else x = x & 0x00000000FFFFFFFF;

    //x =0x00000000555097e1;
    int i;
    int p_i;
    uint64_t p = 1ULL;
    for (i=0;i<3;i++)
    {
    	p = ((x*x)>>32)+(x << 1) + (1LL << 32);
    	p_i = p>>32;
    	p = p & 0x00000000FFFFFFFF;
    	p = ((p*aa)>>32) + aa*p_i;
    	p = (3LL << 32) - p;
    	p_i = (p>>32);
    	p = p & 0x00000000FFFFFFFF;
        x = ((p * x) >> 33) + ((p_i * x) >> 1)+(p>>1)+(p_i<<31);
        x = x & 0x00000000FFFFFFFF;

    }
    x = ((x * aa)>>32)+aa;

    uint64_t c3 = 0x000000006A09E668; //sqrt(2)
    if (k%2) {x = ((x*c3)>>32)+x; }
    x = (k>24?x << ((k-24)/2) : x >> ((25-k)/2));
	return (int8_24)(x>>8);
}

int24_8 sqrt24_8(int24_8 a)
{
    if (a<=0) return 0;
    short k = norm16_16(a);
    uint64_t aa = ((uint64_t)a<<(32-k))&0x00000000FFFFFFFF;
    uint64_t c1 = 0x00000001C9A8AC5C; //1.77
    uint64_t c2 = 0x00000000CF5B8130;//0.80
    uint64_t x = (c1 - ((c2*aa)>>32));
    if (x<(1ll<<32)) x = 0;
    else x = x & 0x00000000FFFFFFFF;

    //x =0x00000000555097e1;
    int i;
    int p_i;
    uint64_t p = 1ULL;
    for (i=0;i<3;i++)
    {
    	p = ((x*x)>>32)+(x << 1) + (1LL << 32);
    	p_i = p>>32;
    	p = p & 0x00000000FFFFFFFF;
    	p = ((p*aa)>>32) + aa*p_i;
    	p = (3LL << 32) - p;
    	p_i = (p>>32);
    	p = p & 0x00000000FFFFFFFF;
        x = ((p * x) >> 33) + ((p_i * x) >> 1)+(p>>1)+(p_i<<31);
        x = x & 0x00000000FFFFFFFF;

    }
    x = ((x * aa)>>32)+aa;

    uint64_t c3 = 0x000000006A09E668; //sqrt(2)
    if (k%2) {x = ((x*c3)>>32)+x; }
    x = (k>8?x << ((k-8)/2) : x >> ((9-k)/2));
	return (int24_8)(x>>24);
}

int8_8 log8_8(int8_8 aa)
{
	uint64_t a[16]={8332236554LL, 7842104992LL, 7406432492LL, 7016620256LL, 6665789243LL, 6348370707LL, 6059808403LL, 5796338472LL, 5554824369LL, 5332631394LL, 5127530187LL, 4937621661LL, 4761278030LL, 4597096029LL, 4443859495LL, 4300509189LL};
	int64_t lna[16]={2846223171LL, 2585842403LL, 2340348885LL, 2108131938LL, 1887828916LL, 1678276757LL, 1478474811LL, 1287555944LL, 1104763792LL, 929434661LL, 760982981LL, 598889506LL, 442691664LL, 291975593LL, 146369537LL, 5538320LL};
	if (aa<=0) return 0;
	int yyy=1;
	short k = norm8_8(aa);
	uint64_t x = ((uint64_t)aa)<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (x*a[key])>>32;
	uint64_t t;
	if (x<(1LL<<31)) t=x;
	else t = x - (1ULL<<32);

	uint64_t app = t - ((t*t)>>33);
	app = app - lna[key];
	app = app + (k-8)*2977044471ULL;
	return (int8_8)(app>>24);
}

inline char bits4_most_significant(char x)
{
	if (!x) return 0;
	return (x&0xC?(x&0x8?4:3):(x&0x2?2:1));
}
