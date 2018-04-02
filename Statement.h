#pragma once

#include <ostream>
#include <vector>

/// A nyelv egy állítása, amit letudunk futtatni
class Statement
{
protected:
	/// A sor, ahol elkezdődött
	int line;
	/// Az oszlop, ahol elkezdődött
	int column;
public:
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	Statement(int line, int column);
	/// Kiírja magát az output streamre
	/// @param os A stream, amire kiírunk
	virtual void print(std::ostream& os, std::string spacing = "") const = 0;

	/// A sor, ahol elkezdődött
	int getLine();
	/// Az oszlop, ahol elkezdődött
	int getColumn();
};

/// Kiír egy Statement-et az output streamre 
/// @param os A stream, amire kiírunk
/// @param other A Statement, amit kiír
/// @see Statement::print
std::ostream& operator<<(std::ostream& os, const Statement& other);

class Expression;

/// Változó deklarálás
class VariableDeclaration : public Statement
{
private:
	/// A változó azonosítója
	std::string identifier;
	/// A változó értékül adott kifejezése
	const Expression* expression;
public:
	/// @param identifier A változó azonosítója
	/// @param expression A változó értékül adott kifejezése
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	VariableDeclaration(std::string identifier, const Expression* expression, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

class FunctionDeclaration : public Statement
{
private:
	/// A függvény azonosítója
	std::string identifier;
	/// A függvény paraméterei
	std::vector<std::string> parameters;
	/// A függvény által kiértékelt kifejezés
	const Expression* expression;
public:
	/// @param identifier A függvény azonosítója
	/// @param parameters A függvény paraméterei
	/// @param expression A függvény által kiértékelt kifejezés
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	FunctionDeclaration(std::string identifier, std::vector<std::string> parameters, const Expression* expression, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};