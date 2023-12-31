#ifndef HELPER_FUNC_HPP
#define HELPER_FUNC_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

#include "tokens.hpp"
#include "reserved_words.hpp"
#include "types.hpp"

char *to_upper(const char *input_str);

bool is_nat(const char *input_str);
bool is_valid_var_name(const char *input_str);
bool is_reserved_word(const char *input_str);
bool is_term(const std::vector<Token>& tokens);
bool has_invalid_id(const std::vector<Token>& tokens);

int find_end(const std::vector<Token>& tokens, const TokenType &push_token, const TokenType &pop_token);

type_ll* infer_type(const std::vector<TokenType>& tokens, const std::vector<var_type>& context);

template <typename T>
std::vector<T> subvector(const std::vector<T>& v, int start, int end);
    
// função que, dada uma string qualquer, retorna
// o seu equivalente maiúsculo
char *to_upper(const char *input_str)
{
    int length = std::strlen(input_str); 

    // aqui alocamos a string que será retornada,
    // naturalmente com o mesmo tamanho da original
    char *output = (char *)std::malloc(sizeof(char) * (length));

    for (int i = 0; i < length; ++i)
	output[i] = std::toupper(input_str[i]);

    output[length] = '\0';
    
    return output;
}

bool has_invalid_id(const std::vector<Token>& tokens)
{
    for (Token token : tokens)
	if (token.type == TT_INVALID_ID)
	    return 1;
        
    return 0;
}

// função polimórfica que retorna um subvetor de um
// vetor de tipo T passado, com a opção de passar
// números negativos em end para ir até o final
template <typename T>
std::vector<T> subvector(const std::vector<T>& v, int start, int end) {
    if (start >= (int)v.size() || end > (int)v.size())
        return std::vector<T>();

    if (end < 0)
	return std::vector<T>(v.begin() + start, v.end());
    
    return std::vector<T>(v.begin() + start, v.begin() + end);
}

std::ostream& operator << (std::ostream& cout, TokenType token)
{
    if (token >= 0 && token <= 13)
	cout << "<TT_" << to_upper(token_strings[static_cast<int>(token)]) << ">";
    else
	switch (token) {
	case (TT_DOT):
	    cout << "<TT_DOT>";
	    break;
	case (TT_COLON):
	    cout << "<TT_COLON>";
	    break;
	case (TT_LPAREN):
	    cout << "<TT_LPAREN>";
	    break;
	case (TT_RPAREN):
	    cout << "<TT_RPAREN>";
	    break;
	case (TT_ARROW):
	    cout << "<TT_ARROW>";
	    break;
	case (TT_VAR):
	    cout << "<TT_VAR>";
	    break;
	case (TT_NUMBER):
	    cout << "<TT_NUMBER>";
	    break;
	default:
	    cout << "<TT_INVALID_ID>";
	}
    
    return cout;
}

bool is_term(const std::vector<Token>& tokens)
{
    if (has_invalid_id(tokens)) return 0;

    if (tokens.size() == 1) {
	switch (tokens[0].type) {
	case ( TT_TRUE   ):
	case ( TT_FALSE  ):
	case ( TT_NUMBER ):
	case ( TT_SUC    ):
	case ( TT_PRED   ):
	case ( TT_EHZERO ):
	case ( TT_VAR    ):
	    return 1;
	    
	default:
	    return 0;
	}
    } else {
	if (tokens[0].type == TT_LPAREN) {
	    int breakpoint = find_end(subvector(tokens, 1, -1), TT_LPAREN, TT_RPAREN);

	    if (breakpoint < 0) return 0;
	}
    }

    return 0;
}

// verifica se uma certa string representa ou não
// um Nat, segundo a gramática da linguagem
bool is_nat(const char *input_str)
{
    int is_nat = 1;

    // se for uma string vazia, obviamente não é Nat
    if (*input_str == '\0' || *input_str == ' ') is_nat = 0;

    // se o primeiro dígito for um zero e houverem mais dígitos
    // não é Nat
    // o ++ e -- são para ir para o próximo char e depois voltar
    // pois a verificação a seguir precisa que o ponteiro esteja
    // na primeira posição da string
    if (*(input_str++) == '0' && *(input_str--)) is_nat = 0;
    
    // se em algum momento o que está na string não for um dígito,
    // 0 .. 9, automaticamente a string não representa um Nat
    while (*input_str != '\0')
        if (!isdigit(*(input_str++)))
            is_nat = 0;
    
    return is_nat;
}

bool is_valid_var_name(const char *input_str)
{
    int is_valid = 1;
    
    // is_valid será falso se o primeiro char não for uma letra ou se a palavra
    // for uma das palavras reservadas (vide reserved_words[])
    is_valid = !(!isalpha(*input_str) || is_reserved_word(input_str));

    // verifica se os chars além do primeiro são alfanuméricos 
    input_str++;
    while (*input_str != '\0')
	if(!isalnum(*(input_str++)))
	    is_valid = 0;
	
    return is_valid;
}

bool is_reserved_word(const char *input_str)
{
    // basicamente verifica se a string de entrada bate
    // com uma das strings das palavras reservadas da
    // linguagem
    for (int i = 0; i < RES_WORDS_COUNT; ++i)
	if (input_str == reserved_words[i])
	    return 1;
    
    return 0;
}

// TODO: TYPE INFERENCE
int find_end(const std::vector<Token>& tokens, const TokenType& push_token, const TokenType& pop_token)
{
    std::stack<TokenType> stack;
    int i = 0;
    
    for (const Token& token : tokens) {
	if (token.type == push_token)
	    stack.push(push_token);
	else
	    if (token.type == pop_token) {
		stack.pop();
		if (stack.empty())
		    return i;
	    }

	i++;
    }

    return -1;    
}

type_ll *infer_type(const std::vector<Token>& tokens, const std::vector<var_type>& context)
{
    type_ll *type_if;
    type_ll *type_then;
    type_ll *type_else;

    switch (tokens[0].type) {
    case ( TT_TRUE   ):
    case ( TT_FALSE  ):
	return new type_ll("Bool");
	    
    case ( TT_NUMBER ):
	return new type_ll("Nat");

    case ( TT_SUC    ):
    case ( TT_PRED   ):
	return new type_ll("( Nat -> Nat )");

    case ( TT_EHZERO ):
	return new type_ll("( Nat -> Bool )");

    case ( TT_VAR    ):
	for (var_type vt : context) {
	    if (!strcmp(tokens[0].token_string, vt.var_name))
		return new type_ll(vt.type);
	}
	    
	return new type_ll();

    case ( TT_IF     ):
	type_if = infer_type(subvector(tokens, 1, find_end(tokens, TT_IF, TT_THEN)), context);

	type_then = infer_type(subvector(tokens, find_end(tokens, TT_IF, TT_THEN) + 1,
						  find_end(tokens, TT_IF, TT_ELSE)), context);

	type_else = infer_type(subvector(tokens, find_end(tokens, TT_IF, TT_ELSE) + 1,
						  find_end(tokens, TT_IF, TT_ENDIF)), context); 

	if (*type_if == type_ll(BOOL) && *type_then == *type_else)
	    return type_then;
	else
	    return new type_ll();
	
    case (TT_LPAREN):
	return new type_ll();    

    default:
	return new type_ll();    
    }	
};

#endif // HELPER_FUNC_HPP
