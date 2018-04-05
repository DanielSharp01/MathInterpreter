#include "Context.h"

#include "TypedValue.h"

GlobalContext::GlobalContext(std::function<void(std::string, int, int)> errorCallback)
	: errorCallback(errorCallback)
{ }

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
	: callingContext(callingContext), Context()
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
