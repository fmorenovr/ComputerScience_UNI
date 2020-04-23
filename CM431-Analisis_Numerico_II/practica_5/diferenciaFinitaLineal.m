#!/usr/bin/octave -qf

% ------------------------------------------------

function [x1,w] = diferenciaFinitaLineal(a,b,px,qx,rx,ya,yb,n)
  h=(b-a)/(n+1);
  x=a+h;
  p=px;
  q=qx;
  r=rx;
  
  a1=zeros(1,n);
  b1=zeros(1,n);
  c=zeros(1,n);
  d=zeros(1,n);
  u=zeros(1,n);
  z=zeros(1,n);
  l=zeros(1,n);
  w=zeros(1,n+1);
  
  a1(1)=2+h*h*q(x);
  b1(1)=-1+0.5*h*p(x);
  d(1)=-h*h*r(x)+ya*(1+0.5*h*p(x));
  
  for i=2:n-1
    x=a+i*h;
    a1(i)=2+h*h*q(x);
    b1(i)=-1+0.5*h*p(x);
    c(i)=-1-0.5*h*p(x);
    d(i)=-h*h*r(x);
  endfor
  
  x=b-h;
  a1(n)=2+h*h*q(x);
  c(n)=-1-0.5*h*p(x);
  d(n)=-h*h*r(x)+yb*(1-0.5*h*p(x));
  
  l(1)=a1(1);
  u(1)=b1(1)/a1(1);
  z(1)=d(1)/l(1);
  
  for i=2:n-1
    l(i)=a1(i)-c(i)*u(i-1);
    u(i)=b1(i)/l(i);
    z(i)=(d(i)-c(i)*z(i-1))/l(i);
  endfor
  
  l(n)=a1(n)-c(n)*u(n-1);
  z(n)=(d(n)-c(n)*z(n-1))/l(n);
  
  w(1)=ya;w(n+2)=yb;w(n+1)=z(n);
  
  for i=n:-1:2
    w(i)=z(i-1)-u(i-1)*w(i+1);
  endfor
  
  for i=1:n+2
    x1(i)=a+(i-1)*h;
    fprintf("\nx:%1.8f y(x):%1.8f\n",x1(i),w(i));
  endfor
endfunction

% px=@(x) -2/x;qx=@(x) 2/x/x;rx=@(x) sin(log(x))/x/x;a=1;b=2;ya=1;yb=2;
