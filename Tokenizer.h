#pragma once

#include "Token.h"
#include <vector>
#include <string>

/// A forráskódot Token-ekre bontja szét
class Tokenizer
{
private:
	/// Feldolgozásra váró forráskód
	std::string source;

	/// A feldolgozott karakter jelenlegi indexe (0-val kezdődik)
	int currIndex = 0;

	/// A feldogozott sor száma (1-gyel kezdődik)
	int currLine = 1;

	/// A feldogozott oszlop száma (1-gyel kezdődik)
	int currColumn = 1;
public:
	/// Beállítja a Tokenizer-t egy forráskódra
	/// @param source Forráskód
	Tokenizer(std::string source);

	/// Visszaadja a forráskódból előállított Token listát
	/// @note A tokenize függvény akárhányszor meghívható, de mindig ugyanazt az eredményt adja, nem érdemes többször meghívni.
	std::vector<Token*> tokenize();

private:
	/// Feldolgozza a következő számot
	Token* parseNumber();

	/// Feldolgozza a következő szót
	/// Ami lehet IdentifierToken, BoolToken vagy UndefinedToken.
	Token* parseWord();

	/// Feldolgozza a következő szimbólumot
	/// Ami lehet SymbolToken vagy UnknownToken
	Token* parseSymbol();

	/// Megmondja végére értünk-e a feldolgozott forráskódnak
	bool isOver();

	/// Visszaadja az éppen feldolgozott karaktert
	char currentChar();

	/// Visszaadja az éppen feldolgozott karaktert, majd utána lép egyet
	char nextChar();

	/// Eggyel előrenéz, de nem lép a következő karakterre
	char lookAheadChar();

	bool isWhitespace(char c);

	bool isDigit(char c);

	bool isAlphaNumeric(char c);
};