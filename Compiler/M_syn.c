#include "M_syn.h"
#include <stdlib.h>

const int MAX_LINE_SIZE = 1000;

FILE* out_asm;
token* syn_errno;
token* cur_tok;

int syntax_analize(token* source, FILE* out_file){

	char* temp = NULL;	
	FILE* std = NULL;
	FILE* syntax_log = stdout;
	node* parse_tree = NULL;
	cur_tok = source;
	out_asm = out_file;

	temp = (char*) calloc (MAX_LINE_SIZE, sizeof(char));
	
	
	std = fopen("std.txt", "r");
	
	parse_tree = node_new();

	parse_tree = get_program();

	//block_semantic_analize(out_asm, parse_tree);
	
	//tex_dump(parse_tree, stdout);

	if (cur_tok -> type != END_PROGRAM){

		syn_errno = cur_tok;
		token_dump(syntax_log, cur_tok);
		fclose(std);
		return -1;

	}
	
	while (fgets(temp, MAX_LINE_SIZE, std) > 0) fprintf(out_asm, "%s", temp);
	
	free(temp);
	fclose(std);
	
	return 0;

}

node* get_program(void){
	
	node* nd = node_new();
	
	if (cur_tok -> type == BEGIN_BLOCK){
		
		nd -> data = cur_tok;
		++cur_tok;
		
	}
	
	nd -> left = get_statement();
	
	if (cur_tok -> type == END_BLOCK){
		
		++cur_tok;
		
	}
	
	return nd;	
}

node* get_statement(void){
	
	node* nd = node_new();
	
	if (cur_tok -> type == BEGIN_BLOCK){
		
		nd -> right = get_program();

		return nd;
		
	}
	
	nd -> right = get_while();
	
	if (cur_tok -> type == END_STATEMENT){
		
		++cur_tok;

	}
	
	if (cur_tok -> type != END_BLOCK){
	
		nd -> left = get_statement();
		
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
			token_dump(stdout, cur_tok);
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
	
	//tex_dump(nd -> left , stdout);
	
	if (cur_tok -> type != FUNCTION) return nd;
	
	nd -> data = cur_tok;
	++cur_tok;
	
	nd -> right = get_asg();

	return nd;
	
}

node* get_asg(void){
	
	node* nd = node_new();
	
	nd -> data = cur_tok;
	if (nd -> data -> type == VAR){
		
		nd -> data -> type = ASSIGN;
		
	}
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
	else {
		
		return nd -> left;
	
	}

	return nd;

}

node* get_1pr(void){

	node* nd = node_new();

	nd -> left = get_0pr();
	


	if (cur_tok -> type == OPERATOR &&\
	       (cur_tok -> val == '*' || cur_tok -> val == '/')){

		nd -> data = cur_tok;
		++cur_tok;
		nd -> right = get_1pr();

	}
	else {
		
		return nd -> left;
		
	}

	return nd;

}

node* get_0pr(void){
	
	node* nd = node_new();

	if (cur_tok -> type == DIFF_OPER) {

		node_dtor(nd);
		return get_diff();

	}

	nd -> left = get_paren();

	if (cur_tok -> type == OPERATOR &&\
	       (cur_tok -> val == 's' || cur_tok -> val == 'c'\
	        || cur_tok -> val == '^')){

		nd -> data = cur_tok;
		++cur_tok;
		nd -> right = get_0pr();

	}
	else {
		
		return nd -> left;
		
	}

	return nd;

}

node* get_diff(void){
	
	FILE* out = 0;
	int temp = 0;
	node* df = NULL;
	node* nd = node_new();
	
	temp = cur_tok -> val;
	++cur_tok;

	nd = get_paren();
	
	out = fopen("diff.tex", "w");
	
	fprintf(out, " \\documentclass[a4paper,20pt]{article} \n\
	\n\
	\\usepackage[english,russian]{babel}\n\
	\\usepackage[utf8]{inputenc}\n\
	\n\
	\\title{Отчет о взятии производной}\n\
	\\author{Клим Киреев, 411 группа, ФРТК}\n\
	\\date{}\n\
	\n\
	\\begin{document}\n\
	\\maketitle\n\
	\\newpage\n");
	
	df = diff_tree(nd, temp, out);
	
	fprintf(out,"\n\\end{document}");
	
	return df;
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
	    cur_tok -> type == STREAM || cur_tok -> type == STRING_CONSTANT){

	nd -> data = cur_tok;
	
	++cur_tok;
	}

	return nd;

}


	

