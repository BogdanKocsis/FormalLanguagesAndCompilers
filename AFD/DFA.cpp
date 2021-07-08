#include "DFA.h"
#include <iostream>
#include <fstream>
#include <string>

void DFA::Read( std::string filename)
{
	std::ifstream inputFile(filename);

	int numberOfElements;
	inputFile >> numberOfElements;
	std::string state;
	for (int index = 0; index < numberOfElements; index++)
	{
		inputFile >> state;
		m_states.insert(state);
	}

	inputFile >> numberOfElements;
	char sigma;
	for (int index = 0; index < numberOfElements; index++)
	{
		inputFile >> sigma;
		m_sigma.insert(sigma);
	}

	inputFile >> m_delta;

	inputFile >> m_initialState;

	inputFile >> numberOfElements;
	for (int index = 0; index < numberOfElements; index++)
	{
		inputFile >> state;
		m_finals.insert(state);
	}

	char symbol;
	std::string startState, finalState;
	inputFile >> numberOfElements;
	for (int index = 0; index < numberOfElements; index++)
	{
		inputFile >> startState >> symbol >> finalState;
		Transition transition(startState, symbol, finalState);
		m_transition.push_back(transition);
	}

}

void DFA::Print()
{
	std::cout << "States: ";
	for (const auto& states : m_states)
	{
		std::cout << states << " ";
	}
	std::cout << std::endl;

	std::cout << "Sigma: ";
	for (const auto& sigma : m_sigma)
	{
		std::cout << sigma << " ";
	}
	std::cout << std::endl;

	//std::cout<<"Delta: "<<m_delta<<std::endl;

	std::cout << "Initial State: " << m_initialState << std::endl;

	std::cout << "Finals: ";
	for (const auto& finals : m_finals)
	{
		std::cout << finals << " ";
	}
	std::cout << std::endl;

	std::cout << "Transitions:\n";
	for (const auto& transition : m_transition)
	{
		std::cout << "( " << transition.GetStartState() << " , " << transition.GetSymbol() << " ) -> " << transition.GetFinalState() << std::endl;
	}
	std::cout << std::endl;

}

bool DFA::SomeChecks()
{

	if (std::find(m_states.begin(), m_states.end(), m_initialState) == m_states.end())
		return false;

	for (const auto& finals : m_finals)
		if (std::find(m_states.begin(), m_states.end(), finals) == m_states.end())
			return false;

	return true;
}

bool DFA::CheckWord(const std::string& word)
{
	for (int index = 0; index != word.size(); index++)
	{
		for (const auto& sigma : m_sigma)
			if (std::find(m_sigma.begin(), m_sigma.end(), word[index]) == m_sigma.end())
				return false;
	}
	return true;
}

bool DFA::Verification(std::string word)
{
	bool ok = true;
	std::string start = m_initialState;
	while (word.size())
	{
		for (const auto& transition : m_transition)
			if (transition.GetStartState() == start && transition.GetSymbol() == word[0])
			{
				start = transition.GetFinalState();
				word.erase(word.begin());
			}

		if (start == "-")
		{
			ok = false; //std::cout << "Blocaj"<<std::endl;
			break;
		}

	}
	if (ok == false)
	{
		std::cout << "Obstruction" << std::endl;
		return ok;
	}
	else {
		if (std::find(m_finals.begin(), m_finals.end(), start) != m_finals.end() && word.size() == 0)

		{
			std::cout << "Acceptable" << std::endl;
			return ok;
		}
		else
		{
			std::cout << "Unacceptable" << std::endl;
			return ok;
		}
	}



}
