#pragma once

#include <ostream>

class Scope;

class Statement
{
private:
	Scope* scope;
public:
	void print(std::ostream& os);
	void run();
};