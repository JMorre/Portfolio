#pragma once
#include "DatalogParser.h"
#include "relation.h"

class database {
public:
	database(datalogProgram D);
	~database();

	void RunQueries();

private:
	std::vector<Query*>* QueryList;
	std::vector<Fact*>* FactList;
	bool InterpretQuery(int n);
	void PrintQueryResults(int n, std::vector<Token*> VariableTokens) const;

	datalogProgram D;
	relation R;
};