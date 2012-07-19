/*
 * FixedPointMath.h
 *
 *  Created on: 18 Jul 2012
 *      Author: moisem
 */

#ifndef FIXEDPOINTMATH_H_
#define FIXEDPOINTMATH_H_

#include "FixedPoint.h"

short norm8_8(int8_8 x);
int8_8 div8_8(int8_8 n, int8_8 m);

inline char bits4_most_significant(char x);

#endif /* FIXEDPOINTMATH_H_ */
