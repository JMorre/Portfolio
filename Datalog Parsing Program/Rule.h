#pragma once
#include "ListType.h"
#include "HeadPredicate.h"

class Rule : public ListType {
public:
	Rule();
	~Rule();
	HeadPredicate* GetHeadPredicate();
	std::vector<Predicate*>* GetPredicateList();

private:
	HeadPredicate Head;
	std::vector<Predicate*> PredicateList;
};