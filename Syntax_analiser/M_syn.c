#include "M_syn.h"
#include <stdio.h>

char* cur_c = NULL;
int syntax_errno = 0;

node* get_G0(char* input_string){
	node* val = node_new();
	cur_c = input_string;
	val = get_E();
	
	if (*cur_c == '\0' && syntax_errno == 0) return val;
	
	return val;
}	

node* get_E(){

	node* val = node_new();
	val = get_T();

	if (syntax_errno) return 0;
	
	if (*cur_c == '+' || *cur_c == '-'){
		
		node* operation = node_new();
		operation -> data = *cur_c;
		
		++cur_c;
		
		operation -> left = val;
		operation -> right = get_E();
		
		return operation;
	}

	return val;

}

node* get_T(){

	node* val = node_new();
	val = get_P();

	if (syntax_errno) return 0;
	
	if (*cur_c == '*' || *cur_c == '/'){
		
		node* operation = node_new();
		operation -> data = *cur_c;
		
		++cur_c;
		
		operation -> left = val;
		operation -> right = get_T();
		
		return operation;
	}

	return val;

}

node* get_P(){
	node* val = node_new();

	if (syntax_errno) return 0;

	if (*cur_c == '(') {
		
		++cur_c;
		val = get_E();

		if (*cur_c != ')') {
			syntax_errno = cur_c;
			return 0;
		}
		
		++cur_c;

		return val;

	}
	else {
		val = get_N();
		return val;
	}

	return 0;

}
	
node* get_N(){
	node* val = NULL;

	if (!('0' <=  *cur_c  &&  *cur_c <= '9')){
		
		syntax_errno = cur_c;
		return 0;

	}

	val = node_new();
	
	while ('0' <=  *cur_c  &&  *cur_c <= '9'){
		
		val -> data = (val -> data)*10 + *cur_c++ - '0';

	}
//	printf("\n  %d %s\n", val, cur_c);
	return val;

}


