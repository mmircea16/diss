/*
 * FixedPointMathTests.h
 *
 *  Created on: 18 Jul 2012
 *      Author: moisem
 */

#ifndef FIXEDPOINTMATHTESTS_H_
#define FIXEDPOINTMATHTESTS_H_

char* test_div_8_8_v2()
{
	  mu_test_title("Divide for 8.8 - Newton Raphson");
	  init_file("tests/gen/8_8/divide.test");
	  int8_8 x1,x2,y;
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
	  	x1 = set_int_part_8_8(x1,input1.integer_part);
		x1 = set_fract_part_8_8(x1,input1.fractional_part);
	  	x2 = set_int_part_8_8(x2,input2.integer_part);
		x2 = set_fract_part_8_8(x2,input2.fractional_part);

	  	y = div8_8_v2(x1,x2);
	 	mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_div_8_8()
{
	  mu_test_title("Divide for 8.8");
	  init_file("tests/gen/8_8/divide.test");
	  int8_8 x1,x2,y;
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
	  	x1 = set_int_part_8_8(x1,input1.integer_part);
		x1 = set_fract_part_8_8(x1,input1.fractional_part);
	  	x2 = set_int_part_8_8(x2,input2.integer_part);
		x2 = set_fract_part_8_8(x2,input2.fractional_part);

	  	y = div8_8(x1,x2);
	 	mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_div_16_16()
{
	  mu_test_title("Divide for 16.16");
	  init_file("tests/gen/16_16/divide.test");
	  int16_16 x1,x2,y;
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
	  	x1 = set_int_part_16_16(x1,input1.integer_part);
		x1 = set_fract_part_16_16(x1,input1.fractional_part);
	  	x2 = set_int_part_16_16(x2,input2.integer_part);
		x2 = set_fract_part_16_16(x2,input2.fractional_part);

	  	y = div16_16(x1,x2);
	 	mu_assert_line("error",i,((get_int_part_16_16(y)==output.integer_part)&&(get_fract_part_16_16(y)==output.fractional_part)));
	  	//printf("diff:%d %d\n",get_int_part_16_16(y)-output.integer_part,get_fract_part_16_16(y)-output.fractional_part);
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_div_16_16_v2()
{
	  mu_test_title("Divide for 16.16 - Newton Raphson");
	  init_file("tests/gen/16_16/divide.test");
	  int16_16 x1,x2,y;
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
	  	x1 = set_int_part_16_16(x1,input1.integer_part);
		x1 = set_fract_part_16_16(x1,input1.fractional_part);
	  	x2 = set_int_part_16_16(x2,input2.integer_part);
		x2 = set_fract_part_16_16(x2,input2.fractional_part);

	  	y = div16_16_v2(x1,x2);
	 	mu_assert_line("error",i,((get_int_part_16_16(y)==output.integer_part)&&(get_fract_part_16_16(y)==output.fractional_part)));
	  	//printf("diff:%d %d\n",get_int_part_16_16(y)-output.integer_part,get_fract_part_16_16(y)-output.fractional_part);
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_bits4_most_significant()
{
	mu_test_title("Testing detecting most significant bit");
	char i;
	char y;
	char results[16]={0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4};
	for (i=0;i<16;i++)
	{
        y = bits4_most_significant(i);
        mu_assert_line("error",i,results[(int)i]==y);
	}
	mu_final();
    return 0;
}

char* test_div_8_24()
{
	  mu_test_title("Divide for 8.24");
	  init_file("tests/gen/8_24/divide.test");
	  int8_24 x1,x2,y;
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
	  	x1 = set_int_part_8_24(x1,input1.integer_part);
		x1 = set_fract_part_8_24(x1,input1.fractional_part);
	  	x2 = set_int_part_8_24(x2,input2.integer_part);
		x2 = set_fract_part_8_24(x2,input2.fractional_part);

	  	y = div8_24(x1,x2);

	  	//printf("diff:%d %d %d\n",i,get_int_part_8_24(y)-output.integer_part,get_fract_part_8_24(y)-output.fractional_part);
	 	//mu_assert_line("error",i,((get_int_part_8_24(y)==output.integer_part)&&(get_fract_part_8_24(y)==output.fractional_part)));
	  	int32_t out = (output.integer_part<<24)+output.fractional_part;
	  	mu_assert_line_with_error("error",i,(out - y),1);
	    i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_div_8_24_v2()
{
	  mu_test_title("Divide for 8.24 - NewtonRaphson");
	  init_file("tests/gen/8_24/divide.test");
	  int8_24 x1,x2,y;
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
	  	x1 = set_int_part_8_24(x1,input1.integer_part);
		x1 = set_fract_part_8_24(x1,input1.fractional_part);
	  	x2 = set_int_part_8_24(x2,input2.integer_part);
		x2 = set_fract_part_8_24(x2,input2.fractional_part);

	  	y = div8_24_v2(x1,x2);

	  	//printf("diff:%d %d %d\n",i,get_int_part_8_24(y)-output.integer_part,get_fract_part_8_24(y)-output.fractional_part);
	  	int32_t out = (output.integer_part<<24)+output.fractional_part;
	 	mu_assert_line_with_error("error",i,(out - y),1);
	    i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_sqrt_8_8()
{
	  mu_test_title("Sqrt for 8.8");
	  init_file("tests/gen/8_8/sqrt.test");
	  int8_8 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	x1 = set_int_part_8_8(x1,input1.integer_part);
		x1 = set_fract_part_8_8(x1,input1.fractional_part);

	  	y = sqrt8_8(x1);

	  	int16_t out = (output.integer_part<<8)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_sqrt_16_16()
{
	  mu_test_title("Sqrt for 16.16");
	  init_file("tests/gen/16_16/sqrt.test");
	  int16_16 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=16;
	  	(input1.fractional_part) >>=16;
	  	x1 = set_int_part_16_16(x1,input1.integer_part);
		x1 = set_fract_part_16_16(x1,input1.fractional_part);

	  	y = sqrt16_16(x1);

	  	int32_t out = (output.integer_part<<16)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_sqrt_8_24()
{
	  mu_test_title("Sqrt for 8.24");
	  init_file("tests/gen/8_24/sqrt.test");
	  int8_24 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=8;
	  	(input1.fractional_part) >>=8;
	  	x1 = set_int_part_8_24(x1,input1.integer_part);
		x1 = set_fract_part_8_24(x1,input1.fractional_part);

	  	y = sqrt8_24(x1);

	  	int32_t out = (output.integer_part<<24)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_sqrt_24_8()
{
	  mu_test_title("Sqrt for 24.8");
	  init_file("tests/gen/24_8/sqrt.test");
	  int24_8 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	x1 = set_int_part_24_8(x1,input1.integer_part);
		x1 = set_fract_part_24_8(x1,input1.fractional_part);

	  	y = sqrt24_8(x1);

	  	int32_t out = (output.integer_part<<8)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_exp_8_8()
{
	  mu_test_title("Exp for 8.8");
	  init_file("tests/gen/8_8/exp.test");
	  int8_8 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	x1 = set_int_part_8_8(x1,input1.integer_part);
		x1 = set_fract_part_8_8(x1,input1.fractional_part);

	  	y = exp8_8(x1);

	  	int16_t out = (output.integer_part<<8)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_exp_16_16()
{
	  mu_test_title("Exp for 16.16");
	  init_file("tests/gen/16_16/exp.test");
	  int16_16 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=16;
	  	(input1.fractional_part) >>=16;
	  	x1 = set_int_part_16_16(x1,input1.integer_part);
		x1 = set_fract_part_16_16(x1,input1.fractional_part);

	  	y = exp16_16_v2(x1);

	  	int32_t out = (output.integer_part<<16)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),1024);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_exp_24_8()
{
	  mu_test_title("Exp for 24.8");
	  init_file("tests/gen/24_8/exp.test");
	  int24_8 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	x1 = set_int_part_24_8(x1,input1.integer_part);
		x1 = set_fract_part_24_8(x1,input1.fractional_part);

	  	y = exp24_8_v2(x1);

	  	int32_t out = (output.integer_part<<8)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),10240);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}


char* test_log_8_8()
{
	  mu_test_title("Log for 8.8");
	  init_file("tests/gen/8_8/log.test");
	  int8_8 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	x1 = set_int_part_8_8(x1,input1.integer_part);
		x1 = set_fract_part_8_8(x1,input1.fractional_part);

	  	y = log8_8(x1);

	  	int16_t out = (output.integer_part<<8)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_log_16_16()
{
	  mu_test_title("Log for 16.16");
	  init_file("tests/gen/16_16/log.test");
	  int16_16 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=16;
	  	(input1.fractional_part) >>=16;
	  	x1 = set_int_part_16_16(x1,input1.integer_part);
		x1 = set_fract_part_16_16(x1,input1.fractional_part);

	  	y = log16_16_v2(x1);

	  	int32_t out = (output.integer_part<<16)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_log_8_24()
{
	  mu_test_title("Log for 8.24");
	  init_file("tests/gen/8_24/log.test");
	  int8_24 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=8;
	  	(input1.fractional_part) >>=8;
	  	x1 = set_int_part_8_24(x1,input1.integer_part);
		x1 = set_fract_part_8_24(x1,input1.fractional_part);

	  	y = log8_24_v2(x1);

	  	int32_t out = (output.integer_part<<24)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_log_24_8()
{
	  mu_test_title("Log for 24.8");
	  init_file("tests/gen/24_8/log.test");
	  int24_8 x1,y;
	  Parsed_fixed_point input1;
	  Parsed_fixed_point output;
	  int i=0;
	  while (get_operand(i,1)!=NULL)
	  {
	  	input1=*(Parsed_fixed_point*)get_operand(i,1);
	  	output=*(Parsed_fixed_point*)get_result(i);

	  	(output.fractional_part) >>=24;
	  	(input1.fractional_part) >>=24;
	  	x1 = set_int_part_24_8(x1,input1.integer_part);
		x1 = set_fract_part_24_8(x1,input1.fractional_part);

	  	y = log24_8(x1);

	  	int32_t out = (output.integer_part<<8)+output.fractional_part;
	    mu_assert_line_with_error("error",i,(out - y),4);
	 	//mu_assert_line("error",i,((get_int_part_8_8(y)==output.integer_part)&&(get_fract_part_8_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_norm_8_8()
{
	mu_test_title("Testing normalization");
	init_file("tests/short/8_8/norm.test");
	int8_8 x,y;
	Parsed_fixed_point input;
	int output;
	int i=0;
	while (get_operand(i,1)!=NULL)
	{
	   input=(*(Parsed_fixed_point*)get_operand(i,1));
	   output=*(int*)get_result(i);

	   (input.fractional_part) >>=24;
	   x = set_int_part_8_8(x,input.integer_part);
	   x = set_fract_part_8_8(x,input.fractional_part);

	   y = norm8_8(x);
	   mu_assert_line("error",i,y==output);
	   i++;
	}

	mu_final();
  return 0;
}

char* test_div_24_8()
{
	  mu_test_title("Divide for 24.8");
	  init_file("tests/gen/24_8/divide.test");
	  int24_8 x1,x2,y;
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
	  	x1 = set_int_part_24_8(x1,input1.integer_part);
		x1 = set_fract_part_24_8(x1,input1.fractional_part);
	  	x2 = set_int_part_24_8(x2,input2.integer_part);
		x2 = set_fract_part_24_8(x2,input2.fractional_part);

	  	y = div24_8(x1,x2);

	  	//printf("diff:%d %d %d\n",i,get_int_part_8_24(y)-output.integer_part,get_fract_part_8_24(y)-output.fractional_part);
	 	//mu_assert_line("error",i,((get_int_part_8_24(y)==output.integer_part)&&(get_fract_part_8_24(y)==output.fractional_part)));
	  	int32_t out = (output.integer_part<<8)+output.fractional_part;
	  	mu_assert_line_with_error("error",i,(out - y),1);
	    i++;
	  	}


	  mu_final();

	  return 0;
}

char* test_div_24_8_v2()
{
	  mu_test_title("Divide for 24.8 - Newton Rapshon");
	  init_file("tests/gen/24_8/divide.test");
	  int24_8 x1,x2,y;
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
	  	x1 = set_int_part_24_8(x1,input1.integer_part);
		x1 = set_fract_part_24_8(x1,input1.fractional_part);
	  	x2 = set_int_part_24_8(x2,input2.integer_part);
		x2 = set_fract_part_24_8(x2,input2.fractional_part);

	  	y = div24_8(x1,x2);

	  	//printf("diff:%d %d %d\n",i,get_int_part_8_24(y)-output.integer_part,get_fract_part_8_24(y)-output.fractional_part);
	 	//mu_assert_line("error",i,((get_int_part_8_24(y)==output.integer_part)&&(get_fract_part_8_24(y)==output.fractional_part)));
	  	int32_t out = (output.integer_part<<8)+output.fractional_part;
	  	mu_assert_line_with_error("error",i,(out - y),1);
	    i++;
	  	}


	  mu_final();

	  return 0;
}

char * all_tests_fixed_point_math() {
	mu_run_test(test_div_8_8);
	mu_run_test(test_div_8_8_v2);
	mu_run_test(test_div_16_16);
	mu_run_test(test_div_16_16_v2);
	mu_run_test(test_div_8_24);
	mu_run_test(test_div_8_24_v2);
	mu_run_test(test_div_24_8);
	mu_run_test(test_div_24_8_v2);
	mu_run_test(test_sqrt_8_8);
	mu_run_test(test_sqrt_16_16);
	mu_run_test(test_sqrt_8_24);
	mu_run_test(test_sqrt_24_8);
	mu_run_test(test_log_8_8);
	mu_run_test(test_log_16_16);
	mu_run_test(test_log_8_24);
	mu_run_test(test_log_24_8);
	mu_run_test(test_exp_8_8);
	mu_run_test(test_exp_16_16);
	mu_run_test(test_exp_24_8);
	mu_run_test(test_bits4_most_significant);
	mu_run_test(test_norm_8_8);
	return 0;
}

#endif /* FIXEDPOINTMATHTESTS_H_ */
