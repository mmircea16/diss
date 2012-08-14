/*
 * FixedPointMath.c
 *
 *  Created on: 18 Jul 2012
 *      Author: moisem
 */
#include "FixedPointMath.h"
#include "Info.h"
uint64_t __A[16]={8332236554LL, 7842104992LL, 7406432492LL, 7016620256LL, 6665789243LL, 6348370707LL, 6059808403LL, 5796338472LL, 5554824369LL, 5332631394LL, 5127530187LL, 4937621661LL, 4761278030LL, 4597096029LL, 4443859495LL, 4300509189LL};
int64_t __LNA[16]={2846223171LL, 2585842403LL, 2340348885LL, 2108131938LL, 1887828916LL, 1678276757LL, 1478474811LL, 1287555944LL, 1104763792LL, 929434661LL, 760982981LL, 598889506LL, 442691664LL, 291975593LL, 146369537LL, 5538320LL};

int64_t __LNAA[16]={728633131983LL, 661975655366LL, 599129314724LL, 539681776256LL, 483284202650LL, 429638849824LL, 378489551710LL, 329614321888LL, 282819530961LL, 237935273317LL, 194811643155LL, 153315713702LL, 113329066061LL, 74745751895LL, 37470601627LL, 1417810161LL};

uint64_t __AA[16]={134217728LL, 402653184LL, 671088640LL, 939524096LL, 1207959552LL, 1476395008LL, 1744830464LL, 2013265920LL, 2281701376LL, 2550136832LL, 2818572288LL, 3087007744LL, 3355443200LL, 3623878656LL, 3892314112LL, 4160749568LL};
uint64_t __EXPAA[16]={4431304193LL, 4717098759LL, 5021325491LL, 5345173162LL, 5689907212LL, 6056874699LL, 6447509556LL, 6863338196LL, 7305985480LL, 7777181060LL, 8278766144LL, 8812700687LL, 9381071050LL, 9986098151LL, 10630146148LL, 11315731672LL};

uint64_t __AA_v2[16]={0LL, 268435456LL, 536870912LL, 805306368LL, 1073741824LL, 1342177280LL, 1610612736LL, 1879048192LL, 0x0000000080000000, 2415919104LL, 2684354560LL, 2952790016LL, 3221225472LL, 3489660928LL, 3758096384LL, 4026531840LL};
uint64_t __EXPAA_v2[16]={4294967296LL, 4571968887LL, 4866835547LL, 5180719472LL, 5514847171LL, 5870524256LL, 6249140541LL, 6652175479LL, 7081203937LL, 7537902354LL, 8024055288LL, 8541562392LL, 9092445836LL, 9678858211LL, 10303090934LL, 10967583209LL};

uint64_t __EXPX[16] = {4303364101LL, 4320206992LL, 4337115804LL, 4354090795LL, 4371132225LL, 4388240352LL, 4405415440LL, 4422657748LL, 4439967541LL, 4457345083LL, 4474790638LL, 4492304474LL, 4509886856LL, 4527538054LL, 4545258337LL, 4563047975LL};

int64_t __LNT[8] = {-119076027LL,-84716105LL,-50628884LL,-16810069LL,16744533LL,50039019LL,83077392LL,115863561LL};
int64_t __INVT[8] = {4415709348LL,4380524413LL,4345895761LL,4311810305LL,4278255360LL,4245218640LL,4212688229LL,4180652577LL};


short norm8_8(int16_t x)
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

short norm16_16(int32_t x)
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

	uint64_t b =(m << (32-k))&MASK_LOWER_32;
	uint64_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;

	if (b==POW_2_31){
		return (sign==-1?~(k>8?n>>(k-9):n<<(9-k)):(k>8?n>>(k-9):n<<(9-k)));
	}
    int i = 0;
	for (i=0;i<3;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=MASK_LOWER_32;
	}
    x = (x*n)+POW_2_32*n;

	x = (k>8?x>>(k-8):x<<(8-k));
	x >>=32;

	if (sign == -1) x = ~x;

#ifdef DEBUG_FLAG
    verify_overflow_16_bits(x);
