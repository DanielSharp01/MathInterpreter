#include "Token.h"

Token::Token(int line, int column)
	: line(line), column(column)
{ }

int Token::getLine()
{
	return line;
}

int Token::getColumn()
{
	return column;
}

std::ostream & operator<<(std::ostream & os, const Token & other)
{
	other.print(os);
	return os;
}

NumberToken::NumberToken(double value, int line, int column)
 : Token(line, column), value(value)
{ }

void NumberToken::print(std::ostream & os) const
{
	os << "NumberToken \"" << value << "\" @line " << line << " @column " << column;;
}

bool NumberToken::match(TokenType type) const
{
	return type == TokenType::NumberLiteral;
}

double NumberToken::getValue() const
{
	return value;
}

BoolToken::BoolToken(bool value, int line, int column)
	: Token(line, column), value(value)
{ }

void BoolToken::print(std::ostream & os) const
{
	os << "BoolToken \"" << value << "\" @line " << line << " @column " << column;;
}

bool BoolToken::match(TokenType type) const
{
	return type == TokenType::BoolLiteral;
}

bool BoolToken::getValue() const
{
	return value;
}

UndefinedToken::UndefinedToken(int line, int column)
	: Token(line, column)
{ }

void UndefinedToken::print(std::ostream & os) const
{
	os << "UndefinedToken @line " << line << " @column " << column;;
}

bool UndefinedToken::match(TokenType type) const
{
	return type == TokenType::UndefinedLiteral;
}

IdentifierToken::IdentifierToken(std::string value, int line, int column)
	: Token(line, column), value(value)
{ }

void IdentifierToken::print(std::ostream & os) const
{
	os << "IdentifierToken \"" << value << "\" @line " << line << " @column " << column;;
}

bool IdentifierToken::match(TokenType type) const
{
	return type == TokenType::Identifier;
}

std::string IdentifierToken::getValue() const
{
	return value;
}

SymbolToken::SymbolToken(std::string value, int line, int column)
	: Token(line, column), value(value)
{ }

void SymbolToken::print(std::ostream & os) const
{
	os << "SymbolToken \"" << value << "\" @line " << line << " @column " << column;;
}

bool SymbolToken::match(TokenType type) const
{
	return type == TokenType::Symbol;
}

bool SymbolToken::match(std::string value) const
{
	return SymbolToken::value == value;
}

std::string SymbolToken::getValue() const
{
	return value;
}

UnknownToken::UnknownToken(std::string value, int line, int column)
	: Token(line, column), value(value)
{ }

void UnknownToken::print(std::ostream & os) const
{
	os << "UnknownToken \"" << value << "\" @line " << line << " @column " << column;;
}

bool UnknownToken::match(TokenType type) const
{
	return type == TokenType::Unknown;
}

std::string UnknownToken::getValue() const
{
	return value;
}

EndingToken::EndingToken(int line, int column)
	: Token(line, column)
{ }

void EndingToken::print(std::ostream & os) const
{
	os << "EndingToken @line " << line << " @column " << column;
}

bool EndingToken::match(TokenType type) const
{
	return type == TokenType::Ending;
}
