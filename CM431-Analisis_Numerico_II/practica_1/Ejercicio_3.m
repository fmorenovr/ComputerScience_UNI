#!/usr/bin/octave -qf

clear;clc;
p = [1 0 0 0 -1];
q = [1 0 0 -1];

disp("P(x)=x^4 - 1");
disp("Q(x)=x^3 - 1");
disp("Cociente del producto de P y Q");
prod = conv(p,q);
disp("El polinomio Producto es: "); disp(prod);

disp("");
disp("Cociente de la division de P y Q");
[div,res] = deconv(p,q);
disp("El polinomio Cociente es: "); disp(div);
disp("El polinomio Residual es: "); disp(res);

