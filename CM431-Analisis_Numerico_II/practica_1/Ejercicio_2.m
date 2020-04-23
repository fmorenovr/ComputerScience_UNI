#!/usr/bin/octave -qf

clear;clc;
p = [1 -6 11 -6];
q = [1 7 21 35 35 21 7 1];

disp("Los ceros del polinomio x^3 - 6x^2 + 11x - 6:");
z = roots(p);
disp(z);

disp("Los ceros del polinomio (x+1)^7:");
w = roots(q);
disp(w);
