#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>

class Grammar
{
public:


	void ReadFromFile(const std::string& fileName);
	std::pair<std::string, std::string> splitTheText(const std::string& text);
	void Write();
	bool CheckingSets(const std::set<char>& Vn, const std::set<char>& Vt);
	bool CheckingStart(char start, const std::set<char>& Vn);
	bool IsCharacter(const std::string& text, char character);
	bool CheckingLeftRuleContainsNeterminal(const std::vector<std::string>& left, std::set<char> Vn);
	bool CheckingRulesContainsStart(char start, const std::vector<std::pair<std::string, std::string>>& rule);
	bool CheckingJustStartInLeft(char start, const std::vector<std::string>& left);
	bool CheckingNeterminalsInLeft(const std::vector<std::string>& left, std::set<char> Vn);
	bool CheckingTerminalsInRight(const std::vector<std::string>& right, std::set<char> Vt);
	bool TheBigCheck();
	bool NotContainsNetereminals(const std::string& text, std::set<char> Vn);
	std::vector<int> PositionsForApplicable(const std::string& start);
	void Replacement(std::string& text, const std::string& search, const std::string& replace);
	void Generate(int option);

private:
	std::set<char> m_Vn;
	std::set<char> m_Vt;
	char m_start;
	std::vector<std::string> m_left, m_right;

};

