#pragma once
#include <vector>
#include "Token.h"
class Predicate;

class ListType {
public:
	ListType();
	~ListType();
	virtual void AddNewID(Token* NewID);
	virtual std::vector<Predicate*>* GetPredicateList();
	//virtual void AddNewString(Token* NewString);
	//virtual HeadPredicate* GetHeadPredicate();
	//virtual std::vector<Predicate*>* GetPredicateList();
	//virtual std::vector<Parameter*>* GetParamList();

private:
	//Token LeadID;
	//HeadPredicate Head;
	//std::vector<Token*> IDList;
	//std::vector<Token*> StringList;
	//std::vector<Predicate*> PredicateList;
	//std::vector<Parameter*> ParamList;
};