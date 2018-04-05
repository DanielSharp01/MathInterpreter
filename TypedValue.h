#pragma once

#include <memory>
#include <iostream>

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
	Undefined,
	/// Hib�s �rt�k
	/// T�pushib�k eset�n keletkezik kifejez�sek ki�rt�kel�sekor
	Error
};

/// T�pusos �rt�k
class TypedValue
{
private:
	/// Az �rt�k t�pusa
	ValueType type;
public:
	/// @param type Az �rt�k t�pusa
	TypedValue(ValueType type);
	/// Megmondja, hogy az �rt�k egy bizonyos t�pus�-e
	/// @param type T�pus, amit vizsg�lunk
	bool is(ValueType type) const;
	/// Az �rt�k t�pusa
	ValueType getType() const;

	/// Ki�rja mag�t az output streamre
	/// @param os A stream, amire ki�runk
	virtual void print(std::ostream& os) const = 0;
};

/// Ki�r egy TypedValue-t az output streamre 
/// @param os A stream, amire ki�runk
/// @param other A TypedValue, amit ki�r
/// @see TypedValue::print
std::ostream& operator<<(std::ostream& os, const TypedValue& other);

/// Egy val�s sz�m
class NumberValue : public TypedValue
{
private:
	/// �rt�k
	double value;
public:
	/// @param value �rt�k
	NumberValue(double value);
	double getValue() const;
	void print(std::ostream& os) const override;
};

/// "igaz"/"hamis" �rt�k
class BoolValue : public TypedValue
{
private:
	/// �rt�k
	bool value;
public:
	/// @param value �rt�k
	BoolValue(bool value);
	/// �rt�k
	bool getValue() const;
	void print(std::ostream& os) const override;
};

/// F�ggv�ny
class FunctionValue : public TypedValue
{
private:
	/// �rt�k
	std::shared_ptr<FunctionPointer> value;
public:
	/// @param value �rt�k
	FunctionValue(std::shared_ptr<FunctionPointer> value);
	/// �rt�k
	std::shared_ptr<FunctionPointer> getValue() const;
	void print(std::ostream& os) const override;
};

/// Nem meghat�rozott �rt�k
class UndefinedValue : public TypedValue
{
public:
	UndefinedValue();
	void print(std::ostream& os) const override;
};

/// Hib�s �rt�k
/// T�pushib�k eset�n keletkezik kifejez�sek ki�rt�kel�sekor
class ErrorValue : public TypedValue
{
public:
	ErrorValue();
	void print(std::ostream& os) const override;
};