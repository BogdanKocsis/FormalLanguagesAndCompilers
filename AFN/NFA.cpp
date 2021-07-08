#include "NFA.h"
#include <iostream>
#include <fstream>

void NFA::Read()
{
	std::ifstream inputFile("inputNFA.txt");

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

void NFA::Print()
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

bool NFA::SomeChecks()
{

	if (std::find(m_states.begin(), m_states.end(), m_initialState) == m_states.end())
		return false;

	for (const auto& finals : m_finals)
		if (std::find(m_states.begin(), m_states.end(), finals) == m_states.end())
			return false;

	return true;
}

bool NFA::CheckWord(const std::string& word)
{
	for (int index = 0; index != word.size(); index++)
	{
		for (const auto& sigma : m_sigma)
			if (std::find(m_sigma.begin(), m_sigma.end(), word[index]) == m_sigma.end())
				return false;
	}
	return true;
}

bool NFA::CheckIfContainsOnlyTerminals(std::vector<std::string> start)
{
	for (const auto& begin : start)
	{

		if ((std::find(m_finals.begin(), m_finals.end(), begin)) == m_finals.end())
		{
			return false;
		}
	}
	return true;
}


void NFA::Verification(std::string word)
{
	bool ok = true;
	std::vector<std::string> start;
	start.push_back(m_initialState);
	int x;
	while (word.size())
	{
		x = start.size();
		for (auto begin : start)
		{
			
			for (const auto& transition : m_transition)
			{

				if (transition.GetStartState() == begin && transition.GetSymbol() == word[0])
				{
					start.push_back(transition.GetFinalState());

				}
			}
		}
		word.erase(word.begin());
		for (int index = 0; index < x; index++)
		{
			start.erase(start.begin());
		}

		if (std::find(start.begin(), start.end(), "-") != start.end())
		{
			ok = false;
			break;
		}

	}



if (ok == 0 && word.size() > 0)
std::cout << "Obstruction" << std::endl;
else
if (CheckIfContainsOnlyTerminals(start) && word.size() == 0)
{
	std::cout << "Acceptable" << std::endl;
}
else
std::cout << "Unacceptable" << std::endl;

}