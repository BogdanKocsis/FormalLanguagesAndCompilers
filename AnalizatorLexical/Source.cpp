#include <iostream>
#include "LexicalAnalyzer.h"


int main()
{
	LexicalAnalyzer LA;
	std::cout << "List of lexical units\n";
	LA.FirstSteps("test2.txt");
	std::cout << "\n";
	LA.WriteHash();

	return 0;

}