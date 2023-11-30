#include <iostream>
#include <bits/stdc++.h>

#include "tokens.hpp"
#include "tokenizer.hpp"
#include "types.hpp"

int main()
{
    char input_str[1024];

    std::cin.getline(input_str, sizeof(input_str));

    std::vector<Token> tokens = Tokenizer::tokenize(input_str);

    // for (const Token& token : subvector(tokens, 1, find_end(tokens, TT_IF, TT_THEN))) {
    // 	std::cout << token.type << " ";
    // }

    // std::cout << '\n';

    // se a expressão digitada não for exatamente um termo, printamos "!"
    if (0/*!is_term(tokens)*/) {
	std::cout << "!" << '\n'; 

    } else {
	std::vector<var_type> context;
	
	type_ll *expr_type = infer_type(tokens, context);

	// print_type() cuida do caso em que o termo não é bem tipado dado
	// o contexto, ou seja, se qualquer parte do termo tiver algum tipo
	// indefinido, automaticamente printamos "-", caso contrário, vamos
	// printar o tipo completo do termo
	print_type(expr_type);
	std::cout << '\n';
	// debug 
	// for (size_t i = 0; i < tokens.size(); ++i)
	//     std::cout << tokens[i] << ' ';
	
	// std::cout << '\n';
    }
    
    return 0;
}

// TODO: implement find_end
// TODO: finish implementing is_term
