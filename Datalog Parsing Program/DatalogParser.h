#pragma once
#include "LexicalAnalyzer.h"
#include "Token.h"
#include "datalogProgram.h"

class DatalogParser {
public:
	DatalogParser(std::vector<Token*> V);
	~DatalogParser();
	bool Parse();
	std::string PrintOffender() const;
	std::string ProgramToString() const;
	datalogProgram GetProgram();

private:
	int i;
	Token* Current;
	std::vector<Token*> TokenList;
	std::string Offender;
	bool F = false;
	bool *PF = &F;

	void SetOffender();
	void AdvanceToken();

	datalogProgram DatalogProgram;

	bool dP();
	bool sch();
	bool schL();
	bool idL(ListType *List);
	bool f();
	bool fL();
	bool r();
	bool rL();
	bool hP(Rule *List);
	bool p(ListType *List);
	bool pL(Rule *List);
	bool pa(bool *E, bool First = false, Predicate *List = NULL, Expression *ENew = NULL, DataParam *DNew = NULL);
	bool paL(Predicate *New);
	bool e(Parameter *Param);
	bool o(Parameter *New);
	bool q();
	bool qL();
	bool sL(Fact *List);
};