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



char* current_file_name=NULL;
FILE* current_file;
Metadata* current_metadata;
void* first_operands;
void* second_operands;
int* results;
int no_of_tests;


int start;


void* get_operand(int test_no,int k)
{
  printf("no_t:%d\n",no_of_tests);
  if (test_no>=no_of_tests) return NULL;
  if (k==1) return (first_operands+test_no);
  if (k==2) return (second_operands+test_no);
  return NULL;
}

void* get_result(int test_no)
{
  if (test_no>=no_of_tests) return NULL;
  return results[test_no];
}

Metadata* get_metadata()
{
	return current_metadata;
}

void init_array(void* array, int format)
{
	if (format==FLOATING_POINT_FORMAT)
	{
		array = (float*)malloc(1000*sizeof(float));
	}
	if (format==FIXED_POINT_FORMAT)
	{
		array = (Parsed_fixed_point*)malloc(1000*sizeof(Parsed_fixed_point));
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
			result += ((*crt-'0')*p);
			p /= 10;
		}
		crt++ ;
	}
	if (state==0) return 1;
	*output = *((int*)&result);
	return 0;
}

/* if returns 1 is error in parsing, 0 parsing ok */
int parse_input_as_binary_fixed_point(char* input,Parsed_fixed_point* output)
{
	char* crt = input;
    int integer_part=0;
    int fractional_part=0;
	int state = 0; /* 0 - must be [0-1]; 1 - must be [0-1] or . or NULL; 2 - must be [0-1] or NULL */
	int p = 2^16;
	while (*crt)
	{
		if ((state==0)||(state==2))
			if (((int)(*crt)< '0')||((int)(*crt)> '1'))
				return 1;
		if (state==1)
			if ((((int)(*crt)< '0')||((int)(*crt)> '1')) && (*crt!='.'))
				return 1;
		if (state==0)
		{
			integer_part *=2;
			integer_part += (*crt-'0');
			state = 1;
		}
		if (state==1)
		{
			if (*crt!='.')
			{
				integer_part *=2;
				integer_part += (*crt-'0');
			    state = 1;
			}else{
				state = 2;
			}
		}

		if (state==2)
		{
			fractional_part += ((*crt-'0')*p);
			p /= 2;
		}
		crt++ ;
	}
	if (state==0) return 1;
	output->integer_part = integer_part;
	output->fractional_part = fractional_part;
	return 0;
}

int parse_input(char* input,void* output,int format)
{
	int k=0;
	if (format==FLOATING_POINT_FORMAT) k=parse_input_as_float(input,output);
	if (format==FIXED_POINT_FORMAT) k=parse_input_as_binary_fixed_point(input,output);
	return k;
}
void parse_file()
{
	int test_no;
	char* first_operand="";
	char* second_operand="";
	char* result="";

	current_metadata = parse_metadata();
    printf("no of operands:%d\n",current_metadata->number_of_operands);
	init_array(first_operands,current_metadata->type_of_operands);
	init_array(results,current_metadata->type_of_result);
	if (current_metadata->number_of_operands==2) init_array(first_operand,current_metadata->type_of_result);

	no_of_tests = 0;
	fseek ( current_file , start, SEEK_SET );
	while (!feof(current_file))
    {
    	if (current_metadata->number_of_operands==1) fscanf(current_file,"#%d %s %s",&test_no,first_operand,result);
    	if (current_metadata->number_of_operands==2) fscanf(current_file,"#%d %s %s %s",&test_no,first_operand,second_operand,result);
      parse_input(first_operand,first_operands+test_no,current_metadata->type_of_operands);
        parse_input(result,results+test_no,current_metadata->type_of_result);
        if (current_metadata->number_of_operands==2) parse_input(first_operand,first_operands,current_metadata->type_of_operands);
        no_of_tests++;
    }
}

Metadata* parse_metadata()
{
	Metadata* meta = (Metadata*) malloc(sizeof(Metadata));
	char auxx[1000];
	fread(auxx,sizeof(char),1000,current_file);
	meta->test_title = (char*)malloc(50*sizeof(char));
	int cnt=0;
    char* crt = auxx;
    start=0;
    printf(">>%s\n",crt);
	while (cnt<4)
	{
		if (*crt=='\n'){ *crt=0;cnt++;}
		if (*crt==':') *crt=0;
		crt ++;
		start++;
	}
	//printf(">>%s\n",auxx);
	crt = auxx;
	cnt = 0;
	while (cnt<8)
	{
		if (*crt==0)
		{
			//printf(">>%s %d\n",crt+2,cnt);
			if (cnt==0) strcpy(meta->test_title,crt+1);
			if (cnt==2) meta->number_of_operands=atoi(crt+1);
			cnt++;
		}
		crt++;
	}


    //strcpy(meta->test_title,auxx);
	//fscanf(current_file,"Title: %s",meta->test_title);
	//fscanf(current_file,"Operands: %d",&(meta->number_of_operands));
    printf("!!%s %d\n",meta->test_title,meta->number_of_operands);
	//char* aux="asda";
	//fscanf(current_file,"Type of operands: %s\n",aux);
	/*if (strcmp(aux,"FLOATING POINT")) meta->type_of_operands = FLOATING_POINT_FORMAT;
	if (strcmp(aux,"FIXED POINT BINARY")) meta->type_of_operands = FIXED_POINT_FORMAT;

	fscanf(current_file,"Type of result: %s\n",aux);
    if (strcmp(aux,"FLOATING POINT")) meta->type_of_result = FLOATING_POINT_FORMAT;
	if (strcmp(aux,"FIXED POINT BINARY")) meta->type_of_result = FIXED_POINT_FORMAT;
*/meta->type_of_operands = FLOATING_POINT_FORMAT;
meta->type_of_result = FIXED_POINT_FORMAT;
	//fscanf(current_file,"Accepts error: %s\n",aux);
	meta->accepts_error = 0;//strcmp(aux,"FALSE");

	return meta;
}
void init_file(const char* file_name)
{
   printf("intro\n");
   if (current_file_name) free(current_file_name);
   current_file_name = (char*) malloc(sizeof(char)*(strlen(file_name)+1));
   strcpy(current_file_name,file_name);
   current_file = fopen(current_file_name,"r");
  parse_file();
}
