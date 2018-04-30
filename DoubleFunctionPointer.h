#pragma once

#include "FunctionPointer.h"
#include "Context.h"
#include "TypedValue.h"
#include <functional>
#include "Expression.h"

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

	std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<const Expression*> params, int startLine, int startColumn) override
	{
		std::vector<const Expression*>::const_iterator it = params.cbegin();
		std::shared_ptr<const TypedValue> a;
		bool error = false;
		if (params.size() < 1)
		{
			callingContext.logError("Function must have at least one parameter", startLine, startColumn);
			error = true;
		}

		if (params.size() >= 1)
		{
			a = (*it)->evaluate(callingContext);
			if (!a->is(ValueType::Number))
			{
				if (!a->is(ValueType::Error)) callingContext.logError("Parameter must be a number", (*it)->getLine(), (*it)->getColumn());
				error = true;
			}
		}
		
		if (error) return std::make_shared<ErrorValue>();

		return std::make_shared<NumberValue>(cppFunc(std::dynamic_pointer_cast<const NumberValue>(a)->getValue()));
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

	std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<const Expression*> params, int startLine, int startColumn) override
	{
		std::vector<const Expression*>::const_iterator it = params.cbegin();
		std::shared_ptr<const TypedValue> a, b;
		bool error = false;
		
		if (params.size() < 2)
		{
			callingContext.logError("Function must have at least two parameters", startLine, startColumn);
			error = true;
		}

		if (params.size() >= 1)
		{
			a = (*it)->evaluate(callingContext);
			if (!a->is(ValueType::Number))
			{
				if (!a->is(ValueType::Error)) callingContext.logError("Parameter must be a number", (*it)->getLine(), (*it)->getColumn());
				error = true;
			}
		}

		if (params.size() >= 2)
		{
			it++;
			b = (*it)->evaluate(callingContext);
			if (!b->is(ValueType::Number))
			{
				if (!b->is(ValueType::Error)) callingContext.logError("Parameter must be a number", (*it)->getLine(), (*it)->getColumn());
				error = true;
			}
		}
		

		if (error) return std::make_shared<ErrorValue>();

		return std::make_shared<NumberValue>(cppFunc(std::dynamic_pointer_cast<const NumberValue>(a)->getValue(), std::dynamic_pointer_cast<const NumberValue>(b)->getValue()));
	}

	std::string getSignature() const override
	{
		return "(x, y)";
	}
};
