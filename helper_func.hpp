#ifndef HELPER_FUNC_HPP
#define HELPER_FUNC_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

#include "tokens.hpp"
#include "reserved_words.hpp"
#include "types.hpp"

char *to_upper(const char *);

bool is_nat(const char *);
bool is_valid_var_name(const char *);
bool is_reserved_word(const char *);
bool is_term(const std::vector<TokenType>&);
bool has_invalid_id(const std::vector<TokenType>&);

int find_end(const std::vector<TokenType>&);

type_ll* infer_type(const std::vector<TokenType>&);

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

bool has_invalid_id(const std::vector<TokenType>& tokens)
{
    for (TokenType token : tokens)
	if (token == TT_INVALID_ID)
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

bool is_term(const std::vector<TokenType>& tokens)
{
    if (has_invalid_id(tokens)) return 0;

    if (tokens.size() == 1) {
	switch (tokens[0]) {
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
	return 0;
	if (tokens[0] == TT_LPAREN) {
	    int breakpoint = find_end(subvector(tokens, 1, -1));

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
int find_end(const std::vector<TokenType>& tokens, const TokenType& push_token, const TokenType& pop_token)
{
    (void)push_token;
    (void)pop_token;

    std::stack<TokenType> stack;
    int i = 0;
    
    if (tokens[i] == TT_IF) {
	stack.push(TT_IF);
	i++;
	
	while (!stack.empty()) {
	    if (tokens[i] == TT_IF) {
		stack.push(TT_IF);
		i++;
	    } else {
		if (tokens[i] == TT_ENDIF) {
		    stack.pop();
		    i++;
		}
	    }
	}
    }
    // TODO
    // if (tokens[0] == TT_LPAREN) {
    // 	stack.push(TT_IF);
    // 	i++;
	
    // 	while (!stack.empty()) {
    // 	    if (tokens[i] == TT_IF) {
    // 		stack.push(TT_IF);
    // 		i++;
    // 	    } else {
    // 		if (tokens[i] == TT_ENDIF) {
    // 		    stack.pop();
    // 		    i++;
    // 		}
    // 	    }
    // 	}
    // }

    // if (tokens[0] == TT_LAMBDA) {
    // 	stack.push(TT_IF);
    // 	i++;
	
    // 	while (!stack.empty()) {
    // 	    if (tokens[i] == TT_IF) {
    // 		stack.push(TT_IF);
    // 		i++;
    // 	    } else {
    // 		if (tokens[i] == TT_ENDIF) {
    // 		    stack.pop();
    // 		    i++;
    // 		}
    // 	    }
    // 	}
    // }
    
    return 0;
}

type_ll *infer_type(const std::vector<TokenType>& tokens, const std::vector<var_type> context)
{
    (void)context;

    type_ll *tipo_um = new type_ll;
    type_ll *tipo_dois = new type_ll;
    
    if (tokens.size() == 1) {
	switch (tokens[0]) {
	case ( TT_TRUE   ):
	case ( TT_FALSE  ):
	    tipo_um->type = BOOL;
	    delete tipo_dois;
	    return tipo_um;

	case ( TT_NUMBER ):
	    tipo_um->type = NAT;
	    delete tipo_dois;
	    return tipo_um;

	case ( TT_SUC    ):
	case ( TT_PRED   ):
	    tipo_um->type = NAT;
	    tipo_dois->type = NAT;
	    add_type(&tipo_um, tipo_dois);
	    return tipo_um;

	case ( TT_EHZERO ):
	    tipo_um->type = NAT;
	    tipo_dois->type = BOOL;
	    add_type(&tipo_um, tipo_dois);
	    return tipo_um;

	case ( TT_VAR    ):
	    // contexto

	default:
	    return new type_ll;
	}
    } else {
	return new type_ll;
	if (tokens[0] == TT_LPAREN) {
	    int breakpoint = find_end(subvector(tokens, 1, -1));

	    if (breakpoint < 0) return 0;
	}
    }

    delete tipo_um;
    delete tipo_dois;
};

#endif // HELPER_FUNC_HPP

