#include "M_syn.h"
#include <stdio.h>

char* cur_c = NULL;
int syntax_errno = 0;

int get_G0(char* input_string){
	int val = 0;
	cur_c = input_string;
	val = get_E();
	
	if (*cur_c == '\0' && syntax_errno == 0) return val;
	
	return val;
}	

int get_E(){
	int val = 0;

	val = get_T();

		//printf("%s\n", cur_c);

	while (*cur_c == '+' || *cur_c == '-'){
		char op = *cur_c;

		++cur_c;

		if (syntax_errno) return 0;

		if (op == '+')
			val += get_T();
		if (op == '-')
			val -= get_T();

	}

	return val;

}


int get_T(){
	int val = 0;

	val = get_P();

	while (*cur_c == '*' || *cur_c == '/'){
		char op = *cur_c;
		
		++cur_c;

		if (syntax_errno) return 0;

		if (op == '*')
			val *= get_P();
		if (op == '/')
			val /= get_P();

	}

	return val;

}

int get_P(){
	int val = 0;

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
	
int get_N(){
	int val = 0;

	if (!('0' <=  *cur_c  &&  *cur_c <= '9')){
		
		syntax_errno = cur_c;
		return 0;

	}
	
	while ('0' <=  *cur_c  &&  *cur_c <= '9'){
		
		val = val*10 + *cur_c++ - '0';

	}
//	printf("\n  %d %s\n", val, cur_c);
	return val;

}


