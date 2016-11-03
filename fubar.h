	#include <string>
	#include <iostream>
	#include <iomanip>
	#include <sstream>

	using namespace std;

	int store(string s);
	string lookup(int n);
	void start(int input);
	void output(int input);
	void finish();
	void ifstatement(int placement);
	void elsestatement(int placement);
	void forstatement (int placement);
	void outputblock(int placement);
	int yylex(void);
	void yyerror(const char *);


