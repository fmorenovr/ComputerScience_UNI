#!/usr/bin/octave -qf

%  METODO DE HEUN

%  resuelve las ecuaciones de primer orden de la forma

%  y' = f(t,y) a<=t<=b y(a) = alpha.

%  usa metodos de aproximacion punto a punto, t = a + ih

%  donde h  es el tamano de paso
%  usando hasta la segunda derivada

%  f=@(x,y) x+y;
%  [x,w] = heunIVP(f,0,2,y0,10);

% ------------------------------------------------
function [t,w] = heunIVP(fx,a,b,y0,n)
  % w son las aproximaciones a y
  f=fx;
  h = (b-a)/n;
  t=a:h:b;
  w=zeros(1,n+1);
  t(1) = a;
  w(1) = y0;
  for i=1:n
    w(i+1) = w(i) + h*f(t(i),w(i));
    w(i+1) = w(i) + h/2*( f(t(i),w(i)) + f(t(i+1),w(i+1)) );
  endfor
endfunction

% --------------------------------------------------
