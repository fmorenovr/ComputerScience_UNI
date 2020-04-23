#!/usr/bin/octave -qf

%  3. Metodo de Simpson 3/8

%   Aproxima la integral mediante un polinomio interpolante de lagrange de grado 3
%   donde el numero de subintervalos debe ser multiplo de 3

% --------------------------------------------------
function [inte] = simpson3_8Rule(fx,a,b,n)
  f=fx;
  h = 1.0*(b-a)/n;
  inte = 0.0;
  for i = 0:3:n-3
    inte = inte + f(a+h*i)+3*f(a+h*(i+1))+3*f(a+h*(i+2))+f(a+h*(i+3));
  endfor
  inte = inte*3.0*h/8;
end
