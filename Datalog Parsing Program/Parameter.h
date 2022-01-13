#pragma once
#include <sstream>
#include "Token.h"

class Parameter {
public:
	Parameter();
	~Parameter();
	virtual void SetData(Token* NewData) {}
	virtual void SetFirstParam(Parameter* NewParam) {}
	virtual void SetSecondParam(Parameter* NewParam) {}
	virtual void SetOperator(Token* NewOp) {}
	virtual std::string ToString() const { return ""; }
	virtual Token* GetData() { return NULL; }

private:
	virtual void Abstract() = 0;
};