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

char* test_compare_lesser_and_greater()
{
	mu_test_title("Comparison for greater and lesser");

	int8_8* x=(int8_8*) malloc(sizeof(int8_8));
	int8_8* y=(int8_8*) malloc(sizeof(int8_8));

    x->p=1;x->q=0x80;
	y->p=0;y->q=0x40;
	int8_8 xx=*x;
	int8_8 yy=*y;
	mu_assert("error: 1.5 > 0.25  failed",(comp_gt(xx,yy))==1);
	mu_assert("error: 1.5 < 0.25  failed",(comp_lt(xx,yy))==0);
	x->p=1;x->q=0x80;
	y->p=1;y->q=0x80;
	xx=*x;
	yy=*y;
	mu_assert("error: 1.5 > 1.5  wrong",(comp_gt(xx,yy))==0);
	mu_assert("error: 1.5 < 1.5  wrong",(comp_lt(xx,yy))==0);

	xx.p=2;xx.q=0x66;
	yy.p=2;yy.q=0x67;
	mu_assert("error: 2.sth > 2.sth+2^-8  wrong",(comp_gt(xx,yy))==0);
	mu_assert("error: 2.sth < 2.sth+2^-8  wrong",(comp_lt(xx,yy))==1);

	mu_final();
	return 0;
}

char* test_constructor()
{
	mu_test_title("Constructor for 8.8 format");

	int8_8 y;
	int8_8_new(1.5,y);

	mu_assert("error: creating 1.5 fails",((y.p==1)&&(y.q=0x80)));

	int8_8_new(0.5,y);
	mu_assert("error: creating 0.5 fails",((y.p==0)&&(y.q=0x80)));

	int8_8_new(1,y);
	mu_assert("error: creating 1 fails",((y.p==1)&&(y.q==0)));

	int8_8_new(133.2,y);
	mu_assert("error: creating 133.2 fails",((y.p==133)&&(y.q=0x66)));

	mu_final();
	return 0;
}


char* test_add()
{
  mu_test_title("Adding")
  int8_8 t1;
  int8_8 t2,sum,computed_sum;
  int8_8_new(1.5,t1);
  int8_8_new(0.2,t2);
  int8_8_new(1.7,sum);
  add8_8(t2,t1,computed_sum);
  mu_assert("error: 1.5 + 0.2 failed",comp_eq(computed_sum,sum));

  int8_8_new(12.75,t1);
  int8_8_new(15.3,t2);
  int8_8_new(28.05,sum);
  add8_8(t2,t1,computed_sum);
  mu_assert("error: 12.75 + 15.3 failed",comp_eq(computed_sum,sum));

  int8_8_new(123.45,t1);
  int8_8_new(2.78,t2);
  int8_8_new(126.23,sum);
  add8_8(t2,t1,computed_sum);
  mu_assert("error: 123.45 + 2.78 failed",comp_eq(computed_sum,sum));

  mu_final();
  /*comment: lose of precision reflects on adds; all the tests are done without having to deal with lost precision*/
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
     mu_run_test(test_compare_lesser_and_greater);
     mu_run_test(test_constructor);
     mu_run_test(test_add);
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
