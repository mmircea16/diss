/*
 * FixedPointMathDebugTests.h
 *
 *  Created on: 14.08.2012
 *      Author: Mircea
 */

#ifndef FIXEDPOINTMATHDEBUGTESTS_H_
#define FIXEDPOINTMATHDEBUGTESTS_H_
#include "Info.h"
char* test_simple_overflow()
{
	debug_on();
	int8_8 t1 = 0x7100;
	int8_8 t2 = 0x1000;
	int8_8 s = add8_8(t1,t2);
	mu_assert("error",get_overflow(CURRENT_ERR)==1);
	return 0;
}

char * all_tests_fixed_point_math_debug() {
	mu_run_test(test_simple_overflow);
	return 0;
}
#endif /* FIXEDPOINTMATHDEBUGTESTS_H_ */
