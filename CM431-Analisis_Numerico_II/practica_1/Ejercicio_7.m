#!/usr/bin/octave -qf

%{
function frunge2(N)
  a = -5;
  b = 5;
  h = pi/N;
  y = 0:h:pi;
  xm = -cos(y);
  x = (a+b)/2 + ((b-a)/2)*xm;
  f = feval('f1',x);
  dt = 1e-03;
  s = a:dt:b;
  [f,p] = difd(f,x,s);
  fs = feval('f1',s);
  plot(s,fs,'b-','Linewidth',2)
  hold on
  plot(s,p,'r-','Linewidth',2)
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
end
%}

n = input('Ingrese numero de puntos: ');

frunge2(n);
