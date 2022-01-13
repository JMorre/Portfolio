#include "Token.h"

Token::Token() {
	Type = UNDEFINED;
	Line = 0;
	String = "";
}

Token::Token(Tokens NewType, int NewLine, std::string NewString) { //initialize token with the values sent by constructor
	Type = NewType;
	Line = NewLine;
	String = NewString;
}

Tokens Token::ReturnType() const { //return the type if requested
	return Type;
}

std::string Token::ReturnTypeString() const { //convert the type to a string and return it
	switch (Type) {
	case COMMA:return "COMMA";
	case PERIOD:return "PERIOD";
	case Q_MARK:return "Q_MARK";
	case LEFT_PAREN:return "LEFT_PAREN";
	case RIGHT_PAREN:return "RIGHT_PAREN";
	case COLON:return "COLON";
	case COLON_DASH:return "COLON_DASH";
	case MULTIPLY:return "MULTIPLY";
	case ADD:return "ADD";
	case SCHEMES:return "SCHEMES";
	case FACTS:return "FACTS";
	case RULES:return "RULES";
	case QUERIES:return "QUERIES";
	case ID:return "ID";
	case STRING:return "STRING";
	case COMMENT:return "COMMENT";
	case WHITESPACE:return "WHITESPACE";
	case UNDEFINED:return "UNDEFINED";
	case EndOfFile:return "EOF";
	}
}

std::string Token::ReturnString() const { //return the string held by the token
	return String;
}

int Token::ReturnLine() const { //return the line value held by the token
	return Line;
}

void Token::SetString(std::string NewString) {
	String = NewString;
}