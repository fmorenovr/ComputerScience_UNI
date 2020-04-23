#!/usr/bin/octave -qf

%{
function frunge1(n)
  % n: grado del pol
  % a,b limites de intervalo
  a=-5;
  b=5;
  h=(b-a)/n;
  x=a:h:b;
  f=feval('f1',x);
  dt=1e-03;
  s=a:dt:b;
  [f,p]=difd(f,x,s);
  fs=feval('f1',s);
  plot(s,fs,'b-','Linewidth',2)
  hold on
  plot(s,p,'r-','Linewidth',2)
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
end
%}

clear;clc;

n = input("Ingrese numero de puntos: ")

frunge1(n);
