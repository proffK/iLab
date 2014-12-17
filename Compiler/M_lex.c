#include "M_lex.h"
#include <stdlib.h>

char* cur_char;
token* cur_token;
char* lex_errno;
int cur_label;

const int TOKEN_BUFFER_SIZE = 1000;
const int FIRST_LABEL = 500;

token* lexical_analize(FILE* inp){

	char* buffer = NULL;
	int temp = 0;
	FILE* lexical_log = stdout;

	token* token_buffer = NULL;
	buffer = create_buffer(inp);
	cur_char = buffer;

	token_buffer = (token*) calloc (TOKEN_BUFFER_SIZE, sizeof(token));
	cur_token = token_buffer;
	cur_label = FIRST_LABEL;
	
	while (*cur_char != '\0' && *cur_char != EOF\
		&& (cur_token - token_buffer < TOKEN_BUFFER_SIZE)) {
			
		space_checker();
	
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

				if (*(cur_char + 1) != '\0' && *(cur_char + 1) == '[' &&\
				    *(cur_char + 2) != '\0' &&\
	    			    *(cur_char + 3) != '\0' && *(cur_char + 3) == ']' &&\
				    *(cur_char + 4) != '\0' && *(cur_char + 4) == '-' &&\
				    *(cur_char + 5) != '\0' && *(cur_char + 5) == '>'){

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
			case '^':

				cur_token -> type = OPERATOR;
				cur_token -> val = '^';

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
				if (*cur_char == '(' &&\
				    *(cur_char + 1) != '\0' && *(cur_char + 1) == 'd' &&\
			            *(cur_char + 2) != '\0' && *(cur_char + 2) == '/' &&\
				    *(cur_char + 3) != '\0' && *(cur_char + 3) == 'd' &&\
				    *(cur_char + 4) != '\0' &&\
				    *(cur_char + 5) != '\0' && *(cur_char + 5) == ')'){

					cur_token -> type = DIFF_OPER;
					cur_token -> val = *(cur_char + 4);
					++cur_token;
					cur_char += 6;

				}
				
				else {
					cur_token -> type = BRACE;
					cur_token -> val = *cur_char;

					++cur_char;
					++cur_token;
				}

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
			case '\'':
				
				if (*(cur_char + 2) == '\''){
				
					cur_token -> type = NUMBER;
					cur_token -> val = *cur_char;

					cur_char += 3;
					++cur_token;
				}
				
				break;
			case '\"':
				
				++cur_char;
				
				while (*cur_char != '\0' &&  *cur_char != '\"'){
					
					++temp;
					++cur_char;
					
				}
				
				--cur_char;
				
				while (*cur_char != '\"'){
					
					cur_token -> type = NUMBER;
					cur_token -> val = *cur_char;
					++cur_token;
					
					cur_token -> type = END_STATEMENT;
					++cur_token;
					
					--cur_char;	
					
				}
				
				++cur_char;
				
				while (*cur_char != '\0' &&  *cur_char != '\"'){
					
					++cur_char;
					
				}
				
				++cur_char;
				
				cur_token -> type = STRING_CONSTANT;
				cur_token -> val = temp;
				++cur_token;
				
				cur_token -> type = END_STATEMENT;
				++cur_token;
				
				temp = 0;
				
				break;
			case 'O':

				if (*(cur_char + 1) != '\0' && *(cur_char + 1) == 'U' &&\
				    *(cur_char + 2) != '\0' && *(cur_char + 2) == 'T'){
					
					cur_token -> type = STREAM;
					cur_token -> val = OUT_STREAM;

					cur_char += 3;
					++cur_token;

				}
				else {
					
					cur_token -> type = VAR;
					cur_token -> val = *cur_char;
					++cur_char;
					++cur_token;
					
				}
				break;
			case '<':
				if (*(cur_char + 1) != '\0' && *(cur_char + 1) == '?' &&\
				    *(cur_char + 2) != '\0' && *(cur_char + 2) == '>'){

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
			case 's':
				if (*(cur_char + 1) != '\0' && *(cur_char + 1) == 'i' &&\
				    *(cur_char + 2) != '\0' && *(cur_char + 2) == 'n'){
					
					cur_token -> type = OPERATOR;
					cur_token -> val = 's';

					cur_char += 3;
					++cur_token;
				}
				else {
					
					cur_token -> type = VAR;
					cur_token -> val = *cur_char;
					++cur_char;
					++cur_token;
					
				}
				break;
			case 'c':
				if (*(cur_char + 1) != '\0' && *(cur_char + 1) == 'o' &&\
				    *(cur_char + 2) != '\0' && *(cur_char + 2) == 's'){
					
					cur_token -> type = OPERATOR;
					cur_token -> val = 'c';

					cur_char += 3;
					++cur_token;
					
				}
				else {
					
					cur_token -> type = VAR;
					cur_token -> val = *cur_char;
					++cur_char;
					++cur_token;
					
				}
				break;				
			case '>':	

				cur_token -> type = COMPARATION;
				cur_token -> val = '>';
				++cur_token;
				++cur_char;
				break;
			case ':':
				if (*(cur_char + 1) != '\0' && *(cur_char + 1) == '>'){

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
				else {
					
					cur_token -> type = VAR;
					cur_token -> val = *cur_char;
					++cur_char;
					++cur_token;
					
				}
				break;
			case '#':
				
				++cur_char;
				
				while (*cur_char != '#' && *cur_char != '\0') ++cur_char;
				
				if (*cur_char != '\0') ++cur_char;

			break;
			case '!':
				if (*(cur_char + 1) != '\0' && *(cur_char + 1) == '?' &&\
				    *(cur_char + 1) != '\0' && *(cur_char + 2) == '!'){

					cur_token -> type = IF;
					cur_token -> val = cur_label;
					++cur_label;
					++cur_token;
					cur_char += 3;

				}
				else {

				lex_errno = cur_char;
				return NULL;
				
				}
				break;	
			default:
				
				space_checker();
				
				if ('a' <= *cur_char && *cur_char <= 'z'){

					cur_token -> type = VAR;
					cur_token -> val = *cur_char;
					++cur_char;
					++cur_token;

				}
				
				else if (*cur_char != '\0'){

				lex_errno = cur_char;
				fprintf(lexical_log, "%s", cur_char);
				return NULL;
				
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

void space_checker(void){
	
	while (*cur_char == ' ' || *cur_char == '\n' || *cur_char == '\t')
			++cur_char;
			
}
