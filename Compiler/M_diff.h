#ifndef M_DIFF
#define M_DIFF

#include "M_tree.h"

node* diff_tree(node* tree, int var, FILE* out);

int tex_dump(node* tree, FILE* out);

node* first_optimize(node* tree);

node* second_optimize(node* tree);

#endif
