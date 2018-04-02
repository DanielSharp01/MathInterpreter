#pragma once

#include <memory>

class FunctionPointer;

/// TypedValue lehetséges típusai
enum class ValueType
{
	/// Egy valós szám
	Number,
	/// "igaz"/"hamis" érték
	Bool,
	/// Függvény
	Function,
	/// Nem meghatározott érték
	Undefined
};

/// Típusos érték
class TypedValue
{
public:
	/// Megmondja, hogy az érték egy bizonyos típusú-e
	/// @param type Típus, amit vizsgálunk
	virtual bool is(ValueType type) const = 0;
};

class NumberValue : public TypedValue
{
private:
	/// Érték
	double value;
public:
	/// @param value Érték
	NumberValue(double value);
	bool is(ValueType type) const override;
	double getValue();
};

class BoolValue : public TypedValue
{
private:
	/// Érték
	bool value;
public:
	/// @param value Érték
	BoolValue(bool value);
	bool is(ValueType type) const override;
	/// Érték
	bool getValue();
};

class FunctionValue : public TypedValue
{
private:
	/// Érték
	std::shared_ptr<FunctionPointer> value;
public:
	/// @param value Érték
	FunctionValue(std::shared_ptr<FunctionPointer> value);
	bool is(ValueType type) const override;
	/// Érték
	std::shared_ptr<FunctionPointer> getValue();
};

class UndefinedValue : public TypedValue
{
	bool is(ValueType type) const override;
};