#pragma once
#include "ListType.h"

class HeadPredicate : public ListType {
public:
	HeadPredicate();
	~HeadPredicate();
	void SetLeadID(Token* NewID);
	void AddNewID(Token* NewID);
	std::string GetLeadIDString() const;
	std::vector<Token*> GetIDList();

private:
	Token LeadID;
	std::vector<Token*> IDList;
};