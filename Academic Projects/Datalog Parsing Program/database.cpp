#include "database.h"

database::database(datalogProgram D) {
	this->D = D;
}

database::~database() {

}

void database::RunQueries() {
	QueryList = new std::vector<Query*>;
	*QueryList = D.GetQueryList();
	FactList = new std::vector<Fact*>;
	*FactList = D.GetFactList();
	for (int i = 0; i < QueryList->size(); i++) {
		InterpretQuery(i);
	}
	for (int i = QueryList->size() - 1; i >= 0; i--) delete QueryList->at(i);
	delete QueryList;
	for (int i = FactList->size() - 1; i >= 0; i--) delete FactList->at(i);
	delete FactList;
}

int TokenPresent(Token* Current, const std::vector<Token*> VariableTokens) {
	for (int i = 0; i < VariableTokens.size(); i++) {
		if (Current->ReturnString() == VariableTokens.at(i)->ReturnString()) return i;
	}
	return -1;
}

void database::PrintQueryResults(int n, std::vector<Token*> VariableTokens) const {
	std::stringstream ss;
	ss << QueryList->at(n)->GetPredicateList()->at(0)->LeadID.ReturnString() << "(";
	int size = QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->size();
	for (int i = 0; i < size; i++) {
		ss << QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->at(i)->GetData()->ReturnString();
		if (i != size - 1) ss << ",";
	}
	ss << ")? ";
	if (R.List.size() > 0) {
		ss << "Yes(" << R.List.size() << ")";
		size = R.List.size();
		if (VariableTokens.size() > 0) {
			for (int i = 0; i < size; i++) {
				ss << "\n  ";
				for (int j = 0; j < VariableTokens.size(); j++) {
					ss << VariableTokens.at(j)->ReturnString() << "=" << R.List.at(i)->StringList.at(j)->ReturnString();
					if (j != VariableTokens.size() - 1) ss << ", ";
				}
			}
		}
	}
	else ss << "No";
	std::cout << ss.str();
}

bool database::InterpretQuery(int n) {
	for (int i = QueryList->size() - 1; i >= 0; i--) delete QueryList->at(i);
	delete QueryList;
	for (int i = FactList->size() - 1; i >= 0; i--) delete FactList->at(i);
	delete FactList;
	QueryList = new std::vector<Query*>;
	*QueryList = D.GetQueryList();
	FactList = new std::vector<Fact*>;
	*FactList = D.GetFactList();
	R.SetFacts(*FactList);
	std::string LeadID = QueryList->at(n)->GetPredicateList()->at(0)->LeadID.ReturnString();
	
	R.Select(LeadID, 1, "=", 1);

	int size = QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->size();
	std::vector<int> ProjectNumbers;
	std::vector<int> SelectNumbers;
	std::vector<Token*> VariableTokens;

	for (int i = 0; i < size; i++) {
		if (QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->at(i)->GetData()->ReturnType() == STRING) {
			R.Select(LeadID, i + 1, "=", QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->at(i)->GetData()->ReturnString());
		}
	}
	size = QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->size();
	for (int i = 0; i < size; i++) {
		int Previous = TokenPresent(QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->at(i)->GetData(), VariableTokens);
		if (Previous != -1) {
			ProjectNumbers.push_back(i + 1);
			SelectNumbers.push_back(ProjectNumbers.at(Previous));
			SelectNumbers.push_back(i + 1);
			//VariableTokens.push_back(QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->at(i)->GetData());
		}
		else if (QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->at(i)->GetData()->ReturnType() == ID) {
			ProjectNumbers.push_back(i + 1);
			VariableTokens.push_back(QueryList->at(n)->GetPredicateList()->at(0)->GetParamList()->at(i)->GetData());
		}
	}
	for (int i = 0; i < SelectNumbers.size(); i += 2) {
		R.Select(LeadID, SelectNumbers.at(i), "=", SelectNumbers.at(i + 1));
	}

	R.Project(ProjectNumbers);

	PrintQueryResults(n, VariableTokens);
	if (n != QueryList->size() - 1) std::cout << "\n";

	return 1;
}