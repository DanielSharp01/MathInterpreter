#pragma once

#include "FunctionPointer.h"
#include "Context.h"
#include "TypedValue.h"
#include <functional>

/// Valós n->1 built in CPP függvény
template <int n>
class DoubleFunctionPointer;

template<>
class DoubleFunctionPointer<1> : public FunctionPointer
{
private:
	/// Built in CPP függvény
	std::function<double(double)> cppFunc;
public:
	/// @param parameters A függvény paramétereinek azonosítói
	/// @param expression A függvény kifejezése (ezt értékeljük ki híváskor)
	DoubleFunctionPointer(std::function<double(double)> cppFunc)
		: cppFunc(cppFunc)
	{ }

	std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<std::shared_ptr<const TypedValue>> paramValues) override
	{
		bool error = false;
		if (paramValues.size() < 1)
		{
			//TODO: Workaround needed for line and column numbers
			callingContext.logError("Operand must be a number in built in function", 0, 0);
			error = true;
		}
		else if (!paramValues[0]->is(ValueType::Number))
		{
			if (!paramValues[0]->is(ValueType::Error))
				callingContext.logError("Operand must be a number in built in function", 0, 0);
			error = true;
		}
		
		if (error) return std::make_shared<ErrorValue>();

		return std::make_shared<NumberValue>(cppFunc(std::dynamic_pointer_cast<const NumberValue>(paramValues[0])->getValue()));
	}

	std::string getSignature() const override
	{
		return "(x)";
	}
};

template<>
class DoubleFunctionPointer<2> : public FunctionPointer
{
private:
	/// Built in CPP függvény
	std::function<double(double, double)> cppFunc;
public:
	/// @param parameters A függvény paramétereinek azonosítói
	/// @param expression A függvény kifejezése (ezt értékeljük ki híváskor)
	DoubleFunctionPointer(std::function<double(double, double)> cppFunc)
		: cppFunc(cppFunc)
	{ }

	std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<std::shared_ptr<const TypedValue>> paramValues) override
	{
		bool error;
		if (paramValues.size() < 1)
		{
			//TODO: Workaround needed for line and column numbers
			callingContext.logError("Operand must be a number in built in function", 0, 0);
			error = true;
		}
		else if (!paramValues[0]->is(ValueType::Number))
		{
			if (!paramValues[0]->is(ValueType::Error))
				callingContext.logError("Operand must be a number in built in function", 0, 0);
			error = true;
		}

		if (paramValues.size() < 2)
		{
			callingContext.logError("Operand must be a number in built in function", 0, 0);
			error = true;
		}
		else if (!paramValues[1]->is(ValueType::Number))
		{
			if (!paramValues[0]->is(ValueType::Error))
				callingContext.logError("Operand must be a number in built in function", 0, 0);
			error = true;
		}
		
		if (error) return std::make_shared<ErrorValue>();

		return std::make_shared<NumberValue>(cppFunc(std::dynamic_pointer_cast<const NumberValue>(paramValues[0])->getValue(), std::dynamic_pointer_cast<const NumberValue>(paramValues[1])->getValue()));
	}

	std::string getSignature() const override
	{
		return "(x, y)";
	}
};
