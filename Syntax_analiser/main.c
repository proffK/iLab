#include <stdio.h>
#include "M_syn.h"

int main(){

	char inp[100] = "";

	gets(inp);

	printf("\n%d\n", get_G0(inp));

	return 0;

}


