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
	/// Parser hiba esetén meghívott callback (Hibaüzenet, Hibás sor, Hibás oszlop)
	std::function<void(std::string, int, int)> errorCallback;
public:
	/// @ tokenIt Token lista iterátorja
	/// @note Minden Token listához külön Tokenizer példány kell
	/// @param errorCallback Parser hiba esetén meghívott callback (Hibaüzenet, Hibás sor, Hibás oszlop)
	Parser(std::vector<Token*>::const_iterator tokensIt, std::function<void(std::string, int, int)> errorCallback);

	/// Feldolgozza a következő parancsot/állítást
	Statement* parseStatement();
private:
	/// Feldolgozza a következő kifejezést
	Expression * parseExpression();
	/// Feldolgozza a következő ConditionalExpression-t vagy átadja a feldolgozást a parseOrExpression-nek
	/// @param ternaryCalls Ha rekurzívan parseoljuk a feltételes kifejezést, akkor lehet az elején ':', amúgy nem
	Expression * parseConditionalExpression(bool ternaryCalls);
	/// Feldolgozza a következő OrExpression-t vagy átadja a feldolgozást a parseAndExpression-nek
	Expression* parseOrExpression();
	/// Feldolgozza a következő AndExpression-t vagy átadja a feldolgozást a parseRelationalExpression-nek
	Expression* parseAndExpression();
	/// Feldolgozza a következő RelationalExpression-t vagy átadja a feldolgozást a parseAddSubExpression-nek
	Expression* parseRelationalExpression();
	/// Feldolgozza a következő AddExpression-t vagy SubExpressiont-t vagy átadja a feldolgozást a parseMulDivModExpression-nek
	Expression* parseAddSubExpression();
	/// Feldolgozza a következő MulExpression-t, DivExpression-t vagy ModExpressiont-t
	/// vagy átadja a feldolgozást a parsePowExpression-nek
	Expression* parseMulDivModExpression();
	/// Feldolgozza a következő PowExpression-t vagy átadja a feldolgozást a parseUnaryExpression-nek
	Expression* parsePowExpression();
	/// Feldolgozza a következő UnaryExpression-t vagy átadja a feldolgozást a parseFunctionCallExpression-nek
	Expression* parseUnaryExpression();
	/// Feldolgozza a következő FunctionCallExpression-t vagy átadja a feldolgozást a parseBaseExpression-nek
	Expression* parseFunctionCallExpression();
	/// Feldolgozza a következő zárójeles kifejezést
	Expression* parseParanthesesExpression();
	/// Feldolgozza a következő literált vagy zárójeles kifejezést
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
	/// Visszaadja a jelenleg feldolgozott Token kezdő sorát
	/// @see Token::line
	int currentLine();
	/// Visszaadja a jelenleg feldolgozott Token kezdő sorát
	/// @see Token::column
	int currentColumn();
};