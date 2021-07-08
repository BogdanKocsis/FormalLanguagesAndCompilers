#pragma once
#include"Transition.h"
#include <vector>
#include<set>
class DFA
{

public:
	DFA() = default;
	~DFA() = default;

	void Read();
	void Print();
	bool SomeChecks();
	bool CheckWord(const std::string& word);
	void Verification(std::string word);
	std::string GetInitialState() const;
	std::set<char> GetSigma() const;
	std::set<std::string> GetStates() const;
	std::vector<Transition> GetTransition() const;
	std::set<std::string> GetFinals() const;

private:

	//std::set<char> m_sigma;
	char m_delta;
	//std::string m_initialState;
	

public:

	std::set<char> m_sigma;
	std::set<std::string> m_states;
	std::string m_initialState; //de facut geterii pentru astea trei
	std::vector<Transition> m_transition;
	std::set<std::string> m_finals;
};

