#include <stdio.h>
#include "m_stack.h"
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

int POISON_HEAD = -99; 

int POISON_SIZE = -666; 

int stack_errno = 0;

enum err_constants {
STACK_OK = 0, /// Successful action.
ERR_MEM_STK = 1, /// There is no enough memory for stack.
ERR_MEM_DATA = 2,/// There is no enough memory for stack.
INV_HEAD = 3, /// Counter point at the segment is out of stack.
FULL = 4, /// Operation tryied to push in full stack
EMPTY = 5 /// Operation tryied to pop from empty stack
};

stack* stack_create(int Size){
	stack* new_stack = (stack*) calloc (1, sizeof(stack));
	
	if (new_stack == NULL) {
		
		errno = ENOMEM;
		abort();
		
	}
	
	(new_stack -> size) = Size;
	(new_stack -> data) = (double*) calloc (Size, sizeof(double));
	
	if ((new_stack -> data) == NULL) {
		
		errno = ENOMEM;
		abort();
	
	}
	
	(new_stack -> head) = -1;
	return new_stack;
}

double pop(stack* stk){
 
	if (stack_is_valide(stk)) {
	
		if (stack_is_empty(stk)) { 
		
			stack_errno = EMPTY;
			stack_dump(stk, stack_errno);
			errno = EACCES;
			return -2;
		
		}
	
		(stk -> head)--;
	if (stack_is_valide(stk)) return ((stk -> data)[stk -> head + 1]);
	}
	return -1;
}

int push(stack* stk, double a){

	if (stack_is_valide(stk)) {
	
		if (stack_is_full(stk)){
		
			errno = EACCES;
			stack_errno = FULL;
			stack_dump(stk, stack_errno);
			
			return -2;
		
		}
	
		(stk -> data)[stk -> head + 1] = a;
		(stk -> head)++;
		
	if (stack_is_valide(stk)) return 0;
	}
	return -1;
}

int stack_is_full(stack* stk) {
	
	if (stack_is_valide(stk)) {
	
		if ((stk -> head + 1) == (stk -> size))
			return 1;
		
	if (stack_is_valide(stk)) return 0;
	}
	return -1;
}

int stack_is_empty(stack* stk) {
	
	stack_is_valide(stk);
	
	if ((stk -> head) == -1) 
	
	if (stack_is_valide(stk)) return 1;
	
	return 0;	
}

long stack_head(stack* stk){
	
	if (stack_is_valide(stk)){
	if (stack_is_valide(stk)) return (stk -> head);
	}
	return POISON_HEAD;
}

int stack_clear(stack* stk){
	
	if (stack_is_valide(stk)) {
	
		do	
			*((stk -> data) + (stk -> head)) = 0;
		while (--(stk -> head) + 1);
	
	if (stack_is_valide(stk)) return 0;
	}
	return -1;
}	
	
int stack_delete(stack* stk){
	
	if (stack_is_valide(stk)) {
	
		free(stk -> data);
		(stk -> data) = NULL;
		(stk -> size) = POISON_HEAD;
		(stk -> head) = POISON_SIZE;
		
		return 0;
	}
	return -1;
}	

double stack_peek(stack* stk){
	
	if (stack_is_valide(stk)) {
	
		if (stack_is_valide(stk)) return (stk -> data)[stk -> head];
	}
	return -1;
}

stack* stack_resize(stack* stk, int new_size){
	double* buf = NULL;
	int i = 0;	
	stack* new_stack = stack_create(new_size);
	buf = (double*) calloc (stk -> size, sizeof(double*));
		
	if (stack_is_valide(stk)) {
		if (buf) { 
		
			for (i = 0; i <= stk -> head; ++i) {
				buf[i] = stk -> data[i];
			}
			
			stack_delete(stk);
			
			i--;
			
			new_stack -> head = i;
 
			if (new_stack -> head + 1) do new_stack -> data[i] = buf[i]; while (--i + 1);
			
			free(buf);
			buf = NULL;
			
			if (stack_is_valide(new_stack)) return new_stack;
		}
		
		errno = ENOMEM;
		return stk;		
	}
		
	return 0;		
}

int stack_is_valide(stack* stk){
	
	if (stk == NULL) {
		errno = EINVAL;
		stack_errno = ERR_MEM_STK;
		stack_dump(stk, stack_errno);
		return 0;
	}

	if (!(stk -> size - 1 >= stk -> head && stk -> head >= -1)){
		errno = EINVAL;
		stack_errno = INV_HEAD;
		stack_dump(stk, stack_errno);
		return 0;
	}
	
	if ((stk -> data) == NULL) {
		
		errno = EINVAL;
		stack_errno = ERR_MEM_DATA;
		stack_dump(stk, stack_errno);
		abort();
	}
	
	return 1;
}


int stack_dump(stack* stk, int stack_err){
	FILE* log = fopen("stack_log.txt", "w");
	switch (stack_err){
		case ERR_MEM_STK:
			
			fprintf(log, "Stack not exist in memory");
			break;
		case ERR_MEM_DATA:
			fprintf(log, "Stack hasn't data in memory");
			break;
		case INV_HEAD:
			fprintf(log, "stack head = %d", stk -> head);
			fprintf(log, "Stack has invalid head value");
			break;
		case FULL:
			fprintf(log, "stack head = %d\nstack size = %d\n", stk -> head, stk -> size);
			while(stk -> head != -1){
				fprintf(log, "%lg\n", pop(stk));
			}
			fprintf(log, "PUSH: Operation tryied to push in full stack");
			break;
		case EMPTY:
			fprintf(log, "POP: Operation tryied to pop from empty stack");
			break;
		default:
			break;
	}
	fclose(log);
	return 0;
}
