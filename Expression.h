#pragma once

#include "Statement.h"

/// Egy kiértékelhető kifejezés
class Expression : public Statement
{
	//TypedValue evaluate(Scope* scope, FunctionFrame* frame);
	void print(std::ostream& os) const override;
	//void run() const override;
};