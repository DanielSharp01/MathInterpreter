#include "Parser.h"

#include "Token.h"
#include "Statement.h"
#include "Expression.h"
#include <string>

Parser::Parser(std::vector<Token*>::const_iterator tokensIt, std::function<void(std::string, int, int)> errorCallback)
	: tokensIt(tokensIt), errorCallback(errorCallback)
{ }

Statement* Parser::parseStatement()
{
	int line = currentLine();
	int column = currentColumn();
	int iteratorRollBack = 0;

	bool rollingBack = false;

	if (isOver())
		return nullptr;
	else if (currentToken()->match(TokenType::Identifier))
	{
		std::string identifier = ((IdentifierToken*)nextToken())->getValue();
		iteratorRollBack++;
		if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("="))
		{
			nextToken();
			return new VariableDeclaration(identifier, parseExpression(), line, column);
		}
		else if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("("))
		{
			std::vector<std::string> params;
			do
			{
				nextToken();
				iteratorRollBack++;
				if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(")")) break;

				if (currentToken()->match(TokenType::Identifier))
				{
					params.push_back(((IdentifierToken*)nextToken())->getValue());
					iteratorRollBack++;
				}
				else
					rollingBack = true;
			} while (!rollingBack && currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(","));

			if (!rollingBack)
			{
				if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(")"))
				{
					nextToken();
					iteratorRollBack++;
				}
				else rollingBack = true;
			}
			
			if (!rollingBack)
			{
				if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("="))
				{
					nextToken();
					return new FunctionDeclaration(identifier, params, parseExpression(), line, column);
				}
				else rollingBack = true;
			}
		}
	}

	rollBack(iteratorRollBack);
	return parseExpression();
}

Expression* Parser::parseExpression()
{
	return parseConditionalExpression(false);
}

Expression* Parser::parseConditionalExpression(bool ternaryCalls)
{
	int line = currentLine();
	int column = currentColumn();
	Expression* condition = parseOrExpression();
	
	//Ennek itt kell lennie, mert amúgy ':' karakter magában '?' nélkül elkezdene loopolni
	if (!ternaryCalls && currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(":"))
	{
		errorCallback("Unexpected symbol ':', you may have missed the '?' from the conditional expression", currentLine(), currentColumn());
		nextToken();
		return parseExpression();
	}

	if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("?"))
	{
		nextToken();
		Expression* left = parseConditionalExpression(true);
		if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(":"))
		{
			nextToken();
			return new ConditionalExpression(condition, left, parseConditionalExpression(true), line, column);
		}
		else
		{
			errorCallback("Expected right side of the conditional/ternary expression", currentLine(), currentColumn());
			return new ConditionalExpression(condition, left, nullptr, line, column);
		}
	}
	else
	{
		return condition;
	}
}

Expression* Parser::parseOrExpression()
{
	int line = currentLine();
	int column = currentColumn();
	Expression* left = parseAndExpression();
	while (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("|"))
	{
		nextToken();
		Expression* right = parseAndExpression();
		left = new OrExpression(left, right, line, column);
	}

	return left;
}

Expression* Parser::parseAndExpression()
{
	int line = currentLine();
	int column = currentColumn();
	Expression* left = parseRelationalExpression();
	while (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("&"))
	{
		nextToken();
		Expression* right = parseRelationalExpression();
		left = new AndExpression(left, right, line, column);
	}

	return left;
}

Expression* Parser::parseRelationalExpression()
{
	int line = currentLine();
	int column = currentColumn();
	Expression* left = parseAddSubExpression();
	while (currentToken()->match(TokenType::Symbol) && (((SymbolToken*)currentToken())->match("<")
		|| ((SymbolToken*)currentToken())->match(">") || ((SymbolToken*)currentToken())->match("<=")
		|| ((SymbolToken*)currentToken())->match(">=") || ((SymbolToken*)currentToken())->match("==")
		|| ((SymbolToken*)currentToken())->match("!=")))
	{
		std::string relSymbol = ((SymbolToken*)currentToken())->getValue();
		nextToken();
		Expression* right = parseAddSubExpression();
		if (relSymbol == "<")
			left = new LessExpression(left, right, line, column);
		else if (relSymbol == ">")
			left = new GreaterExpression(left, right, line, column);
		else if (relSymbol == "<=")
			left = new LessEqualsExpression(left, right, line, column);
		else if (relSymbol == ">=")
			left = new GreaterEqualsExpression(left, right, line, column);
		else if (relSymbol == "==")
			left = new EqualsExpression(left, right, line, column);
		else //if (relSymbol == "!=")
			left = new NotEqualsExpression(left, right, line, column);
	}

	return left;
}

