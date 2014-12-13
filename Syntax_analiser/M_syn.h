#ifndef M_SYN
#define M_SYN
#include "M_tree.h"
/*
 * G0 ::= E
 * E ::= T {"+" "-", T}*
 * T ::= P{"*" "/", P}*
 * P ::= "(" E ")" | N
 * N ::= [0-9]+
*/

node* get_G0(char* input_string);

node* get_E();

node* get_T();

node* get_P();

node* get_N();

#endif
