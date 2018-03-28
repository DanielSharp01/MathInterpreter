#pragma once

#include <ostream>

//class Scope;

/// A nyelv egy állítása, amit letudunk futtatni
class Statement
{
private:
	//Scope* scope;
public:
	/// Kiírja magát az output streamre
	/// @param os A stream, amire kiírunk
	virtual void print(std::ostream& os) const = 0;
	//virtual void run() const = 0;
};

/// Kiír egy Statement-et az output streamre 
/// @param os A stream, amire kiírunk
/// @param other A Statement, amit kiír
/// @see Token::print
std::ostream& operator<<(std::ostream& os, const Statement& other);