#endif

	return (int8_8)x;
}

int8_8 sdiv8_8_v2(int8_8 n,int8_8 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm8_8(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&MASK_LOWER_32;
	uint64_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;

	if (b==POW_2_31){
		x = (k>9?n>>(k-9):n<<(9-k));
		if (x&0xFFFFFFFFFFFF8000) x = 0x7FFF;
		if (sign == -1) x = ~x;
		return x;
	}
    int i = 0;
	for (i=0;i<3;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=MASK_LOWER_32;
	}
    x = (x*n)+POW_2_32*n;

	x = (k>8?x>>(k-8):x<<(8-k));
	x >>=32;

	if (x&0xFFFFFFFFFFFF8000) x = 0x7FFF;
	if (sign == -1) x = ~x;
	return (int8_8)x;
}

int8_8 div8_8(int8_8 n, int8_8 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm8_8(m);
	if (!k) return 0;

    uint64_t z = (((uint16_t)m) << (32-k));
	uint64_t y = -z;
	uint64_t x = y;
	if ((z&MASK_LOWER_32)==POW_2_31){
		return (sign==-1?~(k>9?n>>(k-9):n<<(9-k)):(k>9?n>>(k-9):n<<(9-k)));
	}
	int j;
	uint64_t p=1ULL;


	for (j=0;j<3;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y | POW_2_32;
	uint64_t out = res * n;

    out = (k>8?out>>(k-8):out<<(8-k));
    out >>=32;
    if (sign == -1) out = ~out;
#ifdef DEBUG_FLAG
    verify_overflow_16_bits(out);
#endif
	return (int8_8)(out);
};
int8_8 sdiv8_8(int8_8 n, int8_8 m)
{
    char sign = 1;
    uint64_t out;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm8_8(m);
	if (!k) return 0;

    uint64_t z = (((uint16_t)m) << (32-k));
	uint64_t y = -z;
	uint64_t x = y;
	if ((z&MASK_LOWER_32)==POW_2_31){
		out = (k>9?n>>(k-9):n<<(9-k));
		if (out&0xFFFFFFFFFFFF8000) out = 0x7FFF;
		if (sign == -1) out = ~out;
		return out;
	}
	int j;
	uint64_t p=1ULL;


	for (j=0;j<3;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y | POW_2_32;
	out = res * n;

    out = (k>8?out>>(k-8):out<<(8-k));
    out >>=32;
    if (out&0xFFFFFFFFFFFF8000) out = 0x7FFF;
    if (sign == -1) out = ~out;


	return (int8_8)(out);
};

int16_16 sdiv16_16(int16_16 n, int16_16 m)
{
	uint64_t out;
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

    uint64_t z = (((int32_t)m) << (32-k));
	uint64_t y = -z;
	uint64_t x = y;
	//if (y==POW_2_31) return (k>16?n>>(k-17):n<<(17-k));
	if ((z&MASK_LOWER_32)==POW_2_31){
		out = (k>16?n>>(k-17):n<<(17-k));
		if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
		if (sign == -1) out = ~out;
		return out;
		}
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y;
	out = ((res * n)>>32) + n;

    out = (k>16?out>>(k-16):out<<(16-k));
    if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
    if (sign == -1) out = ~out;
	return (int16_16)(out);
};

int16_16 div16_16(int16_16 n, int16_16 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

    uint64_t z = (((int32_t)m) << (32-k));
	uint64_t y = -z;
	uint64_t x = y;
	//if (y==POW_2_31) return (k>16?n>>(k-17):n<<(17-k));
	if ((z&MASK_LOWER_32)==POW_2_31){
			return (sign==-1?~(k>16?n>>(k-17):n<<(17-k)):(k>16?n>>(k-17):n<<(17-k)));
		}
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y | POW_2_32;
	uint64_t out = res * n;

    out = (k>16?out>>(k-16):out<<(16-k));
    out >>=32;

    if (sign == -1) out = ~out;
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(out);
#endif
	return (int16_16)(out);
};

int16_16 div16_16_v2(int16_16 n,int16_16 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&MASK_LOWER_32;
	uint64_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;

	if (b==POW_2_31){
		return (sign==-1?~(k>8?n>>(k-9):n<<(9-k)):(k>8?n>>(k-9):n<<(9-k)));
	}

    int i = 0;
	for (i=0;i<4;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=MASK_LOWER_32;
	}
    x = (x*n)+POW_2_32*n;

	x = (k>16?x>>(k-16):x<<(16-k));
	x >>=32;

	if (sign == -1) x = ~x;
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(x);
#endif
	return (int16_16)x;
}

int16_16 sdiv16_16_v2(int16_16 n,int16_16 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&MASK_LOWER_32;
	uint64_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;

	if (b==POW_2_31){
		x = (k>16?n>>(k-17):n<<(17-k));
		if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
		if (sign == -1) x = ~x;
		return x;
	}

    int i = 0;
	for (i=0;i<4;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=MASK_LOWER_32;
	}
    x = ((x*n)>>32)+n;

	x = (k>16?x>>(k-16):x<<(16-k));
	if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
	if (sign == -1) x = ~x;
	return (int16_16)x;
}

int8_24 div8_24(int8_24 n, int8_24 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

    uint64_t z = (((int32_t)m) << (32-k));
	uint64_t y = -z;
	uint64_t x = y;
//	if (y==POW_2_31) return (k>24?n>>(k-25):n<<(25-k));
	if ((z&MASK_LOWER_32)==POW_2_31){
				return (sign==-1?~(k>24?n>>(k-25):n<<(25-k)):(k>24?n>>(k-25):n<<(25-k)));
			}
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y | POW_2_32;
	uint64_t out =(((uint64_t) (y * n))>>32)+n;

    out = (k>24?out>>(k-24):out<<(24-k));
    //out >>=32;
    if (sign == -1) {out = ~out;}
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(out);
#endif
	return (int8_24)(out);
};

int8_24 div8_24_v2(int8_24 n,int8_24 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&MASK_LOWER_32;
	uint64_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;
    int i = 0;
	for (i=0;i<4;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=MASK_LOWER_32;
	}
    x = (x*n)+POW_2_32*n;

	x = (k>24?x>>(k-24):x<<(24-k));
	x >>=32;

	 if (sign == -1) {x = ~x;}
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(x);
#endif
	return (int8_24)x;
}

int8_24 sdiv8_24(int8_24 n, int8_24 m)
{
	uint64_t out;
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

    uint64_t z = (((int32_t)m) << (32-k));
	uint64_t y = -z;
	uint64_t x = y;
//	if (y==POW_2_31) return (k>24?n>>(k-25):n<<(25-k));
	if ((z&MASK_LOWER_32)==POW_2_31){
			out = (k>16?n>>(k-17):n<<(17-k));
			if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
			if (sign == -1) out = ~out;
			return out;
			}
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}


	out =(((uint64_t) (y * n))>>32)+n;

    out = (k>24?out>>(k-24):out<<(24-k));
    //out >>=32;

    if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
    if (sign == -1) {out = ~out;}
	return (int8_24)(out);
};

int8_24 sdiv8_24_v2(int8_24 n,int8_24 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&MASK_LOWER_32;
	uint64_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;


	if (b==POW_2_31){
		x = (k>24?n>>(k-25):n<<(25-k));
		if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
		if (sign == -1) x = ~x;
		return x;
	}

    int i = 0;
	for (i=0;i<4;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=MASK_LOWER_32;
	}
    x = ((x*n)>>32)+n;

	x = (k>24?x>>(k-24):x<<(24-k));
	if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
	 if (sign == -1) {x = ~x;}
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
	if (y==POW_2_31) return (k>24?n>>(k-25):n<<(25-k));
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}

	uint64_t res = y | POW_2_32;
	uint64_t out = res * n;

    out = (k>8?out>>(k-8):out<<(8-k));
    out >>=32;
    if (sign == -1) out = ~out;
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(out);
#endif
	return (int24_8)(out);
};

int24_8 div24_8_v2(int24_8 n,int24_8 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&MASK_LOWER_32;
	uint64_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;
    int i = 0;
	for (i=0;i<4;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=MASK_LOWER_32;
	}
    x = (x*n)+POW_2_32*n;

	x = (k>8?x>>(k-8):x<<(8-k));
	x >>=32;

	if (sign == -1) x = ~x;
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(out);
#endif
	return (int24_8)x;
}

int24_8 sdiv24_8(int24_8 n, int24_8 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t out;
	uint64_t z = (((int32_t)m) << (32-k));
	uint64_t y = -z;
	uint64_t x = -z;
	if ((z&MASK_LOWER_32)==POW_2_31){
				out = (k>8?n>>(k-9):n<<(9-k));
				if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
				if (sign == -1) out = ~out;
				return out;
				}
	if (y==POW_2_31) return (k>24?n>>(k-25):n<<(25-k));
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = x*x;
	x = p >> 32;
    p = x*y ;
    y = (p >> 32)+x+y;
	}


	out =((y * n)>>32)+n;

    out = (k>8?out>>(k-8):out<<(8-k));
    if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
    if (sign == -1) out = ~out;

	return (int24_8)(out);
};

