#include "Statement.h"
#include "Expression.h"
#include <string>
#include "Context.h"
#include "TypedValue.h"
#include "FunctionPointer.h"

Statement::Statement(int line, int column)
	: line(line), column(column)
{ }

int Statement::getLine() const
{
	return line;
}

int Statement::getColumn() const
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

VariableDeclaration::~VariableDeclaration()
{
	delete expression;
}

void VariableDeclaration::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "VariableDeclaration  @line " << line << " @column " << column << std::endl;
	os << spacing << "   Identifier: " << identifier << std::endl;
	os << spacing << "   Expression:" << std::endl;
	expression->print(os, spacing + "      ");
}

void VariableDeclaration::run(GlobalContext & context) const
{
	context.defineVariable(identifier, expression->evaluate(context));
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

void FunctionDeclaration::run(GlobalContext & context) const
{
	context.defineVariable(identifier, std::make_shared<FunctionValue>(std::make_shared<FunctionPointer>(identifier, parameters, expression)));
}
