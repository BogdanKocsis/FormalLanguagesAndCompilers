#pragma once
#include<string>
class Transition
{
public:
	Transition(std::string startState, char symbol, std::string finalState);
	~Transition() = default;

	std::string GetStartState() const;
	std::string GetFinalState() const;
	char GetSymbol() const;

private:

	std::string m_startState;
	std::string  m_finalState;
	char  m_symbol;

};

