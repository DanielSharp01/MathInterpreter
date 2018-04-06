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
private:
	/// A függvény paramétereinek azonosítói
	std::vector<std::string> parameters;
	/// A függvény kifejezése (ezt értékeljük ki híváskor)
	const Expression* expression;
public:
	/// @param identifier A függvény azonosítója
	/// @param parameters A függvény paramétereinek azonosítói
	/// @param expression A függvény kifejezése (ezt értékeljük ki híváskor)
	FunctionPointer(const std::vector<std::string>& parameters, const Expression* expression);
	~FunctionPointer();

	/// @param callingContext A hívó kontextus
	/// @param paramValues A függvény paraméterei
	std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<std::shared_ptr<const TypedValue>> paramValues);

	/// A függvény fejléce (kiíráshoz)
	std::string getSignature() const;
};