int24_8 sdiv24_8_v2(int24_8 n,int24_8 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint64_t b =(m << (32-k))&MASK_LOWER_32;
	uint64_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;
    int i = 0;
	for (i=0;i<4;i++){
	  p = x << 1;
	  x = ((((b*x)>>32)*x)>>32) + ((b*x)>>31) + b;
	  x = p-x;
	  x &=MASK_LOWER_32;
	}
    x = ((x*n)>>32)+n;

	x = (k>8?x>>(k-8):x<<(8-k));

	if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
	if (sign == -1) x = ~x;
	return (int24_8)x;
}

int8_8 sqrt8_8(int8_8 a)
{
    if (a<=0) return 0;
    short k = norm8_8(a);
    uint64_t aa = ((uint64_t)a<<(32-k))&MASK_LOWER_32;
    uint64_t x = (SQRT_C1 - ((SQRT_C2*aa)>>32));
    if (x<POW_2_32) x = 0;
    else x = x & MASK_LOWER_32;

    int i;
    int p_i;
    uint64_t p = 1ULL;
    for (i=0;i<3;i++)
    {
    	p = ((x*x)>>32)+(x << 1) + (1LL << 32);
    	p_i = p>>32;
    	p = p & MASK_LOWER_32;
    	p = ((p*aa)>>32) + aa*p_i;
    	p = (3LL << 32) - p;
    	p_i = (p>>32);
    	p = p & MASK_LOWER_32;
        x = ((p * x) >> 33) + ((p_i * x) >> 1)+(p>>1)+(p_i<<31);
        x = x & MASK_LOWER_32;
    }
    x = ((x * aa)>>32)+aa;

    if (k%2) {x = ((x*SQRT_2)>>32)+x; }
    x = (k>8?x << ((k-8)/2) : x >> ((9-k)/2));

	return (int8_8)(x>>24);
}

