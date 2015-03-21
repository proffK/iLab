#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <limits.h>
#include "stk_processors.h"
#include "commands.h"

int proc_errno = 0;

enum proc_err{
	PROC_OK = 0,
	INV_REGS_VAL = 1,
	INV_STACK = 2,
	INV_DATA = 3,
	NO_PROC_MEM = 4,
	INV_COUNT_VAL = 5,
	ARIF_ERR = 6
};


processor* processor_create(int stack_size, int n_reg, long buffer_size){
	processor* new_proc = (processor*) calloc (1 , sizeof(processor));
	
	if (new_proc == NULL) {
		
		errno = ENOMEM;
		abort();
		
	}
	
	new_proc -> data_size = buffer_size;
	
	new_proc -> data = (double*) calloc (buffer_size, sizeof(double));
	
	if (new_proc -> data == NULL) {
		
		errno = ENOMEM;
		abort();
		
	}
	
	new_proc -> stk = stack_create(stack_size);
	new_proc -> regs = (double*) calloc (n_reg, sizeof(double));
	new_proc -> n_reg = n_reg;
	
	return new_proc;
}

int processor_delete(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		proc -> data_size = -1;
		free(proc -> data);
		proc -> data = NULL;
		free(proc -> regs);
		proc -> regs = NULL;
		stack_delete(proc -> stk);
		proc -> n_reg = -1;
		free(proc);
		
	return 0;
	
	}
	
	return -1;
}

int P_add(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		double a = 0, b = 0;
		a = pop(proc -> stk);
		b = pop(proc -> stk);
		push(proc -> stk, a + b);
	
		if (processor_is_valide(proc)) return 0;
	}	
	
	return -1;
}

int P_sub(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		double a = 0, b = 0;
		a = pop(proc -> stk);
		b = pop(proc -> stk);
		push(proc -> stk, b - a);
	
		if (processor_is_valide(proc)) return 0;
	}	
	
	return -1;
}

int P_mul(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		double a = 0, b = 0;
		a = pop(proc -> stk);
		b = pop(proc -> stk);
		push(proc -> stk, a * b);
	
		if (processor_is_valide(proc)) return 0;
	}	
	
	return -1;
}

int P_sin(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		double a = 0;
		a = pop(proc -> stk);
		push(proc -> stk, sin(a));
	
		if (processor_is_valide(proc)) return 0;
	}	
	
	return -1;
}

int P_cos(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		double a = 0;
		a = pop(proc -> stk);
		push(proc -> stk, cos(a));
	
		if (processor_is_valide(proc)) return 0;
	}	
	
	return -1;
}

int P_pow(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		double a = 0, b = 0;
		a = pop(proc -> stk);
		b = pop(proc -> stk);
		
		if (a < 0 && b < 0){
			proc_errno = ARIF_ERR;
			processor_dump(ARIF_ERR, proc);
			return -1;
		}
		push(proc -> stk,pow(b, a));
	
		if (processor_is_valide(proc)) return 0;
	}	
	
	return -1;
}

int P_div(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		double a = 0, b = 0;
		a = pop(proc -> stk);
		b = pop(proc -> stk);
		
		if (a == 0){
			proc_errno = ARIF_ERR;
			processor_dump(ARIF_ERR, proc);
			return -1;
		}
		push(proc -> stk, b / a);
	
		if (processor_is_valide(proc)) return 0;
	}	
	
	return -1;
}

int P_sqrt(processor* proc){
	
	if (processor_is_valide(proc)) {
		
		double a = 0;
		a = pop(proc -> stk);
		
		if (a < 0){
			proc_errno = ARIF_ERR;
			processor_dump(ARIF_ERR, proc);
			return -1;
		}
		push(proc -> stk, sqrt(a));
	
		if (processor_is_valide(proc)) return 0;
	}	
	
	return -1;
}



