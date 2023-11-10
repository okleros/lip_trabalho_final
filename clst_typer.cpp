#include <iostream>
#include <vector>
#include <bits/stdc++.h>

// tips: first, tokenize the expression

bool is_nat(const char *);
bool is_valid_var_name(const char *);
bool is_reserved_word(const char *);
char *to_upper(const char *);

template <typename T>
std::vector<T> subvector(const std::vector<T>& v, size_t, size_t);

namespace ReservedWords
{
    static const char *reserved_words[] = {
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
	TT_DOT = 14,
	TT_COLON = 15,
	TT_OPEN_PARENTHESIS = 16,
	TT_CLOSE_PARENTHESIS = 17,
	TT_ARROW = 18,
	TT_VAR = 19,
	TT_NUMBER = 20,
	TT_INVALID_ID = 21
    };
};

bool is_term(std::vector<TokenType::TokenType>);

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

namespace Tokenizer {
    TokenType::TokenType classify_token(const char *token_string)
    {
	for (int i = 0; i < 20; ++i)
	    if (!strcmp(token_string, TokenStrings::token_strings[i]))
		return static_cast<TokenType::TokenType>(i);

	if (is_valid_var_name(token_string)) return TokenType::TokenType::TT_VAR;

	if (is_nat(token_string)) return TokenType::TokenType::TT_NUMBER;
	
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
	// while (ss >> word) {
	//     current_token = classify_token(word);

	//     tokens.push_back(current_token);
	// }
	while (true) {
	    ss.getline(word, sizeof(word), ' ');
	    
	    if (*word == '\0' && ss.eof()) {
		if (expr[strlen(expr) - 1] == ' ') {
		    current_token = classify_token(" ");
		    tokens.push_back(current_token);
		}

		break;

	    } else {
		current_token = classify_token(word);
		tokens.push_back(current_token);
	    }
	}
	
	return tokens;
    }
}

std::ostream& operator<<(std::ostream& cout,TokenType::TokenType token)
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
	case (TokenType::TokenType::TT_OPEN_PARENTHESIS):
	    cout << "<TT_OPEN_PARENTHESIS>";
	    break;
	case (TokenType::TokenType::TT_CLOSE_PARENTHESIS):
	    cout << "<TT_CLOSE_PARENTHESIS>";
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
    
    std::cout << "pipipipopopo: ";
    std::cin.getline(input_str, sizeof(input_str));

    std::vector<TokenType::TokenType> tokens = Tokenizer::tokenize(input_str);

    for (size_t i = 0; i < tokens.size(); ++i)
	std::cout << tokens[i] << ' ';
	
    std::cout << '\n';
}

bool is_nat(const char *input_str)
{
    int is_nat = 1;

    if (*input_str == '\0') is_nat = 0;
    while (*input_str != '\0')
        if (!isdigit(*(input_str++)))
            is_nat = 0;
    
    return is_nat;
} 

char *to_upper(const char *input_str)
{
    int length = std::strlen(input_str); 
    
    char *output = (char *)std::malloc(sizeof(char) * (length));

    for (int i = 0; i < length; ++i)
	output[i] = std::toupper(input_str[i]);

    output[length] = '\0';
    
    return output;
}

bool is_valid_var_name(const char *input_str)
{
    int is_valid = 1;

    // is_valid será 0 se o primeiro char não for uma letra ou se a palavra
    // for uma das palavras reservadas (vide ReservedWords::reserved_words[])
    is_valid = !(!isalpha(*input_str) || is_reserved_word(input_str));

    input_str++;
    // verifica se os chars além do primeiro são alfanuméricos 
    while (*input_str != '\0')
	if(!isalnum(*(input_str++)))
	    is_valid = 0;
	
    return is_valid;
}

bool is_reserved_word(const char *input_str)
{
    int i;

    // 13 é a quantidade de palavras reservadas da sintaxe concreta, não é um número mágico.
    for (i = 0; i < 13; ++i)
	if (input_str == ReservedWords::reserved_words[i])
	    return 1;
    
    return 0;
}

template <typename T>
std::vector<T> subvector(const std::vector<T>& v, int start, int end) {
    if (start >= (int)v.size() || end > (int)v.size())
        return std::vector<T>();

    if (end < 0)
	return std::vector<T>(v.begin() + start, v.end());
    
    return std::vector<T>(v.begin() + start, v.begin() + end);
}

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
    // if (tokens[0] == TokenType::TokenType::TT_OPEN_PARENTHESIS) {
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
	if (tokens[0] == TokenType::TokenType::TT_OPEN_PARENTHESIS) {
	    int breakpoint = find_end(subvector(tokens, 1, -1));

	    if (breakpoint < 0) return 0;
	}
    }
    
    return 0;
}


// TODO: implement find_end
// TODO: finish implementing is_term
