#include <iostream>
#include <vector>
#include <bits/stdc++.h>

// tips: first, tokenize the expression

int is_nat(const char *);
int is_valid_var_name(const char *);
int is_reserved_word(const char *);

namespace ReservedWords
{
    static const char *reserved_words[14] = {
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
	"end"
    };
};

namespace TokenType {
    enum TokenType {
	TT_TRUE = 0,
	TT_FALSE = 1,
	TT_IF = 2,
	TT_THEN = 3,
	TT_ELSE = 4,
	TT_ENDIF = 5,
	TT_SUC = 6,
	TT_PRED = 7,
	TT_EHZERO = 8,
	TT_LAMBDA = 9,
	TT_NAT = 10,
	TT_BOOL = 11,
	TT_BEGIN = 12,
	TT_END = 13,
	TT_VAR,
	TT_INVALID_ID
    };
};

namespace Tokenizer {
    TokenType::TokenType classify_token(const char *token_string)
    {
	for (int i = 0; i < 14; ++i)
	    if (token_string == ReservedWords::reserved_words[i])
		return static_cast<TokenType::TokenType>(i);

	if (is_valid_var_name(token_string))
	    return TokenType::TokenType::TT_VAR;

	return TokenType::TokenType::TT_INVALID_ID;
    }
    
    std::vector<TokenType::TokenType> tokenize(const char *expr)
    {
	// defini 32 como o maior tamanho de nome de variável possível,
	// questão de organização
	char word[32];
	
	TokenType::TokenType current_token;
	std::vector<TokenType::TokenType> tokens;

	std::stringstream ss(expr);
	while (ss >> word) {
	    current_token = classify_token(word);

	    tokens.push_back(current_token);
	}
	
	return tokens;
    }
}

int main()
{
    // std::cout << argc << " " << *argv << '\n';
    std::cout << ReservedWords::reserved_words[4] << '\n';
    std::cout << is_valid_var_name("numDePassos") << '\n';

    return 0;
}

int is_nat(const char *input_str)
{
    int is_nat = 1;
    
    while (*input_str != '\0')
        if (!isdigit(*(input_str++)))
            is_nat = 0;
    
    return is_nat;
} 

int is_valid_var_name(const char *input_str)
{
    int is_valid = 1;

    // is_valid será 0 se o primeiro dígito for um número ou se a palavra
    // for uma das palavras reservadas (vide ReservedWords::reserved_words[])
    is_valid = !(isdigit(*input_str) || is_reserved_word(input_str));

    input_str++;    
    while (*input_str != '\0')
	if(!isalnum(*(input_str++)))
	    is_valid = 0;
	
    return is_valid;
}

int is_reserved_word(const char *input_str)
{
    int i;

    // 13 é a quantidade de palavras reservadas da sintaxe concreta, não é um número mágico.
    for (i = 0; i < 13; ++i)
	if (input_str == ReservedWords::reserved_words[i])
	    return 1;
    
    return 0;
}
