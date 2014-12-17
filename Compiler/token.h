#ifndef M_TOKEN
#define M_TOKEN

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int type;
	double val;
	int diff_flag;
} token;

enum TOKEN_TYPE {
	NUMBER,
	BRACE,
	VAR,
	ASSIGN,
	OPERATOR,
        END_STATEMENT,
	FUNCTION,
	STREAM,
	END_PROGRAM,
	LABEL,
	COMPARATION,
	WHILE,
	IF,
	FUNC_CODE,
	GOTO,
	BEGIN_BLOCK,
	END_BLOCK,
	CHAR_CONSTANT,
	STRING_CONSTANT,
	DIFF_OPER
};

enum STREAM_TYPE {
	IN_STREAM,
	OUT_STREAM,
	ERR_STREAM
};

int token_dump(FILE* out, token* token_array);

token* token_new();

int token_ctor(token* tok, int type, double val);

int token_delete(token* tok);

#endif
