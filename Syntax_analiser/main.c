#include <stdio.h>
#include <stdlib.h>
#include "M_syn.h"

int main(){
	FILE* source;
        FILE* temp_tree;
	char inp[100] = "";
	char temp[10] = "";

	node* tree = node_new();
	source = fopen("code.txt", "w");
	temp_tree = fopen("temp.txt", "w");
	gets(inp);

	tree = get_G0(inp);

	node_dump(tree, temp_tree);
	node_dtor(tree);
	fclose(temp_tree);

	temp_tree = fopen("temp.txt", "r");
	
	while (fscanf(temp_tree,"%s", temp) > 0){
		
		if (temp[0] == '+'){

			fprintf(source,"add\n");

		}

		else if (temp[0] == '*'){

			fprintf(source,"mul\n");

		}
		
		else if (temp[0] == '/'){

			fprintf(source,"div\n");

		}
		
		else if (temp[0] == '-'){

			fprintf(source,"sub\n");

		}
		else {

			fprintf(source,"push %s\n", temp);
		
		}
	}

	fprintf(source, "out\n");
	
	return 0;

}


