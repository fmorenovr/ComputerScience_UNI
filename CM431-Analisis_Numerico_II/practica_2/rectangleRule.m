#!/usr/bin/octave -qf

%  2. Metodo de Rectangulo

%   Aproxima la integral mediante un polinomio interpolante de lagrange de grado 2

% --------------------------------------------------
function [inte] = rectangleRule(fx,a,b,n)
  f=fx;
  h = 1.0*(b-a)/n;
  inteSup = 0.0;
  inteInf = 0.0;
  for i = 0:n-1
    inteInf = inteInf + f(a+h*i)*h;
    inteSup = inteSup + f(a+h*(i+1))*h;
  endfor
  inte = (inteSup + inteInf)/2;
end
