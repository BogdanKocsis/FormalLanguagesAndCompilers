#include "Grammar.h"
#include <tuple>


std::pair<int, int> NumberAndOption()
{
	int number, option;

	std::cout << "How many words: ";
	std::cin >> number;
	if (number < 0 || number == 0)
		throw std::out_of_range("Enter a number greater than 0");

	std::cout << std::endl;
	std::cout << "0.Without steps\n1.With Steps\nChoose the option:";
	std::cin >> option;
	if (option < 0 || option > 1)
		throw std::out_of_range("The option can be 0 or 1");

	return std::make_pair(number, option);
}


int main()
{
	int number, option;
	Grammar grammar;
	grammar.ReadFromFile("grammar.txt");
	std::pair<int, int> numAndOption;

	try
	{

		std::tie(number, option) = NumberAndOption();
		grammar.Write();
		if (grammar.TheBigCheck())
		{
			for (int index = 0; index < number; index++)
			{
				grammar.Generate(option);
				std::cout << std::endl;
			}
		}
		else
			std::cout << "The grammar does not respect the conditions";
	}
	catch (const std::out_of_range & exception)
	{
		std::cout << exception.what() << std::endl;
	}

	return 0;

}