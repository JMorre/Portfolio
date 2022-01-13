#pragma once
#include "ListType.h"

class Scheme : public ListType {
public:
	Scheme();
	~Scheme();
	void SetLeadID(Token* NewID);
	void AddNewID(Token* NewID);
	std::string GetLeadIDString() const;
	std::vector<Token*> GetIDList();

private:
	Token LeadID;
	std::vector<Token*> IDList;
};