Expression * Parser::parseAddSubExpression()
{
	int line = currentLine();
	int column = currentColumn();
	Expression* left = parseMulDivModExpression();
	while (currentToken()->match(TokenType::Symbol) &&
			(((SymbolToken*)currentToken())->match("+") || ((SymbolToken*)currentToken())->match("-")))
	{
		std::string op = ((SymbolToken*)currentToken())->getValue();
		nextToken();
		Expression* right = parseMulDivModExpression();
		if (op == "+")
			left = new AddExpression(left, right, line, column);
		else //if (op == "-")
			left = new SubExpression(left, right, line, column);
	}

	return left;
}

Expression* Parser::parseMulDivModExpression()
{
	int line = currentLine();
	int column = currentColumn();
	Expression* left = parsePowExpression();
	while (currentToken()->match(TokenType::Symbol) && (((SymbolToken*)currentToken())->match("*") 
		|| ((SymbolToken*)currentToken())->match("/") || ((SymbolToken*)currentToken())->match("%")))
	{
		std::string op = ((SymbolToken*)currentToken())->getValue();
		nextToken();
		Expression* right = parsePowExpression();
		if (op == "*")
			left = new MulExpression(left, right, line, column);
		else if (op == "/")
			left = new DivExpression(left, right, line, column);
		else //if (op == "%")
			left = new ModExpression(left, right, line, column);
	}

	return left;
}

Expression* Parser::parsePowExpression()
{
	int line = currentLine();
	int column = currentColumn();
	Expression* left = parseUnaryExpression();
	while (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("^"))
	{
		nextToken();
		Expression* right = parseUnaryExpression();
		left = new PowExpression(left, right, line, column);
	}

	return left;
}

Expression* Parser::parseUnaryExpression()
{
	int line = currentLine();
	int column = currentColumn();
	if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("-"))
	{
		nextToken();
		return new NegExpression(parseUnaryExpression(), line, column);
	}
	else if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("+"))
	{
		nextToken();
		return parseUnaryExpression();
	}
	else if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("!"))
	{
		nextToken();
		return new NotExpression(parseUnaryExpression(), line, column);
	}
	
	return parseFunctionCallExpression();
}

Expression* Parser::parseFunctionCallExpression()
{
	int line = currentLine();
	int column = currentColumn();
	Expression* called = parseBaseExpression();
	if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("("))
	{
		std::vector<const Expression*> params;
		do
		{
			nextToken();
			if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(")")) break;

			params.push_back(parseExpression());
		} while (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(","));

		if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(")"))
		{
			nextToken();
		}
		else
		{
			errorCallback("Expected closing ')'", currentLine(), currentColumn());
		}

		return new FunctionCallExpression(called, params, line, column);
	}
	else
	{
		return called;
	}
}

Expression* Parser::parseParanthesesExpression()
{
	nextToken();

	Expression* expr = parseExpression();

	if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(")"))
	{
		nextToken();
	}
	else
	{
		errorCallback("Expected closing ')'", currentLine(), currentColumn());
	}

	return expr;
}

Expression * Parser::parseBaseExpression()
{
	int line = currentLine();
	int column = currentColumn();
	if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("("))
	{
		return parseParanthesesExpression();
	}
	else if (currentToken()->match(TokenType::NumberLiteral))
	{
		return new NumberExpression(((NumberToken*)nextToken())->getValue(), line, column);
	}
	else if (currentToken()->match(TokenType::BoolLiteral))
	{
		return new BoolExpression(((BoolToken*)nextToken())->getValue(), line, column);
	}
	else if (currentToken()->match(TokenType::Identifier))
	{
		return new IdentifierExpression(((IdentifierToken*)nextToken())->getValue(), line, column);
	}
	else if (currentToken()->match(TokenType::UndefinedLiteral))
	{
		nextToken();
		return new UndefinedExpression(line, column);
	}
	else
	{
		//Ide kerül minden token, amit nem lehet expression-ben használni, mert ha azt nem skippeljük, akkor elkezd loopolni a parseExpression függvény
		if (currentToken()->match(TokenType::Unknown))
			nextToken(); //Már ki lett írva mint Tokenizer hiba
		else if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("="))
		{
			errorCallback("Unexpected symbol '" + ((SymbolToken*)currentToken())->getValue() + "'", currentLine(), currentColumn());
			nextToken();
		}
		else
		{
			errorCallback("Expected expression", currentLine(), currentColumn());
		}
		
		return new UndefinedExpression(currentLine(), currentColumn());
	}
}

bool Parser::isOver()
{
	return (*tokensIt)->match(TokenType::Ending);
}

Token * Parser::currentToken()
{
	return *tokensIt;
}

Token * Parser::nextToken()
{
	return *tokensIt++;
}

void Parser::rollBack(int by)
{
	tokensIt -= by;
}

int Parser::currentLine()
{
	return currentToken()->getLine();
}

int Parser::currentColumn()
{
	return currentToken()->getColumn();
}
