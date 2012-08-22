/*
 * FixedPointMath.c
 *
 *  Created on: 18 Jul 2012
 *      Author: moisem
 */
#include "FixedPointMath.h"
#include "Info.h"
uint32_t __A[16]={4037269258LL, 3547137696LL, 3111465196LL, 2721652960LL, 2370821947LL, 2053403411LL, 1764841107LL, 1501371176LL, 1259857073LL, 1037664098LL, 832562891LL, 642654365LL, 466310734LL, 302128733LL, 148892199LL, 5541893LL};
uint32_t __LNA[16]={2846223171LL, 2585842403LL, 2340348885LL, 2108131938LL, 1887828916LL, 1678276757LL, 1478474811LL, 1287555944LL, 1104763792LL, 929434661LL, 760982981LL, 598889506LL, 442691664LL, 291975593LL, 146369537LL, 5538320LL};

uint64_t __AA[16]={134217728LL, 402653184LL, 671088640LL, 939524096LL, 1207959552LL, 1476395008LL, 1744830464LL, 2013265920LL, 2281701376LL, 2550136832LL, 2818572288LL, 3087007744LL, 3355443200LL, 3623878656LL, 3892314112LL, 4160749568LL};
uint64_t __EXPAA[16]={4431304193LL, 4717098759LL, 5021325491LL, 5345173162LL, 5689907212LL, 6056874699LL, 6447509556LL, 6863338196LL, 7305985480LL, 7777181060LL, 8278766144LL, 8812700687LL, 9381071050LL, 9986098151LL, 10630146148LL, 11315731672LL};

uint64_t __EXPAA_v2[16]={4294967296LL, 4571968887LL, 4866835547LL, 5180719472LL, 5514847171LL, 5870524256LL, 6249140541LL, 6652175479LL, 7081203937LL, 7537902354LL, 8024055288LL, 8541562392LL, 9092445836LL, 9678858211LL, 10303090934LL, 10967583209LL};

uint64_t __EXPX[16] = {4303364101LL, 4320206992LL, 4337115804LL, 4354090795LL, 4371132225LL, 4388240352LL, 4405415440LL, 4422657748LL, 4439967541LL, 4457345083LL, 4474790638LL, 4492304474LL, 4509886856LL, 4527538054LL, 4545258337LL, 4563047975LL};

int32_t __LNT[8] = {-119076027LL,-84716105LL,-50628884LL,-16810069LL,16744533LL,50039019LL,83077392LL,115863561LL};
uint32_t __INVT[8] = {120742052LL, 85557117LL, 50928465LL, 16843009LL,4278255360LL,4245218640LL,4212688229LL,4180652577LL};


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

	uint32_t b =(m << (32-k))&MASK_LOWER_32;
	uint32_t x = (~((b<<1)&MASK_LOWER_32)+1)&MASK_LOWER_32;
	uint64_t p = 1LL;
    uint64_t q;
	if (b==POW_2_31){
		return (sign==-1?~(k>8?n>>(k-9):n<<(9-k)):(k>8?n>>(k-9):n<<(9-k)));
	}
    int i = 0;
	for (i=0;i<3;i++){
	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;
	}
    x = (((int64_t)x*n)>>32)+n;

	x = (k>8?x>>(k-8):x<<(8-k));

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

	uint32_t b =(m << (32-k));
	uint32_t x = -(b<<1);
	uint64_t p = 1LL;
	uint64_t q;

	if (b==POW_2_31){
		x = (k>9?n>>(k-9):n<<(9-k));
		if (x&0xFFFFFFFFFFFF8000) x = 0x7FFF;
		if (sign == -1) x = ~x;
		return x;
	}

	int i = 0;
	
	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;

	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;

	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;
	
    x = (((int64_t)x*n)>>32)+n;

	x = (k>8?x>>(k-8):x<<(8-k));

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

    uint32_t z = (((uint16_t)m) << (32-k));
	uint32_t y = -z;
	uint32_t x = y;
	uint32_t out;
	if (z==POW_2_31){
		out = (k>9?n>>(k-9):n<<(9-k));
		if (sign == -1) out = ~out;
		return out;
	}
	int j;
	uint64_t p=1ULL;


	
        p = (int64_t) x*x;
	x = p >> 32;
        p = (int64_t) x*y ;
        y = (p >> 32)+x+y;

        p = (int64_t) x*x;
	x = p >> 32;
        p = (int64_t) x*y ;
        y = (p >> 32)+x+y;
	
        p = (int64_t) x*x;
	x = p >> 32;
        p = (int64_t) x*y ;
        y = (p >> 32)+x+y; 

	uint64_t res = (int64_t) y*n;
    out = (res>>32)+n;

    out = (k>8?out>>(k-8):out<<(8-k));
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

    uint32_t z = (((uint16_t)m) << (32-k));
	uint32_t y = -z;
	uint32_t x = y;
	if (z==POW_2_31){
		out = (k>9?n>>(k-9):n<<(9-k));
		if (out&0xFFFFFFFFFFFF8000) out = 0x7FFF;
		if (sign == -1) out = ~out;
		return out;
	}
	int j;
	uint64_t p=1ULL;


	for (j=0;j<3;j++){
    p = (int64_t)x*x;
	x = p >> 32;
    p = (int64_t)x*y ;
    y = (p >> 32)+x+y;
	}

    out = ((y * n)>>32) + n;

    out = (k>8?out>>(k-8):out<<(8-k));

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

       
        uint32_t z = (((int32_t)m) << (32-k));
	uint32_t y = -z;
	uint32_t x = y;
	//if (y==POW_2_31) return (k>16?n>>(k-17):n<<(17-k));
	if (z==POW_2_31){
		out = (k>16?n>>(k-17):n<<(17-k));
		if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
		if (sign == -1) out = ~out;
		return out;
		}
	int j;
	uint64_t p=1ULL;

	for (j=0;j<3;j++){
    p = (int64_t)x*x;
	x = p >> 32;
    p = (int64_t)x*y ;
    y = (p >> 32)+x+y;
	}


	out = (((int64_t)y * n)>>32)+n;

    out = (k>16?out>>(k-16):out<<(16-k));
    if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
    if (sign == -1) out = ~out;
	return (int16_16)(out);
};

