bison -d foo.y && echo BISON OK && flex bar.l && echo FLEX OK && g++-6 foo.tab.c lex.yy.c -ll -ly fubar.c && echo COMPILE OK && rm a.dot && ./a.out < testingfile | tee a.dot &&  xdot a.dot

