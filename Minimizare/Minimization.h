#pragma once
#include "Transition.h"
#include "DFA.h"
#include<vector>
#include <string>
#include <queue>

class Minimization
{

public:
	Minimization() = default;
	~Minimization() = default;
	std::vector<std::vector<std::string>> MakeList();
	void BFS(std::vector<std::vector<std::string>> list);
	void RemoveInaccessibleItems(std::vector<Transition>& m_transition, std::set<std::string>& m_states);
	std::vector<std::vector<std::string>> CreateMatrix(std::set<std::string> states);
	void MarkNonFinalWithFinal(std::vector<std::vector<std::string>>& statesMatrix, std::set<std::string> m_finals);
	void VerifyUnmarkedPairs(std::vector<std::vector<std::string>>& statesMatrix, std::set<char> m_sigma, std::vector<Transition> m_transition, std::set<std::string> states);
	std::vector<std::set<std::string>> makePairs(std::vector<std::vector<std::string>> statesMatrix);
	void Verification(std::vector<std::set<std::string>> sets, std::string word);
	void MakeMinDFA(DFA dfa, std::vector<std::set<std::string>> sets);
	void Test(DFA dfa, std::string word);


private:

	std::queue<int> q;
	std::vector<bool> used{ false };
	std::vector<int> d, p;
	std::vector<std::vector<std::string>>  statesMatrix;
	std::vector<std::set<std::string>> sets;
	std::set<char> min_sigma;
	std::set<std::string> min_states;
	std::string min_initialState;
	std::vector<Transition> min_transition;
	std::set<std::string> min_finals;
	std::vector<std::pair<std::string, std::string>> pairs;

};