int16_16 div16_16(int16_16 n, int16_16 m)
{
    uint64_t out;
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

    uint32_t z = (((int32_t)m) << (32-k));
	uint32_t y = -z;
	uint32_t x = y;
	//if (y==POW_2_31) return (k>16?n>>(k-17):n<<(17-k));
	if (z==POW_2_31){
		out = (k>16?n>>(k-17):n<<(17-k));
		if (sign == -1) out = ~out;
		return out;
		}
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = (int64_t)x*x;
	x = p >> 32;
    p = (int64_t)x*y ;
    y = (p >> 32)+x+y;
	}

    out = (((int64_t)y * n)>>32)+n;

    out = (k>16?out>>(k-16):out<<(16-k));

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

	uint32_t b =(m << (32-k));
	uint32_t x = -(b<<1);
	uint32_t p = 1LL;
        uint32_t q;

        if (b==POW_2_31){
		x = (k>16?n>>(k-17):n<<(17-k));
		if (sign == -1) x = ~x;
		return x;
		}

    int i = 0;
	for (i=0;i<4;i++){
	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;
	}
    x = (((int64_t)x*n)>>32)+n;

	x = (k>16?x>>(k-16):x<<(16-k));

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

	uint32_t b =(m << (32-k));
	uint32_t x = -(b<<1);
	uint32_t p = 1LL;
        uint32_t q;

        if (b==POW_2_31){
		x = (k>16?n>>(k-17):n<<(17-k));
		if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
		if (sign == -1) x = ~x;
		return x;
		}

    int i = 0;
	for (i=0;i<4;i++){
	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;
	}
    x = (((int64_t)x*n)>>32)+n;

	x = (k>16?x>>(k-16):x<<(16-k));
        if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
	if (sign == -1) x = ~x;
	return (int16_16)x;
}


int8_24 div8_24(int8_24 n, int8_24 m)
{
   uint64_t out;
      char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

        uint32_t z = (((int32_t)m) << (32-k));
	uint32_t y = -z;
	uint32_t x = y;
//	if (y==POW_2_31) return (k>24?n>>(k-25):n<<(25-k));
	if (z==POW_2_31){
		out = (k>16?n>>(k-17):n<<(17-k));
		if (sign == -1) out = ~out;
		return out;
			}
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = (int64_t)x*x;
	x = p >> 32;
    p = (int64_t)x*y ;
    y = (p >> 32)+x+y;
	}

     out = (((int64_t)y * n)>>32)+n;

    out = (k>24?out>>(k-24):out<<(24-k));
    //out >>=32;
    if (sign == -1) {out = ~out;}
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(out);
#endif
	return (int8_24)(out);
};

