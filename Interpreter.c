/*
 * Interpreter.c
 *
 *  Created on: 06.06.2012
 *      Author: Mircea
 */
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "Interpreter.h"

#define

char* current_file_name=NULL;
FILE* current_file;
Metadata* current_metadata;
int* first_operands;
int* second_operands;
int* results;




void init_file(const char* file_name)
{
   if (current_file_name) free(current_file_name);
   current_file_name = (char*) malloc(sizeof(char)*(strlen(file_name)+1));
   strcpy(current_file_name,file_name);
   current_file = fopen(current_file_name,"r");
}

Metadata* get_metadata()
{
	return current_metadata;
}

void parse_file()
{
	int test_no;
	char* first_operand;
	char* second_operand;
	char* result;

	current_metadata = parse_metadata();

	while (!feof(current_file))
    {
    	if (current_metadata->number_of_operands==1) fscanf(current_file,"#%d %s %s",&test_no,first_operand,result);
    	if (current_metadata->number_of_operands==2) fscanf(current_file,"#%d %s %s %s",&test_no,first_operand,second_operand,result);
    }
}

/* if returns 1 is error in parsing, 0 parsing ok */
int parse_input_as_float(char* input,int* output)
{
	/* input is float if: [0-9]+.?[0-9]* */
	char* crt = input;
	float result=0;

	float p = 0.1;
	int state = 0; /* 0 - must be [0-9]; 1 - must be [0-9] or . or NULL; 2 - must be [0-9] or NULL */
	while (*crt)
	{
		if ((state==0)||(state==2))
			if (((int)(*crt)< '0')||((int)(*crt)> '9'))
				return 1;
		if (state==1)
			if ((((int)(*crt)< '0')||((int)(*crt)> '9')) && (*crt!='.'))
				return 1;
		if (state==0)
		{
			result *=10;
			result += (*crt-'0');
			state = 1;
		}
		if (state==1)
		{
			if (*crt!='.')
			{
				result *=10;
				result += (*crt-'0');
			    state = 1;
			}else{
				state = 2;
			}
		}

		if (state==2)
		{
			result += (*crt-'0')*p;
			p /= 10;
		}
		crt++ ;
	}
	if (state==0) return 1;
	*output = *((int*)&result);
	return 0;
}


Metadata* parse_metadata()
{
	Metadata* meta = (Metadata*) malloc(sizeof(Metadata));
	fscanf(current_file,"Title:%s\n",meta->test_title);
	fscanf(current_file,"Operands:%d\n",&(meta->number_of_operands));

	char* aux;
	fscanf(current_file,"Type of operands:%d\n",aux);
	if (strcmp(aux,"FLOATING POINT")) meta->type_of_operands = FLOATING_POINT_FORMAT;
	if (strcmp(aux,"FIXED POINT 8.8")) meta->type_of_operands = FIXED_POINT_8_8;

	fscanf(current_file,"Type of result:%d\n",aux);
    if (strcmp(aux,"FLOATING POINT")) meta->type_of_result = FLOATING_POINT_FORMAT;
	if (strcmp(aux,"FIXED POINT 8.8")) meta->type_of_result = FIXED_POINT_8_8;

	fscanf(current_file,"Accepts error:%d\n",aux);
	meta->accepts_error = strcmp(aux,"FALSE");

	return meta;
}

