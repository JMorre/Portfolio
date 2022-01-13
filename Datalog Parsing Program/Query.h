#pragma once
#include "ListType.h"

class Query : public ListType {
public:
	Query();
	~Query();
	std::vector<Predicate*>* GetPredicateList();

private:
	std::vector<Predicate*> PredicateList;
};