#!/usr/bin/octave -qf

clear;clc;
p = [1 2 3 4];
q = [1 0 0 0 -1 -3 0];

disp("P(x) = x^3 + x^2 + 3x + 4");
disp("Q(x) = x^6 - x^2- 3x");
disp("La Derivada de P: ");
dp = polyder(p);
disp(dp);
disp("La Integral de P: ");
ip = polyint(p,8);
disp(ip);

disp("La Derivada de Q: ");
dq = polyder(q);
disp(dq);
disp("La Integral de Q: ");
iq = polyint(q,8);
disp(iq);
