#include "M_syn.h"
#include <stdio.h>

int main(int argc, char* argv[]){
	FILE* in = 0;
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
//	out = fopen(argv[2],  "w");

	tk = lexical_analize(in);
	syntax_analize(tk, argv[2]);

	return 0;
}


