#pragma once

#include <ostream>


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