#include "DatalogParser.h"

DatalogParser::DatalogParser(std::vector<Token*> V) {
	TokenList = V;
	i = 0;
	Current = TokenList[i];
}

DatalogParser::~DatalogParser() {
	/*int Total = TokenList.size();
	for (int i = Total - 1; i >= 0; i--) {
	delete TokenList[i];
	TokenList.pop_back();
	}*/
}

bool DatalogParser::Parse() {
	i = 0;
	Current = TokenList[i];
	if (Current->ReturnType() == Q_MARK) {
		int Flag = 1;
	}
	if (Current->ReturnType() == COMMENT || Current->ReturnType() == WHITESPACE) this->AdvanceToken();
	if (dP()) {
		DatalogProgram.CreateDomain();
		return true;
	}
	else {
		this->SetOffender();
		return false;
	}
}

std::string DatalogParser::PrintOffender() const {
	return Offender;
}

std::string DatalogParser::ProgramToString() const {
	return DatalogProgram.PrintLists();
}



void DatalogParser::SetOffender() {
	std::stringstream ss;
	ss << "(" << TokenList[i]->ReturnTypeString() << ",\"" << TokenList[i]->ReturnString() << "\"," << TokenList[i]->ReturnLine() << ")";
	Offender = ss.str();
}

void DatalogParser::AdvanceToken() {
	do {
		i++;
		if (Current->ReturnLine() == 13) {
			int FLAG = 1;
		}
		Current = TokenList[i];
	} while (Current->ReturnType() == COMMENT || Current->ReturnType() == WHITESPACE);
}

bool DatalogParser::dP() {
	if (Current->ReturnType() == SCHEMES) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == COLON) this->AdvanceToken();
	else return false;

	if (!sch()) return false;

	if (!schL()) return false;

	if (Current->ReturnType() == FACTS) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == COLON) this->AdvanceToken();
	else return false;

	if (!fL()) return false;

	if (Current->ReturnType() == RULES) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == COLON) this->AdvanceToken();
	else return false;

	if (!rL()) return false;

	if (Current->ReturnType() == QUERIES) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == COLON) this->AdvanceToken();
	else return false;

	if (!q()) return false;

	if (!qL()) return false;

	return true;
}

bool DatalogParser::sch() {
	Scheme* New = new Scheme();

	if (Current->ReturnType() == ID) {
		New->SetLeadID(Current);
		this->AdvanceToken();
	}
	else return false;

	if (Current->ReturnType() == LEFT_PAREN) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == ID) {
		New->AddNewID(Current);
		this->AdvanceToken();
	}
	else return false;

	if (!idL(New)) return false;

	if (Current->ReturnType() == RIGHT_PAREN) {
		this->AdvanceToken();
		DatalogProgram.AddScheme(New);
	}
	else return false;

	return true;
}

bool DatalogParser::schL() {
	if (Current->ReturnType() == FACTS) return true;

	else if (Current->ReturnType() == ID);
	else return false;

	if (!sch()) return false;

	if (!schL()) return false;

	return true;
}

bool DatalogParser::idL(ListType *List) { //scheme, headpredicate
	if (Current->ReturnType() == RIGHT_PAREN) return true;

	else if (Current->ReturnType() == COMMA) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == ID) {
		List->AddNewID(Current);
		this->AdvanceToken();
	}
	else return false;

	if (!idL(List)) return false;

	return true;
}

bool DatalogParser::f() {
	Fact* New = new Fact();

	if (Current->ReturnType() == ID) {
		New->SetLeadID(Current);
		this->AdvanceToken();
	}
	else return false;

	if (Current->ReturnType() == LEFT_PAREN) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == STRING) {
		New->AddNewString(Current);
		this->AdvanceToken();
	}
	else return false;

	if (!sL(New)) return false;

	if (Current->ReturnType() == RIGHT_PAREN) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == PERIOD) {
		DatalogProgram.AddFact(New);
		this->AdvanceToken();
	}
	else return false;

	return true;
}

bool DatalogParser::fL() {
	if (Current->ReturnType() == RULES) return true;

	else if (Current->ReturnType() == ID);
	else return false;

	if (!f()) return false;

	if (!fL()) return false;

	return true;
}

bool DatalogParser::r() {
	Rule* New = new Rule();

	if (Current->ReturnType() == ID);
	else return false;

	if (!hP(New)) return false;

	if (Current->ReturnType() == COLON_DASH) this->AdvanceToken();
	else return false;

	if (!p(New)) return false;

	if (!pL(New)) return false;

	if (Current->ReturnType() == PERIOD) {
		DatalogProgram.AddRule(New);
		this->AdvanceToken();
	}
	else return false;

	return true;
}

bool DatalogParser::rL() {
	if (Current->ReturnType() == QUERIES) return true;

	else if (Current->ReturnType() == ID);
	else return false;

	if (!r()) return false;

	if (!rL()) return false;

	return true;
}

