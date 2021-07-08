#pragma once
#include"Transition.h"
#include <vector>
#include<set>
class DFA
{

public:
	DFA() = default;
	~DFA() = default;

	void Read(std::string filename);
	void Print();
	bool SomeChecks();
	bool CheckWord(const std::string& word);
	bool Verification( std::string word);


private:
	std::set<std::string> m_states;
	std::set<char> m_sigma;
	char m_delta;
	std::string m_initialState;
	std::set<std::string> m_finals;
	std::vector<Transition> m_transition;
};

