#include "Expression.h"
#include <string>

Expression::Expression(int line, int column)
	: Statement(line, column)
{ }

NumberExpression::NumberExpression(double value, int line, int column)
	: value(value), Expression(line, column)
{ }

void NumberExpression::print(std::ostream& os, std::string spacing) const
{
	os << spacing << "NumberExpression \"" << value << "\"" << " @line " << line << " @column " << column << std::endl;
}

BoolExpression::BoolExpression(bool value, int line, int column)
	: value(value), Expression(line, column)
{ }

void BoolExpression::print(std::ostream& os, std::string spacing) const
{
	os << spacing << "BoolExpression \"" << (value ? "true" : "false") << "\"" << " @line " << line << " @column " << column << std::endl;
}

IdentifierExpression::IdentifierExpression(std::string value, int line, int column)
	: value(value), Expression(line, column)
{ }

void IdentifierExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "IdentifierExpression \"" << value << "\"" << " @line " << line << " @column " << column << std::endl;
}


UndefinedExpression::UndefinedExpression(int line, int column)
	: Expression(line, column)
{ }

void UndefinedExpression::print(std::ostream& os, std::string spacing) const
{
	os << spacing << "UndefinedExpression @line " << line << " @column " << column << std::endl;
}

UnaryExpression::UnaryExpression(const Expression* first, int line, int column)
	: first(first), Expression(line, column)
{ }

UnaryExpression::~UnaryExpression()
{
	delete first;
}

BinaryExpression::BinaryExpression(const Expression* first, const Expression* second, int line, int column)
	: first(first), second(second), Expression(line, column)
{ }

BinaryExpression::~BinaryExpression()
{
	delete first;
	delete second;
}

TernaryExpression::TernaryExpression(const Expression* first, const Expression* second, const Expression* third, int line, int column)
	: first(first), second(second), third(third), Expression(line, column)
{ }

TernaryExpression::~TernaryExpression()
{
	delete first;
	delete second;
	delete third;
}

ConditionalExpression::ConditionalExpression(const Expression* first, const Expression* second, const Expression* third, int line, int column)
	: TernaryExpression(first, second, third, line, column)
{ }

void ConditionalExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "ConditionalExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
	third->print(os, spacing + "   ");
}

OrExpression::OrExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void OrExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "OrExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

AndExpression::AndExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void AndExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "AndExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

GreaterExpression::GreaterExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void GreaterExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "GreaterExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

LessExpression::LessExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void LessExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "LessExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

GreaterEqualsExpression::GreaterEqualsExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void GreaterEqualsExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "GreaterEqualsExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

LessEqualsExpression::LessEqualsExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void LessEqualsExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "LessEqualsExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

EqualsExpression::EqualsExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void EqualsExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "EqualsExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

NotEqualsExpression::NotEqualsExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void NotEqualsExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "NotEqualsExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

AddExpression::AddExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void AddExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "AddExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

SubExpression::SubExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void SubExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "SubExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

MulExpression::MulExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void MulExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "MulExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

DivExpression::DivExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void DivExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "DivExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

ModExpression::ModExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void ModExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "ModExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

PowExpression::PowExpression(const Expression * first, const Expression * second, int line, int column)
	: BinaryExpression(first, second, line, column)
{ }

void PowExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "PowExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
	second->print(os, spacing + "   ");
}

NegExpression::NegExpression(const Expression * first, int line, int column)
	: UnaryExpression(first, line, column)
{ }

void NegExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "NegExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
}

NotExpression::NotExpression(const Expression * first, int line, int column)
	: UnaryExpression(first, line, column)
{ }

void NotExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "NotExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
}

FunctionCallExpression::FunctionCallExpression(const Expression * callable, std::vector<const Expression*> parameters, int line, int column)
	: callable(callable), parameters(parameters), Expression(line, column)
{ }

FunctionCallExpression::~FunctionCallExpression()
{
	delete callable;
	for (const Expression* param : parameters)
	{
		delete param;
	}
}

void FunctionCallExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "FunctionCallExpression @line " << line << " @column " << column << std::endl;
	os << spacing + "   " << "Callable:" << std::endl;
	callable->print(os, spacing + "      ");
	os << spacing + "   " << "Parameters:" << std::endl;
	for (const Expression* param : parameters)
	{
		param->print(os, spacing + "      ");
	}
}