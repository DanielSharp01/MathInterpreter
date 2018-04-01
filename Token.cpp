#include "Token.h"

Token::Token(int line, int column)
	: line(line), column(column)
{ }

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
	os << "NumberToken \"" << value << "\"";
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
	os << "BoolToken \"" << value << "\"";
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
	os << "UndefinedToken";
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
	os << "IdentifierToken \"" << value << "\"";
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
	os << "SymbolToken \"" << value << "\"";
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

UnknownToken::UnknownToken(char value, int line, int column)
	: Token(line, column), value(value)
{ }

void UnknownToken::print(std::ostream & os) const
{
	os << "UnknownToken \"" << value << "\"";
}

bool UnknownToken::match(TokenType type) const
{
	return type == TokenType::Unknown;
}

char UnknownToken::getValue() const
{
	return value;
}