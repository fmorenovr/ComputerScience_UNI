#!/usr/bin/octave -qf

%  1. Metodo Gauss Hermite

%   Aproxima la funcion f(x) a un polinomio de grado 2n - 1 de legengre
%   En el intervalo [-Inf,Inf], con funcion peso w(x) = e^(-x*x)

%   El vector b se genera de la forma Int(-Inf,Inf) w(x) . Pn(x)
%   como w(x) = e^(-x*x)
%   se tiene Int(-Inf,Inf) e^(-x*x).Pn(x), con n=0,1,...,n-1.

%   Int(-1,1) e^(-t*t).t^(n-1) dt = RHS(n)
%   si n es impar, la integral es 0.
%   cuando n=0, la integral es sqrt(pi)
%   cuando n es par, RHS(n) = (n-2)/2*RHS(n-2)

%   probar: gaussHermiteIntegra('exp',1,2,3)

% ----------------------------------------------
function [xk,w]=gaussHermiteAprox(N)
  % Grado N
  % xk: raices del polinomio aproximado de grado N
  if N<0, fprintf('\npolinomio Gauss-Hermite de orden negativo??\n');
  else
    xk=roots(hermitePoly(N))';
    % se forma el sistema de ecuaciones (Vandermonde) para hallar los pesos
    A(1,:)=ones(1,N);
    b=ones(1,N);
    b(1)=sqrt(pi);
    for n=2:N
      A(n,:)=A(n-1,:).*xk;
      if mod(n-1,2)==0, b(n) = (n-2)/2*b(n-2);
      else b(n) = 0;
      endif
    endfor
    w=b/A';
    % pesos de la aproximacion
  endif
endfunction

% ----------------------------------------------
function I = gaussHermiteIntegra(f,a,b,N)
  [x,w]=gaussHermiteAprox(N);
  fx = feval(f,x);
  I=w*fx';
endfunction

% ----------------------------------------------
