#!/usr/bin/bash

bison $1 -o $1.c
gcc $1.c -o $1.output -lm
rm $1.c