int16_16 sqrt16_16(int16_16 a)
{
    if (a<=0) return 0;
    short k = norm16_16(a);
    uint64_t aa = ((uint64_t)a<<(32-k))&MASK_LOWER_32;
    uint64_t x = (SQRT_C1 - ((SQRT_C2*aa)>>32));
    if (x<POW_2_32) x = 0;
    else x = x & MASK_LOWER_32;

    int i;
    int p_i;
    uint64_t p = 1ULL;
    for (i=0;i<3;i++)
    {
    	p = ((x*x)>>32)+(x << 1) + (1LL << 32);
    	p_i = p>>32;
    	p = p & MASK_LOWER_32;
    	p = ((p*aa)>>32) + aa*p_i;
    	p = (3LL << 32) - p;
    	p_i = (p>>32);
    	p = p & MASK_LOWER_32;
        x = ((p * x) >> 33) + ((p_i * x) >> 1)+(p>>1)+(p_i<<31);
        x = x & MASK_LOWER_32;

    }
    x = ((x * aa)>>32)+aa;

    if (k%2) {x = ((x*SQRT_2)>>32)+x; }
    x = (k>16?x << ((k-16)/2) : x >> ((17-k)/2));
	return (int16_16)(x>>16);
}

int8_24 sqrt8_24(int8_24 a)
{
    if (a<=0) return 0;
    short k = norm16_16(a);
    uint64_t aa = ((uint64_t)a<<(32-k))&MASK_LOWER_32;
    uint64_t x = (SQRT_C1 - ((SQRT_C2*aa)>>32));

    if (x<POW_2_32) x = 0;
    else x = x & MASK_LOWER_32;

    int i;
    int p_i;
    uint64_t p = 1ULL;
    for (i=0;i<3;i++)
    {
    	p = ((x*x)>>32)+(x << 1) + (1LL << 32);
    	p_i = p>>32;
    	p = p & MASK_LOWER_32;
    	p = ((p*aa)>>32) + aa*p_i;
    	p = (3LL << 32) - p;
    	p_i = (p>>32);
    	p = p & MASK_LOWER_32;
        x = ((p * x) >> 33) + ((p_i * x) >> 1)+(p>>1)+(p_i<<31);
        x = x & MASK_LOWER_32;

    }
    x = ((x * aa)>>32)+aa;

    if (k%2) {x = ((x*SQRT_2)>>32)+x; }
    x = (k>24?x << ((k-24)/2) : x >> ((25-k)/2));
	return (int8_24)(x>>8);
}

