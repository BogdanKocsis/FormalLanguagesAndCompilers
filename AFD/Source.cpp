#include "DFA.h"
#include <iostream>
int main()
{
    DFA dfa;
	dfa.Read("inputDFA.txt");
	dfa.Print();
	std::string word;
	char answear = 'N';
	if(!dfa.SomeChecks())
		std::cout << "The DFA does not respect the conditions"<<std::endl;
	else
	{
		do {
			std::cout << "Enter the word: ";
			std::cin >> word;
			if (!dfa.CheckWord(word))
				std::cout << "The word contains symbols outside the sigma set" << std::endl;
			else
				dfa.Verification(word);

			std::cout << "Do you want to continue (Y/N)?"<<std::endl;
			std::cout << "You must type a 'Y' or an 'N' :";
			std::cin >> answear;

		} while ((answear=='y') || (answear=='Y'));
		
	}
	
	return 0;
}