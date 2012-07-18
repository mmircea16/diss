/*
 * FixedPointMathTests.h
 *
 *  Created on: 18 Jul 2012
 *      Author: moisem
 */

#ifndef FIXEDPOINTMATHTESTS_H_
#define FIXEDPOINTMATHTESTS_H_

char* test_div_8_8()
{
	  mu_test_title("Divide for 8.8");
	  init_file("tests/short/8_8/divide.test");
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
	  	x1 = set_int_part_24_8(x1,input1.integer_part);
		x1 = set_fract_part_24_8(x1,input1.fractional_part);
	  	x2 = set_int_part_24_8(x2,input2.integer_part);
		x2 = set_fract_part_24_8(x2,input2.fractional_part);

	  	y = div8_8(x1,x2);

	 	mu_assert_line("error",i,((get_int_part_24_8(y)==output.integer_part)&&(get_fract_part_24_8(y)==output.fractional_part)));
	  	i++;
	  	}


	  mu_final();

	  return 0;
}

char * all_tests_fixed_point_math() {
	mu_run_test(test_div_8_8);
	return 0;
}

#endif /* FIXEDPOINTMATHTESTS_H_ */
