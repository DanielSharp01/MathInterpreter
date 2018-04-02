#pragma once

#include <memory>

class FunctionPointer;

/// TypedValue lehets�ges t�pusai
enum class ValueType
{
	/// Egy val�s sz�m
	Number,
	/// "igaz"/"hamis" �rt�k
	Bool,
	/// F�ggv�ny
	Function,
	/// Nem meghat�rozott �rt�k
	Undefined
};

/// T�pusos �rt�k
class TypedValue
{
public:
	/// Megmondja, hogy az �rt�k egy bizonyos t�pus�-e
	/// @param type T�pus, amit vizsg�lunk
	virtual bool is(ValueType type) const = 0;
};

class NumberValue : public TypedValue
{
private:
	/// �rt�k
	double value;
public:
	/// @param value �rt�k
	NumberValue(double value);
	bool is(ValueType type) const override;
	double getValue();
};

class BoolValue : public TypedValue
{
private:
	/// �rt�k
	bool value;
public:
	/// @param value �rt�k
	BoolValue(bool value);
	bool is(ValueType type) const override;
	/// �rt�k
	bool getValue();
};

class FunctionValue : public TypedValue
{
private:
	/// �rt�k
	std::shared_ptr<FunctionPointer> value;
public:
	/// @param value �rt�k
	FunctionValue(std::shared_ptr<FunctionPointer> value);
	bool is(ValueType type) const override;
	/// �rt�k
	std::shared_ptr<FunctionPointer> getValue();
};

class UndefinedValue : public TypedValue
{
	bool is(ValueType type) const override;
};