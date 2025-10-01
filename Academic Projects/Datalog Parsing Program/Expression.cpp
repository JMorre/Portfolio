#include "Expression.h"

Expression::Expression() { //

}

Expression::~Expression() { //

}

void Expression::SetFirstParam(Parameter* NewParam) {
	FirstParam = NewParam;
}

void Expression::SetSecondParam(Parameter* NewParam) {
	SecondParam = NewParam;
}

void Expression::SetOperator(Token* NewOp) {
	Operator = *NewOp;
}

std::string Expression::ToString() const {
	std::stringstream ss;

	ss << "(" << FirstParam->ToString() << Operator.ReturnString() << SecondParam->ToString() << ")";

	return ss.str();
}