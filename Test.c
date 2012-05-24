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

/* test for comparison functions */

char* test_compare_equal()
{
	mu_test_title("Comparison for equality");

	int8_8* x=(int8_8*) malloc(sizeof(int8_8));
	int8_8* y=(int8_8*) malloc(sizeof(int8_8));
    x->padding1=0;x->padding2=0;
    y->padding1=0;y->padding2=0;
    x->p=1;x->q=0x80;
	y->p=0;y->q=0x40;
	int8_8 xx=*x;
	int8_8 yy=*y;
	mu_assert("error: comparing 1.5 and 0.25 for equality failed",(comp_eq(xx,yy))==0);

	x->p=1;x->q=1;
	y->p=1;y->q=1;
	xx=*x;
	yy=*y;
	mu_assert("error: comparing 1.5 and 1.5 for equality failed",(comp_eq(xx,yy))==1);
	mu_final();
	return 0;
}


char * test_foo() {
	 int foo = 7;
     mu_assert("error, foo != 7", foo == 7);
     return 0;
 }

/* all_tests function is from: http://www.jera.com/techinfo/jtns/jtn002.html */
 char * all_tests() {
     //mu_run_test(test_foo);
     mu_run_test(test_compare_equal);
     return 0;
 }

/* main function is from: http://www.jera.com/techinfo/jtns/jtn002.html */
int main()
{
	 char *result = all_tests();
	 if (result != 0) {
	     printf("%s\n", result);
	 }
	 else {
	     printf("ALL TESTS PASSED\n-------------------\n");
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
