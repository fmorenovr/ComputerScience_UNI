#!/usr/bin/octave -qf

% ------------------------------------------------

function [x,w] = diferenciaFinitaNoLineal(fx,fyx,fy1x,a,b,ya,yb,n,tol,numIter)
  h=(b-a)/(n+1);
  w=zeros(1,n+2);
  w(1)=ya;w(n+2)=yb;
  f=fx;
  fy=fyx;
  fy1=fy1x;

  for i=2:n+1
    w(i)= ya + (i-1)*(yb-ya)/(b-a)*h;
  endfor
  
  a1=zeros(1,n);
  b1=zeros(1,n);
  c=zeros(1,n);
  d=zeros(1,n);
  u=zeros(1,n);
  z=zeros(1,n);
  v=zeros(1,n);
  l=zeros(1,n);
  
  k=1;
  
  while k<=numIter
    x=a+h;
    t=(w(3)-ya)/(2*h);
    a1(1)=2+h*h*fy(x,w(2),t);
    b1(1)=-1+0.5*h*fy1(x,w(2),t);
    d(1)=-1.0*(2*w(2)-w(3)-ya+h*h*f(x,w(2),t));
    
    for i=2:n-1
      x=a+i*h;
      t=(w(i+2)-w(i))/(2*h);
      a1(i)=2+h*h*fy(x,w(i+1),t);
      b1(i)=-1+0.5*h*fy1(x,w(i+1),t);
      c(i)=-1-0.5*h*fy1(x,w(i+1),t);
      d(i)=-1.0*(2*w(i+1)-w(i+2)-w(i)+h*h*f(x,w(i+1),t));
    endfor
    
    x=b-h;
    t=(yb-w(n))/(2*h);
    a1(n)=2+h*h*fy(x,w(n+1),t);
    c(n)=-1-0.5*h*fy1(x,w(n+1),t);
    d(n)=-1.0*(2*w(n+1)-w(n)-yb+h*h*f(x,w(n+1),t));
    
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
    
    v(n)=z(n);
    w(n+1)=w(n+1)+v(n);
    
    for i=n:-1:2
      v(i-1)=z(i-1)-u(i-1)*v(i);
      w(i)=w(i)+v(i-1);
    endfor
    
    if norm(v)<=tol
      for i=1:n+2
        x(i)=a+(i-1)*h;
        fprintf("\nx:%1.8f y(x):%1.8f\n",x(i),w(i));
      endfor
      
      return;
    endif
    
    k=k+1;
  endwhile
  disp('Numero de iteraciones excedido!!');
endfunction

% fx=@(a,b,c) (32+2*a^3-b*c)/8;fyx=@(a,b,c) -c/8;fy1x=@(a,b,c) -b/8;a=1;b=3;ya=17;yb=43/3;n=19;tol=1e-5;numIter=10;
