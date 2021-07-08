#pragma once
#include<string>
class Transition
{
public:
	Transition(char startState, char symbol, char finalState);
	~Transition() = default;

	char GetStartState() const;
	char GetFinalState() const;
	char GetSymbol() const;

private:

	char m_startState;
	char  m_finalState;
	char m_symbol;

};