int P_pop(processor* proc, int reg){
	
	if (processor_is_valide(proc)) {	
	
		*(proc -> regs + reg) = pop(proc -> stk);
	
		if (processor_is_valide(proc)) return 0;
		
	}
	
	return -1;
}

int P_push(processor* proc, int reg) {
	
	if (processor_is_valide(proc)) {
	
		push(proc -> stk, *(proc -> regs + reg));
		
		if (processor_is_valide(proc)) return 0;
		
	}
	
	return -1;
}

int P_rpush(processor* proc, double val) {
	
	if (processor_is_valide(proc)) {
	
		push(proc -> stk, val);
		
		if (processor_is_valide(proc)) return 0;
		
	}
	
	return -1;
}

int processor_is_valide(processor* proc){
	
	if (proc == NULL) {
		
		errno = ENOMEM;
		proc_errno = NO_PROC_MEM;
		processor_dump(proc_errno, proc);
		abort();
		
	}
	
	if (!(stack_is_valide(proc -> stk))) {
		
		proc_errno = INV_STACK;
		processor_dump(proc_errno, proc);
		return 0;
	
	}
	
	if (proc -> data == NULL) {
		
		errno = ENOMEM;
		proc_errno = INV_DATA;
		processor_dump(proc_errno, proc);
		return 0;
		
	}
	
	if (proc -> regs == NULL) {
		
		errno = ENOMEM;
		proc_errno = INV_REGS_VAL;
		processor_dump(proc_errno, proc);
		return 0;
		
	}
	
	return 1;
}

int processor_dump(int proc_er, processor* proc){
	FILE* log = fopen("proc_log.txt", "w");
		
	switch (proc_er) {
		case INV_REGS_VAL:
			fprintf(log, "Invalid registor array");
			fprintf(log, "\nprocessor pointer = %p \nstack pointer = %p data pointer = %p\
			\nprocessor registors pointer = %p\n processor counter = %d", proc, proc -> stk, \
			proc -> data, proc -> regs, proc -> counter);
			break;
		case INV_STACK:
			fprintf(log, "Stack's error. More information in stack_log.txt");
			fprintf(log, "\nprocessor pointer = %p \nstack pointer = %p data pointer = %p\
			\nprocessor registors pointer = %p\n processor counter = %d", proc, proc -> stk, \
			proc -> data, proc -> regs, proc -> counter);
			break;
		case INV_DATA:
			fprintf(log, "Processor's data buffer not exist");
			fprintf(log, "\nprocessor pointer = %p \nstack pointer = %p data pointer = %p\
			\nprocessor registors pointer = %p\n processor counter = %d", proc, proc -> stk, \
			proc -> data, proc -> regs, proc -> counter);
			break;
		case NO_PROC_MEM:
			fprintf(log, "Processor not exist(NO MEMORY)");
			break;
		case ARIF_ERR:
			fprintf(log, "afirmetical error");
			fprintf(log, "\nprocessor pointer = %p \nstack pointer = %p data pointer = %p\
			\nprocessor registors pointer = %p\n processor counter = %d", proc, proc -> stk, \
			proc -> data, proc -> regs, proc -> counter);
			break;
		default:
			break;
	}
	
	fclose(log);
	return 0;
}

int processor_flash(processor* proc, double* firmware, int firmware_size){
	int i = 0;
	if (processor_is_valide(proc)) {
		if (proc -> data_size > firmware_size) {
			for (i = 0; i < firmware_size; ++i){
				proc -> data[i] = firmware[i];
				//printf("\n%lg\n", proc -> data[i]);
			}
		}
	}
	return 0;
	
}

