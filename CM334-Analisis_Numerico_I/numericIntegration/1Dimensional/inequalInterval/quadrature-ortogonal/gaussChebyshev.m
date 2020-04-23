#!/usr/bin/octave -qf

%  2. Metodo Gauss Hermite

%   Aproxima la funcion f(x) a un polinomio de grado 2n - 1 de legengre
%   En el intervalo [-1,1], con funcion peso w(x) = 1/sqrt(1-x*x)

%   El vector b se genera de la forma Int(-1,1) w(x) . Pn(x)
%   como w(x) = 1/sqrt(1-x*x)
%   se tiene Int(-1,1) 1/(1-x*x).Pn(x), con n=0,1,...,n-1.

%   Int(-1,1) 1/sqrt(1-t*t).t^(n-1) dt = pi/n

%   probar: gaussChebyshevIntegra('exp',1,2,3)
% ----------------------------------------------
function [xk,w]=gaussChebyshevAprox(N)
  % Grado N
  % xk: raices del polinomio aproximado de grado N
  if N<0, fprintf('\npolinomio Gauss-Chebyshev de orden negativo??\n');
  else
    xk=cos((2*(1:N)-1)*pi/2/N); % raices de chebyshev
    % se forma el sistema de ecuaciones (Vandermonde) para hallar los pesos
    b=ones(1,N)*pi/N;
    w=b;
    % pesos de la aproximacion
  endif
endfunction

% ----------------------------------------------
function I = gaussChebyshevIntegra(f,a,b,N)
  [t,w]=gaussChebyshevAprox(N);
  x=((b-a)*t+a+b)/2;
  fx = feval(f,x);
  % dx = (b-a)/2*dt
  I=w*fx'*(b-a)/2;
endfunction

% ----------------------------------------------
