/*
 * Test.c
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */
#include <stdio.h>




#define DEBUG_FLAG 1

#include "FixedPoint.h"
#include "FixedPointTests.h"
#include "FixedPointMath.h"
#include "FixedPointMathTests.h"
#include "FixedPointMathDebugTests.h"



#include "minunit.h"

int tests_run = 0;



/* main function is from: http://www.jera.com/techinfo/jtns/jtn002.html */
int main()
{

	//char *result = all_tests_fixed_point();
	//char *result = all_tests_fixed_point_math();
	char *result = all_tests_fixed_point_math_debug();
	 //char *result = all_tests_info();
	 if (result != 0) {
	     printf("%s\n", result);
	 }
	 else {
	     printf("ALL TESTS PASSED\n-------------------\n");
	 }
	 printf("Tests run: %d\n", tests_run);

	 return result != 0;
}




