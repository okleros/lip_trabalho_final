#include <iostream>

enum TypeType {
    NAT,
    BOOL
};

const char *types_string[2] = {"Nat", "Bool"};

struct type_ll
{
    TypeType type;
    type_ll *next_type;

    type_ll(TypeType tp) : type(tp), next_type(nullptr) {};
    
};

void add_type(type_ll *input_type, type_ll *type_to_add)
{
    while (input_type->next_type != nullptr)
	input_type++;

    input_type->next_type = type_to_add;   
}

void print_type(type_ll *input_type)
{
    if (input_type->next_type == nullptr) {
	std::cout << types_string[input_type->type];
    } else {
	std::cout << "( " << types_string[input_type->type] << " -> ";
	print_type(input_type->next_type);
	std::cout << " )";
    }
    
}

int main()
{
    type_ll t1(NAT);
    type_ll t2(BOOL);
    type_ll t3(NAT);
    type_ll t4(NAT);
    type_ll t5(BOOL);
    type_ll t6(NAT);

    add_type(&t1, &t2);
    add_type(&t3, &t4);
    add_type(&t5, &t6);
    add_type(&t1, &t3);
    add_type(&t1, &t5);

    print_type(&t1);
    std::cout << '\n';
    
    return 0;
}
