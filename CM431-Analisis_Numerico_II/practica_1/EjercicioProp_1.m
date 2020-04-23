clc;
disp("Escalamos los datos (en 10^6 )");

Base = [4410 4830 5250 5670]/1000.;
Cuota = [1165.978 1329.190 1501.474 1682.830]/1000;

n = length(Base) - 1;

p=polyfit(Base,Cuota,n);
disp("El polinomio interpolador de grado 3 es: ");
disp(p);

pB = polyval(p,Base);

dpB = polyder(p);
ddpB = polyder(dpB);

plot(Base,pB,'r-','Linewidth',2)
grid on
ddpBNorm = norm(ddpB);
disp("Radio de Curvatura: ");
disp(1./ddpBNorm);
disp("No es una recta, es  una curva!\n");
num=input("Ingrese una cuota base (en millones): ");
%res = res/1000000.;
res = polyval(p,num);
fprintf("La couta es: %0.8f\n",res);
