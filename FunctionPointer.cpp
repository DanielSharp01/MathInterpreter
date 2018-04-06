#include "FunctionPointer.h"

#include "Context.h"
#include "Expression.h"
#include <sstream>

FunctionPointer::FunctionPointer(const std::vector<std::string>& parameters, const Expression* expression)
	:parameters(parameters), expression(expression)
{ }

std::shared_ptr<const TypedValue> FunctionPointer::call(const Context& callingContext, std::vector<std::shared_ptr<const TypedValue>> paramValues)
{
	FunctionContext context = callingContext.makeFunctionContext(parameters, paramValues);
	return expression->evaluate(context);
}

std::string FunctionPointer::getSignature() const
{
	std::stringstream ss;
	ss << "(";
	for (int i = 0; i < parameters.size() - 1; i++)
	{
		ss << parameters[i] << ", ";
	}
	ss << parameters[parameters.size() - 1] << ")";
	return ss.str();
}

FunctionPointer::~FunctionPointer()
{
	delete expression;
}
