#pragma once

#include <string>
#include <vector>
#include <memory>

class Context;
class Expression;
class TypedValue;

/// Egy megh�vhat� f�ggv�nyt reprezent�l
class FunctionPointer
{
public:
	/// F�ggv�ny megh�v�sa
	/// @param callingContext A h�v� kontextus
	/// @param paramValues A f�ggv�ny param�terei
	virtual std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<const Expression*> params, int startLine, int startColumn) = 0;

	/// A f�ggv�ny fejl�ce (ki�r�shoz)
	virtual std::string getSignature() const = 0;
};

/// Nem built in f�ggv�ny
class ExpressionFunctionPointer : public FunctionPointer
{
private:
	/// A f�ggv�ny param�tereinek azonos�t�i
	std::vector<std::string> parameters;
	/// A f�ggv�ny kifejez�se (ezt �rt�kelj�k ki h�v�skor)
	const Expression* expression;
public:
	/// @param parameters A f�ggv�ny param�tereinek azonos�t�i
	/// @param expression A f�ggv�ny kifejez�se (ezt �rt�kelj�k ki h�v�skor)
	ExpressionFunctionPointer(const std::vector<std::string>& parameters, const Expression* expression);
	~ExpressionFunctionPointer();

	std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<const Expression*> params, int startLine, int startColumn) override;
	std::string getSignature() const override;
};