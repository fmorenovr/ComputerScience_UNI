% ------------------------------------------

% Metodos de Interpolacion Directa

% ------------------------------------------

%  interpolar es encontrar un polinomio que incluya a todos los puntos conocidos.
%  es la combinacion lineal de funciones base

% 1. Metodo de VanderMonde

%  Se construye la matriz de vandermonde (a a^2 ...a^n)
%  y un sistema de Ec lineales V(x).c = y
%  donde c = V(x)^-1.y son los coeficientes del polinomio interpolante


% 2. Metodo de Lagrange

%  Dados los nodos { x1, .. xn } los polinomios de Lagrange
%  l0, l1, l2, ... ln
%  li(xj) = 1, si i = j o 0 si i!=j
%  li(x) = (x - xi)/xj - xi)
%  Polinomio interpolante de Lagrange = y0l0 + y1l1 + ... + ynln


% 3. Metodo de Newton

%  Se encarga de ir sumando progresivamente cada polinomio


% 7. Metodo de Neville

%   Lagrande iterados
