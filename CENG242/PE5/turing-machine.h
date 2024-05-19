#pragma once
#include "turing-machine_utils.h"

// Type trait to check if two types are the same
template <typename A, typename B> 
struct is_same { 
    static constexpr auto value = false; 
};

template <typename A> 
struct is_same<A, A> { 
    static constexpr auto value = true; 
};

// EnableIf utility for SFINAE (Substitution Failure Is Not An Error)
template <bool C, typename = void> 
struct EnableIf;

template <typename Type> 
struct EnableIf<true, Type> { 
    using type = Type; 
};

// Lambda template to match rules
template <typename Rule, typename OldState, typename Input>
struct lamda {
    static constexpr auto value = (is_same<OldState, typename Rule::OldState>::value && 
                                   is_same<Input, typename Rule::Input>::value);
};

// TransitionFunction template for processing transitions
template <typename Config, typename Transitions, typename = void>
struct TransitionFunction {
    // Filter the rules based on the current configuration
    template <typename Rule>
    struct lamda_rule {
        static constexpr auto value = (is_same<typename Config::state, typename Rule::old_state>::value && 
                                       is_same<typename Config::input_tape::template at<Config::position>, typename Rule::input>::value);
    };
    
    template<int N>
    struct IntWrapper {
        static constexpr int value = N;
    };

    using filtered = typename Filter<lamda_rule, List<>, Transitions>::type;
    using FRule = Rule<typename Config::state, typename Config::input_tape::template at<Config::position>, QReject, typename Config::input_tape::template at<Config::position>, STOP>;
    using chosenRule = typename cond<(Size<filtered>::value == 0), FRule,typename filtered::template at<0>>::type;
    
    using curr_input = typename Replace<typename chosenRule::output, Config::position, typename Config::input_tape>::type;

    using blank_left = typename cond<(Config::position == 0 && chosenRule::direction == -1),
                                    typename Prepend<Input<-1>, curr_input>::type, curr_input>::type;
    using updated_position = IntWrapper<Config::position + chosenRule::direction>;                          
    using final_position = typename cond< ( Config::position == 0 && chosenRule::direction == -1), IntWrapper<Config::position> , updated_position>::type;                             
                                    
    using blank_right = typename cond<(Config::position == Size<blank_left>::value -1 && chosenRule::direction == 1),
                                    typename Append<Input<-1>, curr_input>::type, curr_input>::type;
    
    using curr_state =  typename chosenRule::new_state;
    using curr_config = Configuration<blank_right, curr_state, final_position::value>;


    using curr_trans = TransitionFunction<curr_config, Transitions>;

    using end_config = typename curr_trans::end_config;
    using end_input = typename curr_trans::end_input;
    using end_state = typename curr_trans::end_state;
    static constexpr auto end_position = curr_trans::end_position /*+ chosenRule::direction*/;

};

// Specialization for accepting or rejecting state
template <typename InputTape, typename State, int Position, typename Transitions>
struct TransitionFunction<Configuration<InputTape, State, Position>, Transitions,
                          typename EnableIf<is_same<State, QAccept>::value || 
                                            is_same<State, QReject>::value>::type> {
    using end_config = Configuration<InputTape, State, Position>;
    using end_input = InputTape;
    using end_state = State;
    static constexpr auto end_position = Position;
};
