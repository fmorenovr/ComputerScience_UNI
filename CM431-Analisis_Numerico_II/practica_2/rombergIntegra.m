#!/usr/bin/octave -qf

%  6. Metodo de Romberg

%   mediante integracion por trapecios, simpson y extrapolacion de Richardson
%   aproxima la integral de manera recursiva
%   donde se construye un vector de aproximaciones R
%   R(1,1) = h/2*(fa+fb)
%   R(n,1) = 1/2*R(n-1,1) + hn*Sum(k=1,2^n -1) f(a+(2k-1)hn)
%   R(n,m) = R(n,m-1) + (1/(4^m -1))*(R(n,m-1)-R(n-1,m-1))
%   n>=m, m>=1, hn = (b-a)/2^n

%   donde R(n,1) es trapezoidalRule con 2^n + 1 puntos
%   donde R(n,2) es simpsonRule con 2^n + 1 puntos
%   donde R(n,3) es booleRule con 2^n + 1 puntos

% --------------------------------------------------
function [R] = rombergIntegra(fx,a,b,n)
  f=fx;
  R=zeros(n,n);
  h = 1.0*(b-a);
  R(1,1) = 0.5*h*(f(a)+f(b));
  for i=2:n
    % aproximaciones por metodo de trapecio
    R(i,1)=R(i-1,1);
    sum = 0.0;
    index = 2^(i-2);
    for k=1:index
      sum = sum + h*f(a+(k-0.5)*h);
    endfor
    R(i,1) = R(i,1) + sum;
    R(i,1) = 0.5*(R(i,1));
    % extrapolacion de Richardson
    for j=2:i
      R(i,j) = R(i,j-1)+1.0/(4^(j-1)-1)*(R(i,j-1)-R(i-1,j-1));
    endfor
    h=h/2.0;
  endfor
end