int24_8 sqrt24_8(int24_8 a)
{
    if (a<=0) return 0;
    short k = norm16_16(a);
    uint64_t aa = ((uint64_t)a<<(32-k))&MASK_LOWER_32;
    uint64_t x = (SQRT_C1 - ((SQRT_C2*aa)>>32));
    if (x<POW_2_32) x = 0;
    else x = x & MASK_LOWER_32;

    int i;
    int p_i;
    uint64_t p = 1ULL;
    for (i=0;i<3;i++)
    {
    	p = ((x*x)>>32)+(x << 1) + (1LL << 32);
    	p_i = p>>32;
    	p = p & MASK_LOWER_32;
    	p = ((p*aa)>>32) + aa*p_i;
    	p = (3LL << 32) - p;
    	p_i = (p>>32);
    	p = p & MASK_LOWER_32;
        x = ((p * x) >> 33) + ((p_i * x) >> 1)+(p>>1)+(p_i<<31);
        x = x & MASK_LOWER_32;

    }
    x = ((x * aa)>>32)+aa;

    if (k%2) {x = ((x*SQRT_2)>>32)+x; }
    x = (k>8?x << ((k-8)/2) : x >> ((9-k)/2));
	return (int24_8)(x>>24);
}

int8_8 log8_8(int8_8 aa)
{
	if (aa<=0) return 0;
	short k = norm8_8(aa);
	uint64_t x = ((uint64_t)aa)<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (x*__A[key])>>32;
	uint64_t t;
	if (x<POW_2_31) t=x;
	else t = x - POW_2_32;

	uint64_t app = t - ((t*t)>>33);
	app = app - __LNA[key];
	app = app + (k-8)*LN_2;
#ifdef DEBUG_FLAG
    verify_overflow_16_bits(app>>24);
#endif
	return (int8_8)(app>>24);
}

int16_16 log16_16(int16_16 aa)
{
	if (aa<=0) return 0;
	short k = norm16_16(aa);
	uint64_t x = ((uint64_t)aa)<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (x*__A[key])>>32;
	uint64_t t;
	if (x<POW_2_31) t=x;
	else t = x - POW_2_32;

	uint64_t app = t - ((t*t)>>33);
	app = app - __LNA[key];
	app = (app<<4) + (k-16)*LN_2_EXTRA; //increased the precision with 4 bits
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app>>20);
#endif
	return (int16_16)(app>>20);
}

