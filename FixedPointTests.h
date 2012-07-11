/*
 * FixedPointTests.h
 *
 *  Created on: 30 May 2012
 *      Author: moisem
 */
#include "minunit.h"
#include "Interpreter.h"
#include "FixedPoint.h"
#ifndef FIXEDPOINTTESTS_H_
#define FIXEDPOINTTESTS_H_

char* test_comparison()
{
  mu_test_title("Comparison");
  init_file("tests/gen/8_8/comparison.test");
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

  	(input1.fractional_part) >>=24;
  	(input2.fractional_part) >>=24;
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


char* test_constructor_8_8()
{
	mu_test_title("Constructor for 8.8 format");
    init_file("tests/gen/8_8/constructor.test");
	int8_8 y;
	float input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(float*)get_operand(i,1));
	  output=*(Parsed_fixed_point*)get_result(i);

		(output.fractional_part) >>=24;
		y = int8_8_new(input);
		mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
		i++;
	}

	mu_final();
	return 0;
}

char* test_constructor_16_16()
{
	mu_test_title("Constructor for 16.16 format");
    init_file("tests/gen/8_8/constructor16_16.test");
	int16_16 y;
	float input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(float*)get_operand(i,1));
	   output=*(Parsed_fixed_point*)get_result(i);

	   (output.fractional_part) >>=16;
		y = int16_16_new(input);
		printf("--- %f\n",input);
		printf("--- %d %d\n",y.p,y.q);
		printf("--- %d %d\n",output.integer_part,output.fractional_part);
		mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
		i++;
	}

	mu_final();
	return 0;
}


char* test_add()
{
  mu_test_title("Adding");
  init_file("tests/gen/8_8/add.test");
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

  	(output.fractional_part) >>=24;
  	(input1.fractional_part) >>=24;
  	(input2.fractional_part) >>=24;
  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

  	y = add8_8(x1,x2);

  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
  	i++;
  	}


  mu_final();

  return 0;
}

char* test_saturated_add()
{
  mu_test_title("Saturated add test");
  init_file("tests/gen/8_8/saturated_add.test");
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

  	(output.fractional_part) >>=24;
  	(input1.fractional_part) >>=24;
  	(input2.fractional_part) >>=24;
  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

  	y = sadd8_8(x1,x2);

  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
  	i++;
  	}


  mu_final();

  return 0;
}


char* test_subtract()
{
	  mu_test_title("Subtracting");
	  init_file("tests/gen/8_8/subtract.test");
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

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	(input2.fractional_part) >>=24;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = sub8_8(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}

char* test_saturated_subtract()
{
	  mu_test_title("Saturated subtract");
	  init_file("tests/gen/8_8/saturated_subtract.test");
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

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	(input2.fractional_part) >>=24;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = ssub8_8(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}

char* test_multiply()
{
	  mu_test_title("Multiplying");
	  init_file("tests/gen/8_8/multiply.test");
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

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	(input2.fractional_part) >>=24;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = mul8_8(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();
	return 0;
}

char* test_saturated_multiply()
{
	  mu_test_title("Saturated Multiplying");
	  init_file("tests/gen/8_8/saturated_multiply.test");
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

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	(input2.fractional_part) >>=24;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = smul8_8(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();
	return 0;
}

char* test_floor()
{
	mu_test_title("Integer part");
	init_file("tests/gen/8_8/floor.test");
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
	  (input.fractional_part) >>=24;
	  x.p=input.integer_part;
	  x.q=input.fractional_part;
	  y = floor(x);
	  mu_assert_line("error",i,y==output);
	  i++;
	}

	mu_final();
    return 0;
}

char* test_floor8_8()
{
	mu_test_title("Integer part (result in 8.8 format)");
	init_file("tests/gen/8_8/floor8_8.test");
	int8_8 y;
	int8_8 x;
	x=*(int8_8*)malloc(sizeof(int8_8));
	Parsed_fixed_point input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(Parsed_fixed_point*)get_operand(i,1));
	  output=*(Parsed_fixed_point*)get_result(i);
	  (input.fractional_part) >>=24;
	  (output.fractional_part) >>=24;
	  x.p=input.integer_part;
	  x.q=input.fractional_part;
	  y = floor8_8(x);
	  mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  i++;
	}

	mu_final();
    return 0;
}

char* test_fractional_part()
{
	mu_test_title("Fractional part");
	init_file("tests/gen/8_8/fractional.test");
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
	   (output.fractional_part) >>=24;
	   (input.fractional_part) >>=24;
	   x.p=input.integer_part;
	   x.q=input.fractional_part;
	   y = fract8_8(x);
	   mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	   i++;
	}

	mu_final();
  return 0;
}

