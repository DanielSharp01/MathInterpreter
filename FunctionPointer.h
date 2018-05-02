#pragma once

#include <string>
#include <vector>
#include <memory>

class Context;
class Expression;
class TypedValue;

/// Egy meghívható függvényt reprezentál
class FunctionPointer
{
public:
	/// Függvény meghívása
	/// @param callingContext A hívó kontextus
	/// @param paramValues A függvény paraméterei
	virtual std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<const Expression*> params, int startLine, int startColumn) = 0;

	/// A függvény fejléce (kiíráshoz)
	virtual std::string getSignature() const = 0;
};

/// Nem built in függvény
class ExpressionFunctionPointer : public FunctionPointer
{
private:
	/// A függvény paramétereinek azonosítói
	std::vector<std::string> parameters;
	/// A függvény kifejezése (ezt értékeljük ki híváskor)
	const Expression* expression;
public:
	/// @param parameters A függvény paramétereinek azonosítói
	/// @param expression A függvény kifejezése (ezt értékeljük ki híváskor)
	ExpressionFunctionPointer(const std::vector<std::string>& parameters, const Expression* expression);
	~ExpressionFunctionPointer();

	std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<const Expression*> params, int startLine, int startColumn) override;
	std::string getSignature() const override;
};