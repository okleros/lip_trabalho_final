
#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <cstring>

enum TokenType {
    TT_TRUE,
    TT_FALSE,
    TT_IF,
    TT_THEN,
    TT_ELSE,
    TT_ENDIF,
    TT_SUC,
    TT_PRED,
    TT_EHZERO,
    TT_LAMBDA,
    TT_NAT,
    TT_BOOL,
    TT_BEGIN,
    TT_END,
    TT_DOT,
    TT_COLON,
    TT_LPAREN,
    TT_RPAREN,
    TT_ARROW,
    TT_VAR,
    TT_NUMBER,
    TT_INVALID_ID
};

struct Token
{
    TokenType type;
    char token_string[32];

    Token(const TokenType &t = TT_INVALID_ID, const char *token_string = "") {
	type = t;
	strcpy(this->token_string, token_string);
    }
};

const char *token_strings[19] = {
    "true",
    "false",
    "if",
    "then",
    "else",
    "endif",
    "suc",
    "pred",
    "ehzero",
    "lambda",
    "Nat",
    "Bool",
    "begin",
    "end",
    ".",
    ":",
    "(",
    ")",
    "->"
};

#endif // TOKENS_HPP
