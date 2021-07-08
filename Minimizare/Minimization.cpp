#include "Minimization.h"
#include <iostream>
#include <fstream>

std::vector<std::vector<std::string>> Minimization::MakeList()
{
	std::vector<std::vector<std::string>> list;

	list.resize(min_states.size());
	for (int index = 0; index < min_states.size(); index++)
	{

		for (const auto& transition : min_transition)
		{
			std::set<std::string>::iterator iter = min_states.begin();
			std::advance(iter, index);
			if (transition.GetStartState() == *iter)
				list[index].push_back(transition.GetFinalState());
		}

	}

	//afisare
	/*for (int index = 0; index < list.size(); index++)
	{

		for (int index1 = 0; index1 < list[index].size(); index1++)
			std::cout << list[index][index1] << " ";
		std::cout << "\n";
	}*/
	return list;
}

void Minimization::BFS(std::vector<std::vector<std::string>> list)
{

	//cautam positia startului pentru ca am nevoie de int
	//getter pentru initial state

	auto it = min_states.find(min_initialState);
	int start = std::distance(min_states.begin(), it);
	used.resize(min_states.size());
	p.resize(min_states.size());
	d.resize(min_states.size());
	q.push(start);
	used[start] = true;
	p[start] = -1;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (std::string index : list[v]) {
			auto it = min_states.find(index);
			int position = std::distance(min_states.begin(), it);
			if (!used[position])
			{
				used[position] = true;
				q.push(position);
				d[position] = d[v] + 1;
				p[position] = v + 1;

			}

		}

	}
	//afisare predecesori
	//for (const auto& index : p)
	//	std::cout << index << " ";
	//std::cout << "\n";

}

void Minimization::RemoveInaccessibleItems(std::vector<Transition>& m_transition, std::set<std::string>& m_states)
{

	int position;
	for (int index = 0; index < p.size(); index++)
	{
		if (p[index] == 0)
		{
			std::set<std::string>::iterator it = m_states.begin();
			for (int i = 0; i < index; i++)
				++it;
			std::string copy = *it;
			m_states.erase(*it);

			std::vector<Transition>::iterator it2 = m_transition.begin();

			while (it2 != m_transition.end())
			{

				if ((*it2).GetStartState() == copy)
				{

					it2 = m_transition.erase(it2);
				}
				else
					++it2;

			}

		}

	}
	/*for (auto index : dfa.m_states)
		std::cout << index;*/

}

std::vector<std::vector<std::string>> Minimization::CreateMatrix(std::set<std::string> states)
{
	std::vector<std::vector<std::string>> statesMatrix(states.size(), std::vector<std::string>(states.size(), "0"));

	std::set<std::string>::iterator it = states.begin();;
	for (int index = 0; index < states.size(); index++)
	{
		statesMatrix[index][index] = (*it++);

	}

	return statesMatrix;

}

void Minimization::MarkNonFinalWithFinal(std::vector<std::vector<std::string>>& statesMatrix, std::set<std::string> m_finals)
{

	for (int index = 0; index < statesMatrix.size(); index++)
	{
		for (int index1 = 0; index1 < statesMatrix[index].size(); index1++)
		{
			auto result1 = std::find(m_finals.begin(), m_finals.end(), std::to_string(index + 1));
			auto result2 = std::find(m_finals.begin(), m_finals.end(), std::to_string(index1 + 1));
			if ((result1 != m_finals.end() && result2 == m_finals.end()) || (result1 == m_finals.end() && result2 != m_finals.end()))
			{
				statesMatrix[index1][index] = "X";
			}
		}

	}



}

