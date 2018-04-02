#pragma once

#include "Token.h"
#include <vector>
#include <string>
#include <functional>

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
	/// Tokenizer hiba esetén meghívott callback
	std::function<void(std::string, int, int)> errorCallback;
public:
	/// @param source Forráskód
	/// @note Minden forráskódhoz külön Tokenizer példány kell
	Tokenizer(std::string source, std::function<void(std::string, int, int)> errorCallback);

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

	/// Whitespace-e?
	/// @param c Vizsgált karakter
	bool isWhitespace(char c);
	/// Számjegy-e?
	/// @param c Vizsgált karakter
	bool isDigit(char c);
	/// Betű vagy számjegy-e?
	/// @param c Vizsgált karakter
	bool isAlphaNumeric(char c);
};