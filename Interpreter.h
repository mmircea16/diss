/*
 * Interpreter.h
 *
 *  Created on: 06.06.2012
 *      Author: Mircea
 */


#define FLOATING_POINT_FORMAT 1 // "Floating point format"
#define FIXED_POINT_8_8 2 //"Fixed point 8.8"

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

typedef struct _metadata Metadata;

void init_file(char* file_name);
void reset();
char* get_current_file_name();
Metadata* get_metadata();
void* get_operand(int test_no,int k);
void* get_result(int test_no);