int8_24 sdiv8_24_v2(int8_24 n,int8_24 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint32_t b =(m << (32-k));
	uint32_t x = -(b<<1);
	uint64_t p = 1LL;
        uint64_t q;

        if (b==POW_2_31){
		x = (k>24?n>>(k-25):n<<(25-k));
                if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
		if (sign == -1) x = ~x;
		return x;
	}

    int i = 0;
	for (i=0;i<4;i++){
	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;
	}
    x = (((int64_t)x*n)>>32)+n;

	x = (k>24?x>>(k-24):x<<(24-k));
         if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
	 if (sign == -1) {x = ~x;}

	return (int8_24)x;
}


int8_24 div8_24_v2(int8_24 n,int8_24 m)
{
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;

	uint32_t b =(m << (32-k));
	uint32_t x = -(b<<1);
	uint64_t p = 1LL;
        uint64_t q;

        if (b==POW_2_31){
		x = (k>24?n>>(k-25):n<<(25-k));
                
		if (sign == -1) x = ~x;
		return x;
	}

    int i = 0;
	for (i=0;i<4;i++){
	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;
	}
    x = (((int64_t)x*n)>>32)+n;

	x = (k>24?x>>(k-24):x<<(24-k));

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

        uint32_t z = (((int32_t)m) << (32-k));
	uint32_t y = -z;
	uint32_t x = y;
//	if (y==POW_2_31) return (k>24?n>>(k-25):n<<(25-k));
	if (z==POW_2_31){
		out = (k>16?n>>(k-17):n<<(17-k));
                if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
		if (sign == -1) out = ~out;
		return out;
			}
	int j;
	uint64_t p=1ULL;

	for (j=0;j<4;j++){
    p = (int64_t)x*x;
	x = p >> 32;
    p = (int64_t)x*y ;
    y = (p >> 32)+x+y;
	}

     out = (((int64_t)y * n)>>32)+n;

    out = (k>24?out>>(k-24):out<<(24-k));
    //out >>=32;
    if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
    if (sign == -1) {out = ~out;}
	
	return (int8_24)out;
}

int24_8 div24_8(int24_8 n, int24_8 m)
{
uint64_t out;
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;


	uint32_t y = -(((int32_t)m) << (32-k));
	uint32_t x = -(((int32_t)m) << (32-k));
	if (y==POW_2_31){
		out = (k>8?n>>(k-9):n<<(9-k));
		if (sign == -1) out = ~out;
		return out;
	}
	int j;
	uint64_t p=1ULL;

   for (j=0;j<4;j++){
    p = (int64_t)x*x;
	x = p >> 32;
    p = (int64_t)x*y ;
    y = (p >> 32)+x+y;
	}

     out = (((int64_t)y * n)>>32)+n;


    out = (k>8?out>>(k-8):out<<(8-k));
    
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

	uint32_t b =(m << (32-k));
	uint32_t x = -(b<<1);
	uint64_t p = 1LL;
       uint64_t q;

        if (b==POW_2_31){
		x = (k>24?n>>(k-25):n<<(25-k));
                
		if (sign == -1) x = ~x;
		return x;
	}

    int i = 0;
	for (i=0;i<4;i++){
	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;
	}
    x = (((int64_t)x*n)>>32)+n;

	x = (k>8?x>>(k-8):x<<(8-k));
	

	if (sign == -1) x = ~x;
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(out);
#endif
	return (int24_8)x;
}

