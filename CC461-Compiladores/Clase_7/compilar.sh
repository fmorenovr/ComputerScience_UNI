#!/bin/bash
bison -d sintactico.y
flex lexico.l
cc lex.yy.c sintactico.tab.c -o analizador -lfl -lm

