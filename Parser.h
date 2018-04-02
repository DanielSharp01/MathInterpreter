#pragma once

#include <vector>
#include <functional>

class Token;
class Expression;
class Statement;

class Parser
{
private:
	/// Token lista iterátorja
	std::vector<Token*>::const_iterator tokensIt;
	/// Parser hiba esetén meghívott callback
	std::function<void(std::string, int, int)> errorCallback;
public:
	/// @ tokenIt Token lista iterátorja
	/// @note Minden Token listához külön Tokenizer példány kell
	Parser(std::vector<Token*>::const_iterator tokensIt, std::function<void(std::string, int, int)> errorCallback);

	/// Feldolgozza a következõ parancsot/állítást
	Statement* parseStatement();
private:
	/// Feldolgozza a következõ kifejezést
	Expression * parseExpression();
	/// Feldolgozza a következõ ConditionalExpression-t vagy átadja a feldolgozást a parseOrExpression-nek
	Expression * parseConditionalExpression();
	/// Feldolgozza a következõ OrExpression-t vagy átadja a feldolgozást a parseAndExpression-nek
	Expression* parseOrExpression();
	/// Feldolgozza a következõ AndExpression-t vagy átadja a feldolgozást a parseRelationalExpression-nek
	Expression* parseAndExpression();
	/// Feldolgozza a következõ RelationalExpression-t vagy átadja a feldolgozást a parseAddSubExpression-nek
	Expression* parseRelationalExpression();
	/// Feldolgozza a következõ AddExpression-t vagy SubExpressiont-t vagy átadja a feldolgozást a parseMulDivModExpression-nek
	Expression* parseAddSubExpression();
	/// Feldolgozza a következõ MulExpression-t, DivExpression-t vagy ModExpressiont-t
	/// vagy átadja a feldolgozást a parsePowExpression-nek
	Expression* parseMulDivModExpression();
	/// Feldolgozza a következõ PowExpression-t vagy átadja a feldolgozást a parseUnaryExpression-nek
	Expression* parsePowExpression();
	/// Feldolgozza a következõ UnaryExpression-t vagy átadja a feldolgozást a parseFunctionCallExpression-nek
	Expression* parseUnaryExpression();
	/// Feldolgozza a következõ FunctionCallExpression-t vagy átadja a feldolgozást a parseBaseExpression-nek
	Expression* parseFunctionCallExpression();
	/// Feldolgozza a következõ zárójeles kifejezést
	Expression* parseParanthesesExpression();
	/// Feldolgozza a következõ literált vagy zárójeles kifejezést
	/// @note Hiba esetén Expected expression hibaüzenetet dob
	Expression* parseBaseExpression();

	/// Megmondja végére értünk-e a feldolgozott Token sorozatnak
	bool isOver();
	/// Visszaadja a jelenleg feldolgozott Token-t
	Token* currentToken();
	/// Visszaadja a jelenleg feldolgozott Token-t, majd lép egyet
	Token* nextToken();
	/// Visszalépteti az iterátort
	/// @param by Ennyit léptet vissza
	void rollBack(int by);
	/// Visszaadja a jelenleg feldolgozott Token kezdõ sorát
	/// @see Token::line
	int currentLine();
	/// Visszaadja a jelenleg feldolgozott Token kezdõ sorát
	/// @see Token::column
	int currentColumn();
};