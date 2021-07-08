#include "Transition.h"

Transition::Transition(const std::string& startState, char symbol, const std::string& finalState) :m_startState(startState), m_symbol(symbol), m_finalState(finalState)
{
}

std::string Transition::GetStartState() const
{
	return m_startState;

}

std::string Transition::GetFinalState() const
{
	return m_finalState;
}

char Transition::GetSymbol() const
{
	return m_symbol;
}
