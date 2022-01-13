#include "Query.h"

Query::Query() { //

}

Query::~Query() { //

}

std::vector<Predicate*>* Query::GetPredicateList() {
	return &PredicateList;
}