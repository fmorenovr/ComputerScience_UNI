#!/usr/bin/octave -qf

%  4. Metodo de Boole

%   Aproxima la integral mediante un polinomio interpolante de lagrange de grado 4

% --------------------------------------------------
function [inte] = booleRule(fx,a,b,n)
  f=fx;
  h = 1.0*(b-a)/n;
  inte = 0.0;
  for i = 0:4:n-1
    inte = inte + 7*f(a+h*i) + 32*f(a+h*(i+1)) + 12*f(a+h*(i+2)) + 32*f(a+h*(i+3)) + 7*f(a+h*(i+4));
  endfor
  inte = inte*2.0*h/45;
end
