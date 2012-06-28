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
	 int8_8 x = int8_8_new(1.5);
	 int yy=0;
	 int16_16 y = _int16_16(yy) ;
	 y.p=1;
	 y.q=1<<15;
	 printf("intro to main:%d %d\n",__int(x),__int(y));
	 //char* result="as";
	 char *result = all_tests_fixed_point();
	// char *result = all_tests_fixed_point_with_info();
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




