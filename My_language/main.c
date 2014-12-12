#include "M_syn.h"
#include <stdio.h>

int main(){
	FILE* in = 0;
	FILE* out = stdout;
	token* tk = NULL;
	
	in = fopen("inp.txt", "r");
	//out = fopen("test.txt",  "w");

	tk = lexical_analize(in);
	syntax_analize(tk, "test.txt");

	return 0;
}


