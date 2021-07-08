#pragma once
#include<string>
class Transition
{
public:
	Transition(const std::string& startState, char symbol, const std::string& finalState);
	~Transition() = default;

	std::string GetStartState() const;
	std::string GetFinalState() const;
	void SetFinalState(std::string state);

	char GetSymbol() const;

private:

	std::string m_startState;
	std::string m_finalState;
	char m_symbol;

};

