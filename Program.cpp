#include <iostream>

#include "Tokenizer.h"
#include "Token.h"
#include "Parser.h"
#include "Expression.h"

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
		}
		
		Parser parser(tokens.cbegin());
		Expression* expression;
		while ((expression = parser.parseExpression()) != nullptr)
		{
			std::cout << *expression;
			delete expression;
		}
		for (Token* token : tokens)
		{
			delete token;
		}

		getline(std::cin, line);
	}

	return 0;
}