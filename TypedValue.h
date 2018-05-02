#pragma once

#include <memory>
#include <iostream>

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
	Undefined,
	/// Hibás érték
	/// Típushibák esetén keletkezik kifejezések kiértékelésekor
	Error
};

/// Típusos érték
class TypedValue
{
private:
	/// Az érték típusa
	ValueType type;
public:
	/// @param type Az érték típusa
	TypedValue(ValueType type);
	/// Megmondja, hogy az érték egy bizonyos típusú-e
	/// @param type Típus, amit vizsgálunk
	bool is(ValueType type) const;
	/// Az érték típusa
	ValueType getType() const;

	/// Kiírja magát az output streamre
	/// @param os A stream, amire kiírunk
	virtual void print(std::ostream& os) const = 0;
};

/// Kiír egy TypedValue-t az output streamre 
/// @param os A stream, amire kiírunk
/// @param other A TypedValue, amit kiír
/// @see TypedValue::print
std::ostream& operator<<(std::ostream& os, const TypedValue& other);

/// Egy valós szám
class NumberValue : public TypedValue
{
private:
	/// Érték
	double value;
public:
	/// @param value Érték
	NumberValue(double value);
	double getValue() const;
	void print(std::ostream& os) const override;
};

/// "igaz"/"hamis" érték
class BoolValue : public TypedValue
{
private:
	/// Érték
	bool value;
public:
	/// @param value Érték
	BoolValue(bool value);
	/// Érték
	bool getValue() const;
	void print(std::ostream& os) const override;
};

/// Függvény
class FunctionValue : public TypedValue
{
private:
	/// Érték
	std::shared_ptr<FunctionPointer> value;
public:
	/// @param value Érték
	FunctionValue(std::shared_ptr<FunctionPointer> value);
	/// Érték
	std::shared_ptr<FunctionPointer> getValue() const;
	void print(std::ostream& os) const override;
};

/// Nem meghatározott érték
class UndefinedValue : public TypedValue
{
public:
	UndefinedValue();
	void print(std::ostream& os) const override;
};

/// Hibás érték
/// Típushibák esetén keletkezik kifejezések kiértékelésekor
class ErrorValue : public TypedValue
{
public:
	ErrorValue();
	void print(std::ostream& os) const override;
};