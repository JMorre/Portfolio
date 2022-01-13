#pragma once
#include "Token.h"
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <iostream>
#include <sstream>

class LexicalAnalyzer {
public:
	LexicalAnalyzer();
	~LexicalAnalyzer();
	//commands to execute the lexical analyzer's file read/write and token operations
	bool Open(std::string File);
	void Read();
	void Write();
	void Clear();

	std::vector<Token*> ReturnList() const;



private:
	char State; //contains the current state, only 30 required, so a char is sufficient
	int CurrentLine; //current line vs. true line exists to store information for what line a...
	int TrueLine;    //multi-line string or comment should display (starting line, rather than the finishing line)
	int Total;
	char Current; //latest character read
	std::string CurrentS; //string of current characters since last token
	std::vector<Token*> TokenList;
	std::ifstream Input;
	//the following chooses what state function to call based on current state
	void TestState();
	//the following functions represent states of the finite state machine, 30 states total
	void Eval0();
	void Eval1();
	void Eval2();
	void Eval3();
	void Eval4();
	void Eval5();
	void Eval6();
	void Eval7();
	void Eval8();
	void Eval9();
	void Eval10();
	void Eval11();
	void Eval12();
	void Eval13();
	void Eval14();
	void Eval15();
	void Eval16();
	void Eval17();
	void Eval18();
	void Eval19();
	void Eval20();
	void Eval21();
	void Eval22();
	void Eval23();
	void Eval23_5();
	void Eval24();
	void Eval25();
	void Eval25_5();
	void Eval26();
	void Eval27();
	void EvalEnd();
	//the following creates an appropriate token
	void AddToken(Tokens Type, std::string);
};