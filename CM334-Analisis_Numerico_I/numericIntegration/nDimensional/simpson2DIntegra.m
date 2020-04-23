#!/usr/bin/octave -qf

%  Metodo de simpson para 2 dimensiones

%  Con integrales dobles del tipo:

%  Int(a,b) Int(c(x),d(x)) f(x,y) dy dx

% ----------------------------------
function [J] = simpson2DIntegra(fx,a,b,cx,dx,n,m)
  h = (b-a)/(2*n);
  f = fx;
  c = cx;
  d = dx;
  J1=0; % extremos
  J2=0; % pares
  J3=0; % impares
  for i = 0:2*n
    x = a + i*h;
    HX = (d(x) - c(x))/(2*m);
    K1 = f(x,c(x)) + f(x,d(x)); % extremos
    K2 = 0; % pares
    K3 = 0; % impares
    for j = 1:2*m-2
      y = c(x) + j*HX;
      Q = f(x,y);
      if mod(j,2)==0
        K2 = K2 + Q;
      else
        K3 = K3 + Q;
      endif
    endfor
    L = (K1 + 2*K2 + 4*K3)*HX/3.0; % L = int(c(xi),d(xi)) f(xi,y) dy
    if i==0 | i==2*n
      J1 = J1 + L;
    else
      if mod(i,2)==0
        J2 = J2 + L;
      else
        J3 = J3 + L;
      endif
    endif
  endfor
  J = h*(J1 + 2*J2 + 4*J3)/3.0;
endfunction

% ----------------------------------
% [J]=simpson2DIntegra(f,a,b,c,d,n,m);
% d=@(x) x^2;c=@(x) x^3;a=0.1;b=0.5;n=10;m=15;
% f=@(x,y) exp(y/x);
