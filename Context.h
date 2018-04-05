#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>

class TypedValue;

class FunctionContext;

/// V�ltoz� azonos�tokat old fel �rt�kk�
class Context
{
public:
	/// Felold egy azonos�t�t �rt�kk�
	/// @param indentifier Feloldand� azonos�t�
	virtual std::shared_ptr<const TypedValue> resolveIdentifier(std::string identifier) const = 0;

	/// Loggol egy hib�t
	/// @param message Hiba�zenet 
	/// @param line Hib�s sor (hiba el�fordul�si helye)
	/// @param column Hib�s oszlop (hiba el�fordul�si helye)
	virtual void logError(std::string message, int line, int column) const = 0;

	/// Csin�l egy f�ggv�nykontextust a megfelel� param�terekkel
	/// @param indentifiers Param�terek azonos�t�i
	/// @param values Param�terek �rt�kei
	virtual FunctionContext makeFunctionContext(const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values) const = 0;
};

/// Glob�lis v�ltoz�k t�rol�ja
class GlobalContext : public Context
{
private:
	/// Runtime hiba eset�n megh�vott callback (Hiba�zenet, Hib�s sor, Hib�s oszlop)
	std::function<void(std::string, int, int)> errorCallback;
	/// Azonos�t� - �rt�k mapping (v�ltoz�k t�bl�ja)
	std::unordered_map<std::string, std::shared_ptr<const TypedValue>> variables;
public:
	/// @param errorCallback Runtime hiba eset�n megh�vott callback (Hiba�zenet, Hib�s sor, Hib�s oszlop)
	GlobalContext(std::function<void(std::string, int, int)> errorCallback);
	/// Defini�l egy v�ltoz� �rt�ket
	/// @param indentifier V�ltoz� azonos�t�ja
	/// @param value V�ltoz� �rt�ke
	void defineVariable(std::string identifier, std::shared_ptr<const TypedValue> value);
	std::shared_ptr<const TypedValue> resolveIdentifier(std::string identifier) const override;
	void logError(std::string message, int line, int column) const override;
	FunctionContext makeFunctionContext(const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values) const override;

};

/// F�ggv�nyh�v�sok v�ltoz�it �s egy GlobalContext-et tartalmaz
class FunctionContext : public Context
{
private:
	/// H�v� kontextus, amivel feloldhat�ak a glob�lis v�ltoz�k
	const GlobalContext& callingContext;
	/// Azonos�t� - �rt�k mapping (f�ggv�nyparam�terek t�bl�ja)
	std::unordered_map<std::string, std::shared_ptr<const TypedValue>> parameters;
public:
	/// @param callingContext H�v� kontextus, amivel feloldhat�ak a glob�lis v�ltoz�k
	/// @param indentifiers Param�terek azonos�t�i
	/// @param values Param�terek �rt�kei
	FunctionContext(const GlobalContext& callingContext, const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values);
	std::shared_ptr<const TypedValue> resolveIdentifier(std::string identifier) const override;
	void logError(std::string message, int line, int column) const override;
	FunctionContext makeFunctionContext(const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values) const override;
};