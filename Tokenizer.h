#pragma once

#include "Tokens/Token.h"
#include <vector>
#include <string>

class Tokenizer
{
private:
	std::string source;
	int currInd;
	int currLine;
	int currColumn;
public:
	Tokenizer(std::string source);
	std::vector<Token*> tokenize();

	Token* parseNumber();
	Token* parseIdentifier();
	Token* parseSymbol();
};