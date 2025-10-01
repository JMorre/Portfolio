#include "Fact.h"

Fact::Fact() { //

}

Fact::~Fact() { //

}

void Fact::SetLeadID(Token* NewID) {
	LeadID = *NewID;
}

void Fact::AddNewString(Token* NewID) {
	StringList.push_back(NewID);
}

std::string Fact::GetLeadIDString() const {
	return this->LeadID.ReturnString();
}

std::vector<Token*> Fact::GetStringList() {
	return StringList;
}