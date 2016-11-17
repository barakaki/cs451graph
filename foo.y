%union {
	int i;
	int s;
}


%token <s>FOR
%token <s>ID
%token <i> INTEGER
%token <s> STRING
%type <s> sexpr
%token IF
%type <s>expression
%token <s> SYM
%type <s>symbol
%token <s> SWITCH
%token <s> BREAK
%token <s> CASE
%token <s> DEFAULT
%token ELSE
%token <s> ANYTHING


%left '+'


%{
	#include "fubar.h"

%}


%%


program: program fndef | {cerr << "program ready" << endl;}
    	;
fndef: type ID '(' params ')' block { cerr << "function defined" << endl;}
    	;
type:   ID
    	;
params: ;


block: '{' statements '}'    	 
    	;
statements:
    	statements statement   	 
    	|
    	;
statement:
    	block
		| IF '(' expression ')' '{' statements '}' ELSE '{' statements '}'	{ cerr << "Found if statement" << endl;}
		| SWITCH '(' ID ')' '{' codehere '}'	{ cerr << "Switch statement found" << endl;}
		| FOR '(' forcodes ';' forcodes ';' forcodes ')' '{' statements '}' 	{ cerr << "For statement found" << endl;}
		| ID 
		| expression ';'
		| sexpr ';'
		| forcode
		| ';'
    	;
sexpr:
		STRING					{ $$ = $1;}
		;
expression:
		ID symbol INTEGER
		| ID symbol ID
		;
symbol:
		SYM 		{$$ = $1;}	
		;
codehere:
		codehere anothercode 
		|
		;
anothercode:
		CASE sexpr ':' statements BREAK';'
		| DEFAULT ':' 
		| CASE sexpr ':' statements
		;
forcodes:
		forcodes forcode
		|
		;
forcode:
		ID
		|symbol
		| '+'
		| '-'
		| "++"
		| INTEGER
		|';'
		;

%%


void yyerror(const char *s) {
	cerr << s << endl;
}


int main(void) {
	yyparse();
	cout << "digraph{\n node[shape = rectangle]\n " << endl;
	justinoutput();
	/**

	start(5);
	output(5);
	finish();*/
	return 0;
}
