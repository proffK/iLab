#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "resourses.h"
#include <assert.h>
#include "m_stack.h"

int compile(FILE* source, double* buffer);

int main(int argc, char* argv[]){
	int buffer_size = 0;
	FILE* byte_code = 0;
	FILE* source = 0;
	char sign[2] = {'k', 'k'};
	char* output_file_name = "";
	double* buffer = (double*) calloc (MAX_BYTE_CODE_SIZE, sizeof(double));
	assert(buffer);
	
	if (argc == 1) {
		printf("Empty input file  name\n");
		free(buffer);
		return 0;
	}
	
	if (argc == 2) {
		printf("Empty output file name\n");
		free(buffer);
		return 0;
	}
	
	source = fopen(argv[1], "r+");
	output_file_name = strcat(argv[2],".kvm");
	byte_code = fopen(output_file_name, "wb");
	buffer_size = compile(source, buffer);
	
	if (buffer_size == 0) {
		printf("Translation error:Incorrect input file\n");
		free(buffer);
		fclose(source);
		fclose(byte_code);		
		return 0;
	}
	
	rewind(source);
	buffer_size = compile(source, buffer);

	if (buffer_size == 0) {
		printf("Translation error:Incorrect input file\n");
		free(buffer);
		fclose(source);
		fclose(byte_code);		
		return 0;
	}
	fwrite(sign, sizeof(char), 2, byte_code);

	if (fwrite(buffer, sizeof(double), buffer_size, byte_code) != buffer_size) {
		printf("Translation error\n");
		free(buffer);
		fclose(source);
		fclose(byte_code);
		return 0;
	}
	
	printf("Translation complete.\nByte-code size = %d\n", buffer_size);
	
	free(buffer);
	fclose(source);
	fclose(byte_code);
	return 0; 
}

