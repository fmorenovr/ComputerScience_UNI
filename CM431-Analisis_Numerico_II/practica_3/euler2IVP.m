#!/usr/bin/octave -qf

%  METODO DE EULER

%  Euler de de orden 2, u = y'
% --------------------------------------------------
function [x,y,u]=euler2IVP(fx,a,b,y0,u0,n)
  f=fx;
  h=(b-a)/n;
  x=a:h:b;
  y=zeros(1,n+1);
  y(1)=y0;
  u=zeros(1,n+1);
  u(1)=u0;
  for i=1:n
    y(i+1)=y(i)+h*u(i); % u = ( y(i+1) - y(i) )/ h
    u(i+1)=u(i)+h*f(x(i),y(i),u(i)); % actualizo la segunda derivada
  endfor
endfunction

% --------------------------------------------------
