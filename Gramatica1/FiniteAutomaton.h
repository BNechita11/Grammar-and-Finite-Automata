#pragma once
#include<set>
#include<iostream>
#include<map>

class FiniteAutomaton {
public:
    FiniteAutomaton(std::set<char> states, std::set<char> alphabet,
        std::map<std::pair<char, char>, std::set<char>> transitions,
        char initial_state, std::set<char>finalStates);

    bool VerifyAutomaton() const;
    void PrintAutomaton() const;
    bool CheckWord(const std::string& word) const;
    bool IsDeterministic() const;

private:
    std::set<char> m_states; 
    std::set<char> m_alphabet; 
    std::set<char>m_finalStates;
    std::map<std::pair<char, char>, std::set<char>> m_transition; 
    char m_initialState; 
    char m_lambda = '~';
};
