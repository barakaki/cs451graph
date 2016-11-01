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


program: program fndef | {cout << "program ready" << endl;}
    	;
fndef: type ID '(' params ')' block { cout << "function defined" << endl;}
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
		| IF '(' expression ')' '{' statements '}' ELSE '{' statements '}'	{ cout << "Found if statement" << endl;}
		| SWITCH '(' sexpr ')' '{' codehere '}'	{ cout << "switch statement found" << endl;}
		| FOR '(' params ';' params ';' params ')' '{' statements '}' 	{ cout << "For statement found" << endl;}
		| ID 
		| expression ';'
		| sexpr ';'
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
		anothercode codehere
		|
		;
anothercode:
		CASE sexpr ':' statements BREAK';'
		| DEFAULT ':' 
		| CASE sexpr ':' 
		;

%%


void yyerror(const char *s) {
	cerr << s << endl;
}


int main(void) {
	yyparse();
	cout << "digraph{\n node[shape = rectangle]\n " << endl;
	start();
	output(5);
	finish();
	return 0;
}
