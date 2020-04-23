#!/usr/bin/octave -qf

%  1. Metodo del Trapecio

%   Aproxima la integral mediante trapecios

% --------------------------------------------------
function [inte] = trapezoidalRule(fx,a,b,n)
  f=fx;
  h = 1.0*(b-a)/n;
  inte = 0.0;
  for i = 0:n-1
    inte = inte + (f(a+h*i) + f(a+h*(i+1)))*h/2;
  endfor
end
