#pragma once

#include <ostream>
#include <string>

enum class TokenType
{
	NumberLiteral, BoolLiteral, UndefinedLiteral, Symbol, Identifier, Uknown
};

class Token
{
private:
	int line;
	int column;
public:
	Token(int line, int column);
	virtual void print(std::ostream& os) const = 0;
	virtual bool match(TokenType type) const = 0;
};

class NumberToken : public Token
{
private:
	double value;
public:
	NumberToken(double value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	double value() const;
};

class BoolToken : public Token
{
private:
	bool value;
public:
	BoolToken(bool value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	bool value() const;
};

class UndefinedToken : public Token
{
public:
	UndefinedToken(int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
};

class IdentifierToken : public Token
{
private:
	std::string value;
public:
	IdentifierToken(std::string value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	std::string value() const;
};

class SymbolToken : public Token
{
private:
	char value;
public:
	SymbolToken(char value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	char value() const;
};


class UnknownToken : public Token
{
private:
	char value;
public:
	UnknownToken(char value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	char value() const;
};

