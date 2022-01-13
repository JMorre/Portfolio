#pragma once
#include "ListType.h"

class Fact : public ListType {
public:
	Fact();
	~Fact();
	void SetLeadID(Token* NewID);
	void AddNewString(Token* NewID);
	std::string GetLeadIDString() const;
	std::vector<Token*> GetStringList();
	std::vector<Token*> StringList;

private:
	Token LeadID;

};