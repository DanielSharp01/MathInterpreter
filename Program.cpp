#include <iostream>

#include "Tokenizer.h"
#include "Token.h"

int main()
{
	std::string line;
	getline(std::cin, line);
	while (line != "quit")
	{
		Tokenizer tokenizer(line);
		std::vector<Token*> tokens = tokenizer.tokenize();
		for (Token* token : tokens)
		{
			std::cout << *token << std::endl;
			delete token;
		}
		getline(std::cin, line);
	}

	return 0;
}