int24_8 sdiv24_8(int24_8 n, int24_8 m)
{
 uint64_t out;
    char sign = 1;
	if (m<0) {m = -m; sign = -1;}
	if (n<0) {n = -n; sign *= -1;}
	short k = norm16_16(m);
	if (!k) return 0;


	uint32_t y = -(((int32_t)m) << (32-k));
	uint32_t x = -(((int32_t)m) << (32-k));
	if (y==POW_2_31){
		out = (k>8?n>>(k-9):n<<(9-k));
                if (out&0xFFFFFFFF80000000) out = 0x7FFFFFFF;
		if (sign == -1) out = ~out;
		return out;
	}
	int j;
	uint64_t p=1ULL;

   for (j=0;j<4;j++){
    p = (int64_t)x*x;
	x = p >> 32;
    p = (int64_t)x*y ;
    y = (p >> 32)+x+y;
	}

     out = (((int64_t)y * n)>>32)+n;


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

	uint32_t b =(m << (32-k));
	uint32_t x = -(b<<1);
	uint64_t p = 1LL;
       uint64_t q;

        if (b==POW_2_31){
		x = (k>24?n>>(k-25):n<<(25-k));
                if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
		if (sign == -1) x = ~x;
		return x;
	}

    int i = 0;
	for (i=0;i<4;i++){
	  p = ((int64_t)x) << 1;
	  q = ((int64_t)b*x)>>32;
	  q = (int64_t)((int32_t)q)*x;
	  x = (q>>32) + (((int64_t)b*x)>>31) + b;
	  x = p-x;
	}
    x = (((int64_t)x*n)>>32)+n;

	x = (k>8?x>>(k-8):x<<(8-k));
	
        if (x&0xFFFFFFFF80000000) x = 0x7FFFFFFF;
	if (sign == -1) x = ~x;

	return (int24_8)x;
}

int8_8 sqrt8_8(int8_8 a)
{
    if (a<=0) return 0;
    short k = norm8_8(a);
    uint32_t aa = (a<<(32-k));
    int32_t c2_aux = SQRT_C2 & MASK_LOWER_32;
    uint64_t xx = (((int64_t) c2_aux*aa)>>32)+aa;
     xx = (SQRT_C1 -xx);
   uint32_t x;
    if (xx<POW_2_32) x = 0;
    else x = xx & MASK_LOWER_32;

    int i;
    uint64_t p = 1ULL;
    int32_t y,t1,t2,t3,aa1;
    aa1 = aa >> 1;
    for (i=0;i<2;i++)
    {
       y = x+(x>>1)+0x80000000;
       p = (int64_t)x*aa1; t1 = p>>32;
       p = (int64_t)t1*x; t2 = p>>32;
       p = (int64_t)t2*x; t3 = p>>32;
       x = y - aa1 - t1 - (t1<<1) - t2 - (t2<<1) - t3;
    }
    uint32_t res = (((int64_t)x * aa)>>32)+aa;

    uint64_t aux=res;
    if (k%2) {aux = (((uint64_t)res*SQRT_2)>>32)+res; }
    aux = (k>8?aux << ((k-8)/2) : aux >> ((9-k)/2));

	return (int8_8)(aux>>24);
}

int16_16 sqrt16_16(int16_16 a)
{
    if (a<=0) return 0;
    short k = norm16_16(a);
    uint32_t aa = (a<<(32-k));
     int32_t c2_aux = SQRT_C2 & MASK_LOWER_32;
     uint64_t xx = (((int64_t) c2_aux*aa)>>32)+aa;
      xx = (SQRT_C1 -xx);
    uint32_t x;
     if (xx<POW_2_32) x = 0;
     else x = xx & MASK_LOWER_32;

     int i;
    uint64_t p = 1ULL;
     int32_t y,t1,t2,t3,aa1;
     aa1 = aa >> 1;
     for (i=0;i<3;i++)
     {
        y = x+(x>>1)+0x80000000;
        p = (int64_t)x*aa1; t1 = p>>32;
        p = (int64_t)t1*x; t2 = p>>32;
        p = (int64_t)t2*x; t3 = p>>32;
        x = y - aa1 - t1 - (t1<<1) - t2 - (t2<<1) - t3;
     }
     uint32_t res = (((int64_t)x * aa)>>32)+aa;

        uint64_t aux=res;
        if (k%2) {aux = (((uint64_t)res*SQRT_2)>>32)+res; }
        aux = (k>16?aux << ((k-16)/2) : aux >> ((17-k)/2));

    	return (int16_16)(aux>>16);
}

