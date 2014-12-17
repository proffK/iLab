
#include "M_diff.h"

node* diff_tree(node* tree, int var, FILE* out){
	static node* diffed_tree = 0;
	node* nd = node_new();

	if(diffed_tree == 0) diffed_tree = nd;

	if (tree == NULL) {
		
		node_dtor(nd);
		return NULL;

	}
	


	if (tree -> data -> type == OPERATOR){

		if (tree -> data -> val == '+' || tree -> data -> val == '-'){

			nd -> data = token_new();
			token_ctor(nd -> data, OPERATOR, tree -> data -> val);
			
			if (tree -> left != NULL && tree -> left -> data != NULL){
				
				nd -> left = node_cpy(tree -> left);
				nd -> left -> data -> diff_flag = 1;
				
			}
			
			if (tree -> right != NULL && tree -> right -> data != NULL){
				
				nd -> right = node_cpy(tree -> right);
				nd -> right -> data -> diff_flag = 1;
				
			}
			
			fprintf(out, "Пользуясь правилом производной суммы:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");
			
			//node_dtor(nd -> left);
			//node_dtor(nd -> right);
			
			nd -> left = diff_tree(tree -> left, var, out);
			nd -> right = diff_tree(tree -> right, var, out);
			
		}

	    else if (tree -> data -> val == '*'){

			

			node_ctor(nd , OPERATOR, '+');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, '*');
			
			if (tree -> left != NULL){
				
				nd -> left -> left = node_cpy(tree -> left);
				nd -> left -> left -> data -> diff_flag = 1;
				
			}
			
			if (tree -> left  != NULL){
				
				nd -> left -> right = node_cpy(tree -> right);
				
			}
			
			
			fprintf(out, "Пользуясь правилом производной произведения:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");

			nd -> left -> left = diff_tree(tree -> left, var, out);
		    nd -> left -> right = node_cpy(tree -> right);	     
			
			nd -> right = node_new();
			node_ctor(nd -> right, OPERATOR, '*');
			
			if (tree -> right != NULL){
				
				nd -> right -> left = node_cpy(tree -> left);
				
			}
			
			if (tree -> right != NULL){
				
				nd -> right -> right = node_cpy(tree -> right);
				nd -> right -> right -> data -> diff_flag = 1;
				
			}

			fprintf(out, "Пользуясь правилом производной произведения:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");

			nd -> right -> left = node_cpy(tree -> left);
		    nd -> right -> right = diff_tree(tree -> right, var, out);

		}

		else if (tree -> data -> val == '/'){

			node_ctor(nd, OPERATOR, '/');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, '+');

			nd -> left -> left = node_new();
			node_ctor(nd -> left -> left, OPERATOR, '*');

			nd -> left -> left -> left = diff_tree(tree -> left, var,\
				       				out);
			nd -> left -> left -> right = node_cpy(tree -> right);

			nd -> left -> right = node_new();
			node_ctor(nd -> left -> right, OPERATOR, '*');

			nd -> left -> right -> left = node_cpy(tree -> left);
			nd -> left -> right -> right = diff_tree(tree -> right,\
				       				  var, out);

			nd -> right = node_new();
			node_ctor(nd -> right, OPERATOR, '^');

			nd -> right -> right = node_new();
			node_ctor(nd -> right -> right, NUMBER, 2);
			nd -> right -> left = node_cpy(tree -> right);

		}

		else if (tree -> data -> val == '^'){

			node_ctor(nd, OPERATOR, '*');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, '*');

			nd -> left -> left = node_new();
			node_ctor(nd -> left -> left, OPERATOR, '^');
			
			nd -> left -> left -> left = node_cpy(tree -> left);
			nd -> left -> left -> right = node_new();
			node_ctor(nd -> left -> left -> right, NUMBER,\
					  tree -> right -> data -> val - 1);

			nd -> left -> right = node_new();
			nd -> left -> right = diff_tree(tree -> left, var, out);

			nd -> right = node_new();
			node_ctor(nd -> right, NUMBER,\
				  tree -> right -> data -> val);

		}

		else if (tree -> data -> val == 's'){

			node_ctor(nd, OPERATOR, '*');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, 'c');

			//printf("...%p\n" , tree -> right -> data);

			nd -> left -> left = node_cpy(tree -> right);

			nd -> right = diff_tree(tree -> right, var, out);

		}

		else if (tree -> data -> val == 'c'){

			node_ctor(nd, OPERATOR, '*');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, '*');

			nd -> left -> left = node_new();
			node_ctor(nd -> left -> left, NUMBER, -1);

			nd -> left -> right = node_new();
			node_ctor(nd -> left -> right, OPERATOR, 'c');
			nd -> left -> right -> left = node_cpy(tree -> right);

			nd -> right = diff_tree(tree -> right, var, out);

		}

		else {

			return NULL;
		
		}

	}

	
	else if (tree -> data -> type == NUMBER){
	

		node_ctor(nd, NUMBER, 0);

	}

	else if (tree -> data -> type == VAR){

		if (tree -> data -> val == var){
			
			node_ctor(nd, NUMBER, 1);

		}
		else {
			
			node_ctor(nd, NUMBER, 0);

		}

	}

	else {

		return NULL;

	}
	
	return nd;

}