void Minimization::VerifyUnmarkedPairs(std::vector<std::vector<std::string>>& statesMatrix, std::set<char> m_sigma, std::vector<Transition> m_transition, std::set<std::string> states)
{
	bool ok = 1;

	while (ok)
	{
		ok = false;
		for (int index = 0; index < statesMatrix.size(); index++)
		{

			for (int index1 = 0; index1 < statesMatrix[index].size(); index1++)
			{
				if (statesMatrix[index1][index] == "0")
				{
					for (const auto& symbol : m_sigma)
					{
						int result1, result2;

						std::vector<Transition>::iterator it2 = m_transition.begin();
						std::vector<Transition>::iterator it3 = m_transition.begin();

						while (it2 != m_transition.end())
						{

							if ((*it2).GetStartState() == std::to_string(index + 1) && (*it2).GetSymbol() == symbol)
							{

								auto position = std::find(states.begin(), states.end(), (*it2).GetFinalState());
								result1 = std::distance(states.begin(), position);
								break;
							}

							else
								++it2;

						}
						while (it3 != m_transition.end())
						{

							if ((*it3).GetStartState() == std::to_string(index1 + 1) && (*it3).GetSymbol() == symbol)
							{

								auto position = std::find(states.begin(), states.end(), (*it3).GetFinalState());
								result2 = std::distance(states.begin(), position);
								break;
							}

							else
								++it3;

						}

						if ((statesMatrix[result1][result2] == "X" || statesMatrix[result2][result1] == "X"))
						{
							statesMatrix[index1][index] = "X";
							statesMatrix[index][index1] = "X";

							ok = true;
							break;
						}
					}
				}
			}

		}
	}



}

std::vector<std::set<std::string>> Minimization::makePairs(std::vector<std::vector<std::string>> statesMatrix)
{

	for (int index = 0; index < statesMatrix.size(); index++)
	{
		for (int index1 = 0; index1 <= index; index1++)
		{
			if (statesMatrix[index1][index] == "0")
			{
				pairs.push_back(std::make_pair(statesMatrix[index1][index - 1], statesMatrix[index1 + 1][index]));
			}

		}


	}
	// tranzitivitatea
	std::vector<std::set<std::string>> setsOfStates;
	for (int index = 0; index < pairs.size() - 1; index++)
	{
		std::set<std::string> states;
		bool ok1 = false;
		std::string pair;
		for (int index1 = index + 1; index1 < pairs.size(); index1++)
		{
			if (pairs[index].first == pairs[index1].first)
			{
				ok1 = true;
				pair = pairs[index].second;
			}

		}
		for (int index1 = index + 1; index1 < pairs.size(); index1++)
		{
			if (ok1 == true && pairs[index1].first == pair)
			{
				states.insert(pairs[index].first);
				states.insert(pairs[index].second);
				states.insert(pairs[index1].second);


				pairs.erase(std::find(pairs.begin(), pairs.end(), pairs[index]));
				pairs.erase(std::find(pairs.begin(), pairs.end(), pairs[index1]));

			}

		}

		setsOfStates.push_back(states);
		states.clear();
	}



	return setsOfStates;
}

