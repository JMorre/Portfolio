#include "LexicalAnalyzer.h"
//constructor and destructor
LexicalAnalyzer::LexicalAnalyzer() { //initialize parameters to zero, first line to 1
	State = 0;
	CurrentLine = 1;
	TrueLine = 1;
	Total = 0;
}

LexicalAnalyzer::~LexicalAnalyzer() { //delete all dynamically allocated token pointers
	for (int i = Total - 1; i >= 0; i--) {
		delete TokenList[i];
		TokenList.pop_back();
	}
}

//the four basic executions of the analyzer
//open the file
bool LexicalAnalyzer::Open(std::string File) {
	Input.open(File);
	if (!Input) { //exit if the file name isn't found
		std::cout << "ERROR - File " << File << " not found.\n";
		return false;
	}
	return true;
}
//read and encode all characters in the input file
void LexicalAnalyzer::Read() {
	if (!Input) return;
	while (1) {
		Input.get(Current); //select the next character
		CurrentS.push_back(Current); //add it to the string
		if (Input.eof()) break;
		this->TestState(); //test which state and instructions it should execute
		if (Current == '\n') TrueLine++; //if the character was an end of line, increment the line counter
	}
	this->EvalEnd(); //at the end, a special state evaluates the end of the file
	return;
}
//write the output of tokens
void LexicalAnalyzer::Write() {
	std::stringstream ss;
	for (int i = 0; i < Total; i++) {
		ss << "(" << TokenList[i]->ReturnTypeString() << ",\"" << TokenList[i]->ReturnString()
			<< "\"," << TokenList[i]->ReturnLine() << ")" << "\n";
	}
	ss << "Total Tokens = " << Total << "\n";
	std::cout << ss.str();
	return;
}
//clear all values in the analyzer (this isn't important when running just one file, but while testing I used multiple files in the same program execution)
void LexicalAnalyzer::Clear() {
	for (int i = Total - 1; i >= 0; i--) { //clear the vector, deleting memory
		delete TokenList[i];
		TokenList.pop_back();
	}
	Input.close(); //reinitialize all other variables
	Input.clear();
	State = 0;
	CurrentLine = 1;
	TrueLine = 1;
	Total = 0;
}

//control function
//the following function checks what state the program is in, and points it to the corresponding execution function
void LexicalAnalyzer::TestState() {
	switch (State) {
	case 0:this->Eval0(); return;
	case 1:this->Eval1(); return;
	case 2:this->Eval2(); return;
	case 3:this->Eval3(); return;
	case 4:this->Eval4(); return;
	case 5:this->Eval5(); return;
	case 6:this->Eval6(); return;
	case 7:this->Eval7(); return;
	case 8:this->Eval8(); return;
	case 9:this->Eval9(); return;
	case 10:this->Eval10(); return;
	case 11:this->Eval11(); return;
	case 12:this->Eval12(); return;
	case 13:this->Eval13(); return;
	case 14:this->Eval14(); return;
	case 15:this->Eval15(); return;
	case 16:this->Eval16(); return;
	case 17:this->Eval17(); return;
	case 18:this->Eval18(); return;
	case 19:this->Eval19(); return;
	case 20:this->Eval20(); return;
	case 21:this->Eval21(); return;
	case 22:this->Eval22(); return;
	case 23:this->Eval23(); return;
	case -23:this->Eval23_5(); return; //I had to add a new function operating alongside 23, after I had already defined 24...
	case 24:this->Eval24(); return;    //so for the sake of clarity I defined a "23 and a half" state with the encoding -23
	case 25:this->Eval25(); return;
	case -25:this->Eval25_5(); return; //same as above
	case 26:this->Eval26(); return;
	case 27:this->Eval27(); return;
	}
}

