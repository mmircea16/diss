/*
 * Test.c
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */
#include <stdio.h>
#include "FixedPoint.h"
#include "minunit.h"

int tests_run = 0;



char * test_foo() {
	 int foo = 7;
     mu_assert("error, foo != 7", foo == 6);
     return 0;
 }

/* all_tests function is from: http://www.jera.com/techinfo/jtns/jtn002.html */
 char * all_tests() {
     mu_run_test(test_foo);

     return 0;
 }

/* main function is from: http://www.jera.com/techinfo/jtns/jtn002.html */
int main()
{
	printf("main\n");
	 char *result = all_tests();
	 if (result != 0) {
	     printf("%s\n", result);
	 }
	 else {
	     printf("ALL TESTS PASSED\n");
	 }
	 printf("Tests run: %d\n", tests_run);



	 return result != 0;
}



/* Old tests -- needs refactoring */
/*
 * printf("Test.c main\n");
	int8_8* x=(int8_8*) malloc(sizeof(int8_8));
	int8_8* y=(int8_8*) malloc(sizeof(int8_8));

	int8_8 my_num=int8_8_new(1,0.2);
	int8_8 other_num=int8_8_new(2,0.25);
	int8_8 sum=int8_8_new(1,0.05);

	int d =sub(other_num,my_num);
	int8_8 dif = _int8_8(d);
	printf("%d %d\n",dif.p,dif.q);
    if (comp_eq(add8_8(other_num,my_num),sum)) printf("yaay\n");
    if (comp_eq(sub8_8(other_num,my_num),sum)) printf("yaay\n");

    int8_8 num = int8_8_new2(25.2);
    printf("Num with new constructor:%x\n",num);
    return 0;
 */
