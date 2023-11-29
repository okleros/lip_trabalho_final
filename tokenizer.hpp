#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <cstring>
#include <sstream>

#include "tokens.hpp"
#include "reserved_words.hpp"
#include "helper_func.hpp"

namespace Tokenizer {
    Token classify_token(const char *token_string)
    {
	// compara a string do token com a string pré-estabelecida
	// no vetor token_strings[] em tokens.hpp
	for (int i = 0; i < 19; ++i)
	    if (!strcmp(token_string, token_strings[i]))
		return Token(static_cast<TokenType>(i), token_string);
	
	// caso não seja uma palavra conhecida, só pode ser
	// um nome de variável
	if (is_valid_var_name(token_string)) return Token(TT_VAR, token_string);

	// ou número
	if (is_nat(token_string)) return Token(TT_NUMBER, token_string);

	// caso não seja nenhum dos acima citados, é um token
	// inválido
	return Token(TT_INVALID_ID, "!");
    }
    
    std::vector<Token> tokenize(const char *expr)
    {
	// defini 32 como o maior tamanho de nome de variável possível
	// por questão de organização, na prática não há essa limitação
	char word[32];
	
	Token current_token;
	std::vector<Token> tokens;

	std::stringstream ss(expr);

	while (true) {
	    ss.getline(word, sizeof(word), ' ');

	    // verifica especificamente se há um espaço no fim da string
	    // pois o método de stringstream não verifica o último espaço
	    // da string
	    if (*word == '\0' && ss.eof()) {
		if (expr[strlen(expr) - 1] == ' ') {
		    current_token = classify_token(" ");
		    tokens.push_back(current_token);
		}
		
		break;

	    } else {
		// faz a classificação dos tokens e coloca numa stream
		// de tokens, denotado por um std::vector<Token>
		current_token = classify_token(word);
		tokens.push_back(current_token);
	    }
	}
	
	return tokens;
    }
}

#endif // TOKENIZER_HPP
