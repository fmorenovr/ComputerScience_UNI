#!/usr/bin/octave -qf

clc;
k = -3:3;
n = length(k);
alpha = 1/2.;
x = k*alpha;
y = tan(x);
a = -1.5;
b=1.5;
h = (b-a)/150;
xx = a:h:b;

[Npoli,DDi] = newtonInterpol(x,y);

disp("");
disp("PARTE a) \n");
disp("El polinomio interpolante de Newton es: ");
disp(Npoli);
disp("Matriz de diferencias divididas es: ");
disp(DDi);

fx = polyval(Npoli,xx);
yx = tan(xx);

disp("");
disp("PARTE b) \n");
disp("Representado en las graficas");
plot(xx,yx,'b-','Linewidth',2)
hold on
%plot(xx,fx,'r-','Linewidth',2)
hold on

disp("");
disp("PARTE c) \n");

disp("");
disp("PARTE d) \n");

x2 = 3/1998.*sin(k*pi/6.);
y2 = tan(x2);
%yy = polyfit(x2,y2,n-1);
[yy,DDi1] = newtonInterpol(x2,y2);
disp("Polinomio Interpolante con x = 3*alpha*sin(k*pi/6.) es: ");
disp(yy);
disp(DDi1);
yy1 = polyval(yy,xx);
plot(xx,yy1,'g-','Linewidth',2)
hold on
grid on

error1 = max(abs(yx-fx));
fprintf("El error maximo del polinomio con x = alpha.k es: %.4f\n",error1);
error2 = max(abs(yx-yy1));
fprintf("El error maximo del polinomio con x = 3*alpha*sin(k*pi/6.) es: %.4f\n",error2);
