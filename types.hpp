#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>

enum TypeType {
    NAT,
    BOOL,
    LPAREN,
    RPAREN,
    INV_TYPE
};

const char *types_string[4] = {"Nat", "Bool", "( ", " )"};

struct type_ll
{
    TypeType type;
    type_ll *next_type;

    type_ll()            : type(INV_TYPE), next_type(nullptr) {}
    type_ll(TypeType tp) : type(tp), next_type(nullptr) {}
    ~type_ll() { delete this; }
    
};

struct var_type
{
    type_ll type;
    char var_name[32];
};

void add_type(type_ll *input_type, type_ll *type_to_add);
void print_type(type_ll *input_type);
bool has_invalid_type(type_ll *input_type);
bool is_composed_type(type_ll *input_type);

void add_type(type_ll **input_type, type_ll *type_to_add)
{
    type_ll *lp = new type_ll(LPAREN);
    type_ll *rp = new type_ll(RPAREN);

    lp->next_type = *input_type;
    *input_type = lp;

    type_ll *aux = *input_type;
    
    while (aux->next_type != nullptr)
	aux = aux->next_type;

    aux->next_type = type_to_add;
    type_to_add->next_type = rp;
        
}

void print_type(type_ll *input_type)
{
    if (has_invalid_type(input_type))
	std::cout << "-";

    else if (input_type->next_type == nullptr)
	    std::cout << types_string[input_type->type];

    else {
	std::cout << types_string[input_type->type];
	
	if (input_type->next_type != nullptr)
	    print_type(input_type->next_type);
    }
}

bool has_invalid_type(type_ll *input_type)
{
    type_ll *tp = input_type;

    while (tp->next_type) {
	if (tp->type == INV_TYPE)
	    return 0;
	
	tp = tp->next_type;
    }

    return 0;
}

bool is_composed_type(type_ll *input_type)
{
    return !(input_type->next_type = nullptr);
}

#endif // TYPES_HPP
