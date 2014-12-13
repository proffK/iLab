#include "M_sem.h"

int block_semantic_analize(FILE* out, node* tree){
	
	if (tree == NULL) return -1;
	
	node* current_node = tree;
	
	while (current_node != NULL){
		
		if (current_node -> right != NULL){
			
			semantic_analize(out, current_node -> right);
			
		}
		
		current_node = current_node -> left;
		
	}
	
	return 0;
	
}

int semantic_analize(FILE* out, node* tree){
	
	if (!(node_ok(tree))){
		
		fprintf(out, "Incorrect tree\n");
		return -1;
		
	}
	
	if (tree -> data != NULL && tree -> data -> type == WHILE){
		
		fprintf(out, ":%lg\n", tree -> data -> val);
		
	}

	if (tree -> data != NULL && tree -> data -> type == BEGIN_BLOCK){
		
		block_semantic_analize(out, tree);
		return 0;
		
	}


	if (tree -> left != NULL){ 
		
		semantic_analize(out, tree -> left);
		
	}
	
	if (tree -> data != NULL && tree -> data -> type == IF){
		
		fprintf(out, " %lg\n", tree -> data -> val);

	}
	
	if (tree -> data != NULL && tree -> data -> type == WHILE){
		
		fprintf(out, " %lg\n", tree -> data -> val + 1);
		
	}

	if (tree -> data != NULL && tree -> data -> type == FUNCTION){

		fprintf(out, "call %lg\n", tree -> data -> val);
		
		
		}



	if (tree -> right != NULL){ 
		
		semantic_analize(out, tree -> right);
	
	}

	if (tree -> data != NULL){

		switch (tree -> data -> type) {

			case NUMBER:
				fprintf(out, "push %lg\n", tree -> data -> val);
				break;
			case VAR:
				fprintf(out, "push r%lg\n",\
					tree -> data -> val - 'a' + 1);
				break;
			case OPERATOR:
				switch ((int) tree -> data -> val){

					case '+':
						fprintf(out, "add\n");
						break;	
					case '-':
						fprintf(out, "sub\n");
						break;
					case '/':
						fprintf(out, "div\n");
						break;
					case '*':
						fprintf(out, "mul\n");
						break;
					case '^':
						fprintf(out, "pow\n");
						break;
					case 's':
						fprintf(out, "sin\n");
						break;
						case 'c':
						fprintf(out, "cos\n");
						break;
					default:
					       break;
				}
			break;
			case FUNCTION:
				break;
			case ASSIGN:
				fprintf(out, "pop r%lg\n",\
					tree -> data -> val - 'a' + 1);
				break;
			case COMPARATION:
				switch ((int) tree -> data -> val){
					case '<':
						fprintf(out, "jna");
						break;
					case '>':
						fprintf(out, "jnb");
			
					break;
					case '=':
						fprintf(out, "jne");
						break;
					default:
						break;
			}
			break;
			case IF:
				fprintf(out, ":%lg\n", tree -> data -> val);
				break;
			case WHILE:
				fprintf(out, "jp %lg\n:%lg\n", tree -> data -> val,\
						tree -> data -> val + 1);
				break;
			default:
				break;
		}


	}

	return 0;
}
