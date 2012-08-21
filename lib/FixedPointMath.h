/*
 * FixedPointMath.h
 *
 *  Created on: 18 Jul 2012
 *      Author: moisem
 */

#ifndef FIXEDPOINTMATH_H_
#define FIXEDPOINTMATH_H_

#include "FixedPoint.h"

/** Lookup tables **/
//Logarithm lookup tables
#define MASK_LOWER_32 (0x00000000FFFFFFFF)
#define POW_2_31 (0x0000000080000000)
#define POW_2_32 (0x0000000100000000)
#define POW_2_24 (0x0000000001000000)
#define POW_2_25 (0x0000000002000000)
#define POW_2_27 (0x0000000008000000)
#define POW_2_23 (0x0000000000800000)
#define SQRT_C1 (0x00000001C9A8AC5C) //1.77
#define SQRT_C2 (0x00000000CF5B8130) //1.8
#define SQRT_2  (0x000000006A09E668) //SQRT(2)
#define LN_2 (2977044471ULL)
#define LN_2_EXTRA (47632711549ULL)
#define LN_2_INV (6196328018LL)
#define MASK_5_TO_8 (0x000000000F000000)
#define MASK_FROM_9 (0x0000000000FFFFFF)
#define MASK_5_TO_7 (0x000000000E000000)
#define MASK_FROM_8 (0x0000000001FFFFFF)
#define MASK_5_TO_6 (0x000000000C000000)
#define MASK_FROM_7 (0x0000000003FFFFFF)

#define PI (13493037704ULL)
#define PI_INV (1367130551ULL)

#define SIN_C1 (715827882ULL) // 1/6
#define SIN_C2 (35791394ULL) // 1/120
#define COS_C1 (178956970ULL) // 1/24

short norm8_8(int16_t x);
short norm16_16(int32_t x);

int8_8 div8_8(int8_8 n, int8_8 m);
int8_8 div8_8_v2(int8_8 n,int8_8 m);
int16_16 div16_16(int16_16 n, int16_16 m);
int16_16 div16_16_v2(int16_16 n,int16_16 m);
int8_24 div8_24(int8_24 n, int8_24 m);
int8_24 div8_24_v2(int8_24 n,int8_24 m);
int24_8 div24_8(int24_8 n, int24_8 m);
int24_8 div24_8_v2(int24_8 n,int24_8 m);

int8_8 sqrt8_8(int8_8 a);
int16_16 sqrt16_16(int16_16 a);
int8_24 sqrt8_24(int8_24 a);
int24_8 sqrt24_8(int24_8 a);

int8_8 log8_8(int8_8 aa);
int16_16 log16_16(int16_16 aa);
int16_16 log16_16_v2(int16_16 aa);
int8_24 log8_24(int8_24 aa);
int8_24 log8_24_v2(int8_24 aa);
int24_8 log24_8(int24_8 aa);

int8_8 exp8_8(int8_8 aa);
int16_16 exp16_16(int16_16 aa);
int16_16 exp16_16_v2(int16_16 a);
int8_24 exp8_24(int8_24 aa);
int8_24 exp8_24_v2(int8_24 a);
int24_8 exp24_8(int24_8 aa);
int24_8 exp24_8_v2(int24_8 a);

int8_8 sin8_8(int8_8 a);

inline char bits4_most_significant(char x);

#endif /* FIXEDPOINTMATH_H_ */
