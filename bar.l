%{
	#include "foo.tab.h"
	#include "fubar.h"
%}


%%


[0-9]+  	{
            	stringstream(yytext) >> yylval.i;
				string s = yytext;	
				yylval.s = store(s);  
            	return INTEGER;
        	}
for			{
				string s = yytext;	
				yylval.s = store(s);
				return FOR;
			}
if			{
				string s = yytext;	
				yylval.s = store(s);
				return IF;
			}
else		{
				string s = yytext;	
				yylval.s = store(s);
				return ELSE;	
			}
switch 		{
				string s = yytext;	
				yylval.s = store(s);
				return SWITCH;
			}
case		{
				string s = yytext;	
				yylval.s = store(s);
				return CASE;
			}
break		{
				string s = yytext;	
				yylval.s = store(s);
				return BREAK;
			}
default		{
				string s = yytext;	
				yylval.s = store(s);
				return DEFAULT;
			}
'[^']+'			{
				string s = yytext;	
				yylval.s = store(s);
				return STRING;		
			}

[<>!=]+		{
				string s = yytext;	
				yylval.s = store(s);
				return SYM;
			}	
[A-Za-z]+   {   
				string s = yytext;	
				yylval.s = store(s);
            	return ID;
				
        	}

[-+;(){}:]  {	
				string s = yytext;	
				yylval.s = store(s);		
				return *yytext;
			}


[ \t\n]   	; /* skip whitespace */


.       	yyerror("invalid character");
%%


int yywrap(void) {
	return 1;
}