//the following 30 functions evaluate commands for each state
//state 0 is the most complicated, since it's the default state and links to the most operations
void LexicalAnalyzer::Eval0() {
	switch (Current) {
	case '\'':State = 23; CurrentLine = TrueLine; return; //if the current character is ', evaluate as a string
	case '#':State = 25; CurrentLine = TrueLine; return; //if the current is #, evaluate as a comment
	case ',':this->AddToken(COMMA, ","); return; //if the character is one of the 7 single tokens, create a token
	case '.':this->AddToken(PERIOD, "."); return;
	case '?':this->AddToken(Q_MARK, "?"); return;
	case '(':this->AddToken(LEFT_PAREN, "("); return;
	case ')':this->AddToken(RIGHT_PAREN, ")"); return;
	case '*':this->AddToken(MULTIPLY, "*"); return;
	case '+':this->AddToken(ADD, "+"); return;
	case ':':State = 1; return; //if the character can begin one of the 5 multiple character tokens, switch states to evaluate the next input
	case 'S':State = 2; return;
	case 'F':State = 8; return;
	case 'R':State = 12; return;
	case 'Q':State = 16; return;
	}
	if (isalpha(Current)) { //if the above haven't been called, and the character is a letter, begin evaluating it as an ID
		State = 22;
		return;
	}
	if (isspace(Current)) { //if the above haven't been called, and the character is a whitespace character, ignore it and strike it from the string
		CurrentS.pop_back();
		return;
	}
	this->AddToken(UNDEFINED, CurrentS); //if any other character is recieved, it will be undefined
	return;
}
//state 1 evaluates the colon, checking for a following dash
void LexicalAnalyzer::Eval1() {
	if (Current == '-') { //if a dash follows immediately, create token
		this->AddToken(COLON_DASH, ":-");
		State = 0;
		return;
	}
	CurrentS.pop_back(); //otherwise, temporarily remove the non-dash character read...
	this->AddToken(COLON, ":"); //create a colon token...
	CurrentS.push_back(Current);//add the character back to the string...
	State = 0; //move back to the default state...
	this->TestState(); //reinterpret the character based on state 0
	return;
}
//state 2 begins the test for the SCHEMES token
void LexicalAnalyzer::Eval2() {
	if (Current == 'c') { //if the S that brought you to state 2 is followed by a c, proceed
		State = 3;
		return;
	}
	State = 22; //otherwise, start treating it as an ID instead
	this->TestState();
	return;
}
//state 3 continues the SCHEMES token
void LexicalAnalyzer::Eval3() {
	if (Current == 'h') { //if an h follows the c, proceed
		State = 4;
		return;
	}
	State = 22; //otherwise, start treating it as an ID instead
	this->TestState();
	return;
}
//state 4 continues
void LexicalAnalyzer::Eval4() {
	if (Current == 'e') {
		State = 5;
		return;
	}
	State = 22;
	this->TestState();
	return;
}
//state 5 continues
void LexicalAnalyzer::Eval5() {
	if (Current == 'm') {
		State = 6;
		return;
	}
	State = 22;
	this->TestState();
	return;
}
//state 6 continues
void LexicalAnalyzer::Eval6() {
	if (Current == 'e') {
		State = 7;
		return;
	}
	State = 22;
	this->TestState();
	return;
}
//state 7 determines whether to create a SCHEMES token, or to treat it as an ID
void LexicalAnalyzer::Eval7() {
	if (isalnum(Input.peek())) { //check the next character; if it's a letter or number, treat it as an ID
		State = 22;
		this->TestState();
		return;
	}
	if (Current == 's') { //otherwise, if the final character is correct...
		State = 0; //move back to state 0 in preparation for the next character...
		this->AddToken(SCHEMES, "Schemes"); //add a schemes token
		return;
	}
	State = 22; //if neither is the case, treat it as an ID (it won't last long as an ID, since the next character isn't alphanumeric)
	this->TestState();
	return;
}
//state 8 begins the test for the Facts token in the same manner; see the documentation of states 2-7 if more explanation is needed for states 8-11
void LexicalAnalyzer::Eval8() {
	if (Current == 'a') {
		State = 9;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval9() {
	if (Current == 'c') {
		State = 10;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval10() {
	if (Current == 't') {
		State = 11;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval11() {
	if (isalnum(Input.peek())) {
		State = 22;
		this->TestState();
		return;
	}
	if (Current == 's') {
		State = 0;
		this->AddToken(FACTS, "Facts");
		return;
	}
	State = 22;
	this->TestState();
	return;
}
//state 12 begins the test for the Rules token; see states 2-7 for further documentation for 12-15
void LexicalAnalyzer::Eval12() {
	if (Current == 'u') {
		State = 13;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval13() {
	if (Current == 'l') {
		State = 14;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval14() {
	if (Current == 'e') {
		State = 15;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval15() {
	if (isalnum(Input.peek())) {
		State = 22;
		this->TestState();
		return;
	}
	if (Current == 's') {
		State = 0;
		this->AddToken(RULES, "Rules");
		return;
	}
	State = 22;
	this->TestState();
	return;
}
//state 16 begins the test for the Queries token; see states 2-7 for further documentation for 16-21
void LexicalAnalyzer::Eval16() {
	if (Current == 'u') {
		State = 17;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval17() {
	if (Current == 'e') {
		State = 18;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval18() {
	if (Current == 'r') {
		State = 19;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval19() {
	if (Current == 'i') {
		State = 20;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval20() {
	if (Current == 'e') {
		State = 21;
		return;
	}
	State = 22;
	this->TestState();
	return;
}

void LexicalAnalyzer::Eval21() {
	if (isalnum(Input.peek())) {
		State = 22;
		this->TestState();
		return;
	}
	if (Current == 's') {
		State = 0;
		this->AddToken(QUERIES, "Queries");
		return;
	}
	State = 22;
	this->TestState();
	return;
}
//state 22 evaluates an ID
void LexicalAnalyzer::Eval22() {
	if (isalnum(Current)) return; //if the current character fits within an ID, go ahead to the next one...
	else { //otherwise...
		CurrentS.pop_back(); //remove the character from the string, temporarily...
		this->AddToken(ID, CurrentS); //add an ID token with the remaining string contents (only the ID characters)...
		CurrentS.push_back(Current); //add the removed character back to the string...
		State = 0; //re-evaluate the new character at state 0
		this->TestState();
		return;
	}
}
//states 23, 23.5, and 24 evaluate a string
void LexicalAnalyzer::Eval23() { //if the last character added to the string (previous character) is a ' or a space, evaluate...
	if (CurrentS.at(CurrentS.size() - 1) == '\'' && Current == ' ') {
		State = -23;  //special circumstances at state 23.5
		return;
	}
	if (isblank(Current)) return; //if the current character is blank, read the next character
	if (Current == '\'') { //if the current character is ', move to evaluate escape codes at state 24
		State = 24;
		return;
	}
	return;
}
//state 23.5 evaluates special string circumstances
void LexicalAnalyzer::Eval23_5() {
	if (Current == '\'') { //if the next character is a ', then the string ' ' has just been encountered.
		CurrentS.pop_back(); //in this case, purge the latest 3 characters from the string, as ' ' is the empty string
		CurrentS.pop_back();
		CurrentS.pop_back();
	}
	State = 23; //continue evaluating the string
	return;
}
//state 24 evaluates the escape code for apostrophes
void LexicalAnalyzer::Eval24() {
	if (Current == '\'') { //if the current (and by necessity, the previous) character are both apostrophes...
		State = 23; //continue with the string, they both belong in the token
		return;
	}
	CurrentS.pop_back(); //otherwise, the string ended last character. Remove the current character temporarily from the string
	this->AddToken(STRING, CurrentS); //create a string token with all remaining characters
	CurrentS.push_back(Current); //add the removed character back to the string
	State = 0; //return to state 0 to re-evaluate the latest character
	this->TestState();
	return;
}
//states 25, 25.5, 26, and 27 evaluate a comment
void LexicalAnalyzer::Eval25() {
	if (Current == '\n' || Current == '\r') { //if the next character is an endline, comment's over
		CurrentS.pop_back(); //remove the endline from the string
		this->AddToken(COMMENT, CurrentS); //add a comment token
		CurrentS.push_back(Current); //put the endline back on the string
		State = 0; //re-evaluate it at state 0
		this->TestState();
		return;
	}
	if (Current == '|') { //if the next character is |, begin a multi-line comment
		State = 26;
		return;
	}
	State = -25; //otherwise, continue evaluating the comment at state 25.5
	return;
}
//state 25.5 is for the case of a comment that was not a multi-line comment (didn't have a |)
void LexicalAnalyzer::Eval25_5() {
	if (Current == '\n' || Current == '\r') { //if endline is encountered, comment's over
		CurrentS.pop_back();
		this->AddToken(COMMENT, CurrentS);
		CurrentS.push_back(Current);
		State = 0;
		this->TestState();
		return;
	}
	return; //otherwise, continue reading until it is
}
//state 26 is for a multi-line comment
void LexicalAnalyzer::Eval26() {
	if (Current == '|') { //wait until the next | is encountered
		State = 27;
		return;
	}
	return;
}
//state 27 tests for the end of a multi-line comment
void LexicalAnalyzer::Eval27() {
	if (Current == '|') return; //if the penultimate symbol, |, is encountered again, stay in this test next character
	if (Current == '#') { //if the final symbol, #, is encountered, the comment ends here
		State = 0;
		this->AddToken(COMMENT, CurrentS); //add comment token with the contents of the string
		return;
	}
	State = 26; //otherwise, move back to state 26, awaiting the beginning of the end symbol
	return;
}
//the final state is called to test end of file conditions
void LexicalAnalyzer::EvalEnd() {
	if (Current != '\n' && Current != '\r') CurrentS.pop_back(); //if the last character read was an end of line, decrement the line counter to avoid counting errors
	int EndLine = TrueLine; //create a temporary endline variable, since strings and comments might be evaluated in a moment
	TrueLine = CurrentLine;
	if (State == -25) this->AddToken(COMMENT, CurrentS); //if the last character was an unfinished single line comment, add a comment token
	if (State == -23 || State == 24) this->AddToken(STRING, CurrentS); //if the last character was an unfinished string, add a string token
	if (State == 23 || State == 26 || State == 27) { //if the latest state was a string or comment...
		this->AddToken(UNDEFINED, CurrentS); //create an undefined token, since it ended at EOF, with the line number the string or comment began with
	}
	TrueLine = EndLine; //reset the end of line number to the true value
	this->AddToken(EndOfFile, ""); //add the end of file token
	return;
}

//the last function manages tokens
//add a token to the list
void LexicalAnalyzer::AddToken(Tokens Type, std::string String) {
	if (Type != STRING && Type != COMMENT) CurrentLine = TrueLine; //if the token is a string or comment, use the line it began on, rather than the line it ended on
	if (String.size() != 0) {
		if (String.at(String.size() - 1) == '\n') String.pop_back(); //if the string's last value exists and is an end line, remove it from the string
	}
	Token* T = new Token(Type, CurrentLine, String); //add a token to the list
	TokenList.push_back(T);
	CurrentS.clear(); //clear the string
	Total++; //increment the number of tokens
	return;
}

std::vector<Token*> LexicalAnalyzer::ReturnList() const {
	return TokenList;
}