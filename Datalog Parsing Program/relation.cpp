#include "relation.h"

relation::relation() {

}

relation::~relation() {

}

void relation::SetFacts(std::vector<Fact*> List) {
	this->List = List;
}

/*sigma_attribute _operator _condition; i.e. sigma_A=1*/
bool relation::Select(std::string LeadID, int Attribute, std::string Operator, std::string Condition) {
	for (int i = List.size() - 1; i >= 0; i--) {
		if (List.at(i)->GetLeadIDString() != LeadID) List.erase(List.begin() + i);
	}

	bool AnyValid = false;
	std::vector<bool> Valid;
	Attribute--;
	for (int i = 0; i < List.size(); i++) {
		if (List.at(i)->GetStringList().size() <= Attribute) Valid.push_back(false);
		else {
			Valid.push_back(true);
			AnyValid = true;
		}
	}
	if (!AnyValid) return false;

	int size = List.size();
	if (Operator == "=") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || List.at(i)->GetStringList().at(Attribute)->ReturnString() != Condition) {
				List.erase(List.begin() + i);
			}
		}
	}
	else if (Operator == "<") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || !(List.at(i)->GetStringList().at(Attribute)->ReturnString() < Condition)) {
				List.erase(List.begin() + i);
			}
		}
	}
	else if (Operator == ">") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || !(List.at(i)->GetStringList().at(Attribute)->ReturnString() > Condition)) {
				List.erase(List.begin() + i);
			}
		}
	}
	else if (Operator == "<=") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || !(List.at(i)->GetStringList().at(Attribute)->ReturnString() <= Condition)) {
				List.erase(List.begin() + i);
			}
		}
	}
	else if (Operator == ">=") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || !(List.at(i)->GetStringList().at(Attribute)->ReturnString() >= Condition)) {
				List.erase(List.begin() + i);
			}
		}
	}
	else return false;
	this->RemoveDuplicates();
	this->Sort();
	return true;
}

bool relation::Select(std::string LeadID, int Attribute, std::string Operator, int Condition) {
	for (int i = List.size() - 1; i >= 0; i--) {
		if (List.at(i)->GetLeadIDString() != LeadID) List.erase(List.begin() + i);
	}

	bool AnyValid = false;
	std::vector<bool> Valid;
	Attribute--;
	Condition--;
	for (int i = 0; i < List.size(); i++) {
		if (List.at(i)->GetStringList().size() <= Attribute || List.at(i)->GetStringList().size() <= Condition) Valid.push_back(false);
		else {
			Valid.push_back(true);
			AnyValid = true;
		}
	}
	if (!AnyValid) return false;

	int size = List.size();
	if (Operator == "=") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || List.at(i)->GetStringList().at(Attribute)->ReturnString() != List.at(i)->GetStringList().at(Condition)->ReturnString()) {
				List.erase(List.begin() + i);
			}
		}
	}
	else if (Operator == "<") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || !(List.at(i)->GetStringList().at(Attribute)->ReturnString() < List.at(i)->GetStringList().at(Condition)->ReturnString())) {
				List.erase(List.begin() + i);
			}
		}
	}
	else if (Operator == ">") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || !(List.at(i)->GetStringList().at(Attribute)->ReturnString() > List.at(i)->GetStringList().at(Condition)->ReturnString())) {
				List.erase(List.begin() + i);
			}
		}
	}
	else if (Operator == "<=") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || !(List.at(i)->GetStringList().at(Attribute)->ReturnString() <= List.at(i)->GetStringList().at(Condition)->ReturnString())) {
				List.erase(List.begin() + i);
			}
		}
	}
	else if (Operator == ">=") {
		for (int i = size - 1; i >= 0; i--) {
			if (!Valid.at(i) || !(List.at(i)->GetStringList().at(Attribute)->ReturnString() >= List.at(i)->GetStringList().at(Condition)->ReturnString())) {
				List.erase(List.begin() + i);
			}
		}
	}
	else return false;
	this->RemoveDuplicates();
	this->Sort();
	return true;
}

