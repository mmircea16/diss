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
	y = int8_8_new_d(1.5);
	mu_assert("error: overflow for 1.5 fails",get_overflow(CURRENT_ERR)==0);

	y = int8_8_new_d(1000.232);
	mu_assert("error: overflow for 1000.232 fails",get_overflow(CURRENT_ERR));

	y = int8_8_new_d(128.0);
	mu_assert("error: overflow for 128 fails",get_overflow(CURRENT_ERR));

	y = int8_8_new_d(-100000.232);
	mu_assert("error: overflow for -100000.232 fails",get_overflow(CURRENT_ERR));

	y = int8_8_new_d(-123.245);
	mu_assert("error: overflow for -123.245 fails",get_overflow(CURRENT_ERR)==0);

	y = int8_8_new_d(-200.2);
	mu_assert("error: overflow for -200.2 fails",get_overflow(CURRENT_ERR));

	mu_final();
	return 0;
}

char* test_overflow_at_sum()
{
   mu_test_title("Overflow for sum");
   debug_on();
   int8_8 y,x,sum;

   y = int8_8_new_d(1.5);
   x = int8_8_new_d(0.5);
   sum = add8_8_d(x,y);
   mu_assert("error: overflow for 1.5+0.5 fails",get_overflow(CURRENT_ERR)==0);

   //int8_8_new(101.5);
   //int8_8_new(100.5,x);
   //add8_8(x,y,sum);
   //mu_assert("error: overflow for 101.5+100.5 fails",get_overflow(CURRENT_ERR));

   //int8_8_new(101.8,y);
   //int8_8_new(13.7,x);
   //add8_8(x,y,sum);
   //mu_assert("error: overflow for 101.8+53.7 fails",get_overflow(CURRENT_ERR)==0);

   //int8_8_new(101.8,y);
   //int8_8_new(54.7,x);
   //add8_8(x,y,sum);
   //mu_assert("error: overflow for 101.8+54.7 fails",get_overflow(CURRENT_ERR));

   //int8_8_new(-1.5,y);
   //int8_8_new(0.5,x);
   //add8_8(x,y,sum);
   //mu_assert("error: overflow for -1.5+0.5 fails",get_overflow(CURRENT_ERR)==0);

   //int8_8_new(101.5,y);
   //int8_8_new(-100.5,x);
   //add8_8(x,y,sum);
   //mu_assert("error: overflow for 101.5+ -100.5 fails",get_overflow(CURRENT_ERR)==0);

   //int8_8_new(-101.8,y);
   //int8_8_new(-53.7,x);
   //add8_8(x,y,sum);
   //mu_assert("error: overflow for -101.8-53.7 fails",get_overflow(CURRENT_ERR));

   //int8_8_new(1.8,y);
   //int8_8_new(-125.7,x);
   //add8_8(x,y,sum);
   //mu_assert("error: overflow for 1.8+ -125.7 fails",get_overflow(CURRENT_ERR)==0);

   mu_final();
   return 0;
}

char* test_overflow_at_multiply()
{
   mu_test_title("Overflow for multiply");
   debug_on();
   int8_8 y,x,sum;

   //int8_8_new(1.5,y);
   //int8_8_new(0.5,x);
   //mul8_8(x,y,sum);
   mu_assert("error: overflow for 1.5*0.5 fails",get_overflow(CURRENT_ERR)==0);

   //int8_8_new(101.5,y);
   //int8_8_new(100.5,x);
   //mul8_8(x,y,sum);
   mu_assert("error: overflow for 101.5*100.5 fails",get_overflow(CURRENT_ERR));

   //int8_8_new(64.0,y);
   //int8_8_new(1.9,x);
   //mul8_8(x,y,sum);
   mu_assert("error: overflow for 64.0*3.9 fails",get_overflow(CURRENT_ERR)==0);

   //int8_8_new(5.0,y);
   //int8_8_new(51.2,x);
   //mul8_8(x,y,sum);
   mu_assert("error: overflow for 5.0*51.2 fails",get_overflow(CURRENT_ERR));

   //int8_8_new(-1.5,y);
   //int8_8_new(0.5,x);
   //mul8_8(x,y,sum);
   mu_assert("error: overflow for -1.5*0.5 fails",get_overflow(CURRENT_ERR)==0);

   //int8_8_new(-101.5,y);
   //int8_8_new(-0.5,x);
   //mul8_8(x,y,sum);
   mu_assert("error: overflow for -101.5* -0.5 fails",get_overflow(CURRENT_ERR)==0);

   //int8_8_new(-64.0,y);
   //int8_8_new(3.9,x);
   //mul8_8(x,y,sum);
   mu_assert("error: overflow for -64.0*3.9 fails",get_overflow(CURRENT_ERR));

   //int8_8_new(-5.0,y);
   //int8_8_new(-51.2,x);
   //mul8_8(x,y,sum);
   mu_assert("error: overflow for -5.0*-51.2 fails",get_overflow(CURRENT_ERR));


   mu_final();
   return 0;
}

char* test_misrepresentation_at_constructor()
{
	mu_test_title("Misrepresentation at constructor");
    int8_8 x;

    //int8_8_new(1.5,x);
	mu_assert("error: misrepresentation failed for 1.5",get_misrepresentation(CURRENT_ERR)==0);

	//int8_8_new(1.2,x);
	mu_assert("error: misrepresentation failed for 1.2",get_misrepresentation(CURRENT_ERR));

    //int8_8_new(-112.375,x);
	mu_assert("error: misrepresentation failed for -112.375",get_misrepresentation(CURRENT_ERR)==0);

	//int8_8_new(-22.8,x);
	mu_assert("error: misrepresentation failed for -22.8",get_misrepresentation(CURRENT_ERR));

    mu_final();
    return 0;
}

char* test_misrepresentation_value_at_constructor()
{
	mu_test_title("misrepresentation value at constructor");
    int8_8 x;
    debug_on();

    //int8_8_new(1.5,x);
	mu_assert("error: misrepresentation failed for 1.5",get_misrepresentation_value()==0);

	//int8_8_new(1.2,x);
	mu_assert("error: misrepresentation failed for 1.2",get_misrepresentation_value()==0x33);

    //int8_8_new(-112.375,x);
	mu_assert("error: misrepresentation failed for -112.375",get_misrepresentation_value()==0);

	//int8_8_new(-22.8,x);
	mu_assert("error: misrepresentation failed for -22.8",get_misrepresentation_value()==0x34);

    mu_final();
    return 0;
}

char * all_tests_fixed_point_with_info() {
	 mu_run_test(test_overflow_at_constructor);
	 mu_run_test(test_overflow_at_sum);
	 //mu_run_test(test_overflow_at_multiply);
	 //mu_run_test(test_misrepresentation_at_constructor);
	 //mu_run_test(test_misrepresentation_value_at_constructor);
     return 0;
 }
