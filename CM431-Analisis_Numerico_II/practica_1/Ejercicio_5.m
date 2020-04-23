#!/usr/bin/octave -qf

clear;clc;
x = [0 1 2 3];
y = [0 2 -1 0];

p = polyfit(x,y,3);
disp("El polinomio interpolador es: ");
disp(p);
plot(x,y,'g-','Linewidth',2);

plot(x,y)
hold on

disp("Los puntos son: ");
i = 0:16;
x = 3*i/16.;
disp(x);
disp("Los puntos de la funcion son: ");
z = polyval(p,x);
disp(z);

plot(x,z,'r-','Linewidth',2);
hold on
grid on