int8_24 log8_24(int8_24 aa)
{
	/*Needs to double the number of entries in the lookup tables to make the interval (0.99,1.01)*/
	if (aa<=0) return 0;
	short k = norm16_16(aa);
	uint64_t x = ((uint64_t)aa)<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (x*__A[key])>>32;
	uint64_t t;
	if (x<POW_2_31) t=x;
	else t = x - POW_2_32;

	uint64_t app = t - ((t*t)>>33);
	app = (app<<8) - __LNA[key];
	app = app + (k-24)*(LN_2_EXTRA<<4); //increased the precision with 4 bits
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app>>16);
#endif
	return (int8_24)(app>>16);
}



int24_8 log24_8(int24_8 aa)
{
	if (aa<=0) return 0;
	short k = norm16_16(aa);
	uint64_t x = ((uint64_t)aa)<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (x*__A[key])>>32;
	uint64_t t;
	if (x<POW_2_31) t=x;
	else t = x - POW_2_32;

	uint64_t app = t - ((t*t)>>33);
	app = app - __LNA[key];
	app = app + (k-8)*LN_2; //increased the precision with 4 bits
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app>>24);
#endif
	return (int24_8)(app>>24);
}

int8_8 exp8_8(int8_8 a)
{
	int64_t x = (((int64_t)a)*LN_2_INV)>>8;
	int32_t t = (x>>32);
	int64_t f = (x&MASK_LOWER_32);
	x = (f*LN_2)>>32;

	uint16_t key = (x>>28);
	x = x -__AA[key];
	uint64_t app = (x+((x*x)>>33))&MASK_LOWER_32;
    app = ((app*(__EXPAA[key]&MASK_LOWER_32))>>32)+(x<0?0:__EXPAA[key])+app*(__EXPAA[key]>>32);

    if (t<24) app >>= (24-t);
    else app <<= (t-24);
#ifdef DEBUG_FLAG
    verify_overflow_16_bits(app);
#endif
	return (int8_8)app;
}

int8_8 sexp8_8(int8_8 a)
{
	int64_t x = (((int64_t)a)*LN_2_INV)>>8;
	int32_t t = (x>>32);
	int64_t f = (x&MASK_LOWER_32);
	x = (f*LN_2)>>32;

	uint16_t key = (x>>28);
	x = x -__AA[key];
	uint64_t app = (x+((x*x)>>33))&MASK_LOWER_32;
    app = ((app*(__EXPAA[key]&MASK_LOWER_32))>>32)+(x<0?0:__EXPAA[key])+app*(__EXPAA[key]>>32);

    if (t<24) app >>= (24-t);
    else app <<= (t-24);
    if (app&0xFFFFFFFFFFFF8000)
    {
    	app = 0x7FFF;
    }
	return (int8_8)app;
}

int16_16 exp16_16(int16_16 a)
{
	int64_t x = (((int64_t)a)*LN_2_INV)>>16;
	int32_t t = (x>>32);
	int64_t f = (x&MASK_LOWER_32);
	x = (f*LN_2)>>32;

	uint16_t key = (x>>28);
	x = x - __AA[key];
	uint64_t app = (x+((x*x)>>33))&MASK_LOWER_32;
    app = ((app*(__EXPAA[key]&MASK_LOWER_32))>>32)+(x<0?0:__EXPAA[key])+app*(__EXPAA[key]>>32);

    if (t<16) app >>= (16-t);
    else app <<= (t-16);
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app);
#endif
	return (int16_16)app;
}

int16_16 exp16_16_v2(int16_16 a)
{
	int64_t x = (((int64_t)a)*LN_2_INV)>>16;
	int32_t t = (x>>32);
	int64_t f = (x&MASK_LOWER_32);
	x = (f*LN_2)>>32;

	uint16_t key = (x>>28);
	x = x - __AA_v2[key];
	/* better approximation */
	short skey=(x&MASK_5_TO_8)>>24;
	uint64_t xx = (x&MASK_FROM_9) - POW_2_23;
	uint64_t app = (xx+((xx*xx)>>33));
	short app_i = (app>>32)+1;
	app &= MASK_LOWER_32;
	app = (((app*__EXPX[skey])>>32)+app_i*__EXPX[skey]);
	app &= MASK_LOWER_32;

    /* end */

    app = ((app*(__EXPAA_v2[key]&MASK_LOWER_32))>>32)+__EXPAA_v2[key]+app*(__EXPAA_v2[key]>>32);

    if (t<16) app >>= (16-t);
    else app <<= (t-16);
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app);
#endif
	return (int16_16)app;
}

