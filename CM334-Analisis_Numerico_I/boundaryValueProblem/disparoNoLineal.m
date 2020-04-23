#!/usr/bin/octave -qf

% --------------------------------------------------

function [x1,w1,w2] = disparoNoLineal(fx,fyx,fy1x,a,b,ya,yb,n,tol,numIter)
  h=(b-a)*1.0/n;
  f=fx;
  fy=fyx;
  fy1=fy1x;
  k=1;
  TK=(yb-ya)/(b-a);
  u1=zeros(1,n+1);
  u2=zeros(1,n+1);
  w1=zeros(1,n+1);
  w2=zeros(1,n+1);
  while k<= numIter
    w1(1)=ya;
    w2(1) = TK;
    u1=0;
    u2=1;
    for i=1:n
      x=a+(i-1)*h;
      k1(1)=h*w2(i);
      k1(2)=h*f(x,w1(i),w2(i));
      
      k2(1)=h*(w2(i)+0.5*k1(2));
      k2(2)=h*f(x+0.5*h,w1(i)+0.5*k1(1),w2(i)+0.5*k1(2));
      
      k3(1)=h*(w2(i)+0.5*k2(2));
      k3(2)=h*f(x+0.5*h,w1(i)+0.5*k2(1),w2(i)+0.5*k2(2));
      
      k4(1)=h*(w2(i)+k3(2));
      k4(2)=h*f(x+h,w1(i)+k3(1),w2(i)+k3(2));
      
      w1(i+1)=w1(i) + (k1(1) + 2*k2(1) + 2*k3(1) + k4(1))/6;
      w2(i+1)=w2(i) + (k1(2) + 2*k2(2) + 2*k3(2) + k4(2))/6;
      
      k_1(1)=h*u2;
      k_1(2)=h*(fy(x,w1(i),w2(i))*u1+fy1(x,w1(i),w2(i))*u2);
      
      k_2(1)=h*(u2 + 0.5*k_1(2));
      k_2(2)=h*(fy(x+0.5*h,w1(i),w2(i))*(u1+0.5*k_1(1))+fy1(x+0.5*h,w1(i),w2(i))*(u2+0.5*k_1(2)));
      
      k_3(1)=h*(u2 + 0.5*k_2(2));
      k_3(2)=h*(fy(x+0.5*h,w1(i),w2(i))*(u1+0.5*k_2(1))+fy1(x+0.5*h,w1(i),w2(i))*(u2+0.5*k_2(2)));
      
      k_4(1)=h*(u2+k_3(2));
      k_4(2)=h*(fy(x+h,w1(i),w2(i))*(u1+k_3(1)) + fy1(x+h,w1(i),w2(i))*(u2+k_3(2)));
      
      u1=u1+(k_1(1)+2*k_2(1)+2*k_3(1)+k_4(1))/6;
      u2=u2+(k_1(2)+2*k_2(2)+2*k_3(2)+k_4(2))/6;
      
    endfor
    if abs(w1(n+1)-yb)<=tol
      for i=1:n+1
        x1(i)=a+(i-1)*h;
        fprintf("\nx:%0.8f y(x):%0.8f y'(x):%0.8f\n",x1(i),w1(i),w2(i));
      endfor
      return;
    endif
    TK = TK - (w1(n+1)-yb)/u1;
    k=k+1;
  endwhile
  disp('Excedio el numero de iteraciones');
endfunction

% fx=@(a,b,c) (32+2*a^3-b*c)/8;fyx=@(a,b,c) -c/8;fy1x=@(a,b,c) -b/8;a=1;b=3;ya=17;yb=43/3;n=20;tol=1e-5;numIter=1;

% [x,y,y1]=disparoNoLineal(fx,fyx,fy1x,a,b,ya,yb,20,tol,10);
