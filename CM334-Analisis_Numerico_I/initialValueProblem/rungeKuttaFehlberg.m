#!/usr/bin/octave -qf

%  METODO DE RUNGE-KUTTA-FEHLGBERG

%  usa hasta la 4 derivada para resolver y' = f(t,y)
% --------------------------------------------------
function [t,w] =rungeKuttaFehlbergIVP(fx,a,b,y0,tol,hmin,hmax)
  f=fx;
  h=hmax;
  BAND=1;
  t=a;
  w=y0;

  while BAND==1
    i=1;
    k1 = h*f(t,w);
    k2 = h*f(t+h/4,w+k1/4);
    k3 = h*f(t+3/8*h,w+3/32*k1+9/32*k2);
    k4 = h*f(t+12/13*h,w+1932/2197*k1-7200/2197*k2+7296/2197*k3);
    k5 = h*f(t+h,w+439/216*k1-8*k2+3680/513*k3-845/4104*k4);
    k6 = h*f(t+h/2,w-8/27*k1+2*k2-3544/2565*k3+1859/4104*k4-11/40*k5);
    
    R = abs(k1/360-128/4275*k3-2197*k4/75240+k5/50+2/55*k6)/h;
    
    if R<=tol
      t=t+h;
      w=w+25/216*k1+1408*k3/2565+2197*k4/4104-k5/5;
    endif
    
    rho = 0.84*sqrt(sqrt(tol/R));
    if rho<=0.1
      h=h*0.1;
    elseif rho >=4
      h=4*h;
    else
      h = rho*h;
    endif
    if h>hmax
      h=hmax;
    endif
    if t>=b
      BAND=0;
    elseif t+h>b
      h=b-t;
    elseif h<hmin
      BAND=0;
      disp('Fallo procedimiento');
      break;
    else;
    endif
    fprintf("%3.6f  %3.6f\n",t,w);
  endwhile
endfunction

% --------------------------------------------------
%  f=@(t,y) y - t^2 +1;
%  [t,w]=rungeKuttaFehlbergIVP(f,0,2,0.5,1e-5,0.01,0.25);
