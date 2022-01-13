#include "relation.h"
#include <sstream>
#include <iostream>
#include "DatalogParser.h"
#include "database.h"



int main(int argc, char *argv[]) {
	std::vector<Token*> V;
	LexicalAnalyzer A;

	if (A.Open(argv[1])) {
		A.Read();
		V = A.ReturnList();
		DatalogParser P = DatalogParser(V);
		if (!P.Parse()) std::cout << "Failure!\n  " << P.PrintOffender();
		else {
			database D = database(P.GetProgram());
			D.RunQueries();
		}
	}
	A.Clear();

	return 0;
}