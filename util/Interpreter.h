/*
 * Interpreter.h
 *
 *  Created on: 06.06.2012
 *      Author: Mircea
 */


#define FLOATING_POINT_FORMAT 1 // "Floating point format"
#define FIXED_POINT_FORMAT 2 //"Fixed point"
#define INTEGER_FORMAT 3 //"Fixed point"

struct _metadata
{
	char* test_title;
	int number_of_operands;
	int type_of_operands;
	int type_of_result;
	int accepts_error; //whether the operation accepts error for test
	float max_absolute_error; // the maximum acceptable absolute error
	float max_relative_error; // the maximum acceptable relative error
};

struct _parsed_fixed_point
{
	unsigned int integer_part;
	unsigned int fractional_part; // actual fractional part * 2^16
};

typedef struct _parsed_fixed_point Parsed_fixed_point;

typedef struct _metadata Metadata;

void init_file(const char* file_name);
char* get_current_file_name();
Metadata* parse_metadata();
Metadata* get_metadata();
void* get_operand(int test_no,int k);
void* get_result(int test_no);
