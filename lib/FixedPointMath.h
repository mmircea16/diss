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

inline char bits4_most_significant(char x);

#endif /* FIXEDPOINTMATH_H_ */
