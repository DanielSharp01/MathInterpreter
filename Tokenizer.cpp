#include "Tokenizer.h"

Tokenizer::Tokenizer(std::string source)
	: source(source)
{ }

std::vector<Token*> Tokenizer::tokenize()
{
	std::vector<Token*> tokens;

	while (!isOver())
	{
		if (isWhitespace(currentChar()))
		{
			nextChar();
		}
		else if ((currentChar() == '.' && isDigit(lookAheadChar())) || isDigit(currentChar()))
		{
			tokens.push_back(parseNumber());
		}
		else if (currentChar() == '_' || isAlphaNumeric(currentChar()))
		{
			tokens.push_back(parseWord());
		}
		else
		{
			tokens.push_back(parseSymbol());
		}
	}

	return tokens;
}

Token* Tokenizer::parseNumber()
{
	bool dot = false;
	int line = currLine, column = currColumn;
	std::string buffer;
	while (isDigit(currentChar()) || (currentChar() == '.' && isDigit(lookAheadChar()) && !dot))
	{
		if (currentChar() == '.')
		{
			dot = true;
		}
		buffer += nextChar();
	}

	return new NumberToken(strtod(buffer.c_str(), nullptr), line, column);
}

Token* Tokenizer::parseWord()
{
	int line = currLine, column = currColumn;
	std::string buffer;
	do
	{
		buffer += nextChar();
	} while (isAlphaNumeric(currentChar()));

	if (buffer == "undefined")
		return new UndefinedToken(line, column);
	else if (buffer == "true")
		return new BoolToken(true, line, column);
	else if (buffer == "false")
		return new BoolToken(false, line, column);
	else
		return new IdentifierToken(buffer, line, column);
}

Token* Tokenizer::parseSymbol()
{
	int line = currLine, column = currColumn;
	char buffer[2] = { nextChar(), currentChar() };
	if (buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/' || buffer[0] == '^' || buffer[0] == '%'
		|| buffer[0] == '(' || buffer[0] == ')' || buffer[0] == '{' || buffer[0] == '}' || buffer[0] == '?' || buffer[0] == ':')
	{
		return new SymbolToken(std::string(buffer, 1), line, column);
	}
	else if (buffer[0] == '|' || buffer[0] == '&')
	{
		if (buffer[0] == buffer[1])
		{
			nextChar();
		}
		
		return new SymbolToken(std::string(buffer, 1), line, column);
	}
	else if (buffer[0] == '!' || buffer[0] == '=' || buffer[0] == '<' || buffer[0] == '>')
	{
		if (buffer[1] == '=')
		{
			nextChar();
			return new SymbolToken(std::string(buffer, 2), line, column);
		}
		else
		{
			return new SymbolToken(std::string(buffer, 1), line, column);
		}
	}
	else
	{
		return new UnknownToken(buffer[0], line, column);
	}
}

bool Tokenizer::isOver()
{
	return currIndex >= source.size();
}

char Tokenizer::currentChar()
{
	return source[currIndex];
}

char Tokenizer::nextChar()
{
	return source[currIndex++];
}

char Tokenizer::lookAheadChar()
{
	return source[currIndex + 1];
}

bool Tokenizer::isWhitespace(char c)
{
	return c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r' || c == '\f';
}

bool Tokenizer::isDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool Tokenizer::isAlphaNumeric(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}