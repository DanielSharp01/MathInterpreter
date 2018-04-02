#pragma once

#include <vector>

class Context;
class FunctionPointer;
class Expression;
class FunctionCallExpression;
class TypedValue;

class Frame
{
	/// Kontextus, ami tárolja a változókat és a Stack-et
	const Context& context;
	/// @param A hivó kifejezés, akinek visszaadjuk az értéket
	const FunctionCallExpression* signalable;

	/// @param context Kontextus, ami tárolja a változókat és a Stack-et
	/// @param signalable A hivó kifejezés, akinek visszaadjuk az értéket
	Frame(const Context& context, const FunctionCallExpression* signalable);

	/// A frame meghívása
	virtual void call() const = 0;
};

class FunctionFrame : public Frame
{
private:
	/// Meghívandó függvény
	FunctionPointer* funcPointer;
	///  A paraméterezett kifejezések
	std::vector<const Expression*> parameters;
public:
	/// @param context Kontextus, ami tárolja a változókat és a Stack-et
	/// @param signalable A hivó kifejezés, akinek visszaadjuk az értéket
	/// @param params A paraméterezett kifejezések
	FunctionFrame(const Context& context, const FunctionCallExpression* signalable, std::vector<const Expression*> params);

	void call() const override;
};

class SignalingFrame : public Frame
{
	/// A jelzett érték
	const TypedValue* value;

	/// @param context Kontextus, ami tárolja a változókat és a Stack-et
	/// @param signalable A hivó kifejezés, akinek visszaadjuk az értéket
	/// @param value A jelzett érték
	SignalingFrame(const Context& context, const FunctionCallExpression* signalable, const TypedValue* value);

	void call() const override;
};