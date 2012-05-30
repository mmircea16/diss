/*
 * FixedPointWithInfoTests.h
 *
 *  Created on: 30 May 2012
 *      Author: moisem
 */

#include "minunit.h"

#ifndef FIXEDPOINTWITHINFOTESTS_H_
#define FIXEDPOINTWITHINFOTESTS_H_


#endif /* FIXEDPOINTWITHINFOTESTS_H_ */


char* test_overflow_at_constructor()
{
	mu_test_title("Overflow when using constructor");
	debug_on();

	int8_8 y;
	int8_8_new(1.5,y);
	mu_assert("error: overflow for 1.5 fails",get_overflow(CURRENT_ERR)==0);

	int8_8_new(1000.232,y);
	mu_assert("error: overflow for 1000.232 fails",get_overflow(CURRENT_ERR));

	mu_final();
	return 0;
}

char * all_tests_fixed_point_with_info() {
	 mu_run_test(test_overflow_at_constructor);
     return 0;
 }