int16_16 sexp16_16_v2(int16_16 a)
{
	int64_t x = (((int64_t)a)*LN_2_INV)>>16;
	int32_t t = (x>>32);
	int64_t f = (x&MASK_LOWER_32);
	x = (f*LN_2)>>32;

	uint16_t key = (x>>28);
	x = x - __AA_v2[key];
	/* better approximation */
	short skey=(x&MASK_5_TO_8)>>24;
	uint64_t xx = (x&MASK_FROM_9) - POW_2_23;
	uint64_t app = (xx+((xx*xx)>>33));
	short app_i = (app>>32)+1;
	app &= MASK_LOWER_32;
	app = (((app*__EXPX[skey])>>32)+app_i*__EXPX[skey]);
	app &= MASK_LOWER_32;

    /* end */

    app = ((app*(__EXPAA_v2[key]&MASK_LOWER_32))>>32)+__EXPAA_v2[key]+app*(__EXPAA_v2[key]>>32);

    if (t<16) app >>= (16-t);
    else app <<= (t-16);

    if (app&0xFFFFFFFF80000000)
    {
       	app = 0x7FFFFFFF;
    }
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app);
#endif
	return (int16_16)app;
}

int24_8 exp24_8(int24_8 a)
{
	int64_t x = (((int64_t)a)*LN_2_INV)>>8;
	int32_t t = (x>>32);
	int64_t f = (x&MASK_LOWER_32);
	x = (f*LN_2)>>32;

	uint16_t key = (x>>28);
	x = x - __AA[key];
	uint64_t app = (x+((x*x)>>33))&MASK_LOWER_32;
    app = ((app*(__EXPAA[key]&MASK_LOWER_32))>>32)+(x<0?0:__EXPAA[key])+app*(__EXPAA[key]>>32);

    if (t<24) app >>= (24-t);
    else app <<= (t-24);
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app);
#endif
	return (int24_8)app;
}

int24_8 exp24_8_v2(int24_8 a)
{
	int64_t x = (((int64_t)a)*LN_2_INV)>>8;
	int32_t t = (x>>32);
	int64_t f = (x&MASK_LOWER_32);
	x = (f*LN_2)>>32;

	uint16_t key = (x>>28);
	x = x - __AA_v2[key];
	/* better approximation */
	short skey=(x&MASK_5_TO_8)>>24;
	uint64_t xx = (x&MASK_FROM_9) - POW_2_23;
	uint64_t app = (xx+((xx*xx)>>33));
	short app_i = (app>>32)+1;
	app &= MASK_LOWER_32;
	app = (((app*__EXPX[skey])>>32)+app_i*__EXPX[skey]);
	app &= MASK_LOWER_32;

	/* end */


    app = ((app*(__EXPAA_v2[key]&MASK_LOWER_32))>>32)+ __EXPAA_v2[key]+app*(__EXPAA_v2[key]>>32);
    if (t<24) app >>= (24-t);
    else app <<= (t-24);
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app);
#endif
	return (int24_8)app;
}

int8_24 exp8_24_v2(int8_24 a)
{
	int64_t x = (((int64_t)a)*LN_2_INV)>>24;
	int32_t t = (x>>32);
	int64_t f = (x&MASK_LOWER_32);
	x = (f*LN_2)>>32;

	uint16_t key = (x>>28);
	x = x - __AA_v2[key];
	/* better approximation */
	short skey=(x&MASK_5_TO_8)>>24;
	uint64_t xx = (x&MASK_FROM_9) - POW_2_23;
	uint64_t app = (xx+((xx*xx)>>33));
	short app_i = (app>>32)+1;
	app &= MASK_LOWER_32;
	app = (((app*__EXPX[skey])>>32)+app_i*__EXPX[skey]);
	app &= MASK_LOWER_32;

	/* end */

    app = ((app*(__EXPAA_v2[key]&MASK_LOWER_32))>>32)+ __EXPAA_v2[key]+app*(__EXPAA_v2[key]>>32);
    if (t<8) app >>= (8-t);
    else app <<= (t-8);
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app);
#endif
	return (int8_24)app;
}

