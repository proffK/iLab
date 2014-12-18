
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
			
			node_dtor(nd -> left);
			nd -> left = diff_tree(tree -> left, var, out);
			
			node_dtor(nd -> right);
			nd -> right = diff_tree(tree -> right, var, out);
			
		}

	    else if (tree -> data -> val == '*'){

			node_ctor(nd , OPERATOR, '+');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, '*');	     
			
			nd -> right = node_new();
			node_ctor(nd -> right, OPERATOR, '*');
			
			if (tree -> right != NULL){
				
				nd -> right -> left = node_cpy(tree -> left);
						
				nd -> right -> right = node_cpy(tree -> right);
				nd -> right -> right -> data -> diff_flag = 1;
				
			}

			if (tree -> left != NULL){
				
				nd -> left -> left = node_cpy(tree -> left);
				nd -> left -> left -> data -> diff_flag = 1;
				
				nd -> left -> right = node_cpy(tree -> right);
								
			}

			fprintf(out, "Пользуясь правилом производной произведения:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");
			
			node_dtor(nd -> left -> left);
			nd -> left -> left = diff_tree(tree -> left, var, out);
			
			node_dtor(nd -> right -> right);
		    nd -> right -> right = diff_tree(tree -> right, var, out);

		}

		else if (tree -> data -> val == '/'){

			node_ctor(nd, OPERATOR, '/');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, '+');

			nd -> left -> left = node_new();
			node_ctor(nd -> left -> left, OPERATOR, '*');
			
			nd -> left -> right = node_new();
			node_ctor(nd -> left -> right, OPERATOR, '*');

			nd -> left -> left -> right = node_cpy(tree -> right);

			nd -> left -> right -> left = node_cpy(tree -> left);

			nd -> right = node_new();
			node_ctor(nd -> right, OPERATOR, '^');
			
			nd -> right -> left = node_cpy(tree -> right);

			nd -> right -> right = node_new();
			node_ctor(nd -> right -> right, NUMBER, 2);
			
			nd -> left -> left -> left = node_cpy(tree -> left);
			
			nd -> left -> left -> left -> data -> diff_flag = 1;
			
			nd -> left -> right -> right = node_cpy(tree -> right);
				       				  
			nd -> left -> right -> right -> data -> diff_flag = 1;
			
			fprintf(out, "Пользуясь правилом производной частного:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");
			
			node_dtor(nd -> left -> left -> left);
			nd -> left -> left -> left = diff_tree(tree -> left, var,\
				       				out);
			
			node_dtor(nd -> left -> right -> right);
			nd -> left -> right -> right = diff_tree(tree -> right,\
				       				  var, out);
			

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
			nd -> right = node_new();
			node_ctor(nd -> right, NUMBER,\
				  tree -> right -> data -> val);
				  
			nd -> left -> right = node_cpy(tree -> left);
			nd -> left -> right -> data -> diff_flag = 1;
			
			fprintf(out, "Пользуясь правилом производной степени:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");
			
			node_dtor(nd -> left -> right);
			nd -> left -> right = diff_tree(tree -> left, var, out);

		}

		else if (tree -> data -> val == 's'){

			node_ctor(nd, OPERATOR, '*');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, 'c');

			nd -> left -> left = node_cpy(tree -> right);
			
			nd -> right = node_cpy(tree -> right);
			nd -> right -> data -> diff_flag = 1;
			
			fprintf(out, "Пользуясь правилом производной синуса:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");
			
			node_dtor(nd -> right);
			nd -> right = diff_tree(tree -> right, var, out);

		}

		else if (tree -> data -> val == 'c'){

			node_ctor(nd, OPERATOR, '*');

			nd -> left = node_new();
			node_ctor(nd -> left, OPERATOR, '*');

			nd -> left -> left = node_new();
			node_ctor(nd -> left -> left, NUMBER, -1);

			nd -> left -> right = node_new();
			node_ctor(nd -> left -> right, OPERATOR, 's');
			
			nd -> left -> right -> left = node_cpy(tree -> right);
			
			nd -> right = node_cpy(tree -> right);
			nd -> right -> data -> diff_flag = 1;
			
			fprintf(out, "Пользуясь правилом производной косинуса:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");
			
			node_dtor(nd -> right);

			nd -> right = diff_tree(tree -> right, var, out);

		}

		else {

			return NULL;
		
		}

	}

	
	else if (tree -> data -> type == NUMBER){
		
		node_ctor(nd, NUMBER, 0);
		
		fprintf(out, "Пользуясь правилом производной константы:\n\n$");
		tex_dump(diffed_tree, out);
		fprintf(out, "$\n\n");
		
	}

	else if (tree -> data -> type == VAR){

		if (tree -> data -> val == var){
			
			node_ctor(nd, NUMBER, 1);
		
			fprintf(out, "Пользуясь правилом производной переменной:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");

		}
		else {
			
			node_ctor(nd, NUMBER, 0);
		
			fprintf(out, "Пользуясь правилом производной константы:\n\n$");
			tex_dump(diffed_tree, out);
			fprintf(out, "$\n\n");
			
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
			default:
			break;
		}
	}
	
	if (tree -> data != NULL) fprintf(out, "}");
	
	if (tree -> data != NULL && tree -> data -> diff_flag == 1){
	
			fprintf(out, ")\'");
	
	}
	
	return 0;
}

