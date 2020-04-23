clc;
disp('Evaluacion de integrales');disp('');
n = input('Ingrese numero de subintervalos: ');
a = input('Ingrese el limite inferior del intervalo: ');
b = input('Ingrese el limite superior del intervalo: ');
N = input('Ingrese el numero de iteraciones( para romberg ): ')

result = simpson1_3Rule(@fexp,a,b,n);

fprintf("\n\nLa integral por simpson 1/3 es: %0.18f\n\n",result);

result = simpson3_8Rule(@fexp,a,b,n);

fprintf("\n\nLa integral por simpson 3/8 es: %0.18f\n\n",result);

result = trapezoidalRule(@fexp,a,b,n);

fprintf("\n\nLa integral por Trapecio es: %0.18f\n\n",result);

result = rectangleRule(@fexp,a,b,n);

fprintf("\n\nLa integral por Rectangulo es: %0.18f\n\n",result);

result = milneRule(@fexp,a,b,n);

fprintf("\n\nLa integral por Milne es: %0.18f\n\n",result);

result = booleRule(@fexp,a,b,n);

fprintf("\n\nLa integral por Boole es: %0.18f\n\n",result);

[R]=rombergIntegra(@fexp,a,b,N);
disp('');
disp('La matriz de romberg es: ');
disp(R);

q = quad('fexp',a,b);

fprintf("\n\nLa integral Real es: %0.18f\n\n",q);
