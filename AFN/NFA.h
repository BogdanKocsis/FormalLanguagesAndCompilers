#pragma once
#include "Transition.h"
#include<vector>
#include <string>
#include <set>

class NFA
{

public:
	NFA() = default;
	~NFA() = default;

	void Read();
	void Print();
	bool SomeChecks();
	bool CheckWord(const std::string& word);
	bool CheckIfContainsOnlyTerminals(std::vector<std::string > start);
	//bool CheckIfContainsOnlyTerminals(std::vector<std::string > start);
	void Verification(std::string word);

private:
	std::set<std::string> m_states;
	std::set<char> m_sigma;
	char m_delta;
	std::string m_initialState;
	std::set<std::string> m_finals;
	std::vector<Transition> m_transition;

};

