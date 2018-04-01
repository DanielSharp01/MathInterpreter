#pragma once

#include <vector>

class Token;
class Expression;

class Parser
{
private:
	/// Token lista iter�torja
	std::vector<Token*>::const_iterator tokensIt;
public:
	/// @ tokenIt Token lista iter�torja
	/// @note Minden Token list�hoz k�l�n Tokenizer p�ld�ny kell
	Parser(std::vector<Token*>::const_iterator tokensIt);
	/// Feldolgozza a k�vetkez� kifejez�st
	Expression* parseExpression();

private:
	/// Feldolgozza a k�vetkez� ConditionalExpression-t vagy �tadja a feldolgoz�st a parseOrExpression-nek
	Expression * parseConditionalExpression();
	/// Feldolgozza a k�vetkez� OrExpression-t vagy �tadja a feldolgoz�st a parseAndExpression-nek
	Expression* parseOrExpression();
	/// Feldolgozza a k�vetkez� AndExpression-t vagy �tadja a feldolgoz�st a parseRelationalExpression-nek
	Expression* parseAndExpression();
	/// Feldolgozza a k�vetkez� RelationalExpression-t vagy �tadja a feldolgoz�st a parseAddSubExpression-nek
	Expression* parseRelationalExpression();
	/// Feldolgozza a k�vetkez� AddExpression-t vagy SubExpressiont-t vagy �tadja a feldolgoz�st a parseMulDivModExpression-nek
	Expression* parseAddSubExpression();
	/// Feldolgozza a k�vetkez� MulExpression-t, DivExpression-t vagy ModExpressiont-t
	/// vagy �tadja a feldolgoz�st a parsePowExpression-nek
	Expression* parseMulDivModExpression();
	/// Feldolgozza a k�vetkez� PowExpression-t vagy �tadja a feldolgoz�st a parseUnaryExpression-nek
	Expression* parsePowExpression();
	/// Feldolgozza a k�vetkez� UnaryExpression-t vagy �tadja a feldolgoz�st a parseFunctionCallExpression-nek
	Expression* parseUnaryExpression();
	/// Feldolgozza a k�vetkez� FunctionCallExpression-t vagy �tadja a feldolgoz�st a parseBaseExpression-nek
	Expression* parseFunctionCallExpression();
	/// Feldolgozza a k�vetkez� z�r�jeles kifejez�st
	Expression* parseParanthesesExpression();
	/// Feldolgozza a k�vetkez� liter�lt vagy z�r�jeles kifejez�st
	/// @note Hiba eset�n Expected expression hiba�zenetet dob
	Expression* parseBaseExpression();

	/// Megmondja v�g�re �rt�nk-e a feldolgozott Token sorozatnak
	bool isOver();
	/// Visszaadja a jelenleg feldolgozott Token-t
	Token* currentToken();
	/// Visszaadja a jelenleg feldolgozott Token-t, majd l�p egyet
	Token* nextToken();
	/// Visszaadja a jelenleg feldolgozott Token kezd� sor�t
	/// @see Token::line
	int currentLine();
	/// Visszaadja a jelenleg feldolgozott Token kezd� sor�t
	/// @see Token::column
	int currentColumn();
};