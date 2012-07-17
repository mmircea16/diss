/*
 * FixedPoint.h
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */


#ifndef FIXEDPOINT_H_
#define FIXEDPOINT_H_

/*structures*/
struct __float{
	 int mantissa :23;
	 int exp :8;
	 int sign :1;
} ;

typedef struct __float _float;

struct __int8_8
{
	unsigned char q:8;
	unsigned char p:8;
};

typedef struct __int8_8 int8_8;


typedef int int16_16;

typedef int int8_24;



struct __int24_8
{
	unsigned char q:8;
	unsigned int p:24;
};

typedef struct __int24_8 int24_8;

#define set_int_part_16_16(X,Y) ((X & 0x0000FFFF) | (Y<<16))
#define set_fract_part_16_16(X,Y) ((X & 0xFFFF0000) | (Y))
#define get_int_part_16_16(X) ((X & 0xFFFF0000) >> 16)
#define get_fract_part_16_16(X) (X & 0x0000FFFF)

#define set_int_part_8_24(X,Y) ((X & 0x00FFFFFF) | (Y<<24))
#define set_fract_part_8_24(X,Y) ((X & 0xFF000000) | (Y))
#define get_int_part_8_24(X) ((X & 0xFF000000) >> 24)
#define get_fract_part_8_24(X) (X & 0x00FFFFFF)


#define  _int(X) ((int)(((X).p<128)?((*(int*)&X)&0x0000FFFF):((*(int*)&X)|0xFFFF0000)))


#define  _int8_8(X) *(int8_8*)&X
#define  _int16_16(X) *(int16_16*)&X
#define  _int8_24(X) *(int8_24*)&X
#define  _int24_8(X) *(int24_8*)&X

#define max_fract(X) ((X).q=0xFFFF)
#define size_fract(X) (max_fract(X)==0xFFFF?16:(max_fract(X)==0x00FF?8:4))
#define max_int_part(X) ((X).p=0xFFFF)
#define norm_int_part(X) (max_int_part(X)==0xFFFF?0:(max_int_part(X)==0x00FF?8:4))
#define __int(X) ((int)(((X).p << 16) + ((X).q << (16-size_fract(X)))))

#define print8_8(X) printf("%d : %d\n",(X).p,(X).q)

/*comparison macros*/
#define comp_gt(X,Y) ((_int(X)) > (_int(Y)))
#define comp_lt(X,Y) ((_int(X)) < (_int(Y)))
#define comp_eq(X,Y) ((_int(X)) == (_int(Y)))
#define comp_not_eq(X,Y) ((_int(X)) != (_int(Y)))
#define comp_gt_eq(X,Y) ((_int(X)) >= (_int(Y)))
#define comp_lt_eq(X,Y) ((_int(X)) <= (_int(Y)))

/*utility macros*/
#define floor(X) ((int)(_int(X)>>8))
/*ceil,trunc,round,fix*/

/*arithmetic macros*/



/*init and alloc macros*/
#define int8_8_alloc(X) if(1){ int __xx=0; X=(int8_8*)&__xx;}

__inline__ int8_8 int8_8_new(const float X);
__inline__ int8_8 add8_8(int8_8 x,int8_8 y);
__inline__ int8_8 sadd8_8(int8_8 x,int8_8 y);
__inline__ int8_8 sub8_8(int8_8 x,int8_8 y);
__inline__ int8_8 ssub8_8(int8_8 x,int8_8 y);
__inline__ int8_8 mul8_8(int8_8 x,int8_8 y);
__inline__ int8_8 smul8_8(int8_8 x,int8_8 y);
__inline__ int8_8 fract8_8(int8_8 x);
__inline__ int8_8 floor8_8(int8_8 x);
__inline__ int16_16 cast8_8_to_16_16(int8_8 x);
__inline__ int8_8 cast16_16_to_8_8(int16_16 x);
__inline__ int16_16 int16_16_new(const float X);
__inline__ int16_16 add16_16(int16_16 x,int16_16 y);
__inline__ int16_16 sadd16_16(int16_16 x,int16_16 y);
__inline__ int16_16 sub16_16(int16_16 x,int16_16 y);
__inline__ int16_16 ssub16_16(int16_16 x,int16_16 y);
__inline__ int16_16 mul16_16(int16_16 x,int16_16 y);
__inline__ int16_16 smul16_16(int16_16 x,int16_16 y);
__inline__ int16_16 fract16_16(int16_16 x);
__inline__ int16_16 floor16_16(int16_16 x);
__inline__ int8_24 int8_24_new(const float X);
__inline__ int8_24 add8_24(int8_24 x,int8_24 y);
__inline__ int8_24 sadd8_24(int8_24 x,int8_24 y);
__inline__ int8_24 sub8_24(int8_24 x,int8_24 y);
__inline__ int8_24 ssub8_24(int8_24 x,int8_24 y);
__inline__ int8_24 mul8_24(int8_24 x,int8_24 y);
__inline__ int8_24 smul8_24(int8_24 x,int8_24 y);
__inline__ int8_24 floor8_24(int8_24 x);
__inline__ int8_24 fract8_24(int8_24 x);
__inline__ int24_8 int24_8_new(const float X);
__inline__ int24_8 add24_8(int24_8 x,int24_8 y);
__inline__ int24_8 sadd24_8(int24_8 x,int24_8 y);
__inline__ int24_8 sub24_8(int24_8 x,int24_8 y);
__inline__ int24_8 ssub24_8(int24_8 x,int24_8 y);
__inline__ int24_8 mul24_8(int24_8 x,int24_8 y);
__inline__ int24_8 smul24_8(int24_8 x,int24_8 y);
__inline__ int24_8 floor24_8(int24_8 x);
__inline__ int24_8 fract24_8(int24_8 x);
#endif

