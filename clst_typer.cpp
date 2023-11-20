#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#define RES_WORDS_COUNT 14

// palavras reservadas da sintaxe concreta da linguagem
namespace ReservedWords
{
    static const char *reserved_words[RES_WORDS_COUNT] = {
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
};

namespace TokenStrings {
    static const char *token_strings[19] = {
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
};

bool is_nat(const char *);
bool is_valid_var_name(const char *);
bool is_reserved_word(const char *);
bool is_term(std::vector<TokenType::TokenType>);
bool has_invalid_id(std::vector<TokenType::TokenType>);

char *to_upper(const char *);

template <typename T>
std::vector<T> subvector(const std::vector<T>& v, size_t, size_t);

namespace Tokenizer {
    TokenType::TokenType classify_token(const char *token_string)
    {
	// compara a string do token com a string pré-estabelecida
	// no namespace TokenStrings
	for (int i = 0; i < 20; ++i)
	    if (!strcmp(token_string, TokenStrings::token_strings[i]))
		return static_cast<TokenType::TokenType>(i);

	// caso não seja uma palavra conhecida, só pode ser ser
	// um nome de variável
	if (is_valid_var_name(token_string)) return TokenType::TokenType::TT_VAR;

	// ou número
	if (is_nat(token_string)) return TokenType::TokenType::TT_NUMBER;

	// caso não seja nenhum dos acima citados, é um token
	// inválido
	return TokenType::TokenType::TT_INVALID_ID;
    }
    
    std::vector<TokenType::TokenType> tokenize(const char *expr)
    {
	// defini 32 como o maior tamanho de nome de variável possível
	// por questão de organização
	char word[32];
	
	TokenType::TokenType current_token;
	std::vector<TokenType::TokenType> tokens;

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
		// de tokens, denotado por um vector<...>
		current_token = classify_token(word);
		tokens.push_back(current_token);
	    }
	}
	
	return tokens;
    }
}
// TODO: REMOVE THIS FUNCTION WHEN NOT NEEDED ANYMORE
std::ostream& operator<<(std::ostream& cout, TokenType::TokenType token)
{
    if (token >= 0 && token <= 13)
	cout << "<TT_" << to_upper(TokenStrings::token_strings[static_cast<int>(token)]) << ">";
    else
	switch (token) {
	case (TokenType::TokenType::TT_DOT):
	    cout << "<TT_DOT>";
	    break;
	case (TokenType::TokenType::TT_COLON):
	    cout << "<TT_COLON>";
	    break;
	case (TokenType::TokenType::TT_LPAREN):
	    cout << "<TT_LPAREN>";
	    break;
	case (TokenType::TokenType::TT_RPAREN):
	    cout << "<TT_RPAREN>";
	    break;
	case (TokenType::TokenType::TT_ARROW):
	    cout << "<TT_ARROW>";
	    break;
	case (TokenType::TokenType::TT_VAR):
	    cout << "<TT_VAR>";
	    break;
	case (TokenType::TokenType::TT_NUMBER):
	    cout << "<TT_NUMBER>";
	    break;
	default:
	    cout << "<TT_INVALID_ID>";
	}
    
    return cout;
}

int main()
{
    char input_str[256];
    
    // std::cout << "pipipipopopo: ";
    std::cin.getline(input_str, sizeof(input_str));

    std::vector<TokenType::TokenType> tokens = Tokenizer::tokenize(input_str);

    for (size_t i = 0; i < tokens.size(); ++i)
	std::cout << tokens[i] << ' ';
	
    std::cout << '\n';
}

// verifica se uma certa string representa ou não
// um Nat, segundo a gramática da linguagem
bool is_nat(const char *input_str)
{
    int is_nat = 1;

    // se for uma string vazia, obviamente não é Nat
    if (*input_str == '\0') is_nat = 0;

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

bool is_valid_var_name(const char *input_str)
{
    int is_valid = 1;
    
    // is_valid será falso se o primeiro char não for uma letra ou se a palavra
    // for uma das palavras reservadas (vide ReservedWords::reserved_words[])
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
	if (input_str == ReservedWords::reserved_words[i])
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

// TODO: TYPE INFERENCE
int find_end(const std::vector<TokenType::TokenType>& tokens)
{
    std::stack<TokenType::TokenType> stack;
    int i = 0;
    
    if (tokens[i] == TokenType::TokenType::TT_IF) {
	stack.push(TokenType::TokenType::TT_IF);
	i++;
	
	while (!stack.empty()) {
	    if (tokens[i] == TokenType::TokenType::TT_IF) {
		stack.push(TokenType::TokenType::TT_IF);
		i++;
	    } else {
		if (tokens[i] == TokenType::TokenType::TT_ENDIF) {
		    stack.pop();
		    i++;
		}
	    }
	}
    }
    // TODO
    // if (tokens[0] == TokenType::TokenType::TT_LPAREN) {
    // 	stack.push(TokenType::TokenType::TT_IF);
    // 	i++;
	
    // 	while (!stack.empty()) {
    // 	    if (tokens[i] == TokenType::TokenType::TT_IF) {
    // 		stack.push(TokenType::TokenType::TT_IF);
    // 		i++;
    // 	    } else {
    // 		if (tokens[i] == TokenType::TokenType::TT_ENDIF) {
    // 		    stack.pop();
    // 		    i++;
    // 		}
    // 	    }
    // 	}
    // }

    // if (tokens[0] == TokenType::TokenType::TT_LAMBDA) {
    // 	stack.push(TokenType::TokenType::TT_IF);
    // 	i++;
	
    // 	while (!stack.empty()) {
    // 	    if (tokens[i] == TokenType::TokenType::TT_IF) {
    // 		stack.push(TokenType::TokenType::TT_IF);
    // 		i++;
    // 	    } else {
    // 		if (tokens[i] == TokenType::TokenType::TT_ENDIF) {
    // 		    stack.pop();
    // 		    i++;
    // 		}
    // 	    }
    // 	}
    // }
    
    return 0;
}

bool is_term(const std::vector<TokenType::TokenType>& tokens)
{
    if (tokens.size() == 1) {
	switch (tokens[0]) {
	case ( TokenType::TokenType::TT_TRUE   ):
	case ( TokenType::TokenType::TT_FALSE  ):
	case ( TokenType::TokenType::TT_NUMBER ):
	case ( TokenType::TokenType::TT_SUC    ):
	case ( TokenType::TokenType::TT_PRED   ):
	case ( TokenType::TokenType::TT_EHZERO ):
	case ( TokenType::TokenType::TT_VAR    ):
	    return 1;

	default:
	    return 0;
	}
    } else {
	if (tokens[0] == TokenType::TokenType::TT_LPAREN) {
	    int breakpoint = find_end(subvector(tokens, 1, -1));

	    if (breakpoint < 0) return 0;
	}
    }
    
    return 0;
}

bool has_invalid_id(std::vector<TokenType::TokenType> tokens)
{
    for (TokenType::TokenType token : tokens)
	if (token == TokenType::TokenType::TT_INVALID_ID)
	    return 0;
        
    return 1;
}

// TODO: implement find_end
// TODO: finish implementing is_term
