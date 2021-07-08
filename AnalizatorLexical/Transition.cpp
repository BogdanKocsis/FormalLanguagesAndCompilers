#include "Transition.h"

Transition::Transition(char startState, char symbol, char finalState):m_startState(startState),m_symbol(symbol),m_finalState(finalState)
{
}

char Transition::GetStartState() const
{
	return m_startState;
	
}

char Transition::GetFinalState() const
{
	return m_finalState;
}

char Transition::GetSymbol() const
{
	return m_symbol;
}
