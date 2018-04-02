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
	/// Azonos�t� - v�ltoz� mapping
	std::unordered_map<std::string, const TypedValue*> variables;
	/// F�ggv�nyh�v�s emul�lt stack-je
	std::stack<Frame> stack;
public:
	/// Felold egy azonos�t�t �rt�kk�
	/// @param indentifier Feloldand� azonos�t�
	const TypedValue* resolveIdentifier(std::string identifier);
	/// Felgodlgozza a stack tetej�t
	void callStack();
	/// Hozz�ad egy FunctionFrame-t a param�terekkel a stack-hez
	/// @param signalable A hiv� kifejez�s, akinek visszaadjuk az �rt�ket
	/// @param params A param�terezett kifejez�sek
	void callFunction(const FunctionCallExpression* signalable, std::vector<const Expression*> params);
	/// Hozz�ad egy SignalFrame-t a param�terekkel a stack-hez
	/// @param signalable A hiv� kifejez�s, akinek visszaadjuk az �rt�ket
	/// @param value A jelzett �rt�k
	void signal(Expression* signalable, const TypedValue* value);
};