int8_24 log8_24_v2(int8_24 aa)
{
	/*Needs to double the number of entries in the lookup tables to make the interval (0.99,1.01)*/
	if (aa<=0) return 0;
	short k = norm16_16(aa);
	uint64_t x = ((uint64_t)aa)<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (x*__A[key])>>32;
	int64_t t;
	char sign;
	if (x<POW_2_31) {t=x;sign = -1;}
	else {t = x - POW_2_32;sign = 1;}

	/* better approximation*/
	t += POW_2_27;
	short skey=(t&MASK_5_TO_7)>>25;
	t = (t & MASK_FROM_8) - POW_2_24;
	t = (t*__INVT[skey])>>32;
	int64_t app = __LNT[skey]+t - ((t*t)>>33);
	/* better approximation end*/
	app = (app<<8) - __LNAA[key];
	app = app + (k-24)*(LN_2_EXTRA<<4); //increased the precision with 4 bits
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app>>16);
#endif
	return (int8_24)(app>>16);
}

int16_16 log16_16_v2(int16_16 aa)
{
	/*Needs to double the number of entries in the lookup tables to make the interval (0.99,1.01)*/
	if (aa<=0) return 0;
	short k = norm16_16(aa);
	uint64_t x = ((uint64_t)aa)<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (x*__A[key])>>32;
	int64_t t;
	char sign;
	if (x<POW_2_31) {t=x;sign = -1;}
	else {t = x - POW_2_32;sign = 1;}

	/* better approximation*/
	t += POW_2_27;
	short skey=(t&MASK_5_TO_7)>>25;
	t = (t & MASK_FROM_8) - POW_2_24;
	t = (t*__INVT[skey])>>32;
	int64_t app = __LNT[skey]+t - ((t*t)>>33);
	/* better approximation end*/
	app = (app<<8) - __LNAA[key];
	app = app + (k-16)*(LN_2_EXTRA<<4); //increased the precision with 4 bits
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app>>24);
#endif
	return (int16_16)(app>>24);
}

int8_8 sin8_8(int8_8 a)
{
	uint64_t x = a;
	short sign = 1;
	if (a<0)
	{
		sign = -1;
		x = -x;
	}
	x = (x*PI_INV)>>7;
	uint64_t p = (x>>32)&0x3;
	x &= MASK_LOWER_32;
	x = ((x * (PI&MASK_LOWER_32))>>33)+((3*x)>>1);

	x = x >> 3;

	uint64_t x_sin;
	uint64_t x_cos;
	uint64_t x2 = (x*x)>>32;
	uint64_t x3 = (x2*x)>>32;
	uint64_t x4 = (x3*x)>>32;
	uint64_t x5 = (x4*x)>>32;

	x_sin = x - ((x3*SIN_C1)>>32)+((x5*SIN_C2)>>32);
	x_cos = POW_2_32 - (x2>>1) + ((x4*COS_C1)>>32);

	uint64_t aux;

	aux = (x_sin*x_cos)>>31;
	x_cos = ((x_cos*x_cos)>>31) - POW_2_32;
	x_sin = aux;

	aux = (x_sin*x_cos)>>31;
	x_cos = ((x_cos*x_cos)>>31) - POW_2_32;
	x_sin = aux;

	aux = (x_sin*x_cos)>>31;
	x_cos = ((x_cos*x_cos)>>31) - POW_2_32;
	x_sin = aux;

	if (p%4 == 1){
		x_sin = x_cos;
	}

	if (p%4 == 2){
		x_sin = -x_sin;
	}

	if (p%4 == 3){
		x_sin = -x_cos;
	}

	if (sign==-1)
	{
		x_sin = -x_sin;
	}

	return (x_sin>>24);
}

inline char bits4_most_significant(char x)
{
	if (!x) return 0;
	return (x&0xC?(x&0x8?4:3):(x&0x2?2:1));
}
