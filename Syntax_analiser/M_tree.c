#include "M_tree.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

//###################################################################################

const int MAX_ELEM_SIZE = 100;

const char* PRINT_NODE_FORMAT = "%d";

const char BEGIN_NODE = ' ';

const char END_NODE = ' ';

//###################################################################################

node* node_new(void){
	
	node* new_node = (node*) calloc (1, sizeof(node));
	
	if (new_node == NULL) {
		
		errno = ENOMEM;
		abort();
		
	}
	
	return new_node;
}
///#####################################################################
int node_ctor(elem_t data, node* new_node){
	
	if (!(node_ok(new_node))) return -1; 
		
		new_node -> data = data;
		new_node -> left = NULL;
		new_node -> right = NULL;
		return 0;
		
	
}
///#####################################################################
int node_dtor(node* deleted_node){
	
	if (!(node_ok(deleted_node))) return -1;
	
	if (deleted_node -> left != NULL) {
	
		node_dtor(deleted_node -> left);
		
	}
	
	if (deleted_node -> right != NULL) {
	
		node_dtor(deleted_node -> right);
		
	}
	
	deleted_node -> data = NULL;
	free(deleted_node);
	deleted_node = NULL;
	
	return 0;
	
}
///#####################################################################
node* add_node_left(node* parent, node* new){
	
	if (!(node_ok(new) && node_ok(parent))) return NULL;
		
	if (parent -> left == NULL){
		
		parent -> left = new;
		return 0;
			
	}
		
	return parent -> left;
	
}
///#####################################################################
node* add_node_right(node* parent, node* new){
	
	if (!(node_ok(new) && node_ok(parent))) return NULL;
		
	if (parent -> right == NULL){
			
	parent -> right = new;
	return 0;
			
	}
		
	return parent -> right;
	
}
///#####################################################################
int node_dump(node* tree, FILE* out){
	
	if (!(node_ok(tree))){
		
		fprintf(out, "Incorrect tree\n");
		return -1;
		
	}
	
	
	if (tree -> left != NULL){ 
		
		node_dump(tree -> left, out);
		
	}
	
	if (tree -> right != NULL){ 
		
		node_dump(tree -> right, out);
		
	}
	
	fprintf(out, "%c", BEGIN_NODE);

	if (tree -> left != NULL || tree -> right != NULL) {
	
		fprintf(out, "%c", tree -> data);
	
	}
	else fprintf(out, PRINT_NODE_FORMAT, tree -> data);

	fprintf(out, "%c", END_NODE);
	return 0;
}
///#####################################################################
char* node_import(node* new, char* buffer, char* (*get_node_data) (char*, elem_t*)){
	
	char* p = NULL;

	p = get_node_data(buffer, &(new -> data));
		
	if (*p == BEGIN_NODE) {
		
		if (new -> left == NULL && *p != END_NODE){
			
			new -> left = node_new();
			p = node_import(new -> left, p, get_node_data);
		}
		
		if (new -> right == NULL && *p != END_NODE){
			
			new -> right = node_new();
			p = node_import(new -> right, p, get_node_data);
		}
		
	}
	
	if 	(*p == END_NODE) {
		++p;
		return p;
		
	}
	
	return NULL;	
}

int node_ok(node* nd){
	if (nd == NULL) return 0;
	return 1;
}

///################################################################################# 

int create_tree(FILE* input, node* tree, char* (*get_node_data) (char*, elem_t*)){
	char* buffer = NULL;
	long len = 0;

	fseek(input, 0, SEEK_END);
	len = ftell(input);
	rewind(input);
	buffer = (char*) calloc (len + 1, sizeof(char));
	
	if (buffer == NULL) return -1;

	buffer[len] = '\0';
	fread(buffer, sizeof(char), len, input);	

	if((node_import(tree, buffer, get_node_data))) return -1;

//	free(buffer);

	return 0;
}
