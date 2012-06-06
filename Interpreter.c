/*
 * Interpreter.c
 *
 *  Created on: 06.06.2012
 *      Author: Mircea
 */
#include "string.h"
#include "stdlib.h"
#include "Interpreter.h"

char* current_file_name=NULL;
FILE* current_file;
Metadata* current_metadata;


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
	current_metadata = parse_metadata();
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