void Minimization::Verification(std::vector<std::set<std::string>> sets, std::string word)
{


	for (const auto& index : pairs)
	{
		if (std::find(min_states.begin(), min_states.end(), index.first) != min_states.end())
			min_states.erase(index.second);
	}


	for (const auto& index : pairs)
	{

		std::vector<Transition>::iterator it2 = min_transition.begin();

		while (it2 != min_transition.end())
		{

			if ((*it2).GetFinalState() == index.second)
			{
				(*it2).SetFinalState(index.first);
			}
			else
				++it2;

		}
	}


	for (const auto& index : pairs)
	{

		std::vector<Transition>::iterator it2 = min_transition.begin();

		while (it2 != min_transition.end())
		{



			if ((*it2).GetStartState() == index.second)
			{

				it2 = min_transition.erase(it2);
			}
			else
				++it2;

		}
	} //elimin tranzitii



	for (auto it = min_finals.begin(); it != min_finals.end(); ) //sterg din finals elementul care nu mai se afla in tranzitii
	{
		bool ok = 0;
		for (const auto& index : min_transition)
		{
			if (index.GetStartState() == *it)
			{
				ok = 1;
				break;
			}
		}
		if (ok == 1)
			++it;
		else
			if (ok == 0)
			{

				it = min_finals.erase(it);

			}


	}


	bool ok = true;
	std::string start = min_initialState;
	while (word.size())
	{
		for (const auto& transition : min_transition)
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
		std::cout << "Obstruction by Minimization" << std::endl;
	else {
		if (std::find(min_finals.begin(), min_finals.end(), start) != min_finals.end() && word.size() == 0)
			std::cout << "Acceptable by Minimization" << std::endl;
		else
			std::cout << "Unacceptable by Minimization" << std::endl;
	}



}

void Minimization::MakeMinDFA(DFA dfa, std::vector<std::set<std::string>> sets)
{

	std::ofstream outputFile("MinDFA.txt");

	outputFile << "States:\n";
	std::set<std::string> outputStates;
	outputStates = dfa.GetStates();
	for (const auto& index : min_states)
	{
		auto position = std::find(outputStates.begin(), outputStates.end(), index);
		if (position != outputStates.end())
		{
			int result = std::distance(outputStates.begin(), position);
			std::string state = "p" + std::to_string(result + 1);
			outputFile << state << " ";
		}

	}

	outputFile << "\n";

	outputFile << "Sigma:\n";
	for (const auto& sigma : min_sigma)
	{
		outputFile << sigma << " ";
	}
	outputFile << "\n";

	outputFile << "Initial State:\n";

	auto position = std::find(outputStates.begin(), outputStates.end(), min_initialState);
	int result = std::distance(outputStates.begin(), position);
	std::string state = "p" + std::to_string(result + 1);
	outputFile << state << " ";
	//pe cele rezultate in urma tranzitivitatii

	for (const auto& index : sets)
	{
		auto position = std::find(index.begin(), index.end(), min_initialState);
		if (position != index.end())
		{
			int result = std::distance(index.begin(), position);
			std::string state = "p" + std::to_string(result + 1);
			outputFile << state << " ";
		}

	}
	//perechile ramase
	for (const auto& index : pairs)
	{
		if (index.first == min_initialState || index.second == min_initialState)
		{

			auto position = std::find(outputStates.begin(), outputStates.end(), index.first);
			int result = std::distance(outputStates.begin(), position);
			std::string state = "p" + std::to_string(result + 1);
			outputFile << state << " ";
		}

	}

	outputFile << "\n";

	outputFile << "Finals:\n";

	for (const auto& index : min_finals)
	{
		auto position = std::find(outputStates.begin(), outputStates.end(), index);
		if (position != outputStates.end())
		{
			int result = std::distance(outputStates.begin(), position);
			std::string state = "p" + std::to_string(result + 1);
			outputFile << state << " ";
		}

	}

	outputFile << "\n";
	outputFile << "Transitions:\n";
	for (const auto& transition : min_transition)
	{
		auto position = std::find(outputStates.begin(), outputStates.end(), transition.GetStartState());
		int result = std::distance(outputStates.begin(), position);
		std::string state = "p" + std::to_string(result + 1);
		outputFile << "( " << state << " , " << transition.GetSymbol() << " )-> ";

		position = std::find(outputStates.begin(), outputStates.end(), transition.GetFinalState());
		result = std::distance(outputStates.begin(), position);
		 state = "p" + std::to_string(result + 1);
		outputFile << state<<"\n";
	}

	outputFile << "\n";
}

void Minimization::Test(DFA dfa, std::string word)
{
	
	//initiliazari
	min_states = dfa.GetStates();
	min_transition = dfa.GetTransition();
	min_sigma = dfa.GetSigma();
	min_initialState = dfa.GetInitialState();
	min_finals = dfa.GetFinals();

	//prelucrare
	std::vector<std::vector<std::string>> m_list = MakeList();
	BFS(m_list);
	RemoveInaccessibleItems(min_transition, min_states);
	statesMatrix = CreateMatrix(min_states);
	MarkNonFinalWithFinal(statesMatrix, min_finals);
	VerifyUnmarkedPairs(statesMatrix, min_sigma, min_transition, min_states);
	sets = makePairs(statesMatrix); 
	std::cout << "\n";
	std::cout << "##Minimization matrix##\n";
	for (int index = 0; index < statesMatrix.size(); index++)
	{
		for (int index1 = 0; index1 <=index; index1++)
		{
			std::cout << statesMatrix[index][index1] << " ";

		}
		std::cout << "\n";

	}
	std::cout << "\n";
	Verification(sets, word);
    MakeMinDFA(dfa, sets);



}

