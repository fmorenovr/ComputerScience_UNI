function frunge2_2()
  a = -5;
  b = 5;
  N=8;
  h = pi/N;
  y = 0:h:pi;
  xm = -cos(y);
  x = (a+b)/2 - ((b-a)/2)*xm;
  f = feval('f1',x);
  dt = 1e-03;
  s = a:dt:b;
  tiempo_inicio=cputime;
  [f,p] = difd(f,x,s);
  fs = feval('f1',s);
  total = cputime - tiempo_inicio;
  maX = max(abs(fs-p));
  fprintf("%i : %0.4f %f\n",N,total,maX);
  plot(s,fs,'r-','Linewidth',2);
  hold on
  plot(s,p,'b-','Linewidth',2);
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
  N=12;
  h = pi/N;
  y = 0:h:pi;
  xm = -cos(y);
  x = (a+b)/2 - ((b-a)/2)*xm;
  f = feval('f1',x);
  dt = 1e-03;
  s = a:dt:b;
  tiempo_inicio=cputime;
  [f,p] = difd(f,x,s);
  fs = feval('f1',s);
  total = cputime - tiempo_inicio;
  maX = max(abs(fs-p));
  fprintf("%i : %0.4f %f\n",N,total,maX);
  plot(s,p,'g-','Linewidth',2);
  hold on
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
  N=16;
  h = pi/N;
  y = 0:h:pi;
  xm = -cos(y);
  x = (a+b)/2 - ((b-a)/2)*xm;
  f = feval('f1',x);
  dt = 1e-03;
  s = a:dt:b;
  tiempo_inicio=cputime;
  [f,p] = difd(f,x,s);
  fs = feval('f1',s);
  total = cputime - tiempo_inicio;
  maX = max(abs(fs-p));
  fprintf("%i : %0.4f %f\n",N,total,maX);
  plot(s,p,'y-','Linewidth',2);
  hold on
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
  N=20;
  h = pi/N;
  y = 0:h:pi;
  xm = -cos(y);
  x = (a+b)/2 - ((b-a)/2)*xm;
  f = feval('f1',x);
  dt = 1e-03;
  s = a:dt:b;
  tiempo_inicio=cputime;
  [f,p] = difd(f,x,s);
  fs = feval('f1',s);
  total = cputime - tiempo_inicio;
  maX = max(abs(fs-p));
  fprintf("%i : %0.4f %f\n",N,total,maX);
  plot(s,p,'m-','Linewidth',2);
  hold on
  xlabel('x')
  legend('f(x)','Pn(x)')
  grid on
end
