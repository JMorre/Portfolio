#pragma once
#include <string>

enum Tokens {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD,
	SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, EndOfFile
};
//List of possible token values


class Token {
public:
	Token();
	Token(Tokens NewType, int NewLine, std::string NewString);
	~Token() {}

	Tokens ReturnType() const;
	std::string ReturnTypeString() const;
	std::string ReturnString() const;
	int ReturnLine() const;
	void SetString(std::string NewString);


private:
	Tokens Type;
	std::string String;
	int Line;
};
