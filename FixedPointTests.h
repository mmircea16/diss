/*
 * FixedPointTests.h
 *
 *  Created on: 30 May 2012
 *      Author: moisem
 */
#include "minunit.h"
#include "Interpreter.h"

#ifndef FIXEDPOINTTESTS_H_
#define FIXEDPOINTTESTS_H_


#endif /* FIXEDPOINTTESTS_H_ */

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

	x->p=1;x->q=0x80;
	y->p=1;y->q=0x80;
	xx=*x;
	yy=*y;
	mu_assert("error: comparing 1.5 and 1.5 for equality failed",(comp_eq(xx,yy))==1);

	x->p=-1;x->q=0x80;
	y->p=-1;y->q=0x80;
	xx=*x;
	yy=*y;
	mu_assert("error: comparing -0.5 and -0.5 for equality failed",(comp_eq(xx,yy))==1);

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

	x->p=0xFE;x->q=0x80;
	y->p=0;y->q=0x40;
	xx=*x;
	yy=*y;

	mu_assert("error: -1.5 > 0.25  failed",(comp_gt(xx,yy))==0);
	mu_assert("error: -1.5 < 0.25  failed",(comp_lt(xx,yy)));

	x->p=0xFE;x->q=0x80;
	y->p=0xFD;y->q=0x80;
	xx=*x;
	yy=*y;
	mu_assert("error: -1.5 > -2.5  wrong",(comp_gt(xx,yy)));
	mu_assert("error: -1.5 < -2.5  wrong",(comp_lt(xx,yy))==0);

	xx.p=0xFE;xx.q=0x00;
	yy.p=0xFF;yy.q=0x00;
	mu_assert("error: -2 > -1  wrong",(comp_gt(xx,yy))==0);
	mu_assert("error: -2 < -1  wrong",(comp_lt(xx,yy)));

	mu_final();
	return 0;
}

char* test_constructor()
{
	mu_test_title("Constructor for 8.8 format");
    init_file("tests/gen/constructor.test");
	int8_8 y;
	float input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(float*)get_operand(i,1));
	  output=*(Parsed_fixed_point*)get_result(i);

		(output.fractional_part) >>=8;
		y = int8_8_new(input);
		mu_assert("error",((y.p==output.integer_part)&&(y.q==output.fractional_part)));
		i++;
	}

	mu_final();
	return 0;
}


char* test_add()
{
  mu_test_title("Adding");
  init_file("tests/gen/add.test");
  int8_8 x1,x2,y;
  x1=*(int8_8*)malloc(sizeof(int8_8));
  x2=*(int8_8*)malloc(sizeof(int8_8));
  Parsed_fixed_point input1;
  Parsed_fixed_point input2;
  Parsed_fixed_point output;
  int i=0;
  while (get_operand(i,1)!=NULL)
  {
  	input1=*(Parsed_fixed_point*)get_operand(i,1);
  	input2=*(Parsed_fixed_point*)get_operand(i,2);
  	output=*(Parsed_fixed_point*)get_result(i);

  	(output.fractional_part) >>=8;
  	(input1.fractional_part) >>=8;
  	(input2.fractional_part) >>=8;
  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

  	y = add8_8(x1,x2);

  	mu_assert("error",((y.p==output.integer_part)&&(y.q==output.fractional_part)));
  	i++;
  	}


  mu_final();

  return 0;
}

char* test_subtract()
{
	  mu_test_title("Subtracting");
	  init_file("tests/gen/subtract.test");
	  int8_8 x1,x2,y;
	  x1=*(int8_8*)malloc(sizeof(int8_8));
	  x2=*(int8_8*)malloc(sizeof(int8_8));
	  Parsed_fixed_point input1;
	  Parsed_fixed_point input2;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	input2=*(Parsed_fixed_point*)get_operand(i,2);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=8;
	  	(input1.fractional_part) >>=8;
	  	(input2.fractional_part) >>=8;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = sub8_8(x1,x2);

	  	mu_assert("error",((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}

char* test_multiply()
{
	  mu_test_title("Multiplying");
	  init_file("tests/gen/multiply.test");
	  int8_8 x1,x2,y;
	  x1=*(int8_8*)malloc(sizeof(int8_8));
	  x2=*(int8_8*)malloc(sizeof(int8_8));
	  Parsed_fixed_point input1;
	  Parsed_fixed_point input2;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	input2=*(Parsed_fixed_point*)get_operand(i,2);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=8;
	  	(input1.fractional_part) >>=8;
	  	(input2.fractional_part) >>=8;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = mul8_8(x1,x2);

	  	mu_assert("error",((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();
	return 0;
}

char* test_floor()
{
	mu_test_title("Integer part");
	init_file("tests/gen/floor.test");
	int y;
	int8_8 x;
	x=*(int8_8*)malloc(sizeof(int8_8));
	Parsed_fixed_point input;
	int output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(Parsed_fixed_point*)get_operand(i,1));
	  output=*(int*)get_result(i);
	  x.p=input.integer_part;x.q=input.fractional_part;
	  y = floor8_8(x);
	  mu_assert("error",y==output);
	  i++;
	}

	mu_final();
    return 0;
}

char* test_fractional_part()
{
  mu_test_title("Fractional part function");
  int8_8 res;
  int8_8 *x,*y;
  int8_8_alloc(x);
  int8_8_alloc(y);
  y->p=0;

  x->p=1;x->q=0x12;y->q=0x12;
  fract8_8(*x,res);
  mu_assert("error: fractional part failed for 1.sth",comp_eq(res,*y));

  x->p=0;x->q=0x52;y->q=0x52;
  fract8_8(*x,res);
  mu_assert("error: fractional part failed for 0.sth",comp_eq(res,*y));

  x->p=138;x->q=0x00;y->q=0x00;
  fract8_8(*x,res);
  mu_assert("error: fractional part failed for 138.0",comp_eq(res,*y));

  //int8_8_new(-1.25,*x);//int8_8_new(0.75,*y);
  fract8_8(*x,res);
  mu_assert("error: fractional part failed for -1.25",comp_eq(res,*y));

  //int8_8_new(-0.75,*x);//int8_8_new(0.25,*y);
  fract8_8(*x,res);
  mu_assert("error: fractional part failed for -0.75",comp_eq(res,*y));

  //int8_8_new(-123.0,*x);//int8_8_new(0.0,*y);
  fract8_8(*x,res);
  mu_assert("error: fractional part failed for -123.0",comp_eq(res,*y));

  mu_final();
  return 0;
}

char * test_foo() {
	 int foo = 7;
     mu_assert("error, foo != 7", foo == 7);
     return 0;
 }

/* all_tests function is from: http://www.jera.com/techinfo/jtns/jtn002.html */
 char * all_tests_fixed_point() {
     //mu_run_test(test_foo);
	 set_no_debug();/*
     mu_run_test(test_compare_equal);
     mu_run_test(test_compare_lesser_and_greater);*/
     mu_run_test(test_constructor);
	 mu_run_test(test_add);
     mu_run_test(test_subtract);
     mu_run_test(test_multiply);
     mu_run_test(test_floor);/*
     mu_run_test(test_fractional_part);*/
     return 0;
 }
