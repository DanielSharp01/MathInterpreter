#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>

class TypedValue;

class FunctionContext;

/// Változó azonosítokat old fel értékké
class Context
{
public:
	/// Felold egy azonosítót értékké
	/// @param indentifier Feloldandó azonosító
	virtual std::shared_ptr<const TypedValue> resolveIdentifier(std::string identifier) const = 0;

	/// Loggol egy hibát
	/// @param message Hibaüzenet 
	/// @param line Hibás sor (hiba elõfordulási helye)
	/// @param column Hibás oszlop (hiba elõfordulási helye)
	virtual void logError(std::string message, int line, int column) const = 0;

	/// Csinál egy függvénykontextust a megfelelõ paraméterekkel
	/// @param indentifiers Paraméterek azonosítói
	/// @param values Paraméterek értékei
	virtual FunctionContext makeFunctionContext(const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values) const = 0;
};

/// Globális változók tárolója
class GlobalContext : public Context
{
private:
	/// Runtime hiba esetén meghívott callback (Hibaüzenet, Hibás sor, Hibás oszlop)
	std::function<void(std::string, int, int)> errorCallback;
	/// Azonosító - érték mapping (változók táblája)
	std::unordered_map<std::string, std::shared_ptr<const TypedValue>> variables;
public:
	/// @param errorCallback Runtime hiba esetén meghívott callback (Hibaüzenet, Hibás sor, Hibás oszlop)
	GlobalContext(std::function<void(std::string, int, int)> errorCallback);
	/// Definiál egy változó értéket
	/// @param indentifier Változó azonosítója
	/// @param value Változó értéke
	void defineVariable(std::string identifier, std::shared_ptr<const TypedValue> value);
	std::shared_ptr<const TypedValue> resolveIdentifier(std::string identifier) const override;
	void logError(std::string message, int line, int column) const override;
	FunctionContext makeFunctionContext(const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values) const override;

};

/// Függvényhívások változóit és egy GlobalContext-et tartalmaz
class FunctionContext : public Context
{
private:
	/// Hívó kontextus, amivel feloldhatóak a globális változók
	const GlobalContext& callingContext;
	/// Azonosító - érték mapping (függvényparaméterek táblája)
	std::unordered_map<std::string, std::shared_ptr<const TypedValue>> parameters;
public:
	/// @param callingContext Hívó kontextus, amivel feloldhatóak a globális változók
	/// @param indentifiers Paraméterek azonosítói
	/// @param values Paraméterek értékei
	FunctionContext(const GlobalContext& callingContext, const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values);
	std::shared_ptr<const TypedValue> resolveIdentifier(std::string identifier) const override;
	void logError(std::string message, int line, int column) const override;
	FunctionContext makeFunctionContext(const std::vector<std::string>& identifiers, const std::vector<std::shared_ptr<const TypedValue>>& values) const override;
};