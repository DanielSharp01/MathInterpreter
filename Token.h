#pragma once

#include <ostream>
#include <string>

/// Token osztálytípus
enum class TokenType
{
	/// Egy valós szám
	NumberLiteral,
	/// "true" / "false"
	BoolLiteral,
	/// Az "undefined" szó
	UndefinedLiteral,
	/// Operátorok és egyéb jelek
	Symbol,
	/// Változó illetve függvénynév
	Identifier,
	/// Token, amit a nyelv nem ismer fel
	Unknown,
	/// A forráskód végére helyezett Token (sentrynek és utolsó sor/utolsó oszlop miatt)
	Ending
};

/// A nyelv alapegysége
class Token
{
protected:
	/// A sor, ahol a Token elkezdődött
	int line;
	/// Az oszlop, ahol a Token elkezdődött
	int column;
public:
	/// @param line A sor, ahol a Token elkezdődött
	/// @param column Az oszlop, ahol a Token elkezdődött
	Token(int line, int column);
	
	virtual ~Token() = default;

	/// Kiírja magát az output streamre
	/// @param os A stream, amire kiírunk
	virtual void print(std::ostream& os) const = 0;

	/// Megmondja, hogy a Token típusa megegyezik e a megadattal
	/// A leszármazott osztályok ezen keresztül tudják "megmondani", milyen típusúak.
	/// @param type Típus, amit viszgálunk
	virtual bool match(TokenType type) const = 0;

	/// A sor, ahol a Token elkezdődött
	int getLine();
	/// Az oszlop, ahol a Token elkezdődött
	int getColumn();
};

/// Kiír egy Token-t az output streamre 
/// @param os A stream, amire kiírunk
/// @param other A Token, amit kiír
/// @see Token::print
std::ostream& operator<<(std::ostream& os, const Token& other);

/// Egy valós szám
class NumberToken : public Token
{
private:
	/// A Token értéke
	double value;
public:
	/// @param value A Token értéke
	/// @param line A sor, ahol a Token elkezdődött
	/// @param column Az oszlop, ahol a Token elkezdődött
	NumberToken(double value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	/// A Token értéke
	double getValue() const;
};

/// "true" / "false"
class BoolToken : public Token
{
private:
	/// A Token értéke
	bool value;
public:
	/// @param value A Token értéke
	/// @param line A sor, ahol a Token elkezdődött
	/// @param column Az oszlop, ahol a Token elkezdődött
	BoolToken(bool value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	/// A Token értéke
	bool getValue() const;
};

/// Az "undefined" szó
class UndefinedToken : public Token
{
public:
	/// @param line A sor, ahol a Token elkezdődött
	/// @param column Az oszlop, ahol a Token elkezdődött
	UndefinedToken(int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
};

/// Változó illetve függvénynév
class IdentifierToken : public Token
{
private:
	/// A Token értéke
	std::string value;
public:
	/// @param value A Token értéke
	/// @param line A sor, ahol a Token elkezdődött
	/// @param column Az oszlop, ahol a Token elkezdődött
	IdentifierToken(std::string value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	/// A Token értéke
	std::string getValue() const;
};

/// Operátorok és egyéb jelek
class SymbolToken : public Token
{
private:
	/// A Token értéke
	std::string value;
public:
	/// @param value A Token értéke
	/// @param line A sor, ahol a Token elkezdődött
	/// @param column Az oszlop, ahol a Token elkezdődött
	SymbolToken(std::string value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;

	/// Checks if the tokens matches a character
	/// @param value The character to check against
	bool match(std::string value) const;
	/// A Token értéke
	std::string getValue() const;
};

/// Token, amit a nyelv nem ismer fel
class UnknownToken : public Token
{
private:
	/// A Token értéke
	std::string value;
public:
	/// @param value A Token értéke
	/// @param line A sor, ahol a Token elkezdődött
	/// @param column Az oszlop, ahol a Token elkezdődött
	UnknownToken(std::string value, int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
	/// A Token értéke
	std::string getValue() const;
};

/// A forráskód végére helyezett Token (sentrynek és utolsó sor/utolsó oszlop miatt)
class EndingToken : public Token
{
public:
	/// @param line A sor, ahol a Token elkezdődött
	/// @param column Az oszlop, ahol a Token elkezdődött
	EndingToken(int line, int column);
	void print(std::ostream& os) const override;
	bool match(TokenType type) const override;
};



