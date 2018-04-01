#pragma once

#include "Statement.h"
#include <vector>

/// Egy kiértékelhető kifejezés
class Expression : public Statement
{
public:
	Expression(int line, int column);
};

/// Egy szám
class NumberExpression : public Expression
{
private:
	/// A kifejezés értéke
	double value;
public:
	/// @param value A kifejezés értéke
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	NumberExpression(double value, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Egy igaz/hamis érték
class BoolExpression : public Expression
{
private:
	/// A kifejezés értéke
	bool value;
public:
	/// @param value A kifejezés értéke
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	BoolExpression(bool value, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Egy azonosító (amely valószínüleg rezolválható egy értékké)
class IdentifierExpression : public Expression
{
private:
	/// A kifejezés értéke
	std::string value;
public:
	/// @param value A kifejezés értéke
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	IdentifierExpression(std::string value, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Egy undefined érték
class UndefinedExpression : public Expression
{
public:
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	UndefinedExpression(int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Egy egy operandusú műveletet reprezentál
class UnaryExpression : public Expression
{
protected:
	/// Az első operandus
	const Expression* first;
public:
	/// @param first Az első operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	UnaryExpression(const Expression* first, int line, int column);
	~UnaryExpression();
};

/// Egy két operandusú műveletet reprezentál
class BinaryExpression : public Expression
{
protected:
	/// Az első operandus
	const Expression* first;
	/// A második operandus
	const Expression* second;
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	BinaryExpression(const Expression* first, const Expression* second, int line, int column);
	~BinaryExpression();
};

/// Egy három operandusú műveletet reprezentál
/// @note A teljesség igénye miatt van it hiszen a ConditonalExpression az egyetlen három operandusú kifejezés
class TernaryExpression : public Expression
{
protected:
	/// Az első operandus
	const Expression* first;
	/// A második operandus
	const Expression* second;
	/// A harmadik operandus
	const Expression* third;
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param third A harmadik operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	TernaryExpression(const Expression* first, const Expression* second, const Expression* third, int line, int column);
	~TernaryExpression();
};

/// Feltételes (ternary) kifejezés három operandussal
class ConditionalExpression : public TernaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param third A harmadik operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	ConditionalExpression(const Expression* first, const Expression* second, const Expression* third, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Vagy kifejezés két operandussal
class OrExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	OrExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// És kifejezés két operandussal
class AndExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	AndExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Nagyobb mint relációs kifejezés két operandussal
class GreaterExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	GreaterExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Kisebb mint relációs kifejezés két operandussal
class LessExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	LessExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Nagyobb vagy egyenlő relációs kifejezés két operandussal
class GreaterEqualsExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	GreaterEqualsExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Kisebb vagy egyenlő relációs kifejezés két operandussal
class LessEqualsExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	LessEqualsExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Egyenlő relációs kifejezés két operandussal
class EqualsExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	EqualsExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Nem egyenlő relációs kifejezés két operandussal
class NotEqualsExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	NotEqualsExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Összeadás kifejezés két operandussal
class AddExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	AddExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Kivonás kifejezés két operandussal
class SubExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	SubExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Szorzás kifejezés két operandussal
class MulExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	MulExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Osztás kifejezés két operandussal
class DivExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	DivExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Modulo kifejezés két operandussal
class ModExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	ModExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

/// Hatványozás kifejezés két operandussal
class PowExpression : public BinaryExpression
{
public:
	/// @param first Az első operandus
	/// @param second A második operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	PowExpression(const Expression* first, const Expression* second, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

class NegExpression : public UnaryExpression
{
public:
	/// @param first Az első operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	NegExpression(const Expression* first, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

class NotExpression : public UnaryExpression
{
public:
	/// @param first Az első operandus
	/// @param line A sor, ahol elkezdődött
	/// @param column Az oszlop, ahol elkezdődött
	NotExpression(const Expression* first, int line, int column);
	void print(std::ostream& os, std::string spacing = "") const override;
};

class FunctionCallExpression : public Expression
{
private:
	const Expression* callable;
	std::vector<const Expression*> parameters;
public:
	FunctionCallExpression(const Expression* callable, std::vector<const Expression*> parameters, int line, int column);
	~FunctionCallExpression();
	void print(std::ostream& os, std::string spacing = "") const override;
};