int compile(FILE* source, double* buffer){
	static int compile_times = 0;
	static int* label_table = 0;
	static int label_table_size = 0;
	int counter = 0;
	int templab = 0;
	int tempint = 0;
	int i = 0;
	double tempval = 0;
	char tempcom[6] = "";
	char temparg[10] = "";	
	stack* st = NULL;
	st = stack_create(COMPILATOR_STACK_SIZE);
		
	while (fscanf(source, "%s", tempcom) > 0) {	
		switch (tempcom[0]) {
			case 'p':
				switch (tempcom[1]) {
					case 'u':
					
					if (tempcom[2] != 's' || tempcom[3] != 'h' || tempcom[4] != '\0'){
						printf("incorrect operator %d : %s\n", counter, tempcom);
						return 0;
					}
					
					fscanf(source, "%s", temparg);
					if (sscanf(temparg, "r%d", &tempint)) {
						if (tempint < NUMBER_OF_REGISTORS) {
								buffer[counter] = PUSH;
								++counter;
								buffer[counter] = tempint;
								++counter;
								break;
						}
						else{
							printf("incorrect argument in operator push %d : %s\n", counter\
							,temparg);
							return 0;
						}
					break;							
					}
					else if (sscanf(temparg, "%lg", &tempval) == 0) {
						printf("incorrect argument in operator push %d : %s\n", counter\
						, temparg);
						return 0;
					}
					else {
						buffer[counter] = RPUSH;
						++counter;
						buffer[counter] = tempval;
						++counter;
					}
					break;
									
					case 'o':
					
					switch (tempcom[2]){
						case 'p':
							if (tempcom[3] != '\0'){
								printf("incorrect operator %d : %s\n", counter, tempcom);
								return 0;
							}				
				
							buffer[counter] = POP;
							++counter;
							fscanf(source, "%s", temparg);
							if (sscanf(temparg, "r%d", &tempint)) {
								if (0 <= tempint && tempint < NUMBER_OF_REGISTORS) {
									buffer[counter] = tempint;
									++counter;
									break;	
								}
								else{
									printf("incorrect argument in operator pop %d : %s\n", counter\
											, temparg);
									return 0;
								}
							}						
							else {
								printf("incorrect argument in operator pop %d : %c\n", counter, temparg[1]);
								return 0;
							}				
							break;
						case 'w':
							if (tempcom[3] != '\0'){
								printf("incorrect operator %d : %s\n", counter, tempcom);
								return 0;
							}
							
							buffer[counter] = POW;
							++counter;
							break;
					}
				break;					
			}
			break;
			case 'a':
			
				if (tempcom[1] != 'd' || tempcom[2] != 'd' || tempcom[3] != '\0'){
					printf("incorrect operator %d : %s\n", counter, tempcom);
					return 0;
				}			
			
				buffer[counter] = ADD;
				++counter;
				break;
			case 's':
				switch (tempcom[1]){
					case 'u':
						if (tempcom[2] != 'b' || tempcom[3] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
						
						buffer[counter] = SUB;
						++counter;
						break;
					case 'i':
						if (tempcom[2] != 'n' || tempcom[3] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
						
						buffer[counter] = SIN;
						++counter;
						break;
					case 'q':
						if (tempcom[2] != 'r' || tempcom[3] != 't' \
							|| tempcom[4] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}
						buffer[counter] = SQRT;
						++counter;
						break;
					default:
						printf("incorrect operator %d : %s\n", counter, tempcom);
						break;
					}
				break;
			case 'm':
			
				if (tempcom[1] != 'u' || tempcom[2] != 'l' || tempcom[3] != '\0'){
					printf("incorrect operator %d : %s\n", counter, tempcom);
					return 0;
				}			
						
				buffer[counter] = MUL;
				++counter;
				break;
			case 'd':
			
				if (tempcom[1] != 'i' || tempcom[2] != 'v' || tempcom[3] != '\0'){
					printf("incorrect operator %d : %s\n", counter, tempcom);
					return 0;
				}			
						
				buffer[counter] = DIV;
				++counter;
				break;
			case 'o':
				switch (tempcom[3]) {
					case '\0':
						if (tempcom[1] != 'u' || tempcom[2] != 't'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
						
						buffer[counter] = OUT;
						++counter;
						break;
					case 'c':
						if (tempcom[1] != 'u' || tempcom[2] != 't'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
						
						fscanf(source, "%d", &tempint);
						
						while (tempint--){
						
						buffer[counter] = OUTC;
						++counter;
						}
						break;
					default:
						printf("incorrect operator %d : %s\n", counter, tempcom);
						return 0;
						break;
					}
				break;
			case 'c':
				switch (tempcom[1]){
					case 'o':
						if (tempcom[2] != 's' || tempcom[3] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
						
						buffer[counter] = COS;
						++counter;
						break;
					case 'a':
						if ( tempcom[2] != 'l' || tempcom[3] != 'l' \
						|| tempcom[4] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
						
						buffer[counter] = CALL;
						++counter;
						templab = -1;
						if (fscanf(source, "%d", &templab)){ 
				
							if ((templab < 0 || MAX_LABEL < templab) && templab != -1) {
								printf("incorrect argument in operator call %d : %d\n", counter, templab);
								return 0;
							}
					
							if (templab > label_table_size) {
								int i = 0;
								label_table = (int*) realloc (label_table, templab * sizeof(int));
						
								for (i = label_table_size; i < templab - 1; ++i) {
									label_table[i] = -1;
								}
						
								label_table_size = templab;
							}
					
							buffer[counter] = label_table[templab - 1];
							++counter;
						}
						else {
							printf("incorrect argument in operator call : %d\n", counter);
							return 0;
						}
				break;
				}
				break;
			case 'r':
			
				if (tempcom[1] != 'e' || tempcom[2] != 't' || tempcom[3] != '\0'){
					printf("incorrect operator %d : %s\n", counter, tempcom);
					return 0;
				}			
							
				buffer[counter] = RET;
				++counter;
				break;	
			case 'i':
				switch (tempcom[3]) {
					case '\0':
						if (tempcom[1] != 'n' || tempcom[2] != 'p'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}
				
						buffer[counter] = INP;
						++counter;
						break;
					case 'c':
						if (tempcom[1] != 'n' || tempcom[2] != 'p'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}
						
						fscanf(source, "%d", &tempint);
						
						while(tempint--){
	
							buffer[counter] = INPC;
							++counter;
						}
							
						break;
					default:
						printf("incorrect operator %d : %s\n", counter, tempcom);
						return 0;
						break;
				}
				break;
			case 'j':
				switch (tempcom[1]) {
					case 'e':
			
						if (tempcom[2] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
									
						buffer[counter] = JE;
						++counter;
						templab = -1;
						if (fscanf(source, "%d", &templab)){ 
				
							if ((templab < 0 || MAX_LABEL < templab) && templab != -1) {
								printf("incorrect argument in operator %s %d : %d\n",\
								tempcom , counter, templab);
								return 0;
							}
							
							if (templab > label_table_size) {
								int i = 0;
								label_table = (int*) realloc (label_table, templab * sizeof(int));
						
								for (i = label_table_size; i < templab - 1; ++i) {
									label_table[i] = -1;
								}
						
								label_table_size = templab;
							}
							
							buffer[counter] = label_table[templab - 1];
							++counter;
						}
						else {
							printf("incorrect argument in operator %s : %d\n",\
							tempcom, counter);
							return 0;
						}
						break;
					case 'b':
			
						if (tempcom[2] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
											
						buffer[counter] = JB;
						++counter;
						templab = -1;
						if (fscanf(source, "%d", &templab)){ 
				
							if ((templab < 0 || MAX_LABEL < templab) && templab != -1) {
								printf("incorrect argument in operator %s %d : %d\n",\
								tempcom , counter, templab);
								return 0;
							}
							
							if (templab > label_table_size) {
								int i = 0;
								label_table = (int*) realloc (label_table, templab * sizeof(int));
						
								for (i = label_table_size; i < templab - 1; ++i) {
									label_table[i] = -1;
								}
						
								label_table_size = templab;
							}
				
							buffer[counter] = label_table[templab - 1];
							++counter;
						}
						else {
							printf("incorrect argument in operator %s : %d\n",\
							tempcom, counter);
							return 0;
						}
						break;
					case 'p':
					
						if (tempcom[2] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
											
						buffer[counter] = JP;
						++counter;
						templab = -1;
						if (fscanf(source, "%d", &templab)){ 
				
							if ((templab < 0 || MAX_LABEL < templab) && templab != -1) {
								printf("incorrect argument in operator %s %d : %d\n",\
								tempcom , counter, templab);
								return 0;
							}
							
							if (templab > label_table_size) {
								int i = 0;
								label_table = (int*) realloc (label_table, templab * sizeof(int));
						
								for (i = label_table_size; i < templab - 1; ++i) {
									label_table[i] = -1;
								}
						
								label_table_size = templab;
							}
				
							buffer[counter] = label_table[templab - 1];
							++counter;
						}	
						break;					
					case 'a':
			
						if (tempcom[2] != '\0'){
							printf("incorrect operator %d : %s\n", counter, tempcom);
							return 0;
						}			
											
						buffer[counter] = JA;
						++counter;
						templab = -1;
						if (fscanf(source, "%d", &templab)){ 
				
							if ((templab < 0 || MAX_LABEL < templab) && templab != -1) {
								printf("incorrect argument in operator %s %d : %d\n",\
								tempcom , counter, templab);
								return 0;
							}
							
							if (templab > label_table_size) {
								int i = 0;
								label_table = (int*) realloc (label_table, templab * sizeof(int));
						
								for (i = label_table_size; i < templab - 1; ++i) {
									label_table[i] = -1;
								}
						
								label_table_size = templab;
							}
				
							buffer[counter] = label_table[templab - 1];
							++counter;
						}
						else {
							printf("incorrect argument in operator %s : %d\n",\
							tempcom, counter);
							return 0;
						}
						break;
					case 'n':
						switch (tempcom[2]) {
							case 'e':
			
								if (tempcom[3] != '\0'){
									printf("incorrect operator %d : %s\n", counter, tempcom);
									return 0;
								}			
													
								buffer[counter] = JNE;
								++counter;
								templab = -1;
								if (fscanf(source, "%d", &templab)){ 
				
									if ((templab < 0 || MAX_LABEL < templab) && templab != -1) {
										printf("incorrect argument in operator %s %d : %d\n",\
										tempcom , counter, templab);
										return 0;
									}
							
									if (templab > label_table_size) {
										int i = 0;
										label_table = (int*) realloc (label_table, templab * sizeof(int));
						
										for (i = label_table_size; i < templab - 1; ++i) {
											label_table[i] = -1;
										}
						
										label_table_size = templab;
									}
				
									buffer[counter] = label_table[templab - 1];
									++counter;
								}
								else {
									printf("incorrect argument in operator %s : %d\n",\
									tempcom, counter);
									return 0;
								}
								break;
							case 'b':
			
								if (tempcom[3] != '\0'){
									printf("incorrect operator %d : %s\n", counter, tempcom);
									return 0;
								}			
															
								buffer[counter] = JNB;
								++counter;
								templab = -1;
								if (fscanf(source, "%d", &templab)){ 
				
									if ((templab < 0 || MAX_LABEL < templab) && templab != -1) {
										printf("incorrect argument in operator %s %d : %d\n",\
										tempcom , counter, templab);
										return 0;
									}
							
									if (templab > label_table_size) {
										int i = 0;
										label_table = (int*) realloc (label_table, templab * sizeof(int));
						
										for (i = label_table_size; i < templab - 1; ++i) {
											label_table[i] = -1;
										}
						
										label_table_size = templab;
									}
				
									buffer[counter] = label_table[templab - 1];
									++counter;
								}
								else {
									printf("incorrect argument in operator %s : %d\n",\
									tempcom, counter);
									return 0;
								}
								break;
							case 'a':
			
								if (tempcom[3] != '\0'){
									printf("incorrect operator %d : %s\n", counter, tempcom);
									return 0;
								}			
															
								buffer[counter] = JNA;
								++counter;
								templab = -1;
								if (fscanf(source, "%d", &templab)){ 
				
									if ((templab < 0 || MAX_LABEL < templab) && templab != -1) {
										printf("incorrect argument in operator %s %d : %d\n",\
										tempcom , counter, templab);
										return 0;
									}
							
									if (templab > label_table_size) {
										int i = 0;
										label_table = (int*) realloc (label_table, templab * sizeof(int));
						
										for (i = label_table_size; i < templab - 1; ++i) {
											label_table[i] = -1;
										}
						
										label_table_size = templab;
									}
				
									buffer[counter] = label_table[templab - 1];
									++counter;
								}
								else {
									printf("incorrect argument in operator %s : %d\n",\
									tempcom, counter);
									return 0;
								}
								break;
						}
					break;
			}
			break;	
			case ':':
				if (sscanf(tempcom, ":%d", &templab)) {
					if (templab < 0 || MAX_LABEL < templab) {
						printf("incorrect operator %d : %s\n", counter, tempcom);
						return 0;
					}
					
				    if (templab > label_table_size) {
						int i = 0;
						label_table = (int*) realloc (label_table, templab * sizeof(int));
						
						for (i = label_table_size; i < templab - 1; ++i) {
							label_table[i] = -1;
						}
						
						label_table_size = templab;
					}
					
					label_table[templab - 1] = counter;
				}
				else {
					printf("incorrect label %s\n", tempcom);
					return 0;
				}
				break;
			case 'e':
				if (tempcom[1] != 'n' || tempcom[2] != 'd' || tempcom[3] != '\0'){
					printf("incorrect operator %d : %s\n", counter, tempcom);
					return 0;
				}
				
				buffer[counter] = END;
				return counter;
			case '.':
				tempint = getc(source);
				while ((tempint = getc(source)) != '\n'){
					push(st, tempint);
					++i;
				}
				
				while (i--){
					buffer[counter] = RPUSH;
					++counter;
					tempint = pop(st);
					buffer[counter] = tempint;
					++counter;
				}
				i = 0;
				break;
			case '/':
				while ((tempint = getc(source)) != '\n');
				break;
			default:
				printf("incorrect operator %d : %s\n", counter, tempcom);
				return 0;					
		}
	}
	buffer[counter] = END;
	++counter;
	compile_times++;
	if (compile_times == 2) {
		free(label_table);
	}
	return counter;
}