node* first_optimize(node* tree, int* end_flag){
	
	node* temp = NULL;
	
	if (tree == NULL) return NULL;
	
	//printf("%d", *end_flag);
	//fflush(stdout);
	

	if (tree -> left != NULL){ 
		
		tree -> left = first_optimize(tree -> left, end_flag);
		
	}

	if (tree -> right != NULL){ 
		
		tree -> right = first_optimize(tree -> right, end_flag);
		
	}
	
		if (tree -> data != NULL && tree -> data -> type == OPERATOR) {
		
		if (tree -> data -> val == '-' ||\
		    tree -> data -> val == '+' ){
			
			if (tree -> left != NULL &&\
				tree -> left -> data -> type == NUMBER &&\
				tree -> left -> data -> val == 0){
				
				++*end_flag;	
				temp = node_cpy(tree -> right);
				node_dtor(tree);
				return temp;
			
			}
			
			if (tree -> right != NULL &&\
				tree -> right -> data -> type == NUMBER &&\
				tree -> right -> data -> val == 0){
				
				++*end_flag;	
				temp = node_cpy(tree -> left);
				node_dtor(tree);
				return temp;
			}
			
			if (tree -> data -> val == '+'){
			
				if (tree -> left != NULL &&\
					tree -> right != NULL &&\
					tree -> right -> data -> type == NUMBER &&\
					tree -> left -> data -> type == NUMBER){
				
					node* nw = node_new();
					node_ctor(nw, NUMBER, tree -> right -> data -> val +\
							tree -> left -> data -> val);
					++*end_flag;
					node_dtor(tree);
					return nw;
			
				}
			}
			
			if (tree -> data -> val == '-'){
			
				if (tree -> left != NULL &&\
					tree -> right != NULL &&\
					tree -> right -> data -> type == NUMBER &&\
					tree -> left -> data -> type == NUMBER){
				
					node* nw = node_new();
					node_ctor(nw, NUMBER, tree -> right -> data -> val -\
							tree -> left -> data -> val);
					++*end_flag;
					node_dtor(tree);
					return nw;
			
				}
			}
		
		}
		
		if (tree -> data -> val == '*'){
			
			if (tree -> left != NULL &&\
				tree -> left -> data -> type == NUMBER &&\
				tree -> left -> data -> val == 1){
				
				++*end_flag;	
				temp = node_cpy(tree -> right);
				node_dtor(tree);
				return temp;
			
			}
			
			if (tree -> left != NULL &&\
				tree -> left -> data -> type == NUMBER &&\
				tree -> left -> data -> val == 0){
				
				++*end_flag;	
				temp = node_cpy(tree -> left);
				node_dtor(tree);
				return temp;
			
			}
			
			if (tree -> right != NULL &&\
				tree -> right -> data -> type == NUMBER &&\
				tree -> right -> data -> val == 1){
				
				++*end_flag;	
				temp = node_cpy(tree -> left);
				node_dtor(tree);
				return temp;
			
			}
			
			if (tree -> right != NULL &&\
				tree -> right -> data -> type == NUMBER &&\
				tree -> right -> data -> val == 0){
				
				++*end_flag;	
				temp = node_cpy(tree -> right);
				node_dtor(tree);
				return temp;
			}
		
		}
		
		if (tree -> data -> val == '/'){
			
			if (tree -> left != NULL &&\
				tree -> left -> data -> type == NUMBER &&\
				tree -> left -> data -> val == 0){
				
				++*end_flag;	
				temp = node_cpy(tree -> left);
				node_dtor(tree);
				return temp;
			
			}
			
			if (tree -> right != NULL &&\
				tree -> right -> data -> type == NUMBER &&\
				tree -> right -> data -> val == 1){
				
				++*end_flag;	
				temp = node_cpy(tree -> left);
				node_dtor(tree);
				return temp;
			
			}
		
		}
		
		if (tree -> data -> val == '^'){
			
			if (tree -> right != NULL &&\
				tree -> right -> data -> type == NUMBER &&\
				tree -> right -> data -> val == 1){
				
				++*end_flag;	
				temp = node_cpy(tree -> left);
				node_dtor(tree);
				return temp;
			
			}
		
		}
	}
		
	
	return tree;
	
}