/*pi_Attribute; i.e. pi_A*/
bool relation::Project(int Attribute) {
	bool AllValid = false;
	std::vector<bool> Valid;
	Attribute--;
	for (int i = 0; i < List.size(); i++) {
		if (List.at(i)->GetStringList().size() <= Attribute) Valid.push_back(false);
		else {
			Valid.push_back(true);
			AllValid = true;
		}
	}
	if (!AllValid) return false;

	int Size = List.size();
	for (int i = Size - 1; i >= 0; i--) {
		if (!Valid.at(i)) {
			List.pop_back();
		}
		else {
			int Size2 = List.at(i)->GetStringList().size();
			for (int j = Size2 - 1; j >= 0; j--) {
				if (j != Attribute) List.at(i)->StringList.erase(List.at(i)->StringList.begin() + j);
			}
		}
	}

	this->RemoveDuplicates();
	this->Sort();
	return true;
}

/*pi_Attribute _Attribute...; i.e. pi_ABC...*/
bool relation::Project(std::vector<int> Attributes) {
	bool AllValid = false;
	std::vector<bool> Valid;
	for (int i = 0; i < Attributes.size(); i++) Attributes.at(i)--;
	for (int i = 0; i < List.size(); i++) {
		for (int j = 0; j < Attributes.size(); j++) {
			if (List.at(i)->GetStringList().size() <= Attributes.at(j)) {
				Valid.push_back(false);
				break;
			}
			else  {
				Valid.push_back(true);
				AllValid = true;
			}
		}
	}
	if (!AllValid) return false;

	int Size = List.size();
	for (int i = Size - 1; i >= 0; i--) {
		if (!Valid.at(i)) {
			List.pop_back();
		}
		else {
			int Size2 = List.at(i)->GetStringList().size();
			for (int j = Size2 - 1; j >= 0; j--) {
				bool Delete = true;
				for (int k = 0; k < Attributes.size(); k++) {
					if (j == Attributes.at(k)) {
						Delete = false;
					}
				}
				if (Delete) List.at(i)->StringList.erase(List.at(i)->StringList.begin() + j);
			}
		}
	}

	this->RemoveDuplicates();
	this->Sort();
	return true;
}

/*rho_OldString <- _NewString; i.e rho_'a'<-'b'*/
bool relation::Rename(std::string OldString, std::string NewString) {
	bool Success = false;
	for (int i = 0; i < List.size(); i++) {
		for (int j = 0; j < List.at(i)->GetStringList().size(); j++) {
			if (List.at(i)->GetStringList().at(j)->ReturnString() == OldString) {
				List.at(i)->GetStringList().at(j)->SetString(NewString);
				Success = true;
			}
		}
	}
	if (Success) {
		this->RemoveDuplicates();
		this->Sort();
		return Success;
	}
	else return false;
}

std::string relation::ToString() const {
	std::stringstream ss;
	ss << "Relation:\n";
	for (int i = 0; i < List.size(); i++) {
		ss << List.at(i)->GetLeadIDString() << "(";
		for (int j = 0; j < List.at(i)->GetStringList().size(); j++) {
			ss << List.at(i)->GetStringList().at(j)->ReturnString();
			if (j != List.at(i)->GetStringList().size() - 1) ss << ",";
			else ss << ")\n";
		}
	}
	return ss.str();
}

bool IsEqual(Fact* First, Fact* Second) {
	std::stringstream ss;
	std::stringstream ss2;
	std::string FirstString;
	std::string SecondString;
	for (int i = 0; i < First->GetStringList().size(); i++) {
		ss << First->GetStringList().at(i)->ReturnString();
	}
	FirstString = ss.str();
	for (int i = 0; i < Second->GetStringList().size(); i++) {
		ss2 << Second->GetStringList().at(i)->ReturnString();
	}
	SecondString = ss2.str();
	return FirstString == SecondString;
}

void relation::RemoveDuplicates() {
	int Size = List.size();
	for (int i = Size - 1; i >= 0; i--) {
		int Size2 = List.size();
		for (int j = Size2 - 1; j >= 0; j--) {
			if (i != j && IsEqual(List.at(i), List.at(j))) {
				List.erase(List.begin() + i);
				break;
			}
		}
	}

	int flag = 1;
	return;
}

bool IsSmaller(Fact* First, Fact* Second) {
	std::stringstream ss;
	std::stringstream ss2;
	std::string FirstString;
	std::string SecondString;
	for (int i = 0; i < First->GetStringList().size(); i++) {
		ss << First->GetStringList().at(i)->ReturnString();
	}
	FirstString = ss.str();
	for (int i = 0; i < Second->GetStringList().size(); i++) {
		ss2 << Second->GetStringList().at(i)->ReturnString();
	}
	SecondString = ss2.str();
	return FirstString < SecondString;
}

void relation::Sort() {
	std::sort(List.begin(), List.end(), IsSmaller);
}