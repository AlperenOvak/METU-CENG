#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <queue>

//#include "nfa.hpp"

// this file is for testing purposes; it will be discarded during grading

using namespace std;

std::vector<std::string> parse_line(const std::string& line, const char delimiter)
{
    std::vector<std::string> res;
    std::string parsed;
    std::istringstream ss(line);
    while(std::getline(ss, parsed, delimiter))
        res.push_back(parsed);
    return res;
}

class Alphabet
{
private:
    std::set<char> symbols;

public:
    void init_from_line(std::string line){
        std::vector<std::string> parseds = parse_line(line, ' ');
        for (std::string symbol : parseds)
            this->symbols.insert(symbol[0]);
    }
    bool is_valid(const std::string& input) const;
    const std::set<char> get_symbols() const;

    Alphabet& operator+=(const Alphabet& other);
    friend std::ostream& operator<<(std::ostream& os, Alphabet& a);
};


class Rule
{
private:
    std::string initial_state;
    char symbol;
    std::string final_state;

public:
    Rule() = delete;
    Rule(const Rule&) = default;
    Rule(const std::string& init_s, char symbol, const std::string& final_s);

    const std::string get_final_state() const;
    bool applies_to(const std::string& init_state, char symbol) const;
    void update_state_name(const std::string& old_name, const std::string& new_name);
    friend std::ostream& operator<<(std::ostream& os, const Rule& r);
};


class TransitionTable
{
private:
    std::vector<Rule> rules;

public:
    void init_from_stream(std::ifstream& config_file){
        std::string line;
        std::vector<std::string> parsed;
        while(std::getline(config_file, line)){
            parsed = parse_line(line, ' ');
            add_rule(parsed[0], parsed[1][0], parsed[2]);
        }
    }
    void add_rule(const std::string& initial_state, char symbol, const std::string& final_state);
    void update_state_name(const std::string& old_name, const std::string& new_name);
    const std::set<std::string> operator()(const std::string& curr_state, char symbol) const;
    TransitionTable& operator+=(const TransitionTable& other);
    friend std::ostream& operator<<(std::ostream& os, TransitionTable& t);
};


class ComputationBranch{
private:
    std::vector<std::pair<std::string,std::string>> config_history;

public:
    ComputationBranch() {};
    ComputationBranch(const ComputationBranch& other) = default;
    ComputationBranch(std::string state, std::string input) {
        // use make_pair(x,y) to create a variable of type pair<std::string,std::string>
        config_history.push_back(std::make_pair(state, input));
    }
    ComputationBranch& operator=(const ComputationBranch& other) = default;
    ComputationBranch(ComputationBranch&& other) = default; // be careful when using move
    ComputationBranch& operator=(ComputationBranch&& other) = default;

    void push_config(const std::string& state, const std::string& input);
    const std::pair<std::string,std::string> get_last_config() const;
    friend std::ostream& operator<<(std::ostream& os, const ComputationBranch& c);
};


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
    for(Rule a: rules){
        a.update_state_name(old_name,new_name);
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


class NFA
{
private:
    std::set<std::string> all_states;
    Alphabet alphabet;
    TransitionTable transitions;
    std::string starting_state;
    std::set<std::string> final_states;
    bool has_state(const std::string& state) const;
    bool is_final_state(const std::string& state) const;

public:
    NFA() = default;
    NFA(const NFA& other) = default;
    NFA& operator=(const NFA& other) = default;

    // you do not have to worry about reading inputs
    // all test cases will be compatible with the below
    NFA(const std::string filename) 
    {
        std::string line;
        std::ifstream config_file(filename);
        if (!config_file.is_open()){
            std::cout << "cannot open the file (wrong file path?)" << std::endl;
            return;
        }
        std::getline(config_file, line); // read the symbols
        this->alphabet.init_from_line(line);

        std::getline(config_file, line); // read all states
        std::vector<std::string> states = parse_line(line, ' ');
        for (const std::string& state: states)
            this->all_states.insert(state);

        std::getline(config_file, line); // read the starting state
        this->starting_state = line;

        std::getline(config_file, line); // read the final states
        states = parse_line(line, ' ');
        for (const std::string& state: states)
            this->final_states.insert(state);

        this->transitions.init_from_stream(config_file);

        config_file.close();
    }
    bool is_DFA() const;
    void update_state_name(const std::string& old_name, const std::string& new_name);
    bool process(std::string input);

    NFA operator!() const;
    NFA operator+(const NFA& other) const;
    friend std::ostream& operator<<(std::ostream& os, NFA& nfa){
        bool first = true;
        os << nfa.alphabet << std::endl;
        // all states
        for (auto it=nfa.all_states.begin(); it != nfa.all_states.end(); it++){
            if (first) {
                os << *it;
                first = false;
            }
            else
                os << " " << *it;
        }
        os << std::endl;
        os << nfa.starting_state << std::endl;
        // final states
        first = true;
        for (auto it=nfa.final_states.begin(); it != nfa.final_states.end(); it++){
            if (first) {
                os << *it;
                first = false;
            }
            else
                os << " " << *it;
        }
        os << std::endl;
        os << nfa.transitions;
        return os;
    }
};

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
    
    if(!alphabet.is_valid(input)){
        std::cout<<"Invalid string\n";
        return false;
    }
    std::string inputt = input;
    std::queue<ComputationBranch> Q;
    ComputationBranch newbranch = ComputationBranch(starting_state,input);
    Q.push(ComputationBranch(starting_state,input));

    while (!Q.empty()) {
        ComputationBranch branch = Q.front();
        Q.pop();

        if (branch.get_last_config().second == "" && is_final_state(branch.get_last_config().first)) {
            std::cout << branch << std::endl;
            std::cout << "Accept" << std::endl;
            return true;
        }


        std::string current_state = branch.get_last_config().first;
        std::string current_inpt = branch.get_last_config().second;

        //go with e 
        std::set<std::string> nextSWithE = transitions(current_state,'e');
        for(std::string emptpNext : nextSWithE){
            ComputationBranch newbranchh = branch;
            newbranchh.push_config(emptpNext,current_inpt);
            Q.push(newbranchh);
        }

        //go with a char
        if(current_inpt != ""){
                nextSWithE = transitions(current_state,current_inpt[0]);
            for(std::string charNext : nextSWithE){
                ComputationBranch newbranchh = branch;
                newbranchh.push_config(charNext,current_inpt.substr(1));
                Q.push(newbranchh);
            }
            
        }

        newbranch = branch;
    }
    std::cout << newbranch <<std::endl;
    std::cout << "Reject" << std::endl;
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

template <typename T>
void printSet(const std::set<T>& mySet) {
    std::cout << "Set elements: ";
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

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