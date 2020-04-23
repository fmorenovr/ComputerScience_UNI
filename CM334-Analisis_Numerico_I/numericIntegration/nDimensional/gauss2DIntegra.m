#!/usr/bin/octave -qf

%  Metodo de gauss para 2 dimensiones

%  Con integrales dobles del tipo:

%  Int(a,b) Int(c(x),d(x)) f(x,y) dy dx

% ----------------------------------
function [J] = simpson2DIntegra(fx,a,b,cx,dx,n,m)
  h1=(b-a)/2; h2=(b+a)/2;
  J=0;
  f = fx;
  c = cx;
  d = dx;
  for i=1:m
    JX=0;
    x=h1*r(m,i) + h2;
    d1=d(x); c1=c(x);
    k1=(d1 - c1)/2;
    k2=(d1 + c1)/2;
    for j=1:n
      y=k1*r(m,j) + k2;
      Q=f(x,y);
      JX = JX + Q;
    endfor
    J = J + c(m,i)*k*JX;
  endfor
  J=h1*J;
endfunction