char* test_cast_8_8_to_16_16()
{
	mu_test_title("Cast from 8_8 to 16_16");

	init_file("tests/gen/16_16/cast_from_8_8.test");
	int8_8 x;
	x=*(int8_8*)malloc(sizeof(int8_8));
	int16_16 y;
	Parsed_fixed_point input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(Parsed_fixed_point*)get_operand(i,1));
	   output=*(Parsed_fixed_point*)get_result(i);

	   (output.fractional_part) >>=16;
	   (input.fractional_part) >>=24;
	   x.p=input.integer_part;
	   x.q=input.fractional_part;
	   y = cast8_8_to_16_16(x);
	   mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	   i++;
	}

	mu_final();
    return 0;
}

char* test_cast_16_16_to_8_8()
{
	mu_test_title("Cast from 16_16 to 8_8");

	init_file("tests/gen/16_16/cast_to_8_8.test");
	int16_16 x;
	x=*(int16_16*)malloc(sizeof(int8_8));
	int8_8 y;
	Parsed_fixed_point input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(Parsed_fixed_point*)get_operand(i,1));
	   output=*(Parsed_fixed_point*)get_result(i);

	   (input.fractional_part) >>=16;
	   (output.fractional_part) >>=24;
	   x.p=input.integer_part;
	   x.q=input.fractional_part;
	   y = cast16_16_to_8_8(x);
	   mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	   i++;
	}

	mu_final();
    return 0;
}

