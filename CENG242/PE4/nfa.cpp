#include "nfa.hpp"

// private:
bool NFA::has_state(const std::string& state) const{
    return all_states.find(state) != all_states.end();
}

bool NFA::is_final_state(const std::string& state) const{
    return final_states.find(state) != final_states.end();
}

// public:
bool NFA::is_DFA() const{
    const std::set<char> alp = alphabet.get_symbols();
    if(alp.find('e')!=alp.end()){
        return false;
    }
    for(const std::string& state : all_states){
        for(char symb : alphabet.get_symbols()){
            std::set<std::string> nextS = transitions(state,symb);
            int pathNum = nextS.size();
            if(pathNum == 0 || pathNum > 1){
                return false;
            }
        }
    }
    return true;
}

void NFA::update_state_name(const std::string& old_name, const std::string& new_name){
    if (all_states.find(old_name) != all_states.end()) {
        all_states.erase(old_name);
        all_states.insert(new_name);
    }
    if (starting_state == old_name) {
        starting_state = new_name;
    }
    if (final_states.find(old_name) != final_states.end()) {
        final_states.erase(old_name);
        final_states.insert(new_name);
    }

    // Step 2: Invoke the update_state_name function on the transitions object
    transitions.update_state_name(old_name, new_name);
}

bool NFA::process(std::string input){
    
    return false;
}
    
NFA NFA::operator!() const{
    if(is_DFA()){
        NFA complement_NFA = *this; // Copy current NFA

        // Replace the set of final states with the set of non-final states
        std::set<std::string> non_final_states;
        for (const std::string& state : all_states) {
            if (!is_final_state(state)) {
                non_final_states.insert(state);
            }
        }
        complement_NFA.final_states = non_final_states;

        return complement_NFA;
    }else{
        std::cout << "Not a DFA" << std::endl;
        return *this;
    }
}

NFA NFA::operator+(const NFA& other) const{
        NFA result = *this;
    NFA othercopy = other;
    result.alphabet += othercopy.alphabet;//concatenate the alphabets
    for(std::string stateOther : othercopy.all_states){
        while(has_state(stateOther)){
           std::string newStateName ="q" + stateOther;
           othercopy.update_state_name(stateOther,newStateName);
           stateOther = newStateName;
        }
    }//add q at the beginning of the same states in other NFA.
    for (std::string state : othercopy.all_states)
        result.all_states.insert(state);

    for (std::string state : othercopy.final_states){
        result.final_states.insert(state);
    }

    std::string startState = "s";
    while(has_state(startState)){
        startState ="s" + startState;
    }
    while(othercopy.has_state(startState)){
        startState ="s" + startState;
    }
    
    result.starting_state = startState; //set the start state
    result.all_states.insert(startState); // add new start state to state list
    //concatenate trasisions
    result.transitions += othercopy.transitions;
    result.transitions.add_rule(startState,'e',starting_state);
    result.transitions.add_rule(startState,'e',othercopy.starting_state);


    return result;
}