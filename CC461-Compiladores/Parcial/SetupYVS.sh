#!/bin/bash
bison -v YoVerSil.y -o YoVerSil.c
cpp YoVerSil.c > YoVerSil.i
gcc -Wall -S YoVerSil.i
rm YoVerSil.i
gcc YoVerSil.c -o yvshell -lm
