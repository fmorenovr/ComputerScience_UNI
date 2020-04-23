#!/usr/bin/bash

bison -d Parser.y
mv Parser.tab.h Parser.h
mv Parser.tab.c Parser.y.c
flex Parser.lex
mv lex.yy.c Parser.lex.c
gcc -g -c Parser.lex.c -o Parser.lex.o
gcc -g -c Parser.y.c -o Parser.y.o
gcc -g -o Parser Parser.lex.o Parser.y.o -lfl
