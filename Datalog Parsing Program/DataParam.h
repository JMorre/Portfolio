#pragma once
#include "Parameter.h"

class DataParam : public Parameter {
public:
	DataParam();
	~DataParam();
	void SetData(Token* NewData);
	std::string ToString() const;
	Token* GetData();

private:
	void Abstract() {}
	Token Data;
};