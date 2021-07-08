#include "LexicalAnalyzer.h"
#include <fstream>
#include <iostream>


void LexicalAnalyzer::Init()
{
	m_brackets.insert(std::make_pair('(', Brackets::LeftRound));
	m_brackets.insert(std::make_pair(')', Brackets::RightRound));
	m_brackets.insert(std::make_pair('[', Brackets::LeftRound));
	m_brackets.insert(std::make_pair(']', Brackets::RightRound));
	m_brackets.insert(std::make_pair('{', Brackets::LeftCurly));
	m_brackets.insert(std::make_pair('}', Brackets::RightCurly));


	m_arithmeticOperators.insert(std::make_pair('+', ArithmeticOperators::Plus));
	m_arithmeticOperators.insert(std::make_pair('-', ArithmeticOperators::Minus));
	m_arithmeticOperators.insert(std::make_pair('*', ArithmeticOperators::Multiplication));
	m_arithmeticOperators.insert(std::make_pair('/', ArithmeticOperators::Division));
	m_arithmeticOperators.insert(std::make_pair('%', ArithmeticOperators::Modulus));



	m_relationalOperators.insert(std::make_pair('<', RelationalOperators::LessThan));
	m_relationalOperators.insert(std::make_pair('>', RelationalOperators::GreaterThan));
	m_relationalOperators.insert(std::make_pair('!', RelationalOperators::NotEqualTo));


	m_keywords.insert(std::make_pair("for", Keyword::For));
	m_keywords.insert(std::make_pair("while", Keyword::While));
	m_keywords.insert(std::make_pair("if", Keyword::If));
	m_keywords.insert(std::make_pair("else", Keyword::Else));
	m_keywords.insert(std::make_pair("int", Keyword::Int));
	m_keywords.insert(std::make_pair("float", Keyword::Float));
	m_keywords.insert(std::make_pair("double", Keyword::Double));
	m_keywords.insert(std::make_pair("do", Keyword::Do));
	m_keywords.insert(std::make_pair("char", Keyword::Char));
	m_keywords.insert(std::make_pair("return", Keyword::Return));
	m_keywords.insert(std::make_pair("auto", Keyword::Auto));
	m_keywords.insert(std::make_pair("struct", Keyword::Struct));
	m_keywords.insert(std::make_pair("union", Keyword::Union));
	m_keywords.insert(std::make_pair("break", Keyword::Break));
	m_keywords.insert(std::make_pair("long", Keyword::Long));
	m_keywords.insert(std::make_pair("const", Keyword::Const));
	m_keywords.insert(std::make_pair("unsigned", Keyword::Unsigned));
	m_keywords.insert(std::make_pair("switch", Keyword::Switch));
	m_keywords.insert(std::make_pair("Continue", Keyword::Continue));
	m_keywords.insert(std::make_pair("void", Keyword::Void));
	m_keywords.insert(std::make_pair("case", Keyword::Case));
	m_keywords.insert(std::make_pair("enum", Keyword::Enum));
	m_keywords.insert(std::make_pair("typedef", Keyword::Typedef));
	m_keywords.insert(std::make_pair("default", Keyword::Default));
	m_keywords.insert(std::make_pair("static", Keyword::Static));
	m_keywords.insert(std::make_pair("bool", Keyword::Bool));
	m_keywords.insert(std::make_pair("true", Keyword::True));
	m_keywords.insert(std::make_pair("false", Keyword::False));
	m_keywords.insert(std::make_pair("cin", Keyword::Cin));
	m_keywords.insert(std::make_pair("cout", Keyword::Cout));
	m_keywords.insert(std::make_pair("std", Keyword::Std));
	m_keywords.insert(std::make_pair("scanf", Keyword::Scanf));
	m_keywords.insert(std::make_pair("printf", Keyword::Printf));


}

bool LexicalAnalyzer::IsComment(const std::string& token)
{
	std::cmatch res;
	std::regex rx("/\\*(.*?)\\*/");
	if (std::regex_search(token.c_str(), res, rx))
		return true;

	return false;
}

bool LexicalAnalyzer::IsBracket(char character)
{

	if (m_brackets.find(character) != m_brackets.end())
		return true;
	return false;
}

bool LexicalAnalyzer::IsArithmeticOperators(char character)
{


	if (m_arithmeticOperators.find(character) != m_arithmeticOperators.end())
		return true;
	return false;

}

bool LexicalAnalyzer::IsRelationalOperators(char  character)
{

	if (m_relationalOperators.find(character) != m_relationalOperators.end())
		return true;
	return false;
}

bool LexicalAnalyzer::IsKeyword(const std::string& token)
{
	if (m_keywords.find(token) != m_keywords.end())
		return true;
	return false;
}

bool LexicalAnalyzer::IsWhitespace(char character)
{
	if (character == ' ' || character == '\n' || character == ',' || character == '\t')
		return true;
	return false;
}

bool LexicalAnalyzer::IsDelimitator(char character)
{
	if (character == ';')
		return true;
	return false;
}

bool LexicalAnalyzer::IsAssignmentOperator(char character)
{
	if (character == '=')
		return true;
	return false;
}

bool LexicalAnalyzer::IsIdentifier(const std::string& token, DFA dfa)
{
	return dfa.Verification(token);
}

