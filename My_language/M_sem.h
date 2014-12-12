#ifndef M_SEM
#define M_SEM
#include "M_tree.h"
#include "token.h"
#include <stdio.h>

int semantic_analize(FILE* out, node* parse_tree);

int block_semantic_analize(FILE* out, node* tree);

#endif
