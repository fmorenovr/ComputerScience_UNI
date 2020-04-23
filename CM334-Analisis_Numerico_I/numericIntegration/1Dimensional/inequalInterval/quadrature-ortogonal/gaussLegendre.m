#!/usr/bin/octave -qf

%  2. Metodo Gauss Legendre

%   Aproxima la funcion f(x) a un polinomio de grado 2n - 1 de legengre
%   En el intervalo [-1,1], con funcion peso w(x) = 1

%   El vector b se genera de la forma Int(-1,1) w(x) . Pn(x)
%   como w(x) = 1,
%   se tiene Int(-1,1) Pn(x), con n=0,1,...,n-1.

%   Int(-1,1) t^(n-1) dt = ( 1 - (-1)^n )/n

%   probar: gaussLegendreIntegra('exp',1,2,3)

% ----------------------------------------------
function [xk,w]=gaussLegendreAprox(N)
  % Grado N
  % xk: raices del polinomio aproximado de grado N
  if N<0, fprintf('\npolinomio Gauss-Legendre de orden negativo??\n');
  else
    xk=roots(legendrePoly(N))';
    % se forma el sistema de ecuaciones (Vandermonde) para hallar los pesos
    A(1,:)=ones(1,N);
    b=ones(1,N);
    b(1)=2;
    for n=2:N
      A(n,:)=A(n-1,:).*xk;
      if mod(n,2)==0, b(n) = 0;
      else b(n) = 2/n;
      endif
    endfor
    w=b/A';
    % pesos de la aproximacion
  endif
endfunction

% ----------------------------------------------
function I = gaussLegendreIntegra(f,a,b,N)
  [t,w]=gaussLegendreAprox(N);
  x=((b-a)*t+a+b)/2; % cambiando el intervalo a legendre
  fx = feval(f,x);
  % dx = (b-a)/2*dt
  I=w*fx'*(b-a)/2;
endfunction

% ----------------------------------------------