int8_24 sqrt8_24(int8_24 a)
{
	 if (a<=0) return 0;
	    short k = norm16_16(a);
	    uint32_t aa = (a<<(32-k));
	     int32_t c2_aux = SQRT_C2 & MASK_LOWER_32;
	     uint64_t xx = (((int64_t) c2_aux*aa)>>32)+aa;
	      xx = (SQRT_C1 -xx);
	    uint32_t x;
	     if (xx<POW_2_32) x = 0;
	     else x = xx & MASK_LOWER_32;

	     int i;
	    uint64_t p = 1ULL;
	     int32_t y,t1,t2,t3,aa1;
	     aa1 = aa >> 1;
	     for (i=0;i<4;i++)
	     {
	        y = x+(x>>1)+0x80000000;
	        p = (int64_t)x*aa1; t1 = p>>32;
	        p = (int64_t)t1*x; t2 = p>>32;
	        p = (int64_t)t2*x; t3 = p>>32;
	        x = y - aa1 - t1 - (t1<<1) - t2 - (t2<<1) - t3;
	     }
	     uint32_t res = (((int64_t)x * aa)>>32)+aa;

	        uint64_t aux=res;
	        if (k%2) {aux = (((uint64_t)res*SQRT_2)>>32)+res; }
	        aux = (k>24?aux << ((k-24)/2) : aux >> ((25-k)/2));

	return (int8_24)(aux>>8);
}

int24_8 sqrt24_8(int24_8 a)
{
	 if (a<=0) return 0;
	    short k = norm16_16(a);
	    uint32_t aa = (a<<(32-k));
	     int32_t c2_aux = SQRT_C2 & MASK_LOWER_32;
	     uint64_t xx = (((int64_t) c2_aux*aa)>>32)+aa;
	      xx = (SQRT_C1 -xx);
	    uint32_t x;
	     if (xx<POW_2_32) x = 0;
	     else x = xx & MASK_LOWER_32;

	     int i;
	    uint64_t p = 1ULL;
	     int32_t y,t1,t2,t3,aa1;
	     aa1 = aa >> 1;
	     for (i=0;i<3;i++)
	     {
	        y = x+(x>>1)+0x80000000;
	        p = (int64_t)x*aa1; t1 = p>>32;
	        p = (int64_t)t1*x; t2 = p>>32;
	        p = (int64_t)t2*x; t3 = p>>32;
	        x = y - aa1 - t1 - (t1<<1) - t2 - (t2<<1) - t3;
	     }
	     uint32_t res = (((int64_t)x * aa)>>32)+aa;

	        uint64_t aux=res;
	        if (k%2) {aux = (((uint64_t)res*SQRT_2)>>32)+res; }
	        aux = (k>8?aux << ((k-8)/2) : aux >> ((9-k)/2));

	return (int24_8)(aux>>24);
}

int8_8 log8_8(int8_8 aa)
{
	if (aa<=0) return 0;
	short k = norm8_8(aa);
	uint32_t x = aa<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (((int64_t)x*__A[key])>>32)+x;
	int32_t t;
	if (x<POW_2_31) t=x;
	else t = x-POW_2_32;

	uint64_t app = t - (((int64_t)t*t)>>33);
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
	uint32_t x = aa<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (((int64_t)x*__A[key])>>32)+x;
	int32_t t;
	if (x<POW_2_31) t=x;
	else t = x-POW_2_32;

	uint64_t app = t - (((int64_t)t*t)>>33);
	app = app - __LNA[key];
	app = app + (k-16)*LN_2;
#ifdef DEBUG_FLAG
    verify_overflow_16_bits(app>>16);
#endif
	return (int16_16)(app>>16);
	//app = (app<<4) + (k-16)*LN_2_EXTRA; //increased the precision with 4 bits
}

int8_24 log8_24(int8_24 aa)
{
	/*Needs to double the number of entries in the lookup tables to make the interval (0.99,1.01)*/
	if (aa<=0) return 0;
	short k = norm16_16(aa);
	uint64_t x = ((uint64_t)aa)<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (((int64_t)x*__A[key])>>32)+x;
	uint64_t t;
	if (x<POW_2_31) t=x;
	else t = x - POW_2_32;

	uint64_t app = t - ((t*t)>>33);
	app = app - __LNA[key];
	app = app + (k-24)*(LN_2); //increased the precision with 4 bits
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app>>12);
#endif
	return (int8_24)(app>>8);
}




int24_8 log24_8(int24_8 aa)
{
	if (aa<=0) return 0;
	short k = norm16_16(aa);
	uint32_t x = aa<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (((int64_t)x*__A[key])>>32)+x;
	int32_t t;
	if (x<POW_2_31) t=x;
	else t = x-POW_2_32;

	uint64_t app = t - (((int64_t)t*t)>>33);
	app = app - __LNA[key];
	app = app + (k-8)*LN_2;
#ifdef DEBUG_FLAG
    verify_overflow_16_bits(app>>24);
#endif
	return (int24_8)(app>>24);
}

