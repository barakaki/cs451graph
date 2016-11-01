bison -d foo.y && echo BISON OK && flex bar.l && echo FLEX OK && g++-6 foo.tab.c lex.yy.c -ll -ly fubar.c && echo COMPILE OK && ./a.out
