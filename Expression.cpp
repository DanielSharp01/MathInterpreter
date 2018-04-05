#include "Expression.h"
#include <string>
#include <cmath>

#include "TypedValue.h"
#include "Context.h"
#include "FunctionPointer.h"

Expression::Expression(int line, int column)
	: Statement(line, column)
{ }

void Expression::run(GlobalContext& context) const
{
	std::cout << "= " << *evaluate(context) << std::endl;
}

NumberExpression::NumberExpression(double value, int line, int column)
	: value(value), Expression(line, column)
{ }

void NumberExpression::print(std::ostream& os, std::string spacing) const
{
	os << spacing << "NumberExpression \"" << value << "\"" << " @line " << line << " @column " << column << std::endl;
}

std::shared_ptr<const TypedValue> NumberExpression::evaluate(const Context & context) const
{
	return std::make_shared<NumberValue>(value);
}

BoolExpression::BoolExpression(bool value, int line, int column)
	: value(value), Expression(line, column)
{ }

void BoolExpression::print(std::ostream& os, std::string spacing) const
{
	os << spacing << "BoolExpression \"" << (value ? "true" : "false") << "\"" << " @line " << line << " @column " << column << std::endl;
}

std::shared_ptr<const TypedValue> BoolExpression::evaluate(const Context & context) const
{
	return std::make_shared<BoolValue>(value);
}

IdentifierExpression::IdentifierExpression(std::string value, int line, int column)
	: value(value), Expression(line, column)
{ }

void IdentifierExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "IdentifierExpression \"" << value << "\"" << " @line " << line << " @column " << column << std::endl;
}

std::shared_ptr<const TypedValue> IdentifierExpression::evaluate(const Context & context) const
{
	return context.resolveIdentifier(value);
}

UndefinedExpression::UndefinedExpression(int line, int column)
	: Expression(line, column)
{ }

void UndefinedExpression::print(std::ostream& os, std::string spacing) const
{
	os << spacing << "UndefinedExpression @line " << line << " @column " << column << std::endl;
}

std::shared_ptr<const TypedValue> UndefinedExpression::evaluate(const Context & context) const
{
	return std::make_shared<UndefinedValue>();
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

std::shared_ptr<const TypedValue> ConditionalExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> conditional = first->evaluate(context);
	if (!conditional->is(ValueType::Bool))
	{
		if (!conditional->is(ValueType::Error)) context.logError("Condition must be a bool", first->getLine(), first->getColumn());
		return std::make_shared<ErrorValue>();
	}

	if (std::dynamic_pointer_cast<const BoolValue>(conditional)->getValue())
	{
		return second->evaluate(context);
	}
	else
	{
		return third->evaluate(context);
	}
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

std::shared_ptr<const TypedValue> OrExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Bool))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a bool", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Bool))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a bool", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const BoolValue>(a)->getValue() || std::dynamic_pointer_cast<const BoolValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> AndExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Bool))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a bool", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Bool))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a bool", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const BoolValue>(a)->getValue() && std::dynamic_pointer_cast<const BoolValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> GreaterExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() > std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> LessExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() < std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> GreaterEqualsExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() >= std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> LessEqualsExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() <= std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> EqualsExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	if (!a->is(b->getType()))
	{
		return std::make_shared<BoolValue>(false);
	}
	else if (a->is(ValueType::Undefined))
	{
		return std::make_shared<BoolValue>(true);
	}
	else if (a->is(ValueType::Number))
	{
		return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() == std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
	}
	else if (a->is(ValueType::Bool))
	{
		return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const BoolValue>(a)->getValue() == std::dynamic_pointer_cast<const BoolValue>(b)->getValue());
	}
	else if (a->is(ValueType::Function))
	{
		return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const FunctionValue>(a)->getValue() == std::dynamic_pointer_cast<const FunctionValue>(b)->getValue());
	}
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

