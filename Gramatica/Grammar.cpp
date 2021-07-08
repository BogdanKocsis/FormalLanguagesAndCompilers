#include "Grammar.h"

#include <fstream>
#include <algorithm>
#include <stdlib.h>     
#include <time.h> 
#include<random>


std::pair<std::string, std::string> Grammar::splitTheText(const std::string& text)
{
	auto index = text.find('-');
	std::pair<std::string, std::string> rule;
	if (index != std::string::npos) {
		rule = std::make_pair(text.substr(0, index), text.substr(index + 1));
		while (!rule.second.empty() && rule.second.front() == '>') {
			rule.second.erase(0, 1);
		}
	}

	return rule;


}

void Grammar::ReadFromFile(const std::string& fileName)
{
	std::ifstream grammarFile(fileName);

	while (!grammarFile.eof())
	{
		int numOfSomething;
		char character;
		std::string rule;
		grammarFile >> numOfSomething;
		for (int index = 0; index < numOfSomething; index++)
		{
			grammarFile >> character;
			m_Vn.insert(character);
		}
		grammarFile >> numOfSomething;
		for (int index = 0; index < numOfSomething; index++)
		{
			grammarFile >> character;
			m_Vt.insert(character);
		}

		grammarFile >> m_start;

		grammarFile >> numOfSomething;

		for (int index = 0; index < numOfSomething; index++)
		{
			grammarFile >> rule;
			std::pair<std::string, std::string> pair = splitTheText(rule);
			m_left.emplace_back(pair.first);
			m_right.emplace_back(pair.second);

		}


	}


}

bool Grammar::CheckingSets(const std::set<char>& Vn, const std::set<char>& Vt)
{
	auto index1 = Vn.begin();
	auto index2 = Vt.begin();
	while (index1 != Vn.end() && index2 != Vt.end())
	{
		if (*index1 == *index2)
			return false;
		else
			if (*index1 < *index2)
				index1++;
			else
				index2++;

	}
	return true;

}
bool Grammar::CheckingStart(char start, const std::set<char>& Vn)
{
	const auto& it = std::find(Vn.begin(), Vn.end(), start);
	if (it != Vn.end())
		return true;
	return false;
}

bool Grammar::IsCharacter(const std::string& text, char character)
{
	for (int index = 0; index < text.size(); index++)
		if (text[index] == character)
			return true;
	return false;
}

bool Grammar::CheckingLeftRuleContainsNeterminal(const std::vector<std::string>& left, std::set<char> Vn)
{

	for (const auto& index : left)
	{
		int counter = 0;
		for (const auto& it : Vn)
		{
			if (IsCharacter(index, it))
				counter++;
		}

		if (counter == 0)
			return false;

	}

	return true;
}

bool Grammar::CheckingJustStartInLeft(char start, const std::vector<std::string>& left)
{
	for (const auto& index : left)
	{
		if (index.length() == 1)
		{
			if (index.at(0) == start)
				return true;
		}
	}

	return false;
}

bool Grammar::CheckingNeterminalsInLeft(const std::vector<std::string>& left, std::set<char> Vn)
{

	bool ok = false;
	for (int index = 0; index < left.size(); index++)
		for (const auto& neterminal : Vn)
		{
			if (left[index].find(neterminal) != std::string::npos)
				ok = true;
		}
	return ok;

}

bool Grammar::CheckingTerminalsInRight(const std::vector<std::string>& right, std::set<char> Vt)
{

	bool ok = false;
	for (int index = 0; index < right.size(); index++)
		for (const auto& terminal : Vt)
		{
			if (right[index].find(terminal) != std::string::npos)
				ok = true;
		}
	return ok;

}

bool Grammar::TheBigCheck()
{
	if (!CheckingSets(m_Vn, m_Vt))
		return false;
	else if (!CheckingStart(m_start, m_Vn))
		return false;
	else if (!CheckingLeftRuleContainsNeterminal(m_left, m_Vn))
		return false;
	else if (!CheckingJustStartInLeft(m_start, m_left))
		return false;
	else if (!CheckingNeterminalsInLeft(m_left, m_Vn) || !CheckingTerminalsInRight(m_right, m_Vt))
		return false;
	return true;
}

bool Grammar::NotContainsNetereminals(const std::string& text, std::set<char> Vn)
{

	for (auto index : Vn)
		if (text.find(index) != std::string::npos)
			return false;
	return true;
}


std::vector<int> Grammar::PositionsForApplicable(const std::string& start)
{
	std::vector<int> positions;
	for (int index = 0; index < m_left.size(); index++)
		if (start.find(m_left[index]) != std::string::npos)
			positions.push_back(index);
	return positions;
}

void Grammar::Replacement(std::string& text, const std::string& search, const std::string& replace) {
	size_t pos = 0;
	pos = text.find(search, pos);
	text.replace(pos, search.size(), replace);

}

int GenerateRandomNumber(int number)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, number - 1);
	return dist(mt);
}

void Grammar::Generate(int option)
{
	std::string Start{ m_start };

	std::vector<int> positions = PositionsForApplicable(Start);
	int copy;
	std::cout << m_start;
	while (positions.size() != 0)
	{
		int numOfRule = GenerateRandomNumber(positions.size());
		Replacement(Start, m_left[positions[numOfRule]], m_right[positions[numOfRule]]);
		if (option == 1)
		{
			std::cout << "=> rule number: " << positions[numOfRule] << " " << Start;
		}

		copy = positions[numOfRule];
		positions.clear();
		positions = PositionsForApplicable(Start);

	}


	if (NotContainsNetereminals(Start, m_Vn) && option == 0)
		std::cout << "=>" << Start;






}

void Grammar::Write()
{
	std::cout << "Vn: ";
	for (auto i : m_Vn)
	{
		std::cout << i << " ";

	}
	std::cout << std::endl;

	std::cout << "Vt: ";
	for (auto i : m_Vt)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;
	std::cout << "Start: " << m_start << std::endl;


	std::cout << "Rules:\n";
	for (int index = 0; index < m_left.size(); index++)
	{
		std::cout << m_left[index] << "->" << m_right[index] << std::endl;

	}



}




