#pragma once
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <regex>
#include "DFA.h"

class LexicalAnalyzer
{

public:
	LexicalAnalyzer() = default;
	~LexicalAnalyzer() = default;
	void Init();
	bool IsComment(const std::string& token);
	bool IsBracket(char character);
	bool IsArithmeticOperators(char character);
	bool IsRelationalOperators(char  character);
	bool IsKeyword(const std::string& token);
	bool IsWhitespace(char character);
	bool IsDelimitator(char character);
	bool IsAssignmentOperator(char character);
	bool IsIdentifier(const std::string& token, DFA dfa);
	bool IsInteger(const std::string& token, DFA dfa);
	bool IsFloat(const std::string& token, DFA dfa);
	bool IsString(const std::string& token, DFA dfa);
	std::string StripSpaces(const std::string& str);
	void FirstSteps(const std::string& filename);
	void Analyze(const std::string& token, DFA identifierDFA, DFA integerDFA, DFA floatDFA, DFA stringDFA);
	void WriteHash();



public:
	enum class Brackets
	{
		LeftRound,
		RightRound,
		LeftSquare,
		RightSquare,
		LeftCurly, 
		RightCurly
	};

	enum class ArithmeticOperators
	{
		Plus,
		Minus,
		Multiplication,
		Division,
		Modulus,
	
	};

	enum class RelationalOperators
	{
		LessThan,
		GreaterThan,
		LessThanOrEqualTo,
		GreaterThanOrEqualTo,
		EqualTo,
		NotEqualTo
	};

	enum class Keyword
	{
		For,
		While,
		If,
		Else,
		Int,
		Float,
		Double,
		Do,
		Char,
		Return,
		Auto,
		Struct,
		Union,
		Break,
		Long,
		Const,
		Unsigned,
		Switch,
		Continue,
		Void,
		Case,
		Enum,
		Typedef,
		Default,
		Static,
		Bool,
		True,
		False,
		Cin,
		Cout,
		Std,
		Printf,
		Scanf

	};
private:

	int counter = 0;
	std::map<char, Brackets> m_brackets;
	std::map<char,  ArithmeticOperators> m_arithmeticOperators;
	std::map<char, RelationalOperators> m_relationalOperators;
	std::map<std::string, Keyword> m_keywords;
	std::unordered_map< std::string, int> m_hashTable;
	
};

