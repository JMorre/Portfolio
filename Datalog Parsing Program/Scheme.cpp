#include "Scheme.h"

Scheme::Scheme() { //

}

Scheme::~Scheme() { //

}

void Scheme::SetLeadID(Token* NewID) {
	LeadID = *NewID;
}

void Scheme::AddNewID(Token* NewID) {
	IDList.push_back(NewID);
}

std::string Scheme::GetLeadIDString() const {
	return this->LeadID.ReturnString();
}

std::vector<Token*> Scheme::GetIDList() {
	return IDList;
}