#include "components.hpp"

/* operator<< overloads */
std::ostream& operator<<(std::ostream& os, Alphabet& a){
    for (char symbol : a.get_symbols())
        os << symbol << " ";
    return os;
}
std::ostream& operator<<(std::ostream& os, const Rule& r){
    os <<  r.initial_state << " " << r.symbol <<" " <<  r.final_state;
        return os;
}
std::ostream& operator<<(std::ostream& os, TransitionTable& t){
    for (Rule rule : t.rules) {
        os << rule << std::endl;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const ComputationBranch& c){
    for (int i = 0; i < static_cast<int>(c.config_history.size()); i++) {
        std::pair<std::string,std::string> config = c.config_history[i];
        if(i!=0){
            os << " :- ";
        }
        os << "("<<config.first << ", " << (config.second.empty() ? "e" : config.second) << ")";
    }
    return os;
}


/* Alphabet */
bool Alphabet::is_valid(const std::string& input) const {
    for (char c : input) {
        if (symbols.find(c) == symbols.end())
            return false;
    }
    return true;
}

const std::set<char> Alphabet::get_symbols() const {
    return symbols;
}


Alphabet& Alphabet::operator+=(const Alphabet& other) {
    for (char symbol : other.symbols)
        symbols.insert(symbol);
    return *this;
}

/* Rule */
Rule::Rule(const std::string& init_s, char symbol, const std::string& final_s){
    initial_state = init_s;
    this->symbol = symbol;
    final_state = final_s;
}

const std::string Rule::get_final_state() const {
    return final_state;
}

/*const std::string Rule::get_initial_state() const {
    return initial_state;
}

const char Rule::get_symbol() const {
    return symbol;
}*/

void Rule::update_state_name(const std::string& old_name, const std::string& new_name){
    if(initial_state == old_name){
        initial_state = new_name;
    }
    if(final_state == old_name){
        final_state = new_name;
    }
}

bool Rule::applies_to(const std::string& c, char s) const{
    if(initial_state == c && symbol == s){
        return true;
    }
    return false;
}

/*bool isEqualRule(Rule a,Rule b){
    if(a.get_final_state() == b.get_final_state() && a.get_initial_state() == b.get_initial_state() && a.get_symbol() == b.get_symbol()){
        return true;
    }
    return false;
}*/


/* TransitionTable */
void TransitionTable::add_rule(const std::string& initial_state, char symbol, const std::string& final_state){
    Rule a = Rule(initial_state,symbol,final_state);
   /* bool isAv = 0;
    for(Rule b : rules){
        if(isEqualRule(a,b)){
            isAv = 1;
            break;
        }
    }
    if(isAv == 0)*/
        rules.push_back(a);
    
}

void TransitionTable::update_state_name(const std::string& old_name, const std::string& new_name){
    for(int i=0 ; i<rules.size();i++){
        rules[i].update_state_name(old_name,new_name);
    }
}

const std::set<std::string> TransitionTable::operator()(const std::string& curr_state, char symbol) const{
    std::set<std::string> next_states;
    for(Rule a:rules){
        if(a.applies_to(curr_state,symbol)){
            next_states.insert(a.get_final_state());
        }
    }
    return next_states;
}


TransitionTable& TransitionTable::operator+=(const TransitionTable& other){
    for(Rule a: other.rules){
        rules.push_back(a);
        /*int isAv = 0;
        for(Rule b:rules){
            if(isEqualRule(a,b)){
                isAv = 1;
                break;
            }
        }
        if(isAv == 0){
            rules.push_back(a);
        }*/
    }
    return *this;
}


/* ComputationBranch */
void ComputationBranch::push_config(const std::string& state, const std::string& input){
    std::pair<std::string,std::string> newConfig = std::make_pair(state,input);
    config_history.push_back(newConfig);
}

const std::pair<std::string,std::string> ComputationBranch::get_last_config() const{
    if (!config_history.empty()) {
        return config_history.back();
    } else {
        // Return an empty configuration if history is empty
        return std::make_pair("", "");
    }
}