#include <iostream>

#include "types.hpp"

int main()
{
    // type_ll *t1 = new type_ll(NAT);
    // type_ll *t2 = new type_ll(BOOL);
    // type_ll *t3 = new type_ll(NAT);
    // type_ll *t4 = new type_ll(NAT);
    // type_ll *t5 = new type_ll(BOOL);
    // type_ll *t6 = new type_ll(NAT);

    // add_type(&t1, t2);
    // add_type(&t1, t3);
    // add_type(&t4, t5);
    // add_type(&t1, t4);
    // add_type(&t1, t6);

    type_ll *t1 = new type_ll("( ( Nat -> Bool ) -> ( Nat -> Bool ) )");
    
    print_type(t1);

    std::cout << '\n';
    
    return 0;
}
