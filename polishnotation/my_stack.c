#include <stdio.h>
#include "my_stack.h"
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
	
stack* stack_create(int Size){
	stack* new_stack = (stack*) calloc (1, sizeof(stack*));
	
	if (new_stack == NULL) {
		
		errno = ENOMEM;
		perror("Error in function stack_create: no memory for stack\n");
		abort();
		
	}
	
	(new_stack -> size) = Size;
	(new_stack -> data) = (double*) calloc (Size, sizeof(double*));
	
	if ((new_stack -> data) == NULL) {
		
		errno = ENOMEM;
		perror("Error in function stack_create: no memory for data of stack\n");
		abort();
	
	}
	
	(new_stack -> head) = -1;
	return new_stack;
}

double pop(stack* stk){
 
	if (stack_is_valide(stk)) {
	
		if (stack_is_empty(stk)) { 
		
			errno = EACCES;
			perror("ERROR: stack is empty\n");
			return -2;
		
		}
	
		(stk -> head)--;
		return ((stk -> data)[stk -> head + 1]);
	}
	return -1;
}

int push(stack* stk, double a){

	if (stack_is_valide(stk)) {
	
		if (stack_is_full(stk)){
		
			errno = EACCES;
			perror("ERROR: stack is full\n");
			return -2;
		
		}
	
		(stk -> data)[stk -> head + 1] = a;
		(stk -> head)++;
		return 0;
	}
	return -1;
}

int stack_is_full(stack* stk) {
	
	if (stack_is_valide(stk)) {
	
		if ((stk -> head + 1) == (stk -> size))
			return 1;
		
		return 0;
	}
	return -1;
}

int stack_is_empty(stack* stk) {
	
	stack_is_valide(stk);
	
	if ((stk -> head) == -1) 
		return 1;
	
	return 0;	
}

long stack_head(stack* stk){
	
	if (stack_is_valide(stk)){
		return (stk -> head);
	}
	return -99;
}

int stack_clear(stack* stk){
	
	if (stack_is_valide(stk)) {
	
		do	
			*((stk -> data) + (stk -> head)) = 0;
		while (--(stk -> head) + 1);
	
		return 0;
	}
	return -1;
}	
	
int stack_delete(stack* stk){
	
	if (stack_is_valide(stk)) {
	
		free(stk -> data);
		(stk -> data) = NULL;
		(stk -> size) = -666;
		(stk -> head) = -99;
		return 0;
	}
	return -1;
}	

double stack_peek(stack* stk){
	
	if (stack_is_valide(stk)) {
	
		return (stk -> data)[stk -> head];
	}
	return -1;
}

stack* stack_expansion(stack* stk, int new_size){
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
			
			return new_stack;
		}
		
		errno = ENOMEM;
		perror("Error in function stack_expansion: no memory for stack\n");
		return stk;		
	}
		
	return 0;		
}

int stack_is_valide(stack* stk){
	
	if (stk == NULL) {
		errno = EINVAL;
		perror("stack not exist\n");
		return 0;
	}

	if (!(stk -> size - 1 >= stk -> head && stk -> head >= -1)){
		errno = EINVAL;
		perror("invalid head value\n");
		return 0;
	}
	
	if ((stk -> data) == NULL) {
		
		errno = EINVAL;
		perror("invalide data adres\n");
		abort();
	}
	
	return 1;
}