int8_8 exp8_8(int8_8 a)
{
	int64_t xx = (((int64_t)a)*LN_2_INV)>>8;
	int32_t t = (xx>>32);
	uint32_t f = (xx&MASK_LOWER_32);
	int32_t x = ((uint64_t)f*LN_2)>>32;

	uint16_t key = (((uint32_t)x)>>28);
	x = x -__AA[key];
	uint64_t app = (x+(((int64_t)x*x)>>33))&MASK_LOWER_32;
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
	uint32_t aux = 0;
	if (key>0) aux=(__AA[key-1]+__AA[key])>>1;
	x = x - aux;
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
	uint32_t aux = 0;
	if (key>0) aux=(__AA[key-1]+__AA[key])>>1;
	x = x - aux;
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
	uint32_t aux = 0;
	if (key>0) aux=(__AA[key-1]+__AA[key])>>1;
	x = x - aux;
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
	uint32_t aux = 0;
	if (key>0) aux=(__AA[key-1]+__AA[key])>>1;
	x = x - aux;
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
	uint32_t aux = 0;
	if (key>0) aux=(__AA[key-1]+__AA[key])>>1;
	x = x - aux;
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
	uint32_t x = aa<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (((int64_t)x*__A[key])>>32)+x;
	int32_t t;
	char sign;
	if (x<POW_2_31) {t=x;sign = -1;}
	else {t = x - POW_2_32;sign = 1;}

	/* better approximation*/
	t += POW_2_27;
	short skey=(t&MASK_5_TO_7)>>25;
	t = (t & MASK_FROM_8) - POW_2_24;
	int aux = 1;
	if (skey>3) aux = 0;
	t = aux*t+(((int64_t)t*__INVT[skey])>>32);
	int64_t app = __LNT[skey]+t - (((int64_t)t*t)>>33);
	/* better approximation end*/
	app = app - (((uint64_t)__LNA[key]));
	app = app + (k-24)*(LN_2); //increased the precision with 4 bits
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app>>8);
#endif
	return (int8_24)(app>>8);
}

int16_16 log16_16_v2(int16_16 aa)
{
	/*Needs to double the number of entries in the lookup tables to make the interval (0.99,1.01)*/
	if (aa<=0) return 0;
	short k = norm16_16(aa);
	uint32_t x = aa<<(32-k);
	uint16_t key = (x>>27)-16;

	x = (((int64_t)x*__A[key])>>32)+x;
	int32_t t;
	char sign;
	if (x<POW_2_31) {t=x;sign = -1;}
	else {t = x - POW_2_32;sign = 1;}

	/* better approximation*/
	t += POW_2_27;
	short skey=(t&MASK_5_TO_7)>>25;
	t = (t & MASK_FROM_8) - POW_2_24;
	int aux = 1;
	if (skey>3) aux = 0;
	t = aux*t+(((int64_t)t*__INVT[skey])>>32);
	int64_t app = __LNT[skey]+t - (((int64_t)t*t)>>33);
	/* better approximation end*/
	app = app - (((uint64_t)__LNA[key]));
	app = app + (k-16)*(LN_2);
#ifdef DEBUG_FLAG
    verify_overflow_32_bits(app>>16);
#endif
	return (int8_24)(app>>16);
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
long __ashldi3 (long a, int k)
{
  if (k!=0) {if (k>32) { a<<=32; k >>=1; }; if (k>16) { a<<=16; k >>=1; };if (k>8) { a<<=8; k >>=1; };if (k>4) { a<<=4; k >>=1; };if (k>2) { a<<=2; k >>=1; };if (k>1) { a<<=1; k >>=1; }; a<<=k;}
  return a;
}

long __lshrdi3 (long a, int k)
{
 if (k!=0) {if (k>32) { a>>=32; k >>=1; }; if (k>16) { a>>=16; k >>=1; };if (k>8) { a>>=8; k >>=1; };if (k>4) { a>>=4; k >>=1; };if (k>2) { a>>=2; k >>=1; };if (k>1) { a>>=1; k >>=1; }; a>>=k;}
 return a;
}
