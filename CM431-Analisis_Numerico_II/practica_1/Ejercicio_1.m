#!/usr/bin/octave -qf

clear;clc;
p = [1 -3 2 1];

disp('El polinomio x^4 - 3x^3 + 2x + 1 evaluado en: ');
i = 0:8;
x = -1 + i/4;
disp(x);
disp("El resultado es: ");
y = polyval(p,x);
disp(y);

plot(x,y,'r-','Linewidth',2)
hold on
grid on
