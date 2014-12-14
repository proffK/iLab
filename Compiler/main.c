#include "M_syn.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE* in = NULL;
	FILE* out = NULL;
	token* tk = NULL;
	
	if (argc == 1) {
		printf("Empty input file  name\n");
		return 0;
	
	}
	if (argc == 2) {
		printf("Empty output file name\n");
		return 0;
	}
	
	in = fopen(argv[1], "r");
	out = fopen(argv[2],  "w");

	tk = lexical_analize(in);
	
	if (tk == NULL) {
		
		printf("\nLexical error\n");
		free(tk);
		fclose(in);
		fclose(out);
		return 0;
		
	}
	else {
		
		printf("Lexical analize complete.\n");
		
	}
	
	if (!(syntax_analize(tk, out))){
		
		printf("Syntax analize complete.\nParse tree build.\nCompilation complete.\n");
		free(tk);
		fclose(in);
		fclose(out);
		return 0;
		
	}
	else {
		
		printf("\nSyntax error\n");
		
	}
	
	free(tk);
	fclose(in);
	fclose(out);

	return 0;
}