int tex_dump(node* tree, FILE* out){
	
	if (!(node_ok(tree))){
		
		fprintf(out, "Incorrect tree\n");
		return -1;
		
	}
		
	if (tree -> data != NULL) fprintf(out, "{");
	
	if (tree -> data != NULL && tree -> data -> diff_flag == 1){
	
			fprintf(out, "(");
	
	}
	
	if (tree -> data != NULL && tree -> data -> type == OPERATOR) {
		
		if (tree -> data -> val == '-' ||\
		    tree -> data -> val == '+' ){
			
			fprintf(out, "(");
			
		}
	}
	
	if (tree -> data != NULL && tree -> data -> type == OPERATOR) {
		
		if (tree -> data -> val == '/'){
			
			fprintf(out, "\\frac");
			
		}
		
		if (tree -> data -> val == 's'){
			
			fprintf(out, "sin(");
			
		}
		
		if (tree -> data -> val == 'c'){
			
			fprintf(out, "cos(");
			
		}
	}

	if (tree -> left != NULL){ 
		
		tex_dump(tree -> left, out);
		
	}
	
	if (tree -> data != NULL && tree -> data -> type == OPERATOR) {
		
		if (tree -> data -> val == '*' ||\
		    tree -> data -> val == '-' ||\
		    tree -> data -> val == '+' ||\
		    tree -> data -> val == '^' ){
			
			fprintf(out, "%c", (int) tree -> data -> val);
			
		}
	}

	if (tree -> right != NULL){ 
		
		tex_dump(tree -> right, out);
		
	}
	
	if (tree -> data != NULL && tree -> data -> type == OPERATOR) {
		
		if (tree -> data -> val == '-' ||\
		    tree -> data -> val == '+' ){
			
			fprintf(out, ")");
			
		}
	}
	
	if (tree -> data != NULL){

		switch (tree -> data -> type) {
			
			case OPERATOR:
				switch ((int) tree -> data -> val){
					case 's':
						fprintf(out, ")");
						break;
					case 'c':
						fprintf(out, ")");
						break;
					default:
					       break;
				}
				break;
			case VAR:
				fprintf(out, "%c", (int) tree -> data -> val);
				break;
			case NUMBER:
				fprintf(out, "%lg", tree -> data -> val);
				break;
			break;
		}
	}
	
	if (tree -> data != NULL) fprintf(out, "}");
	
	if (tree -> data != NULL && tree -> data -> diff_flag == 1){
	
			fprintf(out, ")\'");
	
	}
	
	return 0;
}

node* first_optimize(node* tree){
	return NULL;
}

node* second_optimize(node* tree){
	return NULL;
}

