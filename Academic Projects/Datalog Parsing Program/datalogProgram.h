#pragma once
#include "ListType.h"
#include "Scheme.h"
#include "Fact.h"
#include "Rule.h"
#include "Query.h"
#include "HeadPredicate.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Expression.h"
#include "DataParam.h"
#include <sstream>
#include <algorithm>

class datalogProgram {
public:
	datalogProgram();
	~datalogProgram();
	void CreateDomain();
	void AddScheme(Scheme* NewScheme);
	void AddFact(Fact* NewFact);
	void AddRule(Rule* NewRule);
	void AddQuery(Query* NewQuery);
	std::string PrintLists() const;
	std::vector<Fact*> GetFactList() const;
	std::vector<Query*> GetQueryList() const;

private:
	std::vector<Scheme*> SchemeList;
	std::vector<Fact*> FactList;
	std::vector<Rule*> RuleList;
	std::vector<Query*> QueryList;
	std::vector<std::string> Domain;
};