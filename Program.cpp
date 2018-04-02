#include <iostream>

#include "Tokenizer.h"
#include "Token.h"
#include "Parser.h"
#include "Statement.h"
#include <string>

int main()
{
	std::string line;
	getline(std::cin, line);
	while (line != "quit")
	{
		Tokenizer tokenizer(line, [&](std::string msg, int line, int col) {
			std::cout << "TOKENIZER ERROR: " << msg << " @line " << line << " @column " << col << std::endl;
		});
		std::vector<Token*> tokens = tokenizer.tokenize();
		/*for (Token* token : tokens)
		{
			std::cout << *token << std::endl;
		}*/
		
		Parser parser(tokens.cbegin(), [&](std::string msg, int line, int col) {
			std::cout << "PARSER ERROR: " << msg << " @line " << line << " @column " << col << std::endl;
		});

		Statement* stat;
		while ((stat = parser.parseStatement()) != nullptr)
		{
			std::cout << *stat;
			delete stat;
		}

		
		for (Token* token : tokens)
		{
			delete token;
		}

		getline(std::cin, line);
	}

	return 0;
}