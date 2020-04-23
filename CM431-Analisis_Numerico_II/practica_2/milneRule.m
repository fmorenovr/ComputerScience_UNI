#!/usr/bin/octave -qf

%  6. Metodo de Milne

% --------------------------------------------------
function [inte] = milneRule(fx,a,b,n)
  f=fx;
  h = 1.0*(b-a)/n;
  inte = 0.0;
  for i = 0:n-1
    inte = inte + 2*f(a+h*i+h/4) - f(a+h*i+h/2) + 2*f(a+h*i+3*h/4);
  endfor
  inte = inte*h/3.0;
end
