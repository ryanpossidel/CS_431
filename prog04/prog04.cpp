#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

enum Token{
	RBRACKET=1,
	LBRACKET,
	ID,
	EQUAL,
	SEMICOLON,
	IF,
	LPAREN,
	RPAREN,
	PLUS,
	MINUS,
	EOL
};

int nnext;
vector <int> tokens;
bool term(Token t){
//	return *nnext++ == t;
	return tokens[nnext++] == t;
}
bool PROG();
bool STMTS();
bool LOC();
bool EXP();
bool TAIL();

bool PROG1(){
	return term(LBRACKET) && STMTS() && term(RBRACKET);
}
bool STMTS1(){
	return LOC() && STMTS;
}
bool STMTS2(){
	return true;
}
bool LOC1(){
	return term(ID) && term(EQUAL) && EXP() && term(SEMICOLON);
}
bool LOC2(){
	return term(IF) && term(LPAREN) && EXP() && term(RPAREN) && PROG();
}
bool EXP1(){
	return term(ID) && TAIL();
}
bool TAIL1(){
	return term(PLUS) && EXP();
}
bool TAIL2(){
	return term(MINUS) && EXP();
}
bool TAIL3(){
	return true;
}
bool PROG(){
	int save = nnext;
	return(nnext = save, PROG1());
}
bool STMTS(){
	int save = nnext;
	return(nnext = save, STMTS1())||(nnext = save, STMTS2());
}
bool LOC(){
	int save = nnext;
	return(nnext = save, LOC1())||(nnext = save, LOC2());
}
bool EXP(){
	int save = nnext;
	return(nnext = save, EXP1());
}
bool TAIL(){
	int save = nnext;
	return(nnext = save, TAIL1())||(nnext = save, TAIL2())||(nnext = save, TAIL3());
}


int find_t(string t){
	int result = 0;
	if(t == "}"){
		result = RBRACKET;
	}
	else if(t == "{"){
		result = LBRACKET;
	}
	else if(t == "id"){
		result = ID;
	}
	else if(t == "="){
		result = EQUAL;
	}
	else if(t == ";"){
		result = SEMICOLON;
	}
	else if(t == "if"){
		result = IF;
	}
	else if(t == "("){
		result = LPAREN;
	}
	else if(t == ")"){
		result = RPAREN;
	}
	else if(t == "+"){
		result = PLUS;
	}
	else if(t == "-"){
		result = MINUS;
	}
	else if(t == "\n"){
		result = EOL;
	}
	return result;
}

int main(int argc, char *argv[]){
	ifstream f(argv[1]);
	string line;
	int i = 1;
	while(getline(f, line)){
		tokens.clear();
		stringstream ss(line);
		string toke;
		while(ss >> toke){
			tokens.push_back(find_t(toke));
		}
		tokens.push_back(EOL);
		nnext = 0;
		if(PROG() && term(EOL)){
			cout << i << " GOOD:" << line << endl;
		}else{
			cout << i << " FAIL:" << line << endl;
		}
		i++;
	}
	
	return EXIT_SUCCESS;
}
