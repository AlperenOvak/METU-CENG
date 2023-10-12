#include <iostream>

namespace glb_var{
    int year = 2023;
    int old = 21;
}

int year = 2025;

int main(){
    int year = 2002;
    std::cout << glb_var::year << " " << ::year << " " << year << std::endl;
    /*
    glb_var:: --> 2023
    ::year    --> 2025  (global)
    year      --> 2002  (local)
    
    */

    return 0;
}