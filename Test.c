/*
 * Test.c
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */
#include <stdio.h>





#ifdef DEBUG_FLAG
  #include "FixedPointDebug.h"
  #include "Info.h"
  #include "FixedPointWithInfoTests.h"
  #include "InfoTests.h"
#else
  #include "FixedPoint.h"
  #include "FixedPointTests.h"
#endif



#include "minunit.h"

int tests_run = 0;



/* main function is from: http://www.jera.com/techinfo/jtns/jtn002.html */
int main()
{
	 //char* result="as";
	char *result = all_tests_fixed_point();
	 //char *result = all_tests_fixed_point_with_info();
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




