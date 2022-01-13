#include "datalogProgram.h"

datalogProgram::datalogProgram() { //

}

datalogProgram::~datalogProgram() { //

}

void datalogProgram::AddScheme(Scheme* NewScheme) {
	SchemeList.push_back(NewScheme);
}

void datalogProgram::AddFact(Fact* NewFact) {
	FactList.push_back(NewFact);
}

void datalogProgram::AddRule(Rule* NewRule) {
	RuleList.push_back(NewRule);
}

void datalogProgram::AddQuery(Query* NewQuery) {
	QueryList.push_back(NewQuery);
}

void datalogProgram::CreateDomain() {
	std::string temp;
	bool Add;

	for (int i = 0; i < FactList.size(); i++) {
		std::vector<Token*> List = FactList.at(i)->GetStringList();
		for (int j = 0; j < List.size(); j++) {
			Add = true;
			temp = List.at(j)->ReturnString();
			for (int k = 0; k < Domain.size(); k++) {
				if (Domain.at(k) == temp) {
					Add = false;
					break;
				}
			}
			if (Add) Domain.push_back(temp);
		}
	}

	std::sort(Domain.begin(), Domain.end());

	return;
}

std::string datalogProgram::PrintLists() const {
	std::stringstream ss;
	std::string temp;

	ss << "Schemes(" << SchemeList.size() << "):\n";
	for (int i = 0; i < SchemeList.size(); i++) {
		temp = SchemeList.at(i)->GetLeadIDString();
		ss << "  " << temp << "(";
		std::vector<Token*> List = SchemeList.at(i)->GetIDList();
		for (int j = 0; j < List.size(); j++) {
			temp = List.at(j)->ReturnString();
			ss << temp;
			if (j != List.size() - 1) ss << ",";
			else ss << ")\n";
		}
	}

	ss << "Facts(" << FactList.size() << "):\n";
	for (int i = 0; i < FactList.size(); i++) {
		temp = FactList.at(i)->GetLeadIDString();
		ss << "  " << temp << "(";
		std::vector<Token*> List = FactList.at(i)->GetStringList();
		for (int j = 0; j < List.size(); j++) {
			temp = List.at(j)->ReturnString();
			ss << temp;
			if (j != List.size() - 1) ss << ",";
			else ss << ").\n";
		}
	}

	ss << "Rules(" << RuleList.size() << "):\n";
	for (int i = 0; i < RuleList.size(); i++) {
		temp = RuleList.at(i)->GetHeadPredicate()->GetLeadIDString();
		ss << "  " << temp << "(";
		std::vector<Token*> List = RuleList.at(i)->GetHeadPredicate()->GetIDList();
		for (int j = 0; j < List.size(); j++) {
			temp = List.at(j)->ReturnString();
			ss << temp;
			if (j != List.size() - 1) ss << ",";
			else ss << ") :- ";
		}
		std::vector<Predicate*> *ListPtr = RuleList.at(i)->GetPredicateList();
		for (int j = 0; j < ListPtr->size(); j++) {
			temp = ListPtr->at(j)->ToString();
			ss << temp;
			if (j != ListPtr->size() - 1) ss << ",";
			else ss << ".\n";
		}
	}

	ss << "Queries(" << QueryList.size() << "):\n";
	for (int i = 0; i < QueryList.size(); i++) {
		temp = QueryList.at(i)->GetPredicateList()->at(0)->ToString();
		ss << "  " << temp << "?\n";
	}

	ss << "Domain(" << Domain.size() << "):\n";
	for (int i = 0; i < Domain.size(); i++) {
		temp = Domain.at(i);
		ss << "  " << temp;
		if (i != Domain.size() - 1) ss << "\n";
	}

	return ss.str();
}

std::vector<Fact*> datalogProgram::GetFactList() const {
	std::vector<Fact*> ReturnList;
	Fact *Current;

	for (int i = 0; i < FactList.size(); i++) {
		Current = new Fact;
		*Current = *FactList.at(i);
		ReturnList.push_back(Current);
	}

	return ReturnList;
}

std::vector<Query*> datalogProgram::GetQueryList() const {
	std::vector<Query*> ReturnList;
	Query *Current;

	for (int i = 0; i < QueryList.size(); i++) {
		Current = new Query;
		*Current = *QueryList.at(i);
		ReturnList.push_back(Current);
	}

	return ReturnList;
}