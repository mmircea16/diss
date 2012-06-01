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

	int8_8_new(128.0,y);
	mu_assert("error: overflow for 128 fails",get_overflow(CURRENT_ERR));

	int8_8_new(-1000.232,y);
	mu_assert("error: overflow for -1000.232 fails",get_overflow(CURRENT_ERR));

	int8_8_new(-123.245,y);
	mu_assert("error: overflow for -123.245 fails",get_overflow(CURRENT_ERR)==0);

	int8_8_new(-200.2,y);
	mu_assert("error: overflow for -200.2 fails",get_overflow(CURRENT_ERR));

	mu_final();
	return 0;
}

char* test_overflow_at_sum()
{
   mu_test_title("Overflow for sum");
   debug_on();
   int8_8 y,x,sum;
   int8_8_new(1.5,y);
   int8_8_new(0.5,x);
   add8_8(x,y,sum);
   mu_assert("error: overflow for 1.5+0.5 fails",get_overflow(CURRENT_ERR)==0);

   int8_8_new(201.5,y);
   int8_8_new(200.5,x);
   add8_8(x,y,sum);
   mu_assert("error: overflow for 201.5+200.5 fails",get_overflow(CURRENT_ERR));

   int8_8_new(201.8,y);
   int8_8_new(53.7,x);
   add8_8(x,y,sum);
   mu_assert("error: overflow for 201.8+53.7 fails",get_overflow(CURRENT_ERR)==0);

   int8_8_new(201.8,y);
   int8_8_new(54.7,x);
   add8_8(x,y,sum);
   mu_assert("error: overflow for 201.8+54.7 fails",get_overflow(CURRENT_ERR));

   mu_final();
   return 0;
}

char* test_overflow_at_multiply()
{
   mu_test_title("Overflow for multiply");
   debug_on();
   int8_8 y,x,sum;
   int8_8_new(1.5,y);
   int8_8_new(0.5,x);

   mul8_8(x,y,sum);
   mu_assert("error: overflow for 1.5*0.5 fails",get_overflow(CURRENT_ERR)==0);

   int8_8_new(201.5,y);
   int8_8_new(200.5,x);
   mul8_8(x,y,sum);
   mu_assert("error: overflow for 201.5*200.5 fails",get_overflow(CURRENT_ERR));

   int8_8_new(64.0,y);
   int8_8_new(3.9,x);
   mul8_8(x,y,sum);
   mu_assert("error: overflow for 64.0*3.9 fails",get_overflow(CURRENT_ERR)==0);

   int8_8_new(5.0,y);
   int8_8_new(51.2,x);
   mul8_8(x,y,sum);
   mu_assert("error: overflow for 5.0*51.2 fails",get_overflow(CURRENT_ERR));

   mu_final();
   return 0;
}

char * all_tests_fixed_point_with_info() {
	 mu_run_test(test_overflow_at_constructor);
	 mu_run_test(test_overflow_at_sum);
	 mu_run_test(test_overflow_at_multiply);
     return 0;
 }
