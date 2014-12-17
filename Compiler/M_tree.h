#ifndef M_TREE
#define M_TREE

#include <stdio.h>
#include "token.h"
#include "M_lex.h"

typedef token* elem_t;


struct tree_node {
	elem_t data;
	struct tree_node* left;
	struct tree_node* right;
};

typedef struct tree_node node;

///#####################################################################

node* node_new(void);

int node_ctor(node* new_node, int type, double val);

int node_dtor(node* deleted_node);

int node_dump2(node* tree, FILE* out);
 
node* add_node_left(node* parent, node* new);

node* add_node_right(node* parent, node* new);

int node_dump(node* tree, FILE* out);

int create_tree(FILE* input, node* tree, char* (*get_node_data) (char*, elem_t*));

char* node_import(node* new, char* buffer, char* (*get_node_data) (char*, elem_t*));

int node_ok(node* nd);

node* node_cpy(node* in);

#endif
