#pragma once
#include "Fact.h"
#include <sstream>
#include <algorithm>

class relation {
public:
	relation();
	~relation();

	void SetFacts(std::vector<Fact*> List);

	bool Select(std::string LeadID, int Attribute, std::string Operator, std::string Condition);
	bool Select(std::string LeadID, int Attribute, std::string Operator, int Condition);
	bool Project(int Attribute);
	bool Project(std::vector<int> Attributes);
	bool Rename(std::string OldString, std::string NewString);

	std::string ToString() const;

	void Sort();
	void RemoveDuplicates();

	std::vector<Fact*> List;

private:
};