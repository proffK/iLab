#include "M_lex.h"
#include <stdlib.h>

char* cur_char;
token* cur_token;
char* lex_errno;
int cur_label;

const int TOKEN_BUFFER_SIZE = 1000;
const int FIRST_LABEL = 100;

token* lexical_analize(FILE* inp){

	char* buffer = NULL;

	token* token_buffer = NULL;
	buffer = create_buffer(inp);
	cur_char = buffer;

	token_buffer = (token*) calloc (TOKEN_BUFFER_SIZE, sizeof(token));
	cur_token = token_buffer;
	cur_label = FIRST_LABEL;
	
	while (*cur_char != '\0' && *cur_char != EOF\
		&& (cur_token - token_buffer < TOKEN_BUFFER_SIZE)) {
		
		while (*cur_char == ' ' || *cur_char == '\n' || *cur_char == '\t')
			++cur_char;
	
		switch (*cur_char) {

			case '0': case '1': case '2': case '3' :case '4':
			case '5': case '6': case '7': case '8' :case '9':

				cur_token -> type = NUMBER;

				if (!(sscanf(cur_char, "%lg", &(cur_token -> val))))					{

					lex_errno = cur_char;
					return NULL;

				}
				
				++cur_token;

				while (('0' <= *cur_char && *cur_char <= '9') 
					|| *cur_char == '.') ++cur_char;
				break;

			case '+':

				cur_token -> type = OPERATOR;
				cur_token -> val = '+';

				++cur_char;
				++cur_token;

				break;
			case '-':

				if (*(cur_char + 1) == '[' &&\
	                           (*(cur_char + 2) == 'I' || *(cur_char + 2) == 'C'\
				   || ('0'  <= *(cur_char + 2) &&  *(cur_char + 2)\
					   <= '9')) && *(cur_char + 3) == ']'\
				   && *(cur_char + 4) == '-'\
				   && *(cur_char + 5) == '>') {

					cur_token -> type = FUNCTION;
					
					cur_token -> val = *(cur_char + 2);

					cur_char += 6;

					++cur_token;

				}
				else {
				
				cur_token -> type = OPERATOR;
				cur_token -> val = '-';

				++cur_char;
				++cur_token;

				}

				break;
			case '*':

				cur_token -> type = OPERATOR;
				cur_token -> val = '*';

				++cur_char;
				++cur_token;

				break;
			case '/':

				cur_token -> type = OPERATOR;
				cur_token -> val = '/';

				++cur_char;
				++cur_token;

				break;
			case '}':

				cur_token -> type = END_BLOCK;

				++cur_char;
				++cur_token;

				break;
			case '{':	

				cur_token -> type = BEGIN_BLOCK;

				++cur_char;
				++cur_token;

				break;
			case '(': case ')': case '[': case ']':  

				cur_token -> type = BRACE;
				cur_token -> val = *cur_char;

				++cur_char;
				++cur_token;

				break;
			case '=':
				if (*(cur_char + 1) == '='){

					cur_token -> type = COMPARATION;
					cur_token -> val = '=';
					++cur_token;
					++cur_char;
					++cur_char;

				}
				else {
					--cur_token;
					cur_token -> type = ASSIGN;
					++cur_char;
					++cur_token;
				}
				break;
			case ';':

				cur_token -> type = END_STATEMENT;
				cur_token -> val = *cur_char;

				++cur_char;
				++cur_token;

				break;
			case 'O':

				if (*(cur_char + 1) == 'U' &&
				    *(cur_char + 2) == 'T'){
					
					cur_token -> type = STREAM;
					cur_token -> val = OUT_STREAM;

					cur_char += 3;
					++cur_token;

				}
				else {

					lex_errno = cur_char;
					return NULL;
				
				}

				break;
			case '<':
				if (*(cur_char + 1) == '?' && *(cur_char + 2) == '>'){

					cur_token -> type = WHILE;
					cur_token -> val = cur_label;	
					++cur_token;
					++cur_label;
					++cur_label;
					cur_char += 3;

				}
				else {

					cur_token -> type = COMPARATION;
					cur_token -> val = '<';
					++cur_token;
					++cur_char;
				
				}
				break;
			case '>':	

				cur_token -> type = COMPARATION;
				cur_token -> val = '>';
				++cur_token;
				++cur_char;
				break;
			case ':':
				if (*(cur_char + 1) == '>'){

					cur_token -> type = GOTO;
					++cur_token;
					cur_char += 2;

				}
				else {
					cur_token -> type = LABEL;
					++cur_token;
					++cur_char;
				}
				break;
			case 'I':
				if (*(cur_char + 1) == 'N'){

					cur_token -> type = STREAM;
					cur_token -> val = IN_STREAM;
					++cur_token;
					cur_char += 2;

				}
			case '!':
				if (*(cur_char + 1) == '?' && *(cur_char + 2) == '!'){

					cur_token -> type = IF;
					cur_token -> val = cur_label;
					++cur_label;
					++cur_token;
					cur_char += 3;

				}
				break;	
			default:

				if (*cur_char == '#'){

					++cur_char;

					while(*cur_char != '#' || *cur_char != '\0')\
				       	++cur_char;

				}


				if ('a' <= *cur_char && *cur_char <= 'z'){

					cur_token -> type = VAR;
					cur_token -> val = *cur_char;
					++cur_char;
					++cur_token;

				}

				else{

				lex_errno = cur_char;
				//return 0;

				}

		}		
	}
	
	cur_token -> type = END_PROGRAM;
	++cur_token;

	free(buffer);

	return token_buffer;
}
///#######################################################################

char* create_buffer(FILE* inp){

	int buffer_size = 0;
	char* buffer = NULL;

	fseek(inp, 0, SEEK_END);
	buffer_size = ftell(inp) + 1;
	rewind(inp);

	buffer = (char*) calloc (buffer_size, sizeof(char));
	fread(buffer, sizeof(char), buffer_size - 1, inp);
	
	return buffer;

}		

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
