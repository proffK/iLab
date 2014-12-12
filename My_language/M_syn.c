#include "M_syn.h"
#include <stdlib.h>

const int MAX_LINE_SIZE = 1000;

FILE* out_asm;
token* syn_errno;
token* cur_tok;

int syntax_analize(token* source, char* out_file_name){

	char* temp = NULL;	
	FILE* std = NULL;
	node* parse_tree = NULL;
	cur_tok = source;
	out_asm = fopen(out_file_name, "w");

	temp = (char*) calloc (MAX_LINE_SIZE, sizeof(char));
	
	
	std = fopen("std.txt", "r");
	
	parse_tree = node_new();

	parse_tree = get_statement();

	block_semantic_analize(out_asm, parse_tree);
	//node_dump2(parse_tree, out_asm);

	if (cur_tok -> type != END_PROGRAM){

		syn_errno = cur_tok;
		return -1;

	}
	
	while (fgets(temp, MAX_LINE_SIZE, std) > 0) fprintf(out_asm, "%s", temp);

	return 0;

}

node* get_statement(void){
	
	node* nd = node_new();
	
	if (cur_tok -> type == BEGIN_BLOCK){
		
		nd -> data = cur_tok;
		++cur_tok;
		
		nd -> left = get_statement();
		
	}

	nd -> right = get_while();


	if (cur_tok -> type == END_STATEMENT){
		
		++cur_tok;
		nd -> left = get_statement();

	}
	
	if (cur_tok -> type == END_BLOCK){
		
		++cur_tok;
		//nd -> left = get_statement();

	}

	return nd;	
}

node* get_while(void){
	
	node* nd = node_new();

	if (cur_tok -> type == WHILE && (cur_tok + 1) -> type == BRACE) {
		
		nd -> data = cur_tok;
		cur_tok += 2;
		nd -> left = get_comp();

		if (cur_tok -> type == BRACE){
			
			++cur_tok;
			nd -> right = get_statement();
			
		}
		return nd;
	
	}
	node_dtor(nd);

	return get_if();
}

node* get_if(void){

	node* nd = node_new();

	if (cur_tok -> type == IF && (cur_tok + 1) -> type == BRACE) {
		
		nd -> data = cur_tok;
		cur_tok += 2;
		nd -> left = get_comp();

		if (cur_tok -> type == BRACE){

			++cur_tok;
			nd -> right = get_statement();
			
		}

		return nd;
	
	}
	node_dtor(nd);

	return get_function();
}

node* get_comp(void){

	node* nd = node_new();
	
	nd -> left = get_expression();

	nd -> data = cur_tok;
	++cur_tok;

	nd -> right = get_expression();

	return nd;

}

node* get_function(void){
	
	node* nd = node_new();

	if (cur_tok -> type == ASSIGN){
		
		node_dtor(nd);
		return get_asg();

	}
	
	nd -> left = get_expression();
	
	if (cur_tok -> type != FUNCTION) return nd;
	
	nd -> data = cur_tok;
	++cur_tok;
	
	nd -> right = get_expression();

	return nd;
	
}

node* get_asg(void){
	
	node* nd = node_new();
	
	nd -> data = cur_tok;
	++cur_tok;

	nd -> left = get_expression();

	return nd;

}

node* get_expression(void){

	return get_operator();

}

node* get_operator(void){

	return get_2pr();

}

node* get_2pr(void){

	node* nd = node_new();

	nd -> left = get_1pr();

	if (cur_tok -> type == OPERATOR &&\
	       (cur_tok -> val == '+' || cur_tok -> val == '-')){

		nd -> data = cur_tok;
		++cur_tok;
		nd -> right = get_2pr();

	}

	return nd;

}

node* get_1pr(void){

	node* nd = node_new();

	nd -> left = get_paren();

	if (cur_tok -> type == OPERATOR &&\
	       (cur_tok -> val == '*' || cur_tok -> val == '/')){

		nd -> data = cur_tok;
		++cur_tok;
		nd -> right = get_1pr();

	}

	return nd;

}

node* get_paren(void){

	node* nd = node_new();

	if (cur_tok -> type == BRACE && cur_tok -> val == '('){

		++cur_tok;
		nd = get_expression();

		if (cur_tok -> type == BRACE && cur_tok -> val == ')'){

			++cur_tok;
			return nd;
		}
	}

	node_dtor(nd);

	return get_term();

}

node* get_term(void){

	node* nd = node_new();

	if (cur_tok -> type == VAR || cur_tok -> type == NUMBER ||\
	    cur_tok -> type == STREAM){

	nd -> data = cur_tok;
	
	++cur_tok;
	}

	return nd;

}


	

