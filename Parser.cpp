#include "Parser.h"

#include "Token.h"
#include "Expression.h"

Parser::Parser(std::vector<Token*>::const_iterator tokensIt)
	: tokensIt(tokensIt)
{ }

Expression* Parser::parseExpression()
{
	if (isOver())
		return nullptr;
	else
		parseConditionalExpression();
}

Expression* Parser::parseConditionalExpression()
{
	int line = currentLine();
	int column = currentColumn();
	Expression* condition = parseOrExpression();
	if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match("?"))
	{
		nextToken();
		Expression* left = parseConditionalExpression();
		if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(":"))
		{
			nextToken();
			return new ConditionalExpression(condition, left, parseConditionalExpression(), line, column);
		}
		else
		{
			//TODO: ERROR
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
			params.push_back(parseExpression());
		} while (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(","));
		
		if (currentToken()->match(TokenType::Symbol) && ((SymbolToken*)currentToken())->match(")"))
		{
			nextToken();
		}
		else; //TODO: ERROR

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
	else; //TODO: ERROR

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
		//TODO: ERROR
		return nullptr;
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

int Parser::currentLine()
{
	return currentToken()->getLine();
}

int Parser::currentColumn()
{
	return currentToken()->getColumn();
}