bool LexicalAnalyzer::IsInteger(const std::string& token, DFA dfa)
{
	return dfa.Verification(token);
}

bool LexicalAnalyzer::IsFloat(const std::string& token, DFA dfa)
{
	return dfa.Verification(token);
}

bool LexicalAnalyzer::IsString(const std::string& token, DFA dfa)
{
	return dfa.Verification(StripSpaces(token));
}

std::string LexicalAnalyzer::StripSpaces(const std::string& str)
{
	std::string noSpaces;
	for (int index = 0; index < str.size(); ++index)
		if (str[index] != ' ')
			noSpaces.push_back(str[index]);
	return std::string();
}

void LexicalAnalyzer::FirstSteps(const std::string& filename)
{
	Init();
	std::ifstream inputFile(filename);
	DFA integerDFA;
	DFA floatDFA;
	DFA identifierDFA;
	DFA stringDFA;

	integerDFA.Read("integer.txt");
	floatDFA.Read("float.txt");
	identifierDFA.Read("identifier.txt");
	stringDFA.Read("string.txt");

	std::string line;
	std::string token;
	char lookahead;



	while (std::getline(inputFile, line))
	{
		for (int index = 0; index < line.size(); ++index)
		{
			lookahead = line[index];
			if (IsWhitespace(lookahead))
			{
				Analyze(token, identifierDFA, integerDFA, floatDFA, stringDFA);
				token.clear();
				continue;
			}
			else if (IsDelimitator(lookahead))
			{
				Analyze(token, identifierDFA, integerDFA, floatDFA, stringDFA);
				token.clear();
				std::cout << "<" << lookahead << " , " << "Delimitator>\n";

			}
			else if (IsBracket(lookahead))
			{
				Analyze(token, identifierDFA, integerDFA, floatDFA, stringDFA);
				token.clear();
				std::cout << "<" << lookahead << " , " << "Bracket>\n";
			}
			else if (lookahead == '/' && line[index + 1] == '*')
			{
				Analyze(token, identifierDFA, integerDFA, floatDFA, stringDFA);
				token.clear();
				token.push_back(lookahead);
				index++;
				lookahead = line[index];
				while (lookahead != '/')
				{
					token.push_back(lookahead);
					index++;
					lookahead = line[index];
				}
				token.push_back(lookahead);

			}
			else if (lookahead == '/' && line[index + 1] == '/')
			{
				index = line.size() - 1;
				std::cout << "Commented line\n";
				//std::getline(inputFile, line);
				//inputFile.ignore(2056,'\n');

			}
			else if (IsArithmeticOperators(lookahead))
			{
				Analyze(token, identifierDFA, integerDFA, floatDFA, stringDFA);
				token.clear();
				std::cout << "<" << lookahead << " , " << "Arithmetic Operator>\n";

			}
			else if (IsRelationalOperators(lookahead))
			{
				std::string bindOperator;
				bindOperator = bindOperator + lookahead;
				if (line[index + 1] == '=')
				{
					bindOperator = bindOperator + line[index + 1];
					index++;
				}

				Analyze(token, identifierDFA, integerDFA, floatDFA, stringDFA);
				token.clear();
				std::cout << "<" << bindOperator << " , " << "Relational Operator>\n";
			}
			else if (IsAssignmentOperator(lookahead))
			{
				Analyze(token, identifierDFA, integerDFA, floatDFA, stringDFA);
				token.clear();
				std::cout << "<" << lookahead << " , " << "Assignment Operator>\n";
			}
			else if (lookahead == '"')
			{
				Analyze(token, identifierDFA, integerDFA, floatDFA, stringDFA);
				token.clear();
				token.push_back(lookahead);
				index++;
				lookahead = line[index];
				while (lookahead != '"')
				{
					token.push_back(lookahead);
					index++;
					lookahead = line[index];
				}
				token.push_back(lookahead);
			}

			else
			{
				token.push_back(lookahead);
			}

		}

	}

}

void LexicalAnalyzer::Analyze(const std::string& token, DFA identifierDFA, DFA integerDFA, DFA floatDFA, DFA stringDFA)
{
	try
	{
		if (IsKeyword(token) && token.size())
		{
			std::cout << "<" << token << " , " << "Keyboard>\n";
		}
		else if (IsComment(token) && token.size())
		{
			std::cout << "Commented line\n";
		}

		else if (IsInteger(token, integerDFA) && token.size())
		{
			std::cout << "<" << token << " , " << "Integer>\n";

		}
		else if (IsFloat(token, floatDFA) && token.size())
		{
			std::cout << "<" << token << " , " << "Float>\n";
		}
		else if (IsIdentifier(token, identifierDFA) && token.size())
		{
			std::cout << "<" << token << "," << "Identifier>\n";

			m_hashTable.insert(std::make_pair( token,counter++));
			//counter++;
		}
		else if (IsString(token, stringDFA) && token.size())
		{
			std::cout << "<" << token << " , " << "String>\n";
		}
	}
	catch (const char* e)
	{
		std::cout << e << " " << "Error\n";
	}


}

void LexicalAnalyzer::WriteHash()
{
	std::cout << "No" << " " << "Identifier\n";
	for (const auto& hash : m_hashTable)
	{
		std::cout << hash.second << "  " << hash.first << "\n";
	}
}
