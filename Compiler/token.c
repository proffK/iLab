#include "token.h"

int token_dump(FILE* out, token* token){	
 	
	if (token -> type == NUMBER){
		fprintf(out, "NUMBER:%lg\n", token -> val);
	}
	if (token -> type == VAR){
		fprintf(out, "VAR:%lg\n", token -> val);
	}
	if (token -> type == BRACE){
		fprintf(out, "BRACE:%c\n", (int)  token -> val);
	}
	if (token -> type == ASSIGN){
		fprintf(out, "ASSIGN:%c\n", (int) token -> val);
	}
	if (token -> type == OPERATOR){
		fprintf(out, "OPERATOR:%c\n", (int) token -> val);
	}
	if (token -> type == END_STATEMENT){
		fprintf(out, "END_STATEMENT:%lg\n", token -> val);
	}
	if (token -> type == END_BLOCK){
		fprintf(out, "END_BLOCK:%lg\n", token -> val);
	}
	if (token -> type == BEGIN_BLOCK){
		fprintf(out, "BEGIN_BLOCK:%lg\n", token -> val);
	}
	if (token -> type == FUNCTION){
		fprintf(out, "FUNCTION:%lg\n", token -> val);
	}
	if (token -> type == STREAM){
		fprintf(out, "STREAM:%lg\n", token -> val);
	}
	if (token -> type == WHILE){
		fprintf(out, "WHILE:%lg\n", token -> val);
	}
	if (token -> type == IF){
		fprintf(out, "IF:%lg\n", token -> val);
	}
	if (token -> type == COMPARATION){
		fprintf(out, "COMPARATION:%c\n",(int) token -> val);
	}


	return 0;
}

token* token_new(void){

	token* new = (token*) calloc (1, sizeof(token));

	return  new;

}

int token_ctor(token* tok, int type, double val){

	if (tok == NULL) return -1;

	tok -> type = type;
	tok -> val = val;
	
	return 0;

}

int token_delete(token* tok){

	free(tok);

	return 0;

}

