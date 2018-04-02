#pragma once

#include <string>
#include <vector>

class FunctionFrame;
class Expression;
class FunctionCallExpression;
class Context;

/// Függvény pointer
class FunctionPointer
{
private:
	/// Kontextus, ami tárolja a változókat és a Stack-et
	const Context& context;
	/// A függvény azonosítója
	std::string identifier;
	/// A függvény paraméterei
	std::vector<std::string> parameters;
	/// A függvény által kiértékelt kifejezés
	const Expression* expression;
public:
	/// @param context Kontextus, ami tárolja a változókat és a Stack-et
	/// @param identifier A függvény azonosítója
	/// @param parameters A függvény paraméterei
	/// @param expression A függvény által kiértékelt kifejezés 
	FunctionPointer(const Context& context, std::string identifier, std::vector<std::string> parameters, const Expression* expressions);

	/// Függvény hívás
	/// @param params A paraméterezett kifejezések
	/// @param context Kontextus, ami tárolja a változókat és a Stack-et
	void call(std::vector<const Expression*> params);
};