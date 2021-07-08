#include "NFA.h"
#include <iostream>

int main()
{
	NFA nfa;
	nfa.Read();
	nfa.Print();
	std::string word;
	char answear = 'N';
	if (!nfa.SomeChecks())
		std::cout << "The NFA does not respect the conditions" << std::endl;
	else
	{
		do {
			std::cout << "Enter the word: ";
			std::cin >> word;
			if (!nfa.CheckWord(word))
				std::cout << "The word contains symbols outside the sigma set" << std::endl;
			else
				nfa.Verification(word);

			std::cout << "Do you want to continue (Y/N)?" << std::endl;
			std::cout << "You must type a 'Y' or an 'N' :";
			std::cin >> answear;

		} while ((answear == 'y') || (answear == 'Y'));

	}

	return 0;
}