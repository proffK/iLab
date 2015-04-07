#include "M_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <limits.h>
#include <assert.h>

const int PRIME_SIZE = 10937;

const long MAX_FILE_SIZE = LONG_MAX;

///#####################################################################

long file_length(FILE* input_file, long MAX_FILE_SIZE);

char* word_buffer_create(FILE* input_file, long input_file_length);

unsigned int hash1(char** str);
///Sum hash

unsigned int hash2(char** str);
///Mul hash

unsigned int old_hash3(char* str);
///XOR hash

unsigned int hash3(char* str);
///XOR hash

unsigned int hash4(char** str);
///1 hash

unsigned int hash5(char** str);
///First char hash

unsigned int hash6(char** str);
///Length hash

unsigned int hash7(char** str);
///FAQ6 hash


int hashtest(char* buffer,long buffer_size, FILE* output_file, \
				unsigned int (*hash) (char** str));

///#####################################################################

int main(){
	FILE* input_file = 0;
	FILE* output_file = 0;
	long buffer_size = 0;
	char* buffer = 0;
	
	input_file = fopen("J. D. Salinger - The Catcher in the Rye - 1951.txt", "r");
	output_file = fopen("rezult1.cvs", "w");
	
	buffer_size = file_length(input_file, MAX_FILE_SIZE);
	buffer = word_buffer_create(input_file, buffer_size);
	
	hashtest(buffer, buffer_size, output_file, hash3);
	 
	free(buffer);
	buffer = NULL;

	return 0;
		
}
///#####################################################################
unsigned int hash1(char** str){
	int i = 0;
	unsigned int hash = 1;
	int max = strlen(*str);
	
	for(i = 0; i < max; ++i){
		
		hash += (unsigned char) (*str)[i];
	}
	
	return hash;
}
///#####################################################################
unsigned int hash2(char** str){
	int i = 0;
	unsigned int hash = 1;
	int max = strlen(*str);
	
	
	for(i = 0; i < max; ++i){
		
		hash *= (unsigned char) (*str)[i];
	}
	
	return hash;
}
///#####################################################################
unsigned int old_hash3(char* str){
	
	register unsigned int rezult = 0;
	
    if (*str == '\0')  return 0;
    
    if (*(str + 1) == '\0') return (unsigned char) *str;
    
    rezult = old_hash3(str + 1);
    
    return ((rezult << 1) | ((rezult & 1) >> (sizeof(rezult) - 1))) ^ 
			(unsigned char)(*str);

}
///#####################################################################
unsigned int hash4(char** str){
	return 1;
}
///#####################################################################
unsigned int hash5(char** str){
	return (unsigned char) (*str)[0];
}
///#####################################################################
unsigned int hash6(char** str){
	return strlen(*str);
}
///#####################################################################
unsigned int hash7(char** str){

    unsigned int hash = 0;
    
    int i = 0;
    
	int max = strlen(*str);
	
	if (str != NULL) hash = (unsigned char) (*str)[0];
	
	for(i = 1; i < max; ++i){
		hash += (unsigned char) (*str)[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
	}

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;

}

///#####################################################################

long file_length(FILE* input_file, long MAX_FILE_SIZE){
	
	long i = 0;
	int c = 0;
	
	while((c = fgetc(input_file) != EOF)){
		
		if (c == '\0') return 0;
		++i;
		
	}
	
	return i;
}

///#####################################################################

char* word_buffer_create(FILE* input_file,long input_file_length){
	
	char* buffer = NULL;
	int c = 0;
	
	assert(input_file);
	
	rewind(input_file);
	
	buffer = (char*) calloc (input_file_length + 1, sizeof(char));
	
	fread(buffer, sizeof(char), input_file_length, input_file);
	
	for (c = 0; c < input_file_length; ++c){
		
		if (buffer[c] == ' ' || buffer[c] == '\n' || buffer[c] == '\t'){
			
			buffer[c] = '\0';
			
		}
		
	}
	
	buffer[input_file_length] = '\0';
	
	return buffer;
}

///#####################################################################

int hashtest(char* buffer, long buffer_size, FILE* output_file, 
			unsigned int (*hash) (char** str)){
				
	hash_table* table = 0;
	register int i = 0, j = 1000;
	char* tempstr = 0;
	
	table = hash_table_create(PRIME_SIZE);
	
	for (i = 0; i < buffer_size - 1; ++i){
	
		if	(buffer[i] == '\0'){
			
			tempstr = buffer + i + 1;	
			
			if (!(hash_table_find(table, hash, tempstr))){
				
				hash_table_add(table, tempstr, hash);
				
			
			}
			
		}	
	}
	//clear_log();
	//hash_table_dump(table);
	while (j--) {
	
		for (i = 0; i < buffer_size - 1; ++i){
	
			if	(buffer[i] == '\0'){
			
				tempstr = buffer + i + 1;
			
				hash_table_find(table, hash, tempstr);
				
			}	
		}
		
	//if (j % 100 == 0) printf("%d\n", j);
	
	}
	
	//for (i = 0; i < table -> size; ++i){
	//	fprintf(output_file, "%d , %d \n", i, (table -> data[i]) -> size);
	//}
	
	hash_table_delete(table);
	
	return 0;
}


