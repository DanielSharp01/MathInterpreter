#include <iostream>

#include "Tokenizer.h"
#include "Token.h"
#include "Parser.h"
#include "Statement.h"
#include <string>
#include "Context.h"
#include "TypedValue.h"
#include "Expression.h"

int main()
{
	GlobalContext context([&](std::string msg, int line, int col) {
		std::cout << "RUNTIME ERROR: " << msg << " @line " << line << " @column " << col << std::endl;
	});

	std::string line;
	getline(std::cin, line);
	while (line != "quit")
	{
		int parseTimeError = 0;
		Tokenizer tokenizer(line, [&](std::string msg, int line, int col) {
			std::cout << "TOKENIZER ERROR: " << msg << " @line " << line << " @column " << col << std::endl;
			parseTimeError++;
		});

		std::vector<Token*> tokens = tokenizer.tokenize();
		/*for (Token* token : tokens)
		{
			std::cout << *token << std::endl;
		}*/

		Parser parser(tokens.cbegin(), [&](std::string msg, int line, int col) {
			std::cout << "PARSER ERROR: " << msg << " @line " << line << " @column " << col << std::endl;
			parseTimeError++;
		});

		Statement* stat;
		while ((stat = parser.parseStatement()) != nullptr)
		{
			if (parseTimeError == 0) stat->run(context);
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