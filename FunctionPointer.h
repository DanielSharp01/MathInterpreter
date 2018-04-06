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
private:
	/// A f�ggv�ny param�tereinek azonos�t�i
	std::vector<std::string> parameters;
	/// A f�ggv�ny kifejez�se (ezt �rt�kelj�k ki h�v�skor)
	const Expression* expression;
public:
	/// @param identifier A f�ggv�ny azonos�t�ja
	/// @param parameters A f�ggv�ny param�tereinek azonos�t�i
	/// @param expression A f�ggv�ny kifejez�se (ezt �rt�kelj�k ki h�v�skor)
	FunctionPointer(const std::vector<std::string>& parameters, const Expression* expression);
	~FunctionPointer();

	/// @param callingContext A h�v� kontextus
	/// @param paramValues A f�ggv�ny param�terei
	std::shared_ptr<const TypedValue> call(const Context& callingContext, std::vector<std::shared_ptr<const TypedValue>> paramValues);

	/// A f�ggv�ny fejl�ce (ki�r�shoz)
	std::string getSignature() const;
};