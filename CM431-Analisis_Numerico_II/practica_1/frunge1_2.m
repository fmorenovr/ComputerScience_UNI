function [fs,fxx] = frunge1()
  % n: grado del pol
  % a,b limites de intervalo
  a=-5;
  b=5;
  n=8;
  h=(b-a)/n;
  x=a:h:b;
  f=feval('f1',x); % y 
  fx = polyfit(x,f,n);
  dt=1e-03;
  s=a:dt:b;
  tiempo_inicio=cputime;
  fxx = polyval(fx,s);
  fs=feval('f1',s);
  total = cputime - tiempo_inicio;
  maX = max(abs(fs-fxx));
  fprintf("%i : %0.4f %f\n",n,total,maX);
  plot(s,fxx,'b-','Linewidth',2);
  hold on
  plot(s,fs,'r-','Linewidth',2);
  xlabel('x')
  legend('Pn(x)','f(x)')
  grid on
  n=12;
  h=(b-a)/n;
  x=a:h:b;
  f=feval('f1',x); % y 
  fx = polyfit(x,f,n);
  dt=1e-03;
  s=a:dt:b;
  tiempo_inicio=cputime;
  fxx = polyval(fx,s);
  fs=feval('f1',s);
  total = cputime - tiempo_inicio;
  maX = max(abs(fs-fxx));
  fprintf("%i : %0.4f %f\n",n,total,maX);
  plot(s,fxx,'g-','Linewidth',2);
  hold on
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
  n=16;
  h=(b-a)/n;
  x=a:h:b;
  f=feval('f1',x); % y 
  fx = polyfit(x,f,n);
  dt=1e-03;
  s=a:dt:b;
  tiempo_inicio=cputime;
  fxx = polyval(fx,s);
  fs=feval('f1',s);
  total = cputime - tiempo_inicio;
  maX = max(abs(fs-fxx));
  fprintf("%i : %0.4f %f\n",n,total,maX);
  plot(s,fxx,'y-','Linewidth',2);
  hold on
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
  n=20;
  h=(b-a)/n;
  x=a:h:b;
  f=feval('f1',x); % y 
  fx = polyfit(x,f,n);
  dt=1e-03;
  s=a:dt:b;
  tiempo_inicio=cputime;
  fxx = polyval(fx,s);
  fs=feval('f1',s);
  total = cputime - tiempo_inicio;
  maX = max(abs(fs-fxx));
  fprintf("%i : %0.4f %f\n",n,total,maX);
  plot(s,fxx,'m-','Linewidth',2);
  hold on
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
end
