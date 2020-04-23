#!/usr/bin/octave -qf

% resuelve problemas de forntera de la forma:

% -d(p(x).y'(x)) + q(x).y = f(x), para 0<=x<=1 y y(0)=y(1)=0
%  dx

% --------------------------------------------------

function [c] = rayleighRitzLineal(x,px,qx,fx)
  n=length(x)-2; % len = n+2
  p=px;q=qx;f=fx;
  for i=1:n+1
    h(i)=x(i+1)-x(i);
  endfor

  % definir los phi(x)
  
  for i=2:n
    Q1(i-1)=h(i)/12*(q(x(i))+q(x(i+1)));
    Q2(i-1)=h(i-1)/12*(3*q(x(i))+q(x(i-1)));
    Q3(i-1)=h(i)/12*(3*q(x(i))+q(x(i+1)));
    Q4(i-1)=h(i-1)/2*(p(x(i))+q(x(i-1)));
    Q5(i-1)=h(i-1)/6*(2*f(x(i))+f(x(i-1)));
    Q6(i-1)=h(i)/6*(2*f(x(i))+f(x(i+1)));
  endfor
  
  Q2(n)=h(n)/12*(3*q(x(n+1))+q(x(n)));
  Q3(n)=h(n+1)/12*(3*q(x(n+1))+q(x(n+2)));
  Q4(n)=h(n)/2*(p(x(n+1))+q(x(n)));
  Q4(n+1)=h(n+1)/2*(p(x(n+2))+q(x(n+1)));
  Q5(n)=h(n)/6*(2*f(x(n+1))+f(x(n)));
  Q6(n)=h(n+1)/6*(2*f(x(n+1))+f(x(n+2)));
  
  for i=1:n-1
    alpha(i)=Q4(i)+Q4(i+1)+Q2(i)+Q3(i);
    beta(i)=Q1(i)-Q4(i+1);
    b(i)=Q5(i)+Q6(i);
  endfor
  
  alpha(n)=Q4(n)+Q4(n+1)+Q2(n)+Q3(n);
  b(n)=Q5(n)+Q6(n);
  
  a(1)=alpha(1);
  l(1)=beta(1)/alpha(1);
  z(1)=b(1)/a(1);
  
  for i=2:n-1
    a(i)=alpha(i)-beta(i-1)/l(i-1);
    l(i)=beta(i)/alpha(i);
    z(i)=(b(i)-beta(i-1)*z(i-1))/a(i);
  endfor
  
  a(n)=alpha(n)-beta(n-1)*l(n-1);
  z(n)=(b(n)-beta(n-1)*z(n-1))/a(n);
  
  c(n)=z(n);
  
  for i=n-1:-1:1
    c(i)=z(i)-l(i)*c(i+1);
  endfor
endfunction

% px=@(x) 1;qx=@(x) pi^2;;fx=@(x) 2*pi^2*sin(pi*x);x=0:0.1:1;
