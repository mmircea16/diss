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

char* test_comparison()
{
  mu_test_title("Comparison");
  init_file("tests/gen/comparison.test");
  int8_8 x1,x2;
  int r_eq,r_not_eq,r_gt,r_lt,r_gt_eq,r_lt_eq;

  x1=*(int8_8*)malloc(sizeof(int8_8));
  x2=*(int8_8*)malloc(sizeof(int8_8));
  Parsed_fixed_point input1;
  Parsed_fixed_point input2;
  int output;
  int i=0;
  while (get_operand(i,1)!=NULL)
  {
  	input1=*(Parsed_fixed_point*)get_operand(i,1);
  	input2=*(Parsed_fixed_point*)get_operand(i,2);
  	output=*(int*)get_result(i);

  	(input1.fractional_part) >>=8;
  	(input2.fractional_part) >>=8;
  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

  	r_eq = (output == 0);
  	r_not_eq = (output != 0);
  	r_gt = (output == 1);
  	r_lt = (output == -1);
  	r_gt_eq = (output > -1);
  	r_lt_eq = (output < 1);

  	mu_assert_line("error",i,comp_eq(x1,x2)==r_eq);
  	mu_assert_line("error",i,comp_not_eq(x1,x2)==r_not_eq);
  	mu_assert_line("error",i,comp_gt(x1,x2)==r_gt);
  	mu_assert_line("error",i,comp_lt(x1,x2)==r_lt);
  	mu_assert_line("error",i,comp_gt_eq(x1,x2)==r_gt_eq);
  	mu_assert_line("error",i,comp_lt_eq(x1,x2)==r_lt_eq);
  	i++;
  	}


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
		mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
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

  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
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

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
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

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
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
	  (input.fractional_part) >>=8;
	  x.p=input.integer_part;
	  x.q=input.fractional_part;
	  y = floor8_8(x);
	  mu_assert_line("error",i,y==output);
	  i++;
	}

	mu_final();
    return 0;
}

char* test_fractional_part()
{
	mu_test_title("Fractional part");
	init_file("tests/gen/fractional.test");
	int8_8 x,y;
	x=*(int8_8*)malloc(sizeof(int8_8));
	y=*(int8_8*)malloc(sizeof(int8_8));
	Parsed_fixed_point input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(Parsed_fixed_point*)get_operand(i,1));
	   output=*(Parsed_fixed_point*)get_result(i);
	   (output.fractional_part) >>=8;
	   (input.fractional_part) >>=8;
	   x.p=input.integer_part;
	   x.q=input.fractional_part;
	   y = fract8_8(x);
	   mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	   i++;
	}

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
	 set_no_debug();
	 mu_run_test(test_comparison);
     mu_run_test(test_constructor);
	 mu_run_test(test_add);
     mu_run_test(test_subtract);
     mu_run_test(test_multiply);
     mu_run_test(test_floor);
     mu_run_test(test_fractional_part);
     return 0;
 }

#endif /* FIXEDPOINTTESTS_H_ */
