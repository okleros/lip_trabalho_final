#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>

enum TypeType {
    NAT,
    BOOL,
    INV_TYPE,
};

const char *types_string[2] = {"Nat", "Bool"};

struct type_ll
{
    TypeType type;
    type_ll *next_type;

    type_ll(TypeType tp) : type(tp), next_type(nullptr) {};
    
};

struct var_type
{
    type_ll type;
    char var_name[32];
};

void add_type(type_ll *input_type, type_ll *type_to_add);
void print_type(type_ll *input_type);
bool has_invalid_type(type_ll *input_type);

void add_type(type_ll *input_type, type_ll *type_to_add)
{
    while (input_type->next_type != nullptr)
	input_type++;

    input_type->next_type = type_to_add;   
}

void print_type(type_ll *input_type)
{
    if (has_invalid_type(input_type)) std::cout << "-";
    
    if (input_type->next_type == nullptr) {
	std::cout << types_string[input_type->type];

    } else {
	std::cout << "( " << types_string[input_type->type] << " -> ";
	print_type(input_type->next_type);
	std::cout << " )";
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

#endif // TYPES_HPP
