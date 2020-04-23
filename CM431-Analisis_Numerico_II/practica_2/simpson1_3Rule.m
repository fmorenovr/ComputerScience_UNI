#!/usr/bin/octave -qf

%  2. Metodo de Simpson 1/3

%   Aproxima la integral mediante un polinomio interpolante de lagrange de grado 2
%   Donde el numero de subintervalos debe ser multiplo de 2

% --------------------------------------------------
function [inte] = simpson1_3Rule(fx,a,b,n)
  f=fx;
  h = 1.0*(b-a)/n;
  inte = 0.0;
  for i = 0:2:n-1
    inte = inte + f(a+h*i) + 4*f(a+h*(i+1)) + f(a+h*(i+2));
  endfor
  inte = inte*h/3;
end
