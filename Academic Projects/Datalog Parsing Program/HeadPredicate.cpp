#include "HeadPredicate.h"

HeadPredicate::HeadPredicate() { //

}

HeadPredicate::~HeadPredicate() { //

}

void HeadPredicate::SetLeadID(Token* NewID) {
	LeadID = *NewID;
}

void HeadPredicate::AddNewID(Token* NewID) {
	IDList.push_back(NewID);
}

std::string HeadPredicate::GetLeadIDString() const {
	return LeadID.ReturnString();
}

std::vector<Token*> HeadPredicate::GetIDList() {
	return IDList;
}