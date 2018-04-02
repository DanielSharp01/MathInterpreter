#pragma once

#include <string>
#include <vector>

class FunctionFrame;
class Expression;
class FunctionCallExpression;
class Context;

/// F�ggv�ny pointer
class FunctionPointer
{
private:
	/// Kontextus, ami t�rolja a v�ltoz�kat �s a Stack-et
	const Context& context;
	/// A f�ggv�ny azonos�t�ja
	std::string identifier;
	/// A f�ggv�ny param�terei
	std::vector<std::string> parameters;
	/// A f�ggv�ny �ltal ki�rt�kelt kifejez�s
	const Expression* expression;
public:
	/// @param context Kontextus, ami t�rolja a v�ltoz�kat �s a Stack-et
	/// @param identifier A f�ggv�ny azonos�t�ja
	/// @param parameters A f�ggv�ny param�terei
	/// @param expression A f�ggv�ny �ltal ki�rt�kelt kifejez�s 
	FunctionPointer(const Context& context, std::string identifier, std::vector<std::string> parameters, const Expression* expressions);

	/// F�ggv�ny h�v�s
	/// @param params A param�terezett kifejez�sek
	/// @param context Kontextus, ami t�rolja a v�ltoz�kat �s a Stack-et
	void call(std::vector<const Expression*> params);
};