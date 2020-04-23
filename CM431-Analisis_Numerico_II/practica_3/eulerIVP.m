#!/usr/bin/octave -qf

%  METODO DE EULER

%  resuelve las ecuaciones de primer orden de la forma

%  y' = f(t,y) a<=t<=b y(a) = alpha.

%  usa metodos de aproximacion punto a punto, t = a + ih

%  donde h  es el tamano de paso

%  f=@(x,y) x+y;
%  [x,w] = eulerIVP(f,0,2,y0,10);

%  en general se arma el sistema de y,y1,... y(n-1)
%  que representan las primera n-1 derivadas donde cada una se actualiza de la posterior
%  y = y + hy1
%  y1 = y1 + hy2
%  etc etc
%  yn-2 = yn-2 + hyn-3
%  yn-1 = yn-1 + f(y,y1,y2, ... , yn-1)
% ------------------------------------------------
function [t,w] = eulerIVP(fx,a,b,y0,n)
  % w son las aproximaciones a y
  f=fx;
  h = (b-a)/n;
  t=a:h:b;
  w=zeros(1,n+1);
  t(1) = a;
  w(1) = y0;
  for i=1:n
    w(i+1) = w(i) + h*f(t(i),w(i));
  endfor
endfunction

% --------------------------------------------------
