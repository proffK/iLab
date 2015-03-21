#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "resourses.h"
#include <assert.h>

int disasm(FILE* sourse, double* buffer, int buffer_size);

int main(int argc, char* argv[]){
	char sign[2] = {};
	int buffer_size = 0;
	FILE* byte_code = 0;
	FILE* sourse = 0;
	int sourse_size = 0;
	char* output_file_name = "";
	double* buffer = (double*) calloc (MAX_BYTE_CODE_SIZE, sizeof(double));
	
	assert(buffer);
	
	if (argc == 1) {
		printf("Empty input file name\n");
		free(buffer);
		return 0;
	}
	
	if (argc == 2) {
		printf("Empty output file name\n");
		free(buffer);
		return 0;
	}
	
	if (argc == 3) {
		output_file_name = strcat(argv[2],".kasm");
	}
	
	byte_code = fopen(argv[1], "rb");
	
	fread(sign, sizeof(char), 2, byte_code);
	
	if (sign[0] != 'k' || sign[1] != 'k') {
		printf("Incorrect firmware sign\n");
		return 0;
	}
	
	buffer_size = fread(buffer, sizeof(double), MAX_BYTE_CODE_SIZE, byte_code);
	sourse = fopen(output_file_name, "w");
	
	if (buffer_size == 0) {
		printf("Disassembler error:Incorrect input file\n");
		free(buffer);
		fclose(sourse);
		fclose(byte_code);		
		return 0;
	}
	
	sourse_size = disasm(sourse, buffer, buffer_size);
	
	 if (sourse_size > buffer_size) {
		printf("Disassembler error:Incorrect input file\n");
		free(buffer);
		fclose(sourse);
		fclose(byte_code);		
		return 0;
	}
	
	printf("Disassemble complete\n");
	
	
	free(buffer);
	fclose(sourse);
	fclose(byte_code);
	return 0;
	
} 

int disasm(FILE* sourse, double* buffer, int buffer_size){
	int counter = 0;
	while (buffer[counter] != -1 && counter <= buffer_size) {
		fprintf(sourse ,"%d: ", counter);
		switch ((int) buffer[counter]) {
			case RPUSH:
				++counter;
				fprintf(sourse, "push %lg\n", buffer[counter]);
				++counter;
				break;
			case PUSH:
				++counter;
				fprintf(sourse, "push r%lg\n", buffer[counter]);
				++counter;				
				break;
			case POP:
				++counter;
				fprintf(sourse, "pop r%lg\n", buffer[counter]);
				++counter;				
				break;
			case ADD:
				++counter;
				fprintf(sourse, "add\n");
				break;
			case SUB:
				++counter;
				fprintf(sourse, "sub\n");
				break;
			case MUL:
				++counter;
				fprintf(sourse, "mul\n");
				break;
			case DIV:
				++counter;
				fprintf(sourse, "div\n");
				break;	
			case CALL:
				++counter;
				fprintf(sourse, "call %lg\n", buffer[counter]);
				++counter;
				break;
			case RET:
				++counter;
				fprintf(sourse, "ret\n");
				break;
			case JP:
				++counter;
				fprintf(sourse, "jp %lg\n", buffer[counter]);
				++counter;
				break;
			case JE:
				++counter;
				fprintf(sourse, "je %lg\n", buffer[counter]);
				++counter;
				break;
			case JNE:
				++counter;
				fprintf(sourse, "jne %lg\n", buffer[counter]);
				++counter;
				break;
			case JA:
				++counter;
				fprintf(sourse, "ja %lg\n", buffer[counter]);
				++counter;
				break;	
			case JNA:
				++counter;
				fprintf(sourse, "jna %lg\n", buffer[counter]);
				++counter;
				break;
			case JB:
				++counter;
				fprintf(sourse, "jb %lg\n", buffer[counter]);
				++counter;
				break;	
			case JNB:
				++counter;
				fprintf(sourse, "jnb %lg\n", buffer[counter]);
				++counter;
				break;
			case OUT:
				++counter;
				fprintf(sourse, "out\n");
				break;
			case INP:
				++counter;
				fprintf(sourse, "inp\n");
				break;
			default:
				return -1;
				break;
			}
		}
		return counter;
}
