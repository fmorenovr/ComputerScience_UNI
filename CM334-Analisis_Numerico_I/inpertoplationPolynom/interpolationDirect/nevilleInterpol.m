#!/usr/bin/octave -qf

% 1. METODO DE MATRIZ DE NEVILLE

%  Interpola mediante diferencias dividias y devuelve el polinomio de interpolacion de X, Y envaluado en p(x0)
%  x = 10:2:14
%  y = [12 18 21]
% --------------------------------------------------
function [px0,Q]=nevilleInterpol(x,y,x0)
  n = length(y)-1;
  Q = zeros(n+1,n+1);
  Q(1:n+1,1) = y(:);
  for i = 2:n+1
   for j = 2:i
      Q(i,j) = (x0-x(i-j+1))*Q(i,j-1) - (x0-x(i))*Q(i-1,j-1);
      Q(i,j) = Q(i,j)/(x(i)-x(i-j+1));
    endfor
  endfor
  px0 = Q(n+1,n+1);
endfunction

% --------------------------------------------------
