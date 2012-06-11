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
long long first_operands[2000];
long long second_operands[2000];
long long results[2000];

fpos_t test_positions[3000];

int no_of_tests;


int start;




Metadata* get_metadata()
{
	return current_metadata;
}

void init_array(void** array, int format)
{
	if (format==FLOATING_POINT_FORMAT)
	{
		*array = (float*)malloc(1*sizeof(float));
	}
	if (format==FIXED_POINT_FORMAT)
	{
		*array = (Parsed_fixed_point*)malloc(1000*sizeof(Parsed_fixed_point));
	}
}


/* if returns 1 is error in parsing, 0 parsing ok */
int parse_input_as_float(char* input,float* output)
{
	/* input is float if: [0-9]+.?[0-9]* */
	char* crt = input;
	float result=0.0;
    float sign=1;
	float p = 0.1;
	int state = 4; /* 0 - must be [0-9]; 1 - must be [0-9] or . or NULL; 2 - must be [0-9] or NULL; 4- must be - or [0-9] */
	while (*crt)
	{
		if ((state==0)||(state==2))
			if (((int)(*crt)< '0')||((int)(*crt)> '9'))
				return 1;
		if (state==1)
			if ((((int)(*crt)< '0')||((int)(*crt)> '9')) && (*crt!='.'))
				return 1;
		if (state==4)
			if ((((int)(*crt)< '0')||((int)(*crt)> '9')) && (*crt!='-'))
				return 1;

		if (state==4)
		{
			if (*crt=='-')
			{
				sign=-1;
				state=0;
			}else{
				result *=10;
				result += (*crt-'0');
				state=1;
			}
		}else if (state==0)
		{
			result *=10;
			result += (*crt-'0');
			state = 1;
		}else if (state==1)
		{
			if (*crt!='.')
			{
				result *=10;
				result += (*crt-'0');
			    state = 1;
			}else{
				state = 2;
			}
		}else if (state==2)
		{
			result += ((*crt-'0')*p);
			p /= 10;
		}
		crt++ ;
	}
	if (state==0) return 1;
	*output = (result*sign);
	return 0;
}

/* if returns 1 is error in parsing, 0 parsing ok */
int parse_input_as_binary_fixed_point(char* input,Parsed_fixed_point* output)
{
	char* crt = input;
    int integer_part=0;
    int fractional_part=0;
	int state = 0; /* 0 - must be [0-1]; 1 - must be [0-1] or . or NULL; 2 - must be [0-1] or NULL */
	int p = 1<<15;
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
		}else if (state==1)
		{
			if (*crt!='.')
			{
				integer_part *=2;
				integer_part += (*crt-'0');
			    state = 1;
			}else{
				state = 2;
			}
		}else if (state==2)
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

int parse_input(char* input,int* output,int format)
{
	int k=0;
	if (format==FLOATING_POINT_FORMAT) k=parse_input_as_float(input,(float*)output);
	if (format==FIXED_POINT_FORMAT) k=parse_input_as_binary_fixed_point(input,(Parsed_fixed_point*)output);
	return k;
}
void parse_file()
{
	int test_no;

	current_metadata = parse_metadata();

	no_of_tests = 0;
	fseek ( current_file , start, SEEK_SET );
	int poz=0;
	char auxx;
	fpos_t pos;

	while (!feof(current_file))
    {
		auxx=fgetc(current_file);
		if (auxx=='#')
		{
			//printf("auxx:%c\n",auxx);
			//fgetpos(current_file,&test_positions[no_of_tests]);
			//printf("-------");
			//exit(0);
			no_of_tests++;
		}

    }
}

void go_to_test(int n)
{
	fseek ( current_file , start, SEEK_SET );
	int poz=0;
	char auxx;
	n++;
	while ((!feof(current_file))&&n)
	{
	  auxx=fgetc(current_file);
	  if (auxx=='#') n--;
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
   // printf(">>%s\n",crt);
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
    //printf("!!%s %d\n",meta->test_title,meta->number_of_operands);
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
   //printf("intro\n");
   if (current_file_name) free(current_file_name);
   current_file_name = (char*) malloc(sizeof(char)*(strlen(file_name)+1));
   strcpy(current_file_name,file_name);
   current_file = fopen(current_file_name,"r");
  parse_file();
}

void* get_operand(int test_no,int k)
{
 // printf("no_t:%d %d\n",no_of_tests,test_no);

  int d;
  char* s=(char*)malloc(50*sizeof(char));
  char* ss=(char*)malloc(50*sizeof(char));
  void* res=malloc(8);
  go_to_test(test_no);
  if (test_no>=no_of_tests) return NULL;
  if (k==1) {
	  fscanf(current_file,"%d %s",&d,s);
	  parse_input(s,res,current_metadata->type_of_operands);
  }
  if (k==2) {
	  fscanf(current_file,"%d %s %s",&d,ss,s);
	  parse_input(s,res,current_metadata->type_of_operands);
  }
  return res;
}

void* get_result(int test_no)
{
  int d;
  void* res=malloc(8);
  if (test_no>=no_of_tests) return NULL;
  char* s=(char*)malloc(50*sizeof(char));
  char* ss=(char*)malloc(50*sizeof(char));
  char* sss=(char*)malloc(50*sizeof(char));
  go_to_test(test_no);
  if (current_metadata->number_of_operands==2)
  fscanf(current_file,"%d %s %s %s",&d,sss,ss,s);
  else
  fscanf(current_file,"%d %s %s",&d,sss,s);
  parse_input(s,res,current_metadata->type_of_result);
  return res;
}
