#pragma once
#include "ListType.h"
#include "Parameter.h"
#include <sstream>

class Predicate : public ListType {
public:
	Predicate();
	~Predicate();
	void SetLeadID(Token* NewID);
	std::vector<Parameter*>* GetParamList();
	std::string ToString() const;
	Token LeadID;

private:
	
	std::vector<Parameter*> ParamList;
};