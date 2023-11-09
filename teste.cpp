#include <iostream>

int is_nat(const char *input_str)
{
    int is_nat = 1;
    
    while (*input_str != '\0')
        if (!isdigit(*(input_str++)))
            is_nat = 0;
    
    return is_nat;
}

int main() {
    std::cout << is_nat("999897385738454398");

    return 0;
}
