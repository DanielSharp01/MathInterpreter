#pragma once

#include <vector>

class Context;
class FunctionPointer;
class Expression;
class FunctionCallExpression;
class TypedValue;

class Frame
{
	/// Kontextus, ami t�rolja a v�ltoz�kat �s a Stack-et
	const Context& context;
	/// @param A hiv� kifejez�s, akinek visszaadjuk az �rt�ket
	const FunctionCallExpression* signalable;

	/// @param context Kontextus, ami t�rolja a v�ltoz�kat �s a Stack-et
	/// @param signalable A hiv� kifejez�s, akinek visszaadjuk az �rt�ket
	Frame(const Context& context, const FunctionCallExpression* signalable);

	/// A frame megh�v�sa
	virtual void call() const = 0;
};

class FunctionFrame : public Frame
{
private:
	/// Megh�vand� f�ggv�ny
	FunctionPointer* funcPointer;
	///  A param�terezett kifejez�sek
	std::vector<const Expression*> parameters;
public:
	/// @param context Kontextus, ami t�rolja a v�ltoz�kat �s a Stack-et
	/// @param signalable A hiv� kifejez�s, akinek visszaadjuk az �rt�ket
	/// @param params A param�terezett kifejez�sek
	FunctionFrame(const Context& context, const FunctionCallExpression* signalable, std::vector<const Expression*> params);

	void call() const override;
};

class SignalingFrame : public Frame
{
	/// A jelzett �rt�k
	const TypedValue* value;

	/// @param context Kontextus, ami t�rolja a v�ltoz�kat �s a Stack-et
	/// @param signalable A hiv� kifejez�s, akinek visszaadjuk az �rt�ket
	/// @param value A jelzett �rt�k
	SignalingFrame(const Context& context, const FunctionCallExpression* signalable, const TypedValue* value);

	void call() const override;
};