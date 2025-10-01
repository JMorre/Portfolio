#include "Predicate.h"

Predicate::Predicate() {//
						//std::vector<Parameter*> P;
						//ParamList = P;
}

Predicate::~Predicate() {//

}

void Predicate::SetLeadID(Token* NewID) {//
	LeadID = *NewID;
}

std::vector<Parameter*>* Predicate::GetParamList() {//
	return &ParamList;
}

std::string Predicate::ToString() const {
	std::stringstream ss;

	ss << LeadID.ReturnString() << "(";
	for (int i = 0; i < ParamList.size(); i++) {
		ss << ParamList.at(i)->ToString();
		if (i != ParamList.size() - 1) ss << ",";
		else ss << ")";
	}

	return ss.str();
}