#pragma once

#include <unordered_map>
#include <stack>
#include <string>

class Expression;
class FunctionCallExpression;
class Frame;
class FunctionPointer;
class TypedValue;

class Context
{
private:
	/// Azonosító - változó mapping
	std::unordered_map<std::string, const TypedValue*> variables;
	/// Függvényhívás emulált stack-je
	std::stack<Frame> stack;
public:
	/// Felold egy azonosítót értékké
	/// @param indentifier Feloldandó azonosító
	const TypedValue* resolveIdentifier(std::string identifier);
	/// Felgodlgozza a stack tetejét
	void callStack();
	/// Hozzáad egy FunctionFrame-t a paraméterekkel a stack-hez
	/// @param signalable A hivó kifejezés, akinek visszaadjuk az értéket
	/// @param params A paraméterezett kifejezések
	void callFunction(const FunctionCallExpression* signalable, std::vector<const Expression*> params);
	/// Hozzáad egy SignalFrame-t a paraméterekkel a stack-hez
	/// @param signalable A hivó kifejezés, akinek visszaadjuk az értéket
	/// @param value A jelzett érték
	void signal(Expression* signalable, const TypedValue* value);
};