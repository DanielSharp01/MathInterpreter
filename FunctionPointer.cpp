#include "FunctionPointer.h"

#include "Context.h"
#include "Expression.h"
#include <sstream>

ExpressionFunctionPointer::ExpressionFunctionPointer(const std::vector<std::string>& parameters, const Expression* expression)
	:parameters(parameters), expression(expression)
{ }

std::shared_ptr<const TypedValue> ExpressionFunctionPointer::call(const Context& callingContext, std::vector<const Expression*> params, int startLine, int startColumn)
{
	std::vector<std::shared_ptr<const TypedValue>> values;
	for (const Expression* param : params)
	{
		values.push_back(param->evaluate(callingContext));
	}

	FunctionContext context = callingContext.makeFunctionContext(parameters, values);
	return expression->evaluate(context);
}

std::string ExpressionFunctionPointer::getSignature() const
{
	std::stringstream ss;
	ss << "(";
	int i = 0;
	for (std::string param : parameters)
	{
		ss << param << (i < parameters.size() - 1 ? ", " : "");
		i++;
	}
	ss << ")";
	return ss.str();
}

ExpressionFunctionPointer::~ExpressionFunctionPointer()
{
	delete expression;
}
