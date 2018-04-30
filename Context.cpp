#include "Context.h"

#include "TypedValue.h"
#include "DoubleFunctionPointer.h"
#include <math.h>

/// Not overloaded cosine
double nv_cos(double x) { return cos(x); }
/// Not overloaded size
double nv_sin(double x) { return sin(x); }
/// Not overloaded tangent
double nv_tan(double x) { return tan(x); }
/// Not overloaded arccosine
double nv_acos(double x) { return acos(x); }
/// Not overloaded arccosine
double nv_asin(double x) { return asin(x); }
/// Not overloaded arctangent 1 param
double nv_atan(double x) { return atan(x); }
/// Not overloaded arctangent 2 param
double nv_atan2(double x, double y) { return atan2(x, y); }
/// Not overloaded square root
double nv_sqrt(double x) { return sqrt(x); }

GlobalContext::GlobalContext(std::function<void(std::string, int, int)> errorCallback)
	: errorCallback(errorCallback)
{
	defineVariable("cos", std::make_shared<const FunctionValue>(std::make_shared<DoubleFunctionPointer<1>>(nv_cos)));
	defineVariable("sin", std::make_shared<const FunctionValue>(std::make_shared<DoubleFunctionPointer<1>>(nv_sin)));
	defineVariable("tan", std::make_shared<const FunctionValue>(std::make_shared<DoubleFunctionPointer<1>>(nv_tan)));
	defineVariable("acos", std::make_shared<const FunctionValue>(std::make_shared<DoubleFunctionPointer<1>>(nv_acos)));
	defineVariable("asin", std::make_shared<const FunctionValue>(std::make_shared<DoubleFunctionPointer<1>>(nv_asin)));
	defineVariable("atan", std::make_shared<const FunctionValue>(std::make_shared<DoubleFunctionPointer<1>>(nv_atan)));
	defineVariable("atan2", std::make_shared<const FunctionValue>(std::make_shared<DoubleFunctionPointer<2>>(nv_atan2)));
	defineVariable("sqrt", std::make_shared<const FunctionValue>(std::make_shared<DoubleFunctionPointer<1>>(nv_sqrt)));

	defineVariable("PI", std::make_shared<const NumberValue>(3.1415926535897932384626433832795028841971693993751058209749445923078164062));
	defineVariable("E", std::make_shared<const NumberValue>(exp(1)));
}

void GlobalContext::defineVariable(std::string identifier, std::shared_ptr<const TypedValue> value)
{
	variables[identifier] = value;
}

std::shared_ptr<const TypedValue> GlobalContext::resolveIdentifier(std::string identifier) const
{
	std::unordered_map<std::string, std::shared_ptr<const TypedValue>>::const_iterator it = variables.find(identifier);
	if (it == variables.end())
		return std::make_shared<UndefinedValue>();
	else
		return it->second;
}

void GlobalContext::logError(std::string message, int line, int column) const
{
	errorCallback(message, line, column);
}

FunctionContext GlobalContext::makeFunctionContext(const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values) const
{
	return FunctionContext(*this, identifiers, values);
}

FunctionContext::FunctionContext(const GlobalContext& callingContext, const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values)
	: callingContext(callingContext)
{
	std::vector<std::string>::const_iterator keyIt = identifiers.cbegin();
	std::vector<std::shared_ptr<const TypedValue>>::const_iterator valueIt = values.cbegin();
	for (; keyIt != identifiers.end(); ++keyIt)
	{
		if (valueIt == values.end())
		{
			parameters[*keyIt] = std::make_shared<UndefinedValue>();
		}
		else
		{
			parameters[*keyIt] = *valueIt++;
		}
	}
}

std::shared_ptr<const TypedValue> FunctionContext::resolveIdentifier(std::string identifier) const
{
	std::unordered_map<std::string, std::shared_ptr<const TypedValue>>::const_iterator it = parameters.find(identifier);
	if (it == parameters.end())
		return callingContext.resolveIdentifier(identifier);
	else
		return it->second;
}

void FunctionContext::logError(std::string message, int line, int column) const
{
	callingContext.logError(message, line, column);
}

FunctionContext FunctionContext::makeFunctionContext(const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values) const
{
	return FunctionContext(callingContext, identifiers, values);
}
