#!/usr/bin/octave -qf

%  5. METODO DE HERMITE

%   Construye el polinomio, mediante:

%   POLINOMIOS DE HERMITE
%   H0(x)=1 y H1(x) = 2x
%   FORMA DE LOS COEFICIENTES
%   Hn+1(x) = 2x.Hn(x) - 2n.Hn-1(x)
%   H'n(x) = 2n.Hn-(x)
%   Hn+1(x) = 2x.Hn(x) - H'n(x)

%   Hn(x) = n!*Sum(m=0,m=[n/2]) [(-1)^m*(2x)^(n-2m)/(m!.(n-2m)!)]
%   x [-inf,inf]

%   probar: f = @(x) 1./(1+25*x.^2)

%   POLINOMIO DE INTERPOLACION DE HERMITE
%   una funcion es interpolada por hermite de grado 2n+1
%   H2n+1(x) = Sum(j=0,n) f(xj).Hn,j(x) + Sum(j=0,n) f'(xj).H'n,j(x)

%   donde:
%     Hn,j(x) = [1 - 2(x - xj)L'n,j(xj)].Ln,j(x)*Ln,j(x)
%     H'n,j(x) = [(x - xj)].Ln,j(x)*Ln,j(x)

%    donde: Ln,j(x) denota el j-esimo polinomio de Lagrange de grado n

% --------------------------------------------------
% polinomio hermite Hn(x)
function Hn = hermitePoly(N)
  % Hn+1(x) = 2xHn(x)-H'n(x) polinomio de hermite de grado n
  if N <= 0, Hn = 1;
  else Hn = [2 0];
    for n=2:N
      Hn=2*[Hn 0] - [0 0 polyder(Hn)];
    endfor
  endif
endfunction

% --------------------------------------------------
% polinomio de interoplacion de hermite
function [Hermpol,x] = hermiteInterpol(x,y,dy,n)
endfunction

% --------------------------------------------------