bool DatalogParser::hP(Rule *List) {
	if (Current->ReturnType() == ID) {
		List->GetHeadPredicate()->SetLeadID(Current);
		this->AdvanceToken();
	}
	else return false;

	if (Current->ReturnType() == LEFT_PAREN) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == ID) {
		List->GetHeadPredicate()->AddNewID(Current);
		this->AdvanceToken();
	}
	else return false;

	if (!idL(List->GetHeadPredicate())) return false;

	if (Current->ReturnType() == RIGHT_PAREN) this->AdvanceToken();
	else return false;

	return true;
}

bool DatalogParser::p(ListType *List) { //rule, query
	Predicate* New = new Predicate();

	if (Current->ReturnType() == ID) {
		New->SetLeadID(Current);
		this->AdvanceToken();
	}
	else return false;

	if (Current->ReturnType() == LEFT_PAREN) this->AdvanceToken();
	else return false;

	if (!pa(PF, true, New)) return false;

	if (!paL(New)) return false;

	if (Current->ReturnType() == RIGHT_PAREN) this->AdvanceToken();
	else return false;

	List->GetPredicateList()->push_back(New);

	return true;
}

bool DatalogParser::pL(Rule *List) {
	if (Current->ReturnType() == PERIOD) return true;

	else if (Current->ReturnType() == COMMA) this->AdvanceToken();
	else return false;

	if (!p(List)) return false;

	if (!pL(List)) return false;

	return true;
}

bool DatalogParser::pa(bool *E, bool First, Predicate *List, Expression *ENew, DataParam *DNew) {
	bool Temp = *E;

	if (Current->ReturnType() == LEFT_PAREN) {
		if (!Temp) ENew = new Expression();
		Temp = true;
		if (!e(ENew)) return false;
	}

	else if (Current->ReturnType() == STRING) {
		if (!Temp) DNew = new DataParam();
		Temp = false;
		DNew->SetData(Current);
		this->AdvanceToken();
	}

	else if (Current->ReturnType() == ID) {
		if (!Temp) DNew = new DataParam();
		Temp = false;
		DNew->SetData(Current);
		this->AdvanceToken();
	}

	else return false;

	if (*E) *E = Temp;

	if (First && DNew == NULL) List->GetParamList()->push_back(ENew);
	if (First && ENew == NULL) List->GetParamList()->push_back(DNew);

	return true;
}

bool DatalogParser::paL(Predicate *New) {
	if (Current->ReturnType() == RIGHT_PAREN) return true;

	else if (Current->ReturnType() == COMMA) this->AdvanceToken();
	else return false;

	if (!pa(PF, true, New)) return false;

	if (!paL(New)) return false;

	return true;
}

bool DatalogParser::e(Parameter *Param) {
	Expression* EFirstParam = new Expression();
	Expression* ESecondParam = new Expression();
	DataParam* DFirstParam = new DataParam();
	DataParam* DSecondParam = new DataParam();
	bool* FE = new bool(true);
	bool* SE = new bool(true);

	if (Current->ReturnType() == LEFT_PAREN) this->AdvanceToken();
	else return false;

	if (!pa(FE, false, NULL, EFirstParam, DFirstParam)) return false;

	if (!o(Param)) return false;

	if (!pa(SE, false, NULL, ESecondParam, DSecondParam)) return false;

	if (Current->ReturnType() == RIGHT_PAREN) {
		if (*FE) {
			delete DFirstParam;
			Param->SetFirstParam(EFirstParam);
		}
		else {
			delete EFirstParam;
			Param->SetFirstParam(DFirstParam);
		}
		if (*SE) {
			delete DSecondParam;
			Param->SetSecondParam(ESecondParam);
		}
		else {
			delete ESecondParam;
			Param->SetSecondParam(DSecondParam);
		}
		this->AdvanceToken();
	}
	else return false;

	delete FE;
	delete SE;

	return true;
}

bool DatalogParser::o(Parameter *New) {
	if (Current->ReturnType() == ADD) {
		New->SetOperator(Current);
		this->AdvanceToken();
	}

	else if (Current->ReturnType() == MULTIPLY) {
		New->SetOperator(Current);
		this->AdvanceToken();
	}

	else return false;

	return true;
}

bool DatalogParser::q() {
	Query* New = new Query();

	if (Current->ReturnType() == ID);
	else return false;

	if (!p(New)) return false;

	if (Current->ReturnType() == Q_MARK) {
		this->AdvanceToken();
		DatalogProgram.AddQuery(New);
	}
	else return false;

	return true;
}

bool DatalogParser::qL() {
	if (Current->ReturnType() == EndOfFile) return true;

	else if (Current->ReturnType() == ID);
	else return false;

	if (!q()) return false;

	if (!qL()) return false;

	return true;
}

bool DatalogParser::sL(Fact *List) {
	if (Current->ReturnType() == RIGHT_PAREN) return true;

	else if (Current->ReturnType() == COMMA) this->AdvanceToken();
	else return false;

	if (Current->ReturnType() == STRING) {
		List->AddNewString(Current);
		this->AdvanceToken();
	}
	else return false;

	if (!sL(List)) return false;

	return true;
}

datalogProgram DatalogParser::GetProgram() {
	return DatalogProgram;
}