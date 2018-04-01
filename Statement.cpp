#include "Statement.h"

Statement::Statement(int line, int column)
	: line(line), column(column)
{ }

int Statement::getLine()
{
	return line;
}

int Statement::getColumn()
{
	return column;
}

std::ostream & operator<<(std::ostream & os, const Statement& other)
{
	other.print(os);
	return os;
}
