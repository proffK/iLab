#ifndef M_SYN
#define M_SYN

/*?
 * G0 ::= E
 * E ::= T {"+" "-", T}*
 * T ::= P{"*" "/", P}*
 * P ::= "(" E ")" | N
 * N ::= [0-9]+
*/

int get_G0(char* input_string);

int get_E();

int get_T();

int get_P();

int get_N();

#endif
