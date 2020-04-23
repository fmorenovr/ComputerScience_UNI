inter=-1:1;
h = 0.02;
x = -1:h:1;

y = cosh(inter);

[Npoli,DDi]=newtonInterpol(inter,y);

disp("El polinomio interpolante de Newton es: ");
disp(Npoli);
yi = polyval(Npoli,inter);
%plot(inter,yi,'p-','Linewidth',2)
hold on
%plot(inter,y,'g-','Linewidth',2)
hold on

fx = polyval(Npoli,x);
yx = cosh(x);

disp("");
disp("PARTE b) \n");
disp("Representado en las graficas");
%plot(x,yx,'b-','Linewidth',2)
hold on
%plot(x,fx,'r-','Linewidth',2)
hold on
error1 = max(abs(yx-fx));
fprintf("El error maximo del polinomio es: %.4f\n",error1);

disp("");
disp("PARTE c) \n");
disp("La desviacion cuadratica media de los polinomios es: ");
S =0;
t = length(yx);
for i = 1:t
  S = S + (yx(i)-fx(i))*(yx(i)-fx(i));
endfor
S=S/t;
S = sqrt(S);
disp(S);
grid on

hold off

disp("");
disp("PARTE d) \n");
disp("Polinomio de grado 4");
inter = -1:1/3.:1;
y = cosh(inter);
[Npoli,DDi]=newtonInterpol(inter,y);

disp("El polinomio interpolante de Newton es: ");
disp(Npoli);
yi = polyval(Npoli,inter);
plot(inter,yi,'p-','Linewidth',2)
hold on
plot(inter,y,'g-','Linewidth',2)
hold on

disp("Representado en las graficas");
plot(x,yx,'b-','Linewidth',2)
hold on
plot(x,fx,'r-','Linewidth',2)
hold on
grid on
error1 = max(abs(yx-fx));
fprintf("El error maximo del polinomio es: %.4f\n",error1);
disp("La desviacion cuadratica media de los polinomios es: ");
S =0;
t = length(yx);
for i = 1:t
  S = S + (yx(i)-fx(i))*(yx(i)-fx(i));
endfor
S=S/t;
S = sqrt(S);
disp(S);