std::shared_ptr<const TypedValue> NotEqualsExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	if (!a->is(b->getType()))
	{
		return std::make_shared<BoolValue>(true);
	}
	else if (a->is(ValueType::Undefined))
	{
		return std::make_shared<BoolValue>(false);
	}
	else if (a->is(ValueType::Number))
	{
		return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() != std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
	}
	else if (a->is(ValueType::Bool))
	{
		return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const BoolValue>(a)->getValue() != std::dynamic_pointer_cast<const BoolValue>(b)->getValue());
	}
	else if (a->is(ValueType::Function))
	{
		return std::make_shared<BoolValue>(std::dynamic_pointer_cast<const FunctionValue>(a)->getValue() != std::dynamic_pointer_cast<const FunctionValue>(b)->getValue());
	}
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

std::shared_ptr<const TypedValue> AddExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<NumberValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() + std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> SubExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<NumberValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() - std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> MulExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<NumberValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() * std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> DivExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<NumberValue>(std::dynamic_pointer_cast<const NumberValue>(a)->getValue() / std::dynamic_pointer_cast<const NumberValue>(b)->getValue());
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

std::shared_ptr<const TypedValue> ModExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<NumberValue>(fmod(std::dynamic_pointer_cast<const NumberValue>(a)->getValue(), std::dynamic_pointer_cast<const NumberValue>(b)->getValue()));
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

std::shared_ptr<const TypedValue> PowExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	std::shared_ptr<const TypedValue> b = second->evaluate(context);
	bool error = false;
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		error = true;
	}
	if (!b->is(ValueType::Number))
	{
		if (!b->is(ValueType::Error)) context.logError("Operand must be a number", second->getLine(), second->getColumn());
		error = true;
	}
	if (error) return std::make_shared<ErrorValue>();

	return std::make_shared<NumberValue>(pow(std::dynamic_pointer_cast<const NumberValue>(a)->getValue(), std::dynamic_pointer_cast<const NumberValue>(b)->getValue()));
}

NegExpression::NegExpression(const Expression * first, int line, int column)
	: UnaryExpression(first, line, column)
{ }

void NegExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "NegExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
}

std::shared_ptr<const TypedValue> NegExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	if (!a->is(ValueType::Number))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a number", first->getLine(), first->getColumn());
		return std::make_shared<ErrorValue>();
	}

	return std::make_shared<NumberValue>(-std::dynamic_pointer_cast<const NumberValue>(a)->getValue());
}

NotExpression::NotExpression(const Expression * first, int line, int column)
	: UnaryExpression(first, line, column)
{ }

void NotExpression::print(std::ostream & os, std::string spacing) const
{
	os << spacing << "NotExpression @line " << line << " @column " << column << std::endl;
	first->print(os, spacing + "   ");
}

std::shared_ptr<const TypedValue> NotExpression::evaluate(const Context & context) const
{
	std::shared_ptr<const TypedValue> a = first->evaluate(context);
	if (!a->is(ValueType::Bool))
	{
		if (!a->is(ValueType::Error)) context.logError("Operand must be a bool", first->getLine(), first->getColumn());
		return std::make_shared<ErrorValue>();
	}

	return std::make_shared<BoolValue>(!std::dynamic_pointer_cast<const BoolValue>(a)->getValue());
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

std::shared_ptr<const TypedValue> FunctionCallExpression::evaluate(const Context& context) const
{
	std::shared_ptr<const TypedValue> func = callable->evaluate(context);
	if (!func->is(ValueType::Function))
	{
		if (!func->is(ValueType::Function)) context.logError("Operand must be a function", callable->getLine(), callable->getColumn());
		return std::make_shared<ErrorValue>();
	}

	std::vector<std::shared_ptr<const TypedValue>> values;
	for (const Expression* param : parameters)
	{
		values.push_back(param->evaluate(context));
	}

	return std::dynamic_pointer_cast<const FunctionValue>(func)->getValue()->call(context, values);
}
