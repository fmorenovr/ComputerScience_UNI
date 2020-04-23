function frunge1(n)
  % n: grado del pol
  % a,b limites de intervalo
  a=-5;
  b=5;
  h=(b-a)/n;
  x=a:h:b;
  f=feval('f1',x); % y 
  fx = polyfit(x,f,n);
  dt=1e-03;
  s=a:dt:b;
  fxx = polyval(fx,s);
  fs=feval('f1',s);
  plot(s,fxx,'b-','Linewidth',2);
  hold on
  plot(s,fs,'r-','Linewidth',2);
  xlabel('x')
  legend('Pn(x)','f(x)')
  grid on
end