int processor_start(processor* proc, FILE* input_stream, FILE* output_stream){
	long watch_dog = LONG_MAX;
	if (processor_is_valide(proc)) {
		if (proc -> counter != 0) return -1;
		while (proc -> data[proc -> counter] != -1 || watch_dog--){
			//printf(" ");
			//printf("....%lg\n", proc -> data[proc -> counter]);
			if (processor_is_valide(proc)) {
				double temp1 = 0, temp2 = 0;
				char tempc = '\0';
				switch ((int) proc -> data[proc -> counter]){
					case RPUSH:
						++proc -> counter;
						P_rpush(proc, proc -> data[proc -> counter]);
						++proc -> counter;
						break;
					case PUSH:
						++proc -> counter;
						P_push(proc, proc -> data[proc -> counter]);
						++proc -> counter;
						break;
					case POP:
						++proc -> counter;
						P_pop(proc, proc -> data[proc -> counter]);
						++proc -> counter;
						break;
					case ADD:
						P_add(proc);
						++proc -> counter;
						break;
					case SUB:
						P_sub(proc);
						++proc -> counter;
						break;
					case MUL:
						P_mul(proc);
						++proc -> counter;
						break;
					case DIV: 
						P_div(proc);
						++proc -> counter;
						break;
					case OUT:
						++proc -> counter;
						fprintf(output_stream, "%lg", pop(proc -> stk));
						break; 
					case CALL:
						++proc -> counter;
						++proc -> counter;
						push(proc -> stk, proc -> counter);
						--proc -> counter;
						proc -> counter = proc -> data[proc -> counter];
						break;
					case RET:
						proc -> counter = pop(proc -> stk);
						break;
					case JE:
						temp1 = pop(proc -> stk);
						temp2 = pop(proc -> stk);
						if (temp1 == temp2) {
							++proc -> counter;
							proc -> counter = proc -> data[proc -> counter];
						}
						else proc -> counter += 2;
						break;
					case JNE: 
						temp1 = pop(proc -> stk);
						temp2 = pop(proc -> stk);
						if (temp1 != temp2) {
							++proc -> counter;
							proc -> counter = proc -> data[proc -> counter];
						}
						else proc -> counter += 2;
						break;
					case JB: 
						temp1 = pop(proc -> stk);
						temp2 = pop(proc -> stk);
						if (temp1 < temp2) {
							++proc -> counter;
							proc -> counter = proc -> data[proc -> counter];
						}
						else proc -> counter += 2;
						break;
					case JNB:
						temp1 = pop(proc -> stk);
						temp2 = pop(proc -> stk);
						if (temp1 >= temp2) {
							++proc -> counter;
							proc -> counter = proc -> data[proc -> counter];
						}
						else proc -> counter += 2;
						break;
					case JA: 
						temp1 = pop(proc -> stk);
						temp2 = pop(proc -> stk);
						if (temp1 > temp2) {
							++proc -> counter;
							proc -> counter = proc -> data[proc -> counter];
						}
						else proc -> counter += 2;
						break;
					case JNA: 
						temp1 = pop(proc -> stk);
						temp2 = pop(proc -> stk);
						if (temp1 <= temp2) {
							++proc -> counter;
							proc -> counter = proc -> data[proc -> counter];
						}
						else proc -> counter += 2;
						break;
					case INP:
						++proc -> counter;
						fscanf(input_stream, "%lg", &temp1);
						P_rpush(proc, temp1);
						break;
					case OUTC: 
						++proc -> counter;
						fprintf(output_stream, "%c", (char) pop(proc -> stk));
						break; 
					case INPC: 
						tempc = getc(input_stream);
						P_rpush(proc, tempc);
						++proc -> counter;
						break;
					case SQRT:
						P_sqrt(proc);
						++proc -> counter;
						break;
					case JP:
						++proc -> counter;
						proc -> counter = proc -> data[proc -> counter];
						break;
					case SIN:
						P_sin(proc);
						++proc -> counter;
						break;
					case COS:
						P_cos(proc);
						++proc -> counter;
						break;
					case POW:
						P_pow(proc);
						++proc -> counter;
						break;
					default:
						return -1;
					
				}
			}
		}
	}
	
	return 0;
}
	
