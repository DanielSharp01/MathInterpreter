#include "FunctionPointer.h"

#include "Context.h"
#include "Expression.h"

FunctionPointer::FunctionPointer(std::string indetifier, const std::vector<std::string>& parameters, const Expression* expression)
	: identifier(identifier), parameters(parameters), expression(expression)
{ }

std::shared_ptr<const TypedValue> FunctionPointer::call(const Context& callingContext, std::vector<std::shared_ptr<const TypedValue>> paramValues)
{
	FunctionContext context = callingContext.makeFunctionContext(parameters, paramValues);
	return expression->evaluate(context);
}

FunctionPointer::~FunctionPointer()
{
	delete expression;
}
