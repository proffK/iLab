#ifndef M_TOKEN
#define M_TOKEN

typedef struct {
	int type;
	double val;
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
	END_BLOCK
};

enum STREAM_TYPE {
	IN_STREAM,
	OUT_STREAM,
	ERR_STREAM
};

#endif
