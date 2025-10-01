#include "Rule.h"

Rule::Rule() { //

}

Rule::~Rule() { //

}

HeadPredicate* Rule::GetHeadPredicate() {
	return &Head;
}

std::vector<Predicate*>* Rule::GetPredicateList() {
	return &PredicateList;
}