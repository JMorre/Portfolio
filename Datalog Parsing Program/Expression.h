#pragma once
#include "Parameter.h"

class Expression : public Parameter {
public:
	Expression();
	~Expression();
	void SetFirstParam(Parameter* NewParam);
	void SetSecondParam(Parameter* NewParam);
	void SetOperator(Token* NewOp);
	std::string ToString() const;

private:
	void Abstract() {}
	Parameter* FirstParam;
	Parameter* SecondParam;
	Token Operator;
};