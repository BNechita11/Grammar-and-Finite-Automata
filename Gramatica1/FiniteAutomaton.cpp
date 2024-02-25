#include "FiniteAutomaton.h"
#include<vector>


FiniteAutomaton::FiniteAutomaton(std::set<char> states, std::set<char> alphabet,
	std::map<std::pair<char, char>, std::set<char>> transitions,
	char initial_state, std::set<char>finalStates)
	: m_states(states), m_alphabet(alphabet), m_transition(transitions),
	m_initialState(initial_state), m_finalStates(finalStates) {}

//  std::map<std::pair<char, char>, std::set<char>> m_transition; 


bool FiniteAutomaton::CheckWord(const std::string& word) const {
	std::vector<char> currentStates = { m_initialState };
	for (char symbol : word) {
		//std::set<char> nextStates;
		std::vector<char> nextState;
		for (char currentState : currentStates) {
			auto transition = std::make_pair(currentState, symbol);
			if (m_transition.find(transition) != m_transition.end()) {
				auto it = m_transition.find(transition);
				if (it != m_transition.end()) {
					//nextStates.insert(it->second.begin(), it->second.end());
					
					for (const auto& aux : it->second)
					{
						nextState.push_back(aux);
					}
				}
			}
		}
		currentStates.clear();
		currentStates = nextState;
	}

	for (char currentState : currentStates) {
		if (m_finalStates.find(currentState) != m_finalStates.end()) {
			return true;
		}
	}

	return false;
}


bool FiniteAutomaton::IsDeterministic() const  
{
	std::set<std::pair<int, char>> seenTransitions;
	for (const auto& transition : m_transition) {
		for (char nextState : transition.second) {
			if (seenTransitions.find({ transition.first.first, transition.first.second }) !=
				seenTransitions.end()) {
				std::cout<< "Eroare: Automatul nu este determinist.S-a gasit o tranzitie cu acelasi simbol.\n";
				return false;
			}
			seenTransitions.insert({ transition.first.first, transition.first.second });
		}
		
	}

	if (m_states.find(m_initialState) == m_states.end()) {
		std::cout<< "Eroare: Starea initiala nu este in multimea starilor.\n";
		return false;
	}

	return true;
}


bool FiniteAutomaton::VerifyAutomaton() const
{
	if (m_states.empty() || m_alphabet.empty() || m_initialState == ' ' || m_finalStates.empty() || m_transition.empty())
	{
		std::cout<<"Eroare: Automat incomplet sau gol.\n";
		return false;
	}

	if (m_states.find(m_initialState) == m_states.end()) {
		std::cout<< "Eroare:Starea initiala nu se afla in setul de date.\n";
		return false;
	}

	for (const auto& transition : m_transition) {
		char currentState = transition.first.first;
		char symbol = transition.first.second;
		for (char nextState : transition.second) {
			if (m_states.find(currentState) == m_states.end() ||
				m_states.find(nextState) == m_states.end() ||
				m_alphabet.find(symbol) == m_alphabet.end()) {
				std::cout << "Eroare:Tranzitie invalida gasita.\n";
				return false;
			}
		}
	}
	for (char state : m_states) {
		if (m_alphabet.find(state) != m_alphabet.end()) {
			std::cout << "Eroare: Starea " << state << " se intersecteaza cu alfabetul.\n";
			return false;
		}
	}

	return true;
}


void FiniteAutomaton::PrintAutomaton() const
{
	std::cout << "Stari: { ";
	for (char state : m_states) {
		std::cout << state << " ";
	}
	std::cout << "}\n";

	std::cout << "Alfabet: { ";
	for (char symbol : m_alphabet) {
		std::cout << symbol << " ";
	}
	std::cout << "}\n";

	std::cout << "Tranzitii:\n{\n";
	for (const auto& transition : m_transition) {
		std::cout << "   (" << transition.first.first << ", " << transition.first.second << ") -> { ";
		for (char nextState : transition.second) {
			std::cout << nextState << " ";
		}
		std::cout << "}\n";
	}
	std::cout << "}\n";
	std::cout << "Stare initiala: " << m_initialState << "\n";

	std::cout << "Stari finale: ";
	for (char finalState : m_finalStates) {
		std::cout << finalState << " ";
	}
}


