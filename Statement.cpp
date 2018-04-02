#include "Statement.h"
#include "Expression.h"
#include <string>

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

VariableDeclaration::VariableDeclaration(std::string identifier, const Expression * expression, int line, int column)
	: identifier(identifier), expression(expression), Statement(line, column)
{ }

void VariableDeclaration::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "VariableDeclaration  @line " << line << " @column " << column << std::endl;
	os << spacing << "   Identifier: " << identifier << std::endl;
	os << spacing << "   Expression:" << std::endl;
	expression->print(os, spacing + "      ");
}

FunctionDeclaration::FunctionDeclaration(std::string identifier, std::vector<std::string> parameters, const Expression* expression, int line, int column)
	: identifier(identifier), parameters(parameters), expression(expression), Statement(line, column)
{ }

void FunctionDeclaration::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "FunctionDeclaration  @line " << line << " @column " << column << std::endl;
	os << spacing << "   Identifier: " << identifier << std::endl;
	os << spacing << "   Parameters:" << std::endl;
	for (std::string param : parameters)
	{
		os << spacing << "      " << param << std::endl;
	}
	os << spacing << "   Expression: " << identifier << std::endl;
	expression->print(os, spacing + "      ");
}