char* test_add_16_16()
{
	 mu_test_title("Adding 16.16 numbers");
	 init_file("tests/gen/16_16/add.test");
	 int16_16 x1,x2,y;
	 x1=*(int16_16*)malloc(sizeof(int16_16));
	 x2=*(int16_16*)malloc(sizeof(int16_16));
	 Parsed_fixed_point input1;
	 Parsed_fixed_point input2;
	 Parsed_fixed_point output;
	 int i=0;
	 while (get_operand(i,1)!=NULL)
	 {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	input2=*(Parsed_fixed_point*)get_operand(i,2);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=16;
	  	(input1.fractional_part) >>=16;
	  	(input2.fractional_part) >>=16;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = add16_16(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();

    return 0;
}

char* test_saturated_add_16_16()
{
  mu_test_title("Saturated add 16.16 test");
  init_file("tests/gen/16_16/saturated_add.test");
  int16_16 x1,x2,y;
  x1=*(int16_16*)malloc(sizeof(int16_16));
  x2=*(int16_16*)malloc(sizeof(int16_16));
  Parsed_fixed_point input1;
  Parsed_fixed_point input2;
  Parsed_fixed_point output;
  int i=0;
  while (get_operand(i,1)!=NULL)
  {
  	input1=*(Parsed_fixed_point*)get_operand(i,1);
  	input2=*(Parsed_fixed_point*)get_operand(i,2);
  	output=*(Parsed_fixed_point*)get_result(i);

  	(output.fractional_part) >>=16;
  	(input1.fractional_part) >>=16;
  	(input2.fractional_part) >>=16;
  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

  	y = sadd16_16(x1,x2);

  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
  	i++;
  	}


  mu_final();

  return 0;
}

char* test_subtract_16_16()
{
	  mu_test_title("Subtracting 16.16");
	  init_file("tests/gen/16_16/subtract.test");
	  int16_16 x1,x2,y;
	  x1=*(int16_16*)malloc(sizeof(int16_16));
	  x2=*(int16_16*)malloc(sizeof(int16_16));
	  Parsed_fixed_point input1;
	  Parsed_fixed_point input2;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	input2=*(Parsed_fixed_point*)get_operand(i,2);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=16;
	  	(input1.fractional_part) >>=16;
	  	(input2.fractional_part) >>=16;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = sub16_16(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}

char* test_saturated_subtract_16_16()
{
	  mu_test_title("Saturated subtracting 16.16");
	  init_file("tests/gen/16_16/saturated_subtract.test");
	  int16_16 x1,x2,y;
	  x1=*(int16_16*)malloc(sizeof(int16_16));
	  x2=*(int16_16*)malloc(sizeof(int16_16));
	  Parsed_fixed_point input1;
	  Parsed_fixed_point input2;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	input2=*(Parsed_fixed_point*)get_operand(i,2);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=16;
	  	(input1.fractional_part) >>=16;
	  	(input2.fractional_part) >>=16;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = ssub16_16(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}


char* test_multiply_16_16()
{
	  mu_test_title("Multypling 16.16");
	  init_file("tests/gen/16_16/multiply.test");
	  int16_16 x1,x2,y;
	  x1=*(int16_16*)malloc(sizeof(int16_16));
	  x2=*(int16_16*)malloc(sizeof(int16_16));
	  Parsed_fixed_point input1;
	  Parsed_fixed_point input2;
	  Parsed_fixed_point output;
	  int i=0;


	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	input2=*(Parsed_fixed_point*)get_operand(i,2);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=16;
	  	(input1.fractional_part) >>=16;
	  	(input2.fractional_part) >>=16;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = mul16_16(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}

char* test_saturated_multiply_16_16()
{
	  mu_test_title("Saturated Multypling 16.16");
	  init_file("tests/gen/16_16/saturated_multiply.test");
	  int16_16 x1,x2,y;
	  x1=*(int16_16*)malloc(sizeof(int16_16));
	  x2=*(int16_16*)malloc(sizeof(int16_16));
	  Parsed_fixed_point input1;
	  Parsed_fixed_point input2;
	  Parsed_fixed_point output;
	  int i=0;


	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	input2=*(Parsed_fixed_point*)get_operand(i,2);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=16;
	  	(input1.fractional_part) >>=16;
	  	(input2.fractional_part) >>=16;
	  	x1.p=input1.integer_part;x1.q=input1.fractional_part;
	  	x2.p=input2.integer_part;x2.q=input2.fractional_part;

	  	y = smul16_16(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}

char* test_fractional_part_16_16()
{
	mu_test_title("Fractional part 16.16");
	init_file("tests/gen/16_16/fractional.test");
	int16_16 x,y;
	x=*(int16_16*)malloc(sizeof(int16_16));
	y=*(int16_16*)malloc(sizeof(int16_16));
	Parsed_fixed_point input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(Parsed_fixed_point*)get_operand(i,1));
	   output=*(Parsed_fixed_point*)get_result(i);

	   (output.fractional_part) >>=16;
	   (input.fractional_part) >>=16;
	   x.p=input.integer_part;
	   x.q=input.fractional_part;
	   y = fract16_16(x);
	   mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	   i++;
	}

	mu_final();
  return 0;
}

char* test_integer_part_16_16()
{
	mu_test_title("Integer part 16.16");
	init_file("tests/gen/16_16/integer_part.test");
	int16_16 x,y;
	x=*(int16_16*)malloc(sizeof(int16_16));
	y=*(int16_16*)malloc(sizeof(int16_16));
	Parsed_fixed_point input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(Parsed_fixed_point*)get_operand(i,1));
	   output=*(Parsed_fixed_point*)get_result(i);

	   (output.fractional_part) >>=16;
	   (input.fractional_part) >>=16;
	   x.p=input.integer_part;
	   x.q=input.fractional_part;
	   y = floor16_16(x);
	   mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	   i++;
	}

	mu_final();
  return 0;
}

char* test_add_8_24()
{
	 mu_test_title("Adding 8.24 numbers");
	 init_file("tests/gen/8_24/add.test");
	 int8_24 x1,x2,y;
	 x1=*(int8_24*)malloc(sizeof(int8_24));
	 x2=*(int8_24*)malloc(sizeof(int8_24));
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

	  	y = add8_24(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();

    return 0;
}

char* test_saturated_add_8_24()
{
	 mu_test_title("Adding 8.24 numbers");
	 init_file("tests/gen/8_24/saturated_add.test");
	 int8_24 x1,x2,y;
	 x1=*(int8_24*)malloc(sizeof(int8_24));
	 x2=*(int8_24*)malloc(sizeof(int8_24));
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

	  	y = sadd8_24(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();

    return 0;
}


char* test_add_different_formats()
{
	mu_test_title("Add for different formats");

	int8_8* t;

	int16_16 *y,*sum;
	int16_16 z,x;
	t = (int8_8*) malloc(sizeof(int8_8));
	y = (int16_16*) malloc(sizeof(int16_16));
	sum = (int16_16*) malloc(sizeof(int16_16));

	t->p = 1; t->q=0x08;
	x = cast8_8_to_16_16(*t);
	y->p = 1; y->q=0x8000;
	sum->p = 2; sum->q=0x8800;
	z = add16_16(x,*y);
	mu_assert("error #1", ((z.p==sum->p)&&(z.q==sum->q)));

	t->p = 5; t->q=0x30;
	x = cast8_8_to_16_16(*t);
	y->p = 5; y->q=0x8201;
	sum->p = 10; sum->q=0xB201;
	z = add16_16(x,*y);
	mu_assert("error #2", ((z.p==sum->p)&&(z.q==sum->q)));

	t->p = 12; t->q=0xF0;
	x = cast8_8_to_16_16(*t);
	y->p = 23; y->q=0x1F03;
	sum->p = 36; sum->q=0x0F03;
	z = add16_16(x,*y);
	mu_assert("error #3", ((z.p==sum->p)&&(z.q==sum->q)));

	mu_final();
    return 0;
}

char* test_subtract_8_24()
{
	  mu_test_title("Subtracting 8.24");
	  init_file("tests/gen/8_24/subtract.test");
	  int8_24 x1,x2,y;
	  x1=*(int8_24*)malloc(sizeof(int8_24));
	  x2=*(int8_24*)malloc(sizeof(int8_24));
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

	  	y = sub8_24(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}

char* test_saturated_subtract_8_24()
{
	  mu_test_title("Saturated subtracting 8.24");
	  init_file("tests/gen/8_24/saturated_subtract.test");
	  int8_24 x1,x2,y;
	  x1=*(int8_24*)malloc(sizeof(int8_24));
	  x2=*(int8_24*)malloc(sizeof(int8_24));
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

	  	y = ssub8_24(x1,x2);

	  	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	  }


	  mu_final();
	return 0;
}

char* test_multiply_8_24()
{
	mu_test_title("Multypling 8.24");
	init_file("tests/gen/8_24/multiply.test");
	int8_24 x1,x2,y;
	x1=*(int8_24*)malloc(sizeof(int8_24));
	x2=*(int8_24*)malloc(sizeof(int8_24));
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

	  	y = mul8_24(x1,x2);
    	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	}


	mu_final();
	return 0;
}

char* test_saturared_multiply_8_24()
{
	mu_test_title("Saturated multypling 8.24");
	init_file("tests/gen/8_24/saturated_multiply.test");
	int8_24 x1,x2,y;
	x1=*(int8_24*)malloc(sizeof(int8_24));
	x2=*(int8_24*)malloc(sizeof(int8_24));
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

	  	y = smul8_24(x1,x2);
    	mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
	  	i++;
	}


	mu_final();
	return 0;
}



/*
char* test_constructor_8_24()
{
	mu_test_title("Constructor for 8.24 format");
    init_file("tests/gen/8_24/constructor.test");
	int8_24 y;
	float input;
	Parsed_fixed_point output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(float*)get_operand(i,1));
	  output=*(Parsed_fixed_point*)get_result(i);

		y = int8_24_new(input);
		mu_assert_line("error",i,((y.p==output.integer_part)&&(y.q==output.fractional_part)));
		i++;
	}

	mu_final();
	return 0;
}*/


char * test_foo() {
	 int foo = 7;
     mu_assert("error, foo != 7", foo == 7);
     return 0;
 }

/* all_tests function is from: http://www.jera.com/techinfo/jtns/jtn002.html */
 char * all_tests_fixed_point() {
     //mu_run_test(test_foo);
	// mu_run_test(test_comparison);
     mu_run_test(test_constructor_8_8);
     //mu_run_test(test_constructor_16_16);
	 mu_run_test(test_add);
	 mu_run_test(test_saturated_add);
     mu_run_test(test_subtract);
     mu_run_test(test_saturated_subtract);
     mu_run_test(test_multiply);
     mu_run_test(test_saturated_multiply);
     mu_run_test(test_floor);
     mu_run_test(test_floor8_8);
     mu_run_test(test_fractional_part);
     mu_run_test(test_cast_8_8_to_16_16);
     mu_run_test(test_add_16_16);
     mu_run_test(test_saturated_add_16_16);
     mu_run_test(test_subtract_16_16);
     mu_run_test(test_saturated_subtract_16_16);
     mu_run_test(test_multiply_16_16);
     mu_run_test(test_saturated_multiply_16_16);
     mu_run_test(test_cast_16_16_to_8_8);
     mu_run_test(test_fractional_part_16_16);
     mu_run_test(test_integer_part_16_16);
     mu_run_test(test_add_different_formats);
     mu_run_test(test_add_8_24);
     mu_run_test(test_saturated_add_8_24);
     mu_run_test(test_subtract_8_24);
     mu_run_test(test_saturated_subtract_8_24);
     mu_run_test(test_multiply_8_24);
     mu_run_test(test_saturared_multiply_8_24);
     return 0;
 }

#endif /* FIXEDPOINTTESTS_H_ */
