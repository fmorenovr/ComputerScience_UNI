#!/usr/bin/octave -qf

%  METODO DE RUNGE-KUTTA

%  usa hasta la 4 derivada para resolver y' = f(t,y)
% --------------------------------------------------
function [x,y] =rungeKuttaIVP(fx,a,b,y0,n)
  f=fx;
  h=(b-a)/n;
  x=a:h:b;
  y=zeros(n+1,1); %reserva memoria para n elementos del vector x
  y(1)=y0;
  for i=1:n
      k1=h*f(x(i),y(i));
      k2=h*f(x(i)+h/2,y(i)+k1/2);
      k3=h*f(x(i)+h/2,y(i)+k2/2);
      k4=h*f(x(i)+h,y(i)+k3);
      y(i+1)=y(i)+(k1+2*k2+2*k3+k4)/6;
   endfor
endfunction

% --------------------------------------------------
