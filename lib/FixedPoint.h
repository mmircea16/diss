/*
 * FixedPoint.h
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */


#ifndef FIXEDPOINT_H_
#define FIXEDPOINT_H_

#include "inttypes.h"

#define MAX_INT_8_8 0x7FFF;
#define MIN_INT_8_8 0x8000;

/*structures*/
struct __float{
	 int mantissa :23;
	 int exp :8;
	 int sign :1;
} ;

typedef struct __float _float;



typedef  int16_t int8_8;


typedef int32_t int16_16;

typedef int32_t int8_24;

typedef int32_t int24_8;

typedef int32_t int0_32;
typedef int32_t int2_30;
typedef int16_t int0_16;
typedef int64_t int0_64;

#define set_int_part_8_8(X,Y) ((X & 0x00FF) | (Y<<8))
#define set_fract_part_8_8(X,Y) ((X & 0xFF00) | (Y))
#define get_int_part_8_8(X) ((X & 0xFF00) >> 8)
#define get_fract_part_8_8(X) (X & 0x00FF)

#define set_int_part_16_16(X,Y) ((X & 0x0000FFFF) | (Y<<16))
#define set_fract_part_16_16(X,Y) ((X & 0xFFFF0000) | (Y))
#define get_int_part_16_16(X) ((X & 0xFFFF0000) >> 16)
#define get_fract_part_16_16(X) (X & 0x0000FFFF)

#define set_int_part_8_24(X,Y) ((X & 0x00FFFFFF) | (Y<<24))
#define set_fract_part_8_24(X,Y) ((X & 0xFF000000) | (Y))
#define get_int_part_8_24(X) ((X & 0xFF000000) >> 24)
#define get_fract_part_8_24(X) (X & 0x00FFFFFF)

#define set_int_part_24_8(X,Y) ((X & 0x000000FF) | (Y<<8))
#define set_fract_part_24_8(X,Y) ((X & 0xFFFFFF00) | (Y))
#define get_int_part_24_8(X) ((X & 0xFFFFFF00) >> 8)
#define get_fract_part_24_8(X) (X & 0x000000FF)


/*comparison macros*/
#define comp_gt(X,Y) ((_int(X)) > (_int(Y)))
#define comp_lt(X,Y) ((_int(X)) < (_int(Y)))
#define comp_eq(X,Y) ((_int(X)) == (_int(Y)))
#define comp_not_eq(X,Y) ((_int(X)) != (_int(Y)))
#define comp_gt_eq(X,Y) ((_int(X)) >= (_int(Y)))
#define comp_lt_eq(X,Y) ((_int(X)) <= (_int(Y)))


#define new_int_8_8(X) ((int8_8)((X)*256)) //do not abuse!!!
#define new_int_16_16(X) ((int16_16)((X)*256*256))
#define new_int_24_8(X) ((int24_8)((X)*256))
#define new_int_8_24(X) ((int8_24)((X)*256*256*256))

#define floor8_8(X) ((int8_8) ((X)&0xFF00))
#define floor16_16(X) ((int16_16) ((X)&0xFFFF0000))
#define floor24_8(X) ((int24_8) ((X)&0xFFFFFF00))
#define floor8_24(X) ((int8_24) ((X)&0xFF000000))

#define fract8_8(X) ((int8_8) ((X)&0x00FF))
#define fract16_16(X) ((int16_16) ((X)&0x0000FFFF))
#define fract8_24(X) ((int8_24) ((X)&0x00FFFFFF))
#define fract24_8(X) ((int24_8) ((X)&0x000000FF))

#define add(X,Y) ((X)+(Y))
#define sub(X,Y) ((X)-(Y))
#define mul8_8(X,Y) (((int32_t)(X)*(Y))>>8)
#define mul8_24(X,Y) (((int64_t)(X)*(Y))>>24)
#define mul16_16(X,Y) (((int64_t)(X)*(Y))>>16)
#define mul24_8(X,Y) (((int64_t)(X)*(Y))>>8)




//__inline__ int8_8 add8_8(int8_8 x,int8_8 y);
__inline__ int8_8 sadd8_8(int8_8 x,int8_8 y);
//__inline__ int8_8 sub8_8(int8_8 x,int8_8 y);
__inline__ int8_8 ssub8_8(int8_8 x,int8_8 y);
//__inline__ int8_8 mul8_8(int8_8 x,int8_8 y);
__inline__ int8_8 smul8_8(int8_8 x,int8_8 y);
//__inline__ int8_8 fract8_8(int8_8 x);
//__inline__ int8_8 floor8_8(int8_8 x);
__inline__ int16_16 cast8_8_to_16_16(int8_8 x);
__inline__ int8_8 cast16_16_to_8_8(int16_16 x);
//__inline__ int16_16 int16_16_new(const float X);
//__inline__ int16_16 add16_16(int16_16 x,int16_16 y);
__inline__ int16_16 sadd16_16(int16_16 x,int16_16 y);
//__inline__ int16_16 sub16_16(int16_16 x,int16_16 y);
__inline__ int16_16 ssub16_16(int16_16 x,int16_16 y);
//__inline__ int16_16 mul16_16(int16_16 x,int16_16 y);
__inline__ int16_16 smul16_16(int16_16 x,int16_16 y);
//__inline__ int16_16 fract16_16(int16_16 x);
//__inline__ int16_16 floor16_16(int16_16 x);
//__inline__ int8_24 int8_24_new(const float X);
//__inline__ int8_24 add8_24(int8_24 x,int8_24 y);
__inline__ int8_24 sadd8_24(int8_24 x,int8_24 y);
//__inline__ int8_24 sub8_24(int8_24 x,int8_24 y);
__inline__ int8_24 ssub8_24(int8_24 x,int8_24 y);
//__inline__ int8_24 mul8_24(int8_24 x,int8_24 y);
//__inline__ int8_24 smul8_24(int8_24 x,int8_24 y);
//__inline__ int8_24 floor8_24(int8_24 x);
//__inline__ int8_24 fract8_24(int8_24 x);
//__inline__ int24_8 int24_8_new(const float X);
//__inline__ int24_8 add24_8(int24_8 x,int24_8 y);
__inline__ int24_8 sadd24_8(int24_8 x,int24_8 y);
//__inline__ int24_8 sub24_8(int24_8 x,int24_8 y);
__inline__ int24_8 ssub24_8(int24_8 x,int24_8 y);
//__inline__ int24_8 mul24_8(int24_8 x,int24_8 y);
__inline__ int24_8 smul24_8(int24_8 x,int24_8 y);
//__inline__ int24_8 floor24_8(int24_8 x);
//__inline__ int24_8 fract24_8(int24_8 x);
#endif

