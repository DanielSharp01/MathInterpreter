#include "TypedValue.h"

#include "FunctionPointer.h"

TypedValue::TypedValue(ValueType type)
	: type(type)
{ }

bool TypedValue::is(ValueType type) const
{
	return TypedValue::type == type;
}

ValueType TypedValue::getType() const
{
	return type;
}

NumberValue::NumberValue(double value)
	: value(value), TypedValue(ValueType::Number)
{ }

double NumberValue::getValue() const
{
	return value;
}

void NumberValue::print(std::ostream & os) const
{
	os << value;
}

BoolValue::BoolValue(bool value)
	: value(value), TypedValue(ValueType::Bool)
{ }

bool BoolValue::getValue() const
{
	return value;
}

void BoolValue::print(std::ostream & os) const
{
	os << (value ? "true" : "false");
}

FunctionValue::FunctionValue(std::shared_ptr<FunctionPointer> value)
	: value(value), TypedValue(ValueType::Function)
{ }


std::shared_ptr<FunctionPointer> FunctionValue::getValue() const
{
	return value;
}

void FunctionValue::print(std::ostream & os) const
{
	os << "function " << value->getSignature();
}

UndefinedValue::UndefinedValue()
	: TypedValue(ValueType::Undefined)
{ }

void UndefinedValue::print(std::ostream & os) const
{
	os << "undefined";
}

ErrorValue::ErrorValue()
	: TypedValue(ValueType::Error)
{ }

void ErrorValue::print(std::ostream & os) const
{
	os << "error";
}

std::ostream & operator<<(std::ostream & os, const TypedValue & other)
{
	other.print(os);
	return os;
}
