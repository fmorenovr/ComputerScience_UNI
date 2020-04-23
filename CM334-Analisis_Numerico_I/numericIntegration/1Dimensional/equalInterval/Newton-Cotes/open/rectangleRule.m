#!/usr/bin/octave -qf

%  5. Metodo de Rectangulo

%   Aproxima la integral mediante sumatoria de (b-a)*f(a+i*h)

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
