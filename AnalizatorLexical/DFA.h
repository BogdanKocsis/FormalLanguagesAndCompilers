#pragma once
#include"Transition.h"
#include <vector>
#include<set>
class DFA
{

public:
	DFA() = default;
	~DFA() = default;

	void Read(const std::string& filename);
	void Print();
	bool SomeChecks();
	bool CheckWord(const std::string& word);
	bool Verification( std::string word);



private:
	std::set<char> m_states;
	std::set<char> m_sigma;
	char m_delta;
	char m_initialState;
	std::set<char> m_finals;
	std::vector<Transition> m_transition;
};

