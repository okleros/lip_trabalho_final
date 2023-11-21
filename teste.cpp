#include <iostream>

#include "types.hpp"

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
