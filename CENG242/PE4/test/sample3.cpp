#include <iostream>
#include "nfa.hpp"

using namespace std;

int main(){
    NFA M1("dfa1.inp");
    NFA M2("nfa1.inp");
    NFA M = !M1 + M2;

    M.process("aabbbab");
    M.process("aabbbbaaaaab");
    M.process("baabbbaaaaab");
    M.process("bbbaa");

    